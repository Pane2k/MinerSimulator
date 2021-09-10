#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

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

class mob : public entity
{
public:
    int get_direction()
    {
        return this->direction;
    }
    string get_direction_string()
    {
        switch (direction)
        {
        case North:
            return "North";
            break;
        case East:
            return "East";
            break;
        case South:
            return "South";
            break;
        case West:
            return "West";
            break;

        default:
            return "err dir";
            break;
        }
    }
private:
    enum DIR_name
    {
        North = 0,
        East = 1,
        South = 2,
        West = 3,
    };
    int direction;

};

class player : public mob
{

};

class map
{
public:
    char map_res[16][16] = {    {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','S'},
                                {'S','S','S','S','S','S','S','S','S','S','S','S','S','S','S','P'}, };
private:
    int size_x = 8;
    int size_y = 8;
    
}map_side;

enum ASCII_TAB
{
    // OutLine In Console
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

    // Elements for game
    FullBlockShade = 0xDB,
    DarkBlockShade = 0xB2,
    MediumBlockShade = 0xB1,
    LightBlockShade = 0xB0,

    // Player on the map
    Player_North = 0x5e,
    Player_East = 0x3e,
    Player_South = 0xFB,
    Player_West = 0x3c,

    // Blocks on the map
    Block_Stone = 0xB2,
};
enum Entitys_OnMap
{
    Entity_Stone = 'S',
    Entity_Player = 'P',

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
enum MAP_control
{
    MAP_FullBlockShade,
    MAP_DarkBlockShade,
    MAP_MediumBlockShade,
    MAP_LightBlockShade,
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
        WindowSizeX = CursoreControl.GetScreenWide();
        WindowSizeY = CursoreControl.GetScreenHigth();
        char ScreenBuffer[120][40];
        for (int y_coord = 0; y_coord < WindowSizeY; y_coord++)
        {
            for (int x_coord = 0; x_coord < WindowSizeX; x_coord++)
            {
                SetCursorePosition(x_coord, y_coord);
                int WII = -1;
                do {
                    // To side block
                    if (x_coord == CameraPlayer && y_coord == 0) { WII = WII_HorisontalToDown; break; }
                    if ((x_coord == 0 && y_coord == (CameraPlayer / 2)+1) || (x_coord == CameraPlayer && y_coord == WindowSizeY-3)) { WII = WII_VerticalToRight; break; }
                    if ((x_coord == CameraPlayer && y_coord == (CameraPlayer / 2+1)) || (x_coord == WindowSizeX - 1 && y_coord == WindowSizeY - 3)) { WII = WII_VerticalToLeft; break; }
                    if (x_coord == CameraPlayer && y_coord == WindowSizeY - 1) { WII = WII_HorisontalToUp; break; }

                    // Angle block
                    if (x_coord == 0 && y_coord == 0) { WII = WII_LeftUpAngle; break; }
                    if (x_coord == 0 && y_coord == WindowSizeY - 1) { WII = WII_LeftDownAngle; break; }
                    if (x_coord == WindowSizeX - 1 && y_coord == 0) { WII = WII_RightUpAngle; break; }
                    if (x_coord == WindowSizeX - 1 && y_coord == WindowSizeY-1){ WII = WII_RightDownAngle; break; }
                    
                    // Lines block
                    if ((x_coord > 0 && x_coord < WindowSizeX) && (y_coord == 0 || y_coord == WindowSizeY-1) || (y_coord == (CameraPlayer/2)+1 && (x_coord >0 && x_coord < WinSet.CameraPlayer))|| ((x_coord > WinSet.CameraPlayer && x_coord < WindowSizeX-1) && y_coord == WindowSizeY - 3)) { WII = WII_Horisontal; break; }
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
               
                
            }
            if (y_coord == WindowSizeY - 1) break;
        }
     
 
        
        
    }
    void draw_map() 
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int y_coord = 1, y = 0; y_coord < CameraPlayer; y_coord++, y++)
        {
            for (int x_coord = 1, x = 0; x_coord < (CameraPlayer / 2) + 1; x_coord++, x++)
            {
                SetCursorePosition((x_coord*2)-1, y_coord);
                char map_block = map_side.map_res[y][x];
                

                switch (map_block)
                {
                    case Entity_Stone:
                        SetConsoleTextAttribute(hConsole, 2);
                        cout << (char)Block_Stone;
                        cout << (char)Block_Stone;
                        break;
                    case Entity_Player:
                        SetConsoleTextAttribute(hConsole, 3);
                        cout << (char)Player_North;
                        cout << (char)Player_North;
                        break;
                    default:
                        break;
                }
            }
            
        }
        
    }
};

int main()
{

    

    system("mode con lines=40 cols=120");

    draw_view MainConsole;
    MainConsole.draw_outline();
    MainConsole.draw_map();
    CursoreControl.CursoreWritePos();
    system("PAUSE");
}

