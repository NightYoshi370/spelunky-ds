//
// Created by xdbeef on 02.05.18.
//

#ifndef SPELUNKYDS_ENTRANCEROOMS_H
#define SPELUNKYDS_ENTRANCEROOMS_H


static int entrance_room[3][10][10] = {
        {
                {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                {0, 0, 0, 0, 0, 0, 0, 9, 0, 0},
                {2, 0, 4, 4, 4, 4, 4, 10, 0, 2},
                {1, 0, 0, 0, 0,  0, 0, 9, 0, 3},
                {1, 0, 0, 4, 4, 4, 0, 9, 0, 0},
                {3, 0, 0, 0, 0, 0, 0, 9, 0, 2},
                {0, 0, 0, 0, 0, 0, 0, 9, 2, 1},
                {0, 0, 0, 0, 0, 0,  11, 2, 7, 1},
                {2, 2, 2, 2, 2, 2, 2, 2, 2, 6},
                {1, 1, 1, 1, 1, 1, 1, 2, 1, 6}
        },
        {
                {3, 3, 3, 1, 1, 1, 3, 3, 3, 3},
                {0, 0, 0, 3, 3, 3, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 2,  2, 0},
                {0, 0, 0, 0, 0,  0, 4, 3, 3, 4},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 2, 4, 0, 0, 5, 0},
                {0, 0, 0, 0, 7, 11, 0,  0, 2, 0},
                {5, 2, 2, 2, 2, 2, 2, 2, 1, 6},
                {1, 1, 1, 1, 1, 1, 1, 2, 1, 6}
        },
        {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {4, 0, 0, 0, 0, 0, 0, 0, 0,},
                {0, 0, 0, 2, 4, 0, 0, 2,  9, 4},
                {0, 0, 0, 1, 11, 0, 0, 1, 9, 0},
                {0, 0, 2, 1, 2, 2, 2, 1, 9, 0},
                {0, 0, 5, 8, 7, 1, 6, 1, 9, 0},
                {0, 1, 7, 6, 1, 1, 1, 1, 9, 0},
                {2, 1, 1, 1, 8, 5,  0,  0, 9, 0},
                {5, 1, 1, 1, 1, 7, 0, 0, 9, 2},
                {1, 1, 1, 1, 1, 1, 2, 2, 1, 1},
        },
};

//1 if loot can be placed
static int entrance_room_loot[3][10][10] = {
        {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
};

#endif //SPELUNKYDS_ENTRANCEROOMS_H