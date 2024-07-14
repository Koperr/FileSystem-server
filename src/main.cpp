#include <memory>

#include <httpserver.hpp>

#include "FileSystem.h"

using namespace httpserver;
using json = nlohmann::json;

class FileSystemHandler : public http_resource
{
public:
    FileSystemHandler(FileSystem* fs) : filesystem(fs) {}

    std::shared_ptr<http_response> render_GET(const http_request& req) override 
    {
        std::string path = req.get_arg("path");
        if (path.empty()) {
            path = "/";
        }

        auto jsonResponse = filesystem->ToJson(path);
        if (!jsonResponse.empty()) {
            return std::shared_ptr<http_response>(new string_response(jsonResponse.dump(), 200, "application/json"));
        } else {
            return std::shared_ptr<http_response>(new string_response("Directory not found", 404));
        }
    }

    std::shared_ptr<http_response> render_POST(const http_request& req) override {
        std::string action = req.get_arg("action");
        std::string path = req.get_arg("path");
        std::string name = req.get_arg("name");

        if (action == "create_file") {
            filesystem->CreateFile(path, name);
        } else if (action == "create_dir") {
            filesystem->CreateDirectory(path, name);
        } else if (action == "write_file") {
            std::string content = req.get_arg("content");
            filesystem->WriteFile(path, name, content);
        } else {
            return std::make_shared<string_response>("Invalid action", 400);
        }

        return std::make_shared<string_response>("Success", 200);
    }

    std::shared_ptr<http_response> render_DELETE(const http_request& req) override {
        std::string action = req.get_arg("action");
        std::string path = req.get_arg("path");
        std::string name = req.get_arg("name");

        if (action == "delete_file") {
            filesystem->DeleteFile(path, name);
        } else if (action == "delete_dir") {
            filesystem->DeleteDirectory(path, name);
        } else {
            return std::make_shared<string_response>("Invalid action", 400);
        }

        return std::make_shared<string_response>("Success", 200);
    }

private:
    FileSystem* filesystem;
};


int main()
{
    FileSystem fsys;

    fsys.Run();
}

// przed zabawa w gita 1