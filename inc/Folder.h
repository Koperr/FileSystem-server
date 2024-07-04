#pragma once
#include "FileSystem.h"

class Folder
{
public:
    Folder(const std::string path, const std::string& name);
    ~Folder();

    void createFile(const std::string& name, const std::string& path);
    void createFolder();

    std::string m_Name;
    std::string m_FolderPath;
    
private:
    std::vector<Folder> dirTree;
};