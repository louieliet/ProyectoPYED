#include <iostream>
#include <fstream>  
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <wchar.h>
#include <locale.h>

using namespace std;


class User {
public:
	User(const string& id = "NULL", const string& password = "NULL") {

		setIdx(Idx);
		setID(id);
		setPassword(password);
	}

	void setIdx(const int& idx)
	{	
		srand((int)time(0));
		this->Idx = (rand() % 5) ;
	}

	void setID(const string& id) {

		size_t length{ id.size() };
		length = (length < 8 ? length : 7);
		id.copy(this->id, length);
		this->id[length] = '\0'; 

	}
	
	void setPassword(const string& password) {

		size_t length{ password.size() };
		length = (length < 20 ? length : 19);
		password.copy(this->password, length);
		this->password[length] = '\0'; 

	}
	
	int getIdx() const {return Idx;}
	string getID() const {return id;}
	string getPassword() const {return password;}

private:
	int Idx;
	char id[8];
	char password[20];
};




class Estudiante {
public:
	Estudiante(int Idx = 999, const string& ID = "NULL", const string& name = "NULL") {
		this->Idx = Idx;
		setID(ID);
		setName(name);
	}

	void setID(const string& ID) {

		size_t length{ ID.size() };
		length = (length < 8 ? length : 7);
		ID.copy(this->ID, length);
		this->ID[length] = '\0'; 

	}
	
	void setName(const string& name) {

		size_t length{ name.size() };
		length = (length < 20 ? length : 19);
		name.copy(this->name, length);
		this->name[length] = '\0'; 

	}
	
	int getIdx() const {return Idx;}
	string getID() const {return ID;}
	string getName() const {return name;}

private:
	int Idx;
	char ID[8];
	char name[20];
};