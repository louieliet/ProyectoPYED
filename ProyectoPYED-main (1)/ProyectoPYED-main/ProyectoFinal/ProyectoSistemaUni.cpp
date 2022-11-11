#include "Listas.h"
#include "Profesors.h"
#include "WebServer.h"
#include "Eval.h"

using namespace std;


#define KS_Path "C://Temp/wroot/"

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

aClase sob = aClase();

string showAlumnos(string pCaller) {

    string lRes = fnGetTemplate("lalumno.html");
    string lHTML = "";
    PDNODO2 lData = NULL;
    int lRow = 0;
    string lColor = "";
    while (lData = sob.alumn.get()) {
        lColor = "";
        if (lRow % 2 == 0)
            lColor = "background-color:#E0E0E0;";
        lHTML += "<tr " + lColor + "'>\n";
        lHTML += "<td>\n" + lData->sIDP + "</td>";
        lHTML += "<td>\n" + lData->sNombre + "</td>";
        lHTML += "<td>\n" + lData->sCorreo + "</td>";
        lHTML += "</tr>";
        lRow++;
    }

    strReplace(lRes, "{{pData}}", lHTML);

    return lRes;

}

string showProfesores(string pCaller) {

    string lRes = fnGetTemplate("lprofesor.html");
    string lHTML = "";
    PDNODO lData = NULL;
    int lRow = 0;
    string lColor = "";
    while (lData = sob.prof.get()) {
        lColor = "";
        if (lRow % 2 == 0)
            lColor = "background-color:#E0E0E0;";
        lHTML += "<tr " + lColor + "'>\n";
        lHTML += "<td>\n" + lData->sIDP + "</td>";
        lHTML += "<td>\n" + lData->sNombre + "</td>";
        lHTML += "<td>\n" + lData->sCorreo + "</td>";
        lHTML += "</tr>";
        lRow++;
    }

    strReplace(lRes, "{{pData}}", lHTML);

    return lRes;

}


int main() {

    MyHTTPSrv lSrv = MyHTTPSrv(NULL, NULL);
    //lSrv.SetGetFunc(&fnGetFuncS);
    //lSrv.Run();


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

            string contra = sob.admi.findContra(uss);
            cout << contra << endl;
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
                    cout << endl << endl << "CONFIGURACIÓN DE PROFESORES" << endl;
                    cout << "5. Agregar Profesor" << endl;
                    cout << "6. Mostrar profesores" << endl;
                    cout << endl << endl << "CONFIGURACIÓN DE ALUMNOS" << endl;
                    cout << "7. Agregar Alumno" << endl;
                    cout << "8. Mostrar Alumnos" << endl;
                    cout << endl << endl << "CONFIGURACIÓN DE ADMINISTRADORES" << endl;
                    cout << "9. Agregar Administrador" << endl;
                    cout << "10. Mostrar Administradores" << endl;
                    cout << endl << endl << "CONFIGURACIÓN DE MATERIAS E INSCRIPCIONES" << endl;
                    cout << "11. Ver Inscripciones" << endl;
                    cin >> subs;
                    cin.ignore();
                    switch(subs){
                        case 1: sob.addClase(); break;
                        case 2: sob.ModificarDatoDeClase(); break;
                        case 3: sob.EliminarClase(); break;
                        case 4: sob.mostrarClases(); break;


                        case 5: sob.prof.InsertarProfe(); break;
                        case 6: lSrv.SetGetFunc(&showProfesores); lSrv.Run(); break;

                        case 7:sob.alumn.InsertarAlumno(); break;
                        case 8:lSrv.SetGetFunc(&showAlumnos); lSrv.Run(); break;

                        case 9:sob.admi.InsertarAdmin(); break;
                        case 10:sob.admi.repr(); break;


                        case 11:sob.classes.repr(); break;
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
                    cout << "4. Modificar calificación" << endl;
                    cin >> subs;
                    cin.ignore();
                    switch(subs){
                        case 1: sob.addClase(uss); break;
                        case 2: sob.ModificarDatoDeClase(); break;
                        case 3: sob.EliminarClase(); break;
                        case 4: sob.ModiCalif(); break;
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
                    cout << "2. Eliminar inscripción a materia" << endl;
                    cin >> subs;
                    cin.ignore();
                    switch(subs){
                        case 1:sob.MeterMateria(uss); break;
                        case 2:sob.EliminarInsc(uss); break;
                    }
                    system("pause");
                }while(subs!=0);
            }
        }

    } while (opci != 0);
    
}