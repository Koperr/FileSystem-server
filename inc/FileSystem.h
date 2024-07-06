#pragma once

#include <iostream>
#include <string>
#include <map>
#include <sstream>

#include <stdlib.h>


struct File
{
    std::string name;
    std::string content;
};

struct Directory
{
    std::string name;
    std::map<std::string, Directory> subdirectories;
    std::map<std::string, File> files;
};

class FileSystem
{
public:
    static void setExit(bool b) { m_Exit = b; }

    void run();

    FileSystem();

    void CreateFile(const std::string& path, const std::string& filename);
    void DeleteFile(const std::string& path, const std::string& filename);

    void CreateDirectory(const std::string& path, const std::string& dirname);
    void DeleteDirectory(const std::string& path, const std::string& dirname);

    void WriteFile(const std::string& path, const std::string& filename, const std::string& content);
    std::string ReadFile(const std::string& path, const std::string& filename);
    
protected:
    std::string currentPath;

    Directory* navigateTo(const std::string& path);

private:
    Directory root;


    static bool m_Exit;

    std::string m_Input;
};
