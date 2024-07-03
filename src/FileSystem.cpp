#include "FileSystem.h"
#include "Commands.h"

Commands commands;

Folder::Folder(const std::string& name, const std::string& path)
{
}

void FileSystem::run()
{
    //while (!exit)
    for(int i = 0; i < 5; i++)
    {
        std::cout << currentPath;
        std::getline(std::cin, m_Input);
        commands.checkInput(m_Input);
    }
    
}
