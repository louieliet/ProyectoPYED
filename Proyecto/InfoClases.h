#pragma once
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>
#include "CSV.h"

using namespace std;

typedef struct VNODE* PVNODE;

struct VNODE {
    string ID;
    vector<int> sCalif;
    PVNODE sPrev;
    PVNODE sNext;
};

class DLVer
{
protected:
    PVNODE aHead;
    PVNODE aTail;
    PVNODE aCurr;

public:
    DLVer(void);
    ~DLVer(void);

    void clean(void);

    void push(string ID);
    void pushLoad(string IDAlum, int calif1, int calif2, int calif3);

    PVNODE get(string pMain);
    void resetCurr(void);

    void del(string ID);
    void inscrrepr(string pID);

    bool isEmpty(void);
    PVNODE get(void);
    void repr(bool pRev = false);
    bool has(string pID);

private:
    void push_front(string ID);
    void push_frontLoad(string IDAlum, int calif1, int calif2, int calif3);
    void push_back(string ID);
    void push_backLoad(string IDAlum, int calif1, int calif2, int calif3);

    void pop_front(void);
    void pop_back(void);

    PVNODE find(string ID);
    PVNODE search(string ID);
    PVNODE getNewNode(string ID);
    PVNODE getNewNodeLoad(string IDAlum, int calif1, int calif2, int calif3);
};

//--

typedef struct HNODE* PHNODE;

struct HNODE {
    string sID;
    string sClas;
    DLVer* sVer;
    PHNODE sPrev;
    PHNODE sNext;
};

class DLHor
{
protected:
    PHNODE aHead;
    PHNODE aTail;
    PHNODE aCurr;

public:
    DLHor(void);
    ~DLHor(void);

    void clean(void);

    void push(string pClass, string ClassID, string IDAlum);


    void del(string pID);
    void del(string pID, string ID);

    bool isEmpty(void);
    void repr(bool pRev = false);
    void read(string Path);
    void write(string Path);
    void inscrrepr(string pID);
    //void read(string pPath);
   // void write(string pPath, bool pRev = false);

       PHNODE find(string pID);


private:
    void push_front(string pClass, string ClassID, string IDAlum);
    void push_back(string pClass, string ClassID, string IDAlum);
    void push_backLoad(string pClass, string ClassID, string IDAlum, int calif1, int calif2, int calif3);

    void pop_front(void);
    void pop_back(void);

    PHNODE search(string pID);
    PHNODE getNewNode(string pClass, string ClassID);
};
