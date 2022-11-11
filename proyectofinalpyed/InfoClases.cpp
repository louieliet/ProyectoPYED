#include "InfoClases.h"
#include <sstream>

typedef vector <string> strVec;


void strSplit(string& pStr, char pDelim, strVec& pOut)
{
	stringstream lStream(pStr);
	string lChunk;
	while (getline(lStream, lChunk, pDelim)) {
		pOut.push_back(lChunk);
		// cout << lChunk.c_str() << endl;
	}
} // strSplit



DLVer::DLVer(void) {
	aHead = NULL;
	aTail = NULL;
	aCurr = NULL;
}

DLVer::~DLVer(void) {
	clean();
}

void DLVer::clean(void) {
	while (aHead) {
		PVNODE lTemp = aHead->sNext;
		delete aHead;
		aHead = lTemp;
	}

	aHead = NULL;
	aTail = NULL;
	aCurr = NULL;
}

void DLVer::push(string ID) {
	if (aHead == NULL) {
		aHead = getNewNode(ID);
		aTail = aHead;
	}
	else {
		if (ID < aHead->ID) {
			push_front(ID);
		}
		else if (ID > aTail->ID) {
			push_back(ID);
		}
		else{
			PVNODE lItem = search(ID);
			if (lItem->ID != ID) {
				PVNODE lTemp = getNewNode(ID);
				lTemp->sNext = lItem;
				lTemp->sPrev = lItem->sPrev;
				lItem->sPrev->sNext = lTemp;
				lItem->sPrev = lTemp;
			}
			else {
				cout << "Ya está registrado" << endl;
			}
		}
	}
}


void DLVer::pushLoad(string IDAlum, double calif1, double calif2, double calif3) {
	if (aHead == NULL) {
		aHead = getNewNodeLoad(IDAlum, calif1, calif2, calif3);
		aTail = aHead;
	}
	else {
		if (IDAlum <= aHead->ID) {
			push_frontLoad(IDAlum, calif1, calif2, calif3);
		}
		else if (IDAlum >= aTail->ID) {
			push_backLoad(IDAlum, calif1, calif2, calif3);
		}
		else {
			PVNODE lItem = search(IDAlum);
			if (lItem) {
				PVNODE lTemp = getNewNodeLoad(IDAlum, calif1, calif2, calif3);
				lTemp->sNext = lItem;
				lTemp->sPrev = lItem->sPrev;
				lItem->sPrev->sNext = lTemp;
				lItem->sPrev = lTemp;
			}
		}
	}
}

PVNODE DLVer::get(string ID) {
	PVNODE lTemp = NULL;
	if (aHead) {
		lTemp = find(ID);
	}
	return lTemp;
}

void DLVer::resetCurr(void) {
	aCurr = NULL;
}

void DLVer::del(string ID) {
	if (aHead) {
		if (aHead->ID == ID)
			pop_front();
		else if (aTail->ID == ID)
			pop_back();
		else {
			PVNODE lTemp = find(ID);
			if (lTemp) {
				if (aCurr == lTemp)
					aCurr = lTemp->sNext;
				lTemp->sPrev->sNext = lTemp->sNext;
				lTemp->sNext->sPrev = lTemp->sPrev;
			}
			else {
				cout << "Alumno no encontrado" << endl;
			}
		}
	}
}

bool DLVer::isEmpty(void) {
	return(aHead == NULL);
}

PVNODE DLVer::alumni(void) {
	return aHead;
}

void DLVer::repr(bool pRev) {
	if (aHead) {
		PVNODE lTemp = (pRev == false ? aHead : aTail);
		while (lTemp) {
			cout << "ID: " + lTemp->ID + " | Calficaciones: "; 
			for (int i = 0; i < 3; i++) {
				cout << lTemp->sCalif[i];
				cout << ", ";
			}
			lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
		}
	}
}

void DLVer::inscrrepr(string pID) {
	if (aHead) {
		PVNODE lTemp = (aHead);
		while (lTemp) {
			if(lTemp->ID == pID){
				//cout << lTemp->sCalif.size();
				cout << "Calificaciones: "; 
				for (int i = 0; i < 3; i++) {
					cout << lTemp->sCalif[i];
					if(i<2)
						cout << ", ";
				}
			}
			lTemp = (lTemp->sNext);
		}
	}
}

string DLVer::htmlrepr(string pID) {
	string build = "";
	if (aHead) {
		PVNODE lTemp = (aHead);
		while (lTemp) {
			if (lTemp->ID == pID) {
				for (int i = 0; i < 3; i++) {
					build += "<td>" + to_string(lTemp->sCalif[i]) + "</td>";
				}
			}
			lTemp = (lTemp->sNext);
		}
	}
	return build;
}

void DLVer::push_front(string ID) {
	if (aHead == NULL) {
		aHead = getNewNode(ID);
		aTail = aHead;
	}
	else {
		PVNODE lTemp = getNewNode(ID);
		aHead->sPrev = lTemp;
		lTemp->sNext = aHead;
		aHead = lTemp;
	}
}

void DLVer::push_frontLoad(string ID, double calif1, double calif2, double calif3) {
	if (aHead == NULL) {
		aHead = getNewNodeLoad(ID, calif1, calif2, calif3);
		aTail = aHead;
	}
	else {
		PVNODE lTemp = getNewNodeLoad(ID, calif1, calif2, calif3);
		aHead->sPrev = lTemp;
		lTemp->sNext = aHead;
		aHead = lTemp;
	}
}

void DLVer::push_back(string ID) {
	if (aHead == NULL) {
		aHead = getNewNode(ID);
		aTail = aHead;
	}
	else {
		PVNODE lTemp = getNewNode(ID);
		aTail->sNext = lTemp;
		lTemp->sPrev = aTail;
		aTail = lTemp;
	}
}

void DLVer::push_backLoad(string ID, double calif1, double calif2, double calif3) {
	if (aHead == NULL) {
		aHead = getNewNodeLoad(ID, calif1, calif2, calif3);
		aTail = aHead;
	}
	else {
		PVNODE lTemp = getNewNodeLoad(ID, calif1, calif2, calif3);
		aTail->sNext = lTemp;
		lTemp->sPrev = aTail;
		aTail = lTemp;
	}
}

void DLVer::pop_front(void) {
	if (aHead) {
		PVNODE lTemp = aHead->sNext;
		bool lEqual = (aHead == aCurr);
		delete aHead;
		aHead = lTemp;
		if (aHead) {
			aHead->sPrev = NULL;
			aCurr = (lEqual ? aHead : aCurr);
		}
		else {
			aTail = NULL;
			aCurr = NULL;
		}
	}	
}

void DLVer::pop_back(void) {
	if (aHead) {
		PVNODE lTemp = aTail->sPrev;
		bool lEqual = (aTail == aCurr);
		delete aTail;
		aTail = lTemp;
		if (aTail) {
			aTail->sNext = NULL;
			aCurr = (lEqual ? aTail : aCurr);
		}
		else {
			aHead = NULL;
			aCurr = NULL;
		}
	}
}

PVNODE DLVer::get(void)
{
	PVNODE lTemp = NULL;

	if (aHead) {
		if (aCurr == NULL)
			aCurr = aHead;
		else
			aCurr = aCurr->sNext;
		lTemp = aCurr;
	}

	return lTemp;
} // get

PVNODE DLVer::find(string ID) {
	PVNODE lTemp = aHead;

	while (lTemp) {
		if (ID == lTemp->ID)
			return lTemp;
		lTemp = lTemp->sNext;
	}

	return NULL;
}

PVNODE DLVer::search(string ID) {
	PVNODE lTemp = aHead;

	while (lTemp) {
		if (ID <= lTemp->ID)
			return lTemp;
		lTemp = lTemp->sNext;
	}

	return NULL;
}

PVNODE DLVer::getNewNode(string ID) {
	PVNODE lTemp = new VNODE;
	if (lTemp) {
		lTemp->ID = ID;
		for (int i = 0; i < 3; i++) {
			lTemp->sCalif.push_back(0);
		}
		lTemp->sNext = NULL;
		lTemp->sPrev = NULL;
	}

	return lTemp;

}

PVNODE DLVer::getNewNodeLoad(string IDAlum, double calif1, double calif2, double calif3) {
	PVNODE lTemp = new VNODE;
	if (lTemp) {
		lTemp->ID = IDAlum;
		lTemp->sCalif.push_back(calif1);
		lTemp->sCalif.push_back(calif2);
		lTemp->sCalif.push_back(calif3);
		lTemp->sNext = NULL;
		lTemp->sPrev = NULL;
	}

	return lTemp;
}



// -------------------LISTA HORIZONTAL -----------------


DLHor::DLHor(void) {
	aHead = NULL;
	aTail = NULL;
	aCurr = NULL;
}

DLHor::~DLHor(void) {
	clean();
}

void DLHor::clean(void) {
	while (aHead) {
		PHNODE lTemp = aHead->sNext;
		if (aHead->sVer)
			delete aHead->sVer;
		delete aHead;
		aHead = lTemp;
	}

	aHead = NULL;
	aTail = NULL;
	aCurr = NULL;
}

void DLHor::push(string pClass, string ClassID, string IDAlum) {
	if (aHead == NULL) {
		aHead = getNewNode(pClass, ClassID);
		aTail = aHead;
		aHead->sVer = new DLVer();
		if(aHead->sVer)
			aHead->sVer->push(IDAlum);
	}
	else {
		if (ClassID <= aHead->sID)
			push_front(pClass, ClassID, IDAlum);
		else if (ClassID >= aTail->sID)
			push_back(pClass, ClassID, IDAlum);
		else {
			PHNODE lItem = search(ClassID);
			if (lItem) {
				if (lItem->sID != ClassID) {
					PHNODE lTemp = getNewNode(pClass, ClassID);
					lTemp->sNext = lItem;
					lTemp->sPrev = lItem->sPrev;
					lItem->sPrev->sNext = lTemp;
					lItem->sPrev = lTemp;
					lTemp->sVer = new DLVer();
					if (lTemp->sVer) {
						lTemp->sVer->push(IDAlum);
					}

				}
				else {
					if (lItem->sVer == NULL)
						lItem->sVer = new DLVer();
					if(lItem->sVer)
						lItem->sVer->push(IDAlum);
				}
			}
		}
	}
}



void DLHor::del(string pID) {
	if (aHead) {
		if (aHead->sID == pID)
			pop_front();
		else if (aTail->sID == pID)
			pop_back();
		else {
			PHNODE lTemp = find(pID);
			if (lTemp) {
				if (aCurr == lTemp)
					aCurr = lTemp->sNext;
				lTemp->sPrev->sNext = lTemp->sNext;
				lTemp->sNext->sPrev = lTemp->sPrev;
				if (lTemp->sVer)
					delete lTemp->sVer;
				delete lTemp;
			}
		}
	}
}

void DLHor::del(string pID, string IDAlum) {
	if (aHead) {
		if (aHead->sID == pID) {
			if (aHead->sVer)
				aHead->sVer->del(IDAlum);
		}
		else if (aTail->sID == pID) {
			if (aTail->sVer)
				aTail->sVer->del(IDAlum);
		}
		else {
			PHNODE lTemp = find(pID);
			if (lTemp) {
				if (lTemp->sVer)
					lTemp->sVer->del(IDAlum);
			}
		}
	}
}

bool DLHor::isEmpty(void) {
	return(aHead == NULL);
}

void DLHor::repr(bool pRev) {
	if (aHead) {
		PHNODE lTemp = (pRev == false ? aHead : aTail);
		while (lTemp) {
			cout << " -> ";
			cout << "ID: " + lTemp->sID;
			cout << "| Clase: " + lTemp->sClas << "( ";
			if (lTemp->sVer)
				lTemp->sVer->repr(pRev);
			cout << ")" << endl;
			lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
		}
		cout << endl;
	}
}

void DLHor::inscrrepr(string pID) {
	if (aHead) {
		PHNODE lTemp = (aHead);
		while (lTemp) {
			if(lTemp->sVer->has(pID)){
				cout << "-> ";
				cout << "ID de la clase: " + lTemp->sID;
				cout << " | Clase: " + lTemp->sClas << " (";
				lTemp->sVer->inscrrepr(pID);
				cout << ")" << endl;
			}
			lTemp = (lTemp->sNext);
		}
		cout << endl;
	}
}

string DLHor::htmlrepr(string pID) {
	string build = "";
	if (aHead) {
		
		PHNODE lTemp = (aHead);
		while (lTemp) {
			if (lTemp->sVer->has(pID)) {
				build += "<tr>";
				build += "<td> " + lTemp->sID + "</td>";
				build += " <td>  " + lTemp->sClas + "</td>";
				build += lTemp->sVer->htmlrepr(pID);
				build += "</tr>";
			}
			lTemp = (lTemp->sNext);
		}
		cout << endl;
	}
	return build;
}

bool DLVer::has(string pID){
	if(aHead){
		PVNODE lTemp = aHead;
		while(lTemp){
			//cout << lTemp->ID << "?=" << pID << "==" << (lTemp->ID == pID) << endl;
			if(lTemp->ID == pID){
				return true;
			}
			lTemp = lTemp->sNext;
		}
	}
	return false;
}

void DLHor::push_front(string pClass, string ClassID, string IDAlum) {
	if (aHead == NULL) {
		aHead = getNewNode(pClass, ClassID);
		aTail = aHead;
		aHead->sVer = new DLVer();
		if (aHead->sVer)
			aHead->sVer->push(IDAlum);
	}
	else {
		if (aHead->sID != ClassID) {
			PHNODE lTemp = getNewNode(pClass, ClassID);
			aHead->sPrev = lTemp;
			lTemp->sNext = aHead;
			aHead = lTemp;
			lTemp->sVer = new DLVer();
			if (lTemp->sVer)
				lTemp->sVer->push(IDAlum);
		}
		else {
			if (aHead->sVer == NULL)
				aHead->sVer = new DLVer();
			if (aHead->sVer)
				aHead->sVer->push(IDAlum);
		}
	}
}

void DLHor::write(string pPath)
{
	if (aHead) {
		ofstream lFile(pPath);
		if (lFile.is_open()) {
			PHNODE lTemp = aHead;
			while (lTemp) {
				lFile << lTemp->sID << endl;
				lFile << lTemp->sClas << endl;
				if (lTemp->sVer) {
					lTemp->sVer->resetCurr();
					PVNODE lItem = NULL;
					while (lItem = lTemp->sVer->get()) {
						lFile << "\t" << lItem->ID << "|" << lItem->sCalif[0] << "|" << lItem->sCalif[1] << "|" << lItem->sCalif[2] << endl;
					}
				}
				lTemp = lTemp->sNext;
			}
			lFile.close();
		}
	}
} // write

void DLHor::read(string pPath)
{
	string lLine = "";
	ifstream lFile(pPath);
	string lCat = "";
	string lClas = "";
	strVec lOut;
	int num = 0;

	while (getline(lFile, lLine)) {
		if (lLine[0] != '\t') {
			if (num == 0) {
				lCat = lLine;
				num++;
			}
			else if(num == 1) {
				lClas = lLine;
				num--;
			}
		}
		else{
			if (lCat != "") {
				lLine.replace(lLine.find("\t"), 1, "");
				strSplit(lLine, '|', lOut);
				push_backLoad(lClas, lCat, lOut[0], stod(lOut[1]), stod(lOut[2]), stod(lOut[3]));
				lOut.clear();
			}
		}
	}

	lFile.close();
} // read

void DLHor::push_back(string pClass, string ClassID, string IDAlum) {
	if (aHead == NULL) {
		aHead = getNewNode(pClass, ClassID);
		aTail = aHead;
		aTail->sVer = new DLVer();
		if (aTail->sVer)
			aTail->sVer->push(IDAlum);
	}
	else {
		if (aTail->sID != ClassID) {
			cout << "Hola" << endl;
			PHNODE lTemp = getNewNode(pClass, ClassID);
			aTail->sNext = lTemp;
			lTemp->sPrev = aTail;
			aTail = lTemp;
			lTemp->sVer = new DLVer();
			if (lTemp->sVer)
				lTemp->sVer->push(IDAlum);
		}
		else {
			cout << " hola 2" << endl;
			if (aTail->sVer == NULL)
				aTail->sVer = new DLVer();
			if (aTail->sVer)
				aTail->sVer->push(IDAlum);
		}
	}
}

void DLHor::push_backLoad(string pClass, string ClassID, string IDAlum, double calif1, double calif2, double calif3) {
	if (aHead == NULL) {
		aHead = getNewNode(pClass, ClassID);
		aTail = aHead;
		aTail->sVer = new DLVer();
		if (aTail->sVer)
			aTail->sVer->pushLoad(IDAlum, calif1, calif2, calif3);
	}
	else {
		if (aTail->sID != ClassID) {
			PHNODE lTemp = getNewNode(pClass, ClassID);
			aTail->sNext = lTemp;
			lTemp->sPrev = aTail;
			aTail = lTemp;
			lTemp->sVer = new DLVer();
			if (lTemp->sVer)
				lTemp->sVer->pushLoad(IDAlum, calif1, calif2, calif3);
		}
		else {
			if (aTail->sVer == NULL)
				aTail->sVer = new DLVer();
			if (aTail->sVer)
				aTail->sVer->pushLoad(IDAlum, calif1, calif2, calif3);
		}
	}
}





void DLHor::pop_front(void)
{
	if (aHead) {
		PHNODE lTemp = aHead->sNext;
		bool lEqual = (aHead == aCurr);
		if (aHead->sVer)
			delete aHead->sVer;
		delete aHead;
		aHead = lTemp;
		if (aHead) {
			aHead->sPrev = NULL;
			aCurr = (lEqual ? aHead : aCurr);
		}
		else {
			aTail = NULL;
			aCurr = NULL;
		}
	}
} // pop_front

void DLHor::pop_back(void)
{
	if (aHead) {
		PHNODE lTemp = aTail->sPrev;
		bool lEqual = (aTail == aCurr);
		if (aTail->sVer)
			delete aTail->sVer;
		delete aTail;
		aTail = lTemp;
		if (aTail) {
			aTail->sNext = NULL;
			aCurr = (lEqual ? aTail : aCurr);
		}
		else {
			aHead = NULL;
			aCurr = NULL;
		}
	}
} // pop_back

PHNODE DLHor::find(string ClassID)
{
	PHNODE lTemp = aHead;

	while (lTemp) {
		if (ClassID == lTemp->sID)
			return lTemp;
		lTemp = lTemp->sNext;
	}

	return NULL;
} // find

PHNODE DLHor::search(string ClassID)
{
	PHNODE lTemp = aHead;

	while (lTemp) {
		if (ClassID <= lTemp->sID)
			return lTemp;
		lTemp = lTemp->sNext;
	}

	return NULL;
} // search

PHNODE DLHor::getNewNode(string pClass, string ClassID)
{
	PHNODE lTemp = new HNODE;

	if (lTemp) {
		lTemp->sClas = pClass;
		lTemp->sID = ClassID;
		lTemp->sVer = NULL;
		lTemp->sNext = NULL;
		lTemp->sPrev = NULL;
	}

	return lTemp;
} // getNewNode
