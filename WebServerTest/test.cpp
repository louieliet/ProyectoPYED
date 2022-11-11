#include "WebServer.h"

#include <fstream>

using namespace std;

#define KS_Path "C://temp/wroot/"

string gPath = "";

string fnGetTemplate(string pName)
{
    string lContent = "";

    string lPath = KS_Path + pName;
    ifstream lStream(lPath);
    stringstream lBuff;
    lBuff << lStream.rdbuf();
    lContent = lBuff.str();

    return lContent;
} // fnGetTemplate

strVec fnGetPath(string pCaller)
{
    strVec lParts;
    strVec lSects;
    strVec lPath;

    strSplit(pCaller, '?', lParts);
    if (lParts.size() == 0)
        lParts.push_back(pCaller);
    if (lParts.size() > 0) {
        strSplit(lParts[0], ':', lSects);
        if (lSects.size() >= 3)
            strSplit(lSects[2], '/', lPath);
    }

    return lPath;
} // fnGetPath

map<string, string> fnGetParams(string pCaller)
{
    strVec lParts;
    strVec lPrms;
    strVec lItem;
    map<string, string> lParams;

    strSplit(pCaller, '?', lParts);
    if (lParts.size() == 2) {
        strSplit(lParts[1], '&', lPrms);
        if (lPrms.size() > 0) {
            for (int lIdx = 0; lIdx < lPrms.size(); lIdx++) {
                strSplit(lPrms[lIdx], '=', lItem);
                if (lItem.size() == 2)
                    lParams.insert(pair<string, string>(lItem[0], lItem[1]));
                else
                    lParams.insert(pair<string, string>(lItem[0], ""));
                lItem.clear();
            }
        }
    }

    return lParams;
} // fnGetParams

string fnGetIndexedEP(void)
{
    string lRes = fnGetTemplate("indexed.tpl.html");
    //strReplace(lRes, "{{pData}}", "");

    return lRes;
} // fnGetIndexedEP

string fnGetIndexedRP(void /ECampos pCampo/)
{
    /*string lHTML = "";
    PDATA lData = NULL;
    int lRow = 0;
    string lColor = "";
    while (lData = gLista.get(pCampo)) {
        lColor = "";
        if (lRow % 2 == 0)
            lColor = "background-color:#E0E0E0;";
        lHTML += "<div class='row' style='" + lColor + "'>\n";
        lHTML += "<div class='col-md-3'>\n" + lData->sNombre + "</div>";
        lHTML += "<div class='col-md-3'>\n" + lData->sApellido + "</div>";
        lHTML += "<div class='col-md-2'>\n" + lData->sFNac + "</div>";
        lHTML += "<div class='col-md-2'>\n" + to_string(lData->sSalario) + "</div>";
        lHTML += "<div class='col-md-2'>\n<a href='/indexada?borrar=" + to_string(lData->sID) + "'>[ Borrar (" + to_string(lData->sID) + ")]</a></div>";
        lHTML += "</div>";
        lRow++;
    }*/

    string lRes = fnGetTemplate("indexed.tpl.html");
    //strReplace(lRes, "{{pData}}", lHTML);

    return lRes;
} // fnGetIndexedRP

string fnIndexedLists(string pCaller)
{
    string lRes = "NoFile";

    /*map<string, string> lParams = fnGetParams(pCaller);
    if (lParams["nombre"] != "") {
        gLista.push_back(lParams["nombre"], lParams["apellido"], lParams["fnac"], stod(lParams["salario"]));
        gLista.resetCurr();
        gLista.write(gPath);
        lRes = fnGetIndexedRP(ECampos::nombre);
    }
    else if (lParams["orden"] != "") {
        lRes = fnGetIndexedRP( (ECampos)(stoi(lParams["orden"])) );
    }
    else if (lParams["borrar"] != "") {
        gLista.del(stol(lParams["borrar"]));
        gLista.resetCurr();
        gLista.write(gPath);
        lRes = fnGetIndexedRP(ECampos::nombre);
    }
    else
        lRes = fnGetIndexedRP(ECampos::nombre);
        //lRes = fnGetIndexedEP();
        */
    return lRes;

} // fnIndexedLists

string fnGetFuncS(string pCaller)
{
    string lRes = "NoFile";

    /*if (pCaller != "http://localhost:8080/favicon.ico") {

        strVec lPath = fnGetPath(pCaller);
        if (lPath.size() > 1) {
            cout << "Path: " << lPath[1] << endl;
            if (lPath[1] == "indexada")
                lRes = fnIndexedLists(pCaller);
            else
                lRes = fnGetTemplate("init.tpl.html");
        } else
            lRes = fnGetTemplate("init.tpl.html");
    }*/

    return lRes;
} // fnGetFuncS


int main()
{
    MyHTTPSrv lSrv = MyHTTPSrv(NULL, NULL);
    lSrv.SetGetFunc(&fnGetFuncS);
    lSrv.Run();
} // main