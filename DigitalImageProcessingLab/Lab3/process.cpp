#include "process.h"

Process::Process()
{

}
QVector<QVector<double>> Process::averageFilter(int kSize)
{
    QVector<QVector<double>> value;
    value.resize(kSize);
    for(int i=0;i<kSize;i++) value[i].resize(kSize);
    for(int i=0;i<kSize;i++)
        for(int j=0;j<kSize;j++)
            value[i][j]=1.0/pow(kSize,2);
    return value;
}
Image Process::grayTrans(int mid, int width, Image image)
{
    int x=image.getX();
    int y=image.getY();
    //构造图像并设置灰度
    Image result(x, y);
    result.setGrayscale(256);
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
        {
            if(image.getAPixel(i,j)<=(mid-(width>>1))) result.setAPixel(i,j,0);
            else if(image.getAPixel(i,j)>(mid+(width>>1))) result.setAPixel(i,j,255);
            else result.setAPixel(i,j,(image.getAPixel(i,j)-mid+(width>>1))*255/width);
        }
    return result;
}
Image Process::denoise(Image image,int kSize)
{
    QVector<QVector<double>> filter=averageFilter(kSize);
    int x=image.getX();
    int y=image.getY();
    Image resultImage(image);//首先设置好边缘像素&中间需要进行均值操作的像素
    //对中间需要进行均值操作的像素计算均值
    int tmp;//使用int防止计算像素和时溢出
    //int cnt=0;
    for(int i=kSize/2;i<x-kSize/2;i++)
    {
        for(int j=kSize/2;j<y-kSize/2;j++)
        {
            tmp=0;
            for(int k=-kSize/2;k<=kSize/2;k++)
            {
                for(int l=-kSize/2;l<=kSize/2;l++)
                {
                    tmp+=image.getAPixel(i+k,j+l);
                }
            }
            //if(tmp/kSize/kSize!=image.getAPixel(i,j)) cnt++;
            resultImage.setAPixel(i,j,tmp/kSize/kSize);
        }
    }
    //qDebug("%d",cnt);
    return resultImage;
}
Image Process::sharpen(Image image, int kSize, double alpha)
{
    int x=image.getX();
    int y=image.getY();
    QVector<QVector<double>> filter=averageFilter(kSize);
    Image lowF=denoise(image,kSize);//先平滑
    Image result(image);
    unsigned short lowPixel;
    unsigned short origPixel;
    unsigned short highPixel;
    for(int i=kSize/2;i<x-kSize/2;i++)
        for(int j=kSize/2;j<y-kSize/2;j++)
        {
            lowPixel=lowF.getAPixel(i,j);
            origPixel=image.getAPixel(i,j);
            //高频部分的像素
            highPixel=origPixel>lowPixel?origPixel-lowPixel:lowPixel-origPixel;
            result.setAPixel(i,j,origPixel+alpha*highPixel);
        }
    return result;
}
Image Process::Laplacian(Image image,double alpha)
{
    int laplace_mask[9]={0,-1,0,-1,4,-1,0,-1,0};
    int x=image.getX();
    int y=image.getY();
    int tmp=0;
    int counter=0;
    Image result(image);
    for(int i=1;i<x-1;i++)
    {
        for(int j=1;j<y-1;j++)
        {
            for(int k=i-1;k<=i+1;k++)
            {
                for(int l=j-1;l<=j+1;l++)
                {
                    tmp+=laplace_mask[counter]*image.getAPixel(k,l);
                    counter++;
                }
            }
            result.setAPixel(i,j,tmp*alpha+image.getAPixel(i,j));
            tmp=0;
            counter=0;
        }
    }
    return result;
}
