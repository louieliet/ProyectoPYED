#include "User.h"

void LogIn(vector<User> list)
{
    string u,p;
    bool login;
    bool flag = false;
    cout << left << setw(20) << "Bienvenido" << endl;
    cout << "Username:" << setw(10) << endl;
    cin >> u; 
    cout << "Password:" << setw(10) << endl;
    cin >> p; 


    ifstream file{"users.dat", ios::in};

    for(auto i : list)
    {
        User verify;
        file.seekg( (i.getIdx() - 1 ) * sizeof(User) );
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