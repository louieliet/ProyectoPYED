
#include "Source.cpp"

int main()
{
    vector<User> list;
    User u1("0241718","password");
    User u2("12345678","password");
    list.push_back(u1);
    list.push_back(u2);


    MakeEmptyUsersFile();
    MakeUsersFile(list);

    cout << u1.getIdx();
    cout << u2.getIdx();

    LogIn();
}