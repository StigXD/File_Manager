#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <format>

using namespace std;

class Component
{
protected:

    string name;

public:
    Component(string name)
    {
        this->name = name;
    }

    virtual void Add(Component* component) = 0;

    virtual void Remove(Component* component) = 0;
    virtual int Size() = 0;

    virtual void Print() = 0;
};

class Directory :public Component
{
private:

    vector <Component*> components;

public:
    Directory(string name) : Component(name)
    {
    }

    void Add(Component* component) override
    {
        components.push_back(component);
    }

    void Remove(Component* component) override
    {
        components.erase(remove(components.begin(), components.end(), component), components.end());
    }

    int Size() override
    {
        return components.size();
    }

    void Print() override
    {
        cout << format("Папка {}", name) << endl;
        cout << format("Содержимое:") << endl;
        for (int i = 0; i < components.size(); i++)
            components[i]->Print();
        cout << endl;
    }
};

class File : public Component
{
public:

    File(string name) : Component(name) { }

    void Add(Component* component) override
    {
        throw exception();
    }

    void Remove(Component* component) override
    {
        throw exception();
    }

    int Size() override
    {
        throw exception();
    }

    void Print() override
    {
        cout << format("Файлы: ");
        cout << name << endl;
    }

};
