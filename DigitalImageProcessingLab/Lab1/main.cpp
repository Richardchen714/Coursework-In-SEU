#include "widget.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include "rotate.h"
#include "image.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    Rotate rotate;
    QString path="C:/Users/richardchen0714/Documents/Image/barbara.bmp";
    Image image(path);
    Image rotated=rotate.rotateImage(image,30);
    QImage qimage(rotated.getX(),rotated.getY(),QImage::Format_Grayscale8);

    QColor qcolor;
    for(int i=0;i<qimage.width();i++)
        for(int j=0;j<qimage.height();j++)
        {
            //将rgb均设置为灰度值
            qcolor.setRgb(rotated.pixel[i][j],rotated.pixel[i][j],rotated.pixel[i][j]);
            qimage.setPixelColor(i,j,qcolor);
        }
    qimage.save("C:/Users/richardchen0714/Documents/Image/barbara_30.bmp");
    w.setWindowTitle("Image Transformation");
    w.show();
    return a.exec();
}
