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

		cout << endl << "������� ����������: ";
		ShowDirectory(currentDir, path);
		cout << endl;


		cout << "�������� ����� ����:" << endl;
		cout << "1 - ������� �����" << endl;
		cout << "2 - ������� �����/����" << endl;
		cout << "3 - ������� �����/����" << endl;
		cout << "4 - ������������� �����/����" << endl;
		cout << "5 - ����������/����������� �����/����" << endl;
		cout << "6 - �������� ������ �����" << endl;
		cout << "7 - ����� ����� �� ��������" << endl;
		cout << "8 - ����� �� �����" << endl;
		cout << "9 - �����" << endl;
		cout << "10 - ��������� � ������ �����" << endl;
		cout << "0 - Exit" << endl;
		
		cin >> choice;

		if (choice == 0)
			return;

		switch (choice)
		{
		case 1:
		{
			string nameDirctory;
			cout << "�������� �����" << endl;
			cin.ignore();
			getline(cin, nameDirctory);

			path = currentDir->Open(nameDirctory);
			currentDir = new Directory(path);

			break;
		}
		case 2:
		{
			string name;
			cout << "������� ��������" << endl;
			cin.ignore();
			getline(cin, name);
			fs::path newPath(path);
			newPath.append(name);

			if(newPath.has_extension())
			{
				Component* file = new File(newPath.string());
				file->NewObject(newPath.string());
				currentDir->Add(file);
			}
			else
			{
				Component* subDir = new Directory(newPath.string());
				subDir->NewObject(newPath.string());
				currentDir->Add(subDir);
			}

			break;
		}
		case 3:
		{
			string name;
			cout << "������� ��� �����/�����" << endl;

			cin.ignore();
			getline(cin, name);

			fs::path newPath(path);
			newPath.append(name);

			currentDir->Remove(newPath.string());

			break;
		}
		case 4:
		{
			cout << "�������� ����/�����" << endl;
			string oldName, newName;
			cin.ignore();
			getline(cin, oldName);

			fs::path oldPath(path);
			oldPath.append(oldName);

			cout << "������� ������ ��� => ";
			getline(cin, newName);

			fs::path newPath(path);
			newPath.append(newName);

			currentDir->Rename(oldPath.string(), newPath.string());

			break;
		}
		case 5:
		{
			string name, newPath;
			bool flag;

			cout << "������� ��� �����/�����" << endl;

			cin.ignore();
			getline(cin, name);

			cout << "������� ���� ����������" << endl;
			getline(cin, newPath);
			
			cout << "�����������? (0/1)";
			cin >> flag;

			for (auto& copyFile : fs::recursive_directory_iterator(path))
				if (fs::is_regular_file(copyFile))
				{
					if (copyFile.path().filename().string().find(name) != -1)
					{
						cout << format("������ ���� {}", copyFile.path().filename().string()) << endl;

						if (fs::copy_file(copyFile.path(), newPath + '\\' + copyFile.path().filename().string()))
							cout << format("���� {} ���������� �� ���� {}!", copyFile.path().filename().string(), newPath) << endl;

						if (flag)
							if (fs::remove(copyFile.path()))
								cout << format("�������� ���� {} ������!", copyFile.path().filename().string()) << endl;

						break;
					}
				}
				else if (fs::is_directory(copyFile))
				{
					if (copyFile.path().string().find(name) != -1)
					{
						cout << format("������� ���������� {}", copyFile.path().string()) << endl;

						fs::copy(copyFile.path(), newPath + '\\' + copyFile.path().filename().string());

						cout << format("���������� {} �����������!", copyFile.path().filename().string()) << endl;

						if (flag)
							if (fs::remove_all(copyFile.path()))
								cout << format("�������� ���������� {} �������!", copyFile.path().string()) << endl;

						break;
					}
				}

			break;
		}
		case 6:
		{
			string name;
			cout << "������� ��� �����/�����" << endl;

			cin.ignore();
			getline(cin, name);

			fs::path newPath(path);
			newPath.append(name);

			double sizeObject = 0;

			if (newPath.has_extension())
				currentDir->GetSizeFile(newPath.string(), sizeObject);
			else
				currentDir->GetSizeDirectory(newPath.string(), sizeObject);

			cout << format("������ ����� {} ����� {} Mb", newPath.string(), sizeObject / 1024 / 1024) << endl;
			break;
		}
		case 7:
		{
			string name;
			cout << "����� => " << endl;
			cin >> name;
			
			for (auto& findFile : fs::recursive_directory_iterator(path))
				if (fs::is_regular_file(findFile))
					if (findFile.path().filename().string().find(name)!=-1)
						cout << format("������ ���� {}\n", findFile.path().string());
			break;
		}
		case 8:
		{
			string mask;
			cout << "����� �� ����� => ";
			cin >> mask;

			for (auto& findFile : fs::recursive_directory_iterator(path))
				if (fs::is_regular_file(findFile))
					if(findFile.path().extension().string().find(mask)!=-1)
						cout << format("������ ���� {}\n", findFile.path().string());
			break;
		}
		case 9:
		{
			path = currentDir->MoveBack(path);
			currentDir = new Directory(path);
			break;
		}
		case 10:
		{
			path = currentDir->MoveToRoot(path);
			currentDir = new Directory(path);
			break;
		}

		}
	}

}