//
// Created by xdbeef on 23.04.18.
//

#include "Jar.h"
#include "../MovingObject.h"
#include "Rock.h"
#include "../../Globals.h"
#include "../../../build/jar.h"
#include "../../collisions/Collisions.h"
#include "../../tiles/MapUtils.h"


void Jar::draw() {

    if (frame >= 7) {
        mainSpriteInfo->entry->isHidden = true;
        subSpriteInfo->entry->isHidden = true;
        return;
    }

    if (hold_by_main_dude && global::input_handler->y_key_down && global::input_handler->down_key_held) {
        hold_by_main_dude = false;
        global::main_dude->holding_item = false;
    } else if (!killed && global::input_handler->y_key_down && global::input_handler->down_key_held &&
               /*bottomCollision && */!global::main_dude->holding_item) {

        if (Collisions::checkCollisionWithMainDude(x, y, 8, 8)) {
            hold_by_main_dude = true;
            global::main_dude->holding_item = true;
//            std::cout << "TOOK ITEM";
        }
    }


    if (hold_by_main_dude) {

        y = global::main_dude->y + 6;

        if (global::main_dude->state == 1) {
            x = global::main_dude->x - 2;
        } else
            x = global::main_dude->x + 10;
    }


    int main_x = x - global::camera->x;
    int main_y = y - global::camera->y + 1;
    int sub_x = x - global::camera->x;
    int sub_y = y - global::camera->y - 192 + 1;

    if (global::camera->y + 192 > this->y + 8 || global::camera->y + 192 + 192 < this->y - 8) {
        sub_x = -128;
        sub_y = -128;
    }
    if (global::camera->y > this->y + 8 || global::camera->y + 192 < this->y - 8) {
        main_x = -128;
        main_y = -128;

    }


    if (sub_y + 8 < 0 || sub_x + 8 < 0) {
        sub_x = -128;
        sub_y = -128;
    }

    if (main_y + 8 < 0 || main_x + 8 < 0) {
        main_x = -128;
        main_y = -128;
    }


    if (killed && frame < 7) {

        frameTimer += *global::timer;

        if (frameTimer > 50) {
            frame++;

            frameGfx = (u8 *) jarTiles + ((frame + 1) * 8 * 8 / 2);
            subSpriteInfo->updateFrame(frameGfx, 8 * 8);
            mainSpriteInfo->updateFrame(frameGfx, 8 * 8);

            frameTimer = 0;
        }

        if (frame >= 7) {
            mainSpriteInfo->entry->isHidden = true;
            subSpriteInfo->entry->isHidden = true;
            ready_to_dispose = true;
//            std::cout<<"HIDDEN";
//            mainSpriteInfo = nullptr;
//            subSpriteInfo = nullptr;
        }

    }

    if (xSpeed > 0 || ySpeed > 0) {
        for (int a = 0; a < global::sprites.size(); a++) {
            if ((global::sprites.at(a)->spriteType == SpritesheetType::SNAKE ||
                 global::sprites.at(a)->spriteType == SpritesheetType::BAT||
                 global::sprites.at(a)->spriteType == SpritesheetType::SPIDER)
                && !global::sprites.at(a)->killed) {
                if (Collisions::checkCollisionBodies(x, y, 8, 8, global::sprites.at(a)->x, global::sprites.at(a)->y, 16,
                                                     16)) {
                    global::sprites.at(a)->kill();
                    killed = true;
                    frame = 1;
                    mainSpriteInfo->entry->isHidden = true;
                    subSpriteInfo->entry->isHidden = true;
                    ready_to_dispose = true;
                    global::killedNpcs.push_back(spriteType);
//                    std::cout<<"HIDDEN";
                }
            }
        }
    }


    mainSpriteInfo->entry->x = main_x;
    mainSpriteInfo->entry->y = main_y;

    mainSpriteInfo->entry->hFlip=false;
    subSpriteInfo->entry->hFlip= false;

    mainSpriteInfo->entry->vFlip=false;
    subSpriteInfo->entry->vFlip= false;

    subSpriteInfo->entry->x = sub_x;
    subSpriteInfo->entry->y = sub_y;


    if (global::main_dude->whip && !killed && global::main_dude->whip_timer > 120) {
        if (Collisions::checkCollisionWithMainDudeWhip(x, y, 8, 8)) {
            killed = true;
            mainSpriteInfo->entry->isHidden = true;
            subSpriteInfo->entry->isHidden = true;
            ready_to_dispose = true;
//            std::cout<<"HIDDEN";
        }
    }

}


void Jar::init() {

    initSprite();

    activated_by_main_dude = true;

}

void Jar::updateSpeed() {

    if(killed)
        return;

    if (xSpeed > MAX_X_SPEED_ROCK)
        xSpeed = MAX_X_SPEED_ROCK;
    if (xSpeed < -MAX_X_SPEED_ROCK)
        xSpeed = -MAX_X_SPEED_ROCK;

    if (ySpeed > MAX_Y_SPEED_ROCK)
        ySpeed = MAX_Y_SPEED_ROCK;
    if (ySpeed < -MAX_Y_SPEED_ROCK)
        ySpeed = -MAX_Y_SPEED_ROCK;

    pos_inc_timer += *timer;

    bool change_pos = (pos_inc_timer > 15) && !hold_by_main_dude;

    if (change_pos) {
        updatePosition();
    }

}

void Jar::updatePosition() {

    if (bottomCollision && xSpeed > 0) {
        xSpeed -= 0.2;
        if (xSpeed < 0)
            xSpeed = 0;
    }
    if (bottomCollision && xSpeed < 0) {
        xSpeed += 0.2;
        if (xSpeed > 0)
            xSpeed = 0;
    }

    double tempXspeed = abs(xSpeed);
    double tempYspeed = abs(ySpeed);

    int old_xx = -1;
    int old_yy = -1;
    int xx;
    int yy;

    while (tempXspeed > 0 || tempYspeed > 0) {
        if (tempXspeed > 0) {
            if (xSpeed > 0) {
                x += 1;
            } else if (xSpeed < 0) {
                x -= 1;
            }
        }
        if (tempYspeed > 0) {
            if (ySpeed > 0)
                y += 1;
            else if (ySpeed < 0)
                y -= 1;
        }

//            Collisions::getCenterTile(this->x, this->y, MAIN_DUDE_HEIGHT, MAIN_DUDE_WIDTH, xx, yy);
//fixme

        xx = floor_div(this->x + 0.5 * BOMB_SIZE, 16);
        yy = floor_div(this->y + 0.5 * BOMB_SIZE, 16);

        if (old_xx != xx || old_yy != yy) {
            updateCollisionsMap(xx, yy);
        }

        old_xx = xx;
        old_yy = yy;

        tempXspeed--;
        tempYspeed--;
    }


    if (!bottomCollision)
        ySpeed += GRAVITY_DELTA_SPEED * 0.8;

    pos_inc_timer = 0;
}

void Jar::updateCollisionsMap(int x_current_pos_in_tiles, int y_current_pos_in_tiles) {

    MapTile *tiles[9];
    Collisions::getNeighboringTiles(global::level_generator->mapTiles, x_current_pos_in_tiles, y_current_pos_in_tiles,
                                    tiles);

    bottomCollision = Collisions::checkBottomCollision(tiles, &x, &y, &ySpeed, 8, 8, true);
    leftCollision = Collisions::checkLeftCollision(tiles, &x, &y, &xSpeed, 8, 8, true);
    rightCollision = Collisions::checkRightCollision(tiles, &x, &y, &xSpeed, 8, 8, true);
    upperCollision = Collisions::checkUpperCollision(tiles, &x, &y, &ySpeed, 8, true);

    if ((abs(xSpeed) > 1 || abs(ySpeed) > 1) && (bottomCollision || leftCollision || rightCollision || upperCollision)) {
        killed = true;
        mainSpriteInfo->entry->isHidden = true;
        subSpriteInfo->entry->isHidden = true;
        ready_to_dispose = true;
//        std::cout<<"HIDDEN";
    }

}

void Jar::initSprite() {
    subSpriteInfo = global::sub_oam_manager->initSprite(jarPal, jarPalLen,
                                                        nullptr, 8 * 8, 8, JAR, true, false);
    mainSpriteInfo = global::main_oam_manager->initSprite(jarPal, jarPalLen,
                                                          nullptr, 8 * 8, 8, JAR, true, false);


    frameGfx = (u8 *) jarTiles;
    subSpriteInfo->updateFrame(frameGfx, 8 * 8);
    mainSpriteInfo->updateFrame(frameGfx, 8 * 8);
}
