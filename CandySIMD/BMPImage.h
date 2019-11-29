
//BMPImage.h

#ifndef BMPIMAGE_H

#define BMPIMAGE_H



#include <string>



/** ------------------���������ض���------------------------ */

typedef long int4;              // 4 bytes

typedef unsigned int uint;     // 4 bytes

typedef unsigned char uchar;   // 1 byte

typedef unsigned long uint4;   // 4 bytes

typedef unsigned long ulong;   // 4 bytes

typedef unsigned short uint2;  // 2 bytes

/** -------------------------------------------------------- */



/** ------------------��ɫ�ṹ���ض���---------------------- */

// Color Palette�Ľṹ�壬Ҳ��RGBA��ɫ�ṹ��

typedef struct {

	uchar b;

	uchar g;

	uchar r;

	uchar a;

}BGRA, ColorPalette;



// RGB��ɫ�ṹ��

typedef struct {

	uchar b;

	uchar g;

	uchar r;

}BGR;

/** -------------------------------------------------------- */



class BMPImage {

private:

	/** -------------BMP�ļ�ͷ��BMP��Ϣͷ���ݽṹ����----------- */

	//�ο���������

	//https://blog.csdn.net/u012877472/article/details/50272771

	//https://blog.csdn.net/lanbing510/article/details/8176231

	//����Ҫ����һ�У�����BMPFileHeader��size������14�ֽ�

#pragma  pack(2)

	//bmp�ļ�ͷ��bmp file header������14�ֽڣ�

	typedef struct {

		uint2 bfType;           //2�ֽڣ��ļ����ͣ���Ӧ��0x4d42('BM')

		uint4 bfSize;           //4�ֽڣ��ļ���С���ֽ�Ϊ��λ��

		uint2 bfReserved1;      //2�ֽڣ���������������Ϊ0

		uint2 bfReserved2;      //2�ֽڣ���������������Ϊ0

		uint4 bfOffBits;        //4�ֽڵ�ƫ�ƣ���ʾ���ļ�ͷ��λͼ���ݵ�ƫ��

	} BMPFileHeader;



	//λͼ��Ϣͷ��bitmap information������40�ֽڣ�

	typedef struct {

		uint4 biSize;           //4�ֽڣ���Ϣͷ�Ĵ�С����40��

		int4 biWidth;           //4�ֽڣ�������Ϊ��λ˵��ͼ��Ŀ�ȣ�

		int4 biHeight;          //4�ֽڣ�������Ϊ��λ˵��ͼ��ĸ߶ȣ����Ϊ����˵��λͼ����

		uint2 biPlanes;         //2�ֽڣ�ΪĿ���豸˵����ɫƽ�������ܱ�����Ϊ1��

		uint2 biBitCount;       //2�ֽڣ�˵��������/��������ֵ��1��2��4��8��16��24��32��

		uint4 biCompression;    //4�ֽڣ�˵��ͼ���ѹ�����ͣ�0(BI_RGB)��ʾ��ѹ����

		uint4 biSizeImage;      //4�ֽڣ�˵��λͼ���ݵĴ�С������BI_RGB��ʽʱ����������Ϊ0��

		int4 biXPelsPerMeter;   //4�ֽڣ���ʾˮƽ�ֱ��ʣ���λ������/�ף�

		int4 biYPelsPerMeter;   //4�ֽڣ���ʾ��ֱ�ֱ��ʣ���λ������/�ף�

		uint4 biClrUsed;        //4�ֽڣ�λͼʹ�õĵ�ɫ���е���ɫ��������Ϊ0˵��ʹ�����У�

		uint4 biClrImportant;   //4�ֽڣ���ͼ����ʾ����ҪӰ�����ɫ��������Ϊ0˵������Ҫ��

	} BMPInfoHeader;

	// �ָ�Ĭ��

#pragma  pack(8)

/** -------------------------------------------------------- */



/** ---------------------���к�����------------------------- */

public:

	/**

	 * ���캯������ʼ��һ���յ�BMPImage

	 */

	explicit BMPImage();

	/**

	 * ���캯��������һ��BMPͼ��,��ʧ��ʱ���׳��쳣

	 * @param bmp_file_path ͼ��·��

	 */

	explicit BMPImage(const char* bmp_file_path);

	/**

	 * ���캯����������СΪwidth*height��24λ�ĺ�ɫͼ��

	 * ����ʧ��ʱ���׳��쳣��

	 * @param width ���

	 * @param height �߶�

	 * @param depth ��ȣ�Ŀǰ��֧��24λ��32λͼ��

	 */

	explicit BMPImage(int4 width, int4 height, uint2 depth = 24);

	/**

	 * ��������

	 */

	virtual ~BMPImage();

	/**

	  * ������СΪwidth*height��24λ�ĺ�ɫͼ��

	  * @param width ���

	  * @param height �߶�

	  * @param depth ��ȣ�Ŀǰ��֧��24λͼ��

	  * @return �ɹ�����true������false

	  */

	bool create(int4 width, int4 height, uint2 depth = 24);

	/**

	 * ����һ��BMPͼ��

	 * @param bmp_file_path ͼ��·��

	 * @return �ɹ�����true������false

	 */

	bool open(const char* bmp_file_path);

	/**

	 * ����BMPͼ��

	 * @param save_path ����·��

	 * @return �ɹ�����true������false

	 */

	bool save(const char* save_path);

	/**

	 * ����(row,col)��RGBֵ(����24λBMPͼ��)������

	 * @param row ��

	 * @param col ��

	 * @return RGBֵ������

	 */

	void copy(const BMPImage* img);

	BGR& rgb(uint row, uint col);

	/**

	 * ����(row,col)��RGBAֵ(����32λBMPͼ��)������

	 * @param row ��

	 * @param col ��

	 * @return RGBAֵ������

	 */

	BGRA& rgba(uint row, uint col);

	/**

	 * ���ͼ��

	 * @return �ɹ�����true������false

	 */

	bool clear();



	/**

	 * ����ͼ����

	 * @return ���

	 */

	int4 width();

	/**

	 * ����ͼ��߶�

	 * @return  �߶�

	 */

	int4 height();

	/**

	 * ����ͼ�����

	 * @return ���

	 */

	uint2 depth();

	/** -------------------------------------------------------- */



	/** ----------------------���б�����------------------------ */

public:

	int4 m_width;       //ͼ����

	int4 m_height;      //ͼ�����

	uint2 m_depth;      //ͼ�����

	ulong m_row_size;   //ÿ���ֽ���

	uchar* m_data;      //ͼ�����ݴ洢��



	BMPFileHeader m_file_header;    //BMPͼ����ļ�ͷ

	BMPInfoHeader m_info_header;    //BMPͼ�����Ϣͷ

	uint m_color_palette_size;      //BMP�ĵ�ɫ�������С

	ColorPalette* m_color_palette;  //��ɫ��(Color Palette),��ѡ��

};
/** -------------------------------------------------------- */



#endif //BMPIMAGE_H


