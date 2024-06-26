#include "menu.h"
#include "memtrace.h"

int Menu::Render() {
    try
    {
        if (func == nullptr)
        {
            std::cerr << "Error: No function to execute" << std::endl;
            return 1;
        }
        return func();
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Exception caught: " << typeid(ex).name() << std::endl;
        std::cerr << "Error message: " << ex.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught" << std::endl;
        return 1;
    }
}

void Menu::Clear() {
    printf("\033[2J\033[1;1H");
}
