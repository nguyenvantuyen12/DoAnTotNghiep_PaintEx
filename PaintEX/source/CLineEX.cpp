/******************************************************************
 * Description  : Tao class CLineEx voi cac attribute va cac method can thiet
*****/

#include "stdafx.h"
#include "CLineEX.h"
#include "math.h"
#define EPSILON 5 //Sai so cho phep
//-----------------------------------------------------
bool Move(POINTS ptSrc, POINTS ptDes);
bool Resize(POINTS point, int numTracker);
int	 IsSelectedTracker(POINTS pt);	
void Tracker(POINTS pt, HDC hdc, int pensize);
//--------------Cac phuong thuc visual tu lop cha-----------------------------
/******************************************************************************
* bool CLineEX::Draw(HDC hdc)
* Description : Ham ve DT theo toa do Begin va End.
*****************************************************************************/
bool CLineEX::Draw(HDC hdc)
{	
	HPEN hPen = SetPen(hdc);
	MoveToEx ( hdc, m_ptBegin.x, m_ptBegin.y, NULL );
	LineTo ( hdc, m_ptEnd.x, m_ptEnd.y );	
	////	Giai phong but ve
	ReleasePen(hPen);
	return false;
}
/******************************************************************************
* CLineEX::IsSelected(POINTS pt)
* Description : Tra ve gia tri cua tracker dang chua diem pt truyen vao
*****************************************************************************/

int CLineEX::IsSelected(POINTS pt)
{	
	int nTracker;
	//SetCursor(LoadCursor(NULL, IDC_ARROW));
	nTracker = IsSelectedTracker(pt);		
	if (nTracker > 1) return nTracker;
	//Kiem tra dieu kien diem do co nam trong vung duoc xet khong
	bool flag = false;
	if ((((pt.x - m_ptBegin.x )*(pt.x - m_ptEnd.x )) < 0)&&
		(((pt.y - m_ptBegin.y )* (pt.y - m_ptEnd.y )) < 0))
	{ 
		flag = true;	
	}
	else 
		return false;
	long lCoefA,lCoefB,lCoefC; //Luu cac he so duong thang	
	lCoefA = m_ptEnd.y - m_ptBegin.y;
	lCoefB = m_ptBegin.x - m_ptEnd.x;
	lCoefC = m_ptEnd.x * m_ptBegin.y - m_ptBegin.x * m_ptEnd.y;

	//Tinh khoang cach tu diem toi duong thang
	double dDistance;
	dDistance = abs(lCoefA * pt.x + lCoefB * pt.y + lCoefC)/sqrt(float((lCoefA * lCoefA + lCoefB * lCoefB)));
	if (((dDistance <= EPSILON)&&(flag)))
	{	
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));		
		return MR_DRAG;		
	}
	return 0;
}

/******************************************************************************
* void CLineEX::DrawSelected(HDC hdc)
* Description : Ve 8 trackers cho DT khi DT duoc selected
*****************************************************************************/
void CLineEX::DrawSelected(HDC hdc)
{	
	//Thiet lap but ve

	HPEN hPen = CreatePen (PS_SOLID,  m_nPenWidth , RGB(0, 0, 0));				// but mau den, net lien
	SelectObject (hdc, hPen);
	HGDIOBJ hObjOld;
	hObjOld = SelectObject (hdc, GetStockObject(DC_BRUSH));		
	SetDCBrushColor(hdc, RGB(0, 0, 0));							// to mau den cho tracker
	int pensize;
	pensize = m_nPenWidth + SIZERECTBORDER;
	//Ve Tracker
	Tracker(m_ptBegin, hdc, pensize);
	Tracker(m_ptEnd, hdc, pensize);
	m_bSelected = !m_bSelected;
	DeleteObject(hPen);

}
/******************************************************************************
* bool CLineEX::Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd, int nMode)
* Description : Ham thuc hien viec Resize va Move DT dua vao cac tham so dau vao
*****************************************************************************/
bool CLineEX::Modify (HDC hdc,POINTS ptSrc, POINTS ptDes, int nMode)
{		
	if (nMode == MR_DRAG)
	{			
		Draw(hdc);
		this ->DrawSelected(hdc);		
		Move(ptSrc,ptDes);		
		Draw(hdc);	
		this ->DrawSelected(hdc);		
		return true;
	}
	else
	{			
		this ->DrawSelected(hdc);
		Draw(hdc);
		Resize(ptDes, nMode);		
		this ->DrawSelected(hdc);
		Draw(hdc);
		return true;
	}
}
/******************************************************************************
* bool CLineEX::Rotate(HDC hdc)
* Description : Ham thuc hien viec quay DT
*****************************************************************************/
bool CLineEX::Rotate(HDC hdc)
{ 	
	double dDistance; 
	POINTS PtAfter[2];	//luu toa do sau khi Rotate
	//-------------------- Tinh do dai duong thang
	dDistance = sqrt(float(pow(float(m_ptBegin.x - m_ptEnd.x),2)+ pow(float(m_ptBegin.y - m_ptEnd.y),2)));
	//-------------------- Tinh goc quay
	double cosAl = (float(m_ptBegin.y - m_ptEnd.y))/dDistance;
	double sinAl = (float(m_ptBegin.x - m_ptEnd.x))/dDistance;
	//-------------------- Tinh toa do trung diem
	POINTS ptMiddle;
	ptMiddle.x = (m_ptBegin.x + m_ptEnd.x)/2;
	ptMiddle.y = (m_ptBegin.y + m_ptEnd.y)/2;
	//-------------------- Gan toa do sau khi quay
	PtAfter[0].x = ptMiddle.x - (int)( dDistance/2 * cosAl);
	PtAfter[0].y = ptMiddle.y + (int)(dDistance/2 * sinAl);
	PtAfter[1].x = 2 * ptMiddle.x - PtAfter[0].x;
	PtAfter[1].y = 2 * ptMiddle.y - PtAfter[0].y;
	//-------------------- Gan lai toa do duong thang
	this ->DrawSelected(hdc);
	Draw(hdc);
	if (((PtAfter[1].x >= (LEFTOFFSET + m_nPenWidth + SIZERECTBORDER)) 
		&& (PtAfter[1].y >= (TOPOFFSET+ m_nPenWidth + SIZERECTBORDER)))
		&&((PtAfter[0].x >= (LEFTOFFSET+ m_nPenWidth + SIZERECTBORDER)) 
		&& (PtAfter[0].y >= (TOPOFFSET+ m_nPenWidth + SIZERECTBORDER))))
	{
		m_ptBegin = PtAfter[0];
		m_ptEnd = PtAfter[1];
	}	
	Draw(hdc);
	this ->DrawSelected(hdc);
	return false;
}

//------------------Cac ham private chi su dung trong lop con----------------------
/******************************************************************************
* Method name : CLineEX::CLineEX()
* Description : Ham tao co class CLineEX. Thuc hien khoi tao cac thuoc tinh cho lop CLineEX
*****************************************************************************/
CLineEX::CLineEX()
{	
	m_nPattern = MS_LINE;
}

/******************************************************************************
* int CLineEX::IsSelectedTracker(POINTS pt)
* Description : Tra ve gia tri cua tracker dang chua diem pt truyen vao
*****************************************************************************/
int CLineEX::IsSelectedTracker(POINTS pt)
{	
	double dDistance; 
	//Xet con tro chuot co chon tai diem ptBegin
	dDistance = (int)sqrt(float(((pt.x - m_ptBegin.x)*(pt.x - m_ptBegin.x)+(pt.y - m_ptBegin.y )*(pt.y - m_ptBegin.y))));
	if (dDistance <= EPSILON)
	{	
		SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		return MR_TOPLEFT;
	}
	//Xet con tro chuot co chon tai diem ptEnd
	dDistance = (int)sqrt(float(((pt.x - m_ptEnd.x)*(pt.x - m_ptEnd.x)+(pt.y - m_ptEnd.y )*(pt.y - m_ptEnd.y))));
	if (dDistance <= EPSILON)
	{	
		SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		return MR_BOTTOMRIGHT;
	}	
	return MR_DRAG;
}
/******************************************************************************
* void Tracker(POINTS pt, HDC hdc, int pensize)
* Description : Ve hinh chu nhat tracker voi tam la pt kich thuoc truyen vao la pensize
*****************************************************************************/
void Tracker(POINTS pt, HDC hdc, int pensize)
{
	Rectangle(hdc, pt.x - pensize, pt.y - pensize, pt.x + pensize, pt.y + pensize);
}

/******************************************************************************
* void CLineEX::Move(POINTS ptSrc, POINTS ptDes)
* Description : Ham thuc hien viec Move 1 doi tuong DT dua vao tham so dau vao
*****************************************************************************/
bool CLineEX::Move(POINTS ptSrc, POINTS ptDes) 
{	
	POINTS PtAfter[2];	//luu toa do sau khi Move	
	// Gan toa do sau khi move
	PtAfter[0].x = m_ptBegin.x + ptDes.x - ptSrc.x;
	PtAfter[0].y = m_ptBegin.y + ptDes.y - ptSrc.y;
	PtAfter[1].x = m_ptEnd.x + ptDes.x - ptSrc.x;
	PtAfter[1].y = m_ptEnd.y + ptDes.y - ptSrc.y;
	if (((PtAfter[1].x >= (LEFTOFFSET+ m_nPenWidth + SIZERECTBORDER)) 
		&& (PtAfter[1].y >= (TOPOFFSET+ m_nPenWidth + SIZERECTBORDER)))
		&&((PtAfter[0].x >= (LEFTOFFSET+ m_nPenWidth + SIZERECTBORDER)) 
		&& (PtAfter[0].y >= (TOPOFFSET+ m_nPenWidth + SIZERECTBORDER))))
	{
		m_ptBegin = PtAfter[0] ;
		m_ptEnd = PtAfter[1] ;
	}
	return true;
}
/******************************************************************************
* void CLineEX::Resize(POINTS point, int nMode)
* Description : Ham thuc hien chuc nang Resize DT dua vao chuc nang truyen vao tu tham so 
dau vao va toa do hien tai
*****************************************************************************/
bool CLineEX::Resize(POINTS point, int numTracker)
{	
	switch(numTracker) 
	{
	case MR_TOPLEFT: 
		if ((point.x >= (LEFTOFFSET + m_nPenWidth + SIZERECTBORDER)) 
			&& (point.y >= (TOPOFFSET+ m_nPenWidth + SIZERECTBORDER)))
		//m_ptBegin = m_ptEnd;
		{
			m_ptBegin = point;
		}	
		if ((point.x - m_ptEnd.x)*(point.y - m_ptEnd.y)<0)
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		}		 		
		return true;		
	case MR_BOTTOMRIGHT: 
		if ((point.x >= (LEFTOFFSET + m_nPenWidth + SIZERECTBORDER)) 
			&& (point.y >= (TOPOFFSET+ m_nPenWidth + SIZERECTBORDER)))
		{
			m_ptEnd = point;
		}
		if ((point.x - m_ptBegin.x)*(point.y - m_ptBegin.y)<0)		
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW));			
		}		
		return true;
	}	
	return false;
}