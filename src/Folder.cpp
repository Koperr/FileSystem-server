#include "Folder.h"

Folder::Folder(const std::string path, const std::string& name) : m_Name(name), m_FolderPath(path)
{

}

Folder::~Folder()
{
    
}

void Folder::createFile(const std::string& name, const std::string& path)
{
    this->dirTree.emplace_back(path, name);
}

void Folder::createFolder()
{

}
