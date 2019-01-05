#include "stdafx.h"
#include "CRulerEX.h"

//Ham tao CRulerEX
CRulerEX::CRulerEX(){
	m_pLastPos.x = 0;
	m_pLastPos.y = 0;
	m_bFilled = true;				
	m_nPenWidth = 1;
	m_dwPenStyle = PS_SOLID;
	m_crCursorColor = RGB(255,0,0);
	m_crPenColor = RGB(0,0,0);
}
CRulerEX::~CRulerEX(){

}

//Enable Ruler
void CRulerEX::Enable(){
	m_pLastPos.x = 0;
	m_pLastPos.y = 0;
	m_bFilled = true;				
	m_nPenWidth = 1;
	m_dwPenStyle = PS_SOLID;
	m_crCursorColor = RGB(255, 0, 0);
	m_crPenColor = RGB(0, 0, 0);
}

void CRulerEX::Disable(){
	m_pLastPos.x = 0;
	m_pLastPos.y = 0;
	m_bFilled = true;				
	m_nPenWidth = 1;
	m_dwPenStyle = PS_SOLID;
	m_crCursorColor = RGB(255,255,255);
	m_crPenColor = RGB(255,255,255);	
}
//Phuong thuc dat vi tri cua con tro tren Ruler
void CRulerEX::SetPLastPos(POINT cusor){
	m_pLastPos= cusor;
}
//Phuong thuc ve vach tren Ruler
void CRulerEX::DrawTicker(HWND hWnd,TYPERULER typeRuler,TYPETICKER typeTicker, int xN){

	//Xac dinh cua so lam viec
	HDC hdc = GetDC(hWnd);
	RECT clientRect;
	HFONT font;
	LOGFONT LogFont;
	SetTextColor(hdc,m_crPenColor);
	GetClientRect(hWnd,&clientRect);

	//Xac dinh tham so cua Ruler
	int nSize = (typeRuler==RT_HORIZONTAL)?clientRect.right:clientRect.bottom;
	int tickerMin = TICKERLEVEL1(xN);
	int tickerHeight = HEIGHT1;
	switch (typeTicker){
	case MIN:
		tickerMin = TICKERLEVEL1(xN);
		tickerHeight = HEIGHT1;
		break;
	case MEDIUM:
		tickerMin = TICKERLEVEL2(xN);
		tickerHeight = HEIGHT2;
		break;
	case MAX:
		tickerMin = TICKERLEVEL3(xN);
		tickerHeight = HEIGHT3;
	default:
		break;
	}
	//Xac dinh so luong vach tren Ruler
	int nCountMax = (int)(nSize/tickerMin);
	int nCount;
	HPEN hPen = CreatePen (m_dwPenStyle, m_nPenWidth, m_crPenColor);
	HPEN hPenOld = (HPEN)SelectObject (hdc, hPen);
	//Ve cac vach ngang tren Ruler
	if (typeRuler==RT_HORIZONTAL){
		LogFont.lfStrikeOut = 0;
		LogFont.lfUnderline = 0;
		LogFont.lfHeight = 12;
		LogFont.lfEscapement = 0;
		LogFont.lfItalic = false;
		font = CreateFontIndirect(&LogFont);

		SelectObject(hdc,font);	

		for (nCount=0;nCount<=nCountMax;nCount++){			
			Rectangle(hdc,LEFTRULER+OFFSET+nCount*tickerMin,TOPRULER+OFFSET-
				tickerHeight,LEFTRULER+OFFSET+nCount*tickerMin+1,TOPRULER+OFFSET);		
		if (xN < 3)
		{
			if (tickerMin == TICKERLEVEL3(xN))
			{

				switch(nCount){
				case 0:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin+2,
						TOPRULER+OFFSET-15,(LPCSTR)("0"),1);
					break;
				case 1:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("100"),3);
					break;
				case 2:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("200"),3);
					break;
				case 3:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("300"),3);
					break;
				case 4:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("400"),3);
					break;
				case 5:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("500"),3);
					break;
				case 6:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("600"),3);
					break;
				case 7:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("700"),3);
					break;
				case 8:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("800"),3);
					break;
				case 9:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("900"),3);
					break;
				case 10:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("1000"),4);
					break;
				case 11:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER + OFFSET -15,(LPCSTR)("1100"),4);
					break;
				case 12:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER + OFFSET - 15,(LPCSTR)("1200"),4);
					break;
				case 13:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("1300"),4);
					break;
				case 14:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("1400"),4);
				case 15:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("1500"),4);
				case 16:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("1600"),4);
				case 17:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("1700"),4);
					break;
				case 18:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("1800"),4);
					break;
				case 19:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("1900"),4);
					break;
				default:
					break;						
				}

			}
		}
		else
		{
			if (tickerMin == TICKERLEVEL2(xN))
			{

				switch(nCount){
				case 0:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin+2,
						TOPRULER+OFFSET-15,(LPCSTR)("0"),1);
					break;
				case 1:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("20"),3);
					break;
				case 2:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("40"),3);
					break;
				case 3:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("60"),3);
					break;
				case 4:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("80"),3);
					break;
				case 5:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("100"),3);
					break;
				case 6:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("120"),3);
					break;
				case 7:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("140"),3);
					break;
				case 8:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("160"),3);
					break;
				case 9:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-16,
						TOPRULER+OFFSET-15,(LPCSTR)("180"),3);
					break;
				case 10:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("200"),3);
					break;
				case 11:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER + OFFSET -15,(LPCSTR)("220"),3);
					break;
				case 12:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER + OFFSET - 15,(LPCSTR)("240"),3);
					break;
				case 13:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("260"),3);
					break;
				case 14:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("280"),3);
				case 15:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("300"),3);
				case 16:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("320"),3);
				case 17:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("340"),3);
					break;
				case 18:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("360"),3);
					break;
				case 19:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("380"),3);
					break;
				case 20:
					TextOut(hdc,LEFTRULER+OFFSET+nCount*tickerMin-20,
						TOPRULER+OFFSET-15,(LPCSTR)("400"),3);
					break;
				default:
					break;						
				}
			}
		}
	}
		DeleteObject(font);	
	}
	//Ve cac vach tren Ruler doc
	else{
		LogFont.lfHeight = 11;
		LogFont.lfEscapement = 900;
		LogFont.lfOrientation = 0;
		LogFont.lfStrikeOut = 0;

		LogFont.lfUnderline = 0;
		LogFont.lfItalic = false;

		font = CreateFontIndirect(&LogFont);
		SelectObject(hdc,font);	
		for (nCount=0;nCount<=nCountMax;nCount++){
			Rectangle(hdc,LEFTRULER+OFFSET-tickerHeight,TOPRULER+OFFSET+
				nCount*tickerMin,LEFTRULER+OFFSET,TOPRULER+OFFSET+nCount*tickerMin+1);
		if (xN < 3)
		{
			if (tickerMin == TICKERLEVEL3(xN))
			{

				switch(nCount){
				case 0:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin+6,(LPCSTR)("0"),1);
					break;
				case 1:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("100"),3);
					break;
				case 2:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("200"),3);
					break;
				case 3:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("300"),3);
					break;
				case 4:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("400"),3);
					break;
				case 5:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("500"),3);
					break;
				case 6:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("600"),3);
					break;
				case 7:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("700"),3);
					break;
				case 8:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("800"),3);
					break;
				case 9:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("900"),3);
					break;
				case 10:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("1000"),4);
					break;
				case 11:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("1100"),4);
					break;
				case 12:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("1200"),4);
					break;
				case 13:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("1300"),4);
					break;
				case 14:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("1400"),4);
				case 15:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("1500"),4);
				case 16:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("1600"),4);
				case 17:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("1700"),4);
					break;
				case 18:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("1800"),4);
					break;
				case 19:
					TextOut(hdc,LEFTRULER+OFFSET-tickerHeight+2,
						TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("1900"),4);
					break;
				default:
					break;						
				}

			}
		}
		else
		{
			if (tickerMin == TICKERLEVEL2(xN))
			{
				switch(nCount){
					case 0:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin+7,(LPCSTR)("0"),1);
						break;
					case 1:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("20"),3);
						break;
					case 2:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("40"),3);
						break;
					case 3:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("60"),3);
						break;
					case 4:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("80"),3);
						break;
					case 5:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("100"),3);
						break;
					case 6:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("120"),3);
						break;
					case 7:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("140"),3);
						break;
					case 8:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("160"),3);
						break;
					case 9:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("180"),3);
						break;
					case 10:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("200"),3);
						break;
					case 11:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("220"),3);
						break;
					case 12:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("240"),3);
						break;
					case 13:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("260"),3);
						break;
					case 14:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("280"),3);
					case 15:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("300"),3);
					case 16:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("320"),3);
					case 17:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("340"),3);
						break;
					case 18:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("360"),3);
						break;
					case 19:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("380"),3);
						break;
					case 20:
						TextOut(hdc,LEFTRULER+OFFSET-tickerHeight-7,
							TOPRULER+OFFSET+nCount*tickerMin-2,(LPCSTR)("400"),3);
						break;
					default:
						break;						
				}
			}
		}
	}
		DeleteObject(font);	
}
	SelectObject ( hdc, hPenOld );
	DeleteObject (hPen);
	ReleaseDC(hWnd,hdc);
}

void CRulerEX::ShowRuler(HWND hWnd, int xN){

	//Xac dinh cua so lam viec
	HDC hdc = GetDC(hWnd);
	RECT clientRect;
	GetClientRect(hWnd,&clientRect);

	//Xac dinh loai but ve
	HPEN hPen = CreatePen (m_dwPenStyle, m_nPenWidth, m_crPenColor);
	HPEN hPenOld = (HPEN)SelectObject (hdc, hPen);
	//Ve khung cua Ruler
	Rectangle(hdc,LEFTRULER,TOPRULER,LEFTRULER+OFFSET,TOPRULER+OFFSET);
	Rectangle(hdc,LEFTRULER+OFFSET,TOPRULER,LEFTRULER+clientRect.right,TOPRULER+OFFSET);
	Rectangle(hdc,LEFTRULER,TOPRULER+OFFSET,LEFTRULER+OFFSET,clientRect.bottom);
	SelectObject ( hdc, hPenOld );
	DeleteObject ( hPen );

	//Ve cac vach tren Ruler
	DrawTicker(hWnd,RT_HORIZONTAL,MIN, xN);
	DrawTicker(hWnd,RT_HORIZONTAL,MEDIUM, xN);
	DrawTicker(hWnd,RT_HORIZONTAL,MAX, xN);
	DrawTicker(hWnd,RT_VERTICAL,MIN, xN);
	DrawTicker(hWnd,RT_VERTICAL,MEDIUM, xN);
	DrawTicker(hWnd,RT_VERTICAL,MAX, xN);

	ReleaseDC(hWnd,hdc);
}

//Phuong thuc ve vi tri con tro chuot
void CRulerEX::DrawCursorPosition(HWND hWnd,LPARAM lParam){

	//Xac dinh cua so thao tac
	HDC hdc = GetDC(hWnd);
	RECT clientRect;
	GetClientRect(hWnd,&clientRect);

	//Xac dinh vi tri cua chuot
	POINT CurrentCursor;
	CurrentCursor.x = LOWORD (lParam);
	CurrentCursor.y = HIWORD (lParam);

	if (CurrentCursor.x>=OFFSET&&CurrentCursor.y>=OFFSET&&CurrentCursor.x<=clientRect.right
		&&CurrentCursor.y<=clientRect.bottom){

			//Xoa cac vach tren vi tri cua chuot
			//
			HPEN hPen = CreatePen (m_dwPenStyle, 2, m_crCursorColor);
			/*HPEN hPenOld = (HPEN)*/SelectObject (hdc, hPen);
			SelectObject (hdc, GetStockObject (NULL_BRUSH));
			SetROP2(hdc, R2_NOTXORPEN);

			Rectangle(hdc,LEFTRULER+m_pLastPos.x,TOPRULER+clientRect.top,
				LEFTRULER+m_pLastPos.x+1,TOPRULER+OFFSET);
			Rectangle(hdc,LEFTRULER+clientRect.left,m_pLastPos.y,
				LEFTRULER+OFFSET,m_pLastPos.y+1);		

			// Ve cac vach xac dinh vi tri hien tai cua chuot
			//HGDIOBJ hObjOld;
			/*hObjOld = */
			Rectangle(hdc,CurrentCursor.x,TOPRULER+clientRect.top,
				CurrentCursor.x+1,TOPRULER+OFFSET);
			Rectangle(hdc,LEFTRULER+clientRect.left,CurrentCursor.y,
				LEFTRULER+OFFSET,CurrentCursor.y+1);

			SetPLastPos(CurrentCursor);
			//SelectObject ( hdc, hPenOld );
			DeleteObject (hPen);
	}
	ReleaseDC(hWnd,hdc);
}