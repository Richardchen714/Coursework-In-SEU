#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>
#include <QPixmap>
#include <QVector>
#include <QLabel>
#include <QScrollArea>

class Image
{
public:
    Image(int, int);//构造函数为尺寸
    Image(QString);//根据文件构造图像，本实验为根据raw构建
    Image(QImage);//根据QImage来构造图像
    int getX();
    int getY();
    int getGrayscale();
    QVector<QVector<unsigned short>> getPixel();
    unsigned short getAPixel(int,int);
    QPixmap getPixmap();//此处使用QPixmap便于显示
    void setX(int);
    void setY(int);
    void setGrayscale(int);
    void setPixel(QVector<QVector<unsigned short>>);
    void setAPixel(int, int, unsigned short);
    void display(QString);
private:
    int x,y;//尺寸
    int grayscale;//有效灰度范围
    QVector<QVector<unsigned short>> pixel;
};

#endif // IMAGE_H
