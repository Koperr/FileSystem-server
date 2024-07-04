#pragma once

#include "FileSystem.h"
#include "Folder.h"

#include <map>
#include <functional>


class Commands : public FileSystem
{
public:
    Commands();
    void checkCommand(const std::string& str);
    std::string findFlag(const std::string& str);

    void Exit(const std::string& flag);
    void Mkdir(const std::string& flag);
    void Rmdir(const std::string& flag);
    void Cd(const std::string& flag);
    void Ls(const std::string& flag);
    void Pwd(const std::string& flag);
    void Touch(const std::string& flag);
    void Cat(const std::string& flag);
    void Echo(const std::string& flag);

    void checkInput(const std::string& input);

private:
    std::map<std::string, std::function<void(const std::string& str)>> commandMap;
    
};