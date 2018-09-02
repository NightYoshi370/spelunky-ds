//
// Created by xdbeef on 02.06.18.
//


#include "../spritesheet_type.hpp"
#include "../../globals_declarations.h"
#include "../../collisions/collisions.h"
#include "../../../build/gfx_saleable.h"
#include "../animations/got_collectible.h"
#include "../moving_object.h"
#include "spike_shoes.h"

#define SPIKE_SHOES_POS_INC_DELTA 15

void SpikeShoes::draw() {


    if (ready_to_dispose) {
        mainSpriteInfo->entry->isHidden = true;
        subSpriteInfo->entry->isHidden = true;
        return;
    } else {
        mainSpriteInfo->entry->isHidden = false;
        subSpriteInfo->entry->isHidden = false;
    }


    set_position();

    if (collected)
        return;


    if (bought && check_if_can_be_equipped()) {
        equip();
    } else if (!bought && !hold_by_main_dude) {
        check_if_can_be_pickuped();
    }

    if (hold_by_main_dude) {
        set_pickuped_position(4, -4);
        if (shopping_transaction(this)) {
            collected = true;
            equip();
        }
    }
}


void SpikeShoes::init() {
    initSprite();
    init_anim_icon();
}

void SpikeShoes::updateSpeed() {

    if (collected)
        return;

    limit_speed(MAX_X_SPEED_SPIKE_SHOES, MAX_Y_SPEED_SPIKE_SHOES);

    pos_inc_timer += *global::timer;

    bool change_pos = (pos_inc_timer > SPIKE_SHOES_POS_INC_DELTA) && !hold_by_main_dude;

    if (change_pos) {
        update_position();
        apply_friction(0.055);
        apply_gravity(GRAVITY_DELTA_SPEED);
        pos_inc_timer = 0;
    }

}

void SpikeShoes::updateCollisionsMap(int x_current_pos_in_tiles, int y_current_pos_in_tiles) {

    if (collected)
        return;

    MapTile *tiles[9];
    Collisions::getNeighboringTiles(global::level_generator->map_tiles, x_current_pos_in_tiles,
                                    y_current_pos_in_tiles,
                                    tiles);

    upperCollision = Collisions::checkUpperCollision(tiles, &x, &y, &ySpeed, physical_width, true, BOUNCING_FACTOR_Y);
    bottomCollision = Collisions::checkBottomCollision(tiles, &x, &y, &ySpeed, physical_width, physical_height, true, BOUNCING_FACTOR_Y);
    leftCollision = Collisions::checkLeftCollision(tiles, &x, &y, &xSpeed, physical_width, physical_height, true, BOUNCING_FACTOR_X);
    rightCollision = Collisions::checkRightCollision(tiles, &x, &y, &xSpeed, physical_width, physical_height, true, BOUNCING_FACTOR_X);
}

void SpikeShoes::initSprite() {


    subSpriteInfo = global::sub_oam_manager->initSprite(gfx_saleablePal, gfx_saleablePalLen,
                                                        nullptr, sprite_width * sprite_height, sprite_width,
                                                        spritesheet_type, true, false, LAYER_LEVEL::MIDDLE_TOP);
    mainSpriteInfo = global::main_oam_manager->initSprite(gfx_saleablePal, gfx_saleablePalLen,
                                                          nullptr, sprite_width * sprite_height, sprite_width,
                                                          spritesheet_type, true, false, LAYER_LEVEL::MIDDLE_TOP);

    frameGfx = (u8 *) gfx_saleableTiles + (sprite_width * sprite_height * (12) / 2);

    subSpriteInfo->updateFrame(frameGfx, sprite_width * sprite_height);
    mainSpriteInfo->updateFrame(frameGfx, sprite_width * sprite_height);

}

void SpikeShoes::set_position() {

    if (collected) {
        mainSpriteInfo->entry->priority = OBJPRIORITY_0;

        mainSpriteInfo->entry->x = x;
        mainSpriteInfo->entry->y = y;

        subSpriteInfo->entry->isHidden = true;
        mainSpriteInfo->entry->isHidden = false;

    } else {
        int main_x, main_y, sub_x, sub_y;
        get_x_y_viewported(&main_x, &main_y, &sub_x, &sub_y);

        mainSpriteInfo->entry->x = main_x;
        mainSpriteInfo->entry->y = main_y;

        subSpriteInfo->entry->x = sub_x;
        subSpriteInfo->entry->y = sub_y;
    }

    mainSpriteInfo->entry->vFlip = false;
    mainSpriteInfo->entry->hFlip = false;

    subSpriteInfo->entry->vFlip = false;
    subSpriteInfo->entry->hFlip = false;

    update_anim_icon(x, y, physical_width);

}

SpikeShoes::SpikeShoes() {
    cost = 4 * 1000;
    name = "SPIKE SHOES";
    physical_height = SPIKE_SHOES_PHYSICAL_HEIGHT;
    physical_width = SPIKE_SHOES_PHYSICAL_WIDTH;
    sprite_height = SPIKE_SHOES_SPRITE_HEIGHT;
    sprite_width = SPIKE_SHOES_SPRITE_WIDTH;
    spritesheet_type = SpritesheetType::SALEABLE;
}

void SpikeShoes::equip() {

    GotCollectible *g = new GotCollectible();
    g->x = x - 12;
    g->y = y - 20;
    g->collectible_type = 0;
    g->init();
    global::sprites.push_back(g);

    if (!global::main_dude->carrying_spike_shoes) {
        global::main_dude->carrying_spike_shoes = true;
        set_position();
        collected = true;
        x = HUD_ITEMS_ROW_X;
        y = global::hud->items_offset_y;
        global::hud->increment_offset_on_grabbed_item();
    } else {
        mainSpriteInfo->entry->isHidden = true;
        subSpriteInfo->entry->isHidden = true;
        ready_to_dispose = true;
    }

}

