// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <stdio.h>

// Include the trusted EnclaveFibonacci header that is generated
// during the build. This file is generated by calling the
// sdk tool oeedger8r against the EnclaveFibonacci.edl file.
#include "EnclaveFibonacci_t.h"

// This is the function that the host calls. It wraps
// a message from the host before calling back out to
// the host to print a message from there.

int ecall_fibonacci(int *arr, unsigned int count) {
    int retval = 0;
    ocall_log(&retval, "Enclave entered");
    for (int i = 0; i < count; ++i) {
        if (i == 0) { 
            arr[0] = 0; 
        } else if (i == 1) { 
            arr[1] = 1; 
        } else {
            arr[i] = arr[i-1] + arr[i-2];
        }
    }
    retval = 0;
    ocall_log(&retval, "Enclave left");

    return OE_OK;
}

#define TA_UUID                                            \
    { /* 5d286b7e-ff68-4b4b-b7b8-05f55dbfd0c7 */           \
        0x5d286b7e, 0xff68, 0x4b4b,                        \
        {                                                  \
            0xb7, 0xb8, 0x05, 0xf5, 0x5d, 0xbf, 0xd0, 0xc7 \
        }                                                  \
    }

OE_SET_ENCLAVE_OPTEE(
    TA_UUID,
    1 * 1024 * 1024,
    12 * 1024,
    0,
    "1.0.0",
    "EnclaveFibonacci")
