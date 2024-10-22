#include <stdbool.h>

struct button
{
    int x, y;
    int w, h;
    char text[32];
    int is_pressed;
    bool is_filled;
};

typedef struct button button;