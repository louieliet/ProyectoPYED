#include "Profesors.h"
#include "CSV.h"


DListProf::DListProf(void) {
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
}

DListProf:: ~DListProf(void) {
    clean();
}

void DListProf::clean(void) {
    while (aHead) {
        PDNODO lTemp = aHead->sNext;
        delete aHead;

        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
}

void DListProf::push_front(string pIDP, string pNombre, string pCorreo, string pPassword) {

    if (aHead == NULL) {
        aHead = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail = aHead;
    }
    else {
        PDNODO lTemp = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aHead->sPrev = lTemp;
        lTemp->sNext = aHead;
        aHead = lTemp;
    }

}

void DListProf::push_back(string pIDP, string pNombre, string pCorreo, string pPassword) {
    if (aHead == NULL) {
        aHead = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail = aHead;
    }
    else {
        PDNODO lTemp = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
    }
}

void DListProf::push(string pIDP, string pNombre, string pCorreo, string pPassword) {
    if (aHead == NULL) {
        aHead = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail = aHead;
    }
    else {
        if (pIDP <= aHead->sIDP) {
            push_front(pIDP, pNombre, pCorreo, pPassword);
        }
        else if (pIDP >= aTail->sIDP) {
            push_back(pIDP, pNombre, pCorreo, pPassword);
        }
        else {
            PDNODO lItem = search(pIDP);
            if (lItem) {
                PDNODO lTemp = getNewNode(pIDP, pNombre, pCorreo, pPassword);
                lTemp->sNext = lItem;
                lTemp->sPrev = lItem->sPrev;
                lItem->sPrev->sNext = lTemp;
                lItem->sPrev = lTemp;
            }
        }
    }
}

void DListProf::InsertarProfe(void) {
    string auxID;
    string auxNom;
    string auxCorreo;
    string auxPass;

    cout << "Ingrese el ID" << endl;
    getline(cin, auxID);
    PDNODO lTemp = find(auxID);
    while (lTemp != NULL) {
        cout << "ID ya registrado, ingrese otro: ";
        getline(cin, auxID);
        lTemp = find(auxID);
    }
    cout << endl;
    cout << "Ingrese el nombre: ";
    getline(cin, auxNom);
    cout << endl;
    cout << "Ingrese password: ";
    getline(cin, auxPass);
    auxCorreo = auxID + "@up.edu.mx";

    push(auxID, auxNom, auxCorreo, auxPass);

    cout << endl;
    cout << "--------------" << endl;
    cout << "Registro guardado con exito" << endl;

    write("Profesores.csv");

}


PDNODO DListProf::top_front(void) {

    if (aHead) {
        return aHead;
    }
    return NULL;
}

PDNODO DListProf::top_back(void) {
    if (aHead) {
        return aTail;
    }

    return NULL;
}

PDNODO DListProf::get(void) {

    PDNODO lTemp = NULL;

    if (aHead) {
        if (aCurr == NULL) {
            aCurr = aHead;
        }
        else {
            aCurr = aCurr->sNext;
        }
        lTemp = aCurr;

    }

    return lTemp;

}


void DListProf::pop_front(void) {
    if (aHead) {

        PDNODO lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        delete aHead;
        aHead = lTemp;

        if (aHead == NULL) {
            aTail = NULL;
            aCurr = NULL;
        }
        else {
            aHead->sPrev = NULL;
            aCurr = (lEqual ? aHead : aCurr);
        }
    }
}

void DListProf::pop_back(void) {
    if (aHead) {
        PDNODO lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;

        if (aTail == NULL) {
            aHead = NULL;
            aCurr = NULL;
        }
        else {
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
    }
}

void DListProf::del(string pIDP) {

    if (aHead) {
        if (aHead->sIDP == pIDP) {
            pop_front();
        }
        else if (aHead->sIDP == pIDP) {
            pop_back();
        }
        else {
            PDNODO lTemp = find(pIDP);
            if (lTemp) {
                if (aCurr == lTemp)
                    aCurr = lTemp->sNext;
                lTemp->sPrev->sNext = lTemp->sNext;
                lTemp->sNext->sPrev = lTemp->sPrev;
                delete lTemp;
            }
        }
    }

}

void DListProf::read(string pPath) {
    CSVReader lReader = CSVReader(pPath);
    TCSVTbl lTbl = lReader.read();

    if (lTbl.size() > 0) {
        for (size_t lCol = 0; lCol < lTbl.size(); lCol++) {
            push(lTbl[lCol][0], lTbl[lCol][1], lTbl[lCol][2], lTbl[lCol][3]);
        }
    }
}

void DListProf::write(string pPath)
{
    if (aHead) {
        CSVWriter lWriter = CSVWriter(pPath);
        PDNODO lTemp = aHead;
        while (lTemp) {
            lWriter.write(lTemp->sIDP);
            lWriter.write(lTemp->sNombre);
            lWriter.write(lTemp->sCorreo);
            lWriter.write(lTemp->sPassword);
            lWriter.writeeol();
            lTemp = lTemp->sNext;
        }
    }
} // write

string DListProf::findContra(string usuario) {
    PDNODO lTemp = find(usuario);

    return lTemp->sPassword;
}

bool DListProf::ExisteProfe(string pIDP) {
    PDNODO lTemp = find(pIDP);

    if (lTemp) {
        return true;
    }
    else {
        return false;
    }
}

bool DListProf::isEmpty(void) {
    return(aHead == NULL);
}

void DListProf::repr(void) {
    if (aHead) {
        PDNODO lTemp = aHead;
        while (lTemp) {
            cout << "( " + lTemp->sIDP + ", " + lTemp->sNombre + ", " + lTemp->sCorreo + ")  "<<endl;
            lTemp = lTemp->sNext;
        }
    }
}

PDNODO DListProf::find(string pIDP) {
    PDNODO lTemp = aHead;

    while (lTemp) {
        if (lTemp->sIDP == pIDP) {

            return lTemp;
        }

        lTemp = lTemp->sNext;
    }

    return NULL;
}

PDNODO DListProf::search(string pIDP) {
    PDNODO lTemp = aHead;

    while (lTemp) {
        if (pIDP <= lTemp->sIDP) {
            return lTemp;
        }
        lTemp = lTemp->sNext;
    }

    return NULL;
}

PDNODO DListProf::getNewNode(string pIDP, string pNombre, string pCorreo, string pPassword){

    PDNODO lTemp = new DNODO;

    if (lTemp) {
        lTemp->sIDP = pIDP;
        lTemp->sNombre = pNombre;
        lTemp->sCorreo = pCorreo;
        lTemp->sPassword = pPassword;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;

    }

    return lTemp;

}


// ---------------------------------- Alumnos ---------------------------------


DListAlumno::DListAlumno(void) {
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
}

DListAlumno:: ~DListAlumno(void) {
    clean();
}

void DListAlumno::clean(void) {
    while (aHead) {
        PDNODO2 lTemp = aHead->sNext;
        delete aHead;

        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
}

void DListAlumno::push_front(string pIDP, string pNombre, string pCorreo, string pPassword) {

    if (aHead == NULL) {
        aHead = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail = aHead;
    }
    else {
        PDNODO2 lTemp = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aHead->sPrev = lTemp;
        lTemp->sNext = aHead;
        aHead = lTemp;
    }

}

void DListAlumno::push_back(string pIDP, string pNombre, string pCorreo, string pPassword) {
    if (aHead == NULL) {
        aHead = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail = aHead;
    }
    else {
        PDNODO2 lTemp = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
    }
}

void DListAlumno::push(string pIDP, string pNombre, string pCorreo, string pPassword) {
    if (aHead == NULL) {
        aHead = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail = aHead;
    }
    else {
        if (pIDP <= aHead->sIDP) {
            push_front(pIDP, pNombre, pCorreo, pPassword);
        }
        else if (pIDP >= aTail->sIDP) {
            push_back(pIDP, pNombre, pCorreo, pPassword);
        }
        else {
            PDNODO2 lItem = search(pIDP);
            if (lItem) {
                PDNODO2 lTemp = getNewNode(pIDP, pNombre, pCorreo, pPassword);
                lTemp->sNext = lItem;
                lTemp->sPrev = lItem->sPrev;
                lItem->sPrev->sNext = lTemp;
                lItem->sPrev = lTemp;
            }
        }
    }
}

void DListAlumno::InsertarAlumno(void) {
    string auxID;
    string auxNom;
    string auxCorreo;
    string auxPass;

    cout << "Ingrese el ID" << endl;
    getline(cin, auxID);
    PDNODO2 lTemp = find(auxID);
    while (lTemp != NULL) {
        cout << "ID ya registrado, ingrese otro: ";
        getline(cin, auxID);
        lTemp = find(auxID);
    }
    cout << endl;
    cout << "Ingrese el nombre: ";
    getline(cin, auxNom);
    cout << endl;
    cout << "Ingrese password: ";
    getline(cin, auxPass);
    auxCorreo = auxID + "@up.edu.mx";

    push(auxID, auxNom, auxCorreo, auxPass);

    cout << endl;
    cout << "--------------" << endl;
    cout << "Registro guardado con exito" << endl;

    write("Alumnos.csv");

}


PDNODO2 DListAlumno::top_front(void) {

    if (aHead) {
        return aHead;
    }
    return NULL;
}

PDNODO2 DListAlumno::top_back(void) {
    if (aHead) {
        return aTail;
    }

    return NULL;
}

PDNODO2 DListAlumno::get(void) {

    PDNODO2 lTemp = NULL;

    if (aHead) {
        if (aCurr == NULL) {
            aCurr = aHead;
        }
        else {
            aCurr = aCurr->sNext;
        }
        lTemp = aCurr;

    }

    return lTemp;

}


void DListAlumno::pop_front(void) {
    if (aHead) {

        PDNODO2 lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        delete aHead;
        aHead = lTemp;

        if (aHead == NULL) {
            aTail = NULL;
            aCurr = NULL;
        }
        else {
            aHead->sPrev = NULL;
            aCurr = (lEqual ? aHead : aCurr);
        }
    }
}

void DListAlumno::pop_back(void) {
    if (aHead) {
        PDNODO2 lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;

        if (aTail == NULL) {
            aHead = NULL;
            aCurr = NULL;
        }
        else {
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
    }
}

void DListAlumno::del(string pIDP) {

    if (aHead) {
        if (aHead->sIDP == pIDP) {
            pop_front();
        }
        else if (aHead->sIDP == pIDP) {
            pop_back();
        }
        else {
            PDNODO2 lTemp = find(pIDP);
            if (lTemp) {
                if (aCurr == lTemp)
                    aCurr = lTemp->sNext;
                lTemp->sPrev->sNext = lTemp->sNext;
                lTemp->sNext->sPrev = lTemp->sPrev;
                delete lTemp;
            }
        }
    }

}

void DListAlumno::read(string pPath) {
    CSVReader lReader = CSVReader(pPath);
    TCSVTbl lTbl = lReader.read();

    if (lTbl.size() > 0) {
        for (size_t lCol = 0; lCol < lTbl.size(); lCol++) {
            push(lTbl[lCol][0], lTbl[lCol][1], lTbl[lCol][2], lTbl[lCol][3]);
        }
    }
}

void DListAlumno::write(string pPath)
{
    if (aHead) {
        CSVWriter lWriter = CSVWriter(pPath);
        PDNODO2 lTemp = aHead;
        while (lTemp) {
            lWriter.write(lTemp->sIDP);
            lWriter.write(lTemp->sNombre);
            lWriter.write(lTemp->sCorreo);
            lWriter.write(lTemp->sPassword);
            lWriter.writeeol();
            lTemp = lTemp->sNext;
        }
    }
} // write

bool DListAlumno::ExisteAlumno(string pIDP) {
    PDNODO2 lTemp = find(pIDP);

    if (lTemp) {
        return true;
    }
    else {
        return false;
    }
}

bool DListAlumno::isEmpty(void) {
    return(aHead == NULL);
}

void DListAlumno::repr(void) {
    if (aHead) {
        PDNODO2 lTemp = aHead;
        while (lTemp) {
            cout << "( " + lTemp->sIDP + ", " + lTemp->sNombre + ", " + lTemp->sCorreo + ")  " << endl;
            lTemp = lTemp->sNext;
        }
    }
}

PDNODO2 DListAlumno::find(string pIDP) {
    PDNODO2 lTemp = aHead;

    while (lTemp) {
        if (lTemp->sIDP == pIDP) {

            return lTemp;
        }

        lTemp = lTemp->sNext;
    }

    return NULL;
}

PDNODO2 DListAlumno::search(string pIDP) {
    PDNODO2 lTemp = aHead;

    while (lTemp) {
        if (pIDP <= lTemp->sIDP) {
            return lTemp;
        }
        lTemp = lTemp->sNext;
    }

    return NULL;
}

PDNODO2 DListAlumno::getNewNode(string pIDP, string pNombre, string pCorreo, string pPassword) {

    PDNODO2 lTemp = new DNODO2;

    if (lTemp) {
        lTemp->sIDP = pIDP;
        lTemp->sNombre = pNombre;
        lTemp->sCorreo = pCorreo;
        lTemp->sPassword = pPassword;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;

    }

    return lTemp;

}

//------------------------------- Administracion -----------------------------------------

DListAdmin::DListAdmin(void) {
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
}

DListAdmin:: ~DListAdmin(void) {
    clean();
}

void DListAdmin::clean(void) {
    while (aHead) {
        PDNODO lTemp = aHead->sNext;
        delete aHead;

        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
}

void DListAdmin::push_front(string pIDP, string pNombre, string pCorreo, string pPassword) {

    if (aHead == NULL) {
        aHead = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail = aHead;
    }
    else {
        PDNODO lTemp = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aHead->sPrev = lTemp;
        lTemp->sNext = aHead;
        aHead = lTemp;
    }

}

void DListAdmin::push_back(string pIDP, string pNombre, string pCorreo, string pPassword) {
    if (aHead == NULL) {
        aHead = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail = aHead;
    }
    else {
        PDNODO lTemp = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
    }
}

void DListAdmin::push(string pIDP, string pNombre, string pCorreo, string pPassword) {
    if (aHead == NULL) {
        aHead = getNewNode(pIDP, pNombre, pCorreo, pPassword);
        aTail = aHead;
    }
    else {
        if (pIDP <= aHead->sIDP) {
            push_front(pIDP, pNombre, pCorreo, pPassword);
        }
        else if (pIDP >= aTail->sIDP) {
            push_back(pIDP, pNombre, pCorreo, pPassword);
        }
        else {
            PDNODO lItem = search(pIDP);
            if (lItem) {
                PDNODO lTemp = getNewNode(pIDP, pNombre, pCorreo, pPassword);
                lTemp->sNext = lItem;
                lTemp->sPrev = lItem->sPrev;
                lItem->sPrev->sNext = lTemp;
                lItem->sPrev = lTemp;
            }
        }
    }
}

void DListAdmin::InsertarAdmin(void) {
    string auxID;
    string auxNom;
    string auxCorreo;
    string auxPass;

    cout << "Ingrese el ID" << endl;
    getline(cin, auxID);
    PDNODO lTemp = find(auxID);
    while (lTemp != NULL) {
        cout << "ID ya registrado, ingrese otro: ";
        getline(cin, auxID);
        lTemp = find(auxID);
    }
    cout << endl;
    cout << "Ingrese el nombre: ";
    getline(cin, auxNom);
    cout << endl;
    cout << "Ingrese password: ";
    getline(cin, auxPass);
    auxCorreo = auxID + "@up.edu.mx";

    push(auxID, auxNom, auxCorreo, auxPass);

    cout << endl;
    cout << "--------------" << endl;
    cout << "Registro guardado con exito" << endl;

    write("Admin.csv");



}


PDNODO DListAdmin::get(void) {

    PDNODO lTemp = NULL;

    if (aHead) {
        if (aCurr == NULL) {
            aCurr = aHead;
        }
        else {
            aCurr = aCurr->sNext;
        }
        lTemp = aCurr;

    }

    return lTemp;

}


void  DListAdmin::pop_front(void) {
    if (aHead) {

        PDNODO lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        delete aHead;
        aHead = lTemp;

        if (aHead == NULL) {
            aTail = NULL;
            aCurr = NULL;
        }
        else {
            aHead->sPrev = NULL;
            aCurr = (lEqual ? aHead : aCurr);
        }
    }
}

void DListAdmin::pop_back(void) {
    if (aHead) {
        PDNODO lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;

        if (aTail == NULL) {
            aHead = NULL;
            aCurr = NULL;
        }
        else {
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
    }
}

void DListAdmin::del(string pIDP) {

    if (aHead) {
        if (aHead->sIDP == pIDP) {
            pop_front();
        }
        else if (aHead->sIDP == pIDP) {
            pop_back();
        }
        else {
            PDNODO lTemp = find(pIDP);
            if (lTemp) {
                if (aCurr == lTemp)
                    aCurr = lTemp->sNext;
                lTemp->sPrev->sNext = lTemp->sNext;
                lTemp->sNext->sPrev = lTemp->sPrev;
                delete lTemp;
            }
        }
    }

}

void DListAdmin::read(string pPath) {
    CSVReader lReader = CSVReader(pPath);
    TCSVTbl lTbl = lReader.read();

    if (lTbl.size() > 0) {
        for (size_t lCol = 0; lCol < lTbl.size(); lCol++) {
            push(lTbl[lCol][0], lTbl[lCol][1], lTbl[lCol][2], lTbl[lCol][3]);
        }
    }
}

void  DListAdmin::write(string pPath)
{
    if (aHead) {
        CSVWriter lWriter = CSVWriter(pPath);
        PDNODO lTemp = aHead;
        while (lTemp) {
            lWriter.write(lTemp->sIDP);
            lWriter.write(lTemp->sNombre);
            lWriter.write(lTemp->sCorreo);
            lWriter.write(lTemp->sPassword);
            lWriter.writeeol();
            lTemp = lTemp->sNext;
        }
    }
} // write

string DListAdmin::findContra(string usuario) {
    PDNODO lTemp = find(usuario);

    return lTemp->sPassword;
}

bool DListAdmin::ExisteAdmin(string pIDP) {
    PDNODO lTemp = find(pIDP);

    if (lTemp) {
        return true;
    }
    else {
        return false;
    }
}

bool DListAdmin::isEmpty(void) {
    return(aHead == NULL);
}

void DListAdmin::repr(void) {
    if (aHead) {
        PDNODO lTemp = aHead;
        while (lTemp) {
            cout << "( " + lTemp->sIDP + ", " + lTemp->sNombre + ", " + lTemp->sCorreo + ")  " << endl;
            lTemp = lTemp->sNext;
        }
    }
}

PDNODO  DListAdmin::find(string pIDP) {
    PDNODO lTemp = aHead;

    while (lTemp) {
        if (lTemp->sIDP == pIDP) {

            return lTemp;
        }

        lTemp = lTemp->sNext;
    }

    return NULL;
}

bool DListAdmin::AdminValid(string pNombre, string pPass){
    PDNODO lTemp = aHead;

    while (lTemp) {
        if (lTemp->sIDP == pNombre && lTemp->sPassword == pPass) {

            return true;
        }

        lTemp = lTemp->sNext;
    }

    return false;
}

bool DListAlumno::checkValid(string pID, string pPass){
    PDNODO2 lTemp = aHead;

    while (lTemp) {
        if (lTemp->sIDP == pID && lTemp->sPassword == pPass) {

            return true;
        }

        lTemp = lTemp->sNext;
    }

    return false;
};

bool DListProf::checkValid(string pNombre, string pPass){
    PDNODO lTemp = aHead;

    while (lTemp) {
        if (lTemp->sIDP == pNombre && lTemp->sPassword == pPass) {

            return true;
        }

        lTemp = lTemp->sNext;
    }

    return false;
};

PDNODO DListAdmin::search(string pIDP) {
    PDNODO lTemp = aHead;

    while (lTemp) {
        if (pIDP <= lTemp->sIDP) {
            return lTemp;
        }
        lTemp = lTemp->sNext;
    }

    return NULL;
}

PDNODO  DListAdmin::getNewNode(string pIDP, string pNombre, string pCorreo, string pPassword) {

    PDNODO lTemp = new DNODO;

    if (lTemp) {
        lTemp->sIDP = pIDP;
        lTemp->sNombre = pNombre;
        lTemp->sCorreo = pCorreo;
        lTemp->sPassword = pPassword;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;

    }

    return lTemp;

}
