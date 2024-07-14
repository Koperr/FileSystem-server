//#include <memory>

#include <httpserver.hpp>

#include "FileSystem.h"

using namespace httpserver;

class FileSystemHandler : public http_resource
{
public:
    FileSystemHandler(FileSystem* fs) : filesystem(fs) {}

    

private:
    FileSystem* filesystem;
};


int main()
{
    FileSystem fsys;

    fsys.Run();
}

// przed zabawa w gita 1