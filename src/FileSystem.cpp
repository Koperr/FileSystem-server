#include "FileSystem.h"
#include "Commands.h"

Commands cmd;

bool FileSystem::m_Exit = false;


FileSystem::FileSystem()
{
    root.name = "/";
    currentPath = root.name;
}


void FileSystem::run()
{
    while(!m_Exit)
    {
        // printf("\033[36;1m"); https://man7.org/linux/man-pages/man5/terminal-colors.d.5.html
        printf("\033[36m");
        //std::cout << currentPath;
        std::cout << cmd.currentPath;
        std::getline(std::cin, m_Input);
        cmd.checkInput(m_Input);
    }
    
}


void FileSystem::CreateFile(const std::string& path, const std::string& filename)
{
    Directory* dir = navigateTo(path);
    if (dir)
    {
        dir->files[filename] = {filename, ""};
    }
}
void FileSystem::DeleteFile(const std::string& path, const std::string& filename)
{
    Directory* dir = navigateTo(path);
    if (dir)
    {
        dir->files.erase(filename);
    }
}


void FileSystem::CreateDirectory(const std::string& path, const std::string& dirname)
{
    Directory* dir = navigateTo(path);
    if(dir)
    {
        dir->subdirectories[dirname] = {dirname};
    }
}
void FileSystem::DeleteDirectory(const std::string& path, const std::string& dirname)
{
    Directory* dir = navigateTo(path);
    if(dir)
    {
        dir->subdirectories.erase(dirname);
    }
}


void FileSystem::WriteFile(const std::string& path, const std::string& filename, const std::string& content)
{
    Directory* dir = navigateTo(path);
    if(dir && dir->files.find(filename) != dir->files.end())
    {
        dir->files[filename].content = content;
    }
}


std::string FileSystem::ReadFile(const std::string& path, const std::string& filename)
{
    Directory* dir = navigateTo(path);
    if(dir && dir->files.find(filename) != dir->files.end())
    {
        return dir->files[filename].content;
    }
    return "";
}


Directory* FileSystem::navigateTo(const std::string& path)
{
    Directory* current = &root;
    if(path == "/") return current;

    std::istringstream iss(path);
    std::string token;
    while (std::getline(iss, token, '/'))
    {
        if (!token.empty() && current->subdirectories.find(token) != current->subdirectories.end())
        {
            current = &current->subdirectories[token];
        }
        else
        {
            return nullptr;
        }
    }
    return current;
}
