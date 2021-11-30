#include "seg.h"
Seg::Seg()
{
}
Image Seg::Otsu(Image image)
{
    Image result(image);
    QVector<int> hist(256); //灰度分布直方图，初始化大小为256
    int u = 0;
    int w = image.getX();
    int h = image.getY();
    int size = w * h;
    unsigned char pix;
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            pix = image.getAPixel(i, j);
            hist[pix]++;
            u += pix;
        }
    double val = (1.0 * u) / float(size);
    float max = 0;
    int threshold = 0;
    for (int i = 1; i < 255; i++)
    {
        //int x=var(hist,i,val,size);
        long long total = size * val;
        int n = 0;
        long long m = 0;
        for (int j = 0; j < i; j++)
        {
            m += j * hist[j];
            n += hist[j];
        }
        long long rem = total - m;
        int rempix = size - n;
        float w0 = (1.0 * n) / (1.0 * size);
        float w1 = (1.0 * rem) / (1.0 * size);
        float u0 = (1.0 * m) / (1.0 * n);
        float u1 = (1.0 * rem) / (1.0 * rempix);
        int x = w0 * w1 * (u0 - u1) * (u0 - u1);
        if (x > max)
        {
            max = x;
            threshold = i;
        }
    }
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            pix = image.getAPixel(i, j);
            if (pix > threshold)
                result.setAPixel(i, j, 255);
            else
                result.setAPixel(i, j, 0);
        }
    return result;
}

Image Seg::maxEntropy(Image image)
{
    Image result(image);
    QVector<int> hist(256); //灰度分布直方图，初始化大小为256
    int u = 0;
    int w = image.getX();
    int h = image.getY();
    unsigned char pix;
    unsigned thresh = 0.0;
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            pix = image.getAPixel(i, j);
            hist[pix]++;
            u += pix;
        }
    double prob = 0.0;
    double maxE = 0.0;
    int totalpix = w * h;
    for (int i = 0; i < 256; i++)
    {
        float HO = 0.0; //前景熵
        float HB = 0.0; //背景熵
        //计算前景像素数
        int frontpix = 0;
        for (int j = 0; j < i; ++j)
        {
            frontpix += hist[j];
        }
        //计算前景熵
        for (int j = 0; j < i; ++j)
        {
            if (hist[j] != 0)
            {
                prob = (float)hist[j] / frontpix;
                HO = HO + prob * log(1 / prob);
            }
        }
        //计算背景熵
        for (int k = i; k < 256; ++k)
        {
            if (hist[k] != 0)
            {
                prob = (float)hist[k] / (totalpix - frontpix);
                HB = HB + prob * log(1 / prob);
            }
        }
        //计算最大熵
        if (HO + HB > maxE)
        {
            maxE = HO + HB;
            thresh = i;
        }
    }

    //阈值处理
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (image.getAPixel(i, j) > thresh)
                result.setAPixel(i, j, 255);
            else
                result.setAPixel(i, j, 0);
        }
    }
    return result;
}
