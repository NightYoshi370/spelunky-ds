//
// Created by xdbeef on 29.04.18.
//

#include "../../../build/gfx_copyrights.h"
#include "../../GameState.hpp"

#include "Copyrights.h"
#include "../../graphics/SpriteUtils.hpp"

Copyrights::Copyrights(int x, int y) :
        BaseDecoration(x, y, copyrights_sprite_width, copyrights_sprite_height, copyrights_spritesheet_type) {
    // Cleaning allocated graphics from trash data.
    for (auto &subSpriteInfo : _subSpriteInfos) subSpriteInfo = nullptr;
    init_sprites();
}

void Copyrights::delete_sprites() {
    for (auto &subSpriteInfo : _subSpriteInfos) {
        delete subSpriteInfo;
        subSpriteInfo = nullptr;
    }
}

void Copyrights::init_sprites() {

    delete_sprites();

    for (int a = 0; a < copyrights_graphics; a++) {
        _subSpriteInfos[a] = OAMManager::sub().initSprite(gfx_copyrightsPal, gfx_copyrightsPalLen, nullptr,
                                                                 _sprite_size, ObjSize::OBJSIZE_32, _spritesheet_type,
                                                                 true, false, LAYER_LEVEL::MIDDLE_TOP);

        u8 *frame_gfx = sprite_utils::get_frame((u8 *) gfx_copyrightsTiles, _sprite_size, a);
        sprite_utils::update_frame(frame_gfx, _sprite_size, _subSpriteInfos[a]);
    }

    for (auto &sprite_info : _subSpriteInfos) {
        sprite_utils::set_horizontal_flip(false, sprite_info);
        sprite_utils::set_vertical_flip(false, sprite_info);
        sprite_utils::set_visibility(true, sprite_info);
    }

    update_sprites_position();
}

void Copyrights::update_sprites_position() {

    int dummy, sub_x, sub_y;
    get_x_y_viewported(&dummy, &dummy, &sub_x, &sub_y);

    for (int a = 0; a < copyrights_graphics; a++)
        sprite_utils::set_entry_xy(_subSpriteInfos[a],
                                   static_cast<u16>(sub_x + (_sprite_width * a)), static_cast<u16>(sub_y));
}

void Copyrights::print_classname() const {
    printf("COPYRIGHTS\n");
}

void Copyrights::update_decoration_specific() {
    // Does nothing besides displaying sprites.
}
