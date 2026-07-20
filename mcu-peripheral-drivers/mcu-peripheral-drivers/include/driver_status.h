#ifndef DRIVER_STATUS_H
#define DRIVER_STATUS_H

typedef enum {
    DRIVER_OK = 0,
    DRIVER_ERROR,
    DRIVER_TIMEOUT,
    DRIVER_INVALID_ARGUMENT
} driver_status_t;

#endif
