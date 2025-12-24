/* 
 * Kirill Frolov
 * st141840@student.spbu.ru
 * LabWork1
 */
 
#include "bitmap.h"
#include <iostream>

bool Bitmap::read(std::istream &in) {
    in.read(reinterpret_cast<char*>(&fileHdr), sizeof(fileHdr));
    in.read(reinterpret_cast<char*>(&infoHdr), sizeof(infoHdr));
    return !in.fail();
}

bool Bitmap::write(std::ostream &out) const {
    out.write(reinterpret_cast<const char*>(&fileHdr), sizeof(fileHdr));
    out.write(reinterpret_cast<const char*>(&infoHdr), sizeof(infoHdr));
    return !out.fail();
}

bool Bitmap::isValid() const {
    return fileHdr.signature == 0x4D42 && infoHdr.bitsPerPixel == 24 && infoHdr.compressionMethod == 0;
}

int Bitmap::width() const {
    return infoHdr.imageWidth;
}

int Bitmap::absoluteHeight() const {
    return infoHdr.imageHeight < 0 ? -infoHdr.imageHeight : infoHdr.imageHeight;
}

bool Bitmap::isStoredBottomUp() const {
    return infoHdr.imageHeight > 0;
}

int Bitmap::bitsPerPixel() const {
    return infoHdr.bitsPerPixel;
}

uint32_t Bitmap::pixelOffset() const {
    return fileHdr.pixelDataOffset;
}

void Bitmap::initializeDefaults(int w, int h) {
    fileHdr.signature = 0x4D42;
    fileHdr.reserved1 = 0;
    fileHdr.reserved2 = 0;
    fileHdr.pixelDataOffset = sizeof(BitmapFileHdr) + sizeof(BitmapInfoHdr);

    infoHdr.headerSize = sizeof(BitmapInfoHdr);
    infoHdr.imageWidth = w;
    infoHdr.imageHeight = h;
    infoHdr.colorPlanes = 1;
    infoHdr.bitsPerPixel = 24;
    infoHdr.compressionMethod = 0;
    infoHdr.xResolution = 0;
    infoHdr.yResolution = 0;
    infoHdr.colorsUsed = 0;
    infoHdr.importantColors = 0;

    refreshSizes(w, h);
}

void Bitmap::refreshSizes(int w, int h) {
    const int rowBytes = bytesPerRow(w);
    infoHdr.imageSizeBytes = rowBytes * std::abs(h);
    fileHdr.fileSize = fileHdr.pixelDataOffset + infoHdr.imageSizeBytes;
}

int Bitmap::bytesPerRow(int w) const {
    return ((w * 3 + 3) / 4) * 4;
}