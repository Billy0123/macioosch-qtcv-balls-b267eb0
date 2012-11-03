#include "matqimage.h"

QImage mat2qimage(const Mat original_mat)
{
    // nie potrafię przekonwertować Mat na QImage
    // bez pośredniej konwersji na przestarzały format IplImage
    IplImage original = original_mat;

    QImage displayed((unsigned char *) original.imageData,
                     original.width,
                     original.height,
                     original.widthStep,
                     QImage::Format_RGB888);

    return displayed.rgbSwapped();
}
