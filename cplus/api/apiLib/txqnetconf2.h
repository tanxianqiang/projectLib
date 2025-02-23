/**
 * @file example.h
 * @author Roman Janota <xjanot04@fit.vutbr.cz>
 * @brief libnetconf2 example header
 *
 * @copyright
 * Copyright (c) 2022 CESNET, z.s.p.o.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef _TXQNETCONF2_H_
#define _TXQNETCONF2_H_

#include <stdio.h>

/* directory with library YANG modules */
#define MODULES_DIR "@CMAKE_SOURCE_DIR@/modules"

/* directory with examples source code and this header */
#define EXAMPLES_DIR "@CMAKE_SOURCE_DIR@/examples"

/* SSH listening IP address */
#define SSH_ADDRESS "127.0.0.1"

/* SSH 'password' authentication exptected username and password */
#define SSH_USERNAME "admin"

/* time in microseconds to sleep for if there are no new RPCs and no new sessions */
#define BACKOFF_TIMEOUT_USECS 100

#define ERR_MSG_CLEANUP(msg) \
        rc = 1; \
        fprintf(stderr, "%s", msg); \
        goto cleanup

#endif
