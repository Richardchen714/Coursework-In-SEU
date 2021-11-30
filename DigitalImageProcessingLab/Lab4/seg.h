#ifndef SEG_H
#define SEG_H
#include <QVector>
#include "image.h"

class Seg
{
public:
    Seg();
    Image Otsu(Image);
    Image maxEntropy(Image);
};

#endif // SEG_H
