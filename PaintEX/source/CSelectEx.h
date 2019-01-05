#pragma once
#include "CShapeEX.h"
#ifndef CSELECT_H
#define CSELECT_H
class CSelectEx : public CShapeEX
{
public:
	/********** Following by constructor and distructor functions **********/
	CSelectEx();
	/********** Following by main functions of this class**********/
	bool Draw(HDC hdc);									// Ham thuc hien chuc nang ve 
	int IsSelected(POINTS pt);							// Kien tra	toa do cua con tro hien tai	co nam trong duong bao
	bool Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd, int nMode);	//	Ham thuc hien chuc move cho doi tuong CSelectEx	
	void Set();		//Dat toa do mac dinh cho hinh bao
	bool IsEmpty();
private:
	
	
};
#endif