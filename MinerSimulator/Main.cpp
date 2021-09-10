#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct WindowSettings
{
public:
    int CameraPlayer = 33;
} WinSet; 

class entity
{
    string name;
    int hp;
}; 

class map
{
    int size_x;
    int size_y;

};

enum ASCII_TAB
{
    LeftUpAngle_line = 0xC9,
    RightUpAngle_line = 0xBB,
    Horisontal_line = 0xCD,
    Vertical_line = 0xBA,
    HorisontalToDown_line = 0xCB,
    VerticalToRight_line = 0xCC,
    VerticalToLeft_line = 0xB9,
    RightDownAngle_line = 0xBC,
    LeftDownAngle_line = 0xC8,
    HorisontalToUp_line = 0xCA,

};

enum WII_control
{
    WII_LeftUpAngle,
    WII_RightUpAngle,
    WII_Horisontal,
    WII_HorisontalToDown,
    WII_Vertical,
    WII_VerticalToRight,
    WII_VerticalToLeft,
    WII_RightDownAngle,
    WII_LeftDownAngle,
    WII_HorisontalToUp
};

void ClearConsoleScreen() 
{
    system("cls");
}

class cursor_control
{
public:
    int GetCursorePosition()
    {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
        return csbiInfo.dwCursorPosition.X;
    }
    
    int GetScreenWide()
    {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
        return csbiInfo.dwSize.X;
    }

    int GetScreenHigth()
    {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
        return csbiInfo.dwSize.Y;
    }

    void SetCursorePosition(int x, int y)
    {
        static HANDLE h = NULL;
        if (!h)
            h = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD c = { x, y };
        SetConsoleCursorPosition(h, c);
    }
    void CursoreWritePos()
    {
        SetCursorePosition(WinSet.CameraPlayer + 2, CursoreControl.GetScreenHigth() - 2);
    }
private:
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
}CursoreControl;

int WindowSizeX = CursoreControl.GetScreenWide();
int WindowSizeY = CursoreControl.GetScreenHigth();



class draw_view : public cursor_control, WindowSettings
{
public:
    void draw_outline()
    {
        for (int x_coord = 0; x_coord < WindowSizeX; x_coord++)
        {
            for (int y_coord = 0; y_coord < WindowSizeY; y_coord++)
            {
                SetCursorePosition(x_coord, y_coord);
                int WII = -1;
                do {
                    // To side block
                    if (x_coord == CameraPlayer && y_coord == 0) { WII = WII_HorisontalToDown; break; }
                    if ((x_coord == 0 && y_coord == CameraPlayer / 2) || (x_coord == CameraPlayer && y_coord == WindowSizeY-3)) { WII = WII_VerticalToRight; break; }
                    if ((x_coord == CameraPlayer && y_coord == CameraPlayer / 2) || (x_coord == WindowSizeX - 1 && y_coord == WindowSizeY - 3)) { WII = WII_VerticalToLeft; break; }
                    if (x_coord == CameraPlayer && y_coord == WindowSizeY - 1) { WII = WII_HorisontalToUp; break; }

                    // Angle block
                    if (x_coord == 0 && y_coord == 0) { WII = WII_LeftUpAngle; break; }
                    if (x_coord == 0 && y_coord == WindowSizeY - 1) { WII = WII_LeftDownAngle; break; }
                    if (x_coord == WindowSizeX - 1 && y_coord == 0) { WII = WII_RightUpAngle; break; }
                    if (x_coord == WindowSizeX - 1 && y_coord == WindowSizeY-1){ WII = WII_RightDownAngle; break; }
                    
                    // Lines block
                    if ((x_coord > 0 && x_coord < WindowSizeX) && (y_coord == 0 || y_coord == WindowSizeY-1) || (y_coord == CameraPlayer/2 && (x_coord >0 && x_coord < WinSet.CameraPlayer))|| ((x_coord > WinSet.CameraPlayer && x_coord < WindowSizeX-1) && y_coord == WindowSizeY - 3)) { WII = WII_Horisontal; break; }
                    if (x_coord == 0 || x_coord == CameraPlayer || x_coord == WindowSizeX-1) { WII = WII_Vertical; break; }
                } while (false);

                switch (WII)
                {
                case WII_LeftUpAngle:
                    cout << (char)LeftUpAngle_line;
                    break;
                case WII_RightUpAngle:
                    cout << (char)RightUpAngle_line;
                    break;
                case WII_Horisontal:
                    cout << (char)Horisontal_line;
                    break;
                case WII_HorisontalToDown:
                    cout << (char)HorisontalToDown_line;
                    break;
                case WII_Vertical:
                    cout << (char)Vertical_line;
                    break;
                case WII_VerticalToRight:
                    cout << (char)VerticalToRight_line;
                    break;
                case WII_VerticalToLeft:
                    cout << (char)VerticalToLeft_line;
                    break;
                case WII_RightDownAngle:
                    cout << (char)RightDownAngle_line;
                    break;
                case WII_LeftDownAngle:
                    cout << (char)LeftDownAngle_line;
                    break;
                case WII_HorisontalToUp:
                    cout << (char)HorisontalToUp_line;
                    break;

                default:
                    break;
                }
                if (y_coord == WindowSizeY-1) 
                    break;
            }
        }
    }

};

int main()
{
    draw_view MainConsole;
    MainConsole.draw_outline();
}

