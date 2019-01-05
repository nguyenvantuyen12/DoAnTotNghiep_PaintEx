#include "stdafx.h"
#include "CRectangleEx.h"
#include "CShapeEX.h"

/******************************************************************************
* Method name : CRectangleEx::CRectangleEx()
* Description : Ham tao co class CRectangle. Thuc hien khoi tao cac thuoc tinh cho lop CRectangle
*****************************************************************************/
CRectangleEx::CRectangleEx()
{	
	m_nPattern = MS_RECT;
}
/******************************************************************************
* void CRectangleEx::Setcoordinate()
* Description : Ham set lai toa do cua HCN truoc khi thuc hien ve
*****************************************************************************/
void CRectangleEx::SetCoordinate()
{
	POINTS ptTempBegin, ptTempEnd;
	ptTempBegin = m_ptBegin;
	ptTempEnd = m_ptEnd;
	// Truong hop huong keo thuoc goc phan tu thu I
	if ((m_ptBegin.x < m_ptEnd.x) && 
		(m_ptBegin.y > m_ptEnd.y)) 
	{
		m_ptBegin.x = ptTempBegin.x;
		m_ptBegin.y = ptTempEnd.y;
		m_ptEnd.x = ptTempEnd.x;
		m_ptEnd.y = ptTempBegin.y;
	}
	// Truong hop huong keo thuoc goc phan tu thu IV
	else if ((m_ptBegin.x > m_ptEnd.x) && 
		(m_ptBegin.y > m_ptEnd.y)) 
	{
		m_ptBegin.x = ptTempEnd.x;
		m_ptBegin.y = ptTempEnd.y;
		m_ptEnd.x = ptTempBegin.x;
		m_ptEnd.y = ptTempBegin.y;
	}
	// Truong hop huong keo thuoc goc phan tu thu III
	else if ((m_ptBegin.x > m_ptEnd.x) && 
		(m_ptBegin.y < m_ptEnd.y)) 
	{ 
		m_ptBegin.x = ptTempEnd.x;
		m_ptBegin.y = ptTempBegin.y;
		m_ptEnd.x = ptTempBegin.x;
		m_ptEnd.y = ptTempEnd.y;
	}
	// Truong hop huong keo thuoc goc phan tu thu II
	else 
	{
		m_ptBegin.x = ptTempBegin.x;
		m_ptBegin.y = ptTempBegin.y;
		m_ptEnd.x = ptTempEnd.x;
		m_ptEnd.y = ptTempEnd.y;
	}
}
/******************************************************************************
* bool CRectangleEx::Draw(HDC hdc)
* Description : Ham ve HCN theo toa do Begin va End.
*****************************************************************************/
bool CRectangleEx::Draw(HDC hdc)
{
	//	Set lai but ve
	HPEN hPen = SetPen(hdc);
	
	//	Set lai toa do de tranh truong hop HCN bi loi
	SetCoordinate();
	//	Draw the rectangle
	Rectangle(hdc, m_ptBegin.x, m_ptBegin.y, m_ptEnd.x, m_ptEnd.y);
	//	Giai phong but ve
	ReleasePen(hPen);
	return true;
}
/******************************************************************************
* void CRectangleEx::DrawSelected(HDC hdc)
* Description : Ve 8 trackers cho HCN khi HCN duoc selected
*****************************************************************************/
void CRectangleEx::DrawSelected(HDC hdc)
{
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
	HPEN hPen = CreatePen (PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPenOld = (HPEN)SelectObject (hdc, hPen);
	HGDIOBJ hObjOld;
	hObjOld = SelectObject (hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(0, 0, 0));
	for(int nCount =0; nCount < 8; nCount++)
		Rectangle(hdc, arrPoint[nCount].x - m_nPenWidth - SIZERECTBORDER, arrPoint[nCount].y - m_nPenWidth - SIZERECTBORDER, arrPoint[nCount].x + m_nPenWidth + SIZERECTBORDER, arrPoint[nCount].y + m_nPenWidth + SIZERECTBORDER);
	//	Giai phong but ve
	SelectObject(hdc,hPenOld);
	DeleteObject(hPen);
	DeleteObject(hPenOld);
	DeleteObject(hObjOld);
	m_bSelected = !m_bSelected;
}
/******************************************************************************
* int CRectangleEx::IsSelected(POINTS pt)
* Description : Tra ve gia tri cua tracker dang chua diem pt truyen vao
*****************************************************************************/
int CRectangleEx::IsSelected(POINTS pt)
{
	POINTS arrPoint[8];
	RECT arrRectTracker[8];
	RECT rcRect;
	// setup the rcRect rectangle
	rcRect.left = m_ptBegin.x - m_nPenWidth - SIZERECTBORDER;
	rcRect.top = m_ptBegin.y - m_nPenWidth -  SIZERECTBORDER;
	rcRect.right = m_ptEnd.x + m_nPenWidth + SIZERECTBORDER;
	rcRect.bottom = m_ptEnd.y + m_nPenWidth + SIZERECTBORDER;
	// Set value for 8 positions to define the tracker
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
		arrRectTracker[i].left = arrPoint[i].x - m_nPenWidth - SIZERECTBORDER;
		arrRectTracker[i].top = arrPoint[i].y - m_nPenWidth - SIZERECTBORDER;
		arrRectTracker[i].right = arrPoint[i].x + m_nPenWidth + SIZERECTBORDER;
		arrRectTracker[i].bottom = arrPoint[i].y + m_nPenWidth + SIZERECTBORDER;
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
* void CRectangleEx::Move(POINTS ptSrc, POINTS ptDes)
* Description : Ham thuc hien viec Move 1 doi tuong HCN dua vao tham so dau vao
*****************************************************************************/
void CRectangleEx::Move(POINTS ptSrc, POINTS ptDes)
{
	POINTS ptTemp;
	ptTemp.x = m_ptBegin.x + ptDes.x - ptSrc.x;
	ptTemp.y = m_ptBegin.y + ptDes.y - ptSrc.y;
	if ((ptTemp.x >= LEFTOFFSET + SIZERECTBORDER + m_nPenWidth) && (ptTemp.y >= TOPOFFSET + SIZERECTBORDER + m_nPenWidth))
	{
	//------- Gan toa do sau khi move -----------
	m_ptBegin.x = m_ptBegin.x + ptDes.x - ptSrc.x;
	m_ptBegin.y = m_ptBegin.y + ptDes.y - ptSrc.y;
	m_ptEnd.x = m_ptEnd.x + ptDes.x - ptSrc.x;
	m_ptEnd.y = m_ptEnd.y + ptDes.y - ptSrc.y;	
	}
	
}
/******************************************************************************
* void CRectangleEx::Resize(POINTS pt, int nMode)
* Description : Ham thuc hien chuc nang Resize 1 HCN dua vao chuc nang truyen vao tu tham so dau vao va toa do hien tai
*****************************************************************************/
void CRectangleEx::Resize(POINTS pt, int nMode)
{
	if ((pt.x >= LEFTOFFSET + SIZERECTBORDER + m_nPenWidth) && (pt.y >= TOPOFFSET + SIZERECTBORDER + m_nPenWidth))
	{
		switch (nMode)
		{
			//	Truong hop Tracker o vi tri TOPLEFT
		case MR_TOPLEFT:
			//	Kiem tra gioi han cua HCN nho nhat
			if (((m_ptEnd.x - pt.x) >= LIMIT)&&((m_ptEnd.y - pt.y) >= LIMIT))
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
			if (((pt.x - m_ptBegin.x) >= LIMIT)&&((m_ptEnd.y - pt.y) >= LIMIT))
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
			if (((pt.x - m_ptBegin.x) >= LIMIT)&&((pt.y - m_ptBegin.y) >= LIMIT))
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
			if (((m_ptEnd.x - pt.x) >= LIMIT)&&((pt.y - m_ptBegin.y) >= LIMIT))
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
	
}
/******************************************************************************
* bool CRectangleEx::Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd, int nMode)
* Description : Ham thuc hien viec Resize va Move HCN dua vao cac tham so dau vao
*****************************************************************************/
bool CRectangleEx::Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd, int nMode)
{
		switch(nMode)
		{
			//	Truong hop thuc hien cho chuc nang di chuyen doi tuong
			case MR_DRAG:
				Draw(hdc);
				DrawSelected(hdc);
				Move(ptSrc, ptEnd);
				Draw(hdc);
				DrawSelected(hdc);
				break;
			//	Truong hop ko chon Resize hoac Move
			case MR_NONE:
				break;
			//	Truong hop chon chuc nang Resize tai 1 tracker
			default:
				Draw(hdc);
				DrawSelected(hdc);
				Resize(ptEnd, nMode);
				Draw(hdc);
				DrawSelected(hdc);
				break;
		}
	return true;
}
/******************************************************************************
* bool CRectangleEx::Rotate(HDC hdc)
* Description : Ham thuc hien viec quay HCN
*****************************************************************************/
bool CRectangleEx::Rotate(HDC hdc)
{
	//xoa HCN truoc
	Draw(hdc);
	DrawSelected(hdc);

	POINTS ptCenter, ptTemp;
	int nTmp1,nTmp2;
	//	Set toa do tam cua HCN
	ptCenter.x = (m_ptBegin.x + m_ptEnd.x) / 2;
	ptCenter.y = (m_ptBegin.y + m_ptEnd.y) / 2;
	//	Tinh toan toa do chieu dai va chieu rong
	nTmp1 = abs((m_ptEnd.x - m_ptBegin.x) / 2);
	nTmp2 = abs((m_ptEnd.y - m_ptBegin.y) / 2);
	ptTemp.x = ptCenter.x - nTmp2;
	ptTemp.y = ptCenter.y - nTmp1;
	// Quay 90 do
	if ((ptTemp.x >= LEFTOFFSET) && (ptTemp.y >= TOPOFFSET))
	{
	m_ptBegin.x = ptCenter.x - nTmp2;
	m_ptBegin.y = ptCenter.y - nTmp1;
	m_ptEnd.x = ptCenter.x + nTmp2;
	m_ptEnd.y = ptCenter.y + nTmp1;
	}
	// ve lai HCN
	Draw(hdc);
	DrawSelected(hdc);
	return true;
}