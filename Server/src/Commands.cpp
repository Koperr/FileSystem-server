#include "Commands.h"
#include "FileSystem.h"

Commands::Commands(FileSystem* filesystem)
    :   commandMap{
        {"exit",    [this]() {Exit();    }},
        {"mkdir",   [this]() {Mkdir();   }},
        {"rmdir",   [this]() {Rmdir();   }},
        {"rm",      [this]() {Rm();      }},
        {"cd",      [this]() {Cd();      }},
        {"ls",      [this]() {Ls();      }},
        {"pwd",     [this]() {Pwd();     }},
        {"touch",   [this]() {Touch();   }},
        {"cat",     [this]() {Cat();     }},
        {"echo",    [this]() {Echo();    }},
        {"undo",    [this]() {Undo();    }},
        {"mv",      [this]() {Mv();      }},
        {"printlog",[this]() {PrintLog();}}
    }, fs(filesystem)
    {
    }


void Commands::GetFlags(const std::string& str)
{
    std::string firstFlag;
    std::string substring;
    size_t spacePos = str.find(" ");
    int length = str.length() - spacePos;

    // If there is no spacepos, sets the value of flag to substr of everything exept the first word
    if(spacePos != std::string::npos)
    {
        substring = str.substr(spacePos + 1, length);
        // now "substring" is separated from the command

        spacePos = substring.find(" ");
        length = substring.length() - spacePos;
        if(spacePos == std::string::npos)
        {
            m_Flag1 = substring;
            m_Flag2 = "0";
        }
        else if(spacePos != std::string::npos)
        {
            m_Flag1 = substring.substr(0, spacePos); // first word after command
            m_Flag2 = substring.substr(spacePos + 1, substring.size() - spacePos - 1); // everything else beyond
        }
    }
    else
        {
            m_Flag1 = "0";
            m_Flag2 = "0";
        }
    //std::cout << "Flag 1 [" << m_Flag1 << "]\n";
    //std::cout << "Flag 2 [" << m_Flag2 << "]\n";

}

void Commands::GetCommand(const std::string& str)
{
    size_t spacePos = str.find(" ");

    if(spacePos != std::string::npos)
        m_Command = str.substr(0, spacePos);
    else if(str == "")
        return;
    else
        m_Command = str;

    // checking if "command" is a command
    if(commandMap.find(m_Command) != commandMap.end())
    {
        auto function = commandMap[m_Command];
        function();
    }
    else if(m_Command == "")
        return;
    else
        std::cout << "[ERROR] Wrong command [" << m_Command << "]\n";
    
    //std::cout << "Command [" << m_Command << "]\n"; 
}

void Commands::CheckInput(const std::string& input)
{
    fs->m_Input = input;

    GetFlags(input);

    GetCommand(input);
}

bool Commands::CheckForbiddenWords(const std::string& str)
{
    for(auto it : v_ForbiddenWords)
    {
        if(str.find(it) == std::string::npos)
            return true;
        else
            return false;
    }
    return false;
}

/*/////////////// COMMAND DECLARATIONS \\\\\\\\\\\\\\\*/

void Commands::Exit()
{
    fs->SetExit(true);
}


void Commands::Mkdir()
{
    if(m_Flag1 != "0"  && CheckForbiddenWords(m_Flag2))
    {
    fs->Log("Made directory named: [" + m_Flag1 + "] in [" + m_currentpath + "]");
    std::string dirname = m_Flag1;
    fs->CreateDirectory(fs->m_currentPath, dirname);
    }
}

void Commands::Rmdir()
{
    if(m_Flag1 != "0")
    {
    fs->Log("Removed directory named: [" + m_Flag1 + "] in [" + m_currentpath + "]");
    std::string dirname = m_Flag1;
    fs->DeleteDirectory(fs->m_currentPath, dirname);
    }
}

void Commands::Rm()
{
    if(m_Flag1 != "0")
    {
    fs->Log("Removed File named: [" + m_Flag1 + "] in [" + m_currentpath + "]");
    std::string filename = m_Flag1;
    fs->DeleteFile(fs->m_currentPath, filename);
    }
}

void Commands::Cd()
{
    std::string tempStr1 = m_currentpath;
    if(m_Flag1 != "0" && m_Flag1 == ".." && fs->m_currentPath != "/")
    {
        Directory* currentDir = fs->NavigateTo(fs->m_currentPath);
        size_t strSizeToErase = currentDir->name.length() + 1;
        fs->m_currentPath.erase(fs->m_currentPath.size() - strSizeToErase);
        fs->Log("Changed directory from: [" + tempStr1 + "] to [" + m_currentpath + "]");
    }
    else if(m_Flag1 != "0")
    {
        std::string newPath;
        if(fs->m_currentPath == "/")
        {
            newPath = fs->m_currentPath + m_Flag1 + "/";
        }
        else
        {
            newPath = fs->m_currentPath + m_Flag1 + "/";
        }

        Directory* targetDir = fs->NavigateTo(newPath);
        if(targetDir)
        {
            fs->m_currentPath = newPath;
            std::cout << "Changed directory to: [" << fs->m_currentPath << "]\n";
            fs->Log("Changed directory from: [" + tempStr1 + "] to [" + m_currentpath + "]");
        }
        else
        {
            std::cout << "Wrong path, try again\n";
        }
    }
    else if(fs->m_currentPath == "/")
        std::cout << "You can't use this command while being at root\n";
    else
        std::cout << "Wrong path, try again\n";

}

void Commands::Ls()
{
    Directory* dir = fs->NavigateTo(fs->m_currentPath);
    if(dir)
    {
        listOfFiles = "";
        std::cout << "Listing contents of current dir: [" << fs->m_currentPath << "]\n";
        printf("\033[1;32m");
        listOfFiles += "\033[1;32m";
        for(auto const& folder : dir->subdirectories)
        {
            std::cout << folder.first << std::endl;
            listOfFiles += folder.first + "\n";
        }
        printf("\033[1;35m");
        listOfFiles += "\033[1;35m";
        for(auto const& file : dir->files)
        {
            std::cout << file.first << std::endl;
            listOfFiles += file.first + "\n";
        }
        listOfFiles += "\033[0m";
        printf("\033[0;31m");

        fs->Log("Listed content of [" + fs->m_currentPath + "]");
    }
    else
        std::cout << "Current path is invalid: [" << fs->m_currentPath << "]\n";

}

void Commands::Pwd()
{
    std::cout << "Working directory: [" << fs->m_currentPath << "]\n";
    fs->Log("Printed working directory: [" + fs->m_currentPath + "]");
}

void Commands::Touch()
{
    if(m_Flag1 != "0" && CheckForbiddenWords(m_Flag2))
    {
        fs->CreateFile(fs->m_currentPath, m_Flag1);
        std::cout << "created file named: [" << m_Flag1 << "] in directory: [" << fs->m_currentPath << "]\n";
        fs->Log("Created file named: [" + m_Flag1 + "] in [" + m_currentpath + "]");
    }
    else
        std::cout << "Wrong filename: [" << m_Flag1 << "]\n";
    
}

void Commands::Cat()
{
    if(m_Flag1 != "0")
    {
        std::string content = fs->ReadFile(fs->m_currentPath, m_Flag1);
        printf("\033[1;33m");
        std::cout << content << std::endl;
        this->content = content;
        printf("\033[0;31m");
        fs->Log("Printed content of file: [" + m_Flag1 + "]");
    }
    else
        std::cout << "Wrong filename: [" << m_Flag1 << "]\n";
}

void Commands::Echo()
{
    if(m_Flag1 != "0" && m_Flag2 != "0")
    {
        fs->WriteFile(fs->m_currentPath, m_Flag1, m_Flag2);
        fs->Log("Writed tofile named: [" + m_Flag1 + "] in: [" + m_currentpath + "], the new content is: [" + m_Flag2 + "]");
    }
    else
        std::cout << "Wrong flags!\n";
}

void Commands::Undo()
{
    if(caretaker.mementoList.size() > 0)
    {
        originator.GetStateFromMemento(caretaker.GetMemento(caretaker.mementoList.size() - 1));
        fs->root = originator.getState();

        std::cout << "Undo operation performed\n";
        caretaker.mementoList.pop_back();

        fs->Log("Used UNDO operation");
    }
    else
    {
        std::cout << "No operation to undo\n";
    }
}

void Commands::Mv()
{

    Directory* dir = fs->NavigateTo(fs->m_currentPath);
    if(dir && m_Flag1 != "0" && m_Flag2 != "0")
    {
        std::cout << "command mv\n";

        auto subdirIt = dir->subdirectories.find(m_Flag1);
        if(subdirIt != dir->subdirectories.end())
        {
            Directory subdir = subdirIt->second;
            subdir.name = m_Flag2;
            dir->subdirectories.erase(subdirIt);
            dir->subdirectories[m_Flag2] = subdir;
            fs->Log("The name of: [" + m_Flag1 + "] directory in [" + m_currentpath + "] was changed to[" + m_Flag2 + "]");
        }


        auto fileIt = dir->files.find(m_Flag1);
        if(fileIt != dir->files.end())
        {
            File file = fileIt->second;
            file.name = m_Flag2;
            dir->files.erase(fileIt);
            dir->files[m_Flag2] = file;
            fs->Log("The name of: [" + m_Flag1 + "] file in [" + m_currentpath + "] was changed to[" + m_Flag2 + "]");
        }
    }
}

void Commands::PrintLog()
{
    std::cout << "printed log\n";
    fs->PrintLog();
}