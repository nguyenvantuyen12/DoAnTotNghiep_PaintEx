#ifndef CCIRCLEEX_H
#define CCIRCLEEX_H
#include "CShapeEX.h"
#define SIZESQUAREBORDER 3			// Kich co cua tracker hinh vuong
#define LIMITBORDER (4 * (m_nPenWidth + SIZESQUAREBORDER )) // Dung de ve hinh tron nho nhat khi resize.
class CCircleEX : public CShapeEX
{
public:
	CCircleEX();
	int IsSelected(POINTS pt); //	Tra ve vi tri nhap chuot o vung nao, trackers, hinh tron hay o ngoai.
	bool Draw(HDC hdc); //	Ham ve hinh tron
	bool Modify(HDC hdc, POINTS ptSrc, POINTS ptEnd, int nMode);	//	Ham thuc hien chuc resize hoac move cho doi tuong
	bool Rotate(HDC hdc); // Thuc hien thao tac quay ( khong lam voi hinh tron).
	void DrawSelected(HDC hdc);	//Ve cac tracker.
private:
	bool Move(POINTS ptSrc, POINTS ptDes); //	Di chuyen hinh tron theo su di chuyen cua chuot.
	bool Resize(POINTS pt, int nNumTracker); //	Thay doi kich thuoc cua hinh tron.
	bool CheckPointInRect(POINTS ptTracker, POINTS pt); //	Kiem tra mot diem co thuoc mot hinh vuong hay khong
	bool CheckPointInCircle (int ptBegin_x, int ptBegin_y, int ptEnd_x, int ptEnd_y, POINTS pt);//	Kiem tra mot diem nam trong hay ngoai mot hinh tron.
	//int	 IsSelectedTracker(POINTS pt); //	Xac dinh xem diem pt o vung tracker nao
	int CalculateDistance (POINTS pt1, POINTS pt2); //	Tinh toan khoang cach giua 2 diem
	bool MinDistance (POINTS ptTracker, POINTS pt); //	Xac dinh xem k/c tu 1 diem den tracker nao gan nhat.
};
#endif