#include "ReadInput.h"

void ReadInput::GetFlags(const std::string& str)
{
    size_t spacePos = str.find(" ");
    if(spacePos != std::string::npos)
    {
        std::string substring = str.substr(spacePos + 1);
        spacePos = substring.find(" ");
        if(spacePos == std::string::npos)
        {
            m_Flag1 = substring;
            m_Flag2 = "0";
        }
        else
        {
            m_Flag1 = substring.substr(0, spacePos);
            m_Flag2 = substring.substr(spacePos + 1);
        }
    }
    else
    {
        m_Flag1 = "0";
        m_Flag2 = "0";
    }
}

void ReadInput::GetCommand(const std::string& str)
{
    size_t spacePos = str.find(" ");
    if(spacePos != std::string::npos)
        m_Command = str.substr(0, spacePos);
    else
        m_Command = str;

    if(std::find(m_CommandList.begin(), m_CommandList.end(), m_Command) == m_CommandList.end())
    {
        std::cout << "[ERROR] Wrong command [" << m_Command << "]\n";
        m_Command.clear();
    }
}

void ReadInput::CreateURL(const std::string &input)
{
    GetCommand(input);
    if(m_Command.empty()) return;
    
    GetFlags(input);

    m_URL = "http://localhost:8080/filesystem?action=" + m_Command 
        + "&flag1=" + m_Flag1 + "&flag2=" + m_Flag2;
}

void ReadInput::SetCommand()
{
    if(m_Command.empty()) return;

    //std::cout << "[" << m_Command << "]\n";
    //std::cout << "[" << m_Flag1 << "]\n";
    //std::cout << "[" << m_Flag2 << "]\n";

    // GET
    if(m_Command == "ls" || m_Command == "pwd" || m_Command == "cat" || m_Command == "printlog" || m_Command == "p")
    {
        response = SendRequest(m_URL, "GET");
    }
    else if(m_Command == "cd" || m_Command == "cat" || m_Command == "undo"
         || m_Command == "touch" || m_Command == "mkdir")
    {
        response = SendRequest(m_URL, "PUT");
    } // DELETE
    else if(m_Command == "rmdir" || m_Command == "rm")
    {
        response = SendRequest(m_URL, "DELETE");
    }
    else
    {
        return;
    }
    std::cout << response << "\n";
}

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string ReadInput::SendRequest(const std::string &url, const std::string &method)
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        //std::cout << "Sending [" << method << "] request to URL: [" << url << "]\n";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        if (method == "PUT")
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        }
        else if (method == "DELETE")
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        }
        else if (method == "GET")
        {
            // tu nic nie trzeba ustawiac
        }
        else
        {
            std::cerr << "[ERROR] Unsupported HTTP method: " << method << "\n";
            return "Error: Unsupported HTTP method";
        }
        
        // cos tam ustawia z headerami
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        // ustawia, gdzie ma byc zapisywana informacja zwrotna, i za pomoca czego
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // wysyla request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
            readBuffer = "Error: " + std::string(curl_easy_strerror(res));
        }


        // cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    else
    {
        std::cerr << "[ERROR] Failed to initialize CURL.\n";
        readBuffer = "Error: CURL initialization failed";
    }

    curl_global_cleanup();
    return readBuffer;
}
