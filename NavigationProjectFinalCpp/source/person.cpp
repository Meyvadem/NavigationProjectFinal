#include "../header/person.hpp"
#include <iostream>
#include <fstream>
#include <vector>



vector<Person> Person::persons;
vector<User> User::users;
vector<Admin> Admin::admins;

Person::Person() : name(""), surname(""), username(""), password("") {}
Person::Person(const string &name, const string &surname, const string &username, const string &password)
    : name(name), surname(surname), username(username), password(password) {}

Admin::Admin() : Person() {}
Admin::Admin(const string &name, const string &surname, const string &username, const string &password)
    : Person(name, surname, username, password) {}

User::User() : Person(), age(0) {}
User::User(const string &name, const string &surname, const string &username, const string &password, const int &age)
    : Person(name, surname, username, password), age(age) {}

// Getter functions

string Person::getName() const
{
    return name;
}

string Person::getsurName() const
{
    return surname;
}

string Person::getUsername() const
{
    return username;
}

string Person::getPassword() const
{
    return password;
}

// Setter fonksiyonları

void Person::setName(const string &newName)
{
    name = newName;
}

void Person::setsurName(const string &newsurName)
{
    surname = newsurName;
}

void Person::setUsername(const string &newUsername)
{
    username = newUsername;
}

void Person::setPassword(const string &newPassword)
{
    password = newPassword;
}

void User::setAge(const int &newAge)
{
    age = newAge;
}

int User::getAge() const
{
    return age;
}

void Person::addPerson(const Person &person)
{
    Person::persons.push_back(person);
}

void User::addUser(const User &user)
{
    User::users.push_back(user);
}

void Admin::addAdmin(const Admin &admin)
{
    Admin::admins.push_back(admin);
}

void printAllDetails(const std::vector<User> &users)
{
    int numb = 1;
    std::cout << "User details\n\n";
    for (const User &user : users)
    {
        std::cout << numb++ << ".  Name: " << user.getName() << ", Surname: " << user.getsurName() << ", Username: " << user.getUsername() << ", Password: " << user.getPassword() << ", Age: " << user.getAge() << std::endl;
    }
}
bool Person::login(const vector<Person> &persons) const
{
    string enteredUsername;
    string enteredPassword;

    cout << "Enter username: ";
    cin >> enteredUsername;

    cout << "Enter password: ";
    cin >> enteredPassword;

    for (const auto &person : persons)
    {
        if (enteredUsername == person.getUsername() && enteredPassword == person.getPassword())
        {
            cout << "\nHosgeldin " << person.getName() << endl;
            cout << "\nLogging in...\n\n";
            return true;
        }
    }

    cout << "Person girisi basarisiz!" << endl;
    return false;
}

bool User::login(const vector<Person> &persons) const
{
    string enteredUsername;
    string enteredPassword;

    while (true)
    {
        cout << "Enter username: ";
        cin >> enteredUsername;

        cout << "Enter password: ";
        cin >> enteredPassword;

        for (const auto &person : persons)
        {
            if (enteredUsername == person.getUsername() && enteredPassword == person.getPassword())
            {
                cout << "\nHosgeldin " << person.getName() << endl;
                cout << "\nLogging in...\n\n";
                return true;
            }
        }

        cout << "User girisi basarisiz!" << endl;
    }
}

bool Admin::login(const vector<Person> &persons) const
{
    string enteredUsername;
    string enteredPassword;

    while (true)
    {
        cout << "Enter username: ";
        cin >> enteredUsername;

        cout << "Enter password: ";
        cin >> enteredPassword;

        for (const auto &person : persons)
        {
            if (enteredUsername == person.getUsername() && enteredPassword == person.getPassword())
            {
                cout << "\nHosgeldin " << person.getName() << endl;
                cout << "\nLogging in...\n\n";
                return true;
            }
        }

        cout << "Admin girişi başarisiz!" << endl;
    }
}

void writePeopleToFile(const char* filename, const std::vector<Person>& persons) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Dosya açma hatası" << std::endl;
        return;
    }

    for (const auto& person : persons) {
        file << "Name: " << person.getName() << "   " << " Surname: "<< person.getsurName() << "   " << " Username: "<< person.getUsername() << "   " << " Password: "<< person.getPassword();
        file << "\n";
    }
        
    

    file.close();
}


