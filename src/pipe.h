#ifndef PIPE_H
#define PIPE_H

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t warp_to_x;
    uint16_t warp_to_y;
    const unsigned char *warp_to_map;
}pipe;

#endif
