#ifndef PROCESS_H
#define PROCESS_H
#include <QVector>
#include <cmath>
#include "image.h"

class Process
{
public:
    Process();
    QVector<QVector<double> > averageFilter(int);
    Image grayTrans(int,int,Image);
    Image denoise(Image,int);
    Image sharpen(Image,int,double);
    Image Laplacian(Image,double);
};

#endif // PROCESS_H
