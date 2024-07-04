#pragma once

#include "FileSystem.h"

#include <map>
#include <functional>



class Commands : public FileSystem
{
public:
    Commands();

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
    
};