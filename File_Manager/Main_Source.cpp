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
#include "CreateNewComponent.h"
#include "RemoveComponent.h"
#include "RenameComponent.h"
#include "CopyComponent.h"
#include "GetSizeComponent.h"
#include "FindComponent.h"
#include "MoveBack.h"
#include "MoveToRoot.h"
#include "Menu.h"




IMenu* MakeMenu(IComponent* currentDir, string currentPath)
{

	ICarReader* dbCarReader = new FileCarReader(carDBFileName);
	ICarWriter* dbCarWriter = new FileCarWriter(carDBFileName);

	ICarFinder* carFinder = new CarFinder(carDB);
	ICarSorter* carSorter = new CarSorter(carDB);

	ICarReader* carReader = new ConsoleCarReader();
	ICarWriter* carWriter = new ConsoleCarWriter();

	IMenu* menu = new ConsoleMenu();
	menu->AddCommand(new OpenDirectory(currentDir, currentPath));
	menu->AddCommand(new AddCarCommand(carDB, carReader));
	menu->AddCommand(new RenameComponent(carDB));
	menu->AddCommand(new FindCarByNameCommand(carFinder, carWriter));
	menu->AddCommand(new FindCarByMakeYearCommand(carFinder, carWriter));
	menu->AddCommand(new FindCarByEngineCapacityCommand(carFinder, carWriter));
	menu->AddCommand(new FindCarByCostCommand(carFinder, carWriter));
	menu->AddCommand(new SortCarsByNameCommand(carSorter));
	menu->AddCommand(new SortCarsByMakeYearCommand(carSorter));
	menu->AddCommand(new SortCarsByEngineCapacityCommand(carSorter));
	menu->AddCommand(new SortCarsByCostCommand(carSorter));

	return menu;
}


void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	string currentPath = fs::current_path().string();

	IComponent* currentDir = new Directory(currentPath);

	auto menu = MakeMenu(currentDir, currentPath);

	//carDBSaver->Load();

	menu->Start(currentDir);

	//carDBSaver->Save();

    system("pause");
}