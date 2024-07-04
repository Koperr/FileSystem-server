#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Folder.h"

class FileSystem
{
public:
    void run();

    FileSystem() : m_Exit(false), m_CurrentPath("Home/"){};

    std::string m_CurrentPath;
    //std::vector<Folder> dirTree;
private:
    std::string m_Input;
    bool m_Exit;
};
