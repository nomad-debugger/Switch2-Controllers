#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libusb-1.0/libusb.h>
#include <unistd.h>

#define VENDOR_ID  0x057E
const uint16_t PRODUCT_IDS[] = {0x2066, 0x2067, 0x2069, 0x2073};
#define NUM_PRODUCT_IDS (sizeof(PRODUCT_IDS)/sizeof(PRODUCT_IDS[0]))
#define INTERFACE_NUM 1

const unsigned char DEFAULT_REPORT_DATA[] = {
    0x03, 0x91, 0x00, 0x0d, 0x00, 0x08,
    0x00, 0x00, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
const unsigned char SET_LED_DATA[] = {
    0x09, 0x91, 0x00, 0x07, 0x00, 0x08,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int find_bulk_out_endpoint(libusb_device_handle* handle, uint8_t* endpoint_out) {
    libusb_device* dev = libusb_get_device(handle);
    struct libusb_config_descriptor* config;
    if (libusb_get_config_descriptor(dev, 0, &config) != 0)
        return -1;
    for (int i = 0; i < config->bNumInterfaces; i++) {
        const struct libusb_interface* iface = &config->interface[i];
        for (int j = 0; j < iface->num_altsetting; j++) {
            const struct libusb_interface_descriptor* altsetting = &iface->altsetting[j];
            if (altsetting->bInterfaceNumber == INTERFACE_NUM) {
                for (int k = 0; k < altsetting->bNumEndpoints; k++) {
                    const struct libusb_endpoint_descriptor* ep = &altsetting->endpoint[k];
                    if ((ep->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK) == LIBUSB_TRANSFER_TYPE_BULK &&
                        (ep->bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK) == LIBUSB_ENDPOINT_OUT) {
                        *endpoint_out = ep->bEndpointAddress;
                        libusb_free_config_descriptor(config);
                        return 0;
                    }
                }
            }
        }
    }
    libusb_free_config_descriptor(config);
    return -1;
}

int main() {
    libusb_context* ctx = NULL;
    libusb_init(&ctx);

    while (1) {
        libusb_device_handle* handle = NULL;
        // Suche nach Controller
        for (int i = 0; i < NUM_PRODUCT_IDS; i++) {
            handle = libusb_open_device_with_vid_pid(ctx, VENDOR_ID, PRODUCT_IDS[i]);
            if (handle) {
                printf("Device found (PID: 0x%04X).\n", PRODUCT_IDS[i]);
                break;
            }
        }
        if (!handle) {
            usleep(500 * 1000);
            continue;
        }

        if (libusb_claim_interface(handle, INTERFACE_NUM) != 0) {
            libusb_close(handle);
            usleep(1000 * 1000);
            continue;
        }

        uint8_t endpoint_out = 0;
        if (find_bulk_out_endpoint(handle, &endpoint_out) != 0) {
            libusb_release_interface(handle, INTERFACE_NUM);
            libusb_close(handle);
            usleep(1000 * 1000);
            continue;
        }

        int transferred;
        libusb_bulk_transfer(handle, endpoint_out, (unsigned char*)DEFAULT_REPORT_DATA,
                             sizeof(DEFAULT_REPORT_DATA), &transferred, 1000);
        libusb_bulk_transfer(handle, endpoint_out, (unsigned char*)SET_LED_DATA,
                             sizeof(SET_LED_DATA), &transferred, 1000);

        printf("Enabling done! Warte auf Entfernen/Einstöpseln...\n");

        // Warte bis Gerät entfernt wird
        while (1) {
            unsigned char pingbuf[1] = {0};
            int res = libusb_bulk_transfer(handle, endpoint_out, pingbuf, 0, &transferred, 100);
            if (res == LIBUSB_ERROR_NO_DEVICE) break;
            usleep(1000 * 1000);
        }

        libusb_release_interface(handle, INTERFACE_NUM);
        libusb_close(handle);
        printf("Controller entfernt. Überwache weiter...\n");
        usleep(1000 * 1000);
    }
    libusb_exit(ctx);
    return 0;
}
