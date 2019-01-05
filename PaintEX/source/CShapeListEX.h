#ifndef CSHAPELISTEX_H
#define CSHAPELISTEX_H
#include "CLineEX.h"
#include "CRectangleEx.h"
#include "CRoundedRectEx.h"
#include "CTriangleEx.h"
#include "CCircleEX.h"
#include "CRightTriangleEX.h"
#include "CTextEx.h"
#include "CShapeEX.h"
#include <vector>
#include <fstream>
using namespace std;
#define  NSHAPE 50          // So Shape max
// Dung de luu giu BeginPoint va EndPoint ban dau cua cac Shape 
// ung voi che do Zoom 100%
static POINTS ptTempBegin[NSHAPE],ptTempEnd[NSHAPE]; 

class CShapeListEX
{
public:
	vector<CShapeEX*> listShape;
	bool m_fCopy;	//	co xac dinh xem doi tuong duoc su dung lenh copy chu ko phai cut
	bool m_fCut;	//	co xac dinh xem doi tuong duoc su dung lenh cut chu ko phai copy
	vector<CShapeEX*> listShapeCopy;	//	chua cac doi tuong copy, cut
	//	chua chi so trong list cua cac doi tuong duoc chon
	//	ung dung cho viec di chuyen doi tuong dung phim trai, phai, len, xuong 
	vector<size_t> m_saveSelectPosition; 
	vector<CShapeEX*> listShapeDeleted;
public:
	CShapeListEX(void);
	void AddShapeToList(CShapeEX*);
	CShapeEX* GetObject(int);
	int GetCurrentShape();
	void ClearListShape();
	int IsSelected(HDC,POINTS);		//	tra ve vi tri cua doi tuong dau tien duoc chon
	//	Method save, load object in list to file
	bool SaveToFile(ofstream&, char*);
	bool LoadToFile(ifstream&, char*);
	void ClearTracker(HDC);
	void ClearTracker(HDC,int);
	void DeleteObject(HDC);				//  xoa mot hoac nhieu doi tuong trong danh sach
	void CopyObject();					//	copy mot hoac nhieu doi tuong
	void CutObject(HDC);				//	cut mot hoac nhieu doi tuong trong danh sach
	void PasteObject(HDC, POINTS);		//	dan mot hoac nhieu doi tuong 
	void Draw(HDC);						//	ve ca danh sach ra man hinh, dung cho viec load to file
	void DeleteEmptyTextObject(HDC);    //	xoa khoi danh sach cac doi tuong text rong
	void MoveSomeObject(int, int);		
	void SaveSelectObjectPos();			//	luu vi tri doi tuong duoc tron trong list
	void DrawTracker(HDC);				//  ve tracker cho cac doi tuong duoc chon
	bool AllowPaste();					//  cho phep paste doi tuong
	bool AllowCutAndCopy();				//	cho phep cut va copy doi tuong
	void Undo();
	void ChoseFont(HWND);				//	thay doi font cho doi tuong text duoc chon trong list
	void DeleteText(HDC);
    // Zoom and Scrollbar
    void ZoomObject(int nZoom);             //Thay doi ty le cua toan bo object
    void MoveObject(int nDeltaX, int nDeltaY);// Thay doi vi tri cua toan bo object
    // Luu lai gia tri toa do ban dau cua cac shape
    void SavePoint();

};
#endif