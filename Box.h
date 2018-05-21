/***************************************************************************/
/*                                                                         */
/*  Box.h                                                                  */
/*                                                                         */
/*    The rect object which indicates a ...                                */
/*                                       .                                 */
/*                                                                         */
/*  Copyright 2007 by                                                      */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/
#ifndef _BOX_H_
#define _BOX_H_

#include "def.h"
#include "Color.h"

class Box
{
public:
    Box(RGBVAL fillColor);
    Box(RGBVAL fillColor,AEESize& Size);

    /*Set The Draw Size*/
    void SetSize(AEESize& Size);

    /*Draw this at the point*/
    void Draw(AEEPoint& Point,IGraphics* pIGraphics) const;

    /*Set this block is filled or not*/
    void Set_Filled(boolean isFilled);
protected:

private:
    boolean _isFilled;
    AEESize _Size;
    RGBVAL _fillColor;
};

#endif
