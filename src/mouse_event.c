#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "globals.h"

// Function to simulate a mouse click
void click() {
    INPUT in[2];
    ZeroMemory(&in, sizeof(in));

    in[0].type = INPUT_MOUSE;
    in[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    in[1].type = INPUT_MOUSE;
    in[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(2, in, sizeof(INPUT));
}

// Thread function for the autoclicker
void* autoclick(void* arg) {
    int* is_autoclicker_running = (int*) arg;
    while (*is_autoclicker_running) {
        click();
        Sleep(speed);
    }
    return NULL;
}