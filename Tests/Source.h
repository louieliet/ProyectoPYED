
#include "Header.h"


int MakeEmptyUsersFile(){

    ofstream file{ "users.dat", ios::out | ios::binary };

    if (!file) {
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }
    User out;

    for(int i=0; i<5; ++i){
        file.write(reinterpret_cast<const char*>(&out), sizeof(User));
    }

    return 0;
}


int MakeUsersFile(vector<User> list){

    fstream outFile{"users.dat", ios::in | ios::out | ios::binary};

    if(!outFile){
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    for( auto i : list ){
        outFile.seekp( (i.getIdx() - 1) * sizeof(User) );
        outFile.write( reinterpret_cast<const char*>(&i), sizeof(User) );
    }
    
    return 0;
}



int MakeEmptyStudentsFile(){

    ofstream file{ "students.dat", ios::out | ios::binary };

    if (!file) {
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }
    Estudiante out;

    for(int i=0; i<5; ++i){
        file.write(reinterpret_cast<const char*>(&out), sizeof(Estudiante));
    }

    return 0;
}


int MakeStudentsFile(vector<Estudiante> list){

    fstream outFile{"students.dat", ios::in | ios::out | ios::binary};

    if(!outFile){
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    for( auto i : list ){
        outFile.seekp( (i.getIdx() - 1) * sizeof(Estudiante) );
        outFile.write( reinterpret_cast<const char*>(&i), sizeof(Estudiante) );
    }
    
    return 0;
}

void outputLine(ostream& output, const Estudiante& record) {
    
    output << left <<setw(20) << "ID";
    output << left <<setw(20) << "Estudiante"
    << endl;
	
    output << left << setw(20) << record.getName()
        << setw(20) << record.getID();
}

int Search(vector<Estudiante> list)
{
    ifstream file{"students.dat", ios::in};

    if(!file){
        cerr << "No se pudo abrir el archivo" << endl;
        exit(EXIT_FAILURE);
    }

    string op;
    int flag;

    cout << "Deme el ID" << endl;
    cin >> op;

    flag = 0;

    for( auto i : list)
    {
        if(i.getID()==op)
        {
            file.seekg((i.getIdx() - 1) * sizeof(Estudiante));
            file.read(reinterpret_cast<char*>(&i),sizeof(Estudiante));
            outputLine(cout,i);
            flag = 1;
        }

    }
    if(flag == 0){
        cout << "Error, no se encontro el estudiante. " << endl;
    }
}






















