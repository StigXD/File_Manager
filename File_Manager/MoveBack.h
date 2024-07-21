#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"
#include "AddComponent.h"

class MoveBack : public IComponentFunction
{
	IComponent* currentDir;
	string currentPath;

public:
	MoveBack(IComponent* currentDir, string& currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "Назад";
	}

	void Run(IComponent*& currentDir, string& currentPath) override
	{
		fs::path newPath = currentPath;
		(currentPath) = newPath.parent_path().string();
		currentDir = new Directory(currentPath);
	}
};
