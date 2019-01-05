#pragma once

#include "resource.h"
#define DEFAULT_FORMAT            (DT_LEFT|DT_WORDBREAK|DT_EDITCONTROL|DT_END_ELLIPSIS)
#define TEXT_RIGHT				  (DT_RIGHT|DT_WORDBREAK|DT_EDITCONTROL|DT_END_ELLIPSIS)
#define TEXT_CENTER				  (DT_CENTER|DT_WORDBREAK|DT_EDITCONTROL|DT_END_ELLIPSIS)
void CallRuler(HWND hWnd);
void CallGrid(HWND hWnd);
//paintListShape.PasteObject(hdc, s_ptDes); ID_Paste
// text multi select
//chan multi select len ruler
//doi che do an hien luoi
//coppy, paste multi   2362,2380, 2034, 1796, 1789, 2331,1429, 1467, 655, 2216
//phun mau?????
//delete nhieu doi tuong
//luu file
//rotate
void UpdateListMulS(HDC hdc,int nIndexObjSelect, WPARAM wParam);