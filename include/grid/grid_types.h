struct cell
{
    int x;
    int y;
    int state;
};
typedef struct cell cell;

struct grid
{
    int width;
    int height;
    cell **cells;
};

typedef struct grid grid;