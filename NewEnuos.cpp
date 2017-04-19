/***************************************************************************/
/*                                                                         */
/*  NewEnuos.cpp                                                           */
/*                                                                         */
/*    The entry of the application                                         */
/*                                       .                                 */
/*                                                                         */
/*  Copyright 2007 by                                                      */
/*                  Kan(EMail: k32459871@126.com.)                         */
/*  Data: 2007-5-1                                                         */
/*                                                                         */
/***************************************************************************/

#include "Enuos.h"

extern "C"
int AEEClsCreateInstance(AEECLSID ClsId, IShell *pIShell, IModule *po, void **ppObj)
{
	*ppObj = NULL;

	if( ClsId == AEECLSID_NEWENUOS )
	{		
		if( AEEApplet_New(sizeof(NewEnuos),
                          ClsId,
                          pIShell,
                          po,
                          (IApplet**)ppObj,
                          (AEEHANDLER)NewEnuos::NewEnuos_HandleEvent,
                          (PFNFREEAPPDATA)NewEnuos::NewEnuos_FreeAppData) ) 
                          
		{	         
            if(NewEnuos::NewEnuos_InitAppData((NewEnuos*)*ppObj))
			{			
				return(AEE_SUCCESS);
			}
			else
			{			
				IAPPLET_Release((IApplet*)*ppObj);
				return EFAILED;
			}

        } 

    }

	return(EFAILED);
}


boolean NewEnuos::NewEnuos_HandleEvent(NewEnuos* pMe, AEEEvent eCode, uint16 wParam, uint32 dwParam)
{  

    switch (eCode) 
	{
        // App is told it is starting up
        case EVT_APP_START:    
            DBGPRINTF("Written by kan. Copyright 2007 ");
            IDISPLAY_Update(pMe->m_pIDisplay);
            {
                pMe->canvas->Init();
                pMe->shape->Start();
            }
            
            return(TRUE);


        // App is told it is exiting
        case EVT_APP_STOP:            

      		return(TRUE);

        
        case EVT_APP_SUSPEND:		    

      		return(TRUE);


        // App is being resumed
        case EVT_APP_RESUME:		    

      		return(TRUE);

        case EVT_APP_MESSAGE:
		    // Add your code here...

      		return(TRUE);

        case EVT_KEY:

            if(wParam == AVK_SOFT2)
            {
                ISHELL_CloseApplet(pMe->m_pIShell,FALSE);
            }
            
            switch(wParam)
            {
            case AVK_SELECT:
                if(pMe->shape->GetAppState() == Shape::RUNNING)
                {
                    pMe->shape->Suspend();
                }
                else
                    pMe->shape->Resume();

                break;
            case AVK_CLR:
                
                pMe->shape->Stop();

                break;
            case AVK_UP:
                pMe->shape->TurnNextStyle();
            	break;
            case AVK_DOWN:
                pMe->shape->MoveDown();
            	break;
            case AVK_LEFT:
                pMe->shape->MoveLeft();
                break;
            case AVK_RIGHT:
                pMe->shape->MoveRight();
                break;
            default:
                break;
            }
            
      		return(TRUE);


        // If nothing fits up to this point then we'll just break out
        default:
            dwParam += 1;
            break;
   }

   return FALSE;
}


// this function is called when your application is starting up
boolean NewEnuos::NewEnuos_InitAppData(NewEnuos* pMe)
{   
    pMe->DeviceInfo.wStructSize = sizeof(pMe->GetDevice());
    ISHELL_GetDeviceInfo(pMe->m_pIShell,&(pMe->GetDevice())); 
    
    pMe->canvas = new Canvas;    
    pMe->shape = new Shape(pMe->canvas);

    return TRUE;
}

void NewEnuos::NewEnuos_FreeAppData(NewEnuos* pMe)
{ 
    delete pMe->canvas;
    delete pMe->shape;
}

AEEDeviceInfo& NewEnuos::GetDevice()
{
    return DeviceInfo;
}

NewEnuos::NewEnuos()
{
    //uint32 i = ColorMgr::Black;
}


void* operator new(size_t size)
{
    return MALLOC(size);
}

void operator delete(void* p)
{
    FREE(p);
}