#include "zoom.h"

Zoom::Zoom()
{
}
Image Zoom::ZoomImage(Image image, double scale)//scale为缩放倍数
{
    int oriX=image.getX();
    int oriY=image.getY();
    int sizeX=oriX*scale;
    int sizeY=oriY*scale;
    Image newImage(sizeX,sizeY);
    double x,y,alpha,beta;
    int xint,yint;
    for(int i=0;i<sizeX;i++)
        for(int j=0;j<sizeY;j++)
        {
            //算出(x',y')在原图像中的坐标
            x=i/scale;
            y=j/scale;
            if((x>=oriX)||(x<0)||(y>=oriY)||(y<0))//如果在原图像中没有点
            {
                newImage.pixel[i][j]=0;
                continue;
            }
            xint=floor(x),yint=floor(y);
            alpha=x-xint,beta=y-yint;
            // qDebug("%d,%d",i,j);
            if(xint<oriX-1&&yint<oriY-1)//防止+1引起数组越界
                newImage.pixel[i][j]=(1-alpha)*(1-beta)*image.pixel[xint][yint]+(1-alpha)*beta*image.pixel[xint][yint+1]+(1-beta)*alpha*image.pixel[xint+1][yint]+alpha*beta*image.pixel[xint+1][yint+1];
            else newImage.pixel[i][j]=image.pixel[xint][yint];
        }
    return newImage;
}
