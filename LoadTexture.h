// LoadTexture.h: interface for the CLoadTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADTEXTURE_H__1FE5AE76_7016_4D2A_9860_DEF97F7ACB7C__INCLUDED_)
#define AFX_LOADTEXTURE_H__1FE5AE76_7016_4D2A_9860_DEF97F7ACB7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLoadTexture  
{
public:
	void SetActive();
	void LoadFromFile(char *filename);
	CLoadTexture();
	virtual ~CLoadTexture();

	_AUX_RGBImageRec *image;
	int Width,Height;
	unsigned int ID;
};

#endif // !defined(AFX_LOADTEXTURE_H__1FE5AE76_7016_4D2A_9860_DEF97F7ACB7C__INCLUDED_)
