#include "tabulate/single_include/tabulate/tabulate.hpp"
#include "./memtrace.h"
#include "menu.h"
#include "contacts.h"

int main()
{
    using namespace tabulate;

    String fileName = "telefonkonyv.csv";
    Contacts c;

    Menu mainMenu;
    Menu list;
    Menu create;
    Menu update;
    Menu del;
    Menu search;
    Menu export_file;
    Menu import_file;

    mainMenu.Create([&]() {
        if (Contacts::fileExists(fileName)) c.loadFile(fileName);
        while (true) {
            Menu::Clear();
            std::cout
            << "\033[47;30mPhonebook\033[0m\n\n"
            << "1) List\n"
            << "2) Create\n"
            << "3) Update\n"
            << "4) Delete\n"
            << "5) Search\n"
            << "6) Export File\n"
            << "7) Import File\n"
            << "8) Exit\n\n"
            << "Option: ";
            int option = 0;
            String tmp;
            std::cin >> tmp;
            try {
                option = std::stoi(tmp.c_str());
            } catch (...) {}
            switch (option) {
                case 1: {
                    int status = list.Render();
                    if (status == 1) return 1;
                    break;
                }
                case 2: {
                    int status = create.Render();
                    if (status == 1) return 1;
                    break;
                }
                case 3: {
                    int status = update.Render();
                    if (status == 1) return 1;
                    break;
                }
                case 4: {
                    int status = del.Render();
                    if (status == 1) return 1;
                    break;
                }
                case 5: {
                    int status = search.Render();
                    if (status == 1) return 1;
                    break;
                }
                case 6: {
                    int status = export_file.Render();
                    if (status == 1) return 1;
                    break;
                }
                case 7: {
                    int status = import_file.Render();
                    if (status == 1) return 1;
                    break;
                }
                case 8:
                    return 0;
                    break;
            }
        }
        return 0;
    });

    list.Create([&](){
        Menu::Clear();
        std::cout << "\033[47;30mPhonebook: List\033[0m\n\n";

        if(c.size() == 0) std::cout << "No phone numbers.";
        else {
            Table t;
            t.add_row({"First Name","Last Name","Nickname","Address","Work Number","Private Number"});

            for (const Contact& i : c) {
                t.add_row({i.getFirstName().c_str(),i.getLastName().c_str(),i.getNickname().c_str(),i.getAddress().c_str(),i.getWorkNumber().c_str(),i.getPrivateNumber().c_str()});
            }
            std::cout << t ;
        }
        std::cout << std::endl << std::endl << "Press ENTER to exit";
        std::cin.get();
        return 0;
    });

    create.Create([&](){
        Menu::Clear();
        std::cout << "\033[47;30mPhonebook: Create\033[0m\n\n";
        
        std::cout << "First Name (optional): ";
        String firstName;
        std::cin >> std::noskipws >> firstName;

        std::cout << "Last Name (optional): ";
        String lastName;
        std::cin >> std::noskipws >> lastName;

        std::cout << "Nickname (optional): ";
        String nickname;
        std::cin >> std::noskipws >> nickname;

        std::cout << "Address (optional): ";
        String address;
        std::cin >> std::noskipws >> address;

        String workNumber;
        while (true) {
            std::cout << "Work Number (optional): ";
            std::cin >> workNumber;
            if (Contact::isPhoneNumber(workNumber) || workNumber.size() == 0) break;
            std::cout << "Wrong Phone Number Format! Use +361231234 or 06301231234\n";
        }

        String privateNumber;
        while (true) {
            std::cout << "Private Number: ";
            std::cin >> privateNumber;
            if (c.search([&](const Contact& con){return con.getPrivateNumber() == privateNumber;}) != -1) {
                std::cout << "Phone Number already exits\n";
                continue;
            }
            if (Contact::isPhoneNumber(privateNumber)) break;
            std::cout << "Wrong Phone Number Format! Use +361231234 or 06301231234\n";
        }

        c.pushBack({firstName,lastName,nickname,address,workNumber,privateNumber});
        c.saveFile(fileName);

        return 0;
    });

    update.Create([&](){
        printf("%d",3);
        return 0;
    });

    del.Create([&](){
        printf("%d",4);
        return 0;
    });

    search.Create([&](){
        printf("%d",5);
        return 0;
    });

    export_file.Create([&](){
        printf("%d",6);
        return 0;
    });

    import_file.Create([&](){
        printf("%d",7);
        return 0;
    });

    printf("\n");
    return mainMenu.Render();
}