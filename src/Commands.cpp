#include "Commands.h"

void Commands::checkInput(const std::string& input)
{
    std::string temp_str;
    int spacePos = input.find(" ");
    // if found space, assinging the command to spacePos
    if(spacePos != std::string::npos)
        temp_str = input.substr(0, spacePos);
    else if(input == "")
        return;
    else
        temp_str = input;
    // checking if temp_str is equal to one of the command names
    if(commandMap.find(temp_str) != commandMap.end())
    {
        auto function = commandMap[temp_str];
        function();
    }
    else if(temp_str == "")
        return;
    else
        std::cout << "There is no command named '" << temp_str << "', try again\n";
}

Commands::Commands()
    : commandMap{
        {"mkdir", [this]() {Mkdir();         }},
        {"rmdir", [this]() {Rmdir();         }},
        {"cd",    [this]() {Cd();            }},
        {"ls",    [this]() {Ls();            }},
        {"pwd",   [this]() {Pwd();           }},
        {"touch", [this]() {Touch();         }},
        {"cat",   [this]() {Commands::Cat(); }},
        {"echo",  [this]() {Commands::Echo();}}
    }
{
    
}

void Commands::Mkdir()
{
    std::cout << "Used command: Mkdir\n";
}
void Commands::Rmdir()
{
    std::cout << "Used command: Rmdir\n";
}
void Commands::Cd()
{
    std::cout << "Used command: Cd\n";
}
void Commands::Ls()
{
    std::cout << "Used command: Ls\n";
}
void Commands::Pwd()
{
    std::cout << "Used command: Pwd\n";
    std::cout << "Working directory: " << currentPath << std::endl;
}
void Commands::Touch()
{
    std::cout << "Used command: Touch\n";
}
void Commands::Cat()
{
    std::cout << "Used command: Cat\n";
}
void Commands::Echo()
{
    std::cout << "Used command: Echo\n";
}