#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"
#include "AddComponent.h"

class Open : public IComponentFunction
{
	IComponent* currentDir;
	string* currentPath;

public:
	Open(IComponent* currentDir, string* currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "Открыть директорию";
	}

	void Run() override
	{
		string nameDirctory;
		cout << "Выберите папку" << endl;
		cin.ignore();
		getline(cin, nameDirctory);

		(*currentPath) = currentDir->GetName() + '\\' + nameDirctory;
		currentDir = new Directory(*currentPath);

		if (currentDir->Size() == 0)
		{
			for (const auto& object : fs::directory_iterator(currentDir->GetName()))
				if (fs::is_directory(object))
				{
					IComponent* subDir = new Directory(object.path().string());
					currentDir->Add(subDir);
				}
				else
				{
					IComponent* file = new File(object.path().string());
					currentDir->Add(file);
				}
		}
	}
};
