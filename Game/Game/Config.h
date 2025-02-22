#pragma once
#ifndef CONFIG_H
#define CONFIG_H
#include "Type.h"



/* ゲーム全体に影響が出るパラメータはここに定義する */
#define WINDOW_WIDE    (S16)1024
#define WINDOW_HEIGHT  (S16)768

#define MAX_DELTA_TIME (F32)0.05

/* 頂点情報数 */
#define COODINATE_NUM            (3)              //XYZ座標
#define TOTAL_VERTS_NUM          (COODINATE_NUM)  //頂点のデータ量
#define COODINATE_ATRIBUTE_POS   (0)              //XYZattributeの位置

#endif 
