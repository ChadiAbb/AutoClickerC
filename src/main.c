#include <stdio.h>
#include <stdlib.h>
#include "event_manager.h"
#include "mouse_event.h"
#include "globals.h"

#define MAX_SPEED 50

// Define global variables
pthread_t autoclick_thread;
int is_autoclicker_running = 0;
int speed = 0;

int main(void) {
    printf("Select the clicker speed in milliseconds: ");
    if (scanf("%d", &speed) != 1 || speed < MAX_SPEED) {
        fprintf(stderr, "Invalid input. Please enter a number higher then 50 .\n");
        return 1;
    }

    printf("Press 'F6' to toggle the autoclicker. Press 'c' to exit\n");
    pthread_t monitor_thread;
    if (pthread_create(&monitor_thread, NULL, monitor_hotkey, NULL) != 0) {
        fprintf(stderr, "Failed to create monitor thread\n");
        return 1;
    }

    // Wait for the monitor thread to finish (unlikely in this case)
    pthread_join(monitor_thread, NULL);

    return 0;
}
