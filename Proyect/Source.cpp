#include "User.h"

void LogIn()
{
    string u,p;
    bool login;

    cout << left << setw(20) << "Bienvenido" << endl;
    cout << "Username:" << setw(10) << endl;
    cin >> u; 
    cout << "Password:" << setw(10) << endl;
    cin >> p; 


    ifstream file{"users.dat", ios::in};

    User verify;

    for(int i = 0; i < MAX_USERS; i++)
    {
        file.read((char*)&verify,sizeof(User));
        if(u == verify.getUser() && p == verify.getPassword())
        {
            cout << "W" << endl;
            break;
        }
        else
        {
            cout << "F" << endl;

        }
    }

}