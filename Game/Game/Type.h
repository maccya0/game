#pragma once
#pragma once
#ifndef TYPE_H
#define TYPE_H
#include <cstdint>
/* �^���̒�` */
/* �����^ */
typedef std::int8_t   S8;
typedef std::int16_t  S16;
typedef std::int32_t  S32;
typedef std::int64_t  S64;
typedef std::uint8_t  U8;
typedef std::uint16_t U16;
typedef std::uint32_t U32;
typedef std::uint64_t U64;

/* ���������_�^ */
typedef float   F32;
typedef double  F64;

#define MS 1.0                      //1ms
#define SECOND       1000.0         //1s
#define FPS 60                      //fps
#define FLAME_TIME  int(SECOND/FPS) //1�t���[������       
#endif 