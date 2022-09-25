
#include "Source.cpp"

int main()
{
    vector<User> list;
    User u1(1, "0241718","password");
    list.push_back(u1);
    User u2(2, "0241719","password");
    list.push_back(u2);

    MakeEmptyUsersFile();
    MakeUsersFile(list);

    LogIn(list);
}