#pragma once

#include <vector>

#include "FileSystem.h"


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
    Memento GetMemento(int index);

private:
    std::vector<Memento> mementoList;
};
