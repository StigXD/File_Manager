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
		return "����������/����������� ����������/����";
	}

	void Run() override
	{
		string name, pathDestination;
		bool flag;

		cout << "������� ��� �����/�����" << endl;

		cin.ignore();
		getline(cin, name);
		fs::path namePath(*currentPath);
		namePath.append(name);

		cout << "������� ���� ����������" << endl;

		getline(cin, pathDestination);
		fs::path newPath(pathDestination);
		newPath.append(name);

		cout << "�����������? (0/1)";
		cin >> flag;
		if (fs::is_regular_file(namePath))
		{
			if (fs::copy_file(namePath, newPath))
				cout << format("���� ���������� �� ���� {}!", newPath.string()) << endl;
			if (flag)
				if (fs::remove(namePath))
					cout << format("�������� ���� {} ������!", newPath.string()) << endl;
		}
		else if (fs::is_directory(namePath))
		{
			fs::copy(namePath, newPath);
			cout << format("���� ���������� �� ���� {}!", newPath.string()) << endl;
			if (flag)
				if (fs::remove_all(namePath))
					cout << format("�������� ���������� �������!") << endl;
		}
	}
};
