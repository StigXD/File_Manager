#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"



class Copy : public IComponentFunction
{
	IComponent* currentDir;
	string* currentPath;

public:
	Copy(IComponent* currentDir, string* currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "Копировать/переместить директорию/файл";
	}

	void Run() override
	{
		string name, pathDestination;
		bool flag;

		cout << "Введите имя файла/папки" << endl;

		cin.ignore();
		getline(cin, name);
		fs::path namePath(*currentPath);
		namePath.append(name);

		cout << "Укажите путь назначения" << endl;

		getline(cin, pathDestination);
		fs::path newPath(pathDestination);
		newPath.append(name);

		cout << "Переместить? (0/1)";
		cin >> flag;
		if (fs::is_regular_file(namePath))
		{
			if (fs::copy_file(namePath, newPath))
				cout << format("Файл скопирован по пути {}!", newPath.string()) << endl;
			if (flag)
				if (fs::remove(namePath))
					cout << format("Исходный файл {} удален!", newPath.string()) << endl;
		}
		else if (fs::is_directory(namePath))
		{
			fs::copy(namePath, newPath);
			cout << format("Файл скопирован по пути {}!", newPath.string()) << endl;
			if (flag)
				if (fs::remove_all(namePath))
					cout << format("Исходная директория удалена!") << endl;
		}
	}
};
