#pragma once
#include "CShapeEX.h"
#ifndef CRECTANGLEEX_H
#define CRECTANGLEEX_H
class CRectangleEx : public CShapeEX
{
public:
/********** Following by constructor and distructor functions **********/
	CRectangleEx();
/********** Following by main functions of this class**********/
	bool Draw(HDC hdc);									// Ham thuc hien chuc nang ve 
	int IsSelected(POINTS pt);							//	Ham ve thay doi icon cua con chuot, tham so dau vao la gia tri
														//	toa do cua con tro hien tai
	bool Rotate(HDC hdc);								//	Ham thuc hien xoay HCN 1 goc cho truoc
	bool Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd, int nMode);	//	Ham thuc hien chuc resize hoac move cho doi tuong CRectangle
	void DrawSelected(HDC hdc);							//	Ham ve cac trackers cua doi tuong
	void Move(POINTS ptSrc, POINTS ptDes);				//	Ham di chuyen 1 object voi 2 tham so truyen vao la toa do diem dau va cuoi
	void Resize(POINTS pt, int nMode);					//	Ham thuc hien viec resize doi tuong
private:
	void DeleteTracker(HDC hdc);						//	Ham xoa cac trackers cua doi tuong
	void SetCoordinate();								//	Set the coordinate for a Rectangle before draw
};
#endif