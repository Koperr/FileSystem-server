#include "FileSystem.h"
#include "Commands.h"

Commands commands;


void FileSystem::run()
{
    //while (!exit)
    for(int i = 0; i < 5; i++)
    {
        std::cout << m_CurrentPath;
        std::getline(std::cin, m_Input);
        commands.checkInput(m_Input);
    }
    
}
