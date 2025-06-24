#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <hidapi/hidapi.h>

#define VENDOR_ID  0x057e // Nintendo
#define PRODUCT_ID 0x2073 // NSO GameCube Controller

// Button-Definitionen für Byte 3, 4, 5
typedef struct {
    int byte;      // Byte im Report
    unsigned char mask;
    const char *name;
} ButtonInfo;

const ButtonInfo buttons[] = {
    {3, 0x01, "B"},
    {3, 0x02, "A"},
    {3, 0x04, "Y"},
    {3, 0x08, "X"},
    {3, 0x10, "R"},
    {3, 0x20, "Z"},
    {3, 0x40, "Start/Pause"},
    {4, 0x01, "Dpad Down"},
    {4, 0x02, "Dpad Right"},
    {4, 0x04, "Dpad Left"},
    {4, 0x08, "Dpad Up"},
    {4, 0x10, "L"},
    {4, 0x20, "ZL"},
    {5, 0x01, "Home"},
    {5, 0x02, "Capture"},
    {5, 0x04, "GR"},
    {5, 0x08, "GL"},
    {5, 0x10, "Chat"},
};

#define NUM_BUTTONS (sizeof(buttons)/sizeof(ButtonInfo))

int main() {
    int res;
    unsigned char buf[65]; // Standard HID buffer (1 byte report ID + 64 data)
    hid_device *handle;

    // Initialize the hidapi library
    res = hid_init();
    if (res < 0) {
        fprintf(stderr, "hid_init failed\n");
        return 1;
    }

    // Open the device using the Vendor ID and Product ID
    handle = hid_open(VENDOR_ID, PRODUCT_ID, NULL);
    if (!handle) {
        fprintf(stderr, "Unable to open device (NSO GC Controller)\n");
        return 1;
    }

    printf("Reading HID reports from NSO GameCube Controller...\n\n");

    while (1) {
        res = hid_read(handle, buf, sizeof(buf));
        if (res > 14) {
            unsigned char left_trigger = buf[13];
            unsigned char right_trigger = buf[14];

            // Button-Zustand auslesen
            printf("L:%3d | R:%3d | Buttons: ", left_trigger, right_trigger);

            int first = 1;
            for (size_t i = 0; i < NUM_BUTTONS; ++i) {
                if (buf[buttons[i].byte] & buttons[i].mask) {
                    if (!first) printf(", ");
                    printf("%s", buttons[i].name);
                    first = 0;
                }
            }
            if (first) printf("none");
            printf("            \r"); // Überschreibt Zeile
            fflush(stdout);
        }
    }

    hid_close(handle);
    hid_exit();

    return 0;
}
