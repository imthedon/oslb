#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RED 0
#define YELLOW 1
#define GREEN 2

typedef struct {
    int state;
    int duration;
} TrafficLight;

void initTrafficLight(TrafficLight* tl, int duration) {
    tl->state = RED;
    tl->duration = duration;
}

void changeLight(TrafficLight* tl) {
    switch (tl->state) {
        case RED:
            printf("RED light\n");
            tl->state = GREEN;
            break;
        case YELLOW:
            printf("YELLOW light\n");
            tl->state = RED;
            break;
        case GREEN:
            printf("GREEN light\n");
            tl->state = YELLOW;
            break;
    }
}

int main() {
    TrafficLight tl1, tl2, tl3;
    int duration = 5; // Duration in seconds for each light

    initTrafficLight(&tl1, duration);
    initTrafficLight(&tl2, duration);
    initTrafficLight(&tl3, duration);

    while (1) {
        // Intersection 1
        changeLight(&tl1);
        sleep(tl1.duration);

        // Intersection 2
        changeLight(&tl2);
        sleep(tl2.duration);

        // Intersection 3
        changeLight(&tl3);
        sleep(tl3.duration);
    }

    return 0;
}

