#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"


class Remove : public IComponentFunction
{
	IComponent* currentDir;
	string currentPath;

public:
	Remove(IComponent* currentDir, string& currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "������� ����������/����";
	}

	void Run(IComponent*& currentDir, string& currentPath) override
	{
		string name;
		cout << "������� ��� �����/�����" << endl;

		getline(cin, name);

		fs::path newPath(currentPath);
		newPath.append(name);

		currentDir->Remove(newPath.string());
	}
};
