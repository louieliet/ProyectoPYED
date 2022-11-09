#include "Listas.h"
#include "Profesors.h"


using namespace std;

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
        

    } while (opci != 0);
    
}