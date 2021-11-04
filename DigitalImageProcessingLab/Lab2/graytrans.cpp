#include "graytrans.h"

GrayTrans::GrayTrans()
{

}

Image GrayTrans::trans(int mid, int width, Image image)
{
    int x=image.getX();
    int y=image.getY();
    //构造图像并设置灰度
    Image result(x,y);
    result.setGrayscale(256);
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
        {
            if(image.pixel[i][j]<=(mid-(width>>1))) result.pixel[i][j]=0;
            else if(image.pixel[i][j]>(mid+(width>>1))) result.pixel[i][j]=255;
            else result.pixel[i][j]=(image.pixel[i][j]-mid+(width>>1))*255/width;
        }
    return result;
}
