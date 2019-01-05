#include "StdAfx.h"
#include "CTextEx.h"
#include "CShapeEX.h"
#include <CommDlg.h>
#include <commctrl.h>
//--------------------------------------------------------------------
//Macro define
#define DEFAULT_BKMODE            TRANSPARENT
#define DEFAULT_TEXT_COLOR        RGB(0,0,0)
#define DEFAULT_BK_COLOR		  RGB(255,255,255)
#define DEFAULT_FORMAT            (DT_LEFT|DT_WORDBREAK|DT_EDITCONTROL|DT_END_ELLIPSIS|DT_EXPANDTABS)
#define DEFAULT_TEXT_HEIGHT        0
//--------------------------------------------------------------------
CTextEx::CTextEx()
{
	m_nPattern		= MS_TEXT;
	m_crTextColor	= DEFAULT_TEXT_COLOR;
	m_strBuffer		= ' ';
	m_width			= 7;
	m_lfFontText.lfHeight = 0;
	m_lfFontText.lfWidth = 7;
	m_lfFontText.lfEscapement = 0;
	m_lfFontText.lfOrientation = 0;
	m_lfFontText.lfWeight = FW_NORMAL;
	m_lfFontText.lfItalic = FALSE;
	m_lfFontText.lfUnderline = FALSE;
	m_lfFontText.lfStrikeOut = FALSE;
	m_lfFontText.lfCharSet = ANSI_CHARSET;
	m_lfFontText.lfOutPrecision = OUT_DEFAULT_PRECIS; 
	m_lfFontText.lfClipPrecision = CLIP_DEFAULT_PRECIS; 
	m_lfFontText.lfQuality = DEFAULT_QUALITY; 
	m_lfFontText.lfPitchAndFamily = DEFAULT_PITCH|FF_ROMAN; 
	m_lfFontText.lfFaceName[LF_FACESIZE] = TCHAR("Times New Roman"); 
	m_hfFont = CreateFontIndirect(&m_lfFontText);
}
/******************************************************************************
* void CTextEx::SetStrBuff(TCHAR chInput)
* Description : Ham thuc hien day 1 ky tu vao chInput khi ta nhap ky tu tu ban phim
*****************************************************************************/
void CTextEx::SetStrBuff(TCHAR chInput)
{ 
	m_strBuffer.push_back(chInput);
}
/******************************************************************************
* void CTextEx::SetFormat()
* Description : thiet lap dinh dang text viet ra man hinh
*****************************************************************************/
void CTextEx::SetFormat(UINT uFormat)
{
	m_uFormat = uFormat;
}
/******************************************************************************
* void CTextEx::GetText()
* Description : Ham thuc hien day 1 ky tu vao chInput khi ta nhap ky tu tu ban phim
*****************************************************************************/
TCHAR* CTextEx::GetText()
{	
	TCHAR *pchTmp;
	pchTmp = new TCHAR[m_strBuffer.size()];
	copy(m_strBuffer.begin(), m_strBuffer.end(), pchTmp);
	return pchTmp;
}
/******************************************************************************
* bool CTextEx::EraseString()
* Description : Ham tra ve true/false neu thao tac xoa 1 ky tu trong xau duoc thuc 
*				hien
*****************************************************************************/
bool CTextEx::EraseString(int nPos)
{
	if(m_strBuffer.size()>1)	//	neu chuoi khong phai la rong
	m_strBuffer.erase(m_strBuffer.end()- nPos);
	return true;
}

/******************************************************************************
* bool CTextEx::Draw(HDC hdc)
* Description : Ham tra ve true/false neu thao tac ve hinh CN bao duoc thuc hien
*****************************************************************************/
bool CTextEx::Draw(HDC hdc)

{	
// 	m_nPenWidth = 1;
// 	m_dwPenStyle = PS_DOT;
// 	m_bFilled = false;
// 	m_crPenColor = RGB(0, 0, 0);
// 	HPEN hPen = SetPen(hdc);
// 	SetCoordinate();	//	dat lai toa do begin, end cho duong bao text
// 	//	Ve duong bao cho text
// 	Rectangle(hdc, m_ptBegin.x, m_ptBegin.y, m_ptEnd.x, m_ptEnd.y);
// 	ReleasePen(hPen);
// 	m_bBoundLine = !m_bBoundLine;
	return true;

}
/******************************************************************************
* ++
* void CTextEx::SetFont()
* Description : Dat gia tri cho font chu cho text duoc viet ra
*
* Parameters :	hdc
*
* Global Variables
* Accessed : none
* Modified : none
*
* Return values : none
*
* Modifications : Pham Van Thuan Creates 09.11.2011
				: 
				: 
*				
* Function first created
* CR/PN# - Project
* Description
*
* --
*****************************************************************************/
void CTextEx::SetFont()
{
	if ((m_nDegree == RD_NONE)||(m_nDegree == RD_ONE_HUNDRED_AND_EIGHTY))
	{
		m_lfFontText.lfEscapement = 0;
		m_lfFontText.lfOrientation = 0;
	}
	if (m_nDegree == RD_NINETY)
	{
		m_lfFontText.lfEscapement = 900;
		m_lfFontText.lfOrientation = 900;
	}
	if (m_nDegree == RD_TWO_HUNDRED_AND_SEVENTY)
	{
		m_lfFontText.lfEscapement = 2700;
		m_lfFontText.lfOrientation = 2700;
	}
	m_hfFont = CreateFontIndirect(&m_lfFontText);
}
/***************************************************************
 * Description  : Write Text from pBuffer to HCD				  
*****/
bool CTextEx::WriteText(HDC hdc,COLORREF m_crTextColor)
{
	SetCoordinate();
	//	Duong bao de ve text
	RECT rectBorder;
	//	chon font
	if ((m_nDegree == RD_NONE)||(m_nDegree == RD_ONE_HUNDRED_AND_EIGHTY))
	{		
		SetFont();
		rectBorder.left   = m_ptBegin.x + 5;
		rectBorder.top    = m_ptBegin.y + 5;
		rectBorder.right  = m_ptEnd.x;
		rectBorder.bottom = m_ptEnd.y;
	}
	if (m_nDegree == RD_NINETY)
	{
		SetFont();
		rectBorder.left   = m_ptBegin.x + 5;
		rectBorder.top    = m_ptEnd.y - 5;
		rectBorder.right = m_ptEnd.x;
		rectBorder.bottom = m_ptBegin.y;
	}	
	if (m_nDegree == RD_TWO_HUNDRED_AND_SEVENTY)
	{
		SetFont();
		rectBorder.left   = m_ptEnd.x - 5;
		rectBorder.top    = m_ptBegin.y + 5;
		rectBorder.right = m_ptBegin.x;
		rectBorder.bottom = m_ptEnd.y;
	}
	HFONT hfOld = (HFONT)SelectObject(hdc, m_hfFont);
	TCHAR *pchTmp;	//	con tro kieu TCHAR
 	pchTmp = new TCHAR[m_strBuffer.size() + 1];				//	convert String to Tchar
 	pchTmp[m_strBuffer.size()] = '\0';						//	Ky tu cuoi cung la \0 (string)
	copy(m_strBuffer.begin() + 1, m_strBuffer.end(), pchTmp); 
	SetTextColor(hdc, m_crTextColor);						//	Dat mau cho text
	if ((m_nDegree == RD_NONE)||(m_nDegree == RD_ONE_HUNDRED_AND_EIGHTY))
	{
		TextOut(hdc, rectBorder.left, rectBorder.top, pchTmp, m_strBuffer.size() - 1);		
		if (SHORT(m_strBuffer.size()) > (SHORT)((m_ptEnd.x - m_ptBegin.x)/m_width - 5))
		{
			SetROP2(hdc, R2_NOTXORPEN);
			//   Draw(hdc); //  xoa duong bao cu
			DrawSelected(hdc);
			m_ptEnd.x = m_ptBegin.x + (SHORT)(m_width*(4.99 + m_strBuffer.size()));
			//   Draw(hdc);
			DrawSelected(hdc);
		}
	}
	else
	{
		if(m_nDegree == RD_NINETY)
		{	
			TextOut(hdc, rectBorder.left, rectBorder.top, pchTmp, m_strBuffer.size() - 1);		
			if (SHORT(m_strBuffer.size()) >= (SHORT)((m_ptEnd.y - m_ptBegin.y)/m_width - 5))
			{
				SetROP2(hdc, R2_NOTXORPEN);
				//   Draw(hdc); //  xoa duong bao cu
				DrawSelected(hdc);
				m_ptBegin.y = m_ptEnd.y - (SHORT)(m_width*(4.99 + m_strBuffer.size()));
				//   Draw(hdc);
				DrawSelected(hdc);
			}
		}
		else
		{
			TextOut(hdc, rectBorder.left, rectBorder.top, pchTmp, m_strBuffer.size() - 2);
			if (SHORT(m_strBuffer.size()) >= (SHORT)((m_ptEnd.y - m_ptBegin.y)/m_width - 5))
			{
				SetROP2(hdc, R2_NOTXORPEN);
				//   Draw(hdc); //  xoa duong bao cu
				DrawSelected(hdc);
				m_ptEnd.y = m_ptBegin.y + (SHORT)(m_width*(4.99 + m_strBuffer.size()));
				//   Draw(hdc);
				DrawSelected(hdc);
			}
		}
	}
	delete pchTmp;
	return true;
}
/******************************************************************************
* bool CTextEx::Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd)
* Description : Ham thuc hien viec Resize va Move HCN dua vao cac tham so dau vao
*****************************************************************************/
bool CTextEx::Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd, int nMode)
{	
	switch(nMode)
	{
	case MR_DRAG:	
		//   Draw(hdc);	//	xoa duong bao
		DrawSelected(hdc);	//	xoa tracker
		Move(ptSrc, ptEnd);	//	update toa do
		//   Draw(hdc);			//	ve duong bao moi
		DrawSelected(hdc);	//	ve tracker moi
		break;
	case MR_NONE:
		break;
	default:	
		//   Draw(hdc);			//	xoa duong bao
		DrawSelected(hdc);	//  xoa tracker
		Resize(ptEnd, nMode);//	 update toa do
		//   Draw(hdc);			//	ve duong bao moi
		DrawSelected(hdc);	//	ve tracker moi
		break;
	}
	return true;
}
/******************************************************************************
* int CTextEx::IsSelectedTracker(POINTS pt)
* Description : Tra ve gia tri cua tracker dang chua diem pt truyen vao
*****************************************************************************/
void CTextEx::SetCoordinate()
{
	POINTS ptTempBegin, ptTempEnd;
	ptTempBegin = m_ptBegin;
	ptTempEnd = m_ptEnd;
	//  Truong hop huong keo thuoc goc phan tu thu I
	if ((m_ptBegin.x < m_ptEnd.x) && 
		(m_ptBegin.y > m_ptEnd.y)) 
	{
		m_ptBegin.x = ptTempBegin.x;
		m_ptBegin.y = ptTempEnd.y;
		m_ptEnd.x = ptTempEnd.x;
		m_ptEnd.y = ptTempBegin.y;
	}
	//  Truong hop huong keo thuoc goc phan tu thu IV
	if ((m_ptBegin.x > m_ptEnd.x) && 
		(m_ptBegin.y > m_ptEnd.y)) 
	{
		m_ptBegin.x = ptTempEnd.x;
		m_ptBegin.y = ptTempEnd.y;
		m_ptEnd.x = ptTempBegin.x;
		m_ptEnd.y = ptTempBegin.y;
	}
	//  Truong hop huong keo thuoc goc phan tu thu III
	if ((m_ptBegin.x > m_ptEnd.x) && 
		(m_ptBegin.y < m_ptEnd.y)) 
	{ 
		m_ptBegin.x = ptTempEnd.x;
		m_ptBegin.y = ptTempBegin.y;
		m_ptEnd.x = ptTempBegin.x;
		m_ptEnd.y = ptTempEnd.y;
	}
	//  Truong hop huong keo thuoc goc phan tu thu II
	if ((m_ptBegin.x < m_ptEnd.x) && 
		(m_ptBegin.y < m_ptEnd.y)) 
	{
		m_ptBegin.x = ptTempBegin.x;
		m_ptBegin.y = ptTempBegin.y;
		m_ptEnd.x = ptTempEnd.x;
		m_ptEnd.y = ptTempEnd.y;
	}
}
int CTextEx::IsSelected(POINTS pt)
{
	POINTS arrPoint[8];
	RECT arrRectTracker[8];
	RECT rcRect;
	// setup the rcRect rectangle
	rcRect.left		= m_ptBegin.x	- m_nPenWidth - SIZERECTBORDER;
	rcRect.top		= m_ptBegin.y	- m_nPenWidth -  SIZERECTBORDER;
	rcRect.right	= m_ptEnd.x		+ m_nPenWidth + SIZERECTBORDER;
	rcRect.bottom	= m_ptEnd.y		+ m_nPenWidth + SIZERECTBORDER;
	// set value for 8 positions to define the tracker
	arrPoint[0].x = m_ptBegin.x;
	arrPoint[0].y = m_ptBegin.y;
	arrPoint[1].x = (m_ptBegin.x + m_ptEnd.x) / 2;
	arrPoint[1].y = m_ptBegin.y;
	arrPoint[2].x = m_ptEnd.x;
	arrPoint[2].y = m_ptBegin.y;
	arrPoint[3].x = m_ptEnd.x;
	arrPoint[3].y = (m_ptBegin.y + m_ptEnd.y) / 2;
	arrPoint[4].x = m_ptEnd.x;
	arrPoint[4].y = m_ptEnd.y;
	arrPoint[5].x = (m_ptBegin.x + m_ptEnd.x) / 2;
	arrPoint[5].y = m_ptEnd.y;
	arrPoint[6].x = m_ptBegin.x;
	arrPoint[6].y = m_ptEnd.y;
	arrPoint[7].x = m_ptBegin.x;
	arrPoint[7].y = (m_ptBegin.y + m_ptEnd.y) / 2;
	// setup 8 rectangle trackers
	for (int i = 0; i < 8; i++)
	{
		arrRectTracker[i].left		= arrPoint[i].x - m_nPenWidth - SIZERECTBORDER;
		arrRectTracker[i].top		= arrPoint[i].y - m_nPenWidth - SIZERECTBORDER;
		arrRectTracker[i].right		= arrPoint[i].x + m_nPenWidth + SIZERECTBORDER;
		arrRectTracker[i].bottom	= arrPoint[i].y + m_nPenWidth + SIZERECTBORDER;
	}
	// Convert POINTS to POINT
	POINT ptPoint;
	ptPoint.x = (LONG) pt.x;
	ptPoint.y = (LONG) pt.y;
	// the main of subprogram
	if(PtInRect(&rcRect, ptPoint))
	{
		if(PtInRect(&arrRectTracker[0], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
			return MR_TOPLEFT;
		}
		else if(PtInRect(&arrRectTracker[1], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
			return MR_TOPMIDDLE;
		}
		else if(PtInRect(&arrRectTracker[2], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW));
			return MR_TOPRIGHT;
		}
		else if(PtInRect(&arrRectTracker[3], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
			return MR_RIGHTMIDDLE;
		}
		else if(PtInRect(&arrRectTracker[4], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
			return MR_BOTTOMRIGHT;
		}
		else if(PtInRect(&arrRectTracker[5], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
			return MR_BOTTOMMIDDLE;
		}
		else if(PtInRect(&arrRectTracker[6], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW));
			return MR_BOTTOMLEFT;
		}
		else if(PtInRect(&arrRectTracker[7], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
			return MR_LEFTMIDDLE;
		}
		else
		{
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));
			return MR_DRAG;
		}
	}
	else
	{
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		return MR_NONE;
	}

}

/******************************************************************************
* void CRectangleEx::Resize(POINTS pt, int nMode)
* Description : Ham thuc hien chuc nang Resize 1 HCN dua vao chuc nang truyen vao tu tham so dau vao va toa do hien tai
*****************************************************************************/
void CTextEx::Resize(POINTS pt, int nMode)
{
	switch (nMode)
	{
		//	Truong hop Tracker o vi tri TOPLEFT
	case MR_TOPLEFT:
		//	Kiem tra gioi han cua HCN nho nhat
		if (((m_ptEnd.x - pt.x) >= LIMIT)
			&&((m_ptEnd.y - pt.y) >= LIMIT))
		{
			m_ptBegin.x = pt.x;
			m_ptBegin.y = pt.y;
		}
		break;
		//	Truong hop Tracker o vi tri TOPMIDDLE
	case MR_TOPMIDDLE:
		//	Kiem tra gioi han cua HCN nho nhat
		if ((m_ptEnd.y - pt.y) >= LIMIT)
		{
			m_ptBegin.y = pt.y;
		}
		break;
		//	Truong hop Tracker o vi tri TOPRIGHT
	case MR_TOPRIGHT:
		//	Kiem tra gioi han cua HCN nho nhat
		if (((pt.x - m_ptBegin.x) >= LIMIT)
			&&((m_ptEnd.y - pt.y) >= LIMIT))
		{
			m_ptEnd.x = pt.x;
			m_ptBegin.y = pt.y;
		}
		break;
		//	Truong hop Tracker o vi tri RIGHTMIDDLE
	case MR_RIGHTMIDDLE:
		//	Kiem tra gioi han cua HCN nho nhat
		if ((pt.x - m_ptBegin.x) > LIMIT)
		{
			m_ptEnd.x = pt.x;
		}
		break;
		//	Truong hop Tracker o vi tri BOTTOMRIGHT
	case MR_BOTTOMRIGHT:
		//	Kiem tra gioi han cua HCN nho nhat
		if (((pt.x - m_ptBegin.x) >= LIMIT)
			&&((pt.y - m_ptBegin.y) >= LIMIT))
		{
			m_ptEnd.x = pt.x;
			m_ptEnd.y = pt.y;
		}
		break;
		//	Truong hop Tracker o vi tri BOTTOMMIDDLE
	case MR_BOTTOMMIDDLE:
		//	Kiem tra gioi han cua HCN nho nhat
		if ((pt.y - m_ptBegin.y) >= LIMIT)
		{
			m_ptEnd.y = pt.y;
		}
		break;
		//	Truong hop Tracker o vi tri BOTTOMLEFT
	case MR_BOTTOMLEFT:
		//	Kiem tra gioi han cua HCN nho nhat
		if (((m_ptEnd.x - pt.x) >= LIMIT)
			&&((pt.y - m_ptBegin.y) >= LIMIT))
		{
			m_ptBegin.x = pt.x;
			m_ptEnd.y = pt.y;
		}
		break;
		//	Truong hop Tracker o vi tri LEFTMIDDLE
	case MR_LEFTMIDDLE:
		//	Kiem tra gioi han cua HCN nho nhat
		if ((m_ptEnd.x - pt.x) >= LIMIT)
		{
			m_ptBegin.x = pt.x;
		}
		break;
	default:
		break;
	}
}
bool CTextEx::Move(POINTS ptSrc, POINTS ptDes)
{
	POINTS ptTemp;
	ptTemp.x = m_ptBegin.x + ptDes.x - ptSrc.x;
	ptTemp.y = m_ptBegin.y + ptDes.y - ptSrc.y;
	
	if ((ptTemp.x - SIZERECTBORDER>= LEFTOFFSET) 
		&& (ptTemp.y - SIZERECTBORDER>= TOPOFFSET))
	{
		//------- Gan toa do sau khi move -----------
		m_ptBegin.x = m_ptBegin.x + ptDes.x - ptSrc.x;
		m_ptBegin.y = m_ptBegin.y + ptDes.y - ptSrc.y;
		m_ptEnd.x = m_ptEnd.x + ptDes.x - ptSrc.x;
		m_ptEnd.y = m_ptEnd.y + ptDes.y - ptSrc.y;	
	}
	return true;
}

/******************************************************************************
* void CTextEx::DrawSelected(HDC hdc)
* Description : Ve 8 trackers cho HCN bao khi HCN bao duoc selected
*****************************************************************************/
void CTextEx::DrawSelected(HDC hdc)		//	Ve cac tracker (chi ve tracker thoi)
{
	m_nPenWidth = 1;
	m_dwPenStyle = PS_DOT;
	m_bFilled = false;
	m_crPenColor = RGB(0, 0, 0);
	HPEN hPen = SetPen(hdc);
	SetCoordinate();	//	dat lai toa do begin, end cho duong bao text
	//	Ve duong bao cho text
	Rectangle(hdc, m_ptBegin.x, m_ptBegin.y, m_ptEnd.x, m_ptEnd.y);
	ReleasePen(hPen);
	m_bBoundLine = !m_bBoundLine;

	POINTS arrPoint[8];
	// set value for 8 positions to define the tracker
	arrPoint[0].x = m_ptBegin.x;
	arrPoint[0].y = m_ptBegin.y;
	arrPoint[1].x =(m_ptBegin.x + m_ptEnd.x) / 2;
	arrPoint[1].y = m_ptBegin.y;
	arrPoint[2].x = m_ptEnd.x;
	arrPoint[2].y = m_ptBegin.y;
	arrPoint[3].x = m_ptEnd.x;
	arrPoint[3].y =(m_ptBegin.y + m_ptEnd.y) / 2;
	arrPoint[4].x = m_ptEnd.x;
	arrPoint[4].y = m_ptEnd.y;
	arrPoint[5].x = (m_ptBegin.x + m_ptEnd.x) / 2;
	arrPoint[5].y = m_ptEnd.y;
	arrPoint[6].x = m_ptBegin.x;
	arrPoint[6].y = m_ptEnd.y;
	arrPoint[7].x = m_ptBegin.x;
	arrPoint[7].y = (m_ptBegin.y + m_ptEnd.y) / 2;
	// setup pen and draw 8 trackers rectangle
	/*HPEN */hPen = CreatePen (PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPenOld = (HPEN)SelectObject (hdc, hPen);
	HGDIOBJ hObjOld;
	hObjOld = SelectObject (hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(0, 0, 0));
	for(int nCount =0; nCount < 8; nCount++)
		Rectangle
		(
		hdc, 
		arrPoint[nCount].x - m_nPenWidth - 1, 
		arrPoint[nCount].y - m_nPenWidth - 1, 
		arrPoint[nCount].x + m_nPenWidth + 1, 
		arrPoint[nCount].y + m_nPenWidth + 1
		);
	//	Giai phong but ve
	SelectObject(hdc,hPenOld);
	DeleteObject(hPen);
	DeleteObject(hPenOld);
	DeleteObject(hObjOld);
	m_bSelected = !m_bSelected;
}
/******************************************************************************
* void CTextEx::ChoseFont( HWND hWnd )
* Description : Tao Dialog cho phep thay doi FONT chu cho TEXT
*****************************************************************************/
void CTextEx::ChoseFont( HWND hWnd )
{	
	static CHOOSEFONT cfTemp;
	HDC hdc;
	RECT rectBorder;
	if( m_tfFontLoaded == TRUE )
	{
		cfTemp.Flags	|= CF_INITTOLOGFONTSTRUCT;
		cfTemp.rgbColors = m_crTextColor;
	}
	else
	{
		cfTemp.lStructSize			= sizeof( CHOOSEFONT );
		cfTemp.hwndOwner			= hWnd;
		cfTemp.hDC					= 0;	
		cfTemp.lpLogFont			= &m_lfFontText;
		cfTemp.Flags				= CF_EFFECTS | CF_FORCEFONTEXIST | CF_SCREENFONTS|CF_LIMITSIZE;		
		cfTemp.rgbColors			= m_crTextColor;
		cfTemp.lCustData			= 0L;
		cfTemp.lpfnHook             = NULL;
		cfTemp.lpTemplateName		= NULL;
		cfTemp.hInstance			= 0;
		cfTemp.lpszStyle            = NULL;
		cfTemp.nFontType            = SCREEN_FONTTYPE;
		cfTemp.nSizeMin				= 8;
		cfTemp.nSizeMax				= 72;
	}
	if( ChooseFont( &cfTemp ) == TRUE )
	{
		if( m_tfFontLoaded == TRUE )
			DeleteObject( m_hfFont );
		m_crTextColor = cfTemp.rgbColors;
		m_tfFontLoaded = TRUE;
		hdc = GetDC(hWnd);
		WriteText(hdc, m_crTextColor);
		ReleaseDC(hWnd, hdc);	
	}
	InvalidateRect( hWnd, &rectBorder, TRUE );	
	UpdateWindow(hWnd);
}
/******************************************************************************
* bool CTextEx::Rotate(HDC hdc)
* Description : Ham thuc hien viec quay HCN, quay TEXT
*****************************************************************************/
bool CTextEx::Rotate(HDC hdc)
{
	POINTS ptA1, ptB1;
	ptA1.x = (m_ptBegin.x + m_ptEnd.x)/2 - (m_ptEnd.y - m_ptBegin.y)/2;
	ptA1.y = (m_ptBegin.y + m_ptEnd.y)/2 - (m_ptEnd.x - m_ptBegin.x)/2;
	ptB1.x = (m_ptBegin.x + m_ptEnd.x)/2 + (m_ptEnd.y - m_ptBegin.y)/2;
	ptB1.y = (m_ptBegin.y + m_ptEnd.y)/2 + (m_ptEnd.x - m_ptBegin.x)/2;
	if ((ptA1.x >= LEFTOFFSET + m_nPenWidth + SIZERECTBORDER)
		&&(ptA1.y >= TOPOFFSET + m_nPenWidth + SIZERECTBORDER))
	{	
		//	this->Draw(hdc);					//  xoa hinh ve cu
		this->DrawSelected(hdc);			//  xoa cac tracker hinh ve cu
		WriteText(hdc, RGB(255,255,255));
		m_nDegree = m_nDegree + RD_NINETY;	//  quay toa di 90 do(update toa do moi)
		if (m_nDegree == 4)					//	neu m_nDegree =4 nghia la hinh da quay 360 do thi vong quay tiep theo reset ve 0
		{
			m_nDegree = 0;
		}
		//	update toa do moi cho doi tuong
		m_ptBegin = ptA1;
		m_ptEnd = ptB1;
		//	this->Draw(hdc);					//  ve hinh moi
		this->DrawSelected(hdc);			//  ve cac tracker cho hinh moi
		WriteText(hdc, m_crTextColor);
		return true;
	}
	else
		return true;
}