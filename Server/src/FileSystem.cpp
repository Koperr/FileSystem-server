#include "FileSystem.h"

Originator originator;
CareTaker caretaker;


void FileSystem::Run()
{
    while(!m_Exit)
    {
        // https://man7.org/linux/man-pages/man5/terminal-colors.d.5.html
        printf("\033[36;1m");
        std::cout << m_currentPath;
        printf("\033[35m $ \033[0;36m");
        std::getline(std::cin, m_Input);
        printf("\033[31m");
        cmd.CheckInput(m_Input);
    }
}


void FileSystem::CreateFile(const std::string& path, const std::string& filename)
{
    Directory* dir = NavigateTo(path);
    if (dir)
    {
        originator.setState(*dir);
        caretaker.AddMemento(originator.SaveStateToMemento());

        dir->files[filename] = {filename, ""};
    }
}
void FileSystem::DeleteFile(const std::string& path, const std::string& filename)
{
    Directory* dir = NavigateTo(path);
    if (dir)
    {
        originator.setState(root);
        caretaker.AddMemento(originator.SaveStateToMemento());

        dir->files.erase(filename);
    }
}


void FileSystem::CreateDirectory(const std::string& path, const std::string& dirname)
{
    Directory* dir = NavigateTo(path);
    if(dir)
    {
        originator.setState(root);
        caretaker.AddMemento(originator.SaveStateToMemento());

        dir->subdirectories[dirname] = {dirname};
        //dir->subdirectories[dirname].path = path + dirname + "/";
    }
}
void FileSystem::DeleteDirectory(const std::string& path, const std::string& dirname)
{
    Directory* dir = NavigateTo(path);
    if(dir)
    {
        originator.setState(*dir);
        caretaker.AddMemento(originator.SaveStateToMemento());

        dir->subdirectories.erase(dirname);
    }
}


void FileSystem::WriteFile(const std::string& path, const std::string& filename, const std::string& content)
{
    Directory* dir = NavigateTo(path);
    if(dir && dir->files.find(filename) != dir->files.end())
    {
        originator.setState(*dir);
        caretaker.AddMemento(originator.SaveStateToMemento());
        
        dir->files[filename].content = content;
    }
}


std::string FileSystem::ReadFile(const std::string& path, const std::string& filename)
{
    Directory* dir = NavigateTo(path);
    if(dir && dir->files.find(filename) != dir->files.end())
    {
        return dir->files[filename].content;
    }
    return "";
}



Directory* FileSystem::NavigateTo(const std::string& path)
{
    Directory* current = &root;
    if(path == "/") return current;

    std::istringstream iss(path);
    std::string token;
    while (std::getline(iss, token, '/'))
    {
        if (!token.empty())
        {
            if(current->subdirectories.find(token) != current->subdirectories.end())
            {
                current = &current->subdirectories[token];
            }
            else
            {
                std::cout << "Directory not found: [" << token << "] in path: [" << path << "]\n";
            return nullptr;
            }
        }
    }
    return current;
}

nlohmann::json FileSystem::ToJson(const std::string& path)
{
    Directory* dir = NavigateTo(path);
    if(!dir) return {};

    nlohmann::json j;
    for(const auto& subdir : dir->subdirectories)
    {
        j["directories"].push_back(subdir.first);
    }
    for(const auto& file : dir->files)
    {
        j["directories"].push_back(file.first);
    }

    return j;
}

void FileSystem::Log(const std::string& content)
{
    std::fstream file("Log.txt", std::ios::out | std::ios::app);

    if(!file.is_open())
    {
        std::cout << "Couldnt open Log.txt\n";
        return;
    }

    file << std::endl << content << std::endl;

    file.close();
}

void FileSystem::PrintLog()
{
    std::fstream file("Log.txt", std::ios::in);

    if(!file.is_open())
    {
        std::cout << "Couldnt open Log.txt\n";
        return;
    }

    logContent = "";


    std::string line;

    while(std::getline(file, line))
    {
        logContent += line;
    }
    std::cout << logContent << std::endl;
}
