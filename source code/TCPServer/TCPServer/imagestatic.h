// ImageStatic.h

// Code by Erato.
// 2006. 11. 10

// CImageStatic

// picture control의 속성을 bitmap으로 설정하십시요..
// 그리고 컨트롤 변수를 선언해야 합니다.

#ifndef _IMAGE_STATIC_H_
#define _IMAGE_STATIC_H_

class CImageStatic : public CStatic
{
	DECLARE_DYNAMIC(CImageStatic)

public:	
	bool		ViewImage() ;						// 이 함수는 반드시 OnPaint 혹은 OnDraw에서 호출해야 합니다.
	void		SetImageFile( CString strPath ) ;	// 파일의 경로 지정 함수

private:
	CString		m_strFilePath ;

public:
	CImageStatic();
	virtual ~CImageStatic();

protected:
	DECLARE_MESSAGE_MAP()
};

#endif
