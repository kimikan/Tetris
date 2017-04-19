/***************************************************************************/
/*                                                                         */
/*  Canvas.h                                                               */
/*                                                                         */
/*    The main shape definition                                            */
/*    It was designed as a Canvas object .                                 */
/*                                                                         */
/*  Copyright 2007 by                                                      */
/*                  Kan(EMail: k32459871@126.com.)                         */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/

#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "def.h"
#include "Color.h"
#include "Box.h"

//--------------------------------------------------
const int rows = 25;

const int cols = 18;

const int RowHeight = 12;

const int ColWidth = 12;

const RGBVAL FRONT_COLOR = ColorMgr::Cyan;
//const RGBVAL FRONT_COLOR = ColorMgr::Magenta;

const RGBVAL BACK_COLOR = ColorMgr::DarkGray;
//--------------------------------------------------


class NextStyleArea
{
public:

private:

};

class ResultInfoArea
{
public:
    void DrawScore(int score);
private:
    AEERect rect;
};

class ClientArea
{
public:
    /*Constructor function*/
    ClientArea(IGraphics* pIGraphics);
    
    /*Getter & Setter*/
    const AEEPoint& GetPoint() const;
    void SetPoint(AEEPoint& _point);

    void Init();
    
    /*Paint self on the Graphics*/
    void Draw();

    //set
    void SetFilled(int i, int j, boolean isFilled);

    boolean Accept(int x,int y,int Style);

    boolean DrawStyle(boolean isForeColor,int x,int y,int Style);
    
    boolean FillStyle(boolean isFilled,int x,int y,int Style);

    int RemoveLine();

    int GetScore()const;
private:
    void MoveLine(int src, int des);
private:
    IGraphics* pIGraphics;

    AEEPoint point;
    
    boolean datas[rows][cols];

    int Score;
};


class Canvas
{
public:
    /*Constructor*/
    Canvas();
    
    /*Desconstructor*/
    ~Canvas();

    /*Getter & Setter*/
    void SetClient(ClientArea* pValue);
    ClientArea* GetClient() const;

    void SetResultInfo(ResultInfoArea* pValue);
    ResultInfoArea* GetResultInfo() const;

    void SetNextStyle(NextStyleArea* pValue);
    NextStyleArea* GetNextStyle() const;

    /*Get IGraphics Instance*/
    IGraphics* GetGraphics() const;

    void Init();
    /*Draw self*/
    void Draw();

protected:

private:
    ClientArea      *pIClientArea;
    ResultInfoArea  *pIResultInfoArea;
    NextStyleArea   *pINextStyleArea;

    IGraphics       *pIGraphics;
};

#endif