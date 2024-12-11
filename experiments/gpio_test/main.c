#include <pigpio.h>
#include <stdio.h>
#include <unistd.h>

int button1 = 14;
int button2 = 15;

int ledOutput1 = 23;
int ledOutput2 = 24;

const uint32_t debounceInterval = 60000; 

void button1PressCallback(int gpio, int level, uint32_t tick) {
    static uint32_t buttonCount = 0;
    static uint32_t lastTick1 = 0;

    if ((tick - lastTick1) < debounceInterval) {
        return;
    }

    uint32_t tickRange = tick - lastTick1;

    lastTick1 = tick;

    if (level == 1) {
        printf("Button 1 pressed!\n");
        gpioWrite(ledOutput1, 1);
    } else if (level == 0) {
        printf("lastTick value: %d\n", tickRange);
        buttonCount++;
        printf("buttonCount value: %d\n", buttonCount);
        printf("Button 1 released!\n");
        gpioWrite(ledOutput1, 0);
    }
}

void button2PressCallback(int gpio, int level, uint32_t tick) {
    static uint32_t lastTick = 0;

    if ((tick - lastTick) < debounceInterval) {
        return;
    }

    lastTick = tick;

    if (level == 1) {
        printf("Button 2 pressed!\n");
        gpioWrite(ledOutput2, 1);
    } else if (level == 0) {
        printf("Button 2 released!\n");
        gpioWrite(ledOutput2, 0);
    }
}

void initialiseGpio() {
    gpioSetMode(ledOutput1, PI_OUTPUT);
    gpioSetMode(ledOutput2, PI_OUTPUT);
    gpioSetMode(button1, PI_INPUT);
    gpioSetMode(button2, PI_INPUT);

    gpioSetPullUpDown(button1, PI_PUD_DOWN);
    gpioSetPullUpDown(button2, PI_PUD_DOWN);

    gpioSetAlertFunc(button1, button1PressCallback);
    gpioSetAlertFunc(button2, button2PressCallback);
}

int main() {
    if (gpioInitialise() < 0) {
        fprintf(stderr, "Error: Failed to initialise \n");
        return 1;
    }

    initialiseGpio();

    while (1) {
        sleep(1);
    }

    gpioTerminate();
    return 0;
}