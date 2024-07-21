#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"


class FindByMask : public IComponentFunction
{
	IComponent* currentDir;
	string currentPath;

public:
	FindByMask(IComponent* currentDir, string& currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "����� �� �����";
	}

	void Run(IComponent*& currentDir, string& currentPath) override
	{
		string mask;
		cout << "����� �� ����� => ";
		cin >> mask;

		for (auto& findFile : fs::recursive_directory_iterator(currentPath))
			if (fs::is_regular_file(findFile))
				if(findFile.path().extension().string().find(mask)!=-1)
					cout << format("������ ���� {}\n", findFile.path().string());
	}
};
