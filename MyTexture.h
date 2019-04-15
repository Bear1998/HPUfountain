// MyTexture.h: interface for the CMyTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTEXTURE_H__A044920B_BF54_4224_9F63_A4E4B5369143__INCLUDED_)
#define AFX_MYTEXTURE_H__A044920B_BF54_4224_9F63_A4E4B5369143__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _ImageRec
{
	unsigned short imagic;
	unsigned short type;
	unsigned short dim;
	unsigned short xsize,ysize,zsize;
	unsigned int min,max;
	unsigned int wasteBytes;
	char name[80];
	unsigned long colorMap;
	FILE *file;
	unsigned char *tmp,*tmpR,*tmpG,*tmpB;
	unsigned long rleEnd;
	unsigned int *rowStart;
	int *rowSize;
}ImageRec;

class CMyTexture  
{
public:
	unsigned * read_texture(char *name, int *width, int *height, int *components);
	void ImageGetRow(ImageRec *image, unsigned char *buf, int y, int z);
	void ImageClose(ImageRec *image);
	ImageRec * ImageOpen(const char *fileName);
	void ConvertLong(unsigned *array, long length);
	void ConvertShort(unsigned short *array, long length);
	void rgbatorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *a,unsigned char *l,int n);
	void rgbtorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *l,int n);
	void latorgba(unsigned char *b, unsigned char *a,unsigned char *l,int n);
	void bwtorgba(unsigned char *b,unsigned char *l,int n);
	CMyTexture();
	virtual ~CMyTexture();
};

#endif // !defined(AFX_MYTEXTURE_H__A044920B_BF54_4224_9F63_A4E4B5369143__INCLUDED_)
