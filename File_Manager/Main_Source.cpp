#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>

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

    virtual void Add(Component component) {}

    virtual void Remove(Component component) {}

    virtual void Print()
    {
        cout << name << endl;
    }
};

class Directory :public Component
{
private:

    vector <Component*> components = new vector <Component>();

public:
    Directory(string name): Component(name)
    {
    }

    void Add(Component component) override
    {
        components.push_back(component)
    }

    void Remove(Component component) override
    {
        for(int i = 0; i< components->size(); i++)
            if (components[i]->name == component)
        components.erase(component);
    }

    void Print() override
    {
        Console.WriteLine("Узел " + name);
        Console.WriteLine("Подузлы:");
        for (int i = 0; i < components.Count; i++)
        {
            components[i].Print();
        }
    }
};

class File : public Component
{
    public File(string name)
        : base(name)
    {}
};

class Program
{
    static void Main(string[] args)
    {
        Component* fileSystem = new Directory("Файловая система");
        // определяем новый диск
        Component* diskC = new Directory("Диск С");
        // новые файлы
        Component* pngFile = new File("12345.png");
        Component* docxFile = new File("Document.docx");
        // добавляем файлы на диск С
        diskC.Add(pngFile);
        diskC.Add(docxFile);
        // добавляем диск С в файловую систему
        fileSystem.Add(diskC);
        // выводим все данные
        fileSystem.Print();
        Console.WriteLine();
        // удаляем с диска С файл
        diskC.Remove(pngFile);
        // создаем новую папку
        Component* docsFolder = new Directory("Мои Документы");
        // добавляем в нее файлы
        Component* txtFile = new File("readme.txt");
        Component* csFile = new File("Program.cs");
        docsFolder.Add(txtFile);
        docsFolder.Add(csFile);
        diskC.Add(docsFolder);

        fileSystem.Print();

        Console.Read();
    }
};

