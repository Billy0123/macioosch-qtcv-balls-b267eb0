#ifndef MATQIMAGE_H
#define MATQIMAGE_H

#include <QImage>
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

QImage mat2qimage(const Mat original_mat);

#endif // MATQIMAGE_H
