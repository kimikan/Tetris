/***************************************************************************/
/*                                                                         */
/*  Color.h                                                                */
/*                                                                         */
/*    Some ordinary color definition                                       */
/*                                       .                                 */
/*                                                                         */
/*  Copyright 2007 by                                                      */
/*                  Kan(EMail: k32459871@126.com.)                         */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/

#ifndef _COLOR_H_
#define _COLOR_H_

#include "def.h"

const int i = 32;

class ColorMgr
{
public:
    enum Color
    {
        White = MAKE_RGB(255,255,255),
        
        Black = MAKE_RGB(0,0,0),

        Gray = MAKE_RGB(128,128,128),
        LightGray = MAKE_RGB(192,192,192),
        DarkGray = MAKE_RGB(64,64,64),
        
        Red = MAKE_RGB(255,0,0),
        Pink = MAKE_RGB(255,175,175),

        Orange = MAKE_RGB(255,200,0),

        Yellow = MAKE_RGB(255,255,0),
        
        Green = MAKE_RGB(0,255,0),
        
        Magenta = MAKE_RGB(255,0,255),

        Cyan = MAKE_RGB(0,255,255),
        
        Blue = MAKE_RGB(0,0,255)
    };
public:
    /*Construct for the class color*/
    ColorMgr();
    
    /*Custom color RGB*/
    static RGBVAL Get_ColorRGB(uint32 r, uint32 g, uint32 b);

public:
    /*Get color RGB-R*/
    unsigned char static Get_R(RGBVAL _RgbVal);
    
    /*Get color RGB-G*/
    unsigned char static Get_G(RGBVAL _RgbVal);
    
    /*Get color RGB-B*/
    unsigned char static Get_B(RGBVAL _RgbVal);

private:
    /* 2 * 2 * ....* 2 (i) */
    uint32 static pow(int i);
};

#endif