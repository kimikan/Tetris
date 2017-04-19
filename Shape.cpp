/***************************************************************************/
/*                                                                         */
/*  Shape.cpp                                                              */
/*                                                                         */
/*    The main shape definition                                            */
/*    It was designed as a active object .                                 */
/*                                                                         */
/*  Copyright 2007 by                                                      */
/*                  Kan(EMail: k32459871@126.com.)                         */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/

#include "Shape.h"

#include "Enuos.h"
/*Constructor*/
Shape::Shape(Canvas* pCanvas):_pCanvas(pCanvas)
                             ,Intervals(Default_Intervals),_State(STOPING)
{
    NewEnuos* pMe = (NewEnuos*)GETAPPINSTANCE();
    ISHELL_CreateInstance(pMe->m_pIShell,AEECLSID_STATIC,(void**)&pLbl);

    Reset();
}
void Shape::DrawStr(AECHAR* pA,int len)
{    
    NewEnuos* pMe = (NewEnuos*)GETAPPINSTANCE();
    
    AEERect rc;
    rc.dx = 120;
    rc.dy = 40;
    rc.x = 50;
    rc.y = 130;

    ISTATIC_SetRect(pLbl,&rc);
    
    ISTATIC_SetText(pLbl, NULL, pA, AEE_FONT_BOLD, AEE_FONT_BOLD);
    
    ISTATIC_Redraw(pLbl);   
    rc.dx = 0;
    rc.dy = 0;
    rc.x = -1;
}

void Shape::Reset()
{
   
    uint32 randNo = 0;
    GETRAND((byte*)&randNo,sizeof(uint32));
    this->CurrentStateX = randNo%7;
    
    GETRAND((byte*)&randNo,sizeof(uint32));
    this->CurrentStateY = randNo%4;   
    /* 
    this->CurrentStateX = 0;
    this->CurrentStateY = 0;
    */
    StartPosY = 0;
    StartPosX = 3;
    
    if(FALSE == _pCanvas->GetClient()->Accept(StartPosX,StartPosY
        ,STATES[CurrentStateX][CurrentStateY]))   
    {
        _State = STOPING;
        
        DrawStr((unsigned short*)L"Game Over",10);
        DBGPRINTF("Game Over....");
    }
}

/*Desconstructor*/
Shape::~Shape()
{
    ISTATIC_Release(pLbl);
}

/*Getter & Setter*/
Canvas* Shape::GetCanvas() const
{
    return _pCanvas;
}

int Shape::GetCurrentStateX() const
{
    return this->CurrentStateX;
}

void Shape::SetCurrentStateX(const int state)
{
    this->CurrentStateX = state;
}

int Shape::GetCurrentStateY() const
{
    return this->CurrentStateY;
}

void Shape::SetCurrentStateY(const int state)
{
    this->CurrentStateY = state;
}


int Shape::GetIntervals() const
{
    return this->Intervals;
}

void Shape::SetIntervals(const int intervals)
{
    this->Intervals = intervals;
}

const Shape::APPState Shape::GetAppState() const
{
    return _State;
}

void Shape::Start()
{
    if(_State != RUNNING)
    {
        _State = RUNNING;
        _pCanvas->Draw();
    }
    Intervals = Default_Intervals;
    Run(this);
}

void Shape::Suspend()
{
    if(_State == RUNNING)
    {
        _State = SUSPENDING;
    }
    DrawStr((unsigned short*)L"Suspend",8);
    DBGPRINTF("++++++++++++++Suspend %d",Intervals);
}

void Shape::Resume()
{
    ISTATIC_Reset(pLbl);
    if(_State != RUNNING)
    {
        _State = RUNNING;
        _pCanvas->Draw();
    }
    DBGPRINTF("++++++++++++++Resume %d",Intervals);
    Run(this);
}

void Shape::Stop()
{
    DrawStr((unsigned short*)L"Stop",5);
    Intervals = Default_Intervals;
    _State = STOPING;
}

boolean Shape::MoveLeft()
{    
    if(_State != RUNNING)
        return FALSE;

    if(FALSE == _pCanvas->GetClient()->Accept(StartPosX - 1,StartPosY
        ,STATES[CurrentStateX][CurrentStateY]))   
    {
        return FALSE;
    }
    else
    {
        _pCanvas->GetClient()->DrawStyle(FALSE,StartPosX,StartPosY
            ,STATES[CurrentStateX][CurrentStateY]);
        _pCanvas->GetClient()->DrawStyle(TRUE ,--StartPosX,StartPosY
                                               ,STATES[CurrentStateX][CurrentStateY]);
    }

    return TRUE;
}

boolean Shape::MoveRight()
{    
    if(_State != RUNNING)
        return FALSE;

    if(FALSE == _pCanvas->GetClient()->Accept(StartPosX + 1,StartPosY
        ,STATES[CurrentStateX][CurrentStateY]))   
    {
        return FALSE;
    }
    else
    {
        _pCanvas->GetClient()->DrawStyle(FALSE,StartPosX,StartPosY
            ,STATES[CurrentStateX][CurrentStateY]);
        _pCanvas->GetClient()->DrawStyle(TRUE ,++StartPosX,StartPosY
            ,STATES[CurrentStateX][CurrentStateY]);
    }

    return TRUE;
}

boolean Shape::MoveDown()
{
    if(_State != RUNNING)
        return FALSE;

    while(MoveStep() == TRUE)
    {

    }
    _pCanvas->GetClient()->FillStyle(TRUE ,StartPosX,StartPosY
            ,STATES[CurrentStateX][CurrentStateY]);
    
    int Score = _pCanvas->GetClient()->RemoveLine();
    Reset();
    SetIntervals(Default_Intervals - Score/10 * Add_Intervals);
    return TRUE;
}

boolean Shape::MoveStep()
{    
    if(StartPosY >= 0)
    {
         if(FALSE == this->_pCanvas->GetClient()->Accept(StartPosX,StartPosY+1
                                               ,STATES[CurrentStateX][CurrentStateY]))   
         {
             return FALSE;
         }
         _pCanvas->GetClient()->DrawStyle(FALSE,StartPosX,StartPosY
                                               ,STATES[CurrentStateX][CurrentStateY]);
         _pCanvas->GetClient()->DrawStyle(TRUE ,StartPosX,++StartPosY
                                               ,STATES[CurrentStateX][CurrentStateY]);
    }

    return TRUE;
}

boolean Shape::TurnNextStyle()
{
    int next = CurrentStateY == 3 ? 0 : CurrentStateY + 1;
    
    if(FALSE == this->_pCanvas->GetClient()->Accept(StartPosX,StartPosY
        ,STATES[CurrentStateX][next]))   
    {
        return FALSE;
    }

    _pCanvas->GetClient()->DrawStyle(FALSE,StartPosX,StartPosY
        ,STATES[CurrentStateX][CurrentStateY]);
    
    CurrentStateY = next;
    _pCanvas->GetClient()->DrawStyle(TRUE ,StartPosX,StartPosY
                                               ,STATES[CurrentStateX][CurrentStateY]);
    return TRUE;
}


void Shape::Run(void *pUser)
{
    Shape* pShape = (Shape*)pUser;

    if(pShape->GetAppState() == SUSPENDING)
    {
        return;
    }
    else if(pShape->GetAppState() == STOPING)
    {
        pShape->_pCanvas->GetClient()->Init();
        return;
    }
    else if(pShape->GetAppState() == RUNNING)
    {       
        if(FALSE == pShape->MoveStep())
        {
            pShape->_pCanvas->GetClient()->FillStyle(TRUE ,pShape->StartPosX,pShape->StartPosY
                                               ,STATES[pShape->CurrentStateX][pShape->CurrentStateY]);
            int Score = pShape->_pCanvas->GetClient()->RemoveLine();
            pShape->SetIntervals(Default_Intervals - Score/10 * Add_Intervals);
            pShape->Reset();
        }
       
        NewEnuos* pMe = (NewEnuos*)GETAPPINSTANCE();
        ISHELL_SetTimer(pMe->m_pIShell,pShape->Intervals,(PFNNOTIFY)Shape::Run,pUser);
    }
}