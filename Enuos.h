/***************************************************************************/
/*                                                                         */
/*  NewEnuos.h                                                             */
/*                                                                         */
/*    The entry of the application                                         */
/*                                       .                                 */
/*                                                                         */
/*  Copyright 2007 by                                                      */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/
#ifndef _ENUOS_H_
#define _ENUOS_H_

#include "def.h"
#include "Color.h"
#include "Canvas.h"
#include "Shape.h"

class NewEnuos : public AEEApplet
{    
private:
    AEEDeviceInfo  DeviceInfo;
       
public:
    /*App Handle Event Function*/
    static  boolean NewEnuos_HandleEvent(NewEnuos* pMe, AEEEvent eCode, 
                                            uint16 wParam, uint32 dwParam);
    /*App Init Data Function*/
    static boolean NewEnuos_InitAppData(NewEnuos* pMe);
    
    /*App Free Data Function*/
    static void    NewEnuos_FreeAppData(NewEnuos* pMe);

    /*Getter function for DeviceInfo*/
    AEEDeviceInfo& GetDevice();

    /*Construct function*/
    NewEnuos();
protected:

public:
    Canvas* canvas;
    Shape * shape;
};

#endif
