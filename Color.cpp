/***************************************************************************/
/*                                                                         */
/*  Color.cpp                                                              */
/*                                                                         */
/*    The Color definition                                                 */
/*    It was designed as a static object .                                 */
/*                                                                         */
/*  Copyright 2007 by                                                      */
/*                  Kan(EMail: k32459871@126.com.)                         */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/

#include "Color.h"
#include "Enuos.h"

ColorMgr::ColorMgr()
{
    /*
    void* pApp = GETAPPINSTANCE();
    NewEnuos* pMe = (NewEnuos*)pApp;
    */
}

RGBVAL ColorMgr::Get_ColorRGB(uint32 r, uint32 g, uint32 b)
{
    return MAKE_RGB(r,g,b);
}

unsigned char ColorMgr::Get_R(RGBVAL _RgbVal)
{
    return static_cast<char>((_RgbVal & 0x0000ff00) >> 8);
}

unsigned char ColorMgr::Get_G(RGBVAL _RgbVal)
{
    return static_cast<char>((_RgbVal & 0x00ff0000) >> 16);
}

unsigned char ColorMgr::Get_B(RGBVAL _RgbVal)
{
    return static_cast<char>((_RgbVal & 0xff000000) >> 24);
}


uint32 ColorMgr::pow(int i)
{
    uint32 sum = 1;
    for(int x = 0; x < i; x++)
    {
        sum*=2;
    }
    
    return sum;
}