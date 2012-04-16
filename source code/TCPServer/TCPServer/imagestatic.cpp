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



// CImageStatic �޽��� ó�����Դϴ�.

bool CImageStatic::ViewImage()
{		
	if ( m_strFilePath == _T("") )
		return false ;
	
	// Ȯ���� üũ
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
		// CString -> BSTR�� �����ϰ�, �̹����� �о�´�.
		BSTR bstr = m_strFilePath.AllocSysString() ;
		
		// �̹��� ������ ����
		Image* pImage = new Image( bstr ) ;

		// BSTR ��ü free
		SysFreeString( bstr ) ;

		// Bitmap���� ��ȯ�� �� �ٽ� HBITMAP���� ��ȯ
		Bitmap* pBitmap = (Bitmap*)pImage ;
		HBITMAP hBitmap ;
		pBitmap->GetHBITMAP( Color(255, 255, 255), &hBitmap ) ;

		// ���⿡ ��Ʈ���� ���� �ְ� �Ǹ� picture ��Ʈ�ѿ� ���� �׸��� �ȴ�.
		// ������ ��Ʈ�� ������ ũ���� �ǹǷ� picture ��Ʈ�� ���� �������� �ְ�, Ŭ���� �ִ�.
		//BitmapMain->SetBitmap(hBitmap);

		// picture ��Ʈ���� DC�� ���´�.
		CDC* pDC = this->GetDC() ;

		// picture ��Ʈ���� DC�� ȣȯ�ǰ� �����, ��ȯ�� HBITMAP�� ����Ʈ �Ѵ�.
		HDC	memeDC ;
		memeDC = ::CreateCompatibleDC( pDC->m_hDC  ) ;
		HBITMAP oldBitmap ;
		oldBitmap = ( HBITMAP ) SelectObject( memeDC, hBitmap ) ;

		// picture ��Ʈ���� ũ�⸦ ���´�.
		CRect	prect, wrect ;
		this->GetClientRect( &prect ) ;	

		int x = NULL, y = NULL, width = NULL, height = NULL ;	
		width = prect.Width() ;
		height = prect.Height() ;

		// ���� ������ �̹����� picture ��Ʈ���� ũ�⿡ �°� ��ȯ�Ͽ� ȭ�鿡 ����Ѵ�.
		pDC->SetStretchBltMode( COLORONCOLOR ) ;
		StretchBlt( pDC->m_hDC, x, y, width, height, memeDC, 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight(), SRCCOPY ) ;
		SelectObject( memeDC, oldBitmap ) ;

		// DC�� �����Ѵ�.		
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