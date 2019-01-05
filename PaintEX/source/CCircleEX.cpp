#include "stdafx.h"
#include "CCircleEX.h"
#include "CShapeEX.h"
#include <math.h>

CCircleEX::CCircleEX()
{
	
	m_nPattern = MS_CIRCLE;
}


/******************************************************************
* Method name      : CCircleEX::IsSelected(HDC hdc, POINTS pt)
* Description    : Check a point in or out of circle range, if this 
*					point is in circle range , DrawSelected function
*					is call.
**********/ 
int CCircleEX::IsSelected(POINTS pt)
{	
	int nRadius;
	POINTS ptCenter;
	double dbDeltaX, dbDeltaY;
	ptCenter.x = (m_ptBegin.x + m_ptEnd.x) / 2;	//	Hoanh do tam duong tron.
	ptCenter.y = (m_ptBegin.y + m_ptEnd.y) / 2;	//	Tung do tam duong tron.
	nRadius = int (abs (m_ptBegin.x - ptCenter.x));	//	Ban kinh duong tron.
	dbDeltaX = double(pow(double(pt.x - ptCenter.x) , 2));
	dbDeltaY = double(pow(double(pt.y - ptCenter.y) , 2));
	//nDistance = int(sqrt(dbDeltaX + dbDeltaY));	// Khoang cach tu diem pt den tam hinh tron
	POINTS arr_xPt[8];	//	toa do tam cua 8 tracker hinh vuong.
	{
		arr_xPt[0].x = ptCenter.x - nRadius;
		arr_xPt[0].y = ptCenter.y - nRadius;
		arr_xPt[1].x = ptCenter.x;
		arr_xPt[1].y = ptCenter.y - nRadius;
		arr_xPt[2].x = ptCenter.x + nRadius;
		arr_xPt[2].y = ptCenter.y - nRadius;
		arr_xPt[3].x = ptCenter.x + nRadius;
		arr_xPt[3].y = ptCenter.y;
		arr_xPt[4].x = ptCenter.x + nRadius;
		arr_xPt[4].y = ptCenter.y + nRadius;
		arr_xPt[5].x = ptCenter.x;
		arr_xPt[5].y = ptCenter.y + nRadius;
		arr_xPt[6].x = ptCenter.x - nRadius;
		arr_xPt[6].y = ptCenter.y + nRadius;
		arr_xPt[7].x = ptCenter.x - nRadius;
		arr_xPt[7].y = ptCenter.y;

	}
	if ((CheckPointInRect(arr_xPt[0], pt)) && MinDistance(arr_xPt[0], pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		return MR_TOPLEFT;
	}
	else if ((CheckPointInRect(arr_xPt[1], pt)) && MinDistance(arr_xPt[1], pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
		return MR_TOPMIDDLE;
	}
	else if ((CheckPointInRect(arr_xPt[2], pt)) && MinDistance(arr_xPt[2], pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		return MR_TOPRIGHT;
	}
	else if ((CheckPointInRect(arr_xPt[3], pt)) && MinDistance( arr_xPt[3], pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		return MR_RIGHTMIDDLE;
	}
	else if ((CheckPointInRect(arr_xPt[4], pt)) && MinDistance(arr_xPt[4], pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		return MR_BOTTOMRIGHT;
	}
	else if ((CheckPointInRect(arr_xPt[5], pt)) && MinDistance(arr_xPt[5], pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
		return MR_BOTTOMMIDDLE;
	}
	else if ((CheckPointInRect(arr_xPt[6], pt)) && MinDistance(arr_xPt[6], pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		return MR_BOTTOMLEFT;
	}
	else if ((CheckPointInRect(arr_xPt[7], pt)) && MinDistance(arr_xPt[7], pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		return MR_LEFTMIDDLE;
	}
	else if (CheckPointInCircle(ptCenter.x-nRadius, ptCenter.y-nRadius, ptCenter.x+nRadius, ptCenter.y+nRadius, pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		return MR_DRAG;
	}
	else
	{
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		return MR_NONE;
	}
}
/******************************************************************
* Method name      : CCircleEX::Modify (HDC hdc, POINTS ptSrc, POINTS ptDes, int nMode)
* Description    : Chinh sua hinh tron, move hoac resize , dua vao cac diem
*					toa do chuot ptSrc va ptDes.
**********/ 
bool CCircleEX::Modify (HDC hdc, POINTS ptSrc, POINTS ptDes, int nMode)
{
	switch(nMode)
	{
	case MR_DRAG:
		Draw(hdc);
		DrawSelected(hdc);
		Move(ptSrc, ptDes);
		Draw(hdc);
		DrawSelected(hdc);
		break;
	case MR_NONE:
		break;
	default:
		Draw(hdc);
		DrawSelected(hdc);
		Resize(ptSrc, nMode);
		Draw(hdc);
		DrawSelected(hdc);
		break;
	}
	return true;
}
bool CCircleEX::Rotate(HDC hdc)
{
	return false;
}


/******************************************************************
* Method name      : CCircleEX::DrawSelected(HDC hdc)
* Description    : Draw 8 trackers when object was selected. Trackers
*					are 8 square which have centers at top-left,top-middle,
*					top-right, left-middle, right-middle, bottom-left, 
*					bottom-middle,bottom-right of the square.		
**********/ 
void CCircleEX::DrawSelected(HDC hdc)
{
	int nRadius;
	POINTS ptCenter;
	ptCenter.x = (m_ptBegin.x + m_ptEnd.x)/2;
	ptCenter.y = (m_ptBegin.y + m_ptEnd.y)/2;
	nRadius = int (abs (m_ptBegin.x - ptCenter.x));
	POINTS arr_xPt[8];	//	vi tri tam cua 8 hinh vuong tracker.
	{
		arr_xPt[0].x = ptCenter.x - nRadius;
		arr_xPt[0].y = ptCenter.y - nRadius;
		arr_xPt[1].x = ptCenter.x;
		arr_xPt[1].y = ptCenter.y - nRadius;
		arr_xPt[2].x = ptCenter.x + nRadius;
		arr_xPt[2].y = ptCenter.y - nRadius;
		arr_xPt[3].x = ptCenter.x + nRadius;
		arr_xPt[3].y = ptCenter.y;
		arr_xPt[4].x = ptCenter.x + nRadius;
		arr_xPt[4].y = ptCenter.y + nRadius;
		arr_xPt[5].x = ptCenter.x;
		arr_xPt[5].y = ptCenter.y + nRadius;
		arr_xPt[6].x = ptCenter.x - nRadius;
		arr_xPt[6].y = ptCenter.y + nRadius;
		arr_xPt[7].x = ptCenter.x - nRadius;
		arr_xPt[7].y = ptCenter.y;

	}
	// Draw bounded line
	HPEN hPen = CreatePen (PS_DASH, 1, RGB(0, 0, 0));
	SelectObject (hdc, hPen);
	HGDIOBJ hObjOld;
	hObjOld = SelectObject (hdc, GetStockObject(NULL_BRUSH));
	//	Ve hinh vuong bao ben ngoai hinh tron khi hinh tron duoc chon
	Rectangle(hdc,arr_xPt[0].x , arr_xPt[0].y , arr_xPt[4].x, arr_xPt[4].y );
	hPen = CreatePen (PS_SOLID, m_nPenWidth, RGB(0, 0, 0));
	HPEN hPenOld = (HPEN)SelectObject (hdc, hPen);
	SelectObject (hdc, hPen);
	hObjOld = SelectObject (hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(0, 0, 0));
	for(int i = 0; i < 8; i++)			//	Ve 8 hinh vuong trackers.
	{
		Rectangle(hdc, arr_xPt[i].x-m_nPenWidth-SIZESQUAREBORDER, arr_xPt[i].y-m_nPenWidth-SIZESQUAREBORDER, 
					arr_xPt[i].x+m_nPenWidth+SIZESQUAREBORDER, arr_xPt[i].y+m_nPenWidth+SIZESQUAREBORDER);
	}
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	DeleteObject(hPenOld);
	m_bSelected = !m_bSelected;
}

/******************************************************************
* Method name      :CCircleEX::Move(POINTS ptSrc, POINTS ptDes)
* Description    : Update cac toa do cua hai diem m_ptBegin va m_ptEnd
*				    khi doi tuong duoc chon va chuot di chuyen.
**********/ 
bool CCircleEX::Move(POINTS ptSrc, POINTS ptDes)
{
	int nDeltaX, nDeltaY;
    POINTS ptTempBegin = m_ptBegin;
	nDeltaX = ptDes.x - ptSrc.x;
	nDeltaY = ptDes.y - ptSrc.y;
    ptTempBegin.x += (ptDes.x - ptSrc.x); ptTempBegin.y += (ptDes.y - ptSrc.y);
    if ((ptTempBegin.x >= LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER) && 
		(ptTempBegin.y >= TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER))
    {
        m_ptBegin.x += nDeltaX; m_ptBegin.y += nDeltaY;
        m_ptEnd.x += nDeltaX; m_ptEnd.y += nDeltaY;
    }
	return false;
}


/******************************************************************
* Method name      : CCircleEX::Resize(POINTS pt, int nNumTracker)
* Description    : Thuc hien thao tac resize hinh tron, thao tac resize 
*				   tuy thuoc vao vi tri nhap chuot dau tien o vi tri
*				   tracker nao.
**********/ 
bool CCircleEX::Resize(POINTS pt, int nNumTracker)
{
	switch(nNumTracker)
	{
		//	Diem pt nam o vung MR_TOPLEFT :
	case MR_TOPLEFT:
		m_ptBegin.x = pt.x;
		m_ptBegin.y = m_ptEnd.y + pt.x - m_ptEnd.x;
		if ((pt.x >= m_ptEnd.x - LIMITBORDER))
		{
			m_ptBegin.x = m_ptEnd.x - LIMITBORDER;
			m_ptBegin.y = m_ptEnd.y - LIMITBORDER;
		}
// 		if ((pt.x < m_ptEnd.x - LIMITBORDER) && (abs (pt.y - m_ptBegin.y) > abs (pt.x - m_ptBegin.x)))
// 		{
// 			m_ptBegin.x = pt.x;
// 			m_ptBegin.y = m_ptEnd.y - (m_ptEnd.x - pt.x);
// 		}
// 		if ((pt.y < m_ptEnd.y - LIMITBORDER) && (abs( pt.x - m_ptBegin.x) > abs(pt.y - m_ptBegin.y)))
// 		{
// 			m_ptBegin.y = pt.y;
// 			m_ptBegin.x = m_ptEnd.x - (m_ptEnd.y - pt.y);
// 		}
		//	Neu chuot duoc keo va diem top-left  lien tuc vuot qua bien rule ben trai
		if (m_ptBegin.x < LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER)
		{
			m_ptBegin.x = LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER;
			m_ptBegin.y = m_ptEnd.y - m_ptEnd.x;
		}
		//	Neu chuot duoc keo va diem top-left  lien tuc vuot qua bien rule ben tren
		if (m_ptBegin.y < TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER)
		{
			m_ptBegin.x = m_ptEnd.x - (m_ptEnd.y - TOPOFFSET - m_nPenWidth - SIZESQUAREBORDER);
			m_ptBegin.y = TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER;
		}
			break;
		//	Diem pt nam o vung MR_TOPMIDDLE :
	case MR_TOPMIDDLE:
		m_ptBegin.y = pt.y;
		if ((pt.y >= m_ptEnd.y - LIMITBORDER) || (pt.x <= m_ptBegin.x - LIMITBORDER))
		{
			m_ptEnd.x = m_ptBegin.x + LIMITBORDER;
			m_ptBegin.y = m_ptEnd.y - LIMITBORDER;
		}
		//	Neu chuot duoc keo va diem top-left  lien tuc vuot qua bien rule ben trai
		if (m_ptBegin.x < LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER)
			m_ptBegin.x = LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER;
		//	Neu chuot duoc keo va diem top-left  lien tuc vuot qua bien rule ben tren
		if (m_ptBegin.y < TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER)
			m_ptBegin.y = TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER;
		break;
		//	Diem pt nam o vung MR_TOPRIGHT :
	case MR_TOPRIGHT:
		m_ptEnd.x = pt.x;
		m_ptBegin.y = pt.y;
		if (pt.y >= m_ptEnd.y - LIMITBORDER)
		{
			m_ptEnd.x = m_ptBegin.x + LIMITBORDER;
			m_ptBegin.y = m_ptEnd.y - LIMITBORDER;
		}
		if ((pt.x <= m_ptBegin.x) && (pt.y < m_ptEnd.y - LIMITBORDER))
		{
			m_ptBegin.y = pt.y;
			m_ptEnd.x = m_ptBegin.x + (m_ptEnd.y - pt.y);
		}
		//	Neu chuot duoc keo va diem top-left  lien tuc vuot qua bien rule ben trai
		if (m_ptBegin.x < LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER)
			m_ptBegin.x = LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER;
		//	Neu chuot duoc keo va diem top-left  lien tuc vuot qua bien rule ben tren
		if (m_ptBegin.y < TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER)
			m_ptBegin.y = TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER;
		break;
		//	Diem pt nam o vung MR_RIGHTMIDDLE :
	case MR_RIGHTMIDDLE:
		m_ptEnd.x = pt.x;
		m_ptBegin.y = m_ptBegin.x-pt.x + m_ptEnd.y;
		if (pt.x <= m_ptBegin.x + LIMITBORDER)
		{
			m_ptEnd.x = m_ptBegin.x + LIMITBORDER;
			m_ptBegin.y = m_ptEnd.y - LIMITBORDER;
		}
		//	Neu chuot duoc keo va diem top-left  lien tuc vuot qua bien rule ben trai
		if (m_ptBegin.x < LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER)
			m_ptBegin.x = LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER;
		//	Neu chuot duoc keo va diem top-left  lien tuc vuot qua bien rule ben tren
		if (m_ptBegin.y < TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER)
			m_ptBegin.y = TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER;
		break;
		//	Diem pt nam o vung MR_BOTTOMRIGHT :
	case MR_BOTTOMRIGHT:
		m_ptEnd.x = pt.x;
		m_ptEnd.y = pt.y;
		if (pt.y <= m_ptBegin.y + LIMITBORDER)
		{
			m_ptEnd.x = m_ptBegin.x + LIMITBORDER;
			m_ptEnd.y = m_ptBegin.y + LIMITBORDER;
		}
		if ((pt.y > m_ptBegin.y + LIMITBORDER) && (pt.x < m_ptBegin.x))
		{
			m_ptEnd.x =	m_ptBegin.x + (m_ptBegin.x - pt.x);
			m_ptEnd.y = pt.y; 
		}
		break;
		//	Diem pt nam o vung MR_BOTTOMMIDDLE :
	case MR_BOTTOMMIDDLE:
		m_ptEnd.y = pt.y;
		if (pt.y <= m_ptBegin.y + LIMITBORDER)
		{
			m_ptEnd.x = m_ptBegin.x + LIMITBORDER;
			m_ptEnd.y = m_ptBegin.y + LIMITBORDER;
		}
		break;
		//	Diem pt nam o vung MR_BOTTOMLEFT :
	case MR_BOTTOMLEFT:
		m_ptBegin.x = pt.x;
		m_ptEnd.y = m_ptEnd.x-pt.x + m_ptBegin.y;
		if ((pt.x >= m_ptEnd.x - LIMITBORDER))
		{
			m_ptBegin.x = m_ptEnd.x - LIMITBORDER;
			m_ptEnd.y = m_ptBegin.y + LIMITBORDER;
		} 
		// Giu hinh tron co dinh khi pt.x duoc keo lien tuc ve phia ben trai vuot khoi bien rule.
		if (pt.x <= LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER)
		{
			m_ptBegin.x = LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER;
			m_ptEnd.y = m_ptBegin.y + (m_ptEnd.x - LEFTOFFSET - m_nPenWidth - SIZESQUAREBORDER);
		}
		break;
		//	Diem pt nam o vung MR_LEFTMIDDLE:
	case MR_LEFTMIDDLE:
		if (pt.x >= m_ptEnd.x - LIMITBORDER)
		{
			m_ptEnd.y = m_ptBegin.y + LIMITBORDER;
			m_ptBegin.x = m_ptEnd.x - LIMITBORDER;
		} 
		else
		{
			m_ptBegin.x = pt.x;
			m_ptEnd.y = m_ptEnd.x- pt.x + m_ptBegin.y;
		}
		//	Neu chuot duoc keo va diem top-left lien tuc vuot qua bien rule ben trai
		if (m_ptBegin.x < LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER)
		{
			m_ptBegin.x = LEFTOFFSET + m_nPenWidth + SIZESQUAREBORDER;
			m_ptEnd.y = m_ptBegin.y + (m_ptEnd.x - LEFTOFFSET - m_nPenWidth - SIZESQUAREBORDER);
		}
		//	Neu chuot duoc keo va diem top-left lien tuc vuot qua bien rule ben tren
		if (m_ptBegin.y < TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER)
		{
			m_ptBegin.y = TOPOFFSET + m_nPenWidth + SIZESQUAREBORDER;
		}
		break;
	default:
		break;
	}
	return false;
}

/******************************************************************
* Method name      : CircleEX::CheckPointInRect(POINTS ptTracker, POINTS pt)
* Description    : Kiem tra xem diem pt kieu POINTS co thuoc hinh vuong tracker
*				 co tam la diem ptTracker thuoc kieu POINTS voi cac do dai canh
*				 bien thien theo do rong but ve va kich thuoc canh cua tracker.
* Parameters    :  -	POINTS ptTracker	: diem tracker.
*				   -	POINTS pt	: toa do diem nhap chuot. 	
**********/
bool CCircleEX::CheckPointInRect(POINTS ptTracker, POINTS pt)
{
	if   ((pt.x >= ptTracker.x - m_nPenWidth - SIZESQUAREBORDER )
		&& (pt.x <= ptTracker.x + m_nPenWidth + SIZESQUAREBORDER )
		&& (pt.y <= ptTracker.y + m_nPenWidth + SIZESQUAREBORDER )
		&& (pt.y >= ptTracker.y - m_nPenWidth - SIZESQUAREBORDER ))
		return true;
	else
		return false;

}


/******************************************************************
* Method name      : CCircleEX::CheckPointInCircle (int ptBegin_x, 
						int ptBegin_y, int ptEnd_x, int ptEnd_y, POINTS pt)
* Description    : Kiem tra xem diem pt co nam trong vung hinh tron co hinh vuong
*				   ngoai tiep voi cac toa do left, top, right, bottom tuong ung lan
*				   luot la ptBegin_x, ptBegin_y, ptEnd_x, ptEnd_y
* Parameters    :  -	Cac toa do kieu int: ptBegin_x, ptBegin_y, ptEnd_x, ptEnd_y lan luot 
*						la left, top, right, bottom cua hinh vuong ngoai tiep hinh tron.
*				   -	Diem pt kieu POINTS la toa do chuot.
**********/ 
bool CCircleEX::CheckPointInCircle (int ptBegin_x, int ptBegin_y, int ptEnd_x, int ptEnd_y, POINTS pt)
{
	int nRadius, nDistance;
	POINTS ptCenter;
	double dbDeltaX, dbDeltaY;
	ptCenter.x = (ptBegin_x + ptEnd_x) / 2;	//	Hoanh do tam hinh tron.
	ptCenter.y = (ptBegin_y + ptEnd_y) / 2;	//	Tung do tam hinh tron.
	nRadius = int (abs (ptBegin_x - ptCenter.x));
	dbDeltaX = double(pow(double(pt.x - ptCenter.x) , 2));
	dbDeltaY = double(pow(double(pt.y - ptCenter.y) , 2));
	nDistance = int(sqrt(dbDeltaX + dbDeltaY));	//	Khoang cach tu diem pt den tam hinh tron.
	if (nDistance <= nRadius - SIZESQUAREBORDER)
	{
		return true;
	}
	return false;
}

/******************************************************************
* Method name      : CCircleEX::CalculateDistance (POINTS pt1, POINTS pt2)
* Description    : Tinh toan khoang cach giua hai diem pt1 va pt2 kieu POINTS				 
**********/ 
int CCircleEX::CalculateDistance (POINTS pt1, POINTS pt2)
{
	double dbDeltaX, dbDeltaY;
	int nDistance;
	dbDeltaX = double(pow(double(pt1.x - pt2.x) , 2));
	dbDeltaY = double(pow(double(pt1.y - pt2.y) , 2));
	nDistance = int (sqrt (dbDeltaX + dbDeltaY));
	return nDistance;
}


/******************************************************************
* Method name      : CCircleEX::MinDistance (POINTS ptTracker, POINTS pt)
* Description    :	Xac dinh xem khoang cach tu 1 diem pt den vi tri ptTracker day
*					co phai la nho nhat hay khong. Muc dich la giup phan biet chuot 
*					dang o vi tri tracker nao khi hinh tron o kich thuoc nho nhat, vi
*					luc do cac tracker o vi tri rat gan nhau.				 
**********/ 
bool CCircleEX::MinDistance (POINTS ptTracker, POINTS pt)
{
	int nRadius;
	int count = 0;
	POINTS ptCenter;
	ptCenter.x = ( m_ptBegin.x + m_ptEnd.x) / 2;
	ptCenter.y = (m_ptBegin.y + m_ptEnd.y) / 2;
	nRadius = int (abs (m_ptBegin.x - ptCenter.x));
	POINTS arr_xPt[8];	//	toa do tam cua 8 tracker hinh vuong
	{
		arr_xPt[0].x = ptCenter.x - nRadius;
		arr_xPt[0].y = ptCenter.y - nRadius;
		arr_xPt[1].x = ptCenter.x;
		arr_xPt[1].y = ptCenter.y - nRadius;
		arr_xPt[2].x = ptCenter.x + nRadius;
		arr_xPt[2].y = ptCenter.y - nRadius;
		arr_xPt[3].x = ptCenter.x + nRadius;
		arr_xPt[3].y = ptCenter.y;
		arr_xPt[4].x = ptCenter.x + nRadius;
		arr_xPt[4].y = ptCenter.y + nRadius;
		arr_xPt[5].x = ptCenter.x;
		arr_xPt[5].y = ptCenter.y + nRadius;
		arr_xPt[6].x = ptCenter.x - nRadius;
		arr_xPt[6].y = ptCenter.y + nRadius;
		arr_xPt[7].x = ptCenter.x - nRadius;
		arr_xPt[7].y = ptCenter.y;
	}
	for (int i = 0; i < 8; i++)
	{
		if (CalculateDistance (ptTracker, pt) > CalculateDistance(arr_xPt[i], pt))
		{
			count ++ ;
		}
	}
	if (count > 0)
	{
		return false;
	} 
	else
	{
		return true;
	}
}

/******************************************************************
* Method name      : CCircleEX::Draw(HDC hdc)
* Description    : Ve hinh tron				 
**********/ 
bool CCircleEX::Draw(HDC hdc)
{
	HPEN hPen = SetPen(hdc);
	int top, left, right, bottom;
	//	Tinh chinh cac toa do top-left va bottom-right tu 2 diem m_ptBegin va m_ptEnd 
	if ((m_ptEnd.y >= m_ptBegin.y) && ( m_ptEnd.x >= m_ptBegin.x))
	{
		left = m_ptBegin.x;
		top = m_ptBegin.y;
		right = m_ptBegin.x + abs(m_ptBegin.y - m_ptEnd.y);
		bottom = m_ptEnd.y;
	}
	else if (( m_ptEnd.y < m_ptBegin.y) && ( m_ptEnd.x >= m_ptBegin.x))
	{
		left = m_ptBegin.x;
		top = m_ptEnd.y;
		right = m_ptBegin.x + abs( m_ptBegin.y - m_ptEnd.y);
		bottom = m_ptBegin.y;
	}
	else if (( m_ptEnd.y >= m_ptBegin.y) && ( m_ptEnd.x < m_ptBegin.x))
	{
		left = m_ptEnd.x;
		top = m_ptBegin.y;
		right = m_ptBegin.x ;
		bottom = m_ptBegin.y + abs (m_ptBegin.x - m_ptEnd.x);
	}
	else if (( m_ptEnd.y < m_ptBegin.y) && ( m_ptEnd.x < m_ptBegin.x))
	{
		left = m_ptEnd.x;
		top = m_ptBegin.y - abs (m_ptEnd.x - m_ptBegin.x);
		right = m_ptBegin.x;
		bottom = m_ptBegin.y;
		if (top < TOPOFFSET)
		{
			left = m_ptBegin.x - (m_ptBegin.y - TOPOFFSET);
			top = TOPOFFSET;
		}
	}
	Ellipse(hdc, left, top, right, bottom);
	//	Cap nhat lai toa do cua m_ptBegin va m_ptEnd de thuc hien cac tac vu sau.
	m_ptBegin.x = left;
	m_ptBegin.y = top;
	m_ptEnd.x = right;
	m_ptEnd.y = bottom;

	//	Giai phong but ve
	ReleasePen(hPen);
	return true;
}