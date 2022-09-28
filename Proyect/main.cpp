
#include "Source.cpp"

int main()
{
    vector<User> list;
    vector<Teacher> list2;
    User u1(1, "0241718","password");
    list.push_back(u1);
    Teacher t1(1, "EmilianoMontes", u1.getUser());
    list2.push_back(t1);


    MakeEmptyUsersFile();
    MakeUsersFile(list);

    MakeEmptyTeachersFile();
    MakeTeachersFile(list2);

    LogIn();
}