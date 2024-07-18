#pragma once

#include <string>
#include <iostream>

#include <curl/curl.h>

class FileSystem;

class CurlMethods
{
public:
    CurlMethods(FileSystem* filesystem) : fs(filesystem) {}

    void PerformGetRequest(const std::string& url);
    void PerformPostRequest(const std::string& url);
    void PerformPutRequest(const std::string& url);
    void PerformDeleteRequest(const std::string& url);

private:
    FileSystem* fs;
};