#include "Listas.h"



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
        if (aHead->sData->sNombre == pData->sNombre) //si el string que se quiere borrar es igual al nombre guardado en aHead, hace un pop_front
            pop_front();
        else if (aTail->sData->sNombre == pData->sNombre) //si el string que se quiere borrar es igual al nombre guardado en aTail, hace un pop_back
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
    }

    return lRes;
}


PDNODE DLIndex::find(PDATA pData) // solo busca que sea igual a un nombre en una dirección de memoria, si no, regresa NULL
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (comp(pData, lTemp->sData) == 0)
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
} // Constructor

DList::~DList(void)
{
    clean();
    if (aINom) delete aINom;
    if (aISalon) delete aISalon;
    if (aIProf) delete aIProf;
    if (aIDis) delete aIDis;
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


void DList::push_back(string pNombre, string pSalon, string pProfesor, string pDisponibilidad) //hace un push en el tail, tiene la misma lógica que el push_front
{
    if (aHead == NULL) {
        cout << "Hola" << endl;
        aHead = getNewNode(pNombre, pSalon, pProfesor, pDisponibilidad);
        aTail = aHead;

        aINom->push(aHead->sData);
        aISalon->push(aHead->sData);
        aIProf->push(aHead->sData);
        aIDis->push(aHead->sData);
    }
    else {
        PDNODE lTemp = getNewNode(pNombre, pSalon, pProfesor, pDisponibilidad);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
        aINom->push(lTemp->sData);
        aISalon->push(lTemp->sData);
        aIProf->push(lTemp->sData);
        aIDis->push(lTemp->sData);
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

void DList::del(string pNombre) //borra un elemento cualquiera de la lista
{
    PDNODE lTemp = find(pNombre);
    if (lTemp) {
        aINom->del(lTemp->sData);
        aISalon->del(lTemp->sData);
        aIProf->del(lTemp->sData);
        aIDis->del(lTemp->sData);
    }
    if (aHead->sData->sNombre == pNombre) {
        pop_front();
    }
    else if (aTail->sData->sNombre == pNombre) {
        pop_back();
    }
    else {
        if (lTemp) {
            if (aCurr == lTemp)
                aCurr = lTemp->sNext;
            lTemp->sPrev->sNext = lTemp->sNext;
            lTemp->sNext->sPrev = lTemp->sPrev;
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
        }

    }
} // repr


PDNODE DList::find(string pNombre) // solo busca que sea igual a un nombre en una dirección de memoria, si no, regresa NULL
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pNombre == lTemp->sData->sNombre)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find 

PDNODE DList::getNewNode(string pNombre, string pSalon, string pProfesor, string pDisponibilidad) //te da un nodo nuevo
{
    PDNODE lTemp = new DNODE; //crea un nuevo nodo de la estructura DNODE

    if (lTemp) { //si sí te da una direccion de memoria
        lTemp->sData = new Materia;
        if (lTemp->sData) {
            lTemp->sData->sNombre = pNombre;
            lTemp->sData->sSalon = pSalon;//le pone el string en el nombre
            lTemp->sData->sProfesor = pProfesor;
            lTemp->sData->sDisponibilidad = pDisponibilidad;
        }
        lTemp->sFrec = 1; //empieza con frecuencia de 1
        lTemp->sNext = NULL; //por el momento su next y prev son nulos 
        lTemp->sPrev = NULL;
    }

    return lTemp;// te regresa el nodo
} // getNewNode

void DList::modify(ECampos pCampo, string pNombre) {
    string newdata;
    PDNODE lTemp = find(pNombre);
    if (lTemp) {

        cout << "Ingrese el nuevo dato: " << endl;
        cin >> newdata;
        switch (pCampo) {

        case ECampos::nombre: lTemp->sData->sNombre = newdata; break;
        case ECampos::salon: lTemp->sData->sSalon = newdata; break;
        case ECampos::profesor: lTemp->sData->sProfesor = newdata; break;
        case ECampos::disponibilidad: lTemp->sData->sDisponibilidad = newdata; break;


        }
    }
}



class aClase {

protected:
    string ynombre;
    string yprofesor;
    string ysalon;
    string yDisponibilidad;
    DList aux;

public:
    aClase();
    void addClase(void);
    void ModificarDatoDeClase(void);
    void EliminarClase();
    void mostrarClases();
};

aClase::aClase() {

    aux = DList();
    ynombre = "";
    yprofesor = "";
    ysalon = "";
    yDisponibilidad = "";

}

void aClase::addClase() {
    cout << "Ingrese el nombre de la materia: ";
    cin >> ynombre;
    cout << "Ingrese el salon: ";
    cin >> ysalon;
    cout << "Ingrese el ID del profesor: ";
    cin >> yprofesor;
    yDisponibilidad = "Disponible";

    aux.push_back(ynombre, ysalon, yprofesor, yDisponibilidad);
}

void aClase::ModificarDatoDeClase() {
    string pNombre;
    int auxiliar;
    cout << "Ingrese el nombre de la materia: " << endl;
    cin >> pNombre;
    cout << "Ingrese el número del dato que se desea cambiar" << endl;
    cout << "1. nombre";
    cout << "2. Salon";
    cout << "3. Profesor" << endl;
    cin >> auxiliar;
    switch (auxiliar) {
    case 1: aux.modify(ECampos::nombre, pNombre); break;
    case 2: aux.modify(ECampos::salon, pNombre); break;
    case 3: aux.modify(ECampos::profesor, pNombre); break;
    }
}

void aClase::EliminarClase() {
    string name;
    cout << "Ingrese el nombre de la clase a eliminar: " << endl;
    cin >> name;
    aux.del(name);
}

void aClase::mostrarClases() {
    aux.repr(ECampos::nombre);
}

int main() {
    aClase sob = aClase();
    int opci;

    do {

        cout << "Ingrese el número de lo que desea hacer: " << endl;
        cout << "1. Agregar una clase" << endl;
        cout << "2. Modificar una clase" << endl;
        cout << "3. Eliminar una clase" << endl;
        cout << "4. Mostrar Clases " << endl;
        cin >> opci;
        switch (opci) {
        case 1: sob.addClase(); break;
        case 2: sob.ModificarDatoDeClase(); break;
        case 3: sob.EliminarClase(); break;
        case 4: sob.mostrarClases(); break;


        }
    } while (opci != 5);

}


