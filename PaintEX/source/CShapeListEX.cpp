#include "StdAfx.h"
#include "CShapeListEX.h"

/******************************************************************  
* Method name      : CShapeListEX::CShapeListEX()
* Description    :   Initial an object
**********/ 
CShapeListEX::CShapeListEX(void)
{
	m_fCopy = false;
	m_fCut = false;
}

/******************************************************************
* Method name      : CShapeListEX::AddShapeToList()
* Description    :   add an object to the list of shape
**********/
void CShapeListEX::AddShapeToList(CShapeEX* pShape)
{
	listShape.push_back(pShape);
}
/******************************************************************
* Method name      : CShapeListEX::GetCurrentShape()
* Description    :   get the position of the current object
**********/

int CShapeListEX::GetCurrentShape()
{
	return listShape.size();
}
/******************************************************************
* Method name      : CShapeListEX::GetObject()
* Description    :   lay ra mot doi tuong nam o vi tri cho truoc
**********/
CShapeEX* CShapeListEX::GetObject(int nIndex)
{
	return listShape.at(nIndex);
}
/******************************************************************
* Method name      : CShapeListEX::ClearListShape()
* Description    :   xoa toan bo danh sach
**********/
void CShapeListEX::ClearListShape()
{
	listShape.clear();
	listShapeCopy.clear();
}

/******************************************************************
* Method name      : CShapeListEX::IsSelected()
* Description    :   chon mot doi tuong trong danh sach
**********/

int CShapeListEX::IsSelected(HDC hdc, POINTS point)
{
	for(size_t i =0; i< listShape.size(); i++)
	{
		if(listShape.at(i)->IsSelected(point) != MR_NONE)
			return i;
	}
	return -1;
}
/******************************************************************
* Method name      : CShapeListEX::ClearTracker()
* Description    :   xoa toan bo tracker cua cac doi tuong duoc chon
**********/
void CShapeListEX::ClearTracker(HDC hdc)
{
	for(size_t i =0;i < listShape.size(); i++)
	{
		if((listShape.at(i)->m_bSelected == true)
			&&(listShape.at(i)->m_nPattern != MS_TEXT))
		{
			listShape.at(i)->DrawSelected(hdc);
		}
		if(listShape.at(i)->m_nPattern == MS_TEXT)
		{

			if ((listShape.at(i)->m_bSelected == false)
				&&(listShape.at(i)->m_bBoundLine == true))
			{
				listShape.at(i)->Draw(hdc);
			}
			if ((listShape.at(i)->m_bSelected == true)
				&&(listShape.at(i)->m_bBoundLine == true))
			{
				listShape.at(i)->Draw(hdc);
				listShape.at(i)->DrawSelected(hdc);
			}

		}
	}
}
/******************************************************************
* Method name      : CShapeListEX::ClearTracker()
* Description    :   xoa toan bo tracker, tru doi tuong xac dinh nao do
**********/
void CShapeListEX::ClearTracker(HDC hdc, int nObject)
{
	ClearTracker(hdc);
	if (listShape.at(nObject)->m_nPattern != MS_TEXT)
	{
		listShape.at(nObject)->DrawSelected(hdc);
	}
	else
	{
		listShape.at(nObject)->DrawSelected(hdc);
		listShape.at(nObject)->Draw(hdc);
	}
}

/******************************************************************
* Method name      : CShapeListEX::SaveToFile()
* Description    :   luu du lieu tu list vao file txt
**********/
bool CShapeListEX::SaveToFile(ofstream& pFile, char* fName)
{

	pFile.open(fName);
	if(!pFile.is_open())
		return false;
	for(int i=0; i< (int)listShape.size();i++)
	{
		if(listShape.at(i)->m_nPattern != MS_TEXT)
		{
			if((i <(int)listShape.size()-1))
			{
				pFile << listShape[i]->m_nPattern<<"	"
					<<listShape[i]->m_ptBegin.x<<"	"
					<<listShape[i]->m_ptBegin.y<<"	"
					<<listShape[i]->m_ptEnd.x<<"	"
					<<listShape[i]->m_ptEnd.y<<"	"
					<<listShape[i]->m_bFilled<<"	"
					<<listShape[i]->m_bSelected<<"	"
					<<listShape[i]->m_crBrushColor<<"	"
					<<listShape[i]->m_dwPenStyle<<"	"
					<<listShape[i]->m_nPenWidth<<"	"
					<<listShape[i]->m_nDegree<<"	"
					<<listShape[i]->m_crPenColor<<endl;
			}
			else
			{
				pFile << listShape[i]->m_nPattern<<"	"
					<<listShape[i]->m_ptBegin.x<<"	"
					<<listShape[i]->m_ptBegin.y<<"	"
					<<listShape[i]->m_ptEnd.x<<"	"
					<<listShape[i]->m_ptEnd.y<<"	"
					<<listShape[i]->m_bFilled<<"	"
					<<listShape[i]->m_bSelected<<"	"
					<<listShape[i]->m_crBrushColor<<"	"
					<<listShape[i]->m_dwPenStyle<<"	"
					<<listShape[i]->m_nPenWidth<<"	"
					<<listShape[i]->m_nDegree<<"	"
					<<listShape[i]->m_crPenColor;
			}
		}
		else
		{
			if((i <(int)listShape.size()-1))
			{
				pFile << listShape[i]->m_nPattern<<"	"
					<<listShape[i]->m_ptBegin.x<<"	"
					<<listShape[i]->m_ptBegin.y<<"	"
					<<listShape[i]->m_ptEnd.x<<"	"
					<<listShape[i]->m_ptEnd.y<<"	"
					<<listShape[i]->m_bFilled<<"	"
					<<listShape[i]->m_bSelected<<"	"
					<<listShape[i]->m_crBrushColor<<"	"
					<<listShape[i]->m_dwPenStyle<<"	"
					<<listShape[i]->m_nPenWidth<<"	"
					<<listShape[i]->m_nDegree<<"	"
					<<listShape[i]->m_crPenColor<<"	"
					<<listShape[i]->m_crTextColor<<"	"
					<<listShape[i]->m_strBuffer<<endl;
			}
			else
			{
				pFile << listShape[i]->m_nPattern<<"	"
					<<listShape[i]->m_ptBegin.x<<"	"
					<<listShape[i]->m_ptBegin.y<<"	"
					<<listShape[i]->m_ptEnd.x<<"	"
					<<listShape[i]->m_ptEnd.y<<"	"
					<<listShape[i]->m_bFilled<<"	"
					<<listShape[i]->m_bSelected<<"	"
					<<listShape[i]->m_crBrushColor<<"	"
					<<listShape[i]->m_dwPenStyle<<"	"
					<<listShape[i]->m_nPenWidth<<"	"
					<<listShape[i]->m_nDegree<<"	"
					<<listShape[i]->m_crPenColor<<"	"
					<<listShape[i]->m_crTextColor<<"	"
					<<listShape[i]->m_strBuffer;
			}
		}
	}

	pFile.close();
	return true;
}

/******************************************************************
* Method name      : CShapeListEX::LoadToFile()
* Description    :   doc du lieu tu file text vao list
**********/

bool CShapeListEX::LoadToFile(ifstream& pFile, char* fName)
{
	int nPattern;
	POINTS ptStart, ptEndl;
	bool bFilled;	
	bool bSelected;
	COLORREF crBrushColor;
	DWORD dwPenStyle;
	int nPenWidth;
	int nDegree;
	COLORREF crPenColor;
	COLORREF crTextColor;
	string strBuffer;
	int nCount = 0;
	CShapeEX* pObject;
	listShape.clear();
	pFile.open(fName);
	if(!pFile.is_open())
		return false;
	while(pFile.good())
	{
		pFile >> nPattern >> ptStart.x 
			>> ptStart.y >> ptEndl.x 
			>> ptEndl.y >> bFilled
			>> bSelected >> crBrushColor
			>> dwPenStyle >> nPenWidth
			>> nDegree >> crPenColor;
		switch(nPattern)
		{
		case MS_LINE:
			pObject = new CLineEX();
			nCount ++;
			break;
		case MS_RECT:
			pObject = new CRectangleEx();
			nCount ++;
			break;
		case MS_RIGHT_TRIANGLE:
			pObject = new CRightTriangleEX();
			nCount ++;
			break;
		case MS_TRIANGLE:
			pObject = new CTriangleEX();
			nCount ++;
			break;
		case MS_CIRCLE:
			pObject = new CCircleEX();
			nCount ++;
			break;
		case MS_ROUNDED_RECTANGLE:
			pObject = new CRoundedRectEx();
			nCount ++;
			break;
		case MS_TEXT:
			pFile>> crTextColor >> strBuffer;
			pObject = new CTextEx();
			pObject->m_crTextColor = crTextColor;
			pObject->m_strBuffer = strBuffer;
			nCount ++;
			break;
		default:
			break;
		}
		if (nCount != 0)
		{	
			pObject->m_nPattern = nPattern;
			pObject->m_ptBegin = ptStart;
			pObject->m_ptEnd = ptEndl;
			pObject->m_bFilled = bFilled;
			pObject->m_bSelected = bSelected;
			pObject->m_crBrushColor = crBrushColor;
			pObject->m_dwPenStyle = dwPenStyle;
			pObject->m_nPenWidth = nPenWidth;
			pObject->m_nDegree = nDegree;
			pObject->m_crPenColor = crPenColor;
			this->AddShapeToList(pObject);
		}
	}
	pFile.close();
	return true;
}
/******************************************************************
* Method name      : CShapeListEX::DeleteObject()
* Description    :   xoa mot hoac nhieu doi tuong khoi danh sach doi tuong khoi list
**********/
void CShapeListEX::DeleteObject(HDC hdc)
{	
	listShapeDeleted.clear();
	//	luu lai kich co vector
	int nSize = listShape.size();
	//	luu vi tri cua doi tuong duoc chon cuoi cung trong danh sach
	int nTemp = 0;
	//	dem xem trong danh sach co bao nhieu doi tuong duoc chon
	int nCount = 0;
	//	vong lap nSize lan de khi chon ca danh sach thi xoa duoc het danh sach
	for (int i = 0; i < nSize; i++)
	{
		//	kiem tra xem trong danh sach co doi tuong duoc chon khong
		//	dem so doi tuong duoc chon va lay ra vi tri cua doi tuong cuoi cung duoc chon trong danh sach 
		for (size_t j = 0; j < listShape.size(); j++)
		{
			if (listShape.at(j)->m_bSelected == true)
			{
				nTemp = j;
				nCount++;
			}
		}
		//	neu co doi tuong duoc chon, xoa doi tuong duoc chon cuoi cung

		if (nCount != 0)
		{
			if (listShape.at(nTemp)->m_nPattern != MS_TEXT)
			{	
				listShape.at(nTemp)->Draw(hdc);	//	xoa hinh ve
				listShape.at(nTemp)->DrawSelected(hdc);	//	xoa tracker cua hinh ve
				listShapeDeleted.push_back(listShape.at(nTemp));
				listShape.erase(listShape.begin() + nTemp);	//	xoa doi tuong trong danh sach
			}
			else
			{
				listShape.at(nTemp)->Draw(hdc);	//	xoa hinh ve
				listShape.at(nTemp)->WriteText(hdc, RGB (255,255,255));	//	xoa text
				listShape.at(nTemp)->DrawSelected(hdc);	//	xoa tracker cua hinh ve
				listShapeDeleted.push_back(listShape.at(nTemp));
				listShape.erase(listShape.begin() + nTemp);	//	xoa doi tuong trong danh sach
			}
		}
		//	reset bien dem ve ban dau
		nCount = 0;
	}
}
/******************************************************************
* Method name      : CShapeListEX::Draw()
* Description    :  ve lai toan bo doi tuong trong danh sach
**********/
void CShapeListEX::Draw(HDC hdc)		//	ve lai toan bo danh sach
{
	for(int i=0; i< (int)listShape.size();i++)
	{		
		if (listShape.at(i)->m_nPattern != MS_TEXT)
			listShape.at(i)->Draw(hdc);

		if (listShape.at(i)->m_nPattern == MS_TEXT)
		{
			listShape.at(i)->WriteText(hdc, listShape.at(i)->m_crTextColor);
		}

	}
}
/******************************************************************
* Method name      : CShapeListEX::PasteObject()
* Description    :  dan doi tuong vao noi kich chuot phai
**********/
void CShapeListEX::PasteObject(HDC hdc, POINTS ptDes)
{
 	POINTS ptSrcFix;
	CShapeEX* pShapeTemp;
	int nMode;

	size_t nBeginSize = listShape.size();
	if ((m_fCopy == true)||(m_fCut == true))
	{	
		ptSrcFix.x = (listShapeCopy.at(0)->m_ptBegin.x + listShapeCopy.at(0)->m_ptEnd.x)/2;
		ptSrcFix.y = (listShapeCopy.at(0)->m_ptBegin.y + listShapeCopy.at(0)->m_ptEnd.y)/2;
		for (size_t i = 0; i < listShapeCopy.size(); i++)
		{
			int nDx, nDy;
			nDx = ptDes.x - ptSrcFix.x;
			nDy = ptDes.y - ptSrcFix.y;
			listShapeCopy.at(i)->m_ptBegin.x += nDx; 
			listShapeCopy.at(i)->m_ptBegin.y += nDy;
			listShapeCopy.at(i)->m_ptEnd.x += nDx; 
			listShapeCopy.at(i)->m_ptEnd.y += nDy;
			nMode = listShapeCopy.at(i)->m_nPattern;
			switch(nMode)
			{
			case MS_CIRCLE:
				pShapeTemp = new CCircleEX();
				break;
			case  MS_LINE:
				pShapeTemp = new CLineEX();
				break;
			case MS_RECT:
				pShapeTemp = new CRectangleEx();
				break;
			case MS_TRIANGLE:
				pShapeTemp = new CTriangleEX();
				break;
			case MS_RIGHT_TRIANGLE:
				pShapeTemp = new CRightTriangleEX();
				break;
			case MS_ROUNDED_RECTANGLE:
				pShapeTemp = new CRoundedRectEx();
				break;
			case MS_TEXT:
				pShapeTemp = new CTextEx();
				pShapeTemp->m_crTextColor = listShapeCopy.at(i)->m_crTextColor;
				pShapeTemp->m_strBuffer = listShapeCopy.at(i)->m_strBuffer;
				break;
			}
			pShapeTemp->m_bFilled = listShapeCopy.at(i)->m_bFilled;
			pShapeTemp->m_crBrushColor = listShapeCopy.at(i)->m_crBrushColor;
			pShapeTemp->m_crPenColor = listShapeCopy.at(i)->m_crPenColor;
			pShapeTemp->m_dwPenStyle = listShapeCopy.at(i)->m_dwPenStyle;
			pShapeTemp->m_nDegree = listShapeCopy.at(i)->m_nDegree;
			pShapeTemp->m_nPattern = listShapeCopy.at(i)->m_nPattern;
			pShapeTemp->m_nPenWidth = listShapeCopy.at(i)->m_nPenWidth;
			pShapeTemp->m_ptBegin = listShapeCopy.at(i)->m_ptBegin;
			pShapeTemp->m_ptEnd = listShapeCopy.at(i)->m_ptEnd;
			AddShapeToList(pShapeTemp);
		}
		if (listShape.size() > nBeginSize)
		{
			for (size_t i = nBeginSize; i < listShape.size(); i++)
			{
				if ((listShape.at(i)->m_ptBegin.x >= LEFTOFFSET + listShape.at(i)->m_nPenWidth + 3)
					&&(listShape.at(i)->m_ptBegin.y >= TOPOFFSET + listShape.at(i)->m_nPenWidth + 3))
				{
				
 					if (listShape.at(i)->m_nPattern != MS_TEXT)
 					{
 						listShape.at(i)->Draw(hdc);	//	ve lai doi tuong
 					}
					else
					{
						listShape.at(i)->Draw(hdc);
						listShape.at(i)->WriteText(hdc, listShape.at(i)->m_crTextColor);
					}
				}
			}

		}
		//	nhung doi tuong nao khong duoc ve ra se bi xoa khoi danh sach
		for (size_t i = nBeginSize; i < listShape.size(); i++)
			{
				if (((listShape.at(i)->m_ptBegin.x >= LEFTOFFSET + listShape.at(i)->m_nPenWidth + 3)
					&&(listShape.at(i)->m_ptBegin.y >= TOPOFFSET + listShape.at(i)->m_nPenWidth + 3)) == false)
				{
					listShape.erase(listShape.begin() + i);	//	xoa doi tuong trong danh sach
				}
			}
	}
}
/******************************************************************
* Method name    : CShapeListEX::ZoomObject(int nZoom)
* Description    : Chinh lai kich thuoc tung phan tu trong listshape
*                  theo ty le zoom 
**********/
void CShapeListEX::ZoomObject(int nZoom)		
{
    for(int i=0; i< (int)listShape.size(); i++)
    {		
        //Chieu dai va chieu rong ban dau duoc tang len nZoom lan
        //ptTempBegin va ptTempEnd ung voi zoom 100%.
        listShape.at(i)->m_ptBegin.x = nZoom*ptTempBegin[i].x - (nZoom - 1)*LEFTOFFSET;
        listShape.at(i)->m_ptBegin.y = nZoom*ptTempBegin[i].y - (nZoom - 1)*TOPOFFSET;
        listShape.at(i)->m_ptEnd.x = nZoom*ptTempEnd[i].x - (nZoom - 1)*LEFTOFFSET ;
        listShape.at(i)->m_ptEnd.y = nZoom*ptTempEnd[i].y - (nZoom - 1)*TOPOFFSET;
  }
}
/******************************************************************
* Method name    : CShapeListEX:: MoveObject(int nDeltaX, int nDeltaY)
* Description    : Di chuyen tat ca cac shape trong listshape
*                  theo khoang cach truc X va truc Y                 
**********/

void CShapeListEX:: MoveObject(int nDeltaX, int nDeltaY)
{
    for(int i = 0; i < (int)listShape.size(); i++)
    {
        //2 diem luu toa do ban dau cua hinh ve
        POINTS ptTempBegin, ptTempEnd;
        int nLeftX,nTopY;
        ptTempBegin = listShape.at(i)->m_ptBegin;
        ptTempEnd = listShape.at(i)->m_ptEnd;
        //Lay toa do diem TopLeft cua cac hinh ve
        if ((ptTempBegin.x <= ptTempEnd.x) && (ptTempBegin.y <= ptTempEnd.y))
        {
            nLeftX = ptTempBegin.x + nDeltaX;
            nTopY = ptTempBegin.y + nDeltaY;
        }
        if ((ptTempBegin .x > ptTempEnd.x) && (ptTempBegin .y <= ptTempEnd.y))
        {
            nLeftX = ptTempEnd.x + nDeltaX;
            nTopY = ptTempBegin.y + nDeltaY;
        }
        if ((ptTempBegin.x > ptTempEnd.x) && (ptTempBegin.y > ptTempEnd.y))
        {
            nLeftX = ptTempEnd.x + nDeltaX;
            nTopY = ptTempEnd.y + nDeltaY;
        }
        if ((ptTempBegin.x <= ptTempEnd.x) && (ptTempBegin.y > ptTempEnd.y))
        {
            nLeftX = ptTempBegin.x + nDeltaX;
            nTopY = ptTempEnd.y + nDeltaY;
        }

        //Kiem tra dieu kien de hinh ve khong cham vao ruler
        if ((nLeftX >= LEFTOFFSET) && (nTopY >= TOPOFFSET))
        {
            listShape.at(i)->m_ptBegin.x += nDeltaX; listShape.at(i)->m_ptBegin.y += nDeltaY;
            listShape.at(i)->m_ptEnd.x += nDeltaX; listShape.at(i)->m_ptEnd.y += nDeltaY;
        }
    }
}
/******************************************************************
* Method name    : CShapeListEX::SavePoint()
* Description    : Luu lai gia tri BeginPoint va EndPoint cua
*                  cac shape trong listshape ung voi zoom 100%
**********/
void CShapeListEX::SavePoint()
{
    for (size_t i = 0; i< listShape.size(); i++)
    {
        ptTempBegin[i] = listShape.at(i)->m_ptBegin;
        ptTempEnd[i] = listShape.at(i)->m_ptEnd;
    }
}
/******************************************************************
* Method name    : CShapeListEX::CopyObject()
* Description    : copy mot hoac nhieu doi tuong trong danh sach
*                  cac shape trong listshape 
**********/
void CShapeListEX::CopyObject()
{
	listShapeCopy.clear();
	CShapeEX *pShapeTemp;
	int nMode1;
 	for (size_t i = 0; i < listShape.size(); i++)
	{
		if (listShape.at(i)->m_bSelected == true)
		{
			nMode1 = listShape.at(i)->m_nPattern;
			switch (nMode1)
			{
			case MS_CIRCLE:
				pShapeTemp = new CCircleEX();
				break;
			case  MS_LINE:
				pShapeTemp = new CLineEX();
				break;
			case MS_RECT:
				pShapeTemp = new CRectangleEx();
				break;
			case MS_TRIANGLE:
				pShapeTemp = new CTriangleEX();
				break;
			case MS_RIGHT_TRIANGLE:
				pShapeTemp = new CRightTriangleEX();
				break;
			case MS_ROUNDED_RECTANGLE:
				pShapeTemp = new CRoundedRectEx();
				break;
			case MS_TEXT:
				pShapeTemp = new CTextEx();
				pShapeTemp->m_crTextColor = listShape.at(i)->m_crTextColor;
				pShapeTemp->m_strBuffer = listShape.at(i)->m_strBuffer;
				break;
			}
			pShapeTemp->m_bFilled = listShape.at(i)->m_bFilled;
			pShapeTemp->m_crBrushColor = listShape.at(i)->m_crBrushColor;
			pShapeTemp->m_crPenColor = listShape.at(i)->m_crPenColor;
			pShapeTemp->m_dwPenStyle = listShape.at(i)->m_dwPenStyle;
			pShapeTemp->m_nDegree = listShape.at(i)->m_nDegree;
			pShapeTemp->m_nPattern = listShape.at(i)->m_nPattern;
			pShapeTemp->m_nPenWidth = listShape.at(i)->m_nPenWidth;
			pShapeTemp->m_ptBegin = listShape.at(i)->m_ptBegin;
			pShapeTemp->m_ptEnd = listShape.at(i)->m_ptEnd;
			listShapeCopy.push_back(pShapeTemp);
			m_fCopy = true;
		}
	}
	m_fCut = false;
}
/******************************************************************
* Method name    : CShapeListEX::CutObject()
* Description    : cut mot doi tuong
*                  cac shape trong listshape 
**********/
void CShapeListEX::CutObject(HDC hdc)
{
	CopyObject();
	DeleteObject(hdc);
	if (m_fCopy == true)
	{	
		m_fCopy = false;
		m_fCut = true;
	}

}
/******************************************************************
* Method name    : CShapeListEX::DeleteEmptyTextObject()
* Description    : xoa nhung doi tuong text ma khong co text(rong)
*                  cac shape trong listshape 
**********/
void CShapeListEX::DeleteEmptyTextObject(HDC hdc)
{
	SetROP2(hdc, R2_NOTXORPEN);
	for (size_t i = 0; i < listShape.size(); i++)
	{
		if (listShape.at(i)->m_nPattern == MS_TEXT)
		{
			if (listShape.at(i)->m_strBuffer.size() == 1)
			{
				listShape.at(i)->Draw(hdc);
				listShape.erase(listShape.begin() + i);	//	xoa doi tuong text rong trong danh sach
			}
		}
	}
}
/******************************************************************
* Method name    : CShapeListEX::MoveSomeObject()
* Description    : dich chuyen mot vai doi tuong ma khong phai la toan bo danh sach
*                  cac shape trong listshape 
**********/
void CShapeListEX:: MoveSomeObject(int nDeltaX, int nDeltaY)
{
	for (size_t i = 0; i < m_saveSelectPosition.size(); i++)
	{
		//2 diem luu toa do ban dau cua hinh ve
		POINTS ptTempBegin, ptTempEnd;
		int nLeftX,nTopY;
		ptTempBegin = listShape.at(m_saveSelectPosition.at(i))->m_ptBegin;
		ptTempEnd = listShape.at(m_saveSelectPosition.at(i))->m_ptEnd;
		//Lay toa do diem TopLeft cua cac hinh ve
		if ((ptTempBegin.x <= ptTempEnd.x) && (ptTempBegin.y <= ptTempEnd.y))
		{
			nLeftX = ptTempBegin.x + nDeltaX;
			nTopY = ptTempBegin.y + nDeltaY;
		}
		if ((ptTempBegin .x > ptTempEnd.x) && (ptTempBegin .y <= ptTempEnd.y))
		{
			nLeftX = ptTempEnd.x + nDeltaX;
			nTopY = ptTempBegin.y + nDeltaY;
		}
		if ((ptTempBegin.x > ptTempEnd.x) && (ptTempBegin.y > ptTempEnd.y))
		{
			nLeftX = ptTempEnd.x + nDeltaX;
			nTopY = ptTempEnd.y + nDeltaY;
		}
		if ((ptTempBegin.x <= ptTempEnd.x) && (ptTempBegin.y > ptTempEnd.y))
		{
			nLeftX = ptTempBegin.x + nDeltaX;
			nTopY = ptTempEnd.y + nDeltaY;
		}

		//Kiem tra dieu kien de hinh ve khong cham vao ruler
		if ((nLeftX >= LEFTOFFSET) && (nTopY >= TOPOFFSET))
		{
			listShape.at(m_saveSelectPosition.at(i))->m_ptBegin.x += nDeltaX; listShape.at(m_saveSelectPosition.at(i))->m_ptBegin.y += nDeltaY;
			listShape.at(m_saveSelectPosition.at(i))->m_ptEnd.x += nDeltaX; listShape.at(m_saveSelectPosition.at(i))->m_ptEnd.y += nDeltaY;
		}
	}
}
/******************************************************************
* Method name    : CShapeListEX::SaveSelectObjectPos()
* Description    : luu lai chi so trong list cua cac doi tuong duoc chon
*                  cac shape trong listshape 
**********/
void CShapeListEX::SaveSelectObjectPos()
{
	m_saveSelectPosition.clear();
	for(int i = 0; i < (int)listShape.size(); i++)
	{
		if (listShape.at(i)->m_bSelected == true)
		{
			m_saveSelectPosition.push_back(i);
		}
	}
}
/******************************************************************
* Method name    : CShapeListEX::DrawTracker()
* Description    : ve cac tracker cua cac doi tuong duoc chon
*                  cac shape trong listshape 
**********/
void CShapeListEX::DrawTracker(HDC hdc)
{
	for(size_t i = 0; i < m_saveSelectPosition.size(); i++)
	{
		{
			listShape.at(m_saveSelectPosition.at(i))->DrawSelected(hdc);
		}
	}
}
/******************************************************************
* Method name    : CShapeListEX::AllowPaste()
* Description    : cho phep hanh dong paste
**********/
bool CShapeListEX::AllowPaste()
{
	if (listShapeCopy.size() > 0)
	   return true;
	else
		return false;
}
/******************************************************************
* Method name    : CShapeListEX::AllowCutAndCopy()
* Description    : Cho phep cut hoac copy (dung de bat tat nut cut,copy tren toolbar)
**********/
bool CShapeListEX::AllowCutAndCopy()
{
  int nCount = 0;
  for (size_t i = 0; i < listShape.size(); i++)
  {
	  if (listShape.at(i)->m_bSelected == true)
	  {
		  nCount++;
	  }
  }
  if (nCount > 0)
	return true;
  else
	  return false;
}
/******************************************************************
* Method name    : CShapeListEX::Undo()
* Description    : tro lai hanh dong truoc do
**********/
void CShapeListEX::Undo()
{
	if (listShapeDeleted.size() > 0)
	{
		for (size_t i = 0; i < listShapeDeleted.size(); i++)
		{
			AddShapeToList(listShapeDeleted.at(i));
		}
	}
	listShapeDeleted.clear();
}

/******************************************************************
* Method name    : CShapeListEX::ChoseFont()
* Description    : thay doi font cho cac doi tuong text
**********/
void CShapeListEX::ChoseFont(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	for (size_t i = 0; i < listShape.size(); i++)
	{
		if (listShape.at(i)->m_nPattern == MS_TEXT)
		{
			if (listShape.at(i)->m_bSelected == true)
			{
				listShape.at(i)->WriteText(hdc, RGB(255,255,255));//  xoa text cu di
				listShape.at(i)->ChoseFont(hWnd);
			}
		}
	}
	ReleaseDC(hWnd, hdc);
}
void CShapeListEX::DeleteText(HDC hdc)
{
	for(int i=0; i< (int)listShape.size();i++)
	{		
		if (listShape.at(i)->m_nPattern == MS_TEXT)
		{
			listShape.at(i)->WriteText(hdc, RGB(255, 255, 255));
		}

	}
}