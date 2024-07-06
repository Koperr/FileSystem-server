#pragma once

#include "FileSystem.h"

#include <map>
#include <functional>


class Commands : public FileSystem
{
public:
    Commands();
    void getCommand(const std::string& str);
    std::string getFlag(const std::string& str);

    void Exit();
    void Mkdir();
    void Rmdir();
    void Cd();
    void Ls();
    void Pwd();
    void Touch();
    void Cat();
    void Echo();

    void checkInput(const std::string& input);

private:
    std::map<std::string, std::function<void()>> commandMap;

    std::string m_Input;
    
    std::string m_Command;
    std::string m_Flag;
    
};