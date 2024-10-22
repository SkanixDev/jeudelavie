struct cell
{
    int x;
    int y;
    int state;
    int neighbors;
};
typedef struct cell cell;

struct grid
{
    int width;
    int height;
    cell **cells;
};

typedef struct grid grid;