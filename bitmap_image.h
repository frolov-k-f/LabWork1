/* 
 * Kirill Frolov
 * st141840@student.spbu.ru
 * LabWork1
 */

#ifndef BITMAP_IMAGE
#define BITMAP_IMAGE

#pragma once
#include "bitmap.h"
#include <vector>
#include <string>

class Image {
public:
    virtual bool load(const std::string &path) = 0;
    virtual bool save(const std::string &path) const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual std::vector<Px>& data() = 0;
    virtual const std::vector<Px>& data() const = 0;
    virtual ~Image() = default;
};

class BitmapImage : public Image {
    int imgWidth = 0, imgHeight = 0;
    std::vector<Px> pixelData;
    Bitmap meta;

public:
    BitmapImage() = default;
    bool load(const std::string &path) override;
    bool save(const std::string &path) const override;
    int width() const override;
    int height() const override;
    std::vector<Px>& data() override;
    const std::vector<Px>& data() const override;
    void setSize(int w, int h);
};
#endif