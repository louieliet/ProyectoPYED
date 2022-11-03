#pragma once
#include <iostream>
#include <string>
using namespace std;

typedef struct DNODO* PDNODO;
typedef struct DNODO2* PDNODO2;

struct DNODO {

	string sIDP;
	string sNombre;
	string sCorreo;
	string sPassword;
	PDNODO sNext;
	PDNODO sPrev;
	
};

struct DNODO2 {
	string sIDP;
	string sNombre;
	string sCorreo;
	string sPassword;
	PDNODO2 sNext;
	PDNODO2 sPrev;
};

class DListProf {

protected: 
	PDNODO aHead;
	PDNODO aTail;
	PDNODO aCurr;

public:
	DListProf(void);
	~DListProf(void);

	void clean(void);
	void push_front(string pIDP, string pNombre, string pCorreo, string pPassword);
	void push_back(string pIDP, string pNombre, string pCorreo, string pPassword);
	void push(string pIDP, string pNombre, string pCorreo, string pPassword);
	void InsertarProfe(void);

	PDNODO top_front(void);
	PDNODO top_back(void);
	PDNODO get(void);

	void pop_front(void);
	void pop_back(void);
	void del(string pIDP);
	void read(string pPath);
	void write(string pPath);

	string findContra(string usuario);
	bool ExisteProfe(string pIDP);
	bool isEmpty(void);
	void repr(void);

private:
	PDNODO getNewNode(string pIDP, string pNombre, string pCorreo, string pPassword);
	PDNODO search(string pIDP);
	PDNODO find(string pIDP);


};

class DListAlumno {
protected:

	PDNODO2 aHead;
	PDNODO2 aTail;
	PDNODO2 aCurr;

public:
	DListAlumno(void);
	~DListAlumno(void);

	void clean(void);
	void push_front(string pIDP, string pNombre, string pCorreo, string pPassword);
	void push_back(string pIDP, string pNombre, string pCorreo, string pPassword);
	void push(string pIDP, string pNombre, string pCorreo, string pPassword);
	void InsertarAlumno(void);

	PDNODO2 top_front(void);
	PDNODO2 top_back(void);
	PDNODO2 get(void);

	void pop_front(void);
	void pop_back(void);
	void del(string pIDP);
	void read(string pPath);
	void write(string pPath);

	bool ExisteAlumno(string pIDP);
	bool isEmpty(void);
	void repr(void);

private:
	PDNODO2 getNewNode(string pIDP, string pNombre, string pCorreo, string pPassword);
	PDNODO2 search(string pIDP);
	PDNODO2 find(string pIDP);


};

class DListAdmin {

protected:
	PDNODO aHead;
	PDNODO aTail;
	PDNODO aCurr;

public:
	DListAdmin(void);
	~DListAdmin(void);

	void clean(void);
	void push_front(string pIDP, string pNombre, string pCorreo, string pPassword);
	void push_back(string pIDP, string pNombre, string pCorreo, string pPassword);
	void push(string pIDP, string pNombre, string pCorreo, string pPassword);
	void InsertarAdmin(void);

	PDNODO get(void);

	void pop_front(void);
	void pop_back(void);
	void del(string pIDP);
	void read(string pPath);
	void write(string pPath);

	string findContra(string usuario);
	bool ExisteAdmin(string pIDP);
	bool isEmpty(void);
	void repr(void);

private:
	PDNODO getNewNode(string pIDP, string pNombre, string pCorreo, string pPassword);
	PDNODO search(string pIDP);
	PDNODO find(string pIDP);


};

