#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <format>
#include <functional>
#include "ShowDirectory.h"
#include "Component.h"

using namespace std;

namespace fs = filesystem;

void Menu()
{
	//CacheFilesystem(path);
	string path = fs::current_path().string();

	Component* currentDir = new Directory(path);

	while(true)
	{
		int choice;

		cout << "Текущая директория: " << endl;
		ShowDirectory(currentDir, path);


		cout << "Выберите пункт меню:" << endl;
		cout << "1 - Показать содержимое директории" << endl;
		cout << "2 - Создать папку/файл" << endl;
		cout << "3 - Удалить папку/файл" << endl;
		cout << "4 - Переименовать папку/файл" << endl;
		cout << "5 - Копировать/переместить папку/файл" << endl;
		cout << "6 - Показать размер файла" << endl;
		cout << "7 - Поиск файла по названию" << endl;
		cout << "8 - Поиск по маске" << endl;
		cout << "9 - Назад" << endl;
		cout << "10 - Вернуться в корень диска" << endl;
		cout << "0 - Exit" << endl;
		
		cin >> choice;

		if (choice == 0)
			return;

		switch (choice)
		{
		case 1:
		{
			ShowDirectory(currentDir, path);
			break;
		}
		case 2:
		{
			cout << "Создать:" << endl;
			cout<<"0 - директорию" << endl;
			cout << "1 - файл" << endl;

			bool choose;
			cin >> choose;

			string name;
			cout << "Введите название" << endl;
			cin.ignore();
			getline(cin, name);
			name = path + '\\' + name;


			if(choose)
			{
				ofstream newFile;
				newFile.open(name);
				if (!newFile.is_open())
					cout << "Неудалось создать файл" << endl;
				newFile.close();
			}
			else
				fs::create_directory(name);
			break;
		}
		case 3:
		{
			string name;
			cout << "Введите имя файла/папки" << endl;

			cin.ignore();
			getline(cin, name);

			for (auto& deleteFile : fs::recursive_directory_iterator(path))
				if (fs::is_regular_file(deleteFile))
				{
					if (deleteFile.path().filename().string().find(name) != -1)
					{
						cout << format("Найден файл {}", deleteFile.path().filename().string()) << endl;
						if (fs::remove(deleteFile.path()))
							cout << format("Файл {} удален!", deleteFile.path().filename().string()) << endl;
						break;
					}
				}
				else if (fs::is_directory(deleteFile))
				{
					if (deleteFile.path().string().find(name) != -1)
					{
						cout << format("Найдена директория {}", deleteFile.path().string()) << endl;
						if (fs::remove_all(deleteFile.path()))
							cout << format("Директория {} удалена!", deleteFile.path().string()) << endl;
						break;
					}
				}
			break;
		}
		case 4:
		{
			cout << "Выберите файл/папку" << endl;
			string name, newName;
			cin.ignore();
			getline(cin, name);

			cout << "Введите новове имя => ";
			cin.ignore();
			getline(cin, newName);

			for (auto& object : fs::recursive_directory_iterator(path))
				if (fs::is_regular_file(object) || fs::is_directory(object))
					if (object.path().string().find(name) != -1)
					{
						cout << format("Найден файл: {}\n", object.path().filename().string());
						fs::rename(object.path(), object.path().parent_path().string() + '\\' + newName);
						break;
					}


			break;
		}
		case 5:
		{
			string name, newPath;
			bool flag;

			cout << "Введите имя файла/папки" << endl;

			cin.ignore();
			getline(cin, name);

			cout << "Укажите путь назначения" << endl;
			getline(cin, newPath);
			
			cout << "Переместить? (0/1)";
			cin >> flag;

			for (auto& copyFile : fs::recursive_directory_iterator(path))
				if (fs::is_regular_file(copyFile))
				{
					if (copyFile.path().filename().string().find(name) != -1)
					{
						cout << format("Найден файл {}", copyFile.path().filename().string()) << endl;

						if (fs::copy_file(copyFile.path(), newPath + '\\' + copyFile.path().filename().string()))
							cout << format("Файл {} скопирован по пути {}!", copyFile.path().filename().string(), newPath) << endl;

						if (flag)
							if (fs::remove(copyFile.path()))
								cout << format("Исходный файл {} удален!", copyFile.path().filename().string()) << endl;

						break;
					}
				}
				else if (fs::is_directory(copyFile))
				{
					if (copyFile.path().string().find(name) != -1)
					{
						cout << format("Найдена директория {}", copyFile.path().string()) << endl;

						fs::copy(copyFile.path(), newPath + '\\' + copyFile.path().filename().string());

						cout << format("Директория {} скопирована!", copyFile.path().filename().string()) << endl;

						if (flag)
							if (fs::remove_all(copyFile.path()))
								cout << format("Исходная директория {} удалена!", copyFile.path().string()) << endl;

						break;
					}
				}

			break;
		}
		case 6:
		{
			string name;
			cout << "Введите имя файла/папки" << endl;

			cin.ignore();
			getline(cin, name);

			for (auto& sizeFile : fs::recursive_directory_iterator(path))
				if (sizeFile.path().filename().string().find(name) != -1)
					cout << format("Размер файла {} равен {} Mb", sizeFile.path().filename().string(), fs::file_size(sizeFile.path())/1024/1024) << endl;
			break;
		}
		case 7:
		{
			string name;
			cout << "Поиск => " << endl;
			cin >> name;
			
			for (auto& findFile : fs::recursive_directory_iterator(path))
				if (fs::is_regular_file(findFile))
					if (findFile.path().filename().string().find(name)!=-1)
						cout << format("Найден файл {}\n", findFile.path().string());
			break;
		}
		case 8:
		{
			string mask;
			cout << "Поиск по маске => ";
			cin >> mask;

			for (auto& findFile : fs::recursive_directory_iterator(path))
				if (fs::is_regular_file(findFile))
					if(findFile.path().extension().string().find(mask)!=-1)
						cout << format("Найден файл {}\n", findFile.path().string());
			break;
		}
		case 9:
		{
			currentDir = new Directory(currentDir->MoveBack(path));
			break;
		}
		case 10:
		{
			currentDir = new Directory(currentDir->MoveToRoot(path));
			break;
		}

		}
	}

}