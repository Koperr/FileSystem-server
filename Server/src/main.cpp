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
        std::string action = req.get_arg("action");
        fs->cmd.m_Flag1 = req.get_arg("flag1");
        fs->cmd.m_Flag2 = req.get_arg("flag2");

        if(action == "pwd")
        {
            fs->cmd.Pwd();
            return std::make_shared<string_response>("Current working directory: [" + fs->m_currentPath + "]\n", 200);
        }
        else if(action == "ls")
        {
            fs->cmd.Ls();
            return std::make_shared<string_response>("Content of this dir:\n" + fs->cmd.listOfFiles, 200);
        }
        else if(action == "cat")
        {
            fs->cmd.Cat();
            return std::make_shared<string_response>(fs->cmd.content);
        }
        else if(action == "printlog")
        {
            fs->cmd.PrintLog();
            return std::make_shared<string_response>(fs->logContent);
        }
        else if(action == "p") // to jest do tego, zeby w kazdej lini przed inputem byla obecna sciezka (do celow wizualnych)
        {
            return std::make_shared<string_response>(fs->m_currentPath, 200);
        }
        else
        {
            return std::make_shared<string_response>("Failed to return sth\n", 400);
        }
    }

    std::shared_ptr<http_response> render_DELETE(const http_request& req) override 
    {
        std::string action = req.get_arg("action");
        fs->cmd.m_Flag1 = req.get_arg("flag1");

        if (action == "rm") 
        {
            fs->DeleteFile(fs->m_currentPath, fs->cmd.m_Flag1);
            return std::make_shared<string_response>("Deleted file named: " + fs->cmd.m_Flag1, 200);
        } else if (action == "rmdir") 
        {
            fs->DeleteDirectory(fs->m_currentPath, fs->cmd.m_Flag1);
            return std::make_shared<string_response>("Deleted dir named: " + fs->cmd.m_Flag1, 200);
        } else 
        {
            return std::make_shared<string_response>("Invalid action", 400);
        }

        return std::make_shared<string_response>("Success", 200);
    }

    std::shared_ptr<http_response> render_PUT(const http_request& req) override
    {
        std::string action = req.get_arg("action");
        fs->cmd.m_Flag1 = req.get_arg("flag1");
        fs->cmd.m_Flag2 = req.get_arg("flag2");

        if (action == "mv")
        {
            fs->cmd.Mv();
            return std::make_shared<string_response>("Changed name of file/dir to " + fs->cmd.m_Flag1, 200);
        } 
        else if (action == "echo") 
        {
            fs->cmd.Echo();
            return std::make_shared<string_response>("Overwritten file content", 200);
        }
        else if (action == "cd")
        {
            fs->cmd.Cd();
            return std::make_shared<string_response>("Changed dir", 200);
        }
        else if (action == "touch") 
        {
            fs->cmd.Touch();
            return std::make_shared<string_response>("Created file " + fs->cmd.m_Flag1 + "\n", 200);
        } 
        else if (action == "mkdir") 
        {
            fs->cmd.Mkdir();
            return std::make_shared<string_response>("Created directory " + fs->cmd.m_Flag1 + "\n", 200);
        } 
        else if (action == "undo")
        {
            fs->cmd.Undo();
            return std::make_shared<string_response>("Undo!", 200);
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

// TESTY

// curl "http://localhost:8080/filesystem?action=p"
// curl -X POST "http://localhost:8080/filesystem?action=mkdir&flag1=dupa&flag2=xd"
// curl -X PUT "http://localhost:8080/filesystem?action=cd&flag1=dupa&flag2=xd"
// curl "http://localhost:8080/filesystem?action=pwd"