#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Folder.h"

class FileSystem
{
public:

    void run();

    std::string currentPath;

    FileSystem() : m_Exit(false), currentPath("Home/") {};
private:
    std::string m_Input;
    bool m_Exit;
};

class Folder : public FileSystem
{
public:
    Folder(const std::string& name, const std::string& path);
private:

};