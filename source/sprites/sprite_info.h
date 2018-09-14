//
// Created by xdbeef on 26.03.18.
//

#ifndef SPELUNKYDS_SPRITEINFO_H
#define SPELUNKYDS_SPRITEINFO_H


#include <nds/arm9/sprite.h>
#include "spritesheet_type.hpp"
#include "../memory/oam_type.hpp"

class SpriteInfo {
public:
    u16 *sprite_address{};
    int offset_multiplier{};

    u8 oamId_palette{};
    int oamId_tiles{};

    int width{};
    int height{};
    int angle{};
    SpriteEntry *entry{};
    SpritesheetType spriteType{};

    u16 oam_address{};
    OamType oamType{};

    void updateFrame(u8 *tile, int size);
};


#endif //SPELUNKYDS_SPRITEINFO_H
