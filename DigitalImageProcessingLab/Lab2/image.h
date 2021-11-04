#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>
#include <QPixmap>

class Image
{
public:
    Image(int, int);//构造函数为尺寸
    Image(QString);//根据文件构造图像，本实验为根据raw构建
    Image(QImage);//根据QImage来构造图像
    int getX();
    int getY();
    int getGrayscale();
    QPixmap getPixmap();//此处使用QPixmap便于显示
    void setX(int);
    void setY(int);
    void setGrayscale(int);
    unsigned short** pixel;//每个像素灰度值
private:
    int x,y;//尺寸
    int grayscale;//有效灰度范围
};

#endif // IMAGE_H
