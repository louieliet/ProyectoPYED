#include "WebServer.h"

/*
void strSplit(string & pStr, char pDelim, strVec & pOut)
{
    stringstream lStream(pStr);
    string lChunk;
    while (getline(lStream, lChunk, pDelim)) {
        pOut.push_back(lChunk);
        // cout << lChunk.c_str() << endl;
    }
} // strSplit */

MyHTTPSrv::MyHTTPSrv(wchar_t *pDomain, wchar_t *pPort)
{
    if (pDomain)
        wcscpy_s(aDomain, pDomain);
    else
        wcscpy_s(aDomain, L"localhost");
    if (pPort)
        wcscpy_s(aPort, pPort);
    else
        wcscpy_s(aPort, L"8080");

    wcscpy_s(aURL, L"http://");
    wcscat_s(aURL, aDomain);
    wcscat_s(aURL, L":");
    wcscat_s(aURL, aPort);
    wcscat_s(aURL, L"/");

    aGetFuncW = NULL;
    aGetFuncS = NULL;
} // Constructor

void MyHTTPSrv::SetGetFunc(string (*pGetFuncW)(PCWSTR))
{
    if (pGetFuncW)
        aGetFuncW = pGetFuncW;
} // SetGetFunc

void MyHTTPSrv::SetGetFunc(string(*pGetFuncS)(string))
{
    if (pGetFuncS)
        aGetFuncS = pGetFuncS;
} // SetGetFunc

/*******************************************************************++

Routine Description:
The function to receive a request. This function calls the
corresponding function to handle the response.

Arguments:
hReqQueue - Handle to the request queue

Return Value:
Success/Failure.

--*******************************************************************/
DWORD MyHTTPSrv::DoReceiveRequests(
    IN HANDLE hReqQueue
)
{
    ULONG              result;
    HTTP_REQUEST_ID    requestId;
    DWORD              bytesRead;
    PHTTP_REQUEST      pRequest;
    PCHAR              pRequestBuffer;
    ULONG              RequestBufferLength;
    
    string lRes = "";
    wstring lWCaller = L"";
    string lCaller = "";

    //
    // Allocate a 2 KB buffer. This size should work for most 
    // requests. The buffer size can be increased if required. Space
    // is also required for an HTTP_REQUEST structure.
    //
    RequestBufferLength = sizeof(HTTP_REQUEST) + 20480;
    pRequestBuffer = (PCHAR)ALLOC_MEM(RequestBufferLength);

    if (pRequestBuffer == NULL)
    {
        return ERROR_NOT_ENOUGH_MEMORY;
    }

    pRequest = (PHTTP_REQUEST)pRequestBuffer;

    //
    // Wait for a new request. This is indicated by a NULL 
    // request ID.
    //

    HTTP_SET_NULL_ID(&requestId);

    for (;;)
    {
        RtlZeroMemory(pRequest, RequestBufferLength);

        result = HttpReceiveHttpRequest(
            hReqQueue,          // Req Queue
            requestId,          // Req ID
            0,                  // Flags
            pRequest,           // HTTP request buffer
            RequestBufferLength,// req buffer length
            &bytesRead,         // bytes received
            NULL                // LPOVERLAPPED
        );
        if (NO_ERROR == result)
        {
            //
            // Worked! 
            // 
            switch (pRequest->Verb)
            {
            case HttpVerbGET:
                wprintf(L"Got a GET request for %ws \n",
                    pRequest->CookedUrl.pFullUrl);

                lWCaller = pRequest->CookedUrl.pFullUrl;
                lCaller = string(lWCaller.begin(), lWCaller.end());

                lRes = "Hey! You hit the server \r\n";
                if (aGetFuncS) {
                    lRes = aGetFuncS(lCaller);
                }

                result = SendHttpResponse(
                    hReqQueue,
                    pRequest,
                    200,
                    (PSTR)"OK",
                    (PSTR)lRes.c_str()
                );

                break;

            case HttpVerbPOST:

                wprintf(L"Got a POST request for %ws \n",
                    pRequest->CookedUrl.pFullUrl);

                result = SendHttpPostResponse(hReqQueue, pRequest);
                break;

            default:
                wprintf(L"Got a unknown request for %ws \n",
                    pRequest->CookedUrl.pFullUrl);

                result = SendHttpResponse(
                    hReqQueue,
                    pRequest,
                    503,
                    (PSTR)"Not Implemented",
                    NULL
                );
                break;
            }

            if (result != NO_ERROR)
            {
                break;
            }

            //
            // Reset the Request ID to handle the next request.
            //
            HTTP_SET_NULL_ID(&requestId);
        }
        else if (result == ERROR_MORE_DATA)
        {
            //
            // The input buffer was too small to hold the request
            // headers. Increase the buffer size and call the 
            // API again. 
            //
            // When calling the API again, handle the request
            // that failed by passing a RequestID.
            //
            // This RequestID is read from the old buffer.
            //
            requestId = pRequest->RequestId;

            //
            // Free the old buffer and allocate a new buffer.
            //
            RequestBufferLength = bytesRead;
            FREE_MEM(pRequestBuffer);
            pRequestBuffer = (PCHAR)ALLOC_MEM(RequestBufferLength);

            if (pRequestBuffer == NULL)
            {
                result = ERROR_NOT_ENOUGH_MEMORY;
                break;
            }

            pRequest = (PHTTP_REQUEST)pRequestBuffer;

        }
        else if (ERROR_CONNECTION_INVALID == result &&
            !HTTP_IS_NULL_ID(&requestId))
        {
            // The TCP connection was corrupted by the peer when
            // attempting to handle a request with more buffer. 
            // Continue to the next request.

            HTTP_SET_NULL_ID(&requestId);
        }
        else
        {
            break;
        }

    }

    if (pRequestBuffer)
    {
        FREE_MEM(pRequestBuffer);
    }

    return result;
}

/*******************************************************************++

Routine Description:
    The routine sends a HTTP response

Arguments:
    hReqQueue     - Handle to the request queue
    pRequest      - The parsed HTTP request
    StatusCode    - Response Status Code
    pReason       - Response reason phrase
    pEntityString - Response entity body

Return Value:
    Success/Failure.
--*******************************************************************/

DWORD MyHTTPSrv::SendHttpResponse(
    IN HANDLE        hReqQueue,
    IN PHTTP_REQUEST pRequest,
    IN USHORT        StatusCode,
    IN PSTR          pReason,
    IN PSTR          pEntityString
)
{
    HTTP_RESPONSE   response;
    HTTP_DATA_CHUNK dataChunk;
    DWORD           result;
    DWORD           bytesSent;

    //
    // Initialize the HTTP response structure.
    //
    INITIALIZE_HTTP_RESPONSE(&response, StatusCode, pReason);

    //
    // Add a known header.
    //
    ADD_KNOWN_HEADER(response, HttpHeaderContentType, "text/html");

    if (pEntityString)
    {
        // 
        // Add an entity chunk.
        //
        dataChunk.DataChunkType = HttpDataChunkFromMemory;
        dataChunk.FromMemory.pBuffer = pEntityString;
        dataChunk.FromMemory.BufferLength =
            (ULONG)strlen(pEntityString);

        response.EntityChunkCount = 1;
        response.pEntityChunks = &dataChunk;
    }

    // 
    // Because the entity body is sent in one call, it is not
    // required to specify the Content-Length.
    //

    result = HttpSendHttpResponse(
        hReqQueue,           // ReqQueueHandle
        pRequest->RequestId, // Request ID
        0,                   // Flags
        &response,           // HTTP response
        NULL,                // pReserved1
        &bytesSent,          // bytes sent  (OPTIONAL)
        NULL,                // pReserved2  (must be NULL)
        0,                   // Reserved3   (must be 0)
        NULL,                // LPOVERLAPPED(OPTIONAL)
        NULL                 // pReserved4  (must be NULL)
    );

    if (result != NO_ERROR)
    {
        wprintf(L"HttpSendHttpResponse failed with %lu \n", result);
    }

    return result;
}


#define MAX_ULONG_STR ((ULONG) sizeof("4294967295"))

/*******************************************************************++

Routine Description:
    The routine sends a HTTP response after reading the entity body.

Arguments:
    hReqQueue     - Handle to the request queue.
    pRequest      - The parsed HTTP request.

Return Value:
    Success/Failure.
--*******************************************************************/

DWORD MyHTTPSrv::SendHttpPostResponse(
    IN HANDLE        hReqQueue,
    IN PHTTP_REQUEST pRequest
)
{
    HTTP_RESPONSE   response;
    DWORD           result;
    DWORD           bytesSent;
    PUCHAR          pEntityBuffer;
    ULONG           EntityBufferLength;
    ULONG           BytesRead;
    ULONG           TempFileBytesWritten;
    HANDLE          hTempFile;
    TCHAR           szTempName[MAX_PATH + 1];
    CHAR            szContentLength[MAX_ULONG_STR];
    HTTP_DATA_CHUNK dataChunk;
    ULONG           TotalBytesRead = 0;

    BytesRead = 0;
    hTempFile = INVALID_HANDLE_VALUE;

    //
    // Allocate space for an entity buffer. Buffer can be increased 
    // on demand.
    //
    EntityBufferLength = 20480;
    pEntityBuffer = (PUCHAR)ALLOC_MEM(EntityBufferLength);

    if (pEntityBuffer == NULL)
    {
        result = ERROR_NOT_ENOUGH_MEMORY;
        wprintf(L"Insufficient resources \n");
        goto Done;
    }

    //
    // Initialize the HTTP response structure.
    //
    INITIALIZE_HTTP_RESPONSE(&response, 200, "OK");

    //
    // For POST, echo back the entity from the
    // client
    //
    // NOTE: If the HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY flag had been
    //       passed with HttpReceiveHttpRequest(), the entity would 
    //       have been a part of HTTP_REQUEST (using the pEntityChunks
    //       field). Because that flag was not passed, there are no
    //       o entity bodies in HTTP_REQUEST.
    //

    if (pRequest->Flags & HTTP_REQUEST_FLAG_MORE_ENTITY_BODY_EXISTS)
    {
        // The entity body is sent over multiple calls. Collect 
        // these in a file and send back. Create a temporary 
        // file.
        //

        if (GetTempFileName(
            L".",
            L"New",
            0,
            szTempName
        ) == 0)
        {
            result = GetLastError();
            wprintf(L"GetTempFileName failed with %lu \n", result);
            goto Done;
        }

        hTempFile = CreateFile(
            szTempName,
            GENERIC_READ | GENERIC_WRITE,
            0,                  // Do not share.
            NULL,               // No security descriptor.
            CREATE_ALWAYS,      // Overrwrite existing.
            FILE_ATTRIBUTE_NORMAL,    // Normal file.
            NULL
        );

        if (hTempFile == INVALID_HANDLE_VALUE)
        {
            result = GetLastError();
            wprintf(L"Cannot create temporary file. Error %lu \n",
                result);
            goto Done;
        }

        do
        {
            //
            // Read the entity chunk from the request.
            //
            BytesRead = 0;
            result = HttpReceiveRequestEntityBody(
                hReqQueue,
                pRequest->RequestId,
                0,
                pEntityBuffer,
                EntityBufferLength,
                &BytesRead,
                NULL
            );

            switch (result)
            {
            case NO_ERROR:

                if (BytesRead != 0)
                {
                    TotalBytesRead += BytesRead;
                    WriteFile(
                        hTempFile,
                        pEntityBuffer,
                        BytesRead,
                        &TempFileBytesWritten,
                        NULL
                    );
                }
                break;

            case ERROR_HANDLE_EOF:

                //
                // The last request entity body has been read.
                // Send back a response. 
                //
                // To illustrate entity sends via 
                // HttpSendResponseEntityBody, the response will 
                // be sent over multiple calls. To do this,
                // pass the HTTP_SEND_RESPONSE_FLAG_MORE_DATA
                // flag.

                if (BytesRead != 0)
                {
                    TotalBytesRead += BytesRead;
                    WriteFile(
                        hTempFile,
                        pEntityBuffer,
                        BytesRead,
                        &TempFileBytesWritten,
                        NULL
                    );
                }

                //
                // Because the response is sent over multiple
                // API calls, add a content-length.
                //
                // Alternatively, the response could have been
                // sent using chunked transfer encoding, by  
                // passimg "Transfer-Encoding: Chunked".
                //

                // NOTE: Because the TotalBytesread in a ULONG
                //       are accumulated, this will not work
                //       for entity bodies larger than 4 GB. 
                //       For support of large entity bodies,
                //       use a ULONGLONG.
                // 


                sprintf_s(szContentLength, MAX_ULONG_STR, "%lu", TotalBytesRead);

                ADD_KNOWN_HEADER(
                    response,
                    HttpHeaderContentLength,
                    szContentLength
                );

                result =
                    HttpSendHttpResponse(
                        hReqQueue,           // ReqQueueHandle
                        pRequest->RequestId, // Request ID
                        HTTP_SEND_RESPONSE_FLAG_MORE_DATA,
                        &response,       // HTTP response
                        NULL,            // pReserved1
                        &bytesSent,      // bytes sent-optional
                        NULL,            // pReserved2
                        0,               // Reserved3
                        NULL,            // LPOVERLAPPED
                        NULL             // pReserved4
                    );

                if (result != NO_ERROR)
                {
                    wprintf(
                        L"HttpSendHttpResponse failed with %lu \n",
                        result
                    );
                    goto Done;
                }

                //
                // Send entity body from a file handle.
                //
                dataChunk.DataChunkType =
                    HttpDataChunkFromFileHandle;

                dataChunk.FromFileHandle.
                    ByteRange.StartingOffset.QuadPart = 0;

                dataChunk.FromFileHandle.
                    ByteRange.Length.QuadPart =
                    HTTP_BYTE_RANGE_TO_EOF;

                dataChunk.FromFileHandle.FileHandle = hTempFile;

                result = HttpSendResponseEntityBody(
                    hReqQueue,
                    pRequest->RequestId,
                    0,           // This is the last send.
                    1,           // Entity Chunk Count.
                    &dataChunk,
                    NULL,
                    NULL,
                    0,
                    NULL,
                    NULL
                );

                if (result != NO_ERROR)
                {
                    wprintf(
                        L"HttpSendResponseEntityBody failed %lu\n",
                        result
                    );
                }

                goto Done;

                break;


            default:
                wprintf(
                    L"HttpReceiveRequestEntityBody failed with %lu \n",
                    result);
                goto Done;
            }

        } while (TRUE);
    }
    else
    {
        // This request does not have an entity body.
        //

        result = HttpSendHttpResponse(
            hReqQueue,           // ReqQueueHandle
            pRequest->RequestId, // Request ID
            0,
            &response,           // HTTP response
            NULL,                // pReserved1
            &bytesSent,          // bytes sent (optional)
            NULL,                // pReserved2
            0,                   // Reserved3
            NULL,                // LPOVERLAPPED
            NULL                 // pReserved4
        );
        if (result != NO_ERROR)
        {
            wprintf(L"HttpSendHttpResponse failed with %lu \n",
                result);
        }
    }

Done:

    if (pEntityBuffer)
    {
        FREE_MEM(pEntityBuffer);
    }

    if (INVALID_HANDLE_VALUE != hTempFile)
    {
        CloseHandle(hTempFile);
        DeleteFile(szTempName);
    }

    return result;
}


/*******************************************************************++

Routine Description:
    main routine

Arguments:
    argc - # of command line arguments.
    argv - Arguments.

Return Value:
    Success/Failure

--*******************************************************************/
int MyHTTPSrv::Run(void)
{
    ULONG           retCode;
    HANDLE          hReqQueue = NULL;
    int             UrlAdded = 0;
    HTTPAPI_VERSION HttpApiVersion = HTTPAPI_VERSION_1;

    //
    // Initialize HTTP Server APIs
    //
    retCode = HttpInitialize(
        HttpApiVersion,
        HTTP_INITIALIZE_SERVER,    // Flags
        NULL                       // Reserved
    );

    if (retCode != NO_ERROR)
    {
        wprintf(L"HttpInitialize failed with %lu \n", retCode);
        return retCode;
    }

    //
    // Create a Request Queue Handle
    //
    retCode = HttpCreateHttpHandle(
        &hReqQueue,        // Req Queue
        0                  // Reserved
    );

    if (retCode != NO_ERROR)
    {
        wprintf(L"HttpCreateHttpHandle failed with %lu \n", retCode);
        goto CleanUp;
    }

    //
    // The command line arguments represent URIs that to 
    // listen on. Call HttpAddUrl for each URI.
    //
    // The URI is a fully qualified URI and must include the
    // terminating (/) character.
    //

    wprintf(L"listening for requests on the following url: %s\n", aURL);

    retCode = HttpAddUrl(
        hReqQueue,  // Req Queue
        aURL,       // Fully qualified URL
        NULL        // Reserved
    );

    if (retCode != NO_ERROR)
    {
        wprintf(L"HttpAddUrl failed with %lu \n", retCode);
        goto CleanUp;
    }
    else
    {
        //
        // Track the currently added URLs.
        //
        UrlAdded++;
    }

    DoReceiveRequests(hReqQueue);

    CleanUp:

    //
    // Call HttpRemoveUrl for all added URLs.
    //
    for (int i = 1; i <= UrlAdded; i++)
    {
        HttpRemoveUrl(
            hReqQueue,  // Req Queue
            aURL        // Fully qualified URL
        );
    }

    //
    // Close the Request Queue handle.
    //
    if (hReqQueue)
    {
        CloseHandle(hReqQueue);
    }

    // 
    // Call HttpTerminate.
    //
    HttpTerminate(HTTP_INITIALIZE_SERVER, NULL);

    return retCode;
} // Run
