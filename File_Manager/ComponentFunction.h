#pragma once
#include <string>

using namespace std;

class IComponentFunction
{
public:
	virtual ~IComponentFunction() = default;

	virtual string GetDescription() = 0;
	virtual void Run() = 0;
};
