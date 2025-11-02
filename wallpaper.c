#include<stdio.h>
#include<string.h>
#include<windows.h>

// In future, we can add logging and see the information or time spent on certain mode
// see, if OBS records the lock screen too.

// plan:
// have a wallpaper-config.txt in some folder - possibly in desktop - (hardcode in the code for now - may be add config management later)
// 
// let that file have the wallpaper image info like this: <mode> - <keys> - <wallpaper-path>
// Example: party - "p" - "C:\Users\Hxtreme\Desktop\fun.jpg"
// Here, we can append the specified key with the combination like "ctrl+shift+<specified-key>" = Because, allowing any pattern is not possible.
// Here, storing the info in a hashmap of some sort will be useful. For now, lets use 3 arrays for the mode, key, wallpaper-path
// (if any of this is not unique, we can log an error)
// 
// then, always listen for the key stroke combination - if go it at once, change the wallpaper and print the "mode - key - image"
// First, do this in the foreground and then try to have it in the background.

#define MAX_MODE_LENGTH 10
#define MAX_PATH_LENGTH 100
#define MAX_ENTRIES 50
#define QUIT_KEY_ID 100

char mode[MAX_ENTRIES][MAX_MODE_LENGTH];
char key[MAX_ENTRIES][2]; // one for the key and the other for the '\0' terminator
char path[MAX_ENTRIES][MAX_PATH_LENGTH];

void get_image_info(char line[], int position);
void register_keys(int image_count);
void unregister_keys(int image_count);
void start_wallpaper_keys_message_loop(int image_count);
void change_wallpaper(int index);

// why only 32 bit has to be understood and told?
int WINAPI WinMain(
    HINSTANCE hInstance, // handle (Unique Id) to the current instance of the application
    HINSTANCE hPrevInstance, // handle for any previous instance of the application (obsolete)
    LPSTR lpCmdLine, // LPTR - Long pointer to command line. Contains the info passed to the application via cmd line excluding the application name
    int nCmdShow // Integer flag that specifies how to show the window - normal size or minimized.
)
{
    MessageBoxA(
        NULL,
        "Welcome to the day 4 of Daily Coding\n It is now running in backgroud. Press OK to continue",
        "the Mood Wallpaper Changer",
        MB_OK | MB_ICONINFORMATION
    );

    FILE *fptr = fopen("C:\\wallpaper-config.txt", "r");

    char line[150];
    int image_count = 0;

    while (fgets(line, 150, fptr )!= NULL)
    {
        get_image_info(line, image_count);
        image_count++;
    }

    fclose(fptr);

    register_keys(image_count);

    start_wallpaper_keys_message_loop(image_count);

    unregister_keys(image_count);

}

void get_image_info(char line[], int pos)
{
    char *delimiter = " ";

    // get the first token
    char *token = strtok(line, delimiter);

    //lunch L D:\Downloads\wallpaper-images\lunch-time.jpg
    
    int index = 0;

    while(token != NULL)
    {
        if(index == 0)
        {
            strncpy(mode[pos], token, MAX_MODE_LENGTH - 1);
        }
        if(index == 1)
        {
            key[pos][0] = token[0];
            key[pos][1] = '\0';
        }
        if(index == 2)
        {
            // clean the token from trailing new lines, spaces and carriage returns
            int len = strlen(token);
            while(len > 0 && (token[len-1] == '\n' || token[len-1] == ' ' || token[len-1] == '\r'))
            {
                token[--len] = '\0';
            }

            strncpy(path[pos], token, MAX_PATH_LENGTH - 1);
        }
        index++;

        // the string argument is set to null for further tokens to make the function continue from where it left before.
        token = strtok(NULL, delimiter);
    }
}

void register_keys(int image_count)
{
    int num_keys = image_count;
    if(num_keys <= 0)
    {
        MessageBoxA(
        NULL,
        "No keys available",
        "ERROR",
        MB_OK | MB_ICONERROR
    );
        return;
    }

    // registering the hotkeys

    for(int i = 0; i < num_keys; i++)
    {
        // 1. Register the hot key: Ex: Ctrl + Shift + P

        int register_key_success = RegisterHotKey(
            NULL, // Handle to window - NULL - means the current thread
            i, // Hotkey ID - unique number - ex: 1
            MOD_CONTROL | MOD_SHIFT, // The modifier keys - ctrl and shift here
            key[i][0] // the key - ex: 'P'
        );

        if(!register_key_success)
        {
            MessageBox(NULL, "HotKey registration failed", "Error", MB_OK);
            continue;
        }
    }

    // for extra, register a key for quitting
    int quit_key_success = RegisterHotKey(
        NULL,
        QUIT_KEY_ID,
        MOD_CONTROL | MOD_SHIFT,
        'Q'
    );

    if(!quit_key_success)
    {
        MessageBox(NULL, "HotKey registration failed (Quitting - 'Q')", "Error", MB_OK);
    }

}

void unregister_keys(int image_count)
{
    int num_keys = image_count;

    for(int i = 0; i < num_keys; i++)
    {
        UnregisterHotKey(NULL, i);
    }
}

void start_wallpaper_keys_message_loop(int image_count)
{
    int num_keys = image_count;

    MSG msg = {0}; // MSG is a struct here
    while(GetMessage(&msg, NULL, 0, 0) != 0)
    {
        if(msg.message == WM_HOTKEY)
        {
            int hotkey_id = msg.wParam;
            // check quitting
            if(hotkey_id == QUIT_KEY_ID) 
            {
                MessageBoxA(
                    NULL,
                    "Hotkey Ctrl+Shift+Q is pressed!\n Quitting the program. Bye!",
                    "Hotkey activated",
                    MB_OK | MB_ICONINFORMATION
                );
                return;
            }

            // check other keys

            if(hotkey_id >= 0 && hotkey_id <= num_keys) // check if the hotkey is pressed using it's id in the index range.
            {

                char success_msg[150];
                // sprintf is used to convert the dynamic string into the buffer string
                sprintf(success_msg, "Hotkey Ctrl+Shift+%c is pressed! We can change the wallpaper now!", key[hotkey_id][0]);
                MessageBoxA(
                    NULL,
                    success_msg,
                    "Hotkey activated",
                    MB_OK | MB_ICONINFORMATION
                );

                change_wallpaper(hotkey_id);
            }
        }
    }
}

void change_wallpaper(int index)
{
    // convert the path to widechar array
    wchar_t wpath[MAX_PATH];

    MultiByteToWideChar(CP_ACP, 0, path[index], -1, wpath, MAX_PATH);

    // Call the windows API to set the wallpaper
    BOOL success = SystemParametersInfoW(
        SPI_SETDESKWALLPAPER, // Action - set desktop wallpaper
        0, // something not used for this action
        wpath, // pointer to the path string (must be wchar_t)
        SPIF_UPDATEINIFILE | SPIF_SENDCHANGE // Flags: Update registry and notify all windows
    );

    char wallpaper_set_msg[150];
    if(success)
    {
        sprintf(wallpaper_set_msg, "Wallpaper successfully changed to %s image.", path[index]);
        MessageBoxA(
            NULL,
            wallpaper_set_msg,
            "Wallpaper info",
            MB_OK | MB_ICONINFORMATION
         );
    }
    else
    {
        DWORD error = GetLastError();

        sprintf(wallpaper_set_msg, "Failed to change wallpaper. Error code: %lu", error);

        MessageBoxA(
            NULL,
            wallpaper_set_msg,
            "Error setting Wallpaper",
            MB_OK | MB_ICONINFORMATION
         );
    }
}
