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
        Clear();
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

    void Clear()
    {
        if (!components.empty())
            components.erase(components.begin(), components.end());
    }
};
