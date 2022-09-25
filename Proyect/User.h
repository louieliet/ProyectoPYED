#include "Header.h"

class User{
public:
	User(const int& Idx = 9999999, const string& username = "NULL", const string& password = "NULL") {

		this->Idx = Idx;
		setUsername(username);
		setPassword(password);
	}

	void setUsername(const string& username) {

		size_t length{ username.size() };
		length = (length < MAX_USERNAME ? length : MAX_USERNAME - 1);
		username.copy(this->username, length);
		this->username[length] = '\0'; 

	}
	
	void setPassword(const string& password) {

		size_t length{ password.size() };
		length = (length < MAX_PASSWORD ? length : MAX_PASSWORD - 1);
		password.copy(this->password, length);
		this->password[length] = '\0'; 

	}
	
	int getIdx() const {return Idx;}
	string getUser() const {return username;}
	string getPassword() const {return password;}

private:
	int Idx;
	char username[MAX_USERNAME];
	char password[MAX_PASSWORD];
};


int MakeEmptyUsersFile(){

    ofstream file{ "users.dat", ios::out | ios::binary };

    if (!file) {
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }
    User out;

    for(int i=0; i<MAX_USERS; ++i){
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
