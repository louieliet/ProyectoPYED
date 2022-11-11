#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "Profesors.h"
#include "InfoClases.h"

using namespace std;

typedef struct DNODE* PDNODE;
typedef struct Materia* PDATA;

struct Materia {
    string sNombre;
    string sSalon;
    string sProfesor;
    string sDisponibilidad;
    string sID;
};

struct DNODE {
    PDATA sData;
    int sFrec;
    PDNODE sPrev;
    PDNODE sNext;
};

enum class ECampos { nombre, salon, profesor, disponibilidad, id};


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
    string htmlrepr(bool pRev = false);
    string aHeadver(void);
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
    DLIndex* aIID;

public:
    DList(bool pFrec = false);
    ~DList(void);

    void clean(void);

    //void push_front(string pNombre);
    void push_back(string pNombre, string pSalon, string pProfesor, string pDisponibilidad, string pID);
    //void push(string pNombre);

    //PDNODE top_front(void);
    //PDNODE top_back(void);
    PDATA get(ECampos pCampo, bool pRev = false);

    void pop_front(void);
    void pop_back(void);
    void del(string); //borra un elemento cualquiera de la lista
    bool isEmpty(void);
    void repr(ECampos pCampo, bool pRev = false);
    string htmlrepr(ECampos pCampo, bool pRev = false);
    void modify(ECampos, string, string);

    bool has(string);

    void read(string pPath);
    void write(string pPath);
    string getName(string ID);
    void reprprof(string pID);
    string reprprofhtml(string pID);
    //void read(string pPath, char pMethod = 'b');
    //void write(string pPath, bool pRev = false);

private:
    PDNODE find(string pID);
    //PDNODE search(string pNombre);
    PDNODE getNewNode(string pNombre, string pSalon, string pProfesor, string pDisponibilidad, string pID);
}; //DINDEX


class aClase {

protected:
    string ynombre;
    string yprofesor;
    string ysalon;
    string yDisponibilidad;
    string yID;
    DList aux;

public:
    DListProf prof;
    DListAlumno alumn;
    DListAdmin admi;
    DLHor classes;
    aClase();
    void addClase(void);
    void addClase(string profeID);
    void ModificarDatoDeClase(void);
    void EliminarClase();
    void mostrarClases();
    void InsertData();
    void GuardarData();
    void MeterMateria(string);
    void mostrarClasesProf(string pID);
    string mostrarClasesProfhtml(string pID);
    void EliminarInsc(string AlumnoID);
    void ModiCalif(void);
    string MeterMateriashtml();
};