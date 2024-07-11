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
    
    virtual ~Component() = default;

    virtual void Add(Component* component) = 0;
    virtual string GetName() = 0;
    virtual void SetName(const string& name) = 0;
    virtual void Clear(Component* component) = 0;
    virtual void Remove(const string& path) = 0;
    virtual string MoveBack(const string& path) = 0;
    virtual string MoveToRoot(const string& path) = 0;
    virtual string Open(const string& path) = 0;
    virtual void NewObject(const string& path) = 0;
    virtual void Rename(const string& oldName, const string& newName) = 0;
    virtual double GetSizeDirectory(const string& path, double& sizeObject) = 0;
    virtual double GetSizeFile(const string& path, double& sizeObject) = 0;


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

    ~Directory() override
    {
        if (!components.empty())
            //for (int i = 0; i < components.size(); i++)
                Clear(this);
    }


    string GetName() override
    {
        return name;
    }

    void SetName(const string& name)override
    {
        this->name = name;
    }

    void Add(Component* component) override
    {
        if(components.size() == 0)
            components.push_back(component);
        else
        {
            for (int i = 0; i < components.size(); i++)
                if (components[i]->GetName() == component->GetName())
                {
                    components[i] = component;
                    break;
                }
            components.push_back(component);
        }
    }

    void Clear(Component* component) override
    {
        components.erase(remove(components.begin(), components.end(), component), components.end());
    }

    void Remove(const string& path)
    {
        fs::remove_all(path);
        for (int i = 0; i < components.size(); i++)
            if (components[i]->GetName() == path)
                components.erase(components.begin()+i);
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

    string Open(const string& path) override
    {
        string newPath = name + '\\' + path;
        return newPath;
    }

    void NewObject(const string& path) override
    {
        fs::create_directory(path);
    }

    void Rename(const string& oldName, const string& newName) override
    {
        for (int i = 0; i < components.size(); i++)
            if (components[i]->GetName() == oldName)
                components[i]->SetName(newName);

        fs::rename(oldName, newName);
    }

    double GetSizeDirectory(const string& path, double& sizeObject) override
    {
        for (int i = 0; i < components.size(); i++)
        {
            if (components[i]->GetName() == path)
                for (const auto& object : fs::recursive_directory_iterator(components[i]->GetName()))
                    if (fs::is_directory(object))
                        GetSizeDirectory(object.path().string(), sizeObject);
                    else
                        sizeObject += fs::file_size(object);
        }
        return sizeObject;
    }

    double GetSizeFile(const string& path, double& sizeObject) override
    {
        throw exception();
    }

    int Size() override
    {
        return components.size();
    }

    void Print() override
    {
        cout << format("[Папка] {}", name) << endl;
        if (!components.empty())
        {
            for (int i = 0; i < components.size(); i++)
            {
                if (components[i]->GetName() == "D:\\System Volume Information")
                    continue;
                components[i]->Print();
            }
        }
    }
};

class File : public Component
{
public:

    File(string name) : Component(name) { }

    ~File() override = default;
    //{
    //    if (!components.empty())
    //        //for (int i = 0; i < components.size(); i++)
    //        Remove(this);
    //}

    string GetName() override
    {
        return name;
    }

    void SetName(const string& name)override
    {
        this->name = name;
    }

    void Add(Component* component) override
    {
        throw exception();
    }

    void Clear(Component* component) override
    {
        throw exception();
    }

    void Remove(const string& path)
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

    string Open(const string& path) override
    {
        throw exception();
    }

    void NewObject(const string& path) override
    {
        ofstream newFile;
        newFile.open(path);
        if (!newFile.is_open())
            cout << "Неудалось создать файл" << endl;
        newFile.close();
    }

    void Rename(const string& oldName, const string& newName) override
    {
        throw exception();
    }

    double GetSizeDirectory(const string& path, double& sizeObject) override
    {
        throw exception();
    }

    double GetSizeFile(const string& path, double& sizeObject) override
    {
        sizeObject = fs::file_size(path);
        return sizeObject;
    }

    int Size() override
    {
        throw exception();
    }

    void Print() override
    {
        cout << format("[Файл] {}", name) << endl;
    }

};
