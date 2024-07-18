#pragma once
#include <string>
#include "Component.h"


class Directory :public IComponent
{
private:

    vector <IComponent*> components;
    string name;

public:
    Directory(string name)
    {
        this->name = name;
    }

    ~Directory() override
    {
        if (!components.empty())
            for (int i = 0; i < components.size(); i++)
                delete components[i];
    }


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
        if (components.size() == 0)
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

    void Remove(const string& path)
    {
        fs::remove_all(path);
        for (int i = 0; i < components.size(); i++)
            if (components[i]->GetName() == path)
                components.erase(components.begin() + i);
    }

    double GetSize(const string& path) override
    {
        double sizeObject = 0;
        for (int i = 0; i < components.size(); i++)
        {
            if (components[i]->GetName() == path)
                for (const auto& object : fs::recursive_directory_iterator(components[i]->GetName()))
                    if (fs::is_directory(object))
                        GetSize(object.path().string());
                    else
                        sizeObject += fs::file_size(object);
        }
        return sizeObject;
    }

    //string MoveBack(const string& path) override
    //{
    //    fs::path newPath = path;
    //    return newPath.parent_path().string();
    //}

    //string MoveToRoot(const string& path) override
    //{
    //    fs::path newPath = path;
    //    return newPath.root_path().string();
    //}

    //string Open(const string& path) override
    //{
    //    string newPath = name + '\\' + path;
    //    return newPath;
    //}

    //void NewObject(const string& path) override
    //{
    //    fs::create_directory(path);
    //}

    //void Rename(const string& oldName, const string& newName) override
    //{
    //    for (int i = 0; i < components.size(); i++)
    //        if (components[i]->GetName() == oldName)
    //            components[i]->SetName(newName);

    //    fs::rename(oldName, newName);
    //}


    //void CopyCut(const string& path, const string& newPath, const bool flag) override
    //{
        //if(fs::is_regular_file(path))
        //{
        //    if (fs::copy_file(path, newPath))
        //        cout << format("Файл скопирован по пути {}!", newPath) << endl;
        //    if (flag)
        //        if (fs::remove(path))
        //            cout << format("Исходный файл {} удален!", path) << endl;
        //}
        //else if (fs::is_directory(path))
        //{
        //    for(const auto& iter:components)
        //        if(iter->GetName()==path)
        //        {
        //            CopyCut(iter->GetName())
        //            fs::copy(iter->GetName(), newPath);
        //        }
        //    if (flag)
        //        if (fs::remove_all(path))
        //            cout << format("Исходная директория удалена!") << endl;
        //}

    //}

    //string Find(const string& findName)override
    //{
    //    //if(!components.empty())
    //    //{
    //    //    for (int i = 0; i < components.size(); i++)
    //    //    {
    //    //        if (components[i]->GetName() == findName)
    //    //            return 
    //    //    }
    //    //}
    //}

    int Size() const override
    {
        return components.size();
    }

    void Print() const override
    {
        cout << format("[DIR] {}", name) << endl;
        if (!components.empty())
        {
            for (int i = 0; i < components.size(); i++)
            {
                //if (components[i]->GetName() == "D:\\System Volume Information")
                //    continue;
                try
                {
                    components[i]->Print();
                }
                catch (...) {}
            }
        }
        else
            cout << endl;
    }
};
