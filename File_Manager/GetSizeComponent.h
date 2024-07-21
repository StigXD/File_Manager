#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"


class GetSize : public IComponentFunction
{
	IComponent* currentDir;
	string currentPath;

public:
	GetSize(IComponent* currentDir, string& currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "Показать размер директории/файла";
	}

	void Run(IComponent*& currentDir, string& currentPath) override
	{
		string name;
		cout << "Введите имя файла/папки" << endl;

		getline(cin, name);

		fs::path newPath(currentPath);
		newPath.append(name);

		double sizeObject = 0;

		if (newPath.has_extension())
		{
			IComponent* file = new File(newPath.string());
			sizeObject = file->GetSize(newPath.string());

			cout << format("Размер файла {} равен {} byte", newPath.string(), sizeObject) << endl;

			if (file != nullptr)
				delete file;
		}
		else
		{
			sizeObject = currentDir->GetSize(newPath.string());

			cout << format("Размер файла {} равен {} byte", newPath.string(), sizeObject) << endl;
		}

	}
};
