#include "stdafx.h"
#include "CShapeEX.h"

CShapeEX::CShapeEX()
{
	m_ptBegin.x = m_ptBegin.y = 0;
	m_ptEnd.x = m_ptEnd.y = 0;
	m_nDegree = RD_NONE;
	m_bFilled = false;				
	m_nPenWidth = PW_ONE;
	m_dwPenStyle = PS_SOLID;
	m_crBrushColor = RGB(255,255,255);
	m_crPenColor = RGB(0,0,0);
	m_bSelected = false;
	m_bBoundLine = false;
	m_crTextColor = RGB(0,0,0);
}

HPEN CShapeEX::SetPen(HDC &hdc)
{
	//Create a specified pen and brush. 
	HPEN hPen = CreatePen (m_dwPenStyle, m_nPenWidth, m_crPenColor);
	SelectObject (hdc, hPen);
	//Check m_bFilled flag to fill color circle area.
	if(m_bFilled == true)
	{
		SelectObject (hdc, GetStockObject (DC_BRUSH));
		SetDCBrushColor(hdc, m_crBrushColor);
	}
	else 
		SelectObject (hdc, GetStockObject (NULL_BRUSH));// do not fill the stencil
	return hPen;
}
void CShapeEX::ReleasePen(HPEN hPen)
{
	////	Giai phong but ve
	DeleteObject(hPen);
}
bool CShapeEX::IsEmpty()
{
	if ((m_ptBegin.x == m_ptEnd.x)&&(m_ptBegin.y == m_ptEnd.y))return true;
	return false;
}

bool CShapeEX::Draw(HDC hdc)
{
	return false;
}

bool CShapeEX::Rotate(HDC hdc)
{
	return false;
}

int CShapeEX::IsSelected(POINTS pt)
{	
	return false;
}

bool CShapeEX::Modify(HDC hdc, POINTS ptSrc, POINTS ptDes, int nMode)
{
	return false;
}

void CShapeEX::DrawSelected(HDC hdc)
{
}
//------------------------------------
void CShapeEX::SetStrBuff(TCHAR chInput)
{

}
bool CShapeEX::WriteText(HDC hdc,COLORREF m_crBrushColor)
{
	return false;
}
bool CShapeEX::EraseString(int m_pos)
{
	return false;
}
void CShapeEX::SetFormat(UINT uFormat)
{

}
void CShapeEX::ChoseFont( HWND hWnd )
{

}