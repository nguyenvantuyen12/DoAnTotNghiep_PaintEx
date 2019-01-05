#pragma once
#include <string>
#include <stdio.h>
#include "CShapeEX.h"
using namespace std;
class CTextEx : public CShapeEX
{
public:
	BOOL  m_tfFontLoaded;
	HFONT m_hfFont;
	int m_width;		//	do rong cua mot ky tu
	LOGFONT m_lfFontText;	//	Luu giu kieu font, do lon font chu
public:
	CTextEx();
	void SetStrBuff(TCHAR);
	TCHAR* GetText();
	bool Draw(HDC);
	int IsSelected(POINTS);
	bool WriteText(HDC,COLORREF);
	void SetFormat(UINT);
	void Resize(POINTS, int);
	bool Move(POINTS, POINTS);
	bool Modify(HDC , POINTS , POINTS ,int );
	void DrawSelected(HDC );
	bool EraseString(int);
	void SetCoordinate();
	void ChoseFont( HWND );
	bool Rotate(HDC);
	void SetFont();	//	thiet lap dinh dang font cho text duoc viet ra
};