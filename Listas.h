#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

typedef struct DNODE* PDNODE;
typedef struct Materia* PDATA;
struct Materia {
    string sNombre;
    string sSalon;
    string sProfesor;
    string sDisponibilidad;
};

struct DNODE {
    PDATA sData;
    int sFrec;
    PDNODE sPrev;
    PDNODE sNext;
};

enum class ECampos { nombre, salon, profesor, disponibilidad };

class DLIndex
{
protected:
    PDNODE aHead;
    PDNODE aTail;
    PDNODE aCurr;
    bool aFrec;
    ECampos aType;

public:
    DLIndex(ECampos pType, bool pFrec = false);
    ~DLIndex(void);

    void clean(void);

    void push_front(PDATA pData);
    void push_back(PDATA pData);
    void push(PDATA pData);

    //PDNODE top_front(void);
    //PDNODE top_back(void);
    PDATA get(bool pRev = false);

    void pop_front(void);
    void pop_back(void);
    void del(PDATA pData);

    bool isEmpty(void);
    void repr(bool pRev = false);
    //void read(string pPath, char pMethod = 'b');
    //void write(string pPath, bool pRev = false);

private:
    PDNODE find(PDATA);
    PDNODE search(PDATA);
    PDNODE getNewNode(PDATA pData);
    int comp(PDATA pA, PDATA pB);
}; //DINDEX

class DList
{
protected:
    PDNODE aHead;
    PDNODE aTail;
    PDNODE aCurr;
    bool aFrec;
    DLIndex* aINom;
    DLIndex* aISalon;
    DLIndex* aIProf;
    DLIndex* aIDis;

public:
    DList(bool pFrec = false);
    ~DList(void);

    void clean(void);

    //void push_front(string pNombre);
    void push_back(string pNombre, string pSalon, string pProfesor, string pDisponibilidad);
    //void push(string pNombre);

    //PDNODE top_front(void);
    //PDNODE top_back(void);
    PDATA get(ECampos pCampo, bool pRev = false);

    void pop_front(void);
    void pop_back(void);
    void del(string); //borra un elemento cualquiera de la lista
    bool isEmpty(void);
    void repr(ECampos pCampo, bool pRev = false);
    void modify(ECampos, string);
    //void read(string pPath, char pMethod = 'b');
    //void write(string pPath, bool pRev = false);

private:
    PDNODE find(string pNombre);
    //PDNODE search(string pNombre);
    PDNODE getNewNode(string pNombre, string pSalon, string pProfesor, string pDisponibilidad);
}; //DINDEX

