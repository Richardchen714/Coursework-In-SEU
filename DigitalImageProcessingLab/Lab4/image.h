#ifndef IMAGE_H
#define IMAGE_H
#include<QImage>
#include<QPixmap>
#include<QVector>
#include<QLabel>

class Image
{
public:
    Image(int, int);//构造函数为尺寸
    Image(QString);//根据文件构造图像
    Image(QImage);//根据QImage来构造图像
    int getX();
    int getY();
    QVector<QVector<unsigned char>> getPixel();
    unsigned char getAPixel(int,int);
    QPixmap getPixmap();//此处使用QPixmap便于显示
    void setX(int);
    void setY(int);
    void setPixel(QVector<QVector<unsigned char>>);
    void setAPixel(int, int, unsigned char);
    void display(QString);
private:
    int x,y;//尺寸
    QVector<QVector<unsigned char>> pixel;//每个像素灰度值
};

#endif // IMAGE_H
