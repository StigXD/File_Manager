#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"
#include "AddComponent.h"

class Open : public IComponentFunction
{
	IComponent* currentDir;
	string currentPath;

public:
	Open(IComponent* currentDir, string& currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "Открыть директорию";
	}

	void Run(IComponent*& currentDir, string& currentPath) override
	{
		string nameDirctory;
		cout << "Выберите папку" << endl;
		getline(cin, nameDirctory);

		currentPath = currentDir->GetName() + '\\' + nameDirctory;
		currentDir = new Directory(currentPath);
	}
};
