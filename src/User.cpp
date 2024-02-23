#include <iostream>
#include <list>
using namespace std;

struct contact{
    string name;
    string email;
    long long phoneNum;
}

class User {       
  public:           
    string name;
    list<contact> contacts;

    User(string n) {
        name = n;
        contacts = {};
    }  

    addContact(string n,string e, long long p) {
        contact c;
        c.name = n;
        c.email = e;
        c.phoneNum = p;
        contacts.push_back(c);
    }
};