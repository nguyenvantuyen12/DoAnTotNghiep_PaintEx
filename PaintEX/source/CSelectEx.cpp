#include "stdafx.h"
#include "CShapeEX.h"
#include "CSelectEx.h"

CSelectEx::CSelectEx()
{	
	m_ptBegin.x = m_ptEnd.x = 0;
	m_ptBegin.y = m_ptEnd.y = 0;
}
void CSelectEx::Set()
{	
	/*Khoi tao toa do mac dinh*/
	m_ptBegin.x =  1200;	
	m_ptBegin.y = 820; 
	m_ptEnd.x = 0;
	m_ptEnd.y = 0;  
	m_bSelected = false; 
	
}
bool CSelectEx::Draw(HDC hdc)
{
	/*Thiet lap but ve va che do phun mau*/
	this->m_bFilled = false;
	HPEN hPen = CreatePen (PS_DASH, 1, RGB(0, 0, 0)); // but mau den, net gach
	SelectObject (hdc, hPen);	
	SelectObject (hdc, GetStockObject (NULL_BRUSH));// do not fill the stencil
	/*Ket thuc thiet lap*/
	Rectangle(hdc, m_ptBegin.x, m_ptBegin.y, m_ptEnd.x, m_ptEnd.y);
	m_bSelected = true; /*Dat co la hinh da duoc ve*/
	//	Giai phong but ve
	DeleteObject(hPen);
	return true;
}
/******************************************************************************
* CLineEX::IsSelected(POINTS pt)
* Description : Tra ve gia tri cua tracker dang chua diem pt truyen vao
*****************************************************************************/
int CSelectEx::IsSelected(POINTS pt)							
{
	bool flag = false;
	POINTS p1, p2;	
	p1 = m_ptBegin;
	p2 = m_ptEnd;
	if (((p1.x - pt.x)*(p2.x - pt.x) < 0)			
		&&((p1.y - pt.y)*(p2.y - pt.y) < 0))
		flag = true;		
	return	flag;	
}
/******************************************************************************
* bool CLineEX::Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd, int nMode)
* Description : Ham thuc hien Move nhieu doi tuong dua vao cac tham so dau vao
*****************************************************************************/

bool CSelectEx::Modify(HDC hdc, POINTS ptSrc, POINTS ptDes, int nMode)	
{
	POINTS ptTemp;
	Draw(hdc);	
	ptTemp.x = m_ptBegin.x + ptDes.x - ptSrc.x;
	ptTemp.y = m_ptBegin.y + ptDes.y - ptSrc.y;
	// Quay 90 do
	if ((ptTemp.x >= LEFTOFFSET) && (ptTemp.y >= TOPOFFSET))
	{
		//------- Gan toa do sau khi move -----------
		m_ptBegin.x = m_ptBegin.x + ptDes.x - ptSrc.x;
		m_ptBegin.y = m_ptBegin.y + ptDes.y - ptSrc.y;
		m_ptEnd.x = m_ptEnd.x + ptDes.x - ptSrc.x;
		m_ptEnd.y = m_ptEnd.y + ptDes.y - ptSrc.y;	
		Draw(hdc);
		return 1;
	}
	Draw(hdc);
	return 0;
}

bool CSelectEx::IsEmpty()
{
	if ((m_ptBegin.x > m_ptEnd.x)&&(m_ptBegin.y > m_ptEnd.y))return true;
	return false;
}