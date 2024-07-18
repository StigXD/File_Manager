#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"


class RenameComponent : public IComponentFunction
{
	IComponent* currentDir;
	string currentPath;

public:
	RenameComponent(IComponent* carDB)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "Переименовать директорию/файл";
	}

	void Run() override
	{
		cout << "Выберите файл/папку" << endl;

		string oldName, newName;

		cin.ignore();
		getline(cin, oldName);

		fs::path oldPath(currentPath);
		oldPath.append(oldName);

		cout << "Введите новове имя => ";
		getline(cin, newName);

		fs::path newPath(currentPath);
		newPath.append(newName);

		//for (auto iter: currentDir.)
		//	if (currentDir. == oldName)
		//		currentDir[i]->SetName(newName);

		fs::rename(oldName, newName);
	}
};
