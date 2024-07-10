#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <format>

using namespace std;
namespace fs = filesystem;

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
    virtual string GetName() = 0;
    virtual void Remove(Component* component) = 0;
    virtual string MoveBack(const string& path) = 0;
    virtual string MoveToRoot(const string& path) = 0;
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

    string GetName() override
    {
        return name;
    }

    void Add(Component* component) override
    {
        for (int i = 0; i < components.size(); i++)
            if (components[i]->GetName() == component->GetName())
                components[i] = component;
            else
                components.push_back(component);
    }

    void Remove(Component* component) override
    {
        components.erase(remove(components.begin(), components.end(), component), components.end());
    }

    string MoveBack(const string& path) override
    {
        fs::path newPath = path;
        return newPath.parent_path().string();
    }

    string MoveToRoot(const string& path) override
    {
        fs::path newPath = path; 
        return newPath.root_path().string();

    }

    int Size() override
    {
        return components.size();
    }

    void Print() override
    {
        cout << format("[Ïàïêà] {}", name) << endl << endl;
        if (!components.empty())
        {
            for (int i = 0; i < components.size(); i++)
                if (!fs::is_empty(components[i]->GetName()))
                    components[i]->Print();
        }
    }
};

class File : public Component
{
public:

    File(string name) : Component(name) { }

    string GetName() override
    {
        return name;
    }

    void Add(Component* component) override
    {
        throw exception();
    }

    void Remove(Component* component) override
    {
        throw exception();
    }

    string MoveBack(const string& path) override
    {
        throw exception();
    }
    string MoveToRoot(const string& path) override
    {
        throw exception();
    }

    int Size() override
    {
        throw exception();
    }

    void Print() override
    {
        cout << format("[Ôàéë] {}", name) << endl;
    }

};
