#ifndef RULER_H
#define RULER_H

//Kieu ve thuoc: Thuoc ngang, thuoc doc
enum TYPERULER{RT_VERTICAL,RT_HORIZONTAL};			
//Cac loai vach tren Ruler: vach ngan, vach trung binh, vach dai
//Khoang cach giua hai vach tren Ruler
enum TYPETICKER{MIN,MEDIUM,MAX};	

#define  TICKERLEVEL1(xN) (5 * xN)					//Hai vach ngan cach nhau 5 pixel		
#define  TICKERLEVEL2(xN) (20 * xN)				//Hai vach trung binh cach nhau 20 pixel		
#define  TICKERLEVEL3(xN) (100 * xN)				//Hai vach dai cach nhau 100 pixel
//Chieu cao cua cac vach tren Ruler	
#define  HEIGHT1 5						
#define  HEIGHT2 10						
#define  HEIGHT3 20							

//Tham so cua Ruler
#define  OFFSET 20						
#define  TOPRULER 51					
#define  LEFTRULER 0					

//Lop CRulerEX 
class CRulerEX{ 
private:
	POINT m_pLastPos;			
	bool m_bFilled;				
	int m_nPenWidth;
	DWORD m_dwPenStyle;
	
	COLORREF m_crPenColor;
private:
	void DrawTicker(HWND hWnd,TYPERULER typeRuler=RT_HORIZONTAL,TYPETICKER typeUnit=MIN, int nN = 1);
	void SetPLastPos(POINT cursor);
public:
	COLORREF m_crCursorColor;
	CRulerEX();	
	~CRulerEX();
	void ShowRuler(HWND hWnd, int xN);		
	void DrawCursorPosition(HWND hWnd,LPARAM lparam);
	void Disable();
	void Enable();
};

#endif