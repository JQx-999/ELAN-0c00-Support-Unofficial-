#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libusb-1.0/libusb.h>

#define VENDOR_ID 0x04f3
#define PRODUCT_ID 0x0c00

#define EP_CMD_OUT 0x01
#define EP_DATA_IN 0x83
#define EP_STATUS_IN 0x84

int remove_start(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
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
        printf("Cant open the device");
        return 1;
    }
    printf("Device found and opened successfully!!!\n");
    if (libusb_kernel_driver_active(dev_handle, 0) == 1) {
        printf("Kernel driver active. Detaching it bruh ...\n");
        libusb_detach_kernel_driver(dev_handle, 0);
    }
    r = libusb_claim_interface(dev_handle, 0);
    if (r < 0) {
        printf("Failed to claim interface.\n");
        libusb_close(dev_handle);
        libusb_exit(ctx);
        return 1;
    }
    unsigned char scan_cmd[] = {0x40, 0xff, 0x04};
    int actual_length;
    printf("Sending start removing command\n");
    r = libusb_bulk_transfer(dev_handle, EP_CMD_OUT, scan_cmd, sizeof(scan_cmd), &actual_length, 1000);
    unsigned char status_buffer[64];
    if (r == 0 && actual_length == sizeof(scan_cmd))  {
        printf("Command sent successfully!\n");
        r = libusb_bulk_transfer(dev_handle, EP_DATA_IN, status_buffer, sizeof(status_buffer), &actual_length, 5000);
        if (status_buffer[actual_length - 2] == 0x40 && status_buffer[actual_length - 1] == 0x01) {
            printf("Command recieved correctly.\n");
            unsigned char scan_cmd[] = {0x40, 0xff, 0x13, 0xf5, 0x1, 0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5, 0x15, 0x0, 0x0, 0x0, 0x33, 0x23, 0xf4, 0xd0, 0xdc, 0x3e, 0x65, 0xba, 0x19, 0x52, 0x4f, 0xaf, 0xe9, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
            r = libusb_bulk_transfer(dev_handle, EP_CMD_OUT, scan_cmd, sizeof(scan_cmd), &actual_length, 1000);
            if (r == 0 && actual_length == sizeof(scan_cmd))  {
                printf("Removing the 1st scanned fingerprint.\n");
                r = libusb_bulk_transfer(dev_handle, EP_DATA_IN, status_buffer, sizeof(status_buffer), &actual_length, 5000);
                for (int i = 0; i < actual_length; i++) {
                    printf("%02x", status_buffer[i]);
                    
                }
                printf("\n");
                if (status_buffer[actual_length - 2] == 0x40 && status_buffer[actual_length - 1] == 0x00) {
                    printf("Yeah cleaning up!\n");
                    unsigned char scan_cmd[] = {0x40, 0xff, 0x04};
                    r = libusb_bulk_transfer(dev_handle, EP_CMD_OUT, scan_cmd, sizeof(scan_cmd), &actual_length, 1000);
                    if (r == 0 && actual_length == sizeof(scan_cmd))  {
                        printf("Finalizing!\n");
                        r = libusb_bulk_transfer(dev_handle, EP_DATA_IN, status_buffer, sizeof(status_buffer), &actual_length, 5000);
                        if (status_buffer[actual_length - 2] == 0x40 && status_buffer[actual_length - 1] == 0x00) {
                            printf("Taste the success!\n");
                        }
                    }
                }
                
            }
        } 
    } else {
        printf("Failed to send command %d\n.", r);
    }
}