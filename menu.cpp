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
#if defined _WIN32
    int err = system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    int err = system("clear");
#elif defined (__APPLE__)
    int err = system("clear");
#endif
}
