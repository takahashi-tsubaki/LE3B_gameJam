#pragma once

//当たり判定属性
//地面
const unsigned short COLLISION_ATTR_LANDSPHERE = 0b1 << 0;
const unsigned short COLLISION_ATTR_ALLIES = 0b1 << 1;
//自機
const unsigned short COLLISION_ATTR_PLAYERS = 0b1 << 2;
// 電池の当たり判定用
//電池
const unsigned short COLLISION_ATTR_POWERCHIP = 0b1 << 3;
//カーソル
const unsigned short COLLISION_ATTR_CURSOR = 0b1 << 4;
//設置場所
const unsigned short COLLISION_ATTR_POWERCHIP_AREA = 0b1 << 5;