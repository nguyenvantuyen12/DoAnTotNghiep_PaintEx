#ifndef CSHAPEEX_H
#define CSHAPEEX_H
#define  TICKERLEVEL2 20
#define TOPOFFSET 71
#define LEFTOFFSET 20
#define SIZERECTBORDER 3
#define LIMIT (4 * (m_nPenWidth + SIZERECTBORDER ))	//	Gioi han chan kich thuoc nho nhat cua HCN
extern enum MODE_SHAPEEX //	Dinh nghia enum cac pattern Shape su dung trong chuong trinh
{
	MS_CIRCLE = 0,
	MS_LINE = 3,
	MS_RECT,
	MS_TRIANGLE = 7,
	MS_RIGHT_TRIANGLE = 9,
	MS_ROUNDED_RECTANGLE = 11,
	MS_TEXT = 13,
	MS_SELECTED,
	MS_MULTISELECTED,

};

extern enum ROTATE_DEGREE	// Dinh nghia enum cac goc quay cua Shape
{
	RD_NONE = 0,
	RD_NINETY,
	RD_ONE_HUNDRED_AND_EIGHTY,
	RD_TWO_HUNDRED_AND_SEVENTY
};

extern enum PEN_WIDTH	//	Dinh nghia cac level do rong cua Pen: Su dung 5 muc
{
	PW_ONE = 1,
	PW_TWO,
	PW_THREE,
	PW_FOUR,
	PW_FIVE 
};

extern enum MODE_EDIT		//	Dinh nghia cac mode khi edit cac Shape 
{
	MR_NONE = 0,		
	MR_DRAG,			//	Xay ra khi move tinh tien object
	MR_TOPLEFT,			//	Dieu chinh kich thuoc object 
	MR_TOPMIDDLE,
	MR_TOPRIGHT,
	MR_LEFTMIDDLE,
	MR_RIGHTMIDDLE,
	MR_BOTTOMLEFT,
	MR_BOTTOMMIDDLE,
	MR_BOTTOMRIGHT
};
#include <string>
#include <stdio.h>
using namespace std;
class CShapeEX
{
public:
	CShapeEX();
	HPEN SetPen(HDC &hdc);
	void ReleasePen(HPEN hPen);
	bool IsEmpty();
	virtual bool Draw(HDC hdc);												//	Ve Object
	virtual bool Rotate(HDC hdc);	
	//IsSelected tra ve kieu int la mot trong cac tracker
	virtual int IsSelected(POINTS pt);			//	Kiem tra 1 diem pt co thuoc Object	
	virtual bool Modify (HDC hdc, POINTS ptSrc, POINTS ptDes, int nMode);	
	virtual void DrawSelected(HDC hdc);	//	Ve cac tracker khi nhap chuot hay khi tha chuot 

	//-----Declare funtion for CTextEx 
	virtual void SetStrBuff(TCHAR);								// Day ky tu vao bo dem
	virtual bool WriteText(HDC, COLORREF );								// Viet text ra HDC
	virtual bool EraseString(int);									// Xoa ky tu
	virtual void SetFormat(UINT);                               // Dinh dang cho Text ( can trai, can phai, can giua)
	virtual void ChoseFont( HWND  )	;							// Ham goi dialog FOnts 
	//---------------------------------							

public:
	POINTS m_ptBegin;		 					
	POINTS m_ptEnd;			
public:
	int m_nDegree;	//  goc quay doi tuong
	bool m_bFilled;	//	co xac dinh co fill mau hay la khong	
	int m_nPenWidth;	//  do rong but
	DWORD m_dwPenStyle;	//	kieu but
	COLORREF m_crBrushColor;	//  mau nen doi tuong
	COLORREF m_crPenColor;	//	mau but
	UINT m_uFormat;			//	xac dinh dinh dang cua Text
	int m_nPattern;			//	bien xac dinh dang doi tuong la gi
	bool m_bSelected;	//	Co xac dinh doi tuong dang duoc chon cho viec Edit
	bool m_bBoundLine;	//	co xac dinh duong bao cua doi tuong co duoc ve hay ko
	COLORREF m_crTextColor;	//	mau cua text viet ra
	string m_strBuffer;		//	Chuoi text nhap vao tu ban phim
};
#endif