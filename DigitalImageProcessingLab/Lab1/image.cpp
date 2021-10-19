#include "image.h"
#include <QColor>

Image::Image(int x,int y)
{
    this->x=x;
    this->y=y;
    this->pixel=new unsigned char*[x];
    for(int i=0;i<x;i++)
        this->pixel[i]=new unsigned char[y];
}
Image::Image(QString path)
{
    QImage qimage=*new QImage(path);
    //转化为灰度图像
    this->x=qimage.width();
    this->y=qimage.height();
    this->pixel=new unsigned char*[x];
    for(int i=0;i<x;i++)
        this->pixel[i]=new unsigned char[y];
    //设置像素的灰度值
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
        {
            this->pixel[i][j]=qGray(qimage.pixelColor(i,j).rgb())>>5;//转化为灰度值为0-7
        }
}
Image::Image(QImage qimage)
{
    this->x=qimage.width();
    this->y=qimage.height();
    this->pixel=new unsigned char*[x];
    for(int i=0;i<x;i++)
        this->pixel[i]=new unsigned char[y];
    //设置像素的灰度值
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
        {

            this->pixel[i][j]=qGray(qimage.pixelColor(i,j).rgb())>>5;//转化为灰度值为0-7
        }
}
QPixmap Image::getPixmap()
{
    QImage qimage(this->x,this->y,QImage::Format_Grayscale8);

    QColor qcolor;
    for(int i=0;i<this->x;i++)
        for(int j=0;j<this->y;j++)
        {
            //左移5位转化为256位灰度，并将rgb均设置为灰度值
            qcolor.setRgb(pixel[i][j]<<5,pixel[i][j]<<5,pixel[i][j]<<5);
            qimage.setPixelColor(i,j,qcolor);
        }
    QPixmap pixmap;
    pixmap.convertFromImage(qimage);
    return pixmap;
}
int Image::getX(){return this->x;}
int Image::getY(){return this->y;}
void Image::setX(int x){this->x=x;}
void Image::setY(int y){this->y=y;}

