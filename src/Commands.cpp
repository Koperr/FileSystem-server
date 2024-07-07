#include "Commands.h"


void Commands::getFlags(const std::string& str)
{
    std::string firstFlag;
    std::string substring;
    int spacePos = str.find(" ");
    int length = str.length() - spacePos;

    // If there is no spacepos, sets the value of flag to substr of everything exept the first word
    if(spacePos != std::string::npos)
    {
        substring = str.substr(spacePos + 1, length);
        // now "substring" is separated from the command

        spacePos = substring.find(" ");
        length = substring.length() - spacePos;
        if(spacePos == std::string::npos)
        {
            m_Flag1 = substring;
            m_Flag2 = "0";
        }
        else if(spacePos != std::string::npos)
        {
            m_Flag1 = substring.substr(0, spacePos); // first word after command
            m_Flag2 = substring.substr(spacePos + 1, substring.size() - spacePos - 1); // everything else beyond
        }
    }
    else
        {
            m_Flag1 = "0";
            m_Flag2 = "0";
        }
    std::cout << "Flag 1 [" << m_Flag1 << "]\n";
    std::cout << "Flag 2 [" << m_Flag2 << "]\n";

}

void Commands::getCommand(const std::string& str)
{
    int spacePos = str.find(" ");

    if(spacePos != std::string::npos)
        m_Command = str.substr(0, spacePos);
    else if(str == "")
        return;
    else
        m_Command = str;

    // checking if "command" is a command
    if(commandMap.find(m_Command) != commandMap.end())
    {
        auto function = commandMap[m_Command];
        function();
    }
    else if(m_Command == "")
        return;
    else
        std::cout << "[ERROR] Wrong command [" << m_Command << "]\n";
    
    std::cout << "Command [" << m_Command << "]\n"; 
}

void Commands::checkInput(const std::string& input)
{
    m_Input = input;

    getFlags(input);

    getCommand(input);
}


void Commands::Exit()
{
    setExit(true);
}


void Commands::Mkdir()
{
    if(m_Flag1 != "0")
    {
    std::string dirname = m_Flag1;
    CreateDirectory(m_currentPath, dirname);
    }
}

void Commands::Rmdir()
{
    if(m_Flag1 != "0")
    {
    std::string dirname = m_Flag1;
    DeleteDirectory(m_currentPath, dirname);
    }
}

void Commands::Rm()
{
    if(m_Flag1 != "0")
    {
    std::string filename = m_Flag1;
    DeleteFile(m_currentPath, filename);
    }
}

void Commands::Cd()
{
    if(m_Flag1 != "0" && m_Flag1 == ".." && m_currentPath != "/")
    {
        Directory* currentDir = navigateTo(m_currentPath);
        size_t strSizeToErase = currentDir->name.length() + 1;
        m_currentPath.erase(m_currentPath.size() - strSizeToErase);
    }
    else if(m_Flag1 != "0")
    {
        std::string newPath;
        if(m_currentPath == "/")
            newPath = m_currentPath + m_Flag1 + "/";
        else
            newPath = m_currentPath + m_Flag1 + "/";

        Directory* targetDir = navigateTo(newPath);
        if(targetDir)
        {
            m_currentPath = newPath;
            std::cout << "Changed directory to: [" << m_currentPath << "]\n";
        }
        else
        {
            std::cout << "Wrong path, try again\n";
        }
    }
    else if(m_currentPath == "/")
        std::cout << "You can't use this command while being at root\n";
    else
        std::cout << "Wrong path, try again\n";

}

void Commands::Ls()
{
    Directory* dir = navigateTo(m_currentPath);
    if(dir)
    {
        std::cout << "Listing contents of: [" << m_currentPath << "]\n";
        printf("\033[1;32m");
        for(auto const& folder : navigateTo(m_currentPath)->subdirectories)
            std::cout << folder.first << std::endl;
        printf("\033[1;35m");
        for(auto const& file : navigateTo(m_currentPath)->files)
            std::cout << file.first << std::endl;
        printf("\033[0;31m");

    }
    else
        std::cout << "Current path is invalid: [" << m_currentPath << "]\n";

}

void Commands::Pwd()
{
    std::cout << "Working directory: [" << m_currentPath << "]\n";
}

void Commands::Touch()
{
    if(m_Flag1 != "0")
    {
        CreateFile(m_currentPath, m_Flag1);
        std::cout << "created file named: [" << m_Flag1 << "] in directory: [" << m_currentPath << "]\n";
    }
    else
        std::cout << "Wrong filename: [" << m_Flag1 << "]\n";
    
}

void Commands::Cat()
{
    if(m_Flag1 != "0")
    {
        std::string content = ReadFile(m_currentPath, m_Flag1);
        printf("\033[1;33m");
        std::cout << content << std::endl;
        printf("\033[0;31m");
    }
    else
        std::cout << "Wrong filename: [" << m_Flag1 << "]\n";
}

void Commands::Echo()
{
    if(m_Flag1 != "0" && m_Flag2 != "0")
    {
        WriteFile(m_currentPath, m_Flag1, m_Flag2);
    }
    else
        std::cout << "Wrong flags!\n";
}

void Commands::Undo()
{

}