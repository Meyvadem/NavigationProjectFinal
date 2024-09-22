#ifndef USER_HPP
#define USER_HPP

using namespace std;
#include <string>
#include <iostream>
#include <vector>


class Person
{
protected:
    string name;
    string surname;
    string username;
    string password;

    

public:
    Person();
    Person(const string &name, const string &surname, const string &username, const string &password);

    string getName() const;
    string getsurName() const;
    string getUsername() const;
    string getPassword() const;

    void setName(const string &newName);
    void setsurName(const string &newsurName);
    void setUsername(const string &newUsername);
    void setPassword(const string &newPassword);

    static vector<Person> persons; // Statik vektör

    virtual bool login(const vector<Person> &persons) const; // Virtual login fonksiyonu
    static void addPerson(const Person &person);
    

    
};

class User : public Person
{
private:
    int age;

public:
    User();
    User(const string &name, const string &surname, const string &username, const string &password, const int &age);

    int getAge() const;
    void setAge(const int &newAge);

    static vector<User> users;
    static void addUser(const User &user);

    void printAllDetails(const std::vector<User> &users);
    bool login(const vector<Person> &persons) const override; // Override edilmiş login fonksiyonu
    
};

class Admin : public Person
{
public:
    Admin();
    Admin(const string &name, const string &surname, const string &username, const string &password);

    static vector<Admin> admins;
    static void addAdmin(const Admin &admin);
   
    bool login(const vector<Person> &persons) const override; // Override edilmiş login fonksiyonu
};

void writePeopleToFile(const char* filename, const std::vector<Person>& persons);

#endif
