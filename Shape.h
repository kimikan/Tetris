/***************************************************************************/
/*                                                                         */
/*  Shape.h                                                                */
/*                                                                         */
/*    The main shape definition                                            */
/*    It was designed as a active object .                                 */
/*                                                                         */
/*  Copyright 2007 by                                                      */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "def.h"

#include "Canvas.h"


const int STATES[7][4]  = {
    {0x0f00, 0x4444, 0x0f00, 0x4444}, 
    {0x04e0, 0x0464, 0x00e4, 0x04c4}, 
    {0x4620, 0x6c00, 0x4620, 0x6c00}, 
    {0x2640, 0xc600, 0x2640, 0xc600}, 
    {0x6220, 0x1700, 0x2230, 0x0740}, 
    {0x6440, 0x0e20, 0x44c0, 0x8e00}, 
    {0x0660, 0x0660, 0x0660, 0x0660} };

const int Default_Intervals = 600;//1000;
const int Add_Intervals = 200;
class Shape
{
public:
    enum APPState
    {
        RUNNING = 0,
        SUSPENDING,
        STOPING
    };

public:
    /*Constructor*/
    Shape(Canvas* pCanvas);

    /*Desconstructor*/
    ~Shape();
    
    /*Getter & Setter*/
    Canvas* GetCanvas() const;

    int GetCurrentStateX() const;
    void SetCurrentStateX(const int state);

    int GetCurrentStateY() const;
    void SetCurrentStateY(const int state);

    int GetIntervals() const;
    void SetIntervals(const int intervals);
    
    /*Get Current App State*/
    const APPState GetAppState() const;
    
    void Start();
    
    void Suspend();
    
    void Resume();
    
    void Stop();
    
    boolean MoveLeft();
    
    boolean MoveRight();
    
    boolean MoveDown();
    
    boolean MoveStep();
    
    boolean TurnNextStyle();

    void Reset();
    
protected:
    static void Run(void* pUser);
private:
    void DrawStr(AECHAR* pA,int len);
private:
    int CurrentStateX;
    int CurrentStateY;

    int StartPosX;
    int StartPosY;
    Canvas* _pCanvas;
    
    int Intervals;
    
    APPState _State;

private:
    IStatic* pLbl;
};

#endif
