// ImageStatic.h

// Code by Erato.
// 2006. 11. 10

// CImageStatic

// picture control�� �Ӽ��� bitmap���� �����Ͻʽÿ�..
// �׸��� ��Ʈ�� ������ �����ؾ� �մϴ�.

#ifndef _IMAGE_STATIC_H_
#define _IMAGE_STATIC_H_

class CImageStatic : public CStatic
{
	DECLARE_DYNAMIC(CImageStatic)

public:	
	bool		ViewImage() ;						// �� �Լ��� �ݵ�� OnPaint Ȥ�� OnDraw���� ȣ���ؾ� �մϴ�.
	void		SetImageFile( CString strPath ) ;	// ������ ��� ���� �Լ�

private:
	CString		m_strFilePath ;

public:
	CImageStatic();
	virtual ~CImageStatic();

protected:
	DECLARE_MESSAGE_MAP()
};

#endif
