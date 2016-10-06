/**********************************************************
* Name: circbuf.c
*
* Date: 09/25/2016
*
* Author: Ben Heberlein
*
* Description: This file implements several functions to
* manage a circular_buffer.
*
**********************************************************/

#include <stdint.h>
#include <stdio.h>
#include "circbuf.h"

/***********************************************************
* buffer_full       : uint8_t buffer_full(circbuf_t *circular_buffer);
*   returns         : 1 for full, 0 for not full, -1 for error
    circular_buffer : The circular buffer to be checked
* Author            : Ben Heberlein
* Date              : 09/25/2016
* Description       : Check if circular buffer is full
***********************************************************/
uint8_t buffer_full(circbuf_t *circular_buffer) {
    // Check if valid buffer
    if (circular_buffer == NULL) {
        return -1;
    }

    if (circular_buffer->STATUS == FULL) {
        return 1;
    } else {
        return 0;
    }
}

/***********************************************************
* buffer_empty      : uint8_t buffer_empty(circbuf_t *circular_buffer);
*   returns         : 1 for empty, 0 for not empty, -1 for error
*   circular_buffer : The circular buffer to be checked
* Author            : Ben Heberlein
* Date              : 09/25/2016
* Description       : Check if circular buffer is empty
***********************************************************/
uint8_t buffer_empty(circbuf_t *circular_buffer) {
    // Check if valid buffer
    if (circular_buffer == NULL) {
        return -1;
    }

    if (circular_buffer->STATUS == EMPTY) {
        return 1;
    } else {
        return 0;
    }
}

/***********************************************************
* add_item          : uint8_t add_item(uint8_t data, circbuf_t *circular_buffer);
*   returns         : 0 for success, -1 for failure
*   data            : The data to be added
*   circular_buffer : The circular buffer to be added to
* Author            : Ben Heberlein
* Date              : 09/25/2016
* Description       : Add an item to the circular buffer
***********************************************************/
uint8_t add_item(uint8_t data, circbuf_t *circular_buffer) {
    // Check if valid buffer
    if (circular_buffer == NULL) {
        return -1;
    }

    // Check if full
    if (circular_buffer->STATUS == FULL) {
        return -1;
    }

    // Set data
    *(circular_buffer->head) = data;

    // Increment head and check for wrap
    circular_buffer->head++;
    if ((circular_buffer->head - circular_buffer->buf) > circular_buffer->capacity) {
        circular_buffer->head -= circular_buffer->capacity;
    }
    circular_buffer->size++;

    // Set new state
    if (circular_buffer->size == circular_buffer->capacity ||
        circular_buffer->head == circular_buffer->tail) {

        circular_buffer->STATUS = FULL;
    } else {
        circular_buffer->STATUS = PARTIAL;
    }

    return 0;
}

/***********************************************************
* remove_item       : uint8_t remove_item(circbuf_t *circular_buffer);
*   returns         : The data if successful, 0 if buffer is empty
*   circular_buffer : The circular buffer to get data from
* Author            : Ben Heberlein
* Date              : 09/25/2016
* Description       : Remove an item from the circular buffer
***********************************************************/
uint8_t remove_item(circbuf_t *circular_buffer) {
    // Check if valid buffer
    if (circular_buffer == NULL) {
        return 0;
    }

    // Check if empty
    if (circular_buffer->STATUS == FULL) {
        return 0;
    }

    // Get data
    uint8_t ret = *(circular_buffer->tail);

    // Increment tail and check for wrap
    circular_buffer->tail++;
    if ((circular_buffer->tail - circular_buffer->buf) > circular_buffer->capacity) {
        circular_buffer->tail -= circular_buffer->capacity;
    }
    circular_buffer->size--;

    // Set new state
    if (circular_buffer->size == 0 || circular_buffer->head == circular_buffer->tail+1) {
        circular_buffer->STATUS = EMPTY;
    } else {
        circular_buffer->STATUS = PARTIAL;
    }

    return ret;

}

