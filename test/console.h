#pragma once

#include <Windows.h>
#include <sstream>

class Console
{
public:

    Console()
    {
        auto childHandle = HANDLE{};
        auto attributes = SECURITY_ATTRIBUTES
        {
           .nLength = sizeof(SECURITY_ATTRIBUTES),
           .lpSecurityDescriptor = nullptr, 
           .bInheritHandle = TRUE,
        };

        CreatePipe(&childHandle, &pipe, &attributes, 0);

        auto    pi  = PROCESS_INFORMATION{};
        auto    sui = STARTUPINFOA
        {
            .cb = sizeof(STARTUPINFOA),
            .dwFlags = STARTF_USESTDHANDLES,
            .hStdInput = childHandle
        };

        CreateProcessA("console.exe", 
                       nullptr,
                       nullptr,
                       nullptr,
                       true,
                       CREATE_NEW_CONSOLE ,
                       nullptr,
                       nullptr,
                       &sui,
                       &pi);

        process=pi.hProcess;
        CloseHandle(pi.hThread);
    }


    ~Console()
    {
        TerminateProcess(process,0);
    }

    Console &operator<<(auto const &value)
    {
        auto text = (std::ostringstream{} << value).str();
        auto bw   = DWORD{};

        WriteFile(pipe,text.data(), static_cast<DWORD>(text.size()), &bw,nullptr);


        return *this;
    }


    HANDLE  process;
    HANDLE  pipe;

};
