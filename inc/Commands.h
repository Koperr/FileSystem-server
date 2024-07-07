#pragma once

#include "FileSystem.h"

#include <map>
#include <functional>


class Commands : public FileSystem
{
public:
    Commands()
    : commandMap{
        {"exit",  [this]() {Exit(); }},
        {"mkdir", [this]() {Mkdir();}},
        {"rmdir", [this]() {Rmdir();}},
        {"rm",    [this]() {Rm();   }},
        {"cd",    [this]() {Cd();   }},
        {"ls",    [this]() {Ls();   }},
        {"pwd",   [this]() {Pwd();  }},
        {"touch", [this]() {Touch();}},
        {"cat",   [this]() {Cat();  }},
        {"echo",  [this]() {Echo(); }},
        {"undo",  [this]() {Undo(); }}
    } {}

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


private:
    std::map<std::string, std::function<void()>> commandMap;
    
    std::string m_Command;
    std::string m_Flag1;
    std::string m_Flag2;
};