#include <string>
#include <windows.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";

HWND BatteryLabel, hwnd;               /* This is the handle for our window */

SYSTEM_POWER_STATUS* status;

void updateLabel(){
	GetSystemPowerStatus(status);
	if(status->BatteryFlag==128){
		SendMessage(BatteryLabel,WM_SETTEXT,0,(LPARAM)"AC");	
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)"Plugged in");
	}else{
		if(!status->ACLineStatus)
			SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)"Not Charging");
		else
			SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)"Charging!");
		SendMessage(BatteryLabel,WM_SETTEXT,0,(LPARAM)(std::to_string(status->BatteryLifePercent)+'%').c_str());
	}
	
	//SetTextColor(GetDC(BatteryLabel),(COLORREF)((!status->ACLineStatus)?RGB(0xFF,0,0):RGB(0xFF,0,0)));
	//SendMessage(hwnd,WM_CTLCOLORSTATIC,(WPARAM)GetDC(hwnd),(LPARAM)BatteryLabel);
}

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           WS_EX_TOOLWINDOW|WS_EX_TOPMOST,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "xxx",      /* Title Text */
           WS_DLGFRAME, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           100,                 /* The programs width */
           65,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
           
		HFONT font=CreateFont(
			32,0,0,0,700,
			0,0,0,ANSI_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY,FF_DONTCARE,
			"Consolas"
		);
		
    	BatteryLabel = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           "Static",         /* Classname */
           NULL,
           WS_CHILD|WS_VISIBLE, /* default window */
           0,       /* Windows decides the position */
           0,       /* where the window ends up on the screen */
           100,                 /* The programs width */
           65,                 /* and height in pixels */
           hwnd,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
        );
        
  	ShowWindow (hwnd, nFunsterStil);
	     
    SendMessage(BatteryLabel,WM_SETFONT,(WPARAM)font,true);
    
    SetTimer(hwnd,0,30000,(TIMERPROC)&updateLabel);
	status=new SYSTEM_POWER_STATUS();

	updateLabel();

    /* Make the window visible on the screen */
  

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_DISPLAYCHANGE:
        	SetWindowPos(hwnd,HWND_TOP,(lParam & 0xFFFF)-180,(lParam >> 16)-80,100,65,SWP_SHOWWINDOW);
        	break;
        case WM_POWERBROADCAST:
        	updateLabel();
			return true; 
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
