#include "Commands.h"

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
        std::cout << "[ERROR] There is no command named [" << m_Command << "], try again\n";
}

std::string Commands::getFlag(const std::string& str)
{
    int spacePos = str.find(" ");
    int lengh = str.length() - spacePos;

    // set the "flag" to the "str" without the first word
    if(spacePos != std::string::npos)
        m_Flag = str.substr(spacePos + 1, lengh);


    if(m_Flag.find(" ") == std::string::npos && m_Flag.find("\n") == std::string::npos)
    {
        return m_Flag;
    }
    else
    {
        std::cout << "[ERROR] Wrong flag used\n";
        return "0";
    }
}

void Commands::checkInput(const std::string& input)
{
    m_Input = input;

    getFlag(input);

    getCommand(input);
    
}

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

void Commands::Exit()
{
    setExit(true);
}

void Commands::Mkdir()
{
    std::string dirname = getFlag(m_Input);
    CreateDirectory(currentPath, dirname);
}

void Commands::Rmdir()
{
    std::string dirname = getFlag(m_Input);
    DeleteDirectory(currentPath, dirname);
}

void Commands::Cd()
{
    if (navigateTo(currentPath)->subdirectories.find(getFlag(m_Input)) != navigateTo(currentPath)->subdirectories.end())
    {
        if(currentPath != "/")
        {
            this->currentPath += "/" + getFlag(m_Input);
            std::cout << getFlag(m_Input);
        }
        else
        {
            this->currentPath += getFlag(m_Input);

        }
    }
    else { std::cout << "Wrong path, try again\n"; }
}

void Commands::Ls()
{
    for(auto dirPair : navigateTo(currentPath)->subdirectories)
        std::cout << dirPair.first << std::endl;
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