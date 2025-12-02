#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int window_width = 600;
int window_height = 800;

int top_pos = 0;
int left_pos = 0;
int bottom_pos = 50;
int right_pos = 75;

// LRESULT - the value that our fucntion gives back to Windows. Always 0, if we handled the message.
// CALLBACK - the "__stdcall calling convention" required by windows. For cleaning up the stack by the called function
// WindowProcedure - the name we choose for the function. Can be anything like: WndProc or MyWindowFunc or something else.
// HWND - the "handle" for the window. the ID of the window (the specific window that received the message)
// UNINT - unsigned integer - used for message codes like WM_PAINT, WM_DESTROY
// WPARAM - Extra Information - depends on the message - the key code, mouse button
// LPARAM - Extra Information - depends on the message - contains the coordinates or handles

// This function handles messages (like close button, paint, etc...)
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            // Timer Id = 1, interval = 1000 ms, call our window procedure
            SetTimer(hwnd, 1, 1000, NULL);
            return 0;
        
        case WM_TIMER:
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;
        
        case WM_KEYDOWN:
            switch (wParam)
            {
                case 'W':
                if(top_pos >= 10)
                {
                    top_pos -= 10;
                    bottom_pos -= 10;
                }
                break;
                case 'A':
                if(left_pos >= 10)
                {
                    left_pos -= 10;
                    right_pos -= 10;
                }
                break;
                case 'S':
                if(bottom_pos <= window_height - 40) // adjusted for the window border
                {
                    top_pos += 10;
                    bottom_pos += 10;
                }
                break;
                case 'D':
                if(right_pos <= window_width - 20)
                {
                    left_pos += 10;
                    right_pos += 10;
                }
                break;
            }
            InvalidateRect(hwnd, NULL, TRUE); // force to repaint the rectangle
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            // it does not exit the program. It simply posts a special message WM_QUIT to the queue.
            // then, GetMessage runs and sees it and returns FALSE and the loop ends
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps; // a structure that lives on the memory - like a ticket that contatins which part to redraw
            
            // hdc - means, the device context - this is like a canvas to draw on to the window
            HDC hdc = BeginPaint(hwnd, &ps);

            char str[100] = "Use WASD keys to move the box";
            TextOut(hdc, 50, 50, str, strlen(str));


            // left, top, right, bottom
            RECT rect = {left_pos, top_pos, right_pos, bottom_pos};

            // the window coordinate start from 0,0 in the top left
            // the corners will be: 50,100 - top left, (300 - 50), 100 - top right
            // 50, 200 - bottom left, (300 - 50), 200 - bottom right

            int rand_r = rand() % 256;
            int rand_g = rand() % 256;
            int rand_b = rand() % 256;

            HBRUSH redBrush = CreateSolidBrush(RGB(rand_r, rand_g, rand_b)); // red color brush

            FillRect(hdc, &rect, redBrush);

            DeleteObject(redBrush);

            EndPaint(hwnd, &ps);

            return 0;
        }
    }

    return DefWindowProc(hwnd, msg, wParam, lParam); // windows function to handle the message
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    srand(time(NULL));

    // The window class is called the blue print of the window that we are creating
    const char* className = "MyFirstWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProcedure; // Our message handler
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClass(&wc))
    {
        MessageBox(NULL, "RegisterClass failed", "Error", MB_ICONERROR);
        return -1;
    }

    HWND hwnd = CreateWindowEx(
        0,                              // dwExStyle - extended additional style
        className,                      // the class we just registered
        "My First Real Window in C",    // title
        WS_OVERLAPPEDWINDOW,            // style = normal window with minimize/maximize/close
        CW_USEDEFAULT, CW_USEDEFAULT,   // x, y (the default position)
        window_width, window_height,    // width, height        
        NULL, NULL,                     // parent, menu
        hInstance,
        NULL
    );

    if(!hwnd)
    {
        MessageBox(NULL, "CreateWindowEx failed!", "Error", MB_ICONERROR);
        return -1;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {

        TranslateMessage(&msg); // example pressing 'a' -> becomes WM_CHAR'a'
        DispatchMessage(&msg); // calls our WindowProcedure
    }

    return (int)msg.wParam;
}

/*

Double-click exe
   ↓
Windows calls WinMain()
   ↓
RegisterClass() → blueprint stored globally
   ↓
CreateWindowEx() → window created (invisible)
   ↓
ShowWindow() → window appears
   ↓
UpdateWindow() → first WM_PAINT
   ↓
→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→ (message loop forever)
   ↓
User clicks X → WM_DESTROY → PostQuitMessage(0)
   ↓
GetMessage returns FALSE
   ↓
return msg.wParam → program exits cleanly

*/