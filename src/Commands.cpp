#include "Commands.h"

Commands::Commands()
    : commandMap{
        {"exit",  [this]() {Exit(); }},
        {"mkdir", [this]() {Mkdir();}},
        {"rmdir", [this]() {Rmdir();}},
        {"cd",    [this]() {Cd();   }},
        {"ls",    [this]() {Ls();   }},
        {"pwd",   [this]() {Pwd();  }},
        {"touch", [this]() {Touch();}},
        {"cat",   [this]() {Cat();  }},
        {"echo",  [this]() {Echo(); }}
    }
{
}

void Commands::getFlag(const std::string& str)
{
    int spacePos = str.find(" ");
    int lengh = str.length() - spacePos;

    // If there is no spacepos, sets the value of flag to substr of everything exept the first word
    if(spacePos != std::string::npos)
        m_Flag = str.substr(spacePos + 1, lengh);
    else
        m_Flag = "0";

    // If there is forbidden symbol in the value, it sets the value of flag to "0"
    if(m_Flag.find(" ") == std::string::npos && m_Flag.find("\n") == std::string::npos)
    {
        return;
    }
    else
    {
        m_Flag = "0";
        std::cout << "[ERROR] Wrong flag\n";
    }
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
}

void Commands::checkInput(const std::string& input)
{
    m_Input = input;

    getFlag(input);

    getCommand(input);
}


void Commands::Exit()
{
    setExit(true);
}

void Commands::Mkdir()
{
    if(m_Flag != "0")
    {
    std::string dirname = m_Flag;
    CreateDirectory(currentPath, dirname);
    }
}

void Commands::Rmdir()
{
    if(m_Flag != "0")
    {
    std::string dirname = m_Flag;
    DeleteDirectory(currentPath, dirname);
    }
}

void Commands::Cd()
{
    if(m_Flag != "0")
    {
    if (navigateTo(currentPath)->subdirectories.find(m_Flag) != navigateTo(currentPath)->subdirectories.end())
    {
        if(currentPath != "/")
        {
            currentPath += "/" + m_Flag + "/";
            std::cout << m_Flag;
        }
        else
        {
            currentPath += m_Flag + "/";
        }
    }
    else
        std::cout << "Wrong path, try again\n";
    }
}

void Commands::Ls()
{
    for(auto const& x : navigateTo(currentPath)->subdirectories)
        std::cout << x.first << std::endl;

    //for(auto dirPair : navigateTo(currentPath)->subdirectories)
    //    std::cout << dirPair.first << std::endl;
}

void Commands::Pwd()
{
    std::cout << "Working directory: " << currentPath << std::endl;
}

void Commands::Touch()
{
    std::cout << "COMMAND: [Touch]\n";
}

void Commands::Cat()
{
    std::cout << "COMMAND: [Cat]\n";
}

void Commands::Echo()
{
    std::cout << "COMMAND: [Echo]\n";
}