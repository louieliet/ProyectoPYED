#include "Header.h"

class Teacher{
public:
	Teacher(const int& Idx = 9999999, const string& Teachername = "NULL", const string& username = "NULL") {

		this->Idx = Idx;
        setUsername(username);
		setTeachername(Teachername);
	}

    void setUsername(const string& username) {

		size_t length{ username.size() };
		length = (length < MAX_USERNAME ? length : MAX_USERNAME - 1);
		username.copy(this->username, length);
		this->username[length] = '\0'; 

	}

	void setTeachername(const string& Teachername) {

		size_t length{ Teachername.size() };
		length = (length < MAX_NAME ? length : MAX_NAME - 1);
		Teachername.copy(this->Teachername, length);
		this->Teachername[length] = '\0'; 

	}

    char* setClasecode(const string& code)
    {
        char* codigo;


        return codigo;
    }
    
    void setClases()
    {
        for(int i = 0; i < MAX_MATERIAS; i++)
        {
            char codigo[3];
            string code;
            cout << "Ingrese el código de la clase #" << i << endl;
            cin >> code;
            if(code.size() < MAX_MATERIA_CODE){
                while(code.size() < MAX_MATERIA_CODE){
                    cout << "Ingrese un codigo menor a: " << MAX_MATERIA_CODE << " digitos" << endl;
                    cin >> code;
                }
            }
            size_t lenght{code.size()};
            lenght = (lenght < MAX_MATERIA_CODE ? lenght : MAX_MATERIA_CODE - 1);
            code.copy(codigo,lenght);
            codigo[lenght] = '\0'; 
            Clases[i] = codigo;
            
        }
    }
	
	
	int getIdx() const {return Idx;}
    string getUser() const {return username;}
	string getTeacherName() const {return Teachername;}
    void getClases() const {
        for(int i = 0; i < MAX_MATERIAS; i++){
            cout << Clases[i];
        }
    }

private:
	int Idx;
    char username[MAX_USERNAME];
	char Teachername[MAX_NAME];
    string Clases[MAX_MATERIAS];
};


int MakeEmptyTeachersFile(){

    ofstream file{ "Teachers.dat", ios::out | ios::binary };

    if (!file) {
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }
    Teacher out;

    for(int i=0; i<MAX_USERS; ++i){
        file.write(reinterpret_cast<const char*>(&out), sizeof(Teacher));
    }

    return 0;
}


int MakeTeachersFile(vector<Teacher> list){

    fstream outFile{"Teachers.dat", ios::in | ios::out | ios::binary};

    if(!outFile){
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    for( auto i : list ){
        outFile.seekp( (i.getIdx() - 1) * sizeof(Teacher) );
        outFile.write( reinterpret_cast<const char*>(&i), sizeof(Teacher) );
    }
    
    return 0;
}
