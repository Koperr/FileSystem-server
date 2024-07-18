#include <memory>

#include <httpserver.hpp>

#include "FileSystem.h"

using namespace httpserver;
using json = nlohmann::json;

class FileSystemHandler : public http_resource
{
public:
    FileSystemHandler(FileSystem* fs) : fs(fs) {}

    std::shared_ptr<http_response> render_GET(const http_request& req) override
    {
        std::string path = req.get_arg("path");
        if (path.empty()) {
            path = "/";
        }

        std::cout << "Recieved GET request: path[" << path << "]\n";

        auto jsonResponse = fs->ToJson(path);
        if (!jsonResponse.empty()) {
            return std::shared_ptr<http_response>(new string_response(jsonResponse.dump(), 200, "application/json"));
        } else {
            return std::shared_ptr<http_response>(new string_response("Directory not found\n", 404));
        }
    }

    std::shared_ptr<http_response> render_POST(const http_request& req) override 
    {

        std::string action = req.get_arg("action");
        std::string path = req.get_arg("path");
        std::string name = req.get_arg("name");

        std::cout << "Recieved POST request: action[" << action << "], path[" << path << "], name[" << name << "]\n";

        if (action == "create_file") {
            fs->CreateFile(path, name);
        } else if (action == "create_dir") {
            fs->CreateDirectory(path, name);
        } else if (action == "write_file") {
            std::string content = req.get_arg("content");
            fs->WriteFile(path, name, content);
        } else {
            return std::make_shared<string_response>("Invalid action", 400);
        }

        return std::make_shared<string_response>("Success", 200);
    }

    std::shared_ptr<http_response> render_DELETE(const http_request& req) override 
    {

        std::string action = req.get_arg("action");
        std::string path = req.get_arg("path");
        std::string name = req.get_arg("name");

        std::cout << "Recieved DELETE request: action[" << action << "], path[" << path << "], name[" << name << "]\n";

        if (action == "delete_file") {
            fs->DeleteFile(path, name);
        } else if (action == "delete_dir") {
            fs->DeleteDirectory(path, name);
        } else {
            return std::make_shared<string_response>("Invalid action", 400);
        }

        return std::make_shared<string_response>("Success", 200);
    }

    std::shared_ptr<http_response> render_PUT(const http_request& req) override
    {
        std::string action = req.get_arg("action");
        std::string path = req.get_arg("path");
        std::string name = req.get_arg("name");

        std::cout << "Recieved PUT request: action[" << action << "], path[" << path << "], name[" << name << "]\n";

        if (action == "change_dir_name"){

        } else if (action == "change_file_name"){

        } else if (action == "change_file_content"){

        }
        return std::make_shared<string_response>("Succes\n", 200);
    }

private:
    FileSystem* fs;
};


int main()
{
    std::cout << "Project is running\n";
    FileSystem fs;
    webserver ws = create_webserver(8080);
    FileSystemHandler fsh(&fs);


    ws.register_resource("/filesystem", &fsh, true);
    std::cout << "Serwer działa na porcie 8080" << std::endl;
    ws.start(true);

    std::cout << "Project stopped running\n";
    //fs.Run();
}

///////////////////////////////// GET /////////////////////////////////

// curl "http://localhost:8080/filesystem?path=/"

///////////////////////////////// POST /////////////////////////////////

// tworzenie pliku
// curl -X POST "http://localhost:8080/filesystem?action=create_file&path=/&name=newfile.txt"

// tworzenie katalogu
// curl -X POST "http://localhost:8080/filesystem?action=create_dir&path=/&name=newfile.txt"

// zapis do pliku
// curl -X POST "http://localhost:8080/filesystem?action=write_file&path=/&name=newfile.txt&content=Hello%20World"

///////////////////////////////// DELETE /////////////////////////////////

// usuwanie katalogu
// curl -X DELETE "http://localhost:8080/filesystem?action=delete_dir&path=/&name=newfile.txt"

// usuwanie pliku
// curl -X DELETE "http://localhost:8080/filesystem?action=delete_file&path=/&name=newfile.txt"