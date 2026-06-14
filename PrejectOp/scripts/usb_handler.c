#include <stdio.h>
#include <unistd.h>
#include <libusb-1.0/libusb.h>
#include "usb_handler.h"


#define VENDOR_ID 0x04f3 
#define PRODUCT_ID 0x0c00


#define EP_CMD_OUT 0x01
#define EP_DATA_IN 0x83
#define EP_STATUS_IN 0x84

int usb_start(void) {
    libusb_context *ctx = NULL;
    libusb_device_handle *dev_handle = NULL;
    int r;


    r = libusb_init(&ctx);
    if (r < 0) {
        printf("Bro, libusb_init failed: %d\n", r);
        return 1;
    }

    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_WARNING);

    dev_handle = libusb_open_device_with_vid_pid(ctx, VENDOR_ID, PRODUCT_ID);
    if (dev_handle == NULL) {
        printf("Couldn't open device. Are you running as root/sudo?\n");
        libusb_exit(ctx);
        return 69;
    }
    printf("Device found and opened successfully!\n");
    if (libusb_kernel_driver_active(dev_handle, 0) == 1) {
        printf("Kernel driver active. Detaching it...\n");
        libusb_detach_kernel_driver(dev_handle, 0);
    }
    
    r = libusb_claim_interface(dev_handle, 0);
    if (r < 0) {
        printf("Failed to claim interface: %d\n", r);
        libusb_close(dev_handle);
        libusb_exit(ctx);
        return 1;
    }
    unsigned char scan_cmd[] = {0x40, 0xff, 0x03}; 
    int actual_length;
    
    printf("Sending 'Start Scanning' command...\n");
    r = libusb_bulk_transfer(dev_handle, EP_CMD_OUT, scan_cmd, sizeof(scan_cmd), &actual_length, 1000);
    if (r == 0 && actual_length == sizeof(scan_cmd)) {
        printf("Command sent successfully.\n");
    } else {
        printf("Failed to send command. Error: %d\n", r);
    }
    unsigned char status_buffer[64];
    printf("Waiting for you to touch the sensor...\n");

    while (1) {

        r = libusb_bulk_transfer(dev_handle, EP_STATUS_IN, status_buffer, sizeof(status_buffer), &actual_length, 5000); // 5 sec timeout
        
        if (r == 0 && actual_length > 0) {

            if (status_buffer[actual_length - 2] == 0x40 && status_buffer[actual_length - 1] == 0x00) {
                printf("\n>>> MATCH SUCCESS! (40 00) <<<\n");

                libusb_release_interface(dev_handle, 0);
                libusb_close(dev_handle);
                libusb_exit(ctx);
                printf("Exiting driver.\n");

                return 0;
            } else if (status_buffer[actual_length - 2] == 0x40 && status_buffer[actual_length - 1] == 0xfe) {
                printf("\n>>> SCAN TIMEOUT / TOUCH LONGER! (40 fe) <<<\n");

                  libusb_release_interface(dev_handle, 0);
                  libusb_close(dev_handle);
                  libusb_exit(ctx);
                  printf("Exiting driver.\n");
                  return -1;
            } else if (status_buffer[actual_length - 2] == 0x40 && status_buffer[actual_length - 1] == 0xfd) {
                printf("\n>>> WRONG FINGER! (40 fd) <<<\n");
                  libusb_release_interface(dev_handle, 0);
                  libusb_close(dev_handle);
                  libusb_exit(ctx);
                  printf("Exiting driver.\n");
                  return 1;
            } else if (status_buffer[actual_length - 2] == 0x40 && (status_buffer[actual_length - 1] - 1) == 0x0) {
                printf("\n>>> MATCH SUCCESS! <<<\n");
                for(int i = 0; i < actual_length; i++) {
                    printf("%02x ", status_buffer[i]);
                }
                libusb_release_interface(dev_handle, 0);
                libusb_close(dev_handle);
                libusb_exit(ctx);
                printf("Exiting driver.\n");

                return 0;
            } else {
                printf("Got unknown status packet. Length: %d | Raw Hex: ", actual_length);
                for(int i = 0; i < actual_length; i++) {
                    printf("%02x ", status_buffer[i]);
                }
                  libusb_release_interface(dev_handle, 0);
                  libusb_close(dev_handle);
                  libusb_exit(ctx);
                  printf("Exiting driver.\n");
                  return 1;
                printf("\n");
            }
        } else if (r == LIBUSB_ERROR_TIMEOUT) {
            printf(".");
            fflush(stdout);
        } else {
            printf("\nRead error: %s\n", libusb_error_name(r));
            break;
        }
    }
    libusb_release_interface(dev_handle, 0);
    libusb_close(dev_handle);
    libusb_exit(ctx);
    printf("Exiting driver.\n");
    return 0;
}

