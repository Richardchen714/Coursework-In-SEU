#include "translation.h"

Translation::Translation()
{
}

Image Translation::imageTranslation(Image image,double x,double y)
{
    //图像尺寸
    int sizeX=image.getX();
    int sizeY=image.getY();
    Image newImage=*new Image(sizeX,sizeY);
    //新图像的pixel
    double xOri,yOri,alpha,beta;
    int xint,yint;
    for(int i=0;i<sizeX;i++)
        for(int j=0;j<sizeY;j++)
        {
            //算出(x',y')在原图像中的坐标
            xOri=i-x;
            yOri=j-y;
            if((xOri>=sizeX)||(xOri<0)||(yOri>=sizeY)||(yOri<0))//如果在原图像中没有点
            {
                newImage.pixel[i][j]=0;
                continue;
            }
            xint=floor(xOri),yint=floor(yOri);
            alpha=xOri-xint,beta=yOri-yint;
            if(xint<sizeX-1&&yint<sizeY-1)//防止+1引起数组越界
                newImage.pixel[i][j]=(1-alpha)*(1-beta)*image.pixel[xint][yint]+(1-alpha)*beta*image.pixel[xint][yint+1]+(1-beta)*alpha*image.pixel[xint+1][yint]+alpha*beta*image.pixel[xint+1][yint+1];
            else newImage.pixel[i][j]=image.pixel[xint][yint];
        }
    return newImage;
}
