// db.h
#include <string>
#include <cstdlib>  // For malloc and free
#include <iostream> // For std::cout
#include <stdexcept> // For std::bad_alloc

class Database {
    private:
        std::string db;
        std::string username;
        std::string password;
        bool connected = false;
        static Database* instance;

    // constructor that helps creating instance of db(e.g. sales.db) accepts name of the database, username, password.
    // ToDo
        Database(const std::string& dataBase, const std::string& user, const std::string& pass);

    public:
        //destructor 
        ~Database();
        //get pointer to database
        static Database* getInstance(const std::string& dataBase, const std::string& user, const std::string& pass);

        //setting status for connect
        void connect();
        void disconnect();
        //returning status
        bool isConnected();

        //new operator overload
        void * operator new(size_t ptr_size){
            void* ptr = std::malloc(ptr_size);
            if(!ptr){
                throw std::bad_alloc();
            }
            std::cout << "overloaded new ";
            return ptr;
        }
        //delete operator overload
        void operator delete(void *p){
            std::free(p);
            std::cout << "overloaded delete ";
        }

        //setting and getting password
        void set_username(std::string user);
        std::string get_username();

        //setting and getting password
        void set_password(std::string pass);
        std::string get_password();

        // The static "resetInstance" as defined below.
        static void resetInstance();
};
