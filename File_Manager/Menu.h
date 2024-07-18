#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <functional>
#include "ComponentFunction.h"
#include "ShowDirectory.h"
#include "Component.h"

using namespace std;

namespace fs = filesystem;

//template <typename TValue>
//TValue Parse(std::function<TValue()> parseValue, TValue valueOnError)
//{
//	try
//	{
//		return parseValue();
//	}
//	catch (...)
//	{
//		return valueOnError;
//	}
//}

int ReadSelector(const int maxValue)
{
	string str;
	getline(cin, str);

	try
	{
		const int selector = stoi(str);
		if (selector < 0 || selector > maxValue)
			return -1;

		return selector;
	}
	catch (...)
	{
		return -1;
	}
}

class IMenu
{
public:
	virtual ~IMenu() = default;

	virtual void AddCommand(IComponentFunction* command) = 0;
	virtual void Start(IComponent* currentDir, IPrinter* showDir) = 0;
};

class ConsoleMenu : public IMenu
{
	vector<IComponentFunction*> commands;
	IPrinter* showDir;

	void PrintCommands() const
	{
		for (int i = 0; i < commands.size(); i++)
			cout << i + 1 << ": " << commands[i]->GetDescription() << endl;
		cout << "0: Exit" << endl;
	}

	void ExecutedCommand(const int selector) const
	{
		cout << endl << commands[selector - 1]->GetDescription() << endl << endl;

		try
		{
			commands[selector - 1]->Run();
		}
		catch (const string& message)
		{
			cout << "An error has occurred: " << message << endl;
		}
		catch (...)
		{
			cout << "An error has occurred: unknown" << endl;
		}

		cout << endl;
		system("pause");
	}

public:
	~ConsoleMenu() override
	{
		for (const IComponentFunction* command : commands)
			delete command;

		commands.clear();
	}

	void AddCommand(IComponentFunction* command) override
	{
		commands.push_back(command);
	}

	void Start(IComponent* currentDir, IPrinter* showDir) override
	{

		while (true)
		{
			system("cls");

			this->showDir = showDir;
			this->showDir->Print(currentDir);

			PrintCommands();

			const int selector = ReadSelector(commands.size());
			if (selector == 0)
				break;

			if (selector != -1)
				ExecutedCommand(selector);
		}
	}
};

