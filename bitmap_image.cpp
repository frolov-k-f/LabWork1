/*
 * Kirill Frolov
 * st141840@student.spbu.ru
 * LabWork1
 */

#include "bitmap_image.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "px.h"

int BitmapImage::width() const
{
    return imgWidth;
}
int BitmapImage::height() const
{
    return imgHeight;
}
std::vector<Px>& BitmapImage::data()
{
    return pixelData;
}
const std::vector<Px>& BitmapImage::data() const
{
    return pixelData;
}

void BitmapImage::setSize(int ww, int hh)
{
    imgWidth = ww;
    imgHeight = hh;
    pixelData.assign(static_cast<size_t>(imgWidth) * static_cast<size_t>(imgHeight), Px{0,0,0});
    meta.initializeDefaults(imgWidth, imgHeight);
    meta.refreshSizes(imgWidth, imgHeight);
}

bool BitmapImage::load(const std::string &path)
{
    std::ifstream in(path, std::ios::binary);
    if (!in)
    {
        std::cerr << "BitmapImage::load: cannot open file: " << path << "\n";
        return false;
    }
    if (!meta.read(in))
    {
        std::cerr << "BitmapImage::load: failed to read header\n";
        return false;
    }
    if (!meta.isValid())
    {
        std::cerr << "BitmapImage::load: invalid or unsupported BMP header\n";
        return false;
    }
    imgWidth = meta.width();
    imgHeight = meta.absoluteHeight();
    in.seekg(static_cast<std::streamoff>(meta.pixelOffset()), std::ios::beg);

    int rowSize = meta.bytesPerRow(imgWidth);
    std::vector<uint8_t> row(static_cast<size_t>(rowSize));
    pixelData.assign(static_cast<size_t>(imgWidth) * static_cast<size_t>(imgHeight), Px{0,0,0});
    bool bottomUp = meta.isStoredBottomUp();

    for (int y = 0; y < imgHeight; ++y)
    {
        in.read(reinterpret_cast<char*>(row.data()), rowSize);
        if (!in)
        {
            std::cerr << "BitmapImage::load: unexpected EOF while reading pixel data\n";
            return false;
        }
        int targetRow = bottomUp ? (imgHeight - 1 - y) : y;
        for (int x = 0; x < imgWidth; ++x)
        {
            int src = x * 3;
            Px p;
            p.blue = row[static_cast<size_t>(src) + 0];
            p.green = row[static_cast<size_t>(src) + 1];
            p.red = row[static_cast<size_t>(src) + 2];
            pixelData[static_cast<size_t>(targetRow) * static_cast<size_t>(imgWidth) + static_cast<size_t>(x)] = p;
        }
    }
    return true;
}

bool BitmapImage::save(const std::string &path) const
{
    if (imgWidth <= 0 || imgHeight <= 0)
    {
        std::cerr << "BitmapImage::save: invalid image size\n";
        return false;
    }
    std::ofstream out(path, std::ios::binary);
    if (!out)
    {
        std::cerr << "BitmapImage::save: cannot open file for writing: " << path << "\n";
        return false;
    }

    Bitmap outMeta;
    outMeta.initializeDefaults(imgWidth, imgHeight);
    outMeta.refreshSizes(imgWidth, imgHeight);

    if (!outMeta.write(out))
    {
        std::cerr << "BitmapImage::save: failed to write header\n";
        return false;
    }

    int rowSize = outMeta.bytesPerRow(imgWidth);
    std::vector<uint8_t> row(static_cast<size_t>(rowSize));

    for (int y = imgHeight - 1; y >= 0; --y)
    {
        std::fill(row.begin(), row.end(), 0);
        for (int x = 0; x < imgWidth; ++x)
        {
            const Px &p = pixelData[static_cast<size_t>(y) * static_cast<size_t>(imgWidth) + static_cast<size_t>(x)];
            int idx = x * 3;
            row[static_cast<size_t>(idx) + 0] = p.blue;
            row[static_cast<size_t>(idx) + 1] = p.green;
            row[static_cast<size_t>(idx) + 2] = p.red;
        }
        out.write(reinterpret_cast<const char*>(row.data()), rowSize);
        if (!out)
        {
            std::cerr << "BitmapImage::save: failed while writing row\n";
            return false;
        }
    }
    return true;
}