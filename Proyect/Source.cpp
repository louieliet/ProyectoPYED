#include "User.h"

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
                cout << "Welcome" << endl;
                break;
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