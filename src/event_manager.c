#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>
#include "mouse_event.h"
#include "globals.h"

// Function to handle starting and stopping the autoclicker
void* monitor_hotkey() {
    while (1) {
        if (GetAsyncKeyState(VK_F6) & 0x8000) {
            is_autoclicker_running = !is_autoclicker_running;

            if (is_autoclicker_running) {
                // Start the autoclicker thread
                if (pthread_create(&autoclick_thread, NULL, autoclick, &is_autoclicker_running) != 0) {
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

        if (GetAsyncKeyState('C') & 0x8000) {
            printf("Exiting program...\n");
            exit(0);
        }

        Sleep(50);
    }
    return NULL;
}