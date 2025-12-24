/* 
 * Kirill Frolov
 * st141840@student.spbu.ru
 * LabWork1
 */

#ifndef BITMAP_IMAGE_H
#define BITMAP_IMAGE_H

#include "bitmap_image.h"

BitmapImage rotateClockwise(const BitmapImage &input);
BitmapImage rotateCounterClockwise(const BitmapImage &input);
BitmapImage applyGaussian(const BitmapImage &input);

#endif