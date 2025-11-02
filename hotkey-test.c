#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#define HOTKEY_ID 100

// When compiling this application, Note:
// the key to making it run in the background is the "-mwindows" flag. This tells GCC to link the application against the Windows subsystem instead of the Console subsystem.

// Use this new command:
// gcc hotkey-test.c -o hotkey-test.c -mwindows -l user32
int WINAPI WinMain(
    HINSTANCE hInstance, // handle (Unique Id) to the current instance of the application
    HINSTANCE hPrevInstance, // handle for any previous instance of the application (obsolete)
    LPSTR lpCmdLine, // LPTR - Long pointer to command line. Contains the info passed to the application via cmd line excluding the application name
    int nCmdShow // Integer flag that specifies how to show the window - normal size or minimized.
)
{
    MessageBoxA(
        NULL, 
        "Hotkey listener test started (CTRL + ALT + K.) It is now running in backgroud. Press OK to continue.", 
        "Hotkey POC started...",
        MB_OK | MB_ICONINFORMATION
    );

    // register the HotKey
    // parameters:
    // NULL - Our application doesn't have a visible window (HWND) for handling
    // HOTKEY_ID - unique Id for the Hotkey
    // MOD_CONTROL | MOD_ALT: Modifiers (Ctrl and Alt)
    // 'K': Virtual key code for the letter 'K'

    BOOL registration_success = RegisterHotKey(
        NULL,
        HOTKEY_ID,
        MOD_CONTROL | MOD_ALT,
        'K'
    );

    if(!registration_success)
    {
        DWORD error = GetLastError();
        char error_msg[100];
        
        wsprintf(error_msg, "Failed to register hot keys. Error code %ul", error); // what is the purpose of this wsprintf
        MessageBoxA(NULL, error_msg, "Error", MB_ICONERROR);
        return 1;
    }

    MSG msg = {0};

    while(GetMessage(&msg, NULL, 0, 0) != 0)
    {
        // if it is a hotkey pressed event
        if(msg.message == WM_HOTKEY)
        {
            MessageBoxA(
                NULL,
                "CTRL + ALT + K Pressed! Hurray, Hotkey activation triggered.",
                "Hotkey Activated",
                MB_OK | MB_ICONASTERISK
            );
        }
    }

    UnregisterHotKey(NULL, HOTKEY_ID);
    return 0;
}
