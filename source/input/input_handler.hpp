//
// Created by xdbeef on 07.04.18.
//

#ifndef SPELUNKYDS_INPUTHANDLER_H
#define SPELUNKYDS_INPUTHANDLER_H

/**
 * keysDown - recently pressed keys
 * keysHeld - keys that are currently hold
 */

class InputHandler {
public:
    void updateInput();

    int keys_held{};
    int keys_down{};
    bool stop_handling{};

    //TODO An array for these:

    bool left_key_held{};
    bool right_key_held{};
    bool down_key_held{};
    bool up_key_held{};
    bool b_key_held{};
    bool y_key_held{};
    bool l_bumper_held{};
    bool r_bumper_held{};
    bool r_bumper_down{};
    bool l_bumper_down{};
    bool x_key_down{};
    bool y_key_down{};
    bool a_key_down{};
    bool b_key_down{};
};


#endif //SPELUNKYDS_INPUTHANDLER_H
