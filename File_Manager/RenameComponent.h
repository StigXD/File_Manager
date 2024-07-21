#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"


class Rename : public IComponentFunction
{
	IComponent* currentDir;
	string currentPath;

public:
	Rename(IComponent* currentDir, string& currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "������������� ����������/����";
	}

	void Run(IComponent*& currentDir, string& currentPath) override
	{
		cout << "�������� ����/�����" << endl;

		string oldName, newName;

		getline(cin, oldName);

		fs::path oldPath(currentPath);
		oldPath.append(oldName);

		cout << "������� ������ ��� => ";
		getline(cin, newName);

		fs::path newPath(currentPath);
		newPath.append(newName);

		fs::rename(oldPath, newPath);
	}
};
