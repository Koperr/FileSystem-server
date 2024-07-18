#pragma once

#include <vector>
#include <iostream>
#include <map>
//#include "StructFile&Directory.h"

struct File
{
    std::string name;
    std::string content;
};

struct Directory
{
    std::string name;
    std::map<std::string, Directory> subdirectories;
    std::map<std::string, File> files;
};


class Memento
{
public:
    Memento(Directory directory);

    Directory getState() const;

private:
    Directory m_directory;
};

/////////////////////

class Originator
{
public:
    void setState(Directory directory);
    Directory getState() const;

    Memento SaveStateToMemento();
    void GetStateFromMemento(Memento memento);

private:
    Directory m_directory;
};

///////////////////

class CareTaker
{
public:
    void AddMemento(Memento memento);
    Memento GetMemento(std::vector<Memento>::size_type index);

    
    std::vector<Memento> mementoList;
private:
};

