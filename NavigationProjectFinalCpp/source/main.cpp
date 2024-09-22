#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>
#include <fstream>

#include "map.cpp"
#include "location.cpp"
#include "person.cpp"
#include "pathfinder.cpp"

using namespace std;

void startTravel(Location locations[]);
void showAdminOptions();
void showUserOptions();

int main()
{

    User user("Merve", "Smith", "m", "ms", 21);
    User user1("Kerem", "Smith", "k", "ks", 21);
    User user2("Alperen", "Smith", "a", "as", 21);
    User user3("Kubra", "Smith", "kub", "kubs", 25);
    User user4("Yavuz", "Smith", "y", "ys", 28);
    Admin admin("Bob", "Johnson", "b", "bj");
    Admin admin1("Feride", "Demir", "f", "fd");
    Admin admin2("Apo", "Demir", "a", "ad");

    Person::addPerson(user);
    Person::addPerson(user1);
    Person::addPerson(user2);
    Person::addPerson(user3);
    Person::addPerson(user4);
    Person::addPerson(admin);
    Person::addPerson(admin1);
    Person::addPerson(admin2);

    User::addUser(user);
    User::addUser(user1);
    User::addUser(user2);
    User::addUser(user3);
    User::addUser(user4);

    Admin::addAdmin(admin);
    Admin::addAdmin(admin1);
    Admin::addAdmin(admin2);

    // Dosyaya yazma testi
    writePeopleToFile("persons.txt", Person::persons);

    Location locations[9] = {
        {{10, 12}, {12, 9}, "Home1", LocationType::PRIVATE_PROPERTY},
        {{6, 30}, {32, 6}, "Bim", LocationType::LOCAL_SHOP},
        {{6, 60}, {62, 6}, "Home2", LocationType::PRIVATE_PROPERTY},
        {{16, 24}, {22, 16}, "Cinema", LocationType::ENTERTAINMENT_PLACE},
        {{20, 42}, {42, 19}, "Hospital", LocationType::CORPORATE_BUILDING},
        {{16, 60}, {62, 16}, "Home3", LocationType::PRIVATE_PROPERTY},
        {{26, 24}, {22, 26}, "Hakmar", LocationType::LOCAL_SHOP},
        {{26, 54}, {52, 26}, "Shopping Mall", LocationType::SHOPPING_CENTER},
        {{26, 60}, {62, 26}, "Police", LocationType::CORPORATE_BUILDING},
    };

    while (true)
    {
        int option;

        cout << "\n--------- WELCOME TO NAVIGATION SYSTEM ---------\n";

        cout << "1- Admin Login\n";
        cout << "2- User Login\n";
        cout << "3- Exit\n";

        cout << "\nSelect an option: ";
        cin >> option;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        if (option == 1)
        {
            //--------------------------------------------------------------------------------------------

            cout << "\nADMIN LOGIN\n";
            cout << "------------\n";
            admin.login(Person::persons);
            Sleep(3000);
            std::system("cls");
            while (true)
            {
                int choice;

                showAdminOptions();

                cout << "\nSelect an option : ";
                cin >> choice;

                if (choice == 1)
                {
                    std::system("cls");
                    printLocations(locations);
                }
                else if (choice == 2)
                {
                    std::system("cls");
                    printAllDetails(User::users);
                }

                else if (choice == 3)
                {
                    break;
                }
                else
                {
                    printf("\nInvalid option. Please select [1-4]\n");
                    while (getchar() != '\n')
                        ;
                }
            }
        }
        else if (option == 2)
        {

            cout << "\nUSER LOGIN\n";
            cout << "------------\n";
            bool isvalid = user.login(Person::persons);
            Sleep(3000);
            std::system("cls");

            int choice1;
            if (isvalid)
            {
                showUserOptions();
            }

            cout << "\nSelect an option : ";
            cin >> choice1;

            if (choice1 == 1)
            {
                startTravel(locations);
            }

            else if (choice1 == 2)
            {
                break;
            }
            else
            {

                printf("\nInvalid option. Please select [1-2]\n");
                while (getchar() != '\n')
                    ;
            }
        }
        else if (option == 3)
        {
            cout << "\n------------ Goodbye! ------------\n";
            return 0;
        }
        else
        {
            cout << "Invalid option. Please select 1, 2, or 3.\n";
        }
    }

    gotoxy(1, 40);

    return 0;
}

void startTravel(Location locations[])
{

    int loop = 1; // Döngüyü kontrol etmek için değişken
    while (loop)
    {
        std::system("cls");
        std::cout << "WELCOME TO NAVIGATION SYSTEM" << std::endl;
        Location currentLocation = getLocationChoice(locations);

        std::system("cls");
        std::cout << "WELCOME TO NAVIGATION SYSTEM" << std::endl;
        Location destination = getDestinationChoice(locations);

        std::system("cls");
        gotoxy(100, 2);
        std::cout << "Current Location: " << currentLocation.getName() << std::endl;
        gotoxy(100, 4);
        std::cout << "Destination: " << destination.getName() << std::endl;

        printMap();

        showLocation(currentLocation);
        showDestination(destination);

        gotoxy(100, 8);
        std::cout << "Do you want to start traveling?" << std::endl;
        gotoxy(100, 10);
        std::cout << "To start press 1: ";
        int start;
        std::cin >> start;

        if (start == 1)
        {
            runAStarExample(currentLocation, destination);
        }

        // Kullanıcıdan devam etmek isteyip istemediğini sormak için döngü
        gotoxy(100, 10);
        printf("Press 'p' to stop, any other key to continue...\n");
        char choice = getch(); // Kullanıcının tuşa basmasını bekleyin
        if (choice == 'p' || choice == 'P')
        {
            std::system("cls");
            break;
        }
    }
}

void showAdminOptions()
{
    cout << "\nADMIN SYSTEM\n";
    cout << "------------\n";
    cout << "\n1- Show All Locations" << endl;
    cout << "2- Show All Users" << endl;
    cout << "3- Logout" << endl;
}

void showUserOptions()
{
    cout << "\nUSER SYSTEM\n";
    cout << "------------\n";
    cout << "\n1- Start Travel" << endl;
    cout << "2- Logout" << endl;
}