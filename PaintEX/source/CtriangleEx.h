#pragma once
#ifndef CTriangleEX_H
#define CTriangleEX_H
#include <math.h>
#include "CShapeEX.h"
class CTriangleEX:public CShapeEX				//	Class name declaration
{
private:
	POINTS m_xPt1, m_xPt2, m_xPt3;				//	the triangle's three peaks
public:
	CTriangleEX();								//	Constructor				
	bool Draw(HDC hdc);							//	y dung ham ve doi tuong
	int IsSelected(POINTS);			        //	Check if the selected point is inside object or not
	bool Modify (HDC, POINTS, POINTS, int);
	bool Rotate(HDC);					        //	Rotate function: Update new object's coordinates
	void DrawSelected(HDC hdc);			        //	Ve cac tracker
private:
	bool Move(POINTS ptSrc, POINTS ptDes);
	bool Resize(POINTS point, int numTracker);
	bool SelectedTracker(POINTS pt);
	bool InsideTracker(POINTS ptTracker, POINTS pt);
	//  FUNCTION: SetCoordinates()
	//  PURPOSE: Calculate the triangle's coordinates
	void SetCoordinate()
	{
		int nMode = m_nDegree%4;
		POINTS ptTemp;
		POINTS ptTemp1, ptTemp2;
		//	update lai toa do khi : draw theo huong: bottom right -> top left
		if((m_ptBegin.x > m_ptEnd.x)&&(m_ptBegin.y > m_ptEnd.y))
		{
			ptTemp = m_ptBegin;
			m_ptBegin = m_ptEnd;
			m_ptEnd = ptTemp;
		}
		//	update lai toa do khi : draw theo huong: bottom left -> top right
		if ((m_ptBegin.x < m_ptEnd.x)&&(m_ptBegin.y > m_ptEnd.y))
		{
			ptTemp1.x = m_ptBegin.x;
			ptTemp1.y = m_ptEnd.y;
			ptTemp2.x = m_ptEnd.x;
			ptTemp2.y = m_ptBegin.y;
			m_ptBegin = ptTemp1;
			m_ptEnd = ptTemp2;
		}
		//	update lai toa do khi : draw theo huong: top right -> bottom left 
		if ((m_ptBegin.x > m_ptEnd.x)&&(m_ptBegin.y < m_ptEnd.y))
		{
			ptTemp1.x = m_ptEnd.x;
			ptTemp1.y = m_ptBegin.y;
			ptTemp2.x = m_ptBegin.x;
			ptTemp2.y = m_ptEnd.y;
			m_ptBegin = ptTemp1;
			m_ptEnd = ptTemp2;
		}
		//	mac dinh ve doi tuong theo huong : top left -> bottom right
		switch(nMode)
		{
		case 0:
			m_xPt1.x =(SHORT)(m_ptEnd.x + m_ptBegin.x)/2;
			m_xPt1.y = m_ptBegin.y;
			m_xPt2.x = m_ptEnd.x;
			m_xPt2.y = m_ptEnd.y;
			m_xPt3.x = m_ptBegin.x;
			m_xPt3.y = m_ptEnd.y;
			break;
		case 1:
			m_xPt1.x = m_ptBegin.x;
			m_xPt1.y = (SHORT)(m_ptBegin.y + m_ptEnd.y)/2;
			m_xPt2.x = m_ptEnd.x;
			m_xPt2.y = m_ptBegin.y;
			m_xPt3.x = m_ptEnd.x;
			m_xPt3.y = m_ptEnd.y;
			break;
		case 2:
			m_xPt1.x =(SHORT)(m_ptEnd.x + m_ptBegin.x)/2;
			m_xPt1.y = m_ptEnd.y;
			m_xPt2.x = m_ptBegin.x;
			m_xPt2.y = m_ptBegin.y;
			m_xPt3.x = m_ptEnd.x;
			m_xPt3.y = m_ptBegin.y;
			break;
		case 3:
			m_xPt1.x = m_ptEnd.x;
			m_xPt1.y = (SHORT)(m_ptBegin.y + m_ptEnd.y)/2;
			m_xPt2.x = m_ptBegin.x;
			m_xPt2.y = m_ptBegin.y;
			m_xPt3.x = m_ptBegin.x;
			m_xPt3.y = m_ptEnd.y;
			break;
		}
	}
	//	FUNCTION : InsideTriangle()
	//	PURPOSE  :Check if a point is inside a triangle or not
	bool InsideTriangle(POINTS pt)
	{
		float dbA1,dbA2,dbA3,dbB1,dbB2,dbB3,dbC1,dbC2,dbC3;
		//	he so duong thang tao boi 2 diem m_xPt1 toi m_xPt2
		dbA1 = float((m_xPt2.y - m_xPt1.y));
		dbB1 = float((m_xPt1.x - m_xPt2.x));
		dbC1 = float((m_xPt1.y*m_xPt2.x - m_xPt1.x*m_xPt2.y));
		//	he so duong thang tao boi 2 diem m_xPt2 toi m_xPt3
		dbA2 = float((m_xPt3.y - m_xPt2.y));
		dbB2 = float((m_xPt2.x - m_xPt3.x));
		dbC2 = float((m_xPt2.y*m_xPt3.x - m_xPt2.x*m_xPt3.y));
		//	he so duong thang tao boi 2 diem m_xPt3 toi m_xPt1
		dbA3 = float((m_xPt1.y - m_xPt3.y));
		dbB3 = float((m_xPt3.x - m_xPt1.x));
		dbC3 = float((m_xPt3.y*m_xPt1.x - m_xPt3.x*m_xPt1.y));

		float dbValue1,dbValue2,dbValue3, dbValue1Pt,dbValue2Pt,dbValue3Pt;
		//	gia tri cua cac dinh tam giac tai cac duong thang co he so noi tren
		dbValue1 = dbA1*m_xPt3.x + dbB1*m_xPt3.y + dbC1;
		dbValue2 = dbA2*m_xPt1.x + dbB2*m_xPt1.y + dbC2;
		dbValue3 = dbA3*m_xPt2.x + dbB3*m_xPt2.y + dbC3;
		//	gia tri cua diem pt tai cac duong thang co he so noi tren
		dbValue1Pt = dbA1*pt.x + dbB1*pt.y + dbC1;
		dbValue2Pt = dbA2*pt.x + dbB2*pt.y + dbC2;
		dbValue3Pt = dbA3*pt.x + dbB3*pt.y + dbC3;

		if ((dbValue1*dbValue1Pt >= 0)
			&&(dbValue2*dbValue2Pt >= 0)
			&&(dbValue3*dbValue3Pt >= 0))
		{
			return true;
		}
		else return false;
	}
};
#endif
