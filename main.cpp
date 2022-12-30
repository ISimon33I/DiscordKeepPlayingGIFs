#include <thread>
#include <Windows.h>
#include <wchar.h>
#include <iostream>

bool strEndsWith(const wchar_t* str, const wchar_t* suffix)
{
    size_t len = wcslen(str);
    size_t suffixlen = wcslen(suffix);
    if(suffixlen > len)
    {
        return false;
    }

    str += (len - suffixlen);
    auto result = wcscmp(str, suffix) == 0;
    return result;
}

BOOL CALLBACK WorkerProc(HWND hwnd, LPARAM lParam) {
    const int max_str_size = 100;
    static WCHAR bufferTitle[max_str_size];
    static WCHAR bufferClass[max_str_size];
    auto resultPtr = (HWND*)lParam;
    HWND &result = *resultPtr;

    GetWindowTextW(hwnd, bufferTitle, max_str_size);
    GetClassNameW(hwnd, bufferClass, max_str_size);
    if(strEndsWith(bufferTitle, L"- Discord") && wcsstr(bufferClass, L"Chrome_Widget")) {
        result = hwnd;
        std::wcout << bufferTitle << " | ClassName: " << bufferClass << std::endl;
        
        
        return FALSE;
    }
    
    return TRUE;
}

int main(){
    HWND hWnd = nullptr;
    EnumWindows(WorkerProc, (LPARAM)&hWnd);
    
    if(hWnd == nullptr) {
        std::cout << "Window not found! Exiting..." << std::endl;
        return 1;
    }
    std::cout << "Starting focus loop! hWnd: " << hWnd << std::endl;
    std::cout << "Leave in the background." << std::endl;
    while(true){
        SendMessage(hWnd, WM_ACTIVATE, WA_CLICKACTIVE, NULL);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
