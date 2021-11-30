#include "image.h"

Image::Image(int x, int y)
{
    this->x=x;
    this->y=y;
    this->pixel.resize(x);
    for(int i=0;i<x;i++)
        this->pixel[i].resize(y);
}

Image::Image(QString path)
{
    QImage qimage=*new QImage(path);
    //转化为灰度图像
    this->x=qimage.width();
    this->y=qimage.height();
    this->pixel.resize(x);
    for(int i=0;i<x;i++)
        this->pixel[i].resize(y);
    //设置像素的灰度值
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
        {
            this->pixel[i][j]=qGray(qimage.pixelColor(i,j).rgb());//转化为灰度值为0-7
        }
}
Image::Image(QImage qimage)
{
    this->x=qimage.width();
    this->y=qimage.height();
    this->pixel.resize(x);
    for(int i=0;i<x;i++)
        this->pixel[i].resize(y);
    //设置像素的灰度值
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
            this->pixel[i][j]=qGray(qimage.pixelColor(i,j).rgb());
}
int Image::getX(){return this->x;}
int Image::getY(){return this->y;}
QVector<QVector<unsigned char>> Image::getPixel(){return pixel;}
unsigned char Image::getAPixel(int x, int y){return this->pixel[x][y];}
QPixmap Image::getPixmap()
{
    QImage qimage(this->x,this->y,QImage::Format_Grayscale8);

    QColor qcolor;
    for(int i=0;i<this->x;i++)
        for(int j=0;j<this->y;j++)
        {
            //将rgb均设置为灰度值
            qcolor.setRgb(pixel[i][j],pixel[i][j],pixel[i][j]);
            qimage.setPixelColor(i,j,qcolor);
        }
    QPixmap pixmap;
    pixmap.convertFromImage(qimage);
    return pixmap;
}
void Image::setX(int x){this->x=x;}
void Image::setY(int y){this->y=y;}
void Image::setPixel(QVector<QVector<unsigned char>> pixel){this->pixel=pixel;}
void Image::setAPixel(int x, int y, unsigned char grayScale){this->pixel[x][y]=grayScale;}
void Image::display(QString title)
{
    QLabel *viewedLabel=new QLabel(nullptr);
    viewedLabel->setPixmap(this->getPixmap());
    viewedLabel->setWindowTitle(title);
    viewedLabel->resize(this->x,this->y);
    viewedLabel->show();
}
