#include <iostream>

#include "ReadInput.h"

int main()
{
    ReadInput ri;

    std::cout << "Client working!\n";


    int i = 0;

    while(i < 10)
    {
        std::cout << ri.SendRequest("http://localhost:8080/filesystem?action=p", "GET");
        std::getline(std::cin, ri.m_Input);
        ri.CreateURL(ri.m_Input);
        ri.SetCommand();
        std::cout << i << "\n";
        i++;
    }
}