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
    }

    void Remove(const string& path)
    {
    }

    //string MoveBack(const string& path) override
    //{
    //    throw exception();
    //}
    //string MoveToRoot(const string& path) override
    //{
    //    throw exception();
    //}

    //string Open(const string& path) override
    //{
    //    throw exception();
    //}

    //void NewObject(const string& path) override
    //{
    //    ofstream newFile;
    //    newFile.open(path);
    //    if (!newFile.is_open())
    //        cout << "Неудалось создать файл" << endl;
    //    newFile.close();
    //}

    //void Rename(const string& oldName, const string& newName) override
    //{
    //    throw exception();
    //}

    double GetSize(const string& path) override
    {
        double sizeObject = fs::file_size(path);
        return sizeObject;
    }

    //void CopyCut(const string& path, const string& newPath, const bool flag) override
    //{

    //}

    ////string Find(const string& path)override
    ////{

    ////}

    int Size() const override
    {
    }

    void Print() const override
    {
        cout << format("[FILE] {}", name) << endl;
    }

};
