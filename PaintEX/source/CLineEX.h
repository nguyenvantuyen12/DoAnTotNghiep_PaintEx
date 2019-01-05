#ifndef CLINEEX_H
#define CLINEEX_H

#include "CShapeEX.h"

class CLineEX:public CShapeEX
{
public:
	CLineEX();	
	virtual bool Draw(HDC hdc);	//Xay dung ham ve doi tuong
	virtual int IsSelected(POINTS pt); 
	virtual bool Modify (HDC hdc, POINTS ptSrc, POINTS ptDes, int nMode);//Move && Resize	
	virtual bool Rotate(HDC hdc);
	void DrawSelected(HDC hdc);	//Ve cac tracker	
private:	
	bool Move(POINTS ptSrc, POINTS ptDes);
	bool Resize(POINTS point, int numTracker);
	int	 IsSelectedTracker(POINTS pt);	
	bool Rotate(int degree);	
};

#endif