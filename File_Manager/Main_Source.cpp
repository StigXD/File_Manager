#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <format>
#include "Component.h"
#include "Menu.h"


using namespace std;


void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Menu();

    system("pause");
}