#include "CShapeEX.h"
#ifndef CGRIDEX_H
#define CGRIDEX_H						
#define  OFFSET 20						
#define  TOPRULER 51					
#define  LEFTRULER 0	
class CGridEX{
public:
	int m_nGridWidth;
	int m_nGridHeigh;
	POINT m_pLastPos;			
	bool m_bFilled;				
	int m_nPenWidth;
	DWORD m_dwPenStyle;
	COLORREF m_crCursorColor;
	COLORREF m_crPenColor;
public:
	CGridEX();
	bool ShowGridView(HWND);
	void Enable();
	void Disable();
};

#endif