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

    void CheckInput(const std::string& input);
    void GetCommand(const std::string& str);
    void GetFlags(const std::string& str);

    bool CheckForbiddenWords(const std::string& str);

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
    
    std::vector<std::string> v_ForbiddenWords { "/", "\\" };
    std::string m_Command;
    std::string m_Flag1;
    std::string m_Flag2;

    FileSystem* fs;
};