#pragma once

#include <string>
#include <map>

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
    //std::string path = "/";
};

