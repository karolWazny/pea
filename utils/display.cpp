//
// Created by admin on 05.01.2022.
//

#include <string>

#include <wincontypes.h>
#include <consoleapi2.h>
#include <WinBase.h>

void gotoxy(short x, short y)
{
    COORD coord;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle, coord);
}

void clear() {
    system("cls");
}