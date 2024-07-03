#pragma once

#include "FileSystem.h"

class Commands : public FileSystem
{
public:
    void checkInput();

    void Mkdir();
    void Rmdir();
    void Cd();
    void Ls();
    void Pwd();
    void Touch();
    void Cat();
    void Echo();

private:

};