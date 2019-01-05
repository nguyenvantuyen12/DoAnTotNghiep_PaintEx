
#include "stdafx.h"
#include "CGridEX.h"

CGridEX::CGridEX(){
	m_nGridWidth = 20;
	m_nGridHeigh = 20;
	m_pLastPos.x = 0;
	m_pLastPos.y = 0;
	m_bFilled = true;				
	m_nPenWidth = 1;
	m_dwPenStyle = PS_SOLID;
	m_crCursorColor = RGB(255,0,0);
	m_crPenColor = RGB(0,0,0);
}

void CGridEX::Disable(){
	m_nGridWidth = 20;
	m_nGridHeigh = 20;
	m_pLastPos.x = 0;
	m_pLastPos.y = 0;
	m_bFilled = false;				
	m_nPenWidth = 1;
	m_dwPenStyle = PS_SOLID;
	m_crCursorColor = RGB(255,255,255);
	m_crPenColor = RGB(255,255,255);
}

void CGridEX::Enable(){
	m_nGridWidth = 20;
	m_nGridHeigh = 20;
	m_pLastPos.x = 0;
	m_pLastPos.y = 0;
	m_bFilled = false;				
	m_nPenWidth = 1;
	m_dwPenStyle = PS_SOLID;
	m_crCursorColor = RGB(2,2,2);
	m_crPenColor = RGB(222,222,222);
}
bool CGridEX::ShowGridView(HWND hWnd){
	HDC hdc = GetDC(hWnd);

	RECT ClientRect;
	GetClientRect(hWnd,&ClientRect);
	ClientRect.left = ClientRect.left + LEFTRULER + OFFSET;
	ClientRect.top = ClientRect.top + TOPRULER + OFFSET;
	RECT TempRectWidth = ClientRect;
	RECT TempRectHeight = ClientRect;


	int minWidth = TICKERLEVEL2;
	int minHeight = TICKERLEVEL2;

	int countWidth = (TempRectWidth.right - LEFTRULER - OFFSET) / minWidth;
	int countHeight = (TempRectHeight.bottom - TOPRULER -OFFSET) / minHeight;

	HPEN hPen = CreatePen (m_dwPenStyle, m_nPenWidth, m_crPenColor);
	SelectObject (hdc, hPen);

	for (int i = 0; i<= countWidth; i++)
	{		
		TempRectWidth.right = i * minWidth + LEFTRULER + OFFSET/* + 1*/;
		//DrawEdge(hdc,&TempRectWidth,BDR_RAISEDINNER,BF_RIGHT);
		MoveToEx(hdc, TempRectWidth.right, TempRectWidth.top, NULL);
		LineTo(hdc, TempRectWidth.right, TempRectWidth.bottom);
	}

	//HPEN hPen = CreatePen (m_dwPenStyle, m_nPenWidth, m_crPenColor);
	//SelectObject (hdc, hPen);
	for (int i = 0; i<= countHeight; i++)
	{
		TempRectHeight.bottom = i * minHeight + TOPRULER + OFFSET/* + 1*/;
		//DrawEdge(hdc,&TempRectHeight,BDR_RAISEDINNER,BF_BOTTOM);
		MoveToEx(hdc, TempRectHeight.left, TempRectHeight.bottom, NULL);
		LineTo(hdc, TempRectHeight.right, TempRectHeight.bottom);
	}
	DeleteObject(hPen);
	return true;	
}