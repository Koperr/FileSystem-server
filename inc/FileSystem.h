#pragma once

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fstream>

#include <nlohmann/json.hpp>

#include "Commands.h"
#include "Memento.h"

extern Originator originator;
extern CareTaker caretaker;

class FileSystem
{
public:

    FileSystem()
        :cmd(this)
    {
        m_Exit = false;
        root.name = "/";
        m_currentPath = root.name;
    }
    ~FileSystem()
    {
        std::fstream file("Log.txt", std::ios::out);

        if(!file.is_open())
        {
            std::cout << "Couldnt open Log.txt\n";
            return;
        }

        file << std::endl << "" << std::endl;

        file.close();
    }

    void SetExit(bool b) { m_Exit = b; }
    void Run();

    void CreateFile(const std::string& path, const std::string& filename);
    void DeleteFile(const std::string& path, const std::string& filename);
    void CreateDirectory(const std::string& path, const std::string& dirname);
    void DeleteDirectory(const std::string& path, const std::string& dirname);
    void WriteFile(const std::string& path, const std::string& filename, const std::string& content);
    std::string ReadFile(const std::string& path, const std::string& filename);
    Directory* NavigateTo(const std::string& path);

    nlohmann::json ToJson(const std::string& path);

    void Log(const std::string& content);
    void PrintLog();


    std::string m_currentPath;
    std::string m_Input;
    Directory root;

protected:

private:
    bool m_Exit;

    std::fstream file;
    std::string logContent;

    Commands cmd;

};
