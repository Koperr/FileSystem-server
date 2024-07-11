#pragma once

#include <map>
#include <iostream>
#include <string>
#include <functional>

#include "Memento.h"

class FileSystem; // Forward dec

class Commands
{
public:
    Commands(FileSystem* fs);

    void checkInput(const std::string& input);
    void getCommand(const std::string& str);
    void getFlags(const std::string& str);

    void Exit();
    void Mkdir();
    void Rmdir();
    void Rm();
    void Cd();
    void Ls();
    void Pwd();
    void Touch();
    void Cat();
    void Echo();
    void Undo();
    void Mv();
    void PrintLog();


    std::string m_currentpath;
private:
    std::map<std::string, std::function<void()>> commandMap;
    

    std::string m_Command;
    std::string m_Flag1;
    std::string m_Flag2;

    FileSystem* fs;
};