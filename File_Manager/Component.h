#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <format>

using namespace std;

class IComponent
{
public:
   
    virtual ~IComponent() = default;
    virtual string GetName() = 0;
    virtual void SetName(const string& name) = 0;
    virtual double GetSize(const string& path) = 0;
    virtual void Add(IComponent* component) = 0;
    virtual void Remove(const string& path) = 0;
    virtual void Print() const = 0;
    virtual int Size() const = 0;
    virtual void Clear() = 0;

};



//class ComponentFunction:public Component
//{
//public:
//    virtual void Add(Component* component) = 0;
//    virtual void SetName(const string& name) = 0;
//    virtual void Clear(Component* component) = 0;
//    virtual void Remove(const string& path) = 0;
//    virtual void NewObject(const string& path) = 0;
//    virtual void Rename(const string& oldName, const string& newName) = 0;
//    virtual void CopyCut(const string& path, const string& newPath, const bool flag) = 0;
//    virtual void Print() = 0;
//    virtual double GetSize(const string& path, double& sizeObject) = 0;
//    virtual int Size() = 0;
//    virtual string GetName() = 0;
//    virtual string MoveBack(const string& path) = 0;
//    virtual string MoveToRoot(const string& path) = 0;
//    virtual string Open(const string& path) = 0;
//    virtual string Find(const string& path) = 0;
//
//};