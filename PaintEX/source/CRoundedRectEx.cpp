#include "stdafx.h"
#include "CRoundedRectEx.h"
#include "math.h"

CRoundedRectEx::CRoundedRectEx()
{	
	m_nPattern = MS_ROUNDED_RECTANGLE;
}

bool CRoundedRectEx::Modify (HDC hdc, POINTS ptSrc, POINTS ptDes, int nMode)
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
		Resize(ptDes, nMode);
		Draw(hdc);
		DrawSelected(hdc);
		break;
	}
	
	return true;
	
}

bool CRoundedRectEx::Rotate(HDC hdc)
{
    //  Delete old RoundedRect
	Draw(hdc);
	DrawSelected(hdc);
	POINTS ptCenter;
    POINTS ptTemp;
	int nHalfDistanceX, nHalfDistanceY;
	ptCenter.x = (m_ptBegin.x + m_ptEnd.x) / 2;
	ptCenter.y = (m_ptBegin.y + m_ptEnd.y) / 2;
	nHalfDistanceX = ((m_ptEnd.x - m_ptBegin.x) / 2);
	nHalfDistanceY = ((m_ptEnd.y - m_ptBegin.y) / 2);
	//  Rotate 90 degree
	ptTemp.x = ptCenter.x - nHalfDistanceY;
	ptTemp.y = ptCenter.y - nHalfDistanceX;
	
    //  Draw in draw window
    if ((ptTemp.x >= LEFTOFFSET) && (ptTemp.y >= TOPOFFSET))
    {
        m_ptEnd.x = ptCenter.x + nHalfDistanceY;
        m_ptEnd.y = ptCenter.y + nHalfDistanceX;
        m_ptBegin = ptTemp;
    }
    Draw(hdc);
    DrawSelected(hdc);
	return true;
}

void CRoundedRectEx::DrawSelected(HDC hdc)
{
    POINTS ptArray[8];
	ptArray[0].x = m_ptBegin.x;					 // MR_TOPLEFT
	ptArray[0].y = m_ptBegin.y;
	ptArray[1].x = (m_ptBegin.x + m_ptEnd.x)/ 2; //	MR_TOPMIDDLE
	ptArray[1].y = m_ptBegin.y;
	ptArray[2].x = m_ptEnd.x;				     //	MR_TOPRIGHT
	ptArray[2].y = m_ptBegin.y;	
	ptArray[3].x = m_ptEnd.x;				     //	MR_RIGHTMIDDLE	
	ptArray[3].y = (m_ptBegin.y + m_ptEnd.y)/ 2;
	ptArray[4].x = m_ptEnd.x;					 //	MR_BOTTOMRIGHT
	ptArray[4].y = m_ptEnd.y;	
	ptArray[5].x = (m_ptBegin.x + m_ptEnd.x)/ 2; //	MR_BOTTOMMIDDLE	
	ptArray[5].y = m_ptEnd.y;
	ptArray[6].x = m_ptBegin.x;					 //	MR_BOTTOMLEFT
	ptArray[6].y = m_ptEnd.y;
	ptArray[7].x = m_ptBegin.x;					 //	MR_LEFTMIDDLE
	ptArray[7].y = (m_ptBegin.y + m_ptEnd.y)/ 2;
	
	//	Draw bounded Rectangle: dash and transparent 
	HPEN hPen = CreatePen(PS_DASH, 1, RGB(0, 0, 0)); 
	HPEN hPenOld = (HPEN)SelectObject (hdc, hPen);
 	HGDIOBJ hObjOld;
	hObjOld = SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, m_ptBegin.x, m_ptBegin.y, m_ptEnd.x, m_ptEnd.y);

	//	Chose pen for drawing tracker
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));		
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	//	Chose color to fill tracker 
 	hObjOld = SelectObject (hdc, GetStockObject(DC_BRUSH));
 	SetDCBrushColor(hdc, RGB(0, 0, 0));	

	//	Draw 8 tracker
	for (int i=0; i<8; i++)
	{
		Rectangle(hdc, 
				  ptArray[i].x - SIZERECTTRACKER(m_nPenWidth),
				  ptArray[i].y - SIZERECTTRACKER(m_nPenWidth),
				  ptArray[i].x + SIZERECTTRACKER(m_nPenWidth),
				  ptArray[i].y + SIZERECTTRACKER(m_nPenWidth));
		
	}
	m_bSelected = !m_bSelected;
    //Release pen,hObjOld
    SelectObject(hdc,hPenOld);
    DeleteObject(hPen);
    DeleteObject(hPenOld);
    DeleteObject(hObjOld);
}

bool CRoundedRectEx::Move(POINTS ptSrc, POINTS ptDes)
{

	int nDeltaX, nDeltaY;
    POINTS ptTempBegin = m_ptBegin;
	nDeltaX = ptDes.x - ptSrc.x;
	nDeltaY = ptDes.y - ptSrc.y;
    ptTempBegin.x += (ptDes.x - ptSrc.x); ptTempBegin.y += (ptDes.y - ptSrc.y);
    if ((ptTempBegin.x >= LEFTOFFSET) && (ptTempBegin.y >= TOPOFFSET))
    {
        m_ptBegin.x += nDeltaX; m_ptBegin.y += nDeltaY;
        m_ptEnd.x += nDeltaX; m_ptEnd.y += nDeltaY;
    }


	return false;
}
 

bool CRoundedRectEx::Resize(POINTS ptDes, int nNumTracker)
{
	switch(nNumTracker)
	{
	case MR_TOPLEFT:
		if ((ptDes.x <= m_ptEnd.x - 4*SIZERECTTRACKER(m_nPenWidth)) && 
			(ptDes.y <= m_ptEnd.y - 4*SIZERECTTRACKER(m_nPenWidth)))
		m_ptBegin = ptDes;
		break;
	case MR_TOPMIDDLE:
		if ((ptDes.y <= m_ptEnd.y - 4*SIZERECTTRACKER(m_nPenWidth)))
		m_ptBegin.y = ptDes.y;
		break;
	case MR_TOPRIGHT:
		if ((ptDes.x >= m_ptBegin.x + 4*SIZERECTTRACKER(m_nPenWidth)) && 
			(ptDes.y <= m_ptEnd.y - 4*SIZERECTTRACKER(m_nPenWidth)))
		{
			m_ptBegin.y = ptDes.y;
 			m_ptEnd.x = ptDes.x;
		}
		break;
	case MR_LEFTMIDDLE:
		if (ptDes.x <= (m_ptEnd.x - 4*SIZERECTTRACKER(m_nPenWidth)))
			m_ptBegin.x = ptDes.x;
		break;
	case MR_RIGHTMIDDLE:
 		if (ptDes.x >= (m_ptBegin.x + 4*SIZERECTTRACKER(m_nPenWidth))) 
 		m_ptEnd.x = ptDes.x;
		break;
	case MR_BOTTOMLEFT:
		if ((ptDes.x <= m_ptEnd.x - 4*SIZERECTTRACKER(m_nPenWidth)) && 
			(ptDes.y >=m_ptBegin.y + 4*SIZERECTTRACKER(m_nPenWidth)))
		{
			m_ptBegin.x = ptDes.x;
			m_ptEnd.y = ptDes.y;
		}
		break;
	case MR_BOTTOMMIDDLE:
		if (ptDes.y >= m_ptBegin.y + 4*SIZERECTTRACKER(m_nPenWidth))
		m_ptEnd.y = ptDes.y;
		break;
	case MR_BOTTOMRIGHT:
		if ((ptDes.x >= m_ptBegin.x + 4*SIZERECTTRACKER(m_nPenWidth)) && 
			(ptDes.y >= m_ptBegin.y + 4*SIZERECTTRACKER(m_nPenWidth)))
		m_ptEnd = ptDes;
		break;
	}
	return false;
}

int	 CRoundedRectEx::IsSelected(POINTS pt)
{
	
	RECT rcTracker[8];	// Rectangle Tracker											
	RECT rcRect;		// Bounded Rectangle when Rect is selected	
	POINTS ptArray[8];
	ptArray[0].x = m_ptBegin.x;				     // MR_TOPLEFT
	ptArray[0].y = m_ptBegin.y;
	ptArray[1].x = (m_ptBegin.x + m_ptEnd.x)/ 2; //	MR_TOPMIDDLE
	ptArray[1].y = m_ptBegin.y;
	ptArray[2].x = m_ptEnd.x;				     //	MR_TOPRIGHT
	ptArray[2].y = m_ptBegin.y;	
	ptArray[3].x = m_ptEnd.x;				     //	MR_RIGHTMIDDLE	
	ptArray[3].y = (m_ptBegin.y + m_ptEnd.y)/ 2;
	ptArray[4].x = m_ptEnd.x;					 //	MR_BOTTOMRIGHT
	ptArray[4].y = m_ptEnd.y;	
	ptArray[5].x = (m_ptBegin.x + m_ptEnd.x)/ 2; //	MR_BOTTOMMIDDLE	
	ptArray[5].y = m_ptEnd.y;
	ptArray[6].x = m_ptBegin.x;					 //	MR_BOTTOMLEFT
	ptArray[6].y = m_ptEnd.y;
	ptArray[7].x = m_ptBegin.x;				     //	MR_LEFTMIDDLE
	ptArray[7].y = (m_ptBegin.y + m_ptEnd.y)/ 2;
	// Bounded Rectangle
	rcRect.left = m_ptBegin.x - SIZERECTTRACKER(m_nPenWidth);
	rcRect.top = m_ptBegin.y - SIZERECTTRACKER(m_nPenWidth);
	rcRect.right = m_ptEnd.x + SIZERECTTRACKER(m_nPenWidth);
	rcRect.bottom = m_ptEnd.y + SIZERECTTRACKER(m_nPenWidth);
	
	//  Set 8 tracker
	for (int i=0; i<8; i++)
	{
		rcTracker[i].left = ptArray[i].x - SIZERECTTRACKER(m_nPenWidth);
		rcTracker[i].top = ptArray[i].y - SIZERECTTRACKER(m_nPenWidth);
		rcTracker[i].right = ptArray[i].x + SIZERECTTRACKER(m_nPenWidth);
		rcTracker[i].bottom = ptArray[i].y + SIZERECTTRACKER(m_nPenWidth);
	}
	//  covert POINTS to POINT to use PtInRect(RECT *lprc,POINT pt)
	POINT ptPoint;
 	ptPoint.x = (LONG) pt.x;
 	ptPoint.y = (LONG) pt.y;
	//  Check cursor position in Bounded Rectangle
	if(PtInRect(&rcRect, ptPoint))
	{
		//  Check cursor position in one of 8 tracker
		if(PtInRect(&rcTracker[0], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
			return MR_TOPLEFT;
		}
		else if(PtInRect(&rcTracker[1], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
			return MR_TOPMIDDLE;
		}
		else if(PtInRect(&rcTracker[2], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW));
			return MR_TOPRIGHT;
		}
		else if(PtInRect(&rcTracker[3], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
			return MR_RIGHTMIDDLE;
		}
		else if(PtInRect(&rcTracker[4], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
			return MR_BOTTOMRIGHT;
		}
		else if(PtInRect(&rcTracker[5], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
			return MR_BOTTOMMIDDLE;
		}
		else if(PtInRect(&rcTracker[6], ptPoint)) 
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW));
			return MR_BOTTOMLEFT;
		}
		else if(PtInRect(&rcTracker[7], ptPoint)) 
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

void CRoundedRectEx::Setcoordinate()
{
	POINTS ptTempBegin, ptTempEnd;
	ptTempBegin = m_ptBegin;
	ptTempEnd = m_ptEnd;
	// Save the coordinates of the target rectangle. Avoid  
	// invalid rectangles by ensuring that the value of  
	// the left coordinate is lesser than the  
	// right coordinate, and that the value of the top 
	// coordinate is lesser than the bottom coordinate. 

	if ((m_ptBegin.x < m_ptEnd.x) && 
		(m_ptBegin.y > m_ptEnd.y)) 
	{
		m_ptBegin.x = ptTempBegin.x;
		m_ptBegin.y = ptTempEnd.y;
		m_ptEnd.x = ptTempEnd.x;
		m_ptEnd.y = ptTempBegin.y;
	}
	else if ((m_ptBegin.x > m_ptEnd.x) && 
		(m_ptBegin.y > m_ptEnd.y)) 
	{
		m_ptBegin.x = ptTempEnd.x;
		m_ptBegin.y = ptTempEnd.y;
		m_ptEnd.x = ptTempBegin.x;
		m_ptEnd.y = ptTempBegin.y;
	}
	else if ((m_ptBegin.x > m_ptEnd.x) && 
		(m_ptBegin.y < m_ptEnd.y)) 
	{ 
		m_ptBegin.x = ptTempEnd.x;
		m_ptBegin.y = ptTempBegin.y;
		m_ptEnd.x = ptTempBegin.x;
		m_ptEnd.y = ptTempEnd.y;
	}
	else 
	{
		m_ptBegin.x = ptTempBegin.x;
		m_ptBegin.y = ptTempBegin.y;
		m_ptEnd.x = ptTempEnd.x;
		m_ptEnd.y = ptTempEnd.y;
	}
}


bool CRoundedRectEx::Draw(HDC hdc)
{
    HPEN hPen = SetPen(hdc);
    // Update coordinate of RoundedRect
	Setcoordinate();
	//  Move to begin point.
	MoveToEx(hdc, m_ptBegin.x, m_ptBegin.y,0);

	//  Rounded Distance.
	int nRoundDistance;
	nRoundDistance = ((m_ptEnd.x - m_ptBegin.x) > (m_ptEnd.y - m_ptBegin.y))? 
					 (m_ptEnd.x - m_ptBegin.x)/6: (m_ptEnd.y - m_ptBegin.y)/ 6;
	// Draw RoundedRect
    RoundRect(hdc, 
			  m_ptBegin.x, 
			  m_ptEnd.y, 
			  m_ptEnd.x, 
			  m_ptBegin.y, 
			  nRoundDistance, 
			  nRoundDistance);
	//	Giai phong but ve
	ReleasePen(hPen);
    return true;
}