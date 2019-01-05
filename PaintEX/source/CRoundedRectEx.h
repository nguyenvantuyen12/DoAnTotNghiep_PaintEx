#include "CShapeEX.h"
#ifndef CROUNDEDRECTEX_H
#define CROUNDEDRECTEX_H

#define SIZERECTTRACKER(m_nPenWidth) (m_nPenWidth+3)			// The size of tracker rectangles

  
class CRoundedRectEx : public CShapeEX
{

public:

	CRoundedRectEx();
	int IsSelected(POINTS pt); 
	bool Draw(HDC hdc);
	bool Modify(HDC hdc, POINTS ptSrc, POINTS ptDes, int nMode) ;// Move && Resize
	bool Rotate(HDC hdc);
private:
	
	void DrawSelected(HDC hdc);	
	bool Move(POINTS ptSrc, POINTS ptDes);
	bool Resize(POINTS point, int nNumTracker);
	void Setcoordinate();								//	Set the coordinate for a RoundRectangle before draw
};

#endif