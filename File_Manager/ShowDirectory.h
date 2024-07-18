#pragma once

#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Component.h"
#include "Directory.h"
#include "File.h"

using namespace std;

class IPrinter
{
public:
	virtual ~IPrinter() = default;

	virtual void Print(const IComponent* component) = 0;
};

class ConsolePrint : public IPrinter
{

public:
	void Print(const IComponent* component) override
	{
		component->Print();
	}
};

