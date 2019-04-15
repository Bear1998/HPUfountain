// LoadTexture.cpp: implementation of the CLoadTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HPUFountain.h"
#include "LoadTexture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoadTexture::CLoadTexture()
{

}

CLoadTexture::~CLoadTexture()
{

}

void CLoadTexture::LoadFromFile(char *filename)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1,&ID);//为第i个位图创建纹理
	glBindTexture(GL_TEXTURE_2D,ID);// 将生成的纹理的名称绑定到指定的纹理上
	image=auxDIBImageLoadA(filename);
	Width=image->sizeX;
	Height=image->sizeY;
	gluBuild2DMipmaps(GL_TEXTURE_2D,
						3,
						image->sizeX,
						image->sizeY,
						GL_RGB,
						GL_UNSIGNED_BYTE,
						image->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//放大的过滤方法
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);//缩小的过滤方法
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	delete image;
}

void CLoadTexture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D,ID);
}
