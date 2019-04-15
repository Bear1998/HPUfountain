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
	glGenTextures(1,&ID);//Ϊ��i��λͼ��������
	glBindTexture(GL_TEXTURE_2D,ID);// �����ɵ���������ư󶨵�ָ����������
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

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//�Ŵ�Ĺ��˷���
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);//��С�Ĺ��˷���
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	delete image;
}

void CLoadTexture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D,ID);
}
