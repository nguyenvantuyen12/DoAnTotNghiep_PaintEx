// PaintEX.cpp : Defines the entry point for the application. 
//2362,2380, 2034, 1796, 1789, 2331,1429, 1467, 655, 2216
#include "stdafx.h"
#include "CSelectEx.h"
#include "..\\source\\resource.h"
#include "PaintEX.h"
#include "CRulerEX.h"
#include "CGridEX.h"
#include "CShapeListEX.h"
#include "CTextEx.h"
#include <CommDlg.h>
#include <commctrl.h>
#include <vector> 
#define MAX_LOADSTRING 100
CSelectEx g_MultiSelect; //Pointer of base class
// Global Variables:
HINSTANCE hInst;							// current instance 
TCHAR szTitle[MAX_LOADSTRING];				// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];
int nObjectSelect;
int nCurrentShape;
TCHAR str[255];
CRulerEX ruler;
//thuc hien viec thao tac voi text
bool g_bFlagText = false;	//	Co bao hieu khi doi tuong Text duoc move, resize hoac rotate
//	Move 2 diem begin, end len de su dung ca trong ham CmdProc()
POINTS g_ptBegin;					// x and y coordinates of cursor when left mouse is entered
POINTS g_ptEnd;						// x and y coordinates of cursor
POINTS g_ptDes;						// x and y coordinates of cursor, thuan them vao: bat tao do khi chuot phai click xuong
int  g_nPosCusor = 1;
int g_nCountPasteTime = 0;	//	khi nhan Ctr+V thi bien nay = 1 (danh dau rang Ctr+V duoc nhan dong thoi)
POINTS g_ptPaste;	//	dung diem nay de thay the cho g_ptDes khi nhan Ctr+V
int g_nCountShiftLeft = 0;	//	bien dem so lan nhan phim dich trai
int g_nCountShiftRight = 0;	//	bien dem so lan nhan phim dich phai
int g_nCountShiftUp = 0;	//	bien dem so lan nhan phim dich len
int g_nCountShiftDown = 0;	//	bien dem so lan nhan phim dich xuong
//	bien nho toa do khi chuot trai duoc bat len va doi tuong duoc chon
POINTS g_ptPrev;						// toa do cua chuot khi chuot trai up va doi tuong dang duoc chon
int g_nIndexObjSelect = -1;				// bien luu lai gia tri doi tuong duoc lua chon truoc do
bool g_bFillClick = false;				//	Co bao hieu viec nguoi dung co bam vao nut draw fill tren toolbar hay ko

vector<int*> MarkSelect;
int *temp;
int nIndexObjSelect = -1;
int nTry = 0;
//int i; //phuc vu
size_t nControl;
void MultiSelect(HDC hdc,POINTS ptBegin,POINTS ptEnd);
void ChangePropertyObj(HDC hdc);
//----------------
HMENU g_hOptionsMenu ;
HWND g_hWndToolbar; //	display Toolbar
int g_nIdToolbarButton = ID_DRAW_SELECTOBJECTS;	//	index of tbbutton is executed
int g_nIdToolbarText = ID_TEXT_LEFT;		//	index of tbbutton is executed
HWND g_hWndStatus;							//display Status bar
COLORREF g_crColor = RGB(0, 0, 0);			//color is selected
HPEN g_hPen;
//----------------------------
HFONT hfont;
CHOOSEFONT cf;								//khai bao bien cho menu FOnts
LOGFONT logfont;
HWND hEdit;
//---------------------------------
// Dat trang thai cho Ruler Grid
//----------------------------------
bool g_bFilled = false;
bool g_bEnableRuler = true;	
bool g_bEnableGrid = true;
int g_nPenWidth = PW_ONE;
int g_nPenStyle = PS_SOLID;
int g_nModeShape = MS_SELECTED;		//If MS_LINE:	Draw Line
								 //If MS_SELECTED: Select object to edit...

CShapeEX *g_pObject;				//Pointer of base class

CTextEx g_ctText;	//	Thao tac voi Text

CShapeEX *g_pObjectPrev;					//	bien nho luu lai doi tuong truoc
bool g_bEditPenFlag = false, g_bFillFlag = false, g_bColorFlag = false; // bien dung de lam co bao khi co thay doi chinh sua mau sac, net but
LRESULT CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 

/*   
Declare function and global variable
Global function ClearDC, ZoomDialog
/************************************************************************/

CShapeListEX paintListShape;		//List Object 
int nModeDraw = MS_LINE;	//Set default mode draw is MS_LINE
int nObjectIndex;			//Index of Object in List Object
POINTS pMouseClick;		//Store position of Mouse when mouse left click
int g_nZoomRate	= 1;			//ty le Zoom
BOOL LoadFileToList(HWND);	//Load properties in file to List Object
BOOL SaveFileToList(HWND);	//Save properties of List Object to file
bool ClearDC(HWND);											//Xu ly viec clear man hinh
INT_PTR CALLBACK NewDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK EditPenDialog(HWND, UINT, WPARAM, LPARAM); 
void CheckAndUncheck(int);
//-------------------------------------------------------------------------

COLORREF ShowColorDialog(HWND);					// Display color panel 

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Print(HWND, UINT, WPARAM, LPARAM);	//	Thu tuc thuc hien khi chon Print.		
int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PAINTEX, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINTEX));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_F5));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PAINTEX);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_F5));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable
//szTitle
	hWnd = CreateWindow(szWindowClass, "PaintEX Nguyen Van Tuyen", WS_OVERLAPPEDWINDOW| WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, /*nCmdShow*/SW_MAXIMIZE);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
void MultiSelect(HDC hdc,POINTS ptBegin,POINTS ptEnd);
bool UpdateCover();
bool bSelect = false;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps; //paint data for BeginPaint and EndPaint
	HDC hdc; //device context for window
	static POINT  s_ptRightButton;
	static HMENU s_hMenu;

	POINT ptClientUL;        // client area upper left corner  
	POINT ptClientLR;        // client area lower right corner  
	static HDC hdcCompat;    // DC for copying bitmap 
	static RECT rcClient;    // client-area rectangle
	
	static CGridEX grid;
	static int g_nIdToolbarButton = -1;
	static int m_xCaret,m_yCaret;
	static int s_nMode = MR_NONE;
	// Scrollbar variable
	static int s_iVscrollPos = 0 ; //   Vi tri thumb tren scrollbar thang dung
	static int s_iHscrollPos = 0 ; //   Vi tri thumb tren scrollbar nam ngang 
	static bool s_fFlagMove = true;//   false thi dung scrollbar
	int iTempScrollPos;            //   Vi tri tam thoi cua thumb
	static bool s_bFlagInitial = false;
	switch (message)
	{

	case WM_COMMAND:
		return CmdProc(hWnd, message, wParam, lParam);
		break;
	//--Xu ly cac phim dac biet tren ban phim *****************
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_END:
			g_nPosCusor=0;
			break ;

		case VK_LEFT:	
			hdc = GetDC(hWnd);
			g_nPosCusor++;	
			g_nCountShiftDown = 0;
			g_nCountShiftUp = 0;
			g_nCountShiftRight = 0;
			SetROP2(hdc, R2_NOTXORPEN);
			g_nCountShiftLeft ++;
			if (g_nCountShiftLeft == 1)
			{
				paintListShape.SaveSelectObjectPos();
			}
			paintListShape.Draw(hdc); 
			paintListShape.DrawTracker(hdc);
			paintListShape.DeleteText(hdc);
			paintListShape.MoveSomeObject(-5, 0);
			paintListShape.SavePoint();
			paintListShape.Draw(hdc);
			paintListShape.DrawTracker(hdc);
			ReleaseDC(hWnd, hdc);
			break ;

		case VK_RIGHT:
			hdc = GetDC(hWnd);
			g_nPosCusor--;	

			SetROP2(hdc, R2_NOTXORPEN);
			g_nCountShiftRight ++;	
			g_nCountShiftDown = 0;
			g_nCountShiftUp = 0;
			g_nCountShiftLeft = 0;
			if (g_nCountShiftRight == 1)
			{
				paintListShape.SaveSelectObjectPos();
			}
			paintListShape.Draw(hdc); 
			paintListShape.DrawTracker(hdc);
			paintListShape.DeleteText(hdc);
			paintListShape.MoveSomeObject(+5, 0);
			paintListShape.SavePoint();
			paintListShape.Draw(hdc);
			paintListShape.DrawTracker(hdc);
			ReleaseDC(hWnd, hdc);
			break ;
		case VK_UP:
			hdc = GetDC(hWnd);
			SetROP2(hdc, R2_NOTXORPEN);
			g_nCountShiftUp ++;
			g_nCountShiftDown = 0;
			g_nCountShiftLeft = 0;
			g_nCountShiftRight = 0;
			if (g_nCountShiftUp == 1)
			{
				paintListShape.SaveSelectObjectPos();
			}
			paintListShape.Draw(hdc); 
			paintListShape.DrawTracker(hdc);
			paintListShape.DeleteText(hdc);
			paintListShape.MoveSomeObject(0, -5);
			paintListShape.SavePoint();
			paintListShape.Draw(hdc);
			paintListShape.DrawTracker(hdc);
			ReleaseDC(hWnd, hdc);
			break;
		case VK_DOWN:
			hdc = GetDC(hWnd);
			SetROP2(hdc, R2_NOTXORPEN);
			g_nCountShiftDown ++;
			g_nCountShiftLeft = 0;
			g_nCountShiftUp = 0;
			g_nCountShiftRight = 0;
			if (g_nCountShiftDown == 1)
			{
				paintListShape.SaveSelectObjectPos();
			}
			paintListShape.Draw(hdc); 
			paintListShape.DrawTracker(hdc);
			paintListShape.DeleteText(hdc);
			paintListShape.MoveSomeObject(0, +5);
			paintListShape.SavePoint();
			paintListShape.Draw(hdc);
			paintListShape.DrawTracker(hdc);
			ReleaseDC(hWnd, hdc);
			break;

		case VK_CONTROL:
			if (wParam&&'v')
			{
				g_nCountPasteTime = 1;
			}
			break;
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		//--Xu ly xoa ky tu khi bam phim Delete----------------------
		//	Bien xoa mot doi tuong thanh xoa nhieu doi tuong....
		case VK_DELETE:
			hdc = GetDC(hWnd);
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_UNDO  ,MAKELPARAM(TBSTATE_ENABLED , 0));
			SetROP2(hdc, R2_NOTXORPEN);
			if (g_nModeShape == MS_SELECTED)
			{
				paintListShape.DeleteObject(hdc);
				if (!g_MultiSelect.IsEmpty()) g_MultiSelect.Draw(hdc);
				MarkSelect.clear();				
				g_MultiSelect.Set();
			}		
			ReleaseDC(hWnd,hdc);

			break;
		}
		return 0 ;
	case WM_CHAR:
		if(g_nModeShape == MS_TEXT)
		{
			switch (wParam)
			{
			case '\b':                    // backspace
				{
					hdc = GetDC(hWnd);
					g_pObject->WriteText(hdc,RGB(255,255,255));					
					CallGrid(hWnd);
					g_pObject->EraseString(g_nPosCusor);
					//g_pObject->SetStrBuff((TCHAR)wParam);
					g_pObject->WriteText(hdc,g_pObject->m_crTextColor);
					//InvalidateRect(hWnd,*rcClient,TRUE);
					//m_xCaret=m_xCaret+100;
					ReleaseDC(hWnd, hdc);
				}
				break ;

			default:                      // character codes
				hdc = GetDC(hWnd);
				g_pObject->SetStrBuff((TCHAR)wParam);
				g_pObject->WriteText(hdc,g_pObject->m_crTextColor);
				//m_xCaret=m_xCaret+100;
				ReleaseDC(hWnd,hdc);
			}
		}
		break;
	//------------------------------------------------------------------------------------
	//----Ket thuc xu ly keyboard messages-----------------------------------------------
	case WM_PAINT:
		//Goi ham hien thi Ruler
		hdc = BeginPaint(hWnd, &ps);
		SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_CUT  ,MAKELPARAM(0 , 0));
		SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_COPY  ,MAKELPARAM(0 , 0));
		SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_DELETE, MAKELPARAM(0, 0));
		SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_PASTE, MAKELPARAM(0, 0));
		SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_UNDO  ,MAKELPARAM(0 , 0));
		SendMessage(g_hWndToolbar, TB_SETSTATE,ID_ROTATE_90, MAKELPARAM(0, 0));
		CallRuler(hWnd);
		CallGrid(hWnd);
		MarkSelect.clear();
		g_MultiSelect.Set();
		SetROP2(hdc, R2_NOTXORPEN);
		paintListShape.Draw(hdc);
		ReleaseDC(hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;

	/*Thuc hien khi nhan chuot trai*/
	case WM_LBUTTONDOWN: 
		hdc = GetDC(hWnd);
		if (paintListShape.AllowCutAndCopy())
		{
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_CUT  ,MAKELPARAM(TBSTATE_ENABLED , 0));
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_COPY  ,MAKELPARAM(TBSTATE_ENABLED , 0));
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_DELETE, MAKELPARAM(TBSTATE_ENABLED, 0));
		}
		else
		{
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_CUT  ,MAKELPARAM(0 , 0));
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_COPY  ,MAKELPARAM(0 , 0));
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_DELETE, MAKELPARAM(0, 0));
		}
		g_nCountShiftUp = 0;
		g_nCountShiftRight = 0;
		g_nCountShiftLeft = 0;
		g_nCountShiftDown = 0;
		paintListShape.DeleteEmptyTextObject(hdc);	//	neu co doi tuong text rong thi xoa di
		g_ptPaste.x = 400;	//	khoi tao toa do x cho vi tri paste dau tien
		g_ptPaste.y = 250;  //  khoi tao toa do y cho vi tri paste dau tien
		g_nCountPasteTime = 0;	//	khoi tao cho event Ctr+V (coi nhu chua nhan)
		if (g_bEditPenFlag || g_bFillFlag || g_bColorFlag)
		{
			nIndexObjSelect = g_nIndexObjSelect;
			goto UpdateObject;
		}
		// Save the coordinates of the mouse cursor.
		g_ptBegin = g_ptEnd = MAKEPOINTS(lParam);
		// Initialize Object via mode selected
		switch(g_nModeShape)
		{
		case MS_CIRCLE:
			g_pObject = new CCircleEX();
			s_bFlagInitial = true;
			break;
		case  MS_LINE:
			g_pObject = new CLineEX();
			s_bFlagInitial = true;
			break;
		case MS_RECT:
			g_pObject = new CRectangleEx();
			s_bFlagInitial = true;
			break;
		case MS_TRIANGLE:
			g_pObject = new CTriangleEX();
			s_bFlagInitial = true;
			break;
		case MS_RIGHT_TRIANGLE:
			g_pObject = new CRightTriangleEX();
			s_bFlagInitial = true;
			break;
		case MS_ROUNDED_RECTANGLE:
			g_pObject = new CRoundedRectEx();
			s_bFlagInitial = true;
			break;
		case MS_TEXT:
			g_pObject = new CTextEx();			
			s_bFlagInitial = true;
			break;
		case MS_SELECTED:
			if (!s_bFlagInitial)
				g_pObject = new CSelectEx();
			g_bFillClick = false;
			{			
			/*Giu lai kieu thao tac s_nMode khi click chon*/
			s_nMode = g_pObject->IsSelected(g_ptBegin);	
			/*Giu lai vi tri phan tu chon trong bien nIndexObjSelect*/
			g_nIndexObjSelect = nIndexObjSelect = paintListShape.IsSelected(hdc,g_ptBegin);
	UpdateObject:
			hdc = GetDC(hWnd);
			SetROP2(hdc,R2_NOTXORPEN);
			if (nIndexObjSelect != -1) /*Khi co phan tu duoc chon*/
			{	
				/*******************************************************/
				//Phan phun mau cua ChangePropertyObj					
				//	Cap nhat trang thai cua Fill
				if(!g_bFillClick)
				{
					g_bFilled = paintListShape.listShape.at(nIndexObjSelect)->m_bFilled;
					if (paintListShape.listShape.at(nIndexObjSelect)->m_bFilled)
					{
						/*g_bFilled = false;*/
						CheckMenuItem(GetSubMenu(g_hOptionsMenu, 2), 18, MF_BYPOSITION | MF_CHECKED);
						SendMessage(g_hWndToolbar, TB_SETSTATE,ID_DRAW_FILL  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
					}
					else
					{
						/*g_bFilled = true;*/
						CheckMenuItem(GetSubMenu(g_hOptionsMenu, 2), 18, MF_BYPOSITION | MF_UNCHECKED);
						SendMessage(g_hWndToolbar, TB_SETSTATE,ID_DRAW_FILL  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_ENABLED , 0));							
					}
				}
				else
					g_bFillClick = false;
				// Thay doi trang thai mau mac dinh khi nguoi dung chon vao bang mau
				if (!(wParam & MK_CONTROL)) /*Khi khong giu phim Ctrl*/
				{
					//Xoa hinh bao truoc do
					if (!g_MultiSelect.IsEmpty()) g_MultiSelect.Draw(hdc);	
					//Khoi tao danh sach va xoa tracker
					MarkSelect.clear();
					paintListShape.ClearTracker(hdc, nIndexObjSelect);					
				}
				//	xoa hinh bao cu				
				if (UpdateCover()&&!g_MultiSelect.IsEmpty())g_MultiSelect.Draw(hdc);	
				/*Giu lai doi tuong chon vao g_pObject*/
				g_pObject = paintListShape.GetObject(nIndexObjSelect);
				g_pObject->DrawSelected(hdc);					
				/*Cap nhat danh sach doi tuong chon*/
				UpdateListMulS(hdc, nIndexObjSelect, wParam);	
				if 	((g_pObject->m_nPattern == MS_TEXT)&&(g_pObject->m_bSelected))
				{						
					g_pObject->WriteText(hdc, RGB(255,255,255));
				}
				/*Ket thuc danh sach cap nhat */
				g_pObject = paintListShape.GetObject(nIndexObjSelect);
				/*Cap nhat va ve hinh bao moi*/
				if (UpdateCover()&&!g_MultiSelect.IsEmpty())g_MultiSelect.Draw(hdc);										
				//nTry = MarkSelect.size();  				
				
			}
			/*Khi chuot chon vao mien hinh bao va khong doi tuong nao duoc chon*/
			if ((nIndexObjSelect == -1) /*Khi khong doi tuong nao duoc chon*/
				&&((!g_MultiSelect.IsSelected(g_ptBegin))|| (MarkSelect.size() == 1) ))
				/*Khi chuot chon ngoai mien hinh bao hoac so doi tuong chon la 1 */
			{
				if (!(wParam & MK_CONTROL))
				{
					paintListShape.ClearTracker(hdc);
					hdc = GetDC(hWnd);							
					SetROP2(hdc, R2_NOTXORPEN);						
					if (!g_MultiSelect.IsEmpty()) g_MultiSelect.Draw(hdc);	
					MarkSelect.clear();					
					g_MultiSelect.Set();
				}
				bSelect = false;
			}
			else  /*Khi chuot chon vao mien hinh bao va khong doi tuong nao duoc chon*/
				if (g_MultiSelect.IsSelected(g_ptBegin))
				{
					if (MarkSelect.size()> 0) bSelect = true;	
					/*Khi so doi tuong chon nhieu hon 1 chi cho phep Move*/
					if (MarkSelect.size()> 1) 
						{
							for (size_t i = 0; i < MarkSelect.size(); i++) 
							{
								nControl = *(MarkSelect.at(i)); 
								g_pObject = paintListShape.GetObject(nControl);								
								if (g_pObject->m_nPattern == MS_TEXT) 
								{						
									g_pObject->WriteText(hdc, RGB(255,255,255));
								}
							};
							s_nMode = MR_DRAG;
						}
				}
			/*Goi thao tac phun mau cho doi tuong*/
			ChangePropertyObj(hdc);	
			/*Ket thuc goi thao tac phun mau*/			
			ReleaseDC(hWnd, hdc);
			}
			break;
		default:
			break;
		}
		/*Dat mau hien tai khi thuc hien ve*/
		if (g_nModeShape != MS_SELECTED)
		{			
			g_pObject->m_bFilled = g_bFilled;
			g_pObject->m_crBrushColor = g_crColor;
			g_pObject->m_crPenColor = g_crColor;
			g_pObject->m_dwPenStyle = g_nPenStyle;
			g_pObject->m_nPenWidth = g_nPenWidth;
			g_nIndexObjSelect = -1;
			g_bFillFlag = false;
			g_bEditPenFlag = false;
			g_bColorFlag = false;
			g_bFlagText = false;
		}
		//break;		
		ReleaseDC(hWnd, hdc); 
		break;
	/*Thuc hien khi di chuyen chuot trai*/
	case  WM_MOUSEMOVE:
		//	Draw cusor position on ruler
		if (g_bEnableRuler)
		{
			ruler.m_crCursorColor = RGB(255, 0, 0);
			ruler.DrawCursorPosition(hWnd, lParam);
		} 
		else
		{
			ruler.m_crCursorColor = RGB(255, 255, 255);
			ruler.DrawCursorPosition(hWnd,lParam);
		} 	
		hdc = GetDC(hWnd);
		g_ptEnd = MAKEPOINTS(lParam);		
		if ((MarkSelect.size() > 1)&&(g_MultiSelect.IsSelected(g_ptEnd)))
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));		
		if ((MarkSelect.size() == 1))g_pObject->IsSelected(g_ptEnd);
		if(g_nModeShape != MS_SELECTED)//Ve doi tuong moi
		{	
			/*Kiem tra dieu kien diem dau va gan lai neu khong thoa man*/
			if (g_ptBegin.x < (LEFTOFFSET+ g_nPenWidth + SIZERECTBORDER)) g_ptBegin.x = LEFTOFFSET+ g_nPenWidth + SIZERECTBORDER;
			if (g_ptBegin.y < (TOPOFFSET+ g_nPenWidth + SIZERECTBORDER)) g_ptBegin.y = TOPOFFSET+ g_nPenWidth + SIZERECTBORDER;
			if (g_ptEnd.x < (LEFTOFFSET+ g_nPenWidth + SIZERECTBORDER)) g_ptEnd.x = LEFTOFFSET+ g_nPenWidth + SIZERECTBORDER;
			if (g_ptEnd.y < (TOPOFFSET+ g_nPenWidth + SIZERECTBORDER)) g_ptEnd.y = TOPOFFSET+ g_nPenWidth + SIZERECTBORDER;
			/*Ket thuc phan kiem tra dieu kien diem dau*/
			if (wParam & MK_LBUTTON) 
			{                      
				SetROP2(hdc, R2_NOTXORPEN);
				if(!g_pObject->IsEmpty())
				{
				g_pObject->Draw(hdc);			//	Erase old object	
				if (g_pObject->m_nPattern == MS_TEXT)
					g_pObject->DrawSelected(hdc);
				}
				g_pObject->m_ptBegin = g_ptBegin;
				g_pObject->m_ptEnd = g_ptEnd;		//	update coordinates
				g_pObject->Draw(hdc);				//	Draw new object
				if (g_pObject->m_nPattern == MS_TEXT)
					g_pObject->DrawSelected(hdc);
				ReleaseDC(hWnd,hdc);
			}
		}
		/*Kiem tra dieu kien quet chon nhieu doi tuong*/
		if ((g_nModeShape == MS_SELECTED)&&(!(MarkSelect.size() > 0))&&(!bSelect))
		{	
			/*Kiem tra dieu kien diem dau va gan lai neu khong thoa man*/
			if (g_ptBegin.x < (LEFTOFFSET+ g_nPenWidth + SIZERECTBORDER)) g_ptBegin.x = LEFTOFFSET+ g_nPenWidth + SIZERECTBORDER;
			if (g_ptBegin.y < (TOPOFFSET+ g_nPenWidth + SIZERECTBORDER)) g_ptBegin.y = TOPOFFSET+ g_nPenWidth + SIZERECTBORDER;
			if (g_ptEnd.x < (LEFTOFFSET+ g_nPenWidth + SIZERECTBORDER)) g_ptEnd.x = LEFTOFFSET+ g_nPenWidth + SIZERECTBORDER;
			if (g_ptEnd.y < (TOPOFFSET+ g_nPenWidth + SIZERECTBORDER)) g_ptEnd.y = TOPOFFSET+ g_nPenWidth + SIZERECTBORDER;
			/*Ve hinh bao */
			if (wParam & MK_LBUTTON) 
			{ 	
				SetROP2(hdc, R2_NOTXORPEN);
				g_pObject->IsSelected(g_ptEnd);
				if(g_MultiSelect.m_bSelected)
					g_MultiSelect.Draw(hdc);			//	Erase old object					
				g_MultiSelect.m_ptBegin = g_ptBegin;
				g_MultiSelect.m_ptEnd = g_ptEnd;		//	update coordinates
				g_MultiSelect.Draw(hdc);				//	Draw new object
				ReleaseDC(hWnd,hdc);
			} 
		}
		/*Kiem tra doi tuong co duoc khong va thuc hien thao tac tuong ung*/
		if ((g_nModeShape == MS_SELECTED)&&(MarkSelect.size() > 0)&&(bSelect)) 
		{				
			SetROP2(hdc, R2_NOTXORPEN);			 			
			if (wParam & MK_LBUTTON)
			{
				if ((MarkSelect.size()> 1)&&(g_MultiSelect.Modify(hdc, g_ptBegin, g_ptEnd, s_nMode))
					||(MarkSelect.size()== 1))
					for (nControl = 0; nControl < MarkSelect.size(); nControl++)				
					{					
						nIndexObjSelect = *(MarkSelect.at(nControl));
						g_pObject = paintListShape.GetObject(nIndexObjSelect);
						g_pObject->Modify(hdc, g_ptBegin, g_ptEnd, s_nMode);	 									  
						paintListShape.SavePoint();						
					}; 
				g_ptBegin = g_ptEnd;
				
			}	
			ReleaseDC(hWnd,hdc);
		}
		/*Ket thuc phan thao tac voi doi tuong chon*/	
		// Cap nhat toa do (X,Y) cua control len Status bar	
		nTry = paintListShape.listShape.size();
		wsprintf(str,"X: %d", LOWORD(lParam)-OFFSET-LEFTRULER);
		//wsprintf(str,"X: %d",nTry);
		g_hWndStatus = GetDlgItem(hWnd, IDC_MAIN_STATUS);
		/*nTry = MarkSelect.size();*/
		SendMessage(g_hWndStatus, SB_SETTEXT, 1, (LPARAM)(LPSTR) str);
		//wsprintf(str,"Y: %d", HIWORD(lParam)-OFFSET-TOPRULER);
		/*wsprintf(str,"Y: %d", nTry);*/
		SendMessage(g_hWndStatus,SB_SETTEXT, 2, (LPARAM)(LPSTR) str);
		SendMessage((HWND) g_hWndStatus, (UINT) SB_SETTEXT, (WPARAM)(INT) 0 | 0, (LPARAM) (LPSTR) TEXT("Nguyen Van Tuyen"));
		SendMessage((HWND) g_hWndStatus, (UINT) SB_SETTEXT, (WPARAM)(INT) 0 | 3, (LPARAM) (LPSTR) TEXT("R:"));
		SendMessage((HWND) g_hWndStatus, (UINT) SB_SETTEXT, (WPARAM)(INT) 0 | 4, (LPARAM) (LPSTR) TEXT("G:"));	
		SendMessage((HWND) g_hWndStatus, (UINT) SB_SETTEXT, (WPARAM)(INT) 0 | 5, (LPARAM) (LPSTR) TEXT("B:"));
		break;
	/*Thuc hien khi tha chuot*/
	case  WM_LBUTTONUP:
		hdc = GetDC(hWnd);		
		if (g_bFlagText)
		{
			g_bFlagText = false;
			paintListShape.ClearTracker(hdc);
			MarkSelect.clear();
			g_MultiSelect.Set();
			InvalidateRect(hWnd,NULL,TRUE);
			UpdateWindow(hWnd);

		}
		/*Cap nhat lai danh sach doi tuong chon khi quet chuot*/
		if ((g_nModeShape == MS_SELECTED)&&(!(MarkSelect.size() > 0))&&(!bSelect))
		{	
			MarkSelect.clear();
			SetROP2(hdc, R2_NOTXORPEN);
			if(g_MultiSelect.m_bSelected)g_MultiSelect.Draw(hdc);	
			MultiSelect(hdc,g_ptBegin,g_ptEnd);
			if (UpdateCover()&&!g_MultiSelect.IsEmpty())g_MultiSelect.Draw(hdc);	
		}
		if (MarkSelect.size() > 0) bSelect = true;
		else 
			{
				bSelect = false;
				g_MultiSelect.Set();
			}
		/* Ket thuc phan Cap nhat lai danh sach doi tuong chon*/
		if (paintListShape.AllowCutAndCopy())
		{
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_CUT  ,MAKELPARAM(TBSTATE_ENABLED , 0));
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_COPY  ,MAKELPARAM(TBSTATE_ENABLED , 0));
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_DELETE, MAKELPARAM(TBSTATE_ENABLED, 0));
			SendMessage(g_hWndToolbar, TB_SETSTATE,ID_ROTATE_90, MAKELPARAM(TBSTATE_ENABLED, 0));
		}
		else
		{
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_CUT  ,MAKELPARAM(0 , 0));
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_COPY  ,MAKELPARAM(0 , 0));
			SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_DELETE, MAKELPARAM(0, 0));
			SendMessage(g_hWndToolbar, TB_SETSTATE,ID_ROTATE_90, MAKELPARAM(0, 0));
		}
		/* Thiet lap lai duong bao khi neu truoc do thuc hien modify*/
		if(!(wParam & MK_CONTROL)&&(g_nModeShape == MS_SELECTED))	
		{			
			for (nControl = 0; nControl < MarkSelect.size(); nControl++)				
			{					
				nIndexObjSelect = *(MarkSelect.at(nControl));
				g_pObject = paintListShape.GetObject(nIndexObjSelect);
				if 	(g_pObject->m_nPattern == MS_TEXT)	
				{
					g_pObject->WriteText(hdc,g_pObject->m_crTextColor);					
					g_bFlagText = true;
				}
			};			
			nIndexObjSelect = -1;				
		}
		/* Ket thuc phan thiet lap lai*/
		/* Cap nhat lai danh sach hinh ve khi thao tac truoc do la ve*/
		if(g_nModeShape != MS_SELECTED)	// MODE DRAWING
		{
			if (!g_pObject->IsEmpty())
			{
				paintListShape.AddShapeToList(g_pObject);
				paintListShape.SavePoint();
			}
		}
		/* Ket thuc phan cap nhat lai*/
		nCurrentShape = paintListShape.GetCurrentShape();
		sprintf_s( str,"Draw");
		SetWindowText ( hWnd, str );
		ReleaseDC(hWnd,hdc);			
		break;	
	case WM_RBUTTONUP:
		{
			s_ptRightButton.x = LOWORD(lParam);
			s_ptRightButton.y = HIWORD(lParam);
			s_hMenu = CreatePopupMenu();
			ClientToScreen(hWnd, &s_ptRightButton);
			AppendMenu(s_hMenu, MF_STRING, ID_PEN_EDITPEN, TEXT("Edit Pen"));
			AppendMenu(s_hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenu(s_hMenu, MF_STRING, IDD_COPY, TEXT("&Copy"));
			AppendMenu(s_hMenu, MF_STRING, IDD_CUT, TEXT("Cut"));
			AppendMenu(s_hMenu, MF_STRING, IDD_PASTE, TEXT("Paste"));
			AppendMenu(s_hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenu(s_hMenu, MF_STRING, ID_CLEAR, TEXT("Clear"));
			AppendMenu(s_hMenu, MF_STRING, IDD_DELETE, TEXT("Delete")); 
			TrackPopupMenu(s_hMenu, TPM_RIGHTBUTTON, s_ptRightButton.x, s_ptRightButton.y, 0, hWnd, NULL);
			DestroyMenu(s_hMenu);
		}
		break;
	case WM_RBUTTONDOWN:
		g_ptDes = MAKEPOINTS(lParam);
		g_nCountPasteTime = 0;
		break;
	case  WM_SIZE:
		// Convert the client coordinates of the client-area  
		// rectangle to screen coordinates and save them in a  
		// rectangle. The rectangle is passed to the ClipCursor  
		// function during WM_LBUTTONDOWN processing.  
		GetClientRect(hWnd, &rcClient); 
		ptClientUL.x = rcClient.left + LEFTRULER + OFFSET; 
		ptClientUL.y = rcClient.top + TOPRULER + OFFSET; 
		ptClientLR.x = rcClient.right; 
		ptClientLR.y = rcClient.bottom; 
		ClientToScreen(hWnd, &ptClientUL); 
		ClientToScreen(hWnd, &ptClientLR); 
		SetRect(&rcClient, ptClientUL.x, ptClientUL.y, ptClientLR.x, ptClientLR.y);

		g_hWndStatus = GetDlgItem(hWnd, IDC_MAIN_STATUS);
		SendMessage(g_hWndStatus, WM_SIZE, 0, 0);
		SendMessage(g_hWndToolbar, TB_AUTOSIZE, 0, 0);
		{
			RECT clientRect;
			GetClientRect(hWnd,&clientRect);
			int minSize = (int)(clientRect.right/11);
			int Statwidths[] = {5*minSize, 6*minSize, 7*minSize,8*minSize, 9*minSize,10*minSize, -1};
			SendMessage(g_hWndStatus, SB_SETPARTS, (WPARAM)(sizeof(Statwidths)/sizeof(int)), (LPARAM)Statwidths);
			SendMessage((HWND) g_hWndStatus, (UINT) SB_SETTEXT, (WPARAM)(INT) 0 | 0, (LPARAM) (LPSTR) TEXT("Nguyen Van Tuyen"));
		}
		hdc = GetDC(hWnd);
		paintListShape.ClearTracker(hdc);
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd,NULL,TRUE);
		UpdateWindow(hWnd);
		break;

	case WM_VSCROLL:
		hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
		switch (LOWORD (wParam))
		{
		case SB_LINEUP:
            s_fFlagMove = true;
			s_iVscrollPos -= 1 ;
			// Xoa net cu
			paintListShape.Draw(hdc); 
			paintListShape.ClearTracker(hdc);
			paintListShape.DeleteText(hdc);
            paintListShape.MoveObject(0, +10);
			paintListShape.SavePoint();
			//Ve hinh moi
			paintListShape.Draw(hdc);
			paintListShape.ClearTracker(hdc);
			ReleaseDC(hWnd,hdc);
			break ;
		case SB_LINEDOWN:
            s_fFlagMove = true;
            //Khi hinh ve dung lai cham sat vao ruler thi Vscrollbar dung lai
            for (int i = 0; i< (int)paintListShape.listShape.size(); i++)
            {
                if (((int)paintListShape.listShape.at(i)->m_ptBegin.y - 5 <= 
                                 TOPOFFSET + g_nPenWidth + SIZERECTBORDER) ||
                     ((int)paintListShape.listShape.at(i)->m_ptEnd.y - 5 <= 
                                 TOPOFFSET + g_nPenWidth + SIZERECTBORDER))
                {
                    s_fFlagMove = false;
                    break;
                }
            }
            if (s_fFlagMove == true)
            {
			    s_iVscrollPos += 1 ;
			    // Xoa net cu
			    paintListShape.Draw(hdc); 
			    paintListShape.ClearTracker(hdc);
				paintListShape.DeleteText(hdc);
			    paintListShape.MoveObject(0, -10);
				paintListShape.SavePoint();
			    //Ve hinh moi
			    paintListShape.Draw(hdc);
			    paintListShape.ClearTracker(hdc);
			    ReleaseDC(hWnd,hdc);
            }
			break ;
		case SB_THUMBPOSITION:
            s_fFlagMove = true;
            // Lay toa 2 toa do thumb lien tiep nhau
            iTempScrollPos = s_iVscrollPos;
            // vi tri thumb
            s_iVscrollPos = HIWORD (wParam) ;
            //Khi hinh ve dung lai cham sat vao ruler thi Vscrollbar dung lai
            if((iTempScrollPos - s_iVscrollPos) < 0)
            {
                for (int i = 0; i< (int)paintListShape.listShape.size(); i++)
                {
                    if (((int)paintListShape.listShape.at(i)->m_ptBegin.y +
                        10*(iTempScrollPos - s_iVscrollPos)) <= 
                        TOPOFFSET + g_nPenWidth + SIZERECTBORDER)
                    {
                        s_fFlagMove = false;
                        break;
                    }
                }
            }
            if (s_fFlagMove == true)
            {
                // Xoa net cu
                paintListShape.Draw(hdc); 
                paintListShape.ClearTracker(hdc);
				paintListShape.DeleteText(hdc);
                // Di chuyen doi tuong theo thumb
                paintListShape.MoveObject(0,10*(iTempScrollPos - s_iVscrollPos));
				paintListShape.SavePoint();
                //Ve hinh moi
                paintListShape.Draw(hdc);
                paintListShape.ClearTracker(hdc);
                ReleaseDC(hWnd,hdc);
            }
			break ;
		default :
			break ;
		}
		//Dat vi tri thumb theo vi tri hien thoi s_iVscrollPos
		SetScrollPos (hWnd, SB_VERT, s_iVscrollPos, TRUE) ;
		break ;
    /************************************************************************
    Horizontal scroll bar 
    ************************************************************************/
	case WM_HSCROLL:
		hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
		switch (LOWORD (wParam))
		{
		case SB_LINELEFT:
            s_fFlagMove = true;
			s_iHscrollPos-= 1 ;
			// Xoa
			paintListShape.Draw(hdc); 
			paintListShape.ClearTracker(hdc);
			paintListShape.DeleteText(hdc);
			paintListShape.MoveObject(10, 0);
			paintListShape.SavePoint();
			//Ve
			paintListShape.Draw(hdc);
			paintListShape.ClearTracker(hdc);
			ReleaseDC(hWnd,hdc);
			break ;
		case SB_LINERIGHT:
            s_fFlagMove = true;
            //Khi hinh ve dung lai cham sat vao ruler thi Hscrollbar dung lai
            for (int i = 0; i< (int)paintListShape.listShape.size(); i++)
            {
                if (((int)paintListShape.listShape.at(i)->m_ptBegin.x - 5 <= 
                    LEFTOFFSET + g_nPenWidth + SIZERECTBORDER) ||
                    ((int)paintListShape.listShape.at(i)->m_ptEnd.x - 5 <=
                    LEFTOFFSET + g_nPenWidth + SIZERECTBORDER))
                {
                    s_fFlagMove = false;
                    break;
                }
            }
            if (s_fFlagMove == true)
            {
                s_iHscrollPos += 1 ;
                // Xoa
                paintListShape.Draw(hdc); 
                paintListShape.ClearTracker(hdc);
				paintListShape.DeleteText(hdc);
                paintListShape.MoveObject(-10, 0);
				paintListShape.SavePoint();
                //Ve
                paintListShape.Draw(hdc);
                paintListShape.ClearTracker(hdc);
                ReleaseDC(hWnd,hdc);
            }
			break ;
		case SB_THUMBPOSITION:
            s_fFlagMove = true;
            // Lay toa 2 toa do thumb lien tiep nhau
            iTempScrollPos = s_iHscrollPos;
            // vi tri thumb
            s_iHscrollPos = HIWORD (wParam) ;
            //Khi hinh ve dung lai cham sat vao ruler thi Hscrollbar dung lai
            if((iTempScrollPos-s_iHscrollPos) < 0)
            {
                for (int i = 0; i< (int)paintListShape.listShape.size(); i++)
                {
                    if (((int)paintListShape.listShape.at(i)->m_ptBegin.x +
                        5*(iTempScrollPos - s_iHscrollPos)) <= 
                        LEFTOFFSET + g_nPenWidth + SIZERECTBORDER)
                    {
                        s_fFlagMove = false;
                        break;
                    }
                }
            }
            if (s_fFlagMove == true)
            {
                // Xoa net cu
                paintListShape.Draw(hdc); 
                paintListShape.ClearTracker(hdc);
				paintListShape.DeleteText(hdc);
                // Di chuyen doi tuong theo thumb
                paintListShape.MoveObject(10*(iTempScrollPos - s_iHscrollPos),0);
				paintListShape.SavePoint();
                //Ve hinh moi
                paintListShape.Draw(hdc);
                paintListShape.ClearTracker(hdc);
                ReleaseDC(hWnd,hdc);
            }
            break;
		default :
			break ;
		}
		SetScrollPos (hWnd, SB_HORZ, s_iHscrollPos, TRUE) ;
		break ;
	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

COLORREF ShowColorDialog(HWND hwnd)
{
	CHOOSECOLOR cc;   
	COLORREF crCustClr[] = {RGB(0,    5,   5),
							RGB(0,    15,  55),
							RGB(0,    25, 155),
							RGB(0,    35, 255),
							RGB(10,    0,   5),
							RGB(10,   20,  55),
							RGB(10,   40, 155),
							RGB(10,   60, 255),
							RGB(100,   5,   5),
							RGB(100,  25,  55),
							RGB(100,  50, 155),
							RGB(100, 125, 255),
							RGB(200, 120,   5),
							RGB(200, 150,  55),
							RGB(200, 200, 155),
							RGB(200, 250, 255) };

		ZeroMemory(&cc, sizeof(cc));
		cc.lStructSize = sizeof(cc);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = (LPDWORD) crCustClr;
		if (g_nIndexObjSelect != -1)
			cc.rgbResult = paintListShape.listShape.at(g_nIndexObjSelect)->m_crPenColor;
		else
			cc.rgbResult = RGB(0, 255, 0);
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;
		ChooseColor(&cc);
	return cc.rgbResult;
}

/**********************************************************************
Declare function and global variable
/* 1. Function LoadFileToList
Function use to load properties on file to paintListShape
Input: handle of main window
Output: paintListShape;
/************************************************************************/
BOOL LoadFileToList(HWND hWnd)
{
	TCHAR szFileName[MAX_PATH] = "";	//Get file name to load
	// Query user to open file
	OPENFILENAME ofn;
	BOOL bLoaded = FALSE;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = "PaintEX (*.pex)\0*.pex\0";  	
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = "pex";
	if (GetOpenFileName(&ofn))
	{
		ifstream pFile;
		paintListShape.ClearListShape();
		paintListShape.LoadToFile(pFile, szFileName);
		bLoaded = TRUE;
	}
	return bLoaded;
}
/************************************************************************/
/* 1. Function SaveFileToList
Function use to load properties on file to paintListShape
Input: handle of main window
Output: File Save;
/*************************************************************************/
BOOL SaveFileToList(HWND hWnd)
{
	TCHAR szFileName[MAX_PATH] = "PaintEX1";		//Set file name to save
	BOOL bSaved = FALSE;
	if (strcmp(szFileName, "PaintEX1") == 0)
	{
		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFilter = "PaintEX Files (*.pex)\0*.pex\0";
		ofn.lpstrFile = szFileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = "pex";
		ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
		if (!GetSaveFileName(&ofn))
			return FALSE;
	}
	ofstream pFile;
	paintListShape.SaveToFile(pFile, szFileName);
	bSaved = TRUE;
	return bSaved;
}
/************************************************************************/
/* 1. Function ClearDC
Function use clear paintListShape and clear DC
Input: handle of main window
/*************************************************************************/
bool ClearDC(HWND hWnd)
{
	if(paintListShape.GetCurrentShape() == 0)
		return true;
	paintListShape.ClearListShape();
	MarkSelect.clear();
	g_MultiSelect.Set();	
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
	return true;
}
/************************************************************************/
/* Create NewDialog
Function use Cut a Object in DC
/*************************************************************************/
INT_PTR CALLBACK NewDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDYES)
		{
			SaveFileToList(hDlg);
			paintListShape.ClearListShape();
			{
				CheckAndUncheck(17);
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarButton = ID_DRAW_SELECTOBJECTS;
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				g_nModeShape = MS_SELECTED;
				SendMessage(g_hWndToolbar,TB_SETSTATE,ID_DRAW_FILL,MAKELPARAM(TBSTATE_ENABLED,0));
				SendMessage(g_hWndToolbar,TB_SETSTATE,ID_VIEW_GRID,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_PRESSED,0));
				SendMessage(g_hWndToolbar,TB_SETSTATE,ID_VIEW_RULER,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_PRESSED,0));
				SendMessage(g_hWndToolbar,TB_SETSTATE,ID_ZOOM_ZOOMIN,MAKELPARAM(TBSTATE_ENABLED,0));
				SendMessage(g_hWndToolbar,TB_SETSTATE,ID_ZOOM_ZOOMOUT,MAKELPARAM(TBSTATE_ELLIPSES,0));
				SendMessage(g_hWndStatus, (UINT) SB_SETTEXT, (WPARAM)(INT) 0 | 6, (LPARAM) (LPSTR) TEXT("Zoom: 100%"));
				g_bFilled = FALSE;
				g_bEnableRuler = TRUE;
				g_bEnableGrid = TRUE;
				g_nPenStyle = PS_SOLID;
				g_crColor = RGB(0, 0, 0);
				g_nPenWidth = PW_ONE;
				g_nZoomRate = 1;
				CheckMenuItem(GetSubMenu(g_hOptionsMenu, 1), 6, MF_BYPOSITION | MF_UNCHECKED);
				CheckMenuItem(GetSubMenu(g_hOptionsMenu, 1), 7, MF_BYPOSITION | MF_UNCHECKED);
				CheckMenuItem(GetSubMenu(g_hOptionsMenu, 2), 18, MF_BYPOSITION | MF_UNCHECKED);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if(LOWORD(wParam) == IDNO)
		{
			paintListShape.ClearListShape();
			{
				CheckAndUncheck(17);
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarButton = ID_DRAW_SELECTOBJECTS;
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				g_nModeShape = MS_SELECTED;
				SendMessage(g_hWndToolbar,TB_SETSTATE,ID_DRAW_FILL,MAKELPARAM(TBSTATE_ENABLED,0));
				SendMessage(g_hWndToolbar,TB_SETSTATE,ID_VIEW_GRID,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_PRESSED,0));
				SendMessage(g_hWndToolbar,TB_SETSTATE,ID_VIEW_RULER,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_PRESSED,0));
				SendMessage(g_hWndToolbar,TB_SETSTATE,ID_ZOOM_ZOOMIN,MAKELPARAM(TBSTATE_ENABLED,0));
				SendMessage(g_hWndToolbar,TB_SETSTATE,ID_ZOOM_ZOOMOUT,MAKELPARAM(TBSTATE_ELLIPSES,0));
				SendMessage(g_hWndStatus, (UINT) SB_SETTEXT, (WPARAM)(INT) 0 | 6, (LPARAM) (LPSTR) TEXT("Zoom: 100%"));
				g_bFilled = FALSE;
				g_bEnableRuler = TRUE;
				g_bEnableGrid = TRUE;
				g_nPenStyle = PS_SOLID;
				g_crColor = RGB(0, 0, 0);
				g_nPenWidth = PW_ONE;
				g_nZoomRate = 1;
				CheckMenuItem(GetSubMenu(g_hOptionsMenu, 1), 6, MF_BYPOSITION | MF_UNCHECKED);
				CheckMenuItem(GetSubMenu(g_hOptionsMenu, 1), 7, MF_BYPOSITION | MF_UNCHECKED);
				CheckMenuItem(GetSubMenu(g_hOptionsMenu, 2), 18, MF_BYPOSITION | MF_UNCHECKED);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if(LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)FALSE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

/************************************************************************/
/* Create EditPenDialog
/*************************************************************************/
INT_PTR CALLBACK EditPenDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	int nPenSize = IDC_SIZE1;
	int nPenStyle = IDB_STYLE1;
	if (g_nIndexObjSelect != -1)
	{
		if (paintListShape.listShape.at(g_nIndexObjSelect)->m_nPenWidth == PW_ONE)
			nPenSize = IDC_SIZE1;
		else if (paintListShape.listShape.at(g_nIndexObjSelect)->m_nPenWidth == PW_TWO)
			nPenSize = IDC_SIZE2;
		else if (paintListShape.listShape.at(g_nIndexObjSelect)->m_nPenWidth == PW_THREE)
			nPenSize = IDC_SIZE3;
		else if (paintListShape.listShape.at(g_nIndexObjSelect)->m_nPenWidth == PW_FOUR)
			nPenSize = IDC_SIZE4;
		else if (paintListShape.listShape.at(g_nIndexObjSelect)->m_nPenWidth == PW_FIVE)
			nPenSize = IDC_SIZE5;
		if (paintListShape.listShape.at(g_nIndexObjSelect)-> m_dwPenStyle == PS_SOLID)
			nPenStyle = IDB_STYLE1;
		else if (paintListShape.listShape.at(g_nIndexObjSelect)-> m_dwPenStyle == PS_DOT)
			nPenStyle = IDB_STYLE2;
		else if (paintListShape.listShape.at(g_nIndexObjSelect)-> m_dwPenStyle == PS_DASHDOT)
			nPenStyle = IDB_STYLE3;
	}
	else
	{
		nPenSize = IDC_SIZE1;
		nPenStyle = IDB_STYLE1;
	}
	switch (message)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg,IDC_SIZE1,IDC_SIZE5,nPenSize);
		CheckRadioButton(hDlg,IDB_STYLE1,IDB_STYLE3,nPenStyle);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
 			if(SendMessage(GetDlgItem(hDlg,IDC_SIZE1),BM_GETCHECK,0,0) == BST_CHECKED)
  				g_nPenWidth = PW_ONE;
 			else if(SendMessage(GetDlgItem(hDlg,IDC_SIZE2),BM_GETCHECK,0,0) == BST_CHECKED)
  				g_nPenWidth = PW_TWO;
 			else if(SendMessage(GetDlgItem(hDlg,IDC_SIZE3),BM_GETCHECK,0,0) == BST_CHECKED)
  				g_nPenWidth = PW_THREE;
 			else if(SendMessage(GetDlgItem(hDlg,IDC_SIZE4),BM_GETCHECK,0,0) == BST_CHECKED)
  				g_nPenWidth = PW_FOUR;
 			else if(SendMessage(GetDlgItem(hDlg,IDC_SIZE5),BM_GETCHECK,0,0) == BST_CHECKED)
				g_nPenWidth = PW_FIVE;

 			if(SendMessage(GetDlgItem(hDlg,IDB_STYLE1),BM_GETCHECK,0,0) == BST_CHECKED)
  				g_nPenStyle = PS_SOLID;
  			else if(SendMessage(GetDlgItem(hDlg,IDB_STYLE2),BM_GETCHECK,0,0) == BST_CHECKED)
 				g_nPenStyle = PS_DOT;
 			else if(SendMessage(GetDlgItem(hDlg,IDB_STYLE3),BM_GETCHECK,0,0) == BST_CHECKED)
				g_nPenStyle = PS_DASHDOT;
			
			EndDialog(hDlg, LOWORD(wParam));
			//	bat co bao hieu da chinh sua kieu but
			g_bEditPenFlag = true;
			return (INT_PTR)TRUE;
		}
		if(LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			//	bat co bao hieu da chinh sua kieu but
			g_bEditPenFlag = false;
			return (INT_PTR)FALSE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
/************************************************************************
End Declare function and global variable                               
***********************************************************************/

LRESULT CmdProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	BOOL flag=TRUE;
	HDC hdc;
	static CGridEX grid;
	int wmId    = LOWORD(wParam);
	int wmEvent = HIWORD(wParam);
	g_hOptionsMenu = GetMenu(hWnd);
	// Parse the menu selections:
	switch (wmId)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;

	case IDC_ZOOM_SCALE:
		DialogBox(hInst, MAKEINTRESOURCE(IDC_ZOOM_SCALE), hWnd, About);
		break;

	case ID_PEN_EDITPEN:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_EditPen), hWnd, EditPenDialog);
		//	Add them co bao da thay doi che do phu mau
		if (MarkSelect.size()>0)
		{
			if(g_bEditPenFlag)
				SendMessage(hWnd, WM_LBUTTONDOWN, NULL, NULL);
		}
		else
			g_bEditPenFlag = false;
		break;
	case ID_FILE_NEW:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_NEW), hWnd, NewDialog);
		hdc = GetDC(hWnd);
		paintListShape.ClearTracker(hdc);
		MarkSelect.clear();
		g_MultiSelect.Set();
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;

	case ID_FILE_OPEN:
		LoadFileToList(hWnd);
		hdc = GetDC(hWnd);
		paintListShape.ClearTracker(hdc);
		MarkSelect.clear();
		g_MultiSelect.Set();
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;

	case ID_FILE_SAVEAS:
		SaveFileToList(hWnd);
		hdc = GetDC(hWnd);
		paintListShape.ClearTracker(hdc);
		MarkSelect.clear();
		g_MultiSelect.Set();
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd,NULL,TRUE);
		UpdateWindow(hWnd);
		break;

	case ID_FILE_SAVE:
		SaveFileToList(hWnd);
		hdc = GetDC(hWnd);
		paintListShape.ClearTracker(hdc);
		MarkSelect.clear();
		g_MultiSelect.Set();
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd,NULL,TRUE);
		UpdateWindow(hWnd);
		break;

	case ID_COLOR_EDITCOLOR:
		g_crColor = ShowColorDialog(hWnd);
		//	Add them co bao da thay doi che do phu mau
		if (MarkSelect.size()>0) 
		{
			g_bColorFlag = true;
			SendMessage(hWnd, WM_LBUTTONDOWN, NULL, NULL);
		}
		else
			g_bColorFlag = false;  
		break;
		
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case ID_DRAW_SELECTOBJECTS:
		if(g_nIdToolbarButton != ID_DRAW_SELECTOBJECTS)
			{
				CheckAndUncheck(17);
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarButton = ID_DRAW_SELECTOBJECTS;
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				g_nModeShape = MS_SELECTED;
				break;
			}
		else 
			{
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
			}
		break;

	case ID_DRAW_CIRCLE:
		if(g_nIdToolbarButton != ID_DRAW_CIRCLE)
			{
				CheckAndUncheck(4);
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarButton = ID_DRAW_CIRCLE;
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				g_nModeShape = MS_CIRCLE;
				break;
			}
		else 
		{
			SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
		}	
		break;

	case ID_DRAW_LINE:
		if(g_nIdToolbarButton != ID_DRAW_LINE)
			{
				CheckAndUncheck(0);
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarButton = ID_DRAW_LINE;
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				g_nModeShape = MS_LINE;
				break;
			}
		else 
		{
			SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
		}	
		break;

	case ID_DRAW_RECTANGLE:
		if(g_nIdToolbarButton != ID_DRAW_RECTANGLE)
			{
				CheckAndUncheck(1);
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarButton = ID_DRAW_RECTANGLE;
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				g_nModeShape = MS_RECT;
				break;
			}
		else 
		{
			SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
		}	
		break;

	case ID_DRAW_TRIANGLE:
		if(g_nIdToolbarButton != ID_DRAW_TRIANGLE)
			{	
				CheckAndUncheck(6);
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarButton = ID_DRAW_TRIANGLE;
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				g_nModeShape = MS_TRIANGLE;
				break;
			}
		else 
			{
			SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
			}	
		break;

	case ID_DRAW_RIGHTTRIANGLE:
		if(g_nIdToolbarButton != ID_DRAW_RIGHTTRIANGLE)
			{
				CheckAndUncheck(7);
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarButton = ID_DRAW_RIGHTTRIANGLE;
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				g_nModeShape = MS_RIGHT_TRIANGLE;
				break;
			}	
		else 
		{
			SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
		}	
		break;

	case ID_DRAW_ROUNDEDRECTANGLE:
		if(g_nIdToolbarButton != ID_DRAW_ROUNDEDRECTANGLE)
			{
				CheckAndUncheck(2);
				SendMessage(g_hWndToolbar, TB_SETSTATE, g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarButton = ID_DRAW_ROUNDEDRECTANGLE;
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				g_nModeShape = MS_ROUNDED_RECTANGLE;
				break;
			}
		else 
		{
			SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
		}	
		break;

	case  ID_DRAW_TEXT:
		if(g_nIdToolbarButton != ID_DRAW_TEXT)
			{
				CheckAndUncheck(15);
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarButton = ID_DRAW_TEXT;
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				g_nModeShape = MS_TEXT;
				break;
			}
		else 
			{
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarButton  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
			}	
		break;

	/*Ket thuc tao nut moi*/
	case ID_CLEAR: 
		g_nCountShiftDown = 0;
		g_nCountShiftUp = 0;
		g_nCountShiftLeft = 0;
		g_nCountShiftRight = 0;
		paintListShape.ClearListShape();
		MarkSelect.clear();
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;

	case IDD_DELETE:
		hdc = GetDC(hWnd);
		SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_UNDO  ,MAKELPARAM(TBSTATE_ENABLED , 0));
		SetROP2(hdc, R2_NOTXORPEN);
		if (g_nModeShape == MS_SELECTED)
			{
				paintListShape.DeleteObject(hdc);
				if(!g_MultiSelect.IsEmpty()) g_MultiSelect.Draw(hdc);
				MarkSelect.clear();
				nTry = MarkSelect.size();
				g_MultiSelect.Set();
			}	
		ReleaseDC(hWnd,hdc);
		break;
	case  ID_DRAW_FILL:
		g_bFillClick = true;			// Bat co neu nhu nguoi dung click vao buttom fill
		g_bFilled = !g_bFilled;
		if (g_bFilled)
			{
				CheckMenuItem(GetSubMenu(g_hOptionsMenu, 2), 18, MF_BYPOSITION | MF_CHECKED);
				SendMessage(g_hWndToolbar, TB_SETSTATE,ID_DRAW_FILL  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
			}
		else
			{
				CheckMenuItem(GetSubMenu(g_hOptionsMenu, 2), 18, MF_BYPOSITION | MF_UNCHECKED);
				SendMessage(g_hWndToolbar, TB_SETSTATE,ID_DRAW_FILL  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_ENABLED , 0));
			}
		//	Add them co bao da thay doi che do phu mau
		if (MarkSelect.size()>0)
			{
				g_bFillFlag = true;
				SendMessage(hWnd, WM_LBUTTONDOWN, NULL, NULL);
			}
		else
			g_bFillFlag = false;
		break;
	//Thuc hien quay
	case  IDM_SELECTALL:
		hdc = GetDC(hWnd);
		if (g_nModeShape == MS_SELECTED)
			{
				SetROP2(hdc, R2_NOTXORPEN);
				if(!g_MultiSelect.IsEmpty())g_MultiSelect.Draw(hdc);
				g_MultiSelect.Set();
				MarkSelect.clear();
				paintListShape.ClearTracker(hdc);
				MultiSelect(hdc, g_MultiSelect.m_ptBegin,g_MultiSelect.m_ptEnd);
				UpdateCover();			
				if(!g_MultiSelect.IsEmpty())g_MultiSelect.Draw(hdc);
			} 
		SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_COPY  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_ENABLED , 0));
		SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_CUT  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_ENABLED , 0));
		SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_DELETE  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_ENABLED , 0));
		SendMessage(g_hWndToolbar, TB_SETSTATE,ID_ROTATE_90  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_ENABLED , 0));
		ReleaseDC(hWnd, hdc);
		break;
	case ID_ROTATE_90:
		hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
		/*Thuc hien phep quay_edit */
		if ((g_nModeShape == MS_SELECTED)&& ( MarkSelect.size() > 0))
		{			
			if (!g_MultiSelect.IsEmpty()) g_MultiSelect.Draw(hdc);			
			for (size_t i = 0; i < MarkSelect.size(); i++) 
			{
				nControl = *(MarkSelect.at(i)); 
				g_pObject = paintListShape.GetObject(nControl);
				g_pObject->Rotate(hdc);	
				if ((g_pObject->m_nPattern == MS_TEXT))
					g_bFlagText = true;
			};
			if (UpdateCover()) g_MultiSelect.Draw(hdc);			
		}
		ReleaseDC(hWnd , hdc);
		if (g_bFlagText)
		{
			g_bFlagText = false;
			paintListShape.ClearTracker(hdc);
			MarkSelect.clear();
			g_MultiSelect.Set();
			InvalidateRect(hWnd,NULL,TRUE);
			UpdateWindow(hWnd);
		}
		
		break;

	case IDM_FONT:
		if (g_nModeShape == MS_SELECTED)
			{	
				paintListShape.ChoseFont(hWnd);
			}	
		break;

	//Dat thuoc tinh cho nut can le TEXT
	case ID_TEXT_LEFT:
		if(g_nIdToolbarText != ID_TEXT_LEFT)
			{	
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarText  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarText = ID_TEXT_LEFT;
				if (g_nModeShape==MS_TEXT||g_nModeShape==MS_SELECTED)
					{			
						hdc = GetDC(hWnd);
						g_pObject->WriteText(hdc,RGB(255,255,255));
						CallGrid(hWnd);
						g_pObject->SetFormat(DEFAULT_FORMAT);
						g_pObject->WriteText(hdc,g_pObject->m_crTextColor);
						ReleaseDC(hWnd,hdc);
					}
			}
		else 
			{
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarText  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
			}
		break;

	case ID_TEXT_CENTER:
		if(g_nIdToolbarText != ID_TEXT_CENTER)
			{
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarText  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarText = ID_TEXT_CENTER;
				if (g_nModeShape==MS_TEXT||g_nModeShape==MS_SELECTED)
				{		
					hdc = GetDC(hWnd);			
					g_pObject->WriteText(hdc,RGB(255,255,255));		
					CallGrid(hWnd);
					g_pObject->SetFormat(TEXT_CENTER);
					g_pObject->WriteText(hdc,g_pObject->m_crTextColor); 
					ReleaseDC(hWnd,hdc);
					break;
				}
			}
		else 
			{
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarText  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
			}
		break;

	case ID_TEXT_RIGHT:
		if(g_nIdToolbarText != ID_TEXT_RIGHT)
			{
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarText  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				g_nIdToolbarText = ID_TEXT_RIGHT;
				if (g_nModeShape==MS_TEXT||g_nModeShape==MS_SELECTED)
				{			
					hdc = GetDC(hWnd);				
					g_pObject->WriteText(hdc,RGB(255,255,255));				
					CallGrid(hWnd);
					g_pObject->SetFormat(TEXT_RIGHT);
					g_pObject->WriteText(hdc,g_pObject->m_crTextColor);
					ReleaseDC(hWnd,hdc);
				}
			}
		else 
			{
				SendMessage(g_hWndToolbar, TB_SETSTATE,g_nIdToolbarText  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
			}
		break;
	case ID_ZOOM_ZOOMIN :
		hdc=GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
        //Khi zoom thi bat ruler len(nut bam ruler tren toolbar co trang thai selected)
		SendMessage(g_hWndToolbar,TB_SETSTATE,ID_VIEW_RULER,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_PRESSED,0));
		//  Moi lan zoomin tang ty le zoom len 1
		g_nZoomRate  ++;
		//  Xoa hinh cu
		if (!g_MultiSelect.IsEmpty()) g_MultiSelect.Draw(hdc);
		MarkSelect.clear();
		g_MultiSelect.Set();
		paintListShape.Draw(hdc);
		paintListShape.ClearTracker(hdc);
		//  Thay doi kich thuoc toan bo shape theo ty le g_nZoomRate 
		paintListShape.ZoomObject(g_nZoomRate );  
		//  Ve lai Ruler theo ty le nModeZom
		ruler.ShowRuler(hWnd,g_nZoomRate );	
        //  Ve hinh moi
		paintListShape.Draw(hdc);
		paintListShape.ClearTracker(hdc);
		ReleaseDC(hWnd,hdc);
       // Cap nhat trang thai ZOOM tren thanh status bar
		wsprintf(str,"Zoom: %d00%s", g_nZoomRate,"%");
		g_hWndStatus = GetDlgItem(hWnd, IDC_MAIN_STATUS);
		SendMessage(g_hWndStatus, SB_SETTEXT, 6, (LPARAM)(LPSTR) str);
        if (g_nZoomRate == 2)
            SendMessage(g_hWndToolbar, TB_SETSTATE,ID_ZOOM_ZOOMOUT  ,MAKELPARAM(TBSTATE_ENABLED, 0));
        if (g_nZoomRate == 8)
            SendMessage(g_hWndToolbar, TB_SETSTATE,ID_ZOOM_ZOOMIN  ,MAKELPARAM(TBSTATE_ELLIPSES, 0));  
        break;
	case ID_ZOOM_ZOOMOUT :
		hdc=GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
        //Khi zoom thi bat ruler len(nut bam ruler tren toolbar co trang thai selected)
		SendMessage(g_hWndToolbar,TB_SETSTATE,ID_VIEW_RULER,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_PRESSED,0));
		//  g_nZoomRate  luon lon hon 1
		if (g_nZoomRate  > 1)
		{
			g_nZoomRate  --;
			//  Xoa hinh cu 
			if (!g_MultiSelect.IsEmpty()) g_MultiSelect.Draw(hdc);
			MarkSelect.clear();
			g_MultiSelect.Set();
			paintListShape.Draw(hdc);
			paintListShape.ClearTracker(hdc);
			// Ve lai hinh moi
			paintListShape.ZoomObject(g_nZoomRate );           

			ruler.ShowRuler(hWnd,g_nZoomRate );

			paintListShape.Draw(hdc);
			paintListShape.ClearTracker(hdc);
			ReleaseDC(hWnd,hdc);
		}
		// Cap nhat trang thai ZOOM tren thanh status bar
		wsprintf(str,"Zoom: %d00%s", g_nZoomRate,"%");
		g_hWndStatus = GetDlgItem(hWnd, IDC_MAIN_STATUS);
		SendMessage(g_hWndStatus, SB_SETTEXT, 6, (LPARAM)(LPSTR) str);
        if  (g_nZoomRate == 1)
            SendMessage(g_hWndToolbar, TB_SETSTATE,ID_ZOOM_ZOOMOUT  ,MAKELPARAM(TBSTATE_ELLIPSES, 0));
        if (g_nZoomRate == 7)
            SendMessage(g_hWndToolbar, TB_SETSTATE,ID_ZOOM_ZOOMIN  ,MAKELPARAM(TBSTATE_ENABLED, 0));
       
        break;

	case ID_VIEW_GRID:
		{
			HMENU hViewRuler=GetMenu(hWnd);
			if(g_bEnableGrid)
			{	
				SendMessage(g_hWndToolbar, TB_SETSTATE,ID_VIEW_GRID  ,MAKELPARAM(TBSTATE_ENABLED , 0));
				CheckMenuItem(GetSubMenu(hViewRuler, 1), 5, MF_BYPOSITION | MF_UNCHECKED);
				g_bEnableGrid = 0;				
			}
			else         
			{
				SendMessage(g_hWndToolbar, TB_SETSTATE,ID_VIEW_GRID  ,MAKELPARAM(TBSTATE_ENABLED|TBSTATE_CHECKED , 0));
				CheckMenuItem(GetSubMenu(hViewRuler, 1), 5, MF_BYPOSITION | MF_CHECKED);
				g_bEnableGrid = 1;					
			}
		}
		hdc = GetDC(hWnd);
		paintListShape.ClearTracker(hdc);
		MarkSelect.clear();
		g_MultiSelect.Set();
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;

	case IDM_REFRESH:
		{
			g_nCountShiftDown = 0;
			g_nCountShiftUp = 0;
			g_nCountShiftLeft = 0;
			g_nCountShiftRight = 0;
			hdc = GetDC(hWnd);
			paintListShape.ClearTracker(hdc);
			MarkSelect.clear();
			g_MultiSelect.Set();
			ReleaseDC(hWnd, hdc);
			InvalidateRect(hWnd,NULL,TRUE);
			UpdateWindow(hWnd);
		}
		break;

	case IDD_UNDO:
		hdc = GetDC(hWnd);
		paintListShape.Undo();
		paintListShape.Draw(hdc);
		SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_UNDO  ,MAKELPARAM(0 , 0));
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		ReleaseDC(hWnd, hdc);
		break;

	case IDD_PASTE:
		hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
		if (!g_MultiSelect.IsEmpty()) g_MultiSelect.Draw(hdc);
		MarkSelect.clear();
		g_MultiSelect.Set();
		if (g_nCountPasteTime == 1)	//	neu nhan Ctr+V
		{
			g_ptPaste.x = (g_ptPaste.x + 50);
			g_ptPaste.y += 5;
			paintListShape.PasteObject(hdc, g_ptPaste);
		}

		//	vi co doi tuong text nen can co g_pObject de giai quyet van de cut, copy text
		else
		{
			paintListShape.PasteObject(hdc, g_ptDes);
		}
		ReleaseDC(hWnd, hdc);
		break;

	case IDD_CUT:
		hdc = GetDC(hWnd);
		g_nCountPasteTime = 1;	//	Bat co khoi tao che do paste khong dung chuot phai
		SetROP2(hdc, R2_NOTXORPEN);
		if (g_nModeShape == MS_SELECTED)
			{
				paintListShape.CutObject(hdc);
				if (!g_MultiSelect.IsEmpty()) g_MultiSelect.Draw(hdc);
				MarkSelect.clear();
				g_MultiSelect.Set();
				if (paintListShape.AllowPaste())
					{	
						SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_PASTE  ,MAKELPARAM(TBSTATE_ENABLED , 0));
						SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_UNDO  ,MAKELPARAM(TBSTATE_ENABLED , 0));

					}
				else
					{
						SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_PASTE  ,MAKELPARAM(0 , 0));
					}
			}
		ReleaseDC(hWnd, hdc); 
		break;

	case IDD_COPY: 
		hdc = GetDC(hWnd);
		g_nCountPasteTime = 1;  //	Bat co khoi tao che do paste khong dung chuot phai
		SetROP2(hdc, R2_NOTXORPEN);
		if (g_nModeShape==MS_SELECTED)
		{
			paintListShape.CopyObject();
			if (paintListShape.AllowPaste())
			{	
				SendMessage(g_hWndToolbar, TB_SETSTATE,IDD_PASTE  ,MAKELPARAM(TBSTATE_ENABLED , 0));
			}
			else
			{
				SendMessage(g_hWndToolbar, TB_SETSTATE, IDD_PASTE, MAKELPARAM(0,0));
			}
		}
		ReleaseDC(hWnd, hdc);

		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
} 

void ChangePropertyObj(HDC hdc)
{
	CShapeEX *g_pObjectPrev;
	int i;
	if (MarkSelect.size()> 0)
	for (nControl = 0; nControl < MarkSelect.size(); nControl++)				
		{					
			i = *(MarkSelect.at(nControl));
			g_pObjectPrev = g_pObject = paintListShape.GetObject(i);	
			if (g_bEditPenFlag || g_bFillFlag || g_bColorFlag)
			{
				SetROP2(hdc, R2_NOTXORPEN);
				//	Deleted the previous object
				g_pObject->Draw(hdc);
				g_pObject->DrawSelected(hdc);
				if (g_bEditPenFlag)
				{
					g_pObject->m_dwPenStyle = g_nPenStyle;
					g_pObject->m_nPenWidth = g_nPenWidth;
				}
				if (g_bFillFlag)
				{
					g_pObject->m_bFilled = g_bFilled;
				}
				if (g_bColorFlag)
				{
					g_pObject->m_crBrushColor = g_crColor;
					g_pObject->m_crPenColor = g_crColor;
				}
				// Re-draw the object
				g_pObject->Draw(hdc);
				g_pObject->DrawSelected(hdc);
			}
			
		}

	g_bEditPenFlag = false;
	g_bFillFlag = false;
	g_bColorFlag = false;
}

void CheckAndUncheck(int nPosition)
{
	CheckMenuItem(GetSubMenu(g_hOptionsMenu, 2), nPosition, MF_BYPOSITION | MF_CHECKED);
	for (int i = 0;i<18;i++)
	{
		if (i != nPosition)
			CheckMenuItem(GetSubMenu(g_hOptionsMenu, 2), i, MF_BYPOSITION | MF_UNCHECKED);
	}
}
/************************************************************************
Function Cap nhat lai danh sach doi tuong chon trong truong hop quet chuot
Input: Toa do diem dau va toa do cuoi chuot
Parameter:
+ hdc: Ngu canh de ve
+ ptBegin: Toa do diem dau
+ ptEnd: Toa do diem cuoi
************************************************************************/
void MultiSelect(HDC hdc,POINTS ptBegin,POINTS ptEnd)
{
	bool flag = false;
	POINTS p1, p2;
	paintListShape.ClearTracker(hdc);
	MarkSelect.clear();
	SetROP2(hdc,R2_NOTXORPEN);
	for( size_t i = 0; i < paintListShape.listShape.size(); i++)
	{
		p1 = paintListShape.listShape.at(i)->m_ptBegin;
		p2 = paintListShape.listShape.at(i)->m_ptEnd;
		if (((p1.x - ptBegin.x)*(p1.x - ptEnd.x) < 0)
			&&((p1.y - ptBegin.y)*(p1.y - ptEnd.y) < 0)
			&&((p2.x - ptBegin.x)*(p2.x - ptEnd.x) < 0)
			&&((p2.y - ptBegin.y)*(p2.y - ptEnd.y) < 0))
			flag = true;

		if (flag)
		{	
			temp = new int;
			*temp = i;
			MarkSelect.push_back(temp);
			g_pObject = paintListShape.GetObject(i);		
			g_pObject->DrawSelected(hdc);
			if 	((g_pObject->m_nPattern == MS_TEXT)&&(g_pObject->m_bSelected))
			{						
				g_pObject->WriteText(hdc, RGB(255,255,255));
				//CallGrid(hWnd);
			}
		}
		flag = false;
	}	
}
/***********************************************************************
Function Cap nhat lai toa do hinh bao 
***********************************************************************/
bool UpdateCover()
{	
	g_MultiSelect.Set();
	if (MarkSelect.size() == 1) return false;	
	CShapeEX* g_pObjectemp;	
	//update toa do hinh bao	
	for (size_t i = 0; i < MarkSelect.size(); i++) 
	{
		nControl = *(MarkSelect.at(i));
		g_pObjectemp = paintListShape.GetObject(nControl);
		//--------Update toa do dau-------------
		if (g_pObjectemp->m_ptEnd.x > g_pObjectemp->m_ptBegin.x)
			{if (g_MultiSelect.m_ptBegin.x > g_pObjectemp->m_ptBegin.x)
				g_MultiSelect.m_ptBegin.x = g_pObjectemp->m_ptBegin.x ;
			}
		else
			if (g_MultiSelect.m_ptBegin.x > g_pObjectemp->m_ptEnd.x)
				g_MultiSelect.m_ptBegin.x = g_pObjectemp->m_ptEnd.x ;
		if (g_pObjectemp->m_ptEnd.y > g_pObjectemp->m_ptBegin.y)
			{if (g_MultiSelect.m_ptBegin.y > g_pObjectemp->m_ptBegin.y)
				g_MultiSelect.m_ptBegin.y = g_pObjectemp->m_ptBegin.y;
			}
		else
			if (g_MultiSelect.m_ptBegin.y > g_pObjectemp->m_ptEnd.y)
				g_MultiSelect.m_ptBegin.y = g_pObjectemp->m_ptEnd.y ;
		//----------Update toa do cuoi--------------
		if (g_pObjectemp->m_ptEnd.x > g_pObjectemp->m_ptBegin.x)
			{if (g_MultiSelect.m_ptEnd.x < g_pObjectemp->m_ptEnd.x)
				g_MultiSelect.m_ptEnd.x = g_pObjectemp->m_ptEnd.x ;
			}
		else
			if (g_MultiSelect.m_ptEnd.x < g_pObjectemp->m_ptBegin.x)
				g_MultiSelect.m_ptEnd.x = g_pObjectemp->m_ptBegin.x ;
			
		if (g_pObjectemp->m_ptEnd.y > g_pObjectemp->m_ptBegin.y)
			{if (g_MultiSelect.m_ptEnd.y < g_pObjectemp->m_ptEnd.y)
				g_MultiSelect.m_ptEnd.y = g_pObjectemp->m_ptEnd.y ;
			}
		else 
			if (g_MultiSelect.m_ptEnd.y < g_pObjectemp->m_ptBegin.y)
				g_MultiSelect.m_ptEnd.y = g_pObjectemp->m_ptBegin.y ;
	}
	g_MultiSelect.m_ptBegin.x = g_MultiSelect.m_ptBegin.x - 3*SIZERECTBORDER;
	g_MultiSelect.m_ptBegin.y = g_MultiSelect.m_ptBegin.y - 3*SIZERECTBORDER;
	g_MultiSelect.m_ptEnd.x = g_MultiSelect.m_ptEnd.x + 3*SIZERECTBORDER;
	g_MultiSelect.m_ptEnd.y = g_MultiSelect.m_ptEnd.y + 3*SIZERECTBORDER;
	return true;
} 
 
void CallRuler(HWND hWnd)
{
	CRulerEX ruler;
	if (g_bEnableRuler)
	{
		ruler.Enable();
		ruler.ShowRuler(hWnd,1);
	} 
	else
	{
		ruler.Disable();
		ruler.ShowRuler(hWnd,1);
	} 
}
void CallGrid(HWND hWnd)
{
	CGridEX grid;
	if (g_bEnableGrid)
	{
		grid.Enable();
		grid.ShowGridView(hWnd);
	} 
	else
	{
		grid.Disable();
		grid.ShowGridView(hWnd);
	}
}
/********************************************************************
UpdateListMulS(HDC hdc,int nIndexObjSelect, WPARAM wParam)
Function Cap nhat lai danh sach doi tuong chon 
Parameter:
 + hdc: Ngu canh de ve
 + nIndexObjSelect: vi tri doi tuong chon trong paintListShape
 + wParam: kiem tra trang thai phim duoc giu
*******************************************************************/
void UpdateListMulS(HDC hdc,int nIndexObjSelect, WPARAM wParam)
{
	temp = new int;
	*temp = nIndexObjSelect;
	g_pObject = paintListShape.GetObject(nIndexObjSelect);
	if((g_pObject->m_bSelected)== true)MarkSelect.push_back(temp);
	if ((g_pObject->m_bSelected)==false)
	{
		for (size_t i = 0; i < MarkSelect.size(); i++) 
		{
			nControl = *(MarkSelect.at(i)); 
			if (nControl == nIndexObjSelect)
			{
				MarkSelect.erase(MarkSelect.begin() + i);
				i--;
			}
		}
	}
	if ((MarkSelect.size() == 0)&&(!(wParam & MK_CONTROL)))
	{
		g_pObject->DrawSelected(hdc);
		MarkSelect.push_back(temp);
	}
}