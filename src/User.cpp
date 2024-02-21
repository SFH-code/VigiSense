#include <iostream>
#include <list>
using namespace std;

class User {       
  public:           
    string name;
    list<string> contacts;

    User(string n) {
        name = n;
        contacts = {};
    }  

    addContact(string c) {
        contacts.push_back(c);
    }
};