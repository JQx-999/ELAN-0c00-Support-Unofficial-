#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libusb-1.0/libusb.h>

#define VENDOR_ID 0x04f3 
#define PRODUCT_ID 0x0c00
#define EP_CMD_OUT 0x01 
#define EP_STATUS_IN 0x84 

int main() {
    libusb_context *ctx = NULL;
    libusb_device_handle *dev_handle = NULL;
    
    libusb_init(&ctx);
    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_NONE); 

    dev_handle = libusb_open_device_with_vid_pid(ctx, VENDOR_ID, PRODUCT_ID);
    if (dev_handle == NULL) {
        libusb_exit(ctx);
        return 1; 
    }

    if (libusb_kernel_driver_active(dev_handle, 0) == 1) {
        libusb_detach_kernel_driver(dev_handle, 0);
    }
    libusb_claim_interface(dev_handle, 0);


    unsigned char scan_cmd[] = {0x40, 0xff, 0x03}; 
    int actual_length;
    libusb_bulk_transfer(dev_handle, EP_CMD_OUT, scan_cmd, sizeof(scan_cmd), &actual_length, 1000);

    unsigned char status_buffer[64];
    int r;
    

    r = libusb_bulk_transfer(dev_handle, EP_STATUS_IN, status_buffer, sizeof(status_buffer), &actual_length, 10000); 
    
    int exit_code = 1; 

    if (r == 0 && actual_length > 0) {
        if (status_buffer[actual_length - 2] == 0x40 && status_buffer[actual_length - 1] == 0x00) {
            exit_code = 0; 
        } else {
            exit_code = 1; 
        }
    }

    // Clean up
    libusb_release_interface(dev_handle, 0);
    libusb_close(dev_handle);
    libusb_exit(ctx);
    
    return exit_code;
}
