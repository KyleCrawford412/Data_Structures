#include "passsever.h"

using namespace std;

//create server of specified size
PassServer::PassServer(size_t size): server(size){
	
}

//delete server
PassServer::~PassServer(){
    server.clear();
}

//load file into server
bool PassServer::load(const char *filename){
    return server.load(filename);
}

//add a user to server
bool PassServer::addUser(pair<string, string>& kv){
	//get encryption
    string ecryption = encrypt(kv.second);

	//make pair
    pair<string, string> newUser(kv.first, ecryptedValue);   
	
	//return insertion of new user
    return server.insert(newUser);                     
}

//add user
bool PassServer::addUser(pair<string, string>&& kv){
	//get encryption
    string ecryption = encrypt(kv.second);
	
	//make pair
    pair<string, string> newUser(move(kv.first), move(ecryptedValue));
	
	//return insertion of new user
    return server.insert(newUser);
}

//remove user
bool PassServer::removeUser(const string& k){
    server.remove(k);
}

//change password
bool PassServer::changePassword(const pair<string, string> &p, const string& newpassword){
    
	//Check for user entering the same password
    if((server.contains(p.first)) && (newpassword != p.second)){
        //get encryption
        string tempPass = encrypt(p.second);

        //check that user exists
        pair<string, string> tempUser(p.first, tempPass);
        if(server.match(tempUser)){
            //encrypt the new password
            string newPass = encrypt(newpassword);
			
            //create updated user
            pair<string, string> updatedUser(p.first, newPass);
			
			//insert the new user
            server.insert(updatedUser);
            return true;
        }
		//user doesnt exist
        else{ 
			return false;      
		}
    }
	//tried to change password to same data
    else{ 
		return false;
	}
}

//check if user exists
bool PassServer::find(const string& user){
    return server.contains(user);
}

//show structure and contents of server
void PassServer::dump(){
    server.dump();
}

//return size of server
size_t PassServer::size(){
    return server.size();
}

//write server data to a file
bool PassServer::write_to_file(const char *filename){
    server.write_to_file(filename);
}

//encryption function
string PassServer::encrypt(const string & str){
	//given salt
    char salt[] = "$1$########";                            
    string newEncryption = crypt(str.c_str(), salt);
    newEncryption.replace(0, 12, "");
    return newEncryption;
}