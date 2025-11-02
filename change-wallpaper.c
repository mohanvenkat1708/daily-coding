#include<stdio.h>
#include <string.h>
#include<windows.h>
// #include <winreg.h>
#include<stdbool.h>

// __attribute__((dllimport)) LONG WINAPI RegSetKeyValueA(
//     HKEY hKey, 
//     LPCSTR lpSubKey, 
//     LPCSTR lpValueName, 
//     DWORD dwType, 
//     const VOID *lpData, 
//     DWORD cbData
// );

// #define RRF_RT_DWORD    0x00000004  // Correct value for REG_DWORD
// #define RRF_RT_REG_SZ   0x00000002  // Correct value for REG_SZ

// #define LOCK_SCREEN_KEY "SOFTWARE\\Policies\\Microsoft\\Windows\\System"

// LONG WINAPI RegSetKeyValueA(HKEY hKey, LPCSTR lpSubKey, LPCSTR lpValueName, DWORD dwType, const VOID *lpData, DWORD cbData);

int main()
{
    // important thng: the '\' will in normal cases act as escape character. Hence, we need to use '\\'
    char image_path[] = "D:\\Downloads\\wallpaper-images\\coding-time.jpg";

    wchar_t wpath[MAX_PATH];

    // char choice;
    // printf("Give the option\n[l -> lock screen\t d -> desktop]");

    // scanf("%c", &choice);

    // if(choice == 'd')
    // {
        // Convert char* to wchar_t*
        MultiByteToWideChar(CP_ACP, 0, image_path, -1, wpath, MAX_PATH);

        // Call the windows API to set the wallpaper
        BOOL success = SystemParametersInfoW(
            SPI_SETDESKWALLPAPER, // Action - set desktop wallpaper
            0, // something not used for this action
            wpath, // pointer to the path string (must be wchar_t)
            SPIF_UPDATEINIFILE | SPIF_SENDCHANGE // Flags: Update registry and notify all windows
        );

        if(success)
        {
            printf("Wallpaper successfully changed to %s", image_path);
        }
        else{
            DWORD error = GetLastError();
            printf("Failed to change wallpaper. Error code: %lu", error);
        }
    // }
    // else if(choice == 'l')
    // {
    //     LONG result;
    //     DWORD use_oem = 1;

    //     // Since we are setting the registry value from code, we need this flag to be set to true (or 1).
    //     result = RegSetKeyValueA(
    //         HKEY_LOCAL_MACHINE, // Main key: HKEY_LOCAL_MACHINE
    //         LOCK_SCREEN_KEY, // the sub key
    //         "UseOEMBackground",
    //         RRF_RT_DWORD, // Value type: DWORD - what is this?
    //         &use_oem, // pointer to the data
    //         sizeof(use_oem) // size of the data
    //     );

    //     if(result != ERROR_SUCCESS)
    //     {
    //         printf("Failed to set UseOEMBackground. Error code: %lu", result);
    //         return 1;
    //     }

    //     // setting the background imagepath
    //     // set OEMBackground to the image_path
    //     result = RegSetKeyValueA(
    //         HKEY_LOCAL_MACHINE, // Main key: HKEY_LOCAL_MACHINE
    //         LOCK_SCREEN_KEY, // the sub key
    //         "OEMBackground",
    //         RRF_RT_REG_SZ, // Value type: String - type of the value to be set in the key
    //         image_path, // pointer to the data
    //         sizeof(image_path) + 1 // size of the data
    //     );

    //     if(result == ERROR_SUCCESS)
    //     {
    //         printf("Lock screen wallpaper registry path set to %s.", image_path);
    //     }
    //     else
    //     {
    //         printf("Failed to set OEMBackground path. Error code: %lu", result);
    //     }
    // }
    


}