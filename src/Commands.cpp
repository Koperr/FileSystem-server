#include "Commands.h"

void Commands::checkCommand(const std::string& str)
{
    // setting "command" to the first word
    std::string command;
    int spacePos = str.find(" ");
    if(spacePos != std::string::npos)
        command = str.substr(0, spacePos);
    else if(str == "")
        return;
    else
        command = str;

    // checking if "command" is a command
    if(commandMap.find(command) != commandMap.end())
    {
        auto function = commandMap[command];
        function(command);
    }
    else if(command == "")
        return;
    else
        std::cout << "[ERROR] There is no command named [" << command << "], try again\n";
}

std::string Commands::findFlag(const std::string& str)
{
    std::string flag;
    int spacePos = str.find(" ");
    int lengh = str.length() - spacePos;

    // set the "flag" to the "str" without the first word
    if(spacePos != std::string::npos)
        flag = str.substr(spacePos + 1, lengh);


    if(flag.find(" ") == std::string::npos && flag.find("\n") == std::string::npos)
    {
        std::cout << "FLAG: [" << flag << "]\n";
        return flag;
    }
    else
    {
        std::cout << "[ERROR] Wrong flag used\n";
        return "0";
    }
}

void Commands::checkInput(const std::string& input)
{
    checkCommand(input);
    
    std::string flag = findFlag(input);
}

Commands::Commands()
    : commandMap{
        {"exit",  [this](const std::string& flag) {Exit(flag); }},
        {"mkdir", [this](const std::string& flag) {Mkdir(flag);}},
        {"rmdir", [this](const std::string& flag) {Rmdir(flag);}},
        {"cd",    [this](const std::string& flag) {Cd(flag);   }},
        {"ls",    [this](const std::string& flag) {Ls(flag);   }},
        {"pwd",   [this](const std::string& flag) {Pwd(flag);  }},
        {"touch", [this](const std::string& flag) {Touch(flag);}},
        {"cat",   [this](const std::string& flag) {Cat(flag);  }},
        {"echo",  [this](const std::string& flag) {Echo(flag); }}
    }
{
    
}

void Commands::Exit(const std::string& flag)
{
    std::cout << "COMMAND: [Exit]\n";
}
void Commands::Mkdir(const std::string& flag)
{
    std::cout << "COMMAND: [Mkdir]\n";
}
void Commands::Rmdir(const std::string& flag)
{
    std::cout << "COMMAND: [Rmdir]\n";
}
void Commands::Cd(const std::string& flag)
{
    std::cout << "COMMAND: [Cd]\n";
}
void Commands::Ls(const std::string& flag)
{
    std::cout << "COMMAND: [Ls]\n";
}
void Commands::Pwd(const std::string& flag)
{
    std::cout << "COMMAND: [Pwd]\n";
    std::cout << "Working directory: " << m_CurrentPath << std::endl;
}
void Commands::Touch(const std::string& flag)
{
    std::cout << "COMMAND: [Touch]\n";
}
void Commands::Cat(const std::string& flag)
{
    std::cout << "COMMAND: [Cat]\n";
}
void Commands::Echo(const std::string& flag)
{
    std::cout << "COMMAND: [Echo]\n";
}