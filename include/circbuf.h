/**********************************************************
* Name: circbuf.h
*
* Date: 09/25/2016
*
* Author: Ben Heberlein
*
* Description: This file defines a circular buffer type and
* associated functions.
*
**********************************************************/

#ifndef CIRCBUF_H
#define CIRCBUF_H

#include <stdint.h>

/**********************************************************
* This is the circular buffer state enum used in the
* circbuf_t type.
**********************************************************/
enum circbuf_state {EMPTY, FULL, PARTIAL, INVALID};

/**********************************************************
* circbuf_t
* Author: Ben Heberlein
* Date: 09/25/2016
* Description: This is the main circular buffer structure.
* It has fields for buffer memory, headm tail, capacity,
* current size, and internal state.
**********************************************************/
typedef struct circbuf {

    uint8_t *buf;
    uint8_t *head;
    uint8_t *tail;

    uint16_t capacity;
    uint16_t size;

    enum circbuf_state STATUS;

} circbuf_t;

/***********************************************************
* buffer_full       : uint8_t buffer_full(circbuf_t *circular_buffer);
*   returns         : 1 for full, 0 for not full, -1 for error
    circular_buffer : The circular buffer to be checked
* Author            : Ben Heberlein
* Date              : 09/25/2016
* Description       : Check if circular buffer is full
***********************************************************/
uint8_t buffer_full(circbuf_t *circular_buffer);

/***********************************************************
* buffer_empty      : uint8_t buffer_empty(circbuf_t *circular_buffer);
*   returns         : 1 for empty, 0 for not empty, -1 for error
*   circular_buffer : The circular buffer to be checked
* Author            : Ben Heberlein
* Date              : 09/25/2016
* Description       : Check if circular buffer is empty
***********************************************************/
uint8_t buffer_empty(circbuf_t *circular_buffer);

/***********************************************************
* add_item          : uint8_t add_item(uint8_t data, circbuf_t *circular_buffer);
*   returns         : 0 for success, -1 for failure
*   data            : The data to be added
*   circular_buffer : The circular buffer to be added to
* Author            : Ben Heberlein
* Date              : 09/25/2016
* Description       : Add an item to the circular buffer
***********************************************************/
uint8_t add_item(uint8_t data, circbuf_t *circular_buffer);

/***********************************************************
* remove_item       : uint8_t remove_item(circbuf_t *circular_buffer);
*   returns         : The data if successful, 0 if buffer is empty
*   circular_buffer : The circular buffer to get data from
* Author            : Ben Heberlein
* Date              : 09/25/2016
* Description       : Remove an item from the circular buffer
***********************************************************/
uint8_t remove_item(circbuf_t *circular_buffer);

#endif
