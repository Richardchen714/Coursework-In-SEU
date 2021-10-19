#include <cmath>
#include "rotate.h"
using namespace std;
const double pi=acos(-1.0);
Rotate::Rotate()
{

}

Image Rotate::rotateImage(Image image,int angle)
{
    double rad=angle*pi/180;//角度转弧度
    int sizeX=image.getX();
    int sizeY=image.getY();
    Image newImage(sizeX,sizeY);
    int centerX=sizeX>>1;//图像中心
    int centerY=sizeY>>1;
    double x,y,alpha,beta;
    int xint,yint;
    for(int i=0;i<sizeX;i++)
        for(int j=0;j<sizeY;j++)
        {
            //算出(x',y')在原图像中的坐标
            x=(i-centerX)*cos(rad)+(j-centerY)*sin(rad)+centerX;
            y=(j-centerY)*cos(rad)-(i-centerX)*sin(rad)+centerY;
            if((x>=sizeX)||(x<0)||(y>=sizeY)||(y<0))//如果在原图像中没有点
            {
                newImage.pixel[i][j]=0;
                continue;
            }
            xint=floor(x),yint=floor(y);
            alpha=x-xint,beta=y-yint;
            if(xint<sizeX-1&&yint<sizeY-1)//防止xint或yint+1引起数组越界
                newImage.pixel[i][j]=(1-alpha)*(1-beta)*image.pixel[xint][yint]+(1-alpha)*beta*image.pixel[xint][yint+1]+(1-beta)*alpha*image.pixel[xint+1][yint]+alpha*beta*image.pixel[xint+1][yint+1];
            else newImage.pixel[i][j]=image.pixel[xint][yint];//xint和yint不可能越界
        }
    return newImage;
}
