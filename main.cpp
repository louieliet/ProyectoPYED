#include "Source.h"

using namespace std;


int main()
{
    
    User u1("0241718","password");
    Estudiante s1(u1.getIdx(),u1.getID(),"Emiliano");

    vector<User> Users;
    vector<Estudiante> Students;

    Users.push_back(u1);
    Students.push_back(s1);

    MakeEmptyUsersFile();
    MakeUsersFile(Users);

    MakeEmptyStudentsFile();
    MakeStudentsFile(Students);


    Search(Students);


}