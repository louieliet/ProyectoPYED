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
                        break;
                    }
                }
            }
            else
            {
                cout << "Incorrect password" << endl;
                break;
            }
        }
    }
    if(flag == false){
        cout << "User not founded" << endl;
    }

}
