#include "StdAfx.h"
#include "CRightTriangleEX.h"				//	include file

CRightTriangleEX::CRightTriangleEX()					//	constructor
{	
	m_nPattern = MS_RIGHT_TRIANGLE;
}
/******************************************************************
* Method name      : CRightTriangleEX::Draw()
* Description    :   Draw a triangle 
**********/ 
bool CRightTriangleEX::Draw(HDC hdc)						
{
	HPEN hPen = SetPen(hdc);
	this->SetCoordinates();	//	thiet lap cac toa do cho tam giac 
	
	//	Declare a array which has three point elements (POINT type)
	//	this array is only used for the Polygon() function below
	POINT xPt[3];
	xPt[0].x = m_xPt1.x;
	xPt[0].y = m_xPt1.y;
	xPt[1].x = m_xPt2.x;
	xPt[1].y = m_xPt2.y;
	xPt[2].x = m_xPt3.x;
	xPt[2].y = m_xPt3.y;
	Polygon(hdc, xPt, 3);
	////	Giai phong but ve
	ReleasePen(hPen);
	return true;
}
/******************************************************************
* Method name      : CRightTriangleEX::SelectedTracker()
* Description    :   Check if a point is inside trackers or not
**********/ 
bool CRightTriangleEX::SelectedTracker(POINTS pt)
{
	POINTS arr_xPt[8];				//	the position of trackers
	arr_xPt[0].x = m_ptBegin.x;
	arr_xPt[0].y = m_ptBegin.y;
	arr_xPt[1].x = (m_ptEnd.x + m_ptBegin.x)/2;
	arr_xPt[1].y = m_ptBegin.y;
	arr_xPt[2].x = m_ptEnd.x;
	arr_xPt[2].y = m_ptBegin.y;
	arr_xPt[3].x = m_ptEnd.x;
	arr_xPt[3].y = (m_ptBegin.y + m_ptEnd.y)/2;
	arr_xPt[4].x = m_ptEnd.x;
	arr_xPt[4].y = m_ptEnd.y;
	arr_xPt[5].x = (m_ptEnd.x + m_ptBegin.x)/2;
	arr_xPt[5].y = m_ptEnd.y;
	arr_xPt[6].x = m_ptBegin.x;
	arr_xPt[6].y = m_ptEnd.y;
	arr_xPt[7].x = m_ptBegin.x;
	arr_xPt[7].y = (m_ptBegin.y + m_ptEnd.y)/2;
	if	  ((InsideTracker(arr_xPt[0], pt))
		||(InsideTracker(arr_xPt[1], pt))
		||(InsideTracker(arr_xPt[2], pt)) 
		||(InsideTracker(arr_xPt[3], pt)) 
		||(InsideTracker(arr_xPt[4], pt)) 
		||(InsideTracker(arr_xPt[5], pt)) 
		||(InsideTracker(arr_xPt[6], pt)) 
		||(InsideTracker(arr_xPt[7], pt)))
	{
		return true;
	}
	else
		return false;
}
/******************************************************************
* Method name      : CRightTriangleEX::Modify()
* Description    :   move or resize object
**********/ 
bool CRightTriangleEX::Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd, int nMode)
{
	switch(nMode)
	{
	case MR_DRAG:
		Draw(hdc);	
		DrawSelected(hdc);
		Move(ptSrc, ptEnd);
		Draw(hdc);
		DrawSelected(hdc);
		break;
	case MR_NONE:
		break;
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
/******************************************************************
* Method name      : CRightTriangleEX::Rotate()
* Description    :   rotate object
**********/ 
bool CRightTriangleEX::Rotate(HDC hdc)				
{
	POINTS ptA1, ptB1;
	ptA1.x = (m_ptBegin.x + m_ptEnd.x)/2 - (m_ptEnd.y - m_ptBegin.y)/2;
	ptA1.y = (m_ptBegin.y + m_ptEnd.y)/2 - (m_ptEnd.x - m_ptBegin.x)/2;
	ptB1.x = (m_ptBegin.x + m_ptEnd.x)/2 + (m_ptEnd.y - m_ptBegin.y)/2;
	ptB1.y = (m_ptBegin.y + m_ptEnd.y)/2 + (m_ptEnd.x - m_ptBegin.x)/2;
	if ((ptA1.x >= LEFTOFFSET + m_nPenWidth + 3)
		&&(ptA1.y >= TOPOFFSET + m_nPenWidth + 3))
	{	
		this->Draw(hdc);  //  xoa hinh ve cu
		this->DrawSelected(hdc);			//  xoa cac tracker hinh ve cu
		m_nDegree = m_nDegree + RD_NINETY;	//  quay toa di 90 do(update toa do moi)
		if (m_nDegree == 4)					//	neu m_nDegree =4 nghia la hinh da quay 360 do thi vong quay tiep theo reset ve 0
		{
			m_nDegree = 0;
		}
		//	update toa do moi cho doi tuong
		m_ptBegin = ptA1;
		m_ptEnd = ptB1;
		this->Draw(hdc);	//  ve hinh moi
		this->DrawSelected(hdc);	//  ve cac tracker cho hinh moi
		return true;
	}
	else
		return true;
}
/******************************************************************
* Method name      : CRightTriangleEX::DrawSelected()
* Description    :   Draw trackers
**********/ 
void CRightTriangleEX::DrawSelected(HDC hdc)
{
	POINTS arr_xPt[8];				//	the position of trackers
	arr_xPt[0].x = m_ptBegin.x;
	arr_xPt[0].y = m_ptBegin.y;
	arr_xPt[1].x = (m_ptEnd.x + m_ptBegin.x)/2;
	arr_xPt[1].y = m_ptBegin.y;
	arr_xPt[2].x = m_ptEnd.x;
	arr_xPt[2].y = m_ptBegin.y;
	arr_xPt[3].x = m_ptEnd.x;
	arr_xPt[3].y = (m_ptBegin.y + m_ptEnd.y)/2;
	arr_xPt[4].x = m_ptEnd.x;
	arr_xPt[4].y = m_ptEnd.y;
	arr_xPt[5].x = (m_ptEnd.x + m_ptBegin.x)/2;
	arr_xPt[5].y = m_ptEnd.y;
	arr_xPt[6].x = m_ptBegin.x;
	arr_xPt[6].y = m_ptEnd.y;
	arr_xPt[7].x = m_ptBegin.x;
	arr_xPt[7].y = (m_ptBegin.y + m_ptEnd.y)/2;
	// Draw bounded line
	HPEN hPen = CreatePen (PS_DASH, 1, RGB(0, 0, 0));	// but mau den, net gach
	SelectObject (hdc, hPen);
	HGDIOBJ hObjOld;
 	hObjOld = SelectObject (hdc, GetStockObject(NULL_BRUSH));	
	Rectangle
		(
		hdc, 
		arr_xPt[0].x,
		arr_xPt[0].y,
		arr_xPt[4].x, 
		arr_xPt[4].y
		);
	// thiet lap but ve va mau nen cho cac tracker
	hPen = CreatePen (PS_SOLID, 1, RGB(0, 0, 0));				// but mau den, net lien
	SelectObject (hdc, hPen);
	hObjOld = SelectObject (hdc, GetStockObject(DC_BRUSH));		
	SetDCBrushColor(hdc, RGB(0, 0, 0));							// to mau den cho tracker
	// Draw bounded line
	for(int i=0;i<8;i++)			//	Draw 8 trackers
	{
		Rectangle
			(
				hdc, 
				arr_xPt[i].x - m_nPenWidth - 3,
				arr_xPt[i].y - m_nPenWidth - 3, 
				arr_xPt[i].x + m_nPenWidth + 3,
				arr_xPt[i].y + m_nPenWidth + 3
			);
	}
	SelectObject(hdc, hObjOld);
	DeleteObject(hObjOld);
	SelectObject(hdc, hPen);
	DeleteObject(hPen);
	m_bSelected = !m_bSelected;
}
/******************************************************************
* Method name      : CRightTriangleEX::Move()
* Description    :   update coordinates when move object
**********/ 
bool CRightTriangleEX::Move(POINTS ptSrc, POINTS ptDes)
{
	//	Gan toa do sau khi move
	int nDx, nDy;
	POINTS ptTempBegin = m_ptBegin;
	nDx = ptDes.x - ptSrc.x;
	nDy = ptDes.y - ptSrc.y;
	ptTempBegin.x += (ptDes.x - ptSrc.x); 
	ptTempBegin.y += (ptDes.y - ptSrc.y);
	if ((ptTempBegin.x >= LEFTOFFSET + m_nPenWidth + 3) 
		&& ptTempBegin.y >= TOPOFFSET + m_nPenWidth + 3)
	{
		m_ptBegin.x += nDx; 
		m_ptBegin.y += nDy;
		m_ptEnd.x += nDx; 
		m_ptEnd.y += nDy;
	}

	return true;
}
/******************************************************************
* Method name      : CRightTriangleEX::Resize()
* Description    :   update coordinates when resize object
**********/ 
bool CRightTriangleEX::Resize(POINTS pt, int numTracker)
{
	int nSpace = 4*(m_nPenWidth + 3);
	if ((pt.x >= LEFTOFFSET + m_nPenWidth + 3)
		&&(pt.y >= TOPOFFSET + m_nPenWidth + 3))
	{
		switch(numTracker)
		{
		case MR_TOPLEFT:
			if ((pt.x <= m_ptEnd.x - nSpace)&&(pt.y <= m_ptEnd.y - nSpace))
			{
				m_ptBegin.x = pt.x;
				m_ptBegin.y = pt.y;
			}
			break;
		case MR_TOPMIDDLE:
			if (pt.y <= m_ptEnd.y - nSpace)
			{
				m_ptBegin.y = pt.y;
			}
			break;
		case MR_TOPRIGHT:
			if ((pt.x >= m_ptBegin.x + nSpace)&&(pt.y <= m_ptEnd.y - nSpace))
			{	
				m_ptEnd.x = pt.x;
				m_ptBegin.y = pt.y;
			}
			break;
		case MR_RIGHTMIDDLE:
			if (pt.x >= m_ptBegin.x + nSpace)
			{	
				m_ptEnd.x = pt.x;
			}
			break;
		case MR_BOTTOMRIGHT:
			if ((pt.x >= m_ptBegin.x + nSpace)&&(pt.y >= m_ptEnd.y + nSpace))
			{		
				m_ptEnd.x = pt.x;
				m_ptEnd.y = pt.y;
			}
			break;
		case MR_BOTTOMMIDDLE:
			if (pt.y >= m_ptBegin.y + nSpace)
			{
				m_ptEnd.y = pt.y;
			}
			break;
		case MR_BOTTOMLEFT:
			if ((pt.x <= m_ptEnd.x - nSpace)&&(pt.y >= m_ptBegin.y + nSpace))
			{
				m_ptBegin.x = pt.x;
				m_ptEnd.y = pt.y;
			}
			break;
		case MR_LEFTMIDDLE:
			if (pt.x <= m_ptEnd.x - nSpace)
			{
				m_ptBegin.x = pt.x;
			}
			break;
		default:
			break;
		}
		return true;
	}
	else 	
	return false;
}
/******************************************************************
* Method name      : CRightTriangleEX::InsideTracker()
* Description    :   Check if a point is inside trackers or not
**********/ 
bool CRightTriangleEX::InsideTracker(POINTS ptTracker, POINTS pt)
{
	if   ((pt.x >= ptTracker.x - m_nPenWidth - 3)
		&&(pt.x <= ptTracker.x + m_nPenWidth + 3)
		&&(pt.y <= ptTracker.y + m_nPenWidth + 3)
		&&(pt.y >= ptTracker.y - m_nPenWidth - 3))
		return true;
	else
		return false;
}
/******************************************************************
* Method name      : CRightTriangleEX::IsSelected()
* Description    :   Check if a point is inside object or not
**********/ 
int	 CRightTriangleEX::IsSelected(POINTS pt)
{
	POINTS arr_xPt[8];				//	the position of trackers
		arr_xPt[0].x = m_ptBegin.x;
		arr_xPt[0].x = m_ptBegin.x;
		arr_xPt[0].y = m_ptBegin.y;
		arr_xPt[1].x = (m_ptEnd.x + m_ptBegin.x)/2;
		arr_xPt[1].y = m_ptBegin.y;
		arr_xPt[2].x = m_ptEnd.x;
		arr_xPt[2].y = m_ptBegin.y;
		arr_xPt[3].x = m_ptEnd.x;
		arr_xPt[3].y = (m_ptBegin.y + m_ptEnd.y)/2;
		arr_xPt[4].x = m_ptEnd.x;
		arr_xPt[4].y = m_ptEnd.y;
		arr_xPt[5].x = (m_ptEnd.x + m_ptBegin.x)/2;
		arr_xPt[5].y = m_ptEnd.y;
		arr_xPt[6].x = m_ptBegin.x;
		arr_xPt[6].y = m_ptEnd.y;
		arr_xPt[7].x = m_ptBegin.x;
		arr_xPt[7].y = (m_ptBegin.y + m_ptEnd.y)/2;
	this->SetCoordinates();//  lenh nay chu yeu dung de phuc vu cho ham InsideTriangle() ben duoi day
	if(InsideTracker(arr_xPt[0],pt)) 
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //  doi bieu tuong chuot 
		return MR_TOPLEFT; //	Tra ve gi tri MR_TOPLEFT
	}
	if(InsideTracker(arr_xPt[1],pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
		return MR_TOPMIDDLE;
	}

	if(InsideTracker(arr_xPt[2],pt)) 
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		return MR_TOPRIGHT;
	}

	if(InsideTracker(arr_xPt[3],pt)) 
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		return MR_RIGHTMIDDLE;
	}

	if(InsideTracker(arr_xPt[4],pt)) 
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		return MR_BOTTOMRIGHT;
	}

	if(InsideTracker(arr_xPt[5],pt)) 
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
		return MR_BOTTOMMIDDLE;
	}

	if(InsideTracker(arr_xPt[6],pt)) 
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		return MR_BOTTOMLEFT;
	}

	if(InsideTracker(arr_xPt[7],pt)) 
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		return MR_LEFTMIDDLE;
	}

	if (InsideTriangle(pt))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		return MR_DRAG;
	}
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	return MR_NONE;

}
