
#include "Source.cpp"

int main()
{
    Teacher t1(1,"Z","0241718");
    Teacher t2(1,"Abril","0241718");
    Teacher t3(1,"Emi","0241718");

    Node teacherstree = NULL;

    vector<Teacher> list;
    list.push_back(t1);
    list.push_back(t2);
    list.push_back(t3);

    MakeEmptyTeachersFile();
    MakeTeachersFile(list);

    InsertTeachers(teacherstree);
    Preorden(teacherstree);
    
}