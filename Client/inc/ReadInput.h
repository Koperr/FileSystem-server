#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>

#include <nlohmann/json.hpp>

class ReadInput
{
public:

    void CreateURL(const std::string& input);
    void SetCommand();
    std::string SendRequest(const std::string& url, const std::string& method);

    std::string m_Input;
    
    std::string m_Flag1;
    std::string m_Flag2;
    std::string m_Command;
private:
    void GetFlags(const std::string& input);
    void GetCommand(const std::string& input);

    //nlohmann::json flags;

    std::string m_URL;
    std::string response;

    std::vector<std::string> m_CommandList
    {
        "mkdir",
        "rmdir",
        "rm",
        "cd",
        "ls",
        "pwd",
        "touch",
        "cat",
        "echo",
        "undo",
        "mv",
        "printlog",
        "p"
    };
};