#include "Listas.h"
#include "CSV.h"
#include "Profesors.h"
#include "InfoClases.h"
#include <vector>

string DLIndex::aHeadver() {
    if (aHead == NULL) {
        return "vacio";
    }
    else {
        return "algo";
    }
}

DLIndex::DLIndex(ECampos pType, bool pFrec)
{
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
    aFrec = pFrec;
    aType = pType;
} // Constructor

DLIndex::~DLIndex(void)
{
    clean();
    // cout << "Bye!" << endl;
} // Destructor

void DLIndex::clean(void)
{
    while (aHead) {
        PDNODE lTemp = aHead->sNext;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean

void DLIndex::push_front(PDATA pData) // Va a pushear un string
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead; //si la  lista está vacía, el atail y el ahead están en el mismo lugar
    }
    else {
        PDNODE lTemp = getNewNode(pData);
        aHead->sPrev = lTemp;
        lTemp->sNext = aHead;
        aHead = lTemp;
    }
}
// push_front 

void DLIndex::push_back(PDATA pData) //hace un push en el tail, tiene la misma lógica que el push_front
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {
        PDNODE lTemp = getNewNode(pData);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
    }
}
// push_back

void DLIndex::push(PDATA pData) //hace un push normal
{
    cout << "verificador de ahead - " << aHeadver() << endl;
    if (aHead == NULL) { //si no hay aHead, crea el primer nodo de la lista
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else { //si hay llista:
        if (comp(pData, aHead->sData) <= 0) //verifica que el push sea menor o igual a la cabeza de la lista, si es así, mete un push_Front
            push_front(pData);
        else if (comp(pData, aTail->sData) >= 0) //verifica que el push sea mayor o igual a la cola de la lista, si es así, mete un push_back
            push_back(pData);
        else { //si está en medio de la cabeza y cola
            PDNODE lItem = search(pData); //busca lugar disponible en la lista
            if (lItem) { //si sí encuentra una dirección de memoria
               /* if (aFrec && (lItem->sNombre == pNombre)) { //primero verifica si el nombre en esa direccion de memoria es igual al string dado, si es así, aumenta la frecuencia
                    (lItem->sFrec)++;
                }
                else { //si no hay frecuencia y no son iguales, solamente añade un nuevo nodo con el string.*/
                PDNODE lTemp = getNewNode(pData);
                lTemp->sNext = lItem;
                lTemp->sPrev = lItem->sPrev;
                lItem->sPrev->sNext = lTemp;
                lItem->sPrev = lTemp;
            }
        }
    }
} // push*/


PDATA DLIndex::get(bool pRev) ///te da la direccion de memoria donde se encuentra accur
{
    PDATA lTemp = NULL;

    if (aHead) {
        if (aCurr == NULL)
            aCurr = (pRev == false ? aHead : aTail);
        else
            aCurr = (pRev == false ? aCurr->sNext : aCurr->sPrev);
        if (aCurr)
            lTemp = aCurr->sData;
    }

    return lTemp;
} // get

void DLIndex::pop_front(void) //borrar la direccion de memoria de aHead
{
    if (aHead) {
        PDNODE lTemp = aHead->sNext;
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
    else {
        return;
    }
} // pop_front

void DLIndex::pop_back(void) // borra la ultima dirección de memoria, actúa parecido que el pop_front
{
    bool lDo = true;

    if (aHead) {

        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;
        if (aTail) { //solo que aquí cambia el sNext porque si es la ultima posición, debe ser nulo su next
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
        else {
            aHead = NULL;
            aCurr = NULL;
        }


    }
    else {
        return;
    }

} // pop_back

void DLIndex::del(PDATA pData) //borra un elemento cualquiera de la lista
{
    if (aHead) { //verifica que la lista exista
        if (aHead->sData == pData) //si el string que se quiere borrar es igual al nombre guardado en aHead, hace un pop_front
            pop_front();
        else if (aTail->sData == pData) //si el string que se quiere borrar es igual al nombre guardado en aTail, hace un pop_back
            pop_back();
        else { //si no está ni en aHead ni aTail
            PDNODE lTemp = find(pData); //busca dónde está el nombre
            if (lTemp) { //si existe esa direccion de memoria
                if (aCurr == lTemp)
                    aCurr = lTemp->sNext;
                lTemp->sPrev->sNext = lTemp->sNext;
                lTemp->sNext->sPrev = lTemp->sPrev;
                delete lTemp;
            }
        }
    }
}

bool DLIndex::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DLIndex::repr(bool pRev) //solo imprime los datos guardados en la lista, ya sea con frecuencia o sin ella
{
    if (aHead) {
        PDNODE lTemp = (pRev == false ? aHead : aTail);
        while (lTemp) {
            cout << " -> ";
            cout << "[" << lTemp->sData->sNombre << ",";
            cout << lTemp->sData->sID << ",";
            cout << lTemp->sData->sSalon << ",";
            cout << lTemp->sData->sProfesor << ",";
            cout << lTemp->sData->sDisponibilidad << "]";
            /*if (aFrec)
                cout << " #" << lTemp->sFrec;*/
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << " ->|| " << endl;
    }
} // repr

int DLIndex::comp(PDATA pA, PDATA pB) {
    int lRes = 0;

    switch (aType) {
    case ECampos::nombre:
        if (pA->sNombre < pB->sNombre) lRes = -1;
        else if (pA->sNombre == pB->sNombre) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::salon:
        if (pA->sSalon < pB->sSalon) lRes = -1;
        else if (pA->sSalon == pB->sSalon) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::profesor:
        if (pA->sProfesor < pB->sProfesor) lRes = -1;
        else if (pA->sProfesor == pB->sProfesor) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::disponibilidad:
        if (pA->sDisponibilidad < pB->sDisponibilidad) lRes = -1;
        else if (pA->sDisponibilidad == pB->sDisponibilidad) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::id:
        if (pA->sID < pB->sID) lRes = -1;
        else if (pA->sID == pB->sID) lRes = 0;
        else lRes = 1;
        break;

    }

    return lRes;
}


PDNODE DLIndex::find(PDATA pData) // solo busca que sea igual a un nombre en una dirección de memoria, si no, regresa NULL
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pData == lTemp->sData)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find 

PDNODE DLIndex::search(PDATA pData) //recorre la lista desde la cabeza hasta si el nombre buscado es igual al que hay en una dirección de memoria o menor
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (comp(pData, lTemp->sData) <= 0)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search*/


PDNODE DLIndex::getNewNode(PDATA pData) //te da un nodo nuevo
{
    PDNODE lTemp = new DNODE; //crea un nuevo nodo de la estructura DNODE

    if (lTemp) { //si sí te da una direccion de memoria
        lTemp->sData = pData;
        lTemp->sFrec = 1; //empieza con frecuencia de 1
        lTemp->sNext = NULL; //por el momento su next y prev son nulos 
        lTemp->sPrev = NULL;
    }

    return lTemp;// te regresa el nodo
} // getNewNode



// --------------------------------------

DList::DList(bool pFrec)
{
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
    aFrec = pFrec;

    aINom = new DLIndex(ECampos::nombre);
    aISalon = new DLIndex(ECampos::salon);
    aIProf = new DLIndex(ECampos::profesor);
    aIDis = new DLIndex(ECampos::disponibilidad);
    aIID = new DLIndex(ECampos::id);
} // Constructor

DList::~DList(void)
{
    clean();
    if (aINom) delete aINom;
    if (aISalon) delete aISalon;
    if (aIProf) delete aIProf;
    if (aIDis) delete aIDis;
    if (aIID) delete aIID;
    // cout << "Bye!" << endl;
} // Destructor

void DList::clean(void)
{
    while (aHead) {
        PDNODE lTemp = aHead->sNext;
        if (aHead->sData)
            delete aHead->sData;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean


void DList::push_back(string pNombre, string pSalon, string pProfesor, string pDisponibilidad, string pID) //hace un push en el tail, tiene la misma lógica que el push_front
{
    if (aHead == NULL) {
        cout << "Hola" << endl;
        aHead = getNewNode(pNombre, pSalon, pProfesor, pDisponibilidad, pID);

        aTail = aHead;

        aINom->push(aHead->sData);
        aISalon->push(aHead->sData);
        aIProf->push(aHead->sData);
        aIDis->push(aHead->sData);
        aIID->push(aHead->sData);
    }
    else {
        PDNODE lTemp = getNewNode(pNombre, pSalon, pProfesor, pDisponibilidad, pID);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
        aINom->push(lTemp->sData);
        aISalon->push(lTemp->sData);
        aIProf->push(lTemp->sData);
        aIDis->push(lTemp->sData);
        aIID->push(lTemp->sData);
    }
}
// push_back





PDATA DList::get(ECampos pCampo, bool pRev) ///te da la direccion de memoria donde se encuentra accur
{
    PDATA lTemp = NULL;

    switch (pCampo) {
    case ECampos::nombre: lTemp = aINom->get(pRev); break;
    case ECampos::salon: lTemp = aISalon->get(pRev); break;
    case ECampos::profesor: lTemp = aIProf->get(pRev); break;
    case ECampos::disponibilidad: lTemp = aIDis->get(pRev); break;
    case ECampos::id: lTemp = aIID->get(pRev); break;
    }


    return lTemp;
} // get

void DList::pop_front(void) //borrar la direccion de memoria de aHead
{

    if (aHead) {
        PDNODE lTemp = aHead->sNext; //crea una direccion de memoria temporal con la siguiente direccion de memoria al aHead
        bool lEqual = (aHead == aCurr); //si el aHead es igual al Acurr, lEqual será verdadero, sino falso
        delete aHead; //borra el aHead
        aHead = lTemp; //ahora el aHead será la variable temporal
        if (aHead) { //si existe el aHead
            aHead->sPrev = NULL; //el previo del aHead será nulo 
            aCurr = (lEqual ? aHead : aCurr); //y aCurr será aHead si estaba en el aHead, sino seguirá siendo aCurr
        }
        else { //si no existe la lista, el aTail y el aCurr serán nulos
            aTail = NULL;
            aCurr = NULL;
        }
    }
} // pop_front

void DList::pop_back(void) // borra la ultima dirección de memoria, actúa parecido que el pop_front
{
    if (aHead) {
        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;
        if (aTail) { //solo que aquí cambia el sNext porque si es la ultima posición, debe ser nulo su next
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
        else {
            aHead = NULL;
            aCurr = NULL;
        }
    }
} // pop_back

void DList::del(string pID) //borra un elemento cualquiera de la lista
{
    PDNODE lTemp = find(pID);
    if (lTemp) {
        aINom->del(lTemp->sData);
        aISalon->del(lTemp->sData);
        aIProf->del(lTemp->sData);
        aIDis->del(lTemp->sData);
        aIID->del(lTemp->sData);
    }
    if (aHead->sData->sID == pID) {
        pop_front();
    }
    else if (aTail->sData->sID == pID) {
        pop_back();
    }
    else {
        if (lTemp) {
            if (aCurr == lTemp)
                aCurr = lTemp->sNext;
            lTemp->sPrev->sNext = lTemp->sNext;
            lTemp->sNext->sPrev = lTemp->sPrev;
            if (lTemp->sData)
                delete lTemp->sData;
            delete lTemp;
        }
    }
} // del 

bool DList::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DList::repr(ECampos pCampo, bool pRev) //solo imprime los datos guardados en la lista, ya sea con frecuencia o sin ella
{
    if (aHead) {
        switch (pCampo) {
        case ECampos::nombre: aINom->repr(pRev); break;
        case ECampos::salon:aISalon->repr(pRev); break;
        case ECampos::profesor: aIProf->repr(pRev); break;
        case ECampos::disponibilidad: aIDis->repr(pRev); break;
        case ECampos::id: aIID->repr(pRev); break;
        }

    }
} // repr

void DList::reprprof(string pID){
    if (aHead) {
        PDNODE lTemp = (aHead);
        while (lTemp) {
            //cout<<pID<<"?="<<lTemp->sData->sID<<endl;
            if(pID == lTemp->sData->sProfesor){
                cout << " -> ";
                cout << lTemp->sData->sID << " ";
                cout << lTemp->sData->sNombre << ", Salon - ";
                cout << lTemp->sData->sSalon << ", ";
                //cout << lTemp->sData->sProfesor << ",";
                cout << lTemp->sData->sDisponibilidad << endl;
                /*if (aFrec)
                    cout << " #" << lTemp->sFrec;*/
            }
            lTemp = (lTemp->sNext);
        }
        cout << endl;
    }
}

void DList::read(string pPath) {
    CSVReader lReader = CSVReader(pPath);
    TCSVTbl lTbl = lReader.read();

    if (lTbl.size() > 0) {
        for (size_t lCol = 0; lCol < lTbl.size(); lCol++) {
            push_back(lTbl[lCol][0], lTbl[lCol][1], lTbl[lCol][2], lTbl[lCol][3], lTbl[lCol][4]);
        }
    }
}

void DList::write(string pPath)
{
    if (aHead) {
        CSVWriter lWriter = CSVWriter(pPath);
        PDNODE lTemp = aHead;
        while (lTemp) {
            lWriter.write(lTemp->sData->sNombre);
            lWriter.write(lTemp->sData->sSalon);
            lWriter.write(lTemp->sData->sProfesor);
            lWriter.write(lTemp->sData->sDisponibilidad);
            lWriter.write(lTemp->sData->sID);
            lWriter.writeeol();
            lTemp = lTemp->sNext;
        }
    }
} // write
PDNODE DList::find(string pID) // solo busca que sea igual a un nombre en una dirección de memoria, si no, regresa NULL
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pID == lTemp->sData->sID)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find 

PDNODE DList::getNewNode(string pNombre, string pSalon, string pProfesor, string pDisponibilidad, string pID) //te da un nodo nuevo
{
    PDNODE lTemp = new DNODE; //crea un nuevo nodo de la estructura DNODE

    if (lTemp) { //si sí te da una direccion de memoria
        lTemp->sData = new Materia;
        if (lTemp->sData) {
            lTemp->sData->sNombre = pNombre;
            lTemp->sData->sSalon = pSalon;//le pone el string en el nombre
            lTemp->sData->sProfesor = pProfesor;
            lTemp->sData->sDisponibilidad = pDisponibilidad;
            lTemp->sData->sID = pID;
        }
        lTemp->sFrec = 1; //empieza con frecuencia de 1
        lTemp->sNext = NULL; //por el momento su next y prev son nulos 
        lTemp->sPrev = NULL;
    }

    return lTemp;// te regresa el nodo
} // getNewNode

void DList::modify(ECampos pCampo, string pNombre, string pNuevo) {
    PDNODE lTemp = find(pNombre);
    if (lTemp) {

        
        switch (pCampo) {

        case ECampos::nombre: lTemp->sData->sNombre = pNuevo; break;
        case ECampos::salon: lTemp->sData->sSalon = pNuevo; break;
        case ECampos::profesor: lTemp->sData->sProfesor = pNuevo; break;
        case ECampos::disponibilidad: lTemp->sData->sDisponibilidad = pNuevo; break;
        case ECampos::id: lTemp->sData->sID = pNuevo; break;

        }
    }
}

string DList::getName(string ID) {

    if (aHead) {
        PDNODE lTemp = find(ID);
        if (lTemp) {
            return lTemp->sData->sNombre;
        }
    }

    return "NULL";

}



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
};

aClase::aClase() {

    //aux = DList();
    ynombre = "";
    yID = "";
    yprofesor = "";
    ysalon = "";
    yDisponibilidad = "";

}

void aClase::addClase() {
    if (!prof.isEmpty()) {
        cout << "Se va a agregar una materia nueva " << endl;
        cout << "Ingrese el ID de la materia: ";
        getline(cin, yID);
        cout << "Ingrese el nombre de la materia: ";
        getline(cin, ynombre);
        cout << "Ingrese el salon: ";
        getline(cin, ysalon);
        cout << "Ingrese el ID del profesor: ";
        getline(cin, yprofesor);
        while (prof.ExisteProfe(yprofesor) == NULL) {
            cout << "ID incorrecto, ingrese otro: ";
            getline(cin, yprofesor);
        }
        yDisponibilidad = "Disponible";

        aux.push_back(ynombre, ysalon, yprofesor, yDisponibilidad, yID);

        aux.write("Libro2.csv");
    }
    else {
        cout << "No hay profesores registrados" << endl;
    }
}

void aClase::addClase(string profeID) {
    if (!prof.isEmpty()) {
        cout << "Se va a agregar una materia nueva " << endl;
        cout << "Ingrese el ID de la materia: ";
        getline(cin, yID);
        cout << "Ingrese el nombre de la materia: ";
        getline(cin, ynombre);
        cout << "Ingrese el salon: ";
        getline(cin, ysalon);
        /*cout << "Ingrese el ID del profesor: ";
        getline(cin, yprofesor);
        while (prof.ExisteProfe(yprofesor) == NULL) {
            cout << "ID incorrecto, ingrese otro: ";
            getline(cin, yprofesor);
        }*/
        yDisponibilidad = "Disponible";

        aux.push_back(ynombre, ysalon, profeID, yDisponibilidad, yID);

        aux.write("Libro2.csv");
    }
    else {
        cout << "No hay profesores registrados" << endl;
    }
}

void aClase::ModificarDatoDeClase() {
    string pNombre;
    string newdata;
    int auxiliar;
    cout << "Modificar datos" << endl;
    cout << "Ingrese el ID de la materia: ";
    getline(cin, pNombre);
    cout << "Ingrese el número del dato que se desea cambiar" << endl;
    cout << "1. nombre" << endl;
    cout << "2. Salon" << endl;
    cout << "3. Profesor" << endl;
    cout << "4. ID" << endl;
    cin >> auxiliar;
    cin.ignore();
    PHNODE temp = classes.find(pNombre);
    //cout<<"clase encontrada - "<<temp->sID<<endl;

    cout << "Ingrese el nuevo dato: " << endl;
    getline(cin, newdata);

    switch (auxiliar) {
    case 1: aux.modify(ECampos::nombre, pNombre, newdata); temp->sClas = newdata; break;
    case 2: aux.modify(ECampos::salon, pNombre, newdata); break;
    case 3: aux.modify(ECampos::profesor, pNombre, newdata); break;
    case 4:aux.modify(ECampos::id, pNombre, newdata); temp->sID = newdata; break;
    }
    //cout<<"clase actualizada - "<<temp->sID<<endl;

    aux.write("Libro2.csv");
}

void aClase::EliminarClase() {
    string idd;
    cout << "Ingrese el ID de la clase a eliminar: " << endl;
    getline(cin, idd);
    aux.del(idd);

    aux.write("Libro2.csv");
}

void aClase::mostrarClases() {
    aux.repr(ECampos::id);
}

void aClase::mostrarClasesProf(string pID) {
    aux.reprprof(pID);
}

void aClase::InsertData() {
    aux.read("Libro2.csv");

}

void aClase::GuardarData() {
    aux.write("Libro2.csv");
}
void aClase::MeterMateria(string AlumID) {
    if (!aux.isEmpty()) {
        string idMat;
        cout << "Materias a inscribir: " << endl;
        cout << "----------------------" << endl;
        aux.repr(ECampos::id);
        cout << "----------------------" << endl;
        cout << "Ingrese el ID de la materia: ";
        getline(cin, idMat);

        string nom = aux.getName(idMat);
        if (nom == "NULL") {
            cout << "Clase no encontrada" << endl;
        }
        else {
            classes.push(nom, idMat, AlumID);
        }
    }
    else {
        cout<<"No hay materias"<<endl;
    }


}

int main() {
    aClase sob = aClase();
    int opci, subs = 1;
    //sob.admi.InsertarAdmin();
    sob.admi.read("Admin.csv");
    sob.prof.read("Profesores.csv"); 
    sob.alumn.read("Alumnos.csv");
    sob.classes.read("Inscripciones.txt");
    sob.InsertData();
    do {
        system("CLS");
        cout << "BIENVENIDO AL SISTEMA DE LA UNIVERSIDAD UP" << endl;
        cout << "0. Salir" << endl;
        cout << "1. Ingresar como administrador" << endl;
        cout << "2. Ingresar como profesor" << endl;
        cout << "3. Ingresar como alumno" << endl;
        cin >> opci;
        cin.ignore();
        if(opci==1){
            string uss, pas;
            cout<<"Ingrese el nombre de usuario del administrador >> ";
            cin >> uss;
            cin.ignore();
            cout<<"Ingrese la contraseña >> ";
            cin >> pas;
            cin.ignore();
            if(!sob.admi.AdminValid(uss, pas)){
                cout << "Datos inválidos." << endl;
            }else{
                do {
                    system("CLS");
                    cout << "BIENVENIDO AL PANEL DE ADMINISTRADOR" << endl;
                    cout << "0. Salir" << endl;
                    cout << endl << endl << "CONFIGURACIÓN DE CLASES" << endl;
                    cout << "1. Agregar una clase" << endl;
                    cout << "2. Modificar una clase" << endl;
                    cout << "3. Eliminar una clase" << endl;
                    cout << "4. Mostrar Clases " << endl;
                    cout << "5. Insertar datos " << endl;
                    cout << "6. Guardar datos" << endl;
                    cout << endl << endl << "CONFIGURACIÓN DE PROFESORES" << endl;
                    cout << "7. Agregar Profe" << endl;
                    cout << "8. Insertar Profesores" << endl;
                    cout << "9. Mostrar profesores" << endl;
                    cout << "10. Guardar profesores" << endl;
                    cout << endl << endl << "CONFIGURACIÓN DE ALUMNOS" << endl;
                    cout << "11. Agregar Alumno" << endl;
                    cout << "12. Insertar Alumnos" << endl;
                    cout << "13. Mostrar Alumnos" << endl;
                    cout << "14. Guardar profesores" << endl;
                    cout << endl << endl << "CONFIGURACIÓN DE ADMINISTRADORES" << endl;
                    cout << "15. Agregar Administrador" << endl;
                    cout << "16. Cargar Administradores" << endl;
                    cout << "17. Mostrar Administradores" << endl;
                    cout << "18. Guardar profesores" << endl;
                    cout << endl << endl << "CONFIGURACIÓN DE MATERIAS E INSCRIPCIONES" << endl;
                    cout << "19. Inscribir materias" << endl;
                    cout << "20. Ver Inscripciones" << endl;
                    cout << "21. Subir inscripciones" << endl;
                    cout << "22. Guardar inscripciones" << endl;
                    cin >> subs;
                    cin.ignore();
                    switch(subs){
                        case 1: sob.addClase(); break;
                        case 2: sob.ModificarDatoDeClase(); break;
                        case 3: sob.EliminarClase(); break;
                        case 4: sob.mostrarClases(); break;
                        case 5: sob.InsertData(); break;
                        case 6: sob.GuardarData(); break;

                        case 7: sob.prof.InsertarProfe(); break;
                        case 8: sob.prof.read("Profesores.csv"); break;
                        case 9: sob.prof.repr(); break;
                        case 10:sob.prof.write("Profesores.csv"); break;

                        case 11:sob.alumn.InsertarAlumno(); break;
                        case 12:sob.alumn.read("Alumnos.csv"); break;
                        case 13:sob.alumn.repr(); break;
                        case 14:sob.alumn.write("Alumnos.csv"); break;

                        case 15:sob.admi.InsertarAdmin(); break;
                        case 16:sob.admi.read("Admin.csv"); break;
                        case 17:sob.admi.repr(); break;
                        case 18:sob.admi.write("Admin.csv"); break;

                        case 19:sob.MeterMateria("0236847"); break;
                        case 20:sob.classes.repr(); break;
                        case 21:sob.classes.read("Inscripciones.txt"); break;
                        case 22:sob.classes.write("Inscripciones.txt"); break;
                    }
                    system("pause");
                }while(subs!=0);
            }
        }else if(opci==2){
            string uss, pas;
            cout<<"Ingrese el ID del profesor >> ";
            cin >> uss;
            cin.ignore();
            cout<<"Ingrese la contraseña >> ";
            cin >> pas;
            cin.ignore();
            if(!sob.prof.checkValid(uss, pas)){
                cout << "Datos inválidos." << endl;
            }else{
                do {
                    cout << "BIENVENIDO AL PANEL DE PROFESORES" << endl;
                    cout << endl;
                    cout<<"Mis clases:"<<endl;
                    sob.mostrarClasesProf(uss);
                    cout << endl;
                    cout << "0. Salir" << endl;
                    cout << "1. Agregar clase" << endl;
                    cout << "2. Modificar clase" << endl;
                    cout << "3. Eliminar clase" << endl;
                    cin >> subs;
                    cin.ignore();
                    switch(subs){
                        case 1: sob.addClase(uss); break;
                        case 2: sob.ModificarDatoDeClase(); break;
                        case 3: sob.EliminarClase(); break;
                    }
                    system("pause");
                }while(subs!=0);
            }
        }else if(opci==3){
            string uss, pas;
            cout<<"Ingrese el ID del alumno >> ";
            cin >> uss;
            cin.ignore();
            cout<<"Ingrese la contraseña >> ";
            cin >> pas;
            cin.ignore();
            if(!sob.alumn.checkValid(uss, pas)){
                cout << "Datos inválidos." << endl;
            }else{
                PDNODO2 alumno = sob.alumn.find(uss);
                do {
                    system("CLS");
                    cout << alumno->sIDP << "\t" << alumno->sNombre << "\t\t" << alumno->sCorreo << endl;
                    cout << "BIENVENIDO AL PANEL DE ALUMNOS" << endl;
                    cout << endl;
                    cout << "Clases inscritas: " << endl;
                    sob.classes.inscrrepr(uss);
                    cout << endl;
                    cout << "0. Salir" << endl;
                    cout << "1. Inscribir materia" << endl;
                    cin >> subs;
                    cin.ignore();
                    switch(subs){
                        case 1:sob.MeterMateria(uss); break;
                    }
                    system("pause");
                }while(subs!=0);
            }
        }
        

        /*cout << "Ingrese el número de lo que desea hacer: " << endl;
        cout << "1. Agregar una clase" << endl;
        cout << "2. Modificar una clase" << endl;
        cout << "3. Eliminar una clase" << endl;
        cout << "4. Mostrar Clases " << endl;
        cout << "5. Insertar datos " << endl;
        cout << "6. Guardar datos" << endl;
        cout << "7. Agregar Profe" << endl;
        cout << "8. Insertar Profesores" << endl;
        cout << "9. Mostrar profesores" << endl;
        cout << "10. Agregar Alumno" << endl;
        cout << "11. Insertar Alumnos" << endl;
        cout << "12. Mostrar Alumnos" << endl;
        cout << "13. Agregar Administrador" << endl;
        cout << "14. Cargar Administradores" << endl;
        cout << "15. Mostrar Administradores" << endl;
        cout << "16. Inscribir materias" << endl;
        cout << "17. Ver Inscripciones" << endl;
        cout << "18. Guardar inscripciones" << endl;
        cout << "19. Subir inscripciones" << endl;
        cin >> opci;
        cin.ignore();
        switch (opci) {
            case 1: sob.addClase(); break;
            case 2: sob.ModificarDatoDeClase(); break;
            case 3: sob.EliminarClase(); break;
            case 4: sob.mostrarClases(); break;
            case 5: sob.InsertData(); break;
            case 6: sob.GuardarData(); break;
            case 7: sob.prof.InsertarProfe(); break;
            case 8: sob.prof.read("Profesores.csv"); break;
            case 9: sob.prof.repr(); break;
            case 10:sob.alumn.InsertarAlumno(); break;
            case 11:sob.alumn.read("Alumnos.csv"); break;
            case 12:sob.alumn.repr(); break;
            case 13:sob.admi.InsertarAdmin(); break;
            case 14:sob.admi.read("Admin.csv"); break;
            case 15:sob.admi.repr(); break;
            case 16:sob.MeterMateria("0236847"); break;
            case 17:sob.classes.repr(); break;
            case 18:sob.classes.write("Inscripciones.txt"); break;
            case 19:sob.classes.read("Inscripciones.txt"); break;
        }
        */
    } while (opci != 0);
    
}
