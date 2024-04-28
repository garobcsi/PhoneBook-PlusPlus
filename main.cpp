#include "tabulate/single_include/tabulate/tabulate.hpp"
#include "./memtrace.h"
#include "menu.h"
#include "contacts.h"

int main()
{
    using namespace tabulate;

    String fileName = "telefonkonyv.csv";
    Contacts con;

    Menu mainMenu;
    Menu list;
    Menu create;
    Menu update;
    Menu del;
    Menu search;
    Menu export_file;
    Menu import_file;

    mainMenu.Create([&]() {
        if (Contacts::fileExists(fileName) && !Contacts::fileEmpty(fileName)) con.loadFile(fileName);
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
                    con.saveFile(fileName);
                    return 0;
                    break;
            }
        }
        return 0;
    });

    list.Create([&](){
        Menu::Clear();
        std::cout << "\033[47;30mPhonebook: List\033[0m\n\n";

        if(con.size() == 0) std::cout << "No phone numbers";
        else {
            Table t;
            t.add_row({"First Name","Last Name","Nickname","Address","Work Number","Private Number"});

            for (const Contact& i : con) {
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
            if (con.search([&](const Contact& c){return c.getPrivateNumber() == privateNumber;}) != -1) {
                std::cout << "Phone Number already exits\n";
                continue;
            }
            if (Contact::isPhoneNumber(privateNumber)) break;
            std::cout << "Wrong Phone Number Format! Use +361231234 or 06301231234\n";
        }

        con.pushBack({firstName, lastName, nickname, address, workNumber, privateNumber});
        con.saveFile(fileName);


        std::cout  << std::endl << "Contact created successfully\n\n" << "Press ENTER to exit";
        std::cin.get();
        return 0;
    });

    update.Create([&](){
        Menu::Clear();
        std::cout << "\033[47;30mPhonebook: Update\033[0m\n\n";

        int index = -1;
        String privNum;
        while (true) {
            std::cout << "Modify Private Number: ";
            std::cin >> std::noskipws >> privNum;
            if (!Contact::isPhoneNumber(privNum))  {
                std::cout << "Wrong Phone Number Format! Use +361231234 or 06301231234\n";
                continue;
            }
            if ((index = con.search([&](const Contact& c){return c.getPrivateNumber() == privNum;})) == -1) {
                std::cout << "Phone Number doesn't exist\n";
            } else break;
        }

        std::cout << "\nFirst Name (optional): ";
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
            if ((con.search([&](const Contact& c){return c.getPrivateNumber() == privateNumber;}) != -1) && privateNumber != privNum) {
                std::cout << "Phone Number already exits\n";
                continue;
            }
            if (Contact::isPhoneNumber(privateNumber)) break;
            std::cout << "Wrong Phone Number Format! Use +361231234 or 06301231234\n";
        }

        con[index] = {firstName, lastName, nickname, address, workNumber, privateNumber};
        con.saveFile(fileName);

        std::cout  << std::endl << "Contact updated successfully\n\n" << "Press ENTER to exit";
        std::cin.get();
        return 0;
    });

    del.Create([&](){
        Menu::Clear();
        std::cout << "\033[47;30mPhonebook: Delete\033[0m\n\n";

        int index = -1;
        String privNum;
        while (true) {
            std::cout << "Delete Private Number: ";
            std::cin >> std::noskipws >> privNum;
            if (!Contact::isPhoneNumber(privNum))  {
                std::cout << "Wrong Phone Number Format! Use +361231234 or 06301231234\n";
                continue;
            }
            if ((index = con.search([&](const Contact& c){return c.getPrivateNumber() == privNum;})) == -1) {
                std::cout << "Phone Number doesn't exist\n";
            } else break;
        }

        con.removeEl(index);
        con.saveFile(fileName);

        std::cout  << std::endl << "Contact deleted successfully\n\n" << "Press ENTER to exit";
        std::cin.get();
        return 0;
    });

    search.Create([&](){
        Menu::Clear();
        std::cout << "\033[47;30mPhonebook: Search\033[0m\n\n";

        if(con.size() == 0) std::cout << "No phone numbers";
        else {
            int index = -1;
            String privNum;
            while (true) {
                std::cout << "Search Private Number: ";
                std::cin >> std::noskipws >> privNum;
                if (!Contact::isPhoneNumber(privNum))  {
                    std::cout << "Wrong Phone Number Format! Use +361231234 or 06301231234\n";
                    continue;
                }
                if ((index = con.search([&](const Contact& c){return c.getPrivateNumber() == privNum;})) == -1) {
                    std::cout << "Phone Number doesn't exist\n";
                } else break;
            }
            Table t;
            t.add_row({"First Name","Last Name","Nickname","Address","Work Number","Private Number"});

            Contact tmp = con[index];
            t.add_row({tmp.getFirstName().c_str(),tmp.getLastName().c_str(),tmp.getNickname().c_str(),tmp.getAddress().c_str(),tmp.getWorkNumber().c_str(),tmp.getPrivateNumber().c_str()});

            std::cout << t ;
        }
        std::cout << std::endl << std::endl << "Press ENTER to exit";
        std::cin.get();
        return 0;
    });

    export_file.Create([&](){
        Menu::Clear();
        std::cout << "\033[47;30mPhonebook: Export\033[0m\n\n";
        String f;
        while(true) {
            std::cout << "Filename: ";
            std::cin >> std::noskipws >> f;
            if (Contacts::fileExists(f)) {
                std::cout << "File already exits\n";
            }
            else break;
        }
        con.saveFile(f);

        std::cout  << std::endl << "File exported successfully\n\n" << "Press ENTER to exit";
        std::cin.get();
        return 0;
    });

    import_file.Create([&](){
        Menu::Clear();
        std::cout << "\033[47;30mPhonebook: Import\033[0m\n\n";
        String f;
        while(true) {
            std::cout << "Filename: ";
            std::cin >> std::noskipws >> f;
            if (!Contacts::fileExists(f)) {
                std::cout << "File doesn't exits\n";
            }
            else break;
        }
        if (Contacts::fileEmpty(f)) con.clear();
        else try {
            con.loadFile(f);
            con.saveFile(fileName);
            std::cout << "\nFile imported successfully";
        } catch (...) {
            std::cout << "\nFile is corrupted !";
            if (!Contacts::fileEmpty(fileName)) {
                con.loadFile(fileName); con.saveFile(fileName);
            }
        }

        std::cout << "\n\nPress ENTER to exit";
        std::cin.get();
        return 0;
    });

    printf("\n");
    return mainMenu.Render();
}