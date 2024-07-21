#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"
#include "AddComponent.h"

class MoveToRoot : public IComponentFunction
{
	IComponent* currentDir;
	string currentPath;

public:
	MoveToRoot(IComponent* currentDir, string& currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "Вернуться в корень диска";
	}

	void Run(IComponent*& currentDir, string& currentPath) override
	{
		fs::path newPath = currentPath;
		(currentPath) = newPath.root_path().string();
		currentDir = new Directory(currentPath);
	}
};
