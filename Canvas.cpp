/***************************************************************************/
/*                                                                         */
/*  Canvas.cpp                                                             */
/*                                                                         */
/*    The main shape definition                                            */
/*    It was designed as a Canvas object .                                 */
/*                                                                         */
/*  Copyright 2007                       */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/

#include "Canvas.h"
#include "Enuos.h"

/*Constructor function*/
ClientArea::ClientArea(IGraphics* pIGraphics)
{
    this->pIGraphics = pIGraphics;

    Init();
}

/*Getter & Setter*/
const AEEPoint& ClientArea::GetPoint() const
{
    return this->point;
}


void ClientArea::SetPoint(AEEPoint& _point)
{
    MEMCPY(&this->point,&_point,sizeof(AEEPoint));
}

void ClientArea::SetFilled(int i, int j,boolean isFilled)
{
    this->datas[i][j] = isFilled;
}

int ClientArea::GetScore()const
{
    return Score;
}

void ClientArea::Init()
{
    Score = 0;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            AEESize size;
            AEEPoint point;
            
            point.x = j * ColWidth + this->point.x;
            point.y = i * RowHeight + this->point.y;
            
            size.cx = ColWidth;
            size.cy = RowHeight;
            datas[i][j] = FALSE;   
        }
    }
    
    Draw();
}
/*Paint self on the Graphics*/
void ClientArea::Draw()
{
    AEERect rect;
    rect.x = point.x + 1;
    rect.y = point.y + 1;
    rect.dx = static_cast<int16>(cols * ColWidth) - 1;
    rect.dy = static_cast<int16>(rows * RowHeight) - 1;
    
    unsigned char R = ColorMgr::Get_R(BACK_COLOR);
    unsigned char G = ColorMgr::Get_G(BACK_COLOR);
    unsigned char B = ColorMgr::Get_B(BACK_COLOR);
    
    IGRAPHICS_SetFillColor (pIGraphics, R, G, B, 0);  
    IGRAPHICS_SetColor (pIGraphics, 0, 0, 0, 0); 
    IGRAPHICS_SetFillMode (pIGraphics, TRUE);
    IGRAPHICS_SetStrokeStyle(pIGraphics,STROKE_SOLID);
    IGRAPHICS_DrawRect(pIGraphics,&rect);

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            AEESize size;
            AEEPoint point;
            
            point.x = j * ColWidth + this->point.x;
            point.y = i * RowHeight + this->point.y;
            
            size.cx = ColWidth;
            size.cy = RowHeight;
            if(this->datas[i][j] == TRUE)
            {                
                Box b(FRONT_COLOR,size);
                b.Draw(point,pIGraphics);
            }
            else
            {                
                Box b(BACK_COLOR,size);
                b.Draw(point,pIGraphics);
            }
        }
    }
}
boolean ClientArea::Accept(int x,int y,int Style)
{
    int key = 0X8000;
    
    for(int i= 0; i < 4; i++)
    {
        for(int j = 0; j< 4; j++)
        {
            if((Style & key) != 0)            
            {
                if((x+j) >= cols 
                    || (x+j) < 0
                    || (y + i) < 0
                    || (y + i) >= rows 
                    || datas[y + i][x + j] == TRUE)
                {
                    return FALSE;
                }
            }

            key >>= 1;
        }
    }

    return TRUE;
}


boolean ClientArea::DrawStyle(boolean isForeColor,int x,int y,int Style)
{
    int key = 0X8000;
    AEESize size;
    AEEPoint point;    
    
    size.cx = ColWidth;
    size.cy = RowHeight;
    
    for(int i= 0; i < 4; i++)
    {
        for(int j = 0; j< 4; j++)
        {
            point.x = (x+j)*ColWidth + this->point.x;
            point.y = (y+i)*RowHeight + this->point.y;
            
            if((x+j) >= cols && (y + i) >= rows) 
                continue;

            if((Style & key) != 0)            
            {    
                if(isForeColor == TRUE)
                {
                    Box b(FRONT_COLOR,size);
                    b.Draw(point,pIGraphics);
                   
                    //datas[x+j][y+i] = TRUE;
                }
                else
                {
                    Box b(BACK_COLOR,size);
                    b.Draw(point,pIGraphics);
                    //datas[x+j][y+i] = FALSE;
                }
                
            }
            
            key >>= 1;
        }
    }
    
    {
        NewEnuos* pMe = (NewEnuos*)GETAPPINSTANCE();
        IDISPLAY_Update(pMe->m_pIDisplay);
    }
    
    return TRUE;
}
boolean ClientArea::FillStyle(boolean isFilled,int x,int y,int Style)
{
    int key = 0X8000;
    
    for(int i= 0; i < 4; i++)
    {
        for(int j = 0; j< 4; j++)
        {
            if((Style & key) != 0)            
            {
                datas[y+i][x+j] = isFilled;
            }
            
            key >>= 1;
        }
    }

    return TRUE;
}

void ClientArea::MoveLine(int src, int des)
{
    for(int i= 0; i < cols; i++)
    {
        datas[des][i] = datas[src][i];
    }
}

int ClientArea::RemoveLine()
{
    /*
    boolean bR[rows];

    for(int i = 0; i < rows; i ++)
    {
        boolean isAll = TRUE;
        for(int j = 0; j< cols ;j++)
        {
            if(datas[i][j] == FALSE)
            {
                isAll = FALSE;
                break;
            }
        }
        
        bR[i] = isAll;
    }

    for( int v1 = rows - 1 ; v1 > 0; v1--)
    {
        if(bR[v1] == FALSE)
        {
            continue;
        }

        for(int line = v1; line > 0; line -- )
        {
            MoveLine(line - 1,line);
        }

        for(int j = 0; j< cols; j++)
        {
            datas[0][j] = FALSE;
        }
    }
    for(int j = 0; j< cols; j++)
    {
        datas[0][j] = FALSE;
    }
    */
    int sum = 0;
    for(int i = 0; i < rows; i ++)
    {
        boolean isAll = TRUE;
        for(int j = 0; j< cols ;j++)
        {
            if(datas[i][j] == FALSE)
            {
                isAll = FALSE;
                break;
            }
        }
        
        if(isAll == TRUE)
        {
            sum ++;
            DBGPRINTF(" ----------- Now Score is: %d",Score);
            for (int k = i;k > 0;k --)
            {
                MoveLine(k - 1,k);
            }
             
            for (int j = 0;j < cols;j ++)
            {
			    datas[0][j] = FALSE;
            }
        }
    }

    switch(sum)
    {
    case 1:
        Score++;
        break;
    case 2:
        Score += 2;
        break;
    case 3:
        Score += 4;
        break;
    case 4:
        Score += 7;
        break;
    default:
        Score += sum;
    }
    //(Score /10)
    Draw();

    return Score;
}
//---------------------For Canvas---------------------------
/*Constructor*/
Canvas::Canvas()
{
    AEEPoint point;
    point.x = 10;
    point.y = 10;

    NewEnuos* pMe = (NewEnuos*)(GETAPPINSTANCE());
    ISHELL_CreateInstance(pMe->m_pIShell,AEECLSID_GRAPHICS,(void**)&this->pIGraphics);

    this->pIClientArea = new ClientArea(pIGraphics);
    pIClientArea->SetPoint(point);
    
    this->pINextStyleArea = new NextStyleArea;
    this->pIResultInfoArea = new ResultInfoArea;
}

/*Desconstructor*/
Canvas::~Canvas()
{
    IGRAPHICS_Release(this->pIGraphics);

    delete this->pIClientArea;
    delete this->pINextStyleArea;
    delete this->pIResultInfoArea;
}

/*Getter & Setter*/
void Canvas::SetClient(ClientArea* pValue)
{
    this->pIClientArea = pValue;
}
ClientArea* Canvas::GetClient() const
{
    return this->pIClientArea;
}

void Canvas::SetResultInfo(ResultInfoArea* pValue)
{
    this->pIResultInfoArea = pValue;
}

ResultInfoArea* Canvas::GetResultInfo() const
{
    return this->pIResultInfoArea;
}

void Canvas::SetNextStyle(NextStyleArea* pValue)
{
    this->pINextStyleArea = pValue;
}

NextStyleArea* Canvas::GetNextStyle() const
{
    return this->pINextStyleArea;
}

/*Get IGraphics Instance*/
IGraphics* Canvas::GetGraphics() const
{
    return this->pIGraphics;
}

void Canvas::Init()
{
    this->pIClientArea->Init();
}

void Canvas::Draw()
{
    this->pIClientArea->Draw();
}
