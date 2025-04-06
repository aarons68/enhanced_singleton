 //db.cpp
#include "db.h"
Database* Database::instance = nullptr;

//constructor
Database::Database(const std::string& dataBase, const std::string& user, const std::string& pass):
        db(dataBase), username(user), password(pass){}

Database::~Database(){
    if(isConnected()){
        disconnect();
    }
}
//get pointer to database
Database* Database::getInstance(const std::string& dataBase, const std::string& user, const std::string& pass){
    if(instance == nullptr){
        instance = new Database(dataBase, user, pass);
    }
    else{
        if(instance->db != dataBase || instance->password != pass || instance->username != user){
            throw std::runtime_error("invalid database name, username or password");
        }
    }
    return instance;
}

//setting status for connect
void Database::connect(){
    connected = true;
}
void Database::disconnect(){
    connected = false;
}
//returning status
bool Database::isConnected(){
    return connected;
}

//setting and getting password
void Database::set_username(std::string user){
    username = user;
}
std::string Database::get_username(){
    return username;
}

//setting and getting password
void Database::set_password(std::string pass){
    password = pass;
}
std::string Database::get_password(){
    return password;
}


void Database::resetInstance() {
   if (instance != nullptr) {
     delete instance;
     instance = nullptr;
   }
 }
