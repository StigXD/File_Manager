#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <format>

using namespace std;
namespace fs = filesystem;

#include "Component.h"
#include "OpenDirectory.h"
#include "AddComponent.h"
#include "RemoveComponent.h"
#include "RenameComponent.h"
#include "CopyComponent.h"
#include "GetSizeComponent.h"
#include "FindComponent.h"
#include "FindByMask.h"
#include "MoveBack.h"
#include "MoveToRoot.h"
#include "Menu.h"




IMenu* MakeMenu(IComponent* currentDir, string& currentPath)
{
	IMenu* menu = new ConsoleMenu();
	menu->AddCommand(new Open(currentDir, currentPath));
	menu->AddCommand(new Add(currentDir, currentPath));
	menu->AddCommand(new Remove(currentDir, currentPath));
	menu->AddCommand(new Rename(currentDir, currentPath));
	menu->AddCommand(new Copy(currentDir, currentPath));
	menu->AddCommand(new GetSize(currentDir, currentPath));
	menu->AddCommand(new Find(currentDir, currentPath));
	menu->AddCommand(new FindByMask(currentDir, currentPath));
	menu->AddCommand(new MoveBack(currentDir, currentPath));
	menu->AddCommand(new MoveToRoot(currentDir, currentPath));

	return menu;
}


void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	static string currentPath = fs::current_path().string();

	static IComponent* currentDir = new Directory(currentPath);

	IPrinter* showMenu = new ConsolePrint();

	auto menu = MakeMenu(currentDir, currentPath);

	menu->Start(currentDir, showMenu, currentPath);

    system("pause");
}