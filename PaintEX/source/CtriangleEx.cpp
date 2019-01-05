#include "StdAfx.h"
#include "CTriangleEX.h"					    //	include file

/******************************************************************
* Method name      : CTriangleEX::CTriangleEX()
* Description    :   Constructor
**********/ 
CTriangleEX::CTriangleEX()					    //	constructor
{
	m_nPattern = MS_TRIANGLE;
}
/******************************************************************
* Method name      : CTriangleEX::Draw()
* Description    :   Draw a triangle 
**********/ 
bool CTriangleEX::Draw(HDC hdc)		
{
	HPEN hPen = SetPen(hdc);
	SetCoordinate();		//	calculate the object's coordinates
	//	Declare a array which has three point elements (POINT type)
	//	this array is only used for the Polygon() function below
	POINT arr_xPt[3];
	arr_xPt[0].x = m_xPt1.x;
	arr_xPt[0].y = m_xPt1.y;
	arr_xPt[1].x = m_xPt2.x;
	arr_xPt[1].y = m_xPt2.y;
	arr_xPt[2].x = m_xPt3.x;
	arr_xPt[2].y = m_xPt3.y;
	Polygon(hdc, arr_xPt, 3);	//	ve tam giac kin 
	//	Giai phong but ve
	ReleasePen(hPen);
	return true;
}
/******************************************************************
* Method name      : CTriangleEX::SelectedTracker()
* Description    :   Check if a point is inside trackers or not
**********/ 
bool CTriangleEX::SelectedTracker(POINTS pt)
{
	POINTS arr_xPt[8];	//	the position of trackers
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
	if	  ((InsideTracker(arr_xPt[0], pt))	// diem chon nam trong tracker TOPLEFT
		||(InsideTracker(arr_xPt[1], pt))	// diem chon nam trong tracker TOPMIDDLE
		||(InsideTracker(arr_xPt[2], pt))	// diem chon nam trong tracker TOPRIGHT
		||(InsideTracker(arr_xPt[3], pt))	// diem chon nam trong tracker RIGHTMIDDLE
		||(InsideTracker(arr_xPt[4], pt))	// diem chon nam trong tracker BOTTOMRIGHT
		||(InsideTracker(arr_xPt[5], pt))	// diem chon nam trong tracker BOTTOMMIDDLE
		||(InsideTracker(arr_xPt[6], pt))	// diem chon nam trong tracker BOTTOMLEFT
		||(InsideTracker(arr_xPt[7], pt)))	// diem chon nam trong tracker LEFTMIDDLE
	{
		return true;	// neu diem chon nam mot trong cac tracker thi return true
	}
	else
		return false;	//	neu khong nam trong tracker nao thi return false
}
/******************************************************************
* Method name      : CTriangleEX::Modify()
* Description    :   move or resize object
**********/ 
bool CTriangleEX::Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd, int nMode)
{
	
	switch(nMode)
	{
	case MR_DRAG:		//	che do Move
		Draw(hdc);		//  xoa doi tuong cu
		DrawSelected(hdc);	//  xoa trackers cua doi tuong cu
		Move(ptSrc, ptEnd);	//  update toa do moi cho doi tuong
		Draw(hdc);			//  ve hinh moi
		DrawSelected(hdc);  //  ve trackers cho hinh moi
		break;
	case MR_NONE:			//  che do khong Move, khog Resize, se khong lam gi ca
		break;
	default:				//	mac dinh la che do Resize
		Draw(hdc);			//  xoa hinh cu
		DrawSelected(hdc);  //  xoa trackers cua hinh cu
		Resize(ptEnd, nMode);  //  update toa doi moi cho doi tuong
		Draw(hdc);			   //  ve hinh moi
		DrawSelected(hdc);     //  ve trackers cho hinh moi 
		break;
	}
	return true;
}
/******************************************************************
* Method name      : CTriangleEX::Rotate()
* Description    :   rotate object
**********/ 
bool CTriangleEX::Rotate(HDC hdc)			
{
	POINTS ptA1, ptB1;
	ptA1.x = (m_ptBegin.x + m_ptEnd.x)/2 - (m_ptEnd.y - m_ptBegin.y)/2;
	ptA1.y = (m_ptBegin.y + m_ptEnd.y)/2 - (m_ptEnd.x - m_ptBegin.x)/2;
	ptB1.x = (m_ptBegin.x + m_ptEnd.x)/2 + (m_ptEnd.y - m_ptBegin.y)/2;
	ptB1.y = (m_ptBegin.y + m_ptEnd.y)/2 + (m_ptEnd.x - m_ptBegin.x)/2;
	if ((ptA1.x >= LEFTOFFSET + m_nPenWidth + SIZERECTBORDER)
		&&(ptA1.y >= TOPOFFSET + m_nPenWidth + SIZERECTBORDER))
	{	
		this->Draw(hdc);					//  xoa hinh ve cu
		this->DrawSelected(hdc);			//  xoa cac tracker hinh ve cu
		m_nDegree = m_nDegree + RD_NINETY;	//  quay toa di 90 do(update toa do moi)
		if (m_nDegree == 4)					//	neu m_nDegree =4 nghia la hinh da quay 360 do thi vong quay tiep theo reset ve 0
		{
			m_nDegree = 0;
		}
		//	update toa do moi cho doi tuong
		m_ptBegin = ptA1;
		m_ptEnd = ptB1;
		this->Draw(hdc);					//  ve hinh moi
		this->DrawSelected(hdc);			//  ve cac tracker cho hinh moi
		return true;
	}
	else
		return true;
}
/******************************************************************
* Method name      : CTriangleEX::DrawSelected()
* Description    :   Draw trackers
**********/ 
void CTriangleEX::DrawSelected(HDC hdc)			
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
	HPEN hPen = CreatePen (PS_DASH, 1, RGB(0, 0, 0)); //  but ve kich thuoc la 1, mau den, net dut
	HPEN hPenOld = (HPEN)SelectObject (hdc, hPen);
	//	thiet lap thuoc tinh trong suot khi vi duong bao
	HGDIOBJ hObjOld;
	hObjOld = SelectObject (hdc, GetStockObject(NULL_BRUSH));
	//	ve duong bao cho doi tuong
	Rectangle
		(
		hdc, 
		arr_xPt[0].x, 
		arr_xPt[0].y, 
		arr_xPt[4].x, 
		arr_xPt[4].y
		);
	//	thiet lap but ve tracker : do rong m_nPenWidth, mau den, net lien
	hPen = CreatePen (PS_SOLID, m_nPenWidth, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject (hdc, hPen);
	//	thiet lap thuoc tinh mau nen khi ve tracker cho doi tuong
	hObjOld = SelectObject (hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(0, 0, 0)); //	nen mau den
	for(int i=0; i<8; i++)			//	Draw 8 trackers
	{
		Rectangle
			(
			hdc, 
			arr_xPt[i].x - m_nPenWidth - SIZERECTBORDER, 
			arr_xPt[i].y - m_nPenWidth - SIZERECTBORDER,
			arr_xPt[i].x + m_nPenWidth + SIZERECTBORDER,
			arr_xPt[i].y + m_nPenWidth + SIZERECTBORDER
			);
	}
	SelectObject(hdc, hObjOld);
	DeleteObject(hObjOld);
	SelectObject(hdc, hPen);
	DeleteObject(hPen);
	DeleteObject(hPenOld);
	DeleteObject(hObjOld);
	m_bSelected = !m_bSelected;
}
/******************************************************************
* Method name      : CTriangleEX::Move()
* Description    :   update coordinates when move object
**********/ 
bool CTriangleEX::Move(POINTS ptSrc, POINTS ptDes)
{
	//	Gan toa do sau khi move
	int nDx, nDy;
	POINTS ptTempBegin = m_ptBegin;
	nDx = ptDes.x - ptSrc.x;
	nDy = ptDes.y - ptSrc.y;
	ptTempBegin.x += (ptDes.x - ptSrc.x);
	ptTempBegin.y += (ptDes.y - ptSrc.y);
	if ((ptTempBegin.x >= LEFTOFFSET + m_nPenWidth + SIZERECTBORDER)
		&& (ptTempBegin.y >= TOPOFFSET + m_nPenWidth + SIZERECTBORDER))
	{
		m_ptBegin.x += nDx; 
		m_ptBegin.y += nDy;
		m_ptEnd.x += nDx; 
		m_ptEnd.y += nDy;
	}

	return false;
}
/******************************************************************
* Method name      : CTriangleEX::Resize()
* Description    :   update coordinates when resize object
**********/ 
bool CTriangleEX::Resize(POINTS pt, int numTracker)
{
	int nSpace = 4*(m_nPenWidth + SIZERECTBORDER);	//	han che khoang cach resize toi cac cacnh cua duong bao
	if ((pt.x >= LEFTOFFSET + m_nPenWidth + SIZERECTBORDER)
		&&(pt.y >= TOPOFFSET + m_nPenWidth + SIZERECTBORDER))
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
				m_ptEnd.x = pt.x;	//  update hoanh do cua diem End
				m_ptBegin.y = pt.y;	//  update tung do cua diem Begin
			}
			break;
		case MR_RIGHTMIDDLE:
			if (pt.x >= m_ptBegin.x + nSpace)
			{	
				m_ptEnd.x = pt.x; //  update hoanh do cua diem End
			}
			break;
		case MR_BOTTOMRIGHT:
			if ((pt.x >= m_ptBegin.x + nSpace)&&(pt.y >= m_ptBegin.y + nSpace))
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
* Method name      : CTriangleEX::InsideTracker()
* Description    :   Check if a point is inside trackers or not
**********/ 
bool CTriangleEX::InsideTracker(POINTS ptTracker, POINTS pt)
{
	if   ((pt.x >= ptTracker.x - m_nPenWidth - SIZERECTBORDER) //  the hien su co gian do lon tracker theo do rong but ve
		&&(pt.x <= ptTracker.x + m_nPenWidth + SIZERECTBORDER)
		&&(pt.y <= ptTracker.y + m_nPenWidth + SIZERECTBORDER)
		&&(pt.y >= ptTracker.y - m_nPenWidth - SIZERECTBORDER))
		return true;
	else
		return false;
}
/****************************************************************** 
* Method name      : CTriangleEX::IsSelected()
* Description    :   Check if a point is inside object or not
**********/ 
int	 CTriangleEX::IsSelected(POINTS pt)
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
	this->SetCoordinate(); //  lenh nay chu yeu dung de phuc vu cho ham InsideTriangle() ben duoi day
	if(InsideTracker(arr_xPt[0],pt)) //	neu diem chon nam trong tracker TOPLEFT
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //  doi bieu tuong chuot 
		return MR_TOPLEFT;	//	Tra ve gi tri MR_TOPLEFT
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
