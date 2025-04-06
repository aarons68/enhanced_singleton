 //db.cpp
#include "db.h"
Database* Database::instance = nullptr;

//constructor
Database::Database(const std::string& dataBase, const std::string& user, const std::string& pass):
        db(dataBase), username(user), password(pass){refreshConnection();}

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
    refreshConnection();
    connected = true;
}
void Database::disconnect(){
    connected = false;
}

//returning status
bool Database::isConnected(){
    if (connected && isTimeout()) {
        disconnect();
    }
    return connected;
}

//setting and getting password
void Database::set_username(const std::string& user){
    refreshConnection();
    username = user;
}
std::string Database::get_username(){
    refreshConnection();
    return username;
}

//setting and getting password
void Database::set_password(const std::string& pass){
    refreshConnection();
    password = pass;
}
std::string Database::get_password(){
    refreshConnection();
    return password;
}

void Database::resetInstance() {
   if (instance != nullptr) {
     delete instance;
     instance = nullptr;
   }
 }


//copy constructor
Database::Database(const Database& other) {
    throw std::runtime_error("copy constructor error");
}

//copy assignment
Database& Database::operator=(const Database& other) {
    throw std::runtime_error("copy assignment error");
}

//move constructor
Database::Database(Database&& other) {
    throw std::runtime_error("move constructor error");
}

//move assignment
Database& Database::operator=(Database&& other) {
    throw std::runtime_error("move assignment error");
}

bool Database::isTimeout() {
    time_t curr_t = std::time(nullptr);
    return difftime(curr_t, last_activity) > TIMEOUT;
}

void Database::refreshConnection() {
    last_activity = std::time(nullptr);
}