/* 
 * Kirill Frolov
 * st141840@student.spbu.ru
 * LabWork1
 */

#ifndef BITMAP_H
#define BITMAP_H

#pragma once
#include <cstdint>
#include <istream>
#include <ostream>
#include "px.h"

#pragma pack(push, 1)
struct BitmapFileHdr {
    uint16_t signature;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelDataOffset;
};

struct BitmapInfoHdr {
    uint32_t headerSize;
    int32_t  imageWidth;
    int32_t  imageHeight;
    uint16_t colorPlanes;
    uint16_t bitsPerPixel;
    uint32_t compressionMethod;
    uint32_t imageSizeBytes;
    int32_t  xResolution;
    int32_t  yResolution;
    uint32_t colorsUsed;
    uint32_t importantColors;
};
#pragma pack(pop)

class Bitmap {
    BitmapFileHdr fileHdr{};
    BitmapInfoHdr infoHdr{};

public:
    Bitmap() = default;
    bool read(std::istream &in);
    bool write(std::ostream &out) const;
    bool isValid() const;
    int width() const;
    int absoluteHeight() const;
    bool isStoredBottomUp() const;
    int bitsPerPixel() const;
    uint32_t pixelOffset() const;
    void initializeDefaults(int w, int h);
    void refreshSizes(int w, int h);
    int bytesPerRow(int w) const;
};

#endif