#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>

int speed = 0;
int is_autoclicker_running = 0; // Flag to track autoclicker state
pthread_t autoclick_thread;

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
void* autoclick() {
    while (is_autoclicker_running) {
        click();
        Sleep(speed);
    }
    return NULL;
}

// Function to handle starting and stopping the autoclicker
void* monitor_hotkey() {
    while (1) {
        if (GetAsyncKeyState(VK_F6) & 0x8000) {
            is_autoclicker_running = !is_autoclicker_running;

            if (is_autoclicker_running) {
                // Start the autoclicker thread
                if (pthread_create(&autoclick_thread, NULL, autoclick, NULL) != 0) {
                    fprintf(stderr, "Failed to create autoclicker thread\n");
                    exit(1);
                }
                printf("Autoclicker ON\n");
            } else {
                // Signal the autoclicker thread to stop
                pthread_join(autoclick_thread, NULL);
                printf("Autoclicker OFF\n");
            }
            Sleep(200);
        }
    }
    return NULL;
}

int main(void) {
    printf("Select the clicker speed in milliseconds: ");
    if (scanf("%d", &speed) != 1 || speed <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    printf("Press F6 to toggle the autoclicker\n");

    pthread_t monitor_thread;
    if (pthread_create(&monitor_thread, NULL, monitor_hotkey, NULL) != 0) {
        fprintf(stderr, "Failed to create monitor thread\n");
        return 1;
    }

    // Wait for the monitor thread to finish (unlikely in this case)
    pthread_join(monitor_thread, NULL);

    return 0;
}
