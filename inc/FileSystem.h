#pragma once

#include <iostream>
#include <string>
#include <vector>

class FileSystem
{
public:
    FileSystem() : m_Exit(false), currentPath("Home") {};

    void run();


    std::string currentPath;

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