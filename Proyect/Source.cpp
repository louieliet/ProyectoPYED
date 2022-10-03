#include "User.h"
#include "Teacher.h"

void LogIn()
{
    string u,p;
    bool login;
    bool flag = false;

    system("cls");

    cout << left << setw(20) << "Bienvenido" << endl;
    cout << "Username:" << setw(10) << endl;
    cin >> u; 
    cout << "Password:" << setw(10) << endl;
    cin >> p; 


    ifstream file{"users.dat", ios::in};
    ifstream file2{"Teachers.dat", ios::in};

    if(!file){cerr << "File could not be opened :s" << endl; exit(EXIT_FAILURE);}

    for(int i = 0; i < MAX_USERS; i++)
    {

        User verify;
        file.seekg( i * sizeof(User) );
        file.read(reinterpret_cast<char*>(&verify),sizeof(User));

        if(u == verify.getUser())
        {
            flag = true;

            if(p == verify.getPassword())
            {
                Teacher name;
                for(int i = 0; i < MAX_USERS; i++)
                {
                    file2.seekg( i * sizeof(Teacher) );
                    file2.read(reinterpret_cast<char*>(&name),sizeof(Teacher));
                    if( verify.getUser() == name.getUser() ){
                        cout << "Welcome, " << name.getTeacherName() << endl;
                        file.close();
                        file2.close();
                        break;
                    }
                }
            }
            else
            {
                cout << "Incorrect password" << endl;
                break;
                file.close();
                file2.close();
            }
        }
    }
    if(flag == false){
        cout << "User not founded" << endl;
        file.close();
        file2.close();
    }

}


typedef struct NodeStruct* Node;

struct NodeStruct{
    string valor;
    struct NodeStruct* left;
    struct NodeStruct* right;
};

void InsertTeachers(Node &raiz){

    ifstream file{"Teachers.dat", ios::in};

    for(int i = 0; i < MAX_USERS; i++){ 

        Teacher lTemp;
        file.seekg( i * sizeof(User) );
        file.read(reinterpret_cast<char*>(&lTemp),sizeof(Teacher));

        if(raiz == NULL){
            Node newnode = new (struct NodeStruct);
            newnode->valor = lTemp.getTeacherName();
            newnode->left = NULL;
            newnode->right = NULL;
            raiz = newnode;
        }
        else{
            if(lTemp.getTeacherName() < raiz->valor){
                InsertTeachers(raiz->left);
            }
            else if(lTemp.getTeacherName() > raiz->valor){
                InsertTeachers(raiz->right);
            }
        }
    }
}

void Preorden(Node raiz){
    if(raiz != NULL){
        cout << raiz->valor << ", ";
        Preorden(raiz->left);
        Preorden(raiz->right);
    }
}

