/***************************************************************************/
/*                                                                         */
/*  Box.cpp                                                                */
/*                                                                         */
/*    The rect object which indicates a ...                                */
/*                                       .                                 */
/*                                                                         */
/*  Copyright 2007                       */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/

#include "Box.h"

Box::Box(RGBVAL fillColor):_isFilled(FALSE),_fillColor(fillColor)
{
    
}

Box::Box(RGBVAL fillColor,AEESize& Size):_isFilled(FALSE),_fillColor(fillColor)
{
    MEMCPY(&_Size,&Size,sizeof(Size));
}


void Box::SetSize(AEESize& Size)
{
    MEMCPY(&_Size,&Size,sizeof(AEESize));
}

void Box::Draw(AEEPoint& Point,IGraphics* pIGraphics) const
{
    if( NULL == pIGraphics)    
    {        
        return;
    }
    
    AEERect rect;
    rect.x = Point.x + 1;
    rect.y = Point.y + 1;
    rect.dx = static_cast<int16>(_Size.cx) - 1;
    rect.dy = static_cast<int16>(_Size.cy) - 1;

    unsigned char R = ColorMgr::Get_R(_fillColor);
    unsigned char G = ColorMgr::Get_G(_fillColor);
    unsigned char B = ColorMgr::Get_B(_fillColor);

    IGRAPHICS_SetFillColor (pIGraphics, R, G, B, 0);  
    IGRAPHICS_SetColor (pIGraphics, R, G, B, 0); 
    IGRAPHICS_SetFillMode (pIGraphics, TRUE);

    //int oldSize = IGRAPHICS_GetPointSize(pIGraphics);
    //IGRAPHICS_SetPointSize(pIGraphics,10);
    IGRAPHICS_DrawRect(pIGraphics,&rect);
    //IGRAPHICS_SetPointSize(pIGraphics,oldSize);
}

void Box::Set_Filled(boolean isFilled)
{
    _isFilled = isFilled;
}
