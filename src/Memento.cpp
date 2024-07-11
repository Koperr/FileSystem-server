#include "Memento.h"

Memento::Memento(Directory directory) 
    : m_directory(directory) {}
Directory Memento::getState() const
{
    return m_directory; 
}


void Originator::setState(Directory directory)
{
    m_directory = directory;
}

Directory Originator::getState() const
{
    return m_directory;
}

Memento Originator::SaveStateToMemento()
{
    return Memento(m_directory);
}

void Originator::GetStateFromMemento(Memento memento)
{
    m_directory = memento.getState();
}

void CareTaker::AddMemento(Memento memento)
{
    mementoList.push_back(memento);
}

Memento CareTaker::GetMemento(std::vector<Memento>::size_type index)
{
    if(index < mementoList.size())
        return mementoList[index];
    else
    {
        // TODO 
        // OBSLUZYC TEN PRZYPADEK, TO CO JEST PONIZEJ TO TYMCZASOWA PROWIZORKA
        std::cout << "Cannot get previous state!\n";
        return mementoList[0];
    }
}