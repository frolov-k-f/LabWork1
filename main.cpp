/*
 * Kirill Frolov
 * st141840@student.spbu.ru
 * LabWork1
 */

#include <iostream>
#include "bitmap_image.h"
#include "image_transform.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: lab1 <input.bmp>\n";
        return 1;
    }
    BitmapImage img;
    if (!img.load(argv[1]))
    {
        std::cerr << "Failed to load BMP\n";
        return 2;
    }

    auto cw = rotateClockwise(img);
    cw.save("rot_cw.bmp");

    auto ccw = rotateCounterClockwise(img);
    ccw.save("rot_ccw.bmp");

    auto g = applyGaussian(cw);
    g.save("gauss.bmp");

    return 0;
}