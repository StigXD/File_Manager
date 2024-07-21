#pragma once
#include <string>
#include "Component.h"


class File : public IComponent
{
    string name;

public:

    File(string name)
    {
        this->name = name;
    }

    ~File() override = default;

    string GetName() override
    {
        return name;
    }

    void SetName(const string& name)override
    {
        this->name = name;
    }

    void Add(IComponent* component) override
    {
        throw ("Error type of component");
    }

    void Remove(const string& path)
    {
        throw ("Error type of component");
    }

    double GetSize(const string& path) override
    {
        double sizeObject = fs::file_size(path);
        return sizeObject;
    }

    int Size() const override
    {
        throw ("Error type of component");
    }

    void Print() const override
    {
        cout << format("[FILE] {}", name) << endl;
    }

    void Clear()
    {
        throw ("Error type of component");
    }

};
