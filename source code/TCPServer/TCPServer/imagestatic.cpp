// ImageStatic.cpp

// Code by Erato.
// 2006. 11. 10

#include "stdafx.h"
#include "ImageStatic.h"


// CImageStatic

IMPLEMENT_DYNAMIC(CImageStatic, CStatic)
CImageStatic::CImageStatic()
{
}

CImageStatic::~CImageStatic()
{
}


BEGIN_MESSAGE_MAP(CImageStatic, CStatic)
END_MESSAGE_MAP()



// CImageStatic 메시지 처리기입니다.

bool CImageStatic::ViewImage()
{		
	if ( m_strFilePath == _T("") )
		return false ;
	
	// 확장자 체크
	int nDotPosition = m_strFilePath.Find( _T('.') ) ;
	CString	strExtension ;
	strExtension = m_strFilePath.Mid( nDotPosition+1, m_strFilePath.GetLength() ) ;	

	int nLength = NULL ;

	for ( int i = 0 ; i < 100 ; i++ )
	{
		nLength = strExtension.Find( _T('.') ) ;

		if ( nLength != -1 )		
			strExtension = strExtension.Mid( nLength+1, strExtension.GetLength() ) ;
		else
			break ;
	}

	if ( strExtension == _T("jpg") || strExtension == _T("JPG") ||
		strExtension == _T("gif") || strExtension == _T("GIF") ||
		strExtension == _T("bmp") || strExtension == _T("BMP") )
	{				
		// CString -> BSTR로 변경하고, 이미지를 읽어온다.
		BSTR bstr = m_strFilePath.AllocSysString() ;
		
		// 이미지 포인터 객제
		Image* pImage = new Image( bstr ) ;

		// BSTR 객체 free
		SysFreeString( bstr ) ;

		// Bitmap으로 변환한 후 다시 HBITMAP으로 변환
		Bitmap* pBitmap = (Bitmap*)pImage ;
		HBITMAP hBitmap ;
		pBitmap->GetHBITMAP( Color(255, 255, 255), &hBitmap ) ;

		// 여기에 비트맵을 직접 넣게 되면 picture 컨트롤에 직접 그리게 된다.
		// 하지만 비트맵 원래의 크기대로 되므로 picture 컨트롤 보다 작을수도 있고, 클수도 있다.
		//BitmapMain->SetBitmap(hBitmap);

		// picture 컨트롤의 DC를 얻어온다.
		CDC* pDC = this->GetDC() ;

		// picture 컨트롤의 DC와 호환되게 만들고, 변환돈 HBITMAP을 셀렉트 한다.
		HDC	memeDC ;
		memeDC = ::CreateCompatibleDC( pDC->m_hDC  ) ;
		HBITMAP oldBitmap ;
		oldBitmap = ( HBITMAP ) SelectObject( memeDC, hBitmap ) ;

		// picture 컨트롤의 크기를 얻어온다.
		CRect	prect, wrect ;
		this->GetClientRect( &prect ) ;	

		int x = NULL, y = NULL, width = NULL, height = NULL ;	
		width = prect.Width() ;
		height = prect.Height() ;

		// 이제 원래의 이미지를 picture 컨트롤의 크기에 맞게 변환하여 화면에 출력한다.
		pDC->SetStretchBltMode( COLORONCOLOR ) ;
		StretchBlt( pDC->m_hDC, x, y, width, height, memeDC, 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight(), SRCCOPY ) ;
		SelectObject( memeDC, oldBitmap ) ;

		// DC를 삭제한다.		
		delete pImage ;
		DeleteObject( pBitmap ) ;
		DeleteObject( hBitmap ) ;
		DeleteDC( memeDC ) ;
		DeleteDC( pDC->m_hDC ) ;
	}
	else
		return false ;

	return true ;
}

// file path
void CImageStatic::SetImageFile( CString strPath )
{
	m_strFilePath = strPath ;
}