#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void click() {
    INPUT in[2];
    ZeroMemory(&in, sizeof(in));

    in[0].type = INPUT_MOUSE;
    in[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    
    in[1].type = INPUT_MOUSE;
    in[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    UINT us = SendInput(2, in, sizeof(INPUT)); 
}

int main(void)
{
    int speed;
    printf("Select the clicker speed per second: ");
    if (scanf("%d", &speed) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Appuyez sur F6 pour afficher la vitesse...\n");
    while (1) {
        if (GetAsyncKeyState(VK_F6) & 0x8000) {
            printf("Vitesse : %d\n", speed);
            click();
        }
        Sleep(80);
    }
    return 0;
}
