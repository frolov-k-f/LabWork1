/*
 * Kirill Frolov
 * st141840@student.spbu.ru
 * LabWork1
 */

#include "image_transform.h"
#include <algorithm>
#include "px.h"

BitmapImage rotateClockwise(const BitmapImage &input)
{
    int w = input.width(), h = input.height();
    BitmapImage result;
    result.setSize(h, w);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            result.data()[x * h + (h - 1 - y)] = input.data()[y * w + x];
    return result;
}

BitmapImage rotateCounterClockwise(const BitmapImage &input)
{
    int w = input.width(), h = input.height();
    BitmapImage result;
    result.setSize(h, w);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            result.data()[(w - 1 - x) * h + y] = input.data()[y * w + x];
    return result;
}

BitmapImage applyGaussian(const BitmapImage &input)
{
    int w = input.width(), h = input.height();
    BitmapImage result;
    result.setSize(w, h);
    const int kernel[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
    int kernelSum = 16;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int sumB = 0, sumG = 0, sumR = 0;
            for (int ky = -1; ky <= 1; ky++)
            {
                for (int kx = -1; kx <= 1; kx++)
                {
                    int clampedX = std::clamp(x + kx, 0, w - 1);
                    int clampedY = std::clamp(y + ky, 0, h - 1);
                    const Px &px = input.data()[clampedY * w + clampedX];
                    int weight = kernel[ky + 1][kx + 1];
                    sumB += px.blue * weight;
                    sumG += px.green * weight;
                    sumR += px.red * weight;
                }
            }
            Px newPx;
            newPx.blue  = static_cast<uint8_t>(sumB / kernelSum);
            newPx.green = static_cast<uint8_t>(sumG / kernelSum);
            newPx.red   = static_cast<uint8_t>(sumR / kernelSum);
            result.data()[y * w + x] = newPx;
        }
    }
    return result;
}