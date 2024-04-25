#include "tabulate/single_include/tabulate/tabulate.hpp"
#include "./memtrace.h"
#include "menu.h"
#include "contacts.h"

int main()
{
    using namespace tabulate;

    String file = "telefonkonyv.csv";
    Contacts c;

    if (Contacts::fileExists(file)) c.loadFile(file);

    Menu mainMenu;
    Menu list;
    Menu create;
    Menu update;
    Menu del;
    Menu search;
    Menu export_file;
    Menu import_file;

    mainMenu.Create([&]() {
        while (true) {
            Menu::Clear();
            std::cout
            << "Phonebook\n\n"
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
    });

    list.Create([](){
        printf("%d",1);
        return 0;
    });

    create.Create([](){
        printf("%d",2);
        return 0;
    });

    update.Create([](){
        printf("%d",3);
        return 0;
    });

    del.Create([](){
        printf("%d",4);
        return 0;
    });

    search.Create([](){
        printf("%d",5);
        return 0;
    });

    export_file.Create([](){
        printf("%d",6);
        return 0;
    });

    import_file.Create([](){
        printf("%d",7);
        return 0;
    });

    printf("\n");
    return mainMenu.Render();
}