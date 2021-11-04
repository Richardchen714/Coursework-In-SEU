#include "image.h"
#include <QColor>
#include <QByteArray>
#include <QFile>

Image::Image(int x,int y)
{
    this->x=x;
    this->y=y;
    this->pixel=new unsigned short*[x];
    for(int i=0;i<x;i++)
        this->pixel[i]=new unsigned short[y];
}
Image::Image(QString path)//从raw文件中读取图片
{
    QFile file;
    file.setFileName(path);
    if(!file.open(QIODevice::ReadOnly)) qDebug("Failed to open file");
    QByteArray array=file.readAll();
    //设置高度、宽度、像素值、有效灰度范围为0-2^12-1
    int width,height;
    width=(((unsigned char)array[3])<<24)+(((unsigned char)array[2])<<16)+
            (((unsigned char)array[1])<<8)+(unsigned char)array[0];
    height=(((unsigned char)array[7])<<24)+(((unsigned char)array[6])<<16)+
            (((unsigned char)array[5])<<8)+(unsigned char)array[4];

    this->x=width;
    this->y=height;
    this->pixel=new unsigned short*[width];
    for(int i=0;i<width;i++)
        this->pixel[i]=new unsigned short[height];
    this->grayscale=1<<12;
    for(int i=0;i<width;i++)
        for(int j=0;j<height;j++)
        {
            this->pixel[i][j]=(unsigned char)array[8+(j*width+i)*2]
                +(((((unsigned char)array[8+(j*width+i)*2+1])<<4)>>4)<<8);
        }
}
Image::Image(QImage qimage)
{
    this->x=qimage.width();
    this->y=qimage.height();
    this->pixel=new unsigned short*[x];
    for(int i=0;i<x;i++)
        this->pixel[i]=new unsigned short[y];
    //设置像素的灰度值
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
        {
            this->pixel[i][j]=qGray(qimage.pixelColor(i,j).rgb());
        }
}
QPixmap Image::getPixmap()
{
    QImage qimage(this->x,this->y,QImage::Format_Grayscale8);

    QColor qcolor;
    for(int i=0;i<this->x;i++)
        for(int j=0;j<this->y;j++)
        {
            if(this->grayscale==1<<12)
            //将rgb均设置为灰度值
            //由于使用的qt版本不支持12位灰度，此处将其映射为8位灰度来显示
                qcolor.setRgb(pixel[i][j]>>4,pixel[i][j]>>4,pixel[i][j]>>4);
            else if(this->grayscale==1<<8)
                qcolor.setRgb(pixel[i][j],pixel[i][j],pixel[i][j]);
            qimage.setPixelColor(i,j,qcolor);
        }
    QPixmap pixmap;
    pixmap.convertFromImage(qimage);
    return pixmap;
}
int Image::getX(){return this->x;}
int Image::getY(){return this->y;}
int Image::getGrayscale(){return this->grayscale;}
void Image::setX(int x){this->x=x;}
void Image::setY(int y){this->y=y;}
void Image::setGrayscale(int grayscale){this->grayscale=grayscale;}

