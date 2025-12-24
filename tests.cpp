#include <gtest/gtest.h>
#include "bitmap_image.h"
#include "bitmap.h"
#include "image_transform.h"
#include <fstream>
#include <vector>

TEST(BitmapImageTest, LoadValidFile)
{
    BitmapImage img;
    EXPECT_TRUE(img.load("sample.bmp"));
}

TEST(BitmapImageTest, LoadNonExistentFile)
{
    BitmapImage img;
    EXPECT_FALSE(img.load("nonexistent.bmp"));
}

TEST(BitmapImageTest, SaveValidImage)
{
    BitmapImage img;
    img.setSize(10, 10);
    EXPECT_TRUE(img.save("test_output.bmp"));
    std::remove("test_output.bmp");
}

TEST(BitmapImageTest, SaveInvalidSize)
{
    BitmapImage img;
    EXPECT_FALSE(img.save("test_output.bmp"));
}

TEST(BitmapImageTest, WidthAfterLoad)
{
    BitmapImage img;
    ASSERT_TRUE(img.load("sample.bmp"));
    EXPECT_GT(img.width(), 0);
}

TEST(BitmapImageTest, WidthAfterSetSize)
{
    BitmapImage img;
    img.setSize(100, 50);
    EXPECT_EQ(img.width(), 100);
}

TEST(BitmapImageTest, HeightAfterLoad)
{
    BitmapImage img;
    ASSERT_TRUE(img.load("sample.bmp"));
    EXPECT_GT(img.height(), 0);
}

TEST(BitmapImageTest, HeightAfterSetSize)
{
    BitmapImage img;
    img.setSize(60, 70);
    EXPECT_EQ(img.height(), 70);
}

TEST(BitmapImageTest, DataSizeAfterLoad)
{
    BitmapImage img;
    ASSERT_TRUE(img.load("sample.bmp"));
    EXPECT_EQ(img.data().size(), static_cast<size_t>(img.width() * img.height()));
}

TEST(BitmapImageTest, DataSizeAfterSetSize)
{
    BitmapImage img;
    img.setSize(3, 4);
    EXPECT_EQ(img.data().size(), 12);
}

TEST(ImageTransformTest, RotateClockwiseDimensions)
{
    BitmapImage img;
    img.setSize(2, 3);
    auto rotated = rotateClockwise(img);
    EXPECT_EQ(rotated.width(), 3);
    EXPECT_EQ(rotated.height(), 2);
}

TEST(ImageTransformTest, RotateCounterClockwiseDimensions)
{
    BitmapImage img;
    img.setSize(4, 5);
    auto rotated = rotateCounterClockwise(img);
    EXPECT_EQ(rotated.width(), 5);
    EXPECT_EQ(rotated.height(), 4);
}

TEST(ImageTransformTest, GaussianBlurProducesSameSize)
{
    BitmapImage img;
    img.setSize(10, 10);
    auto blurred = applyGaussian(img);
    EXPECT_EQ(blurred.width(), 10);
    EXPECT_EQ(blurred.height(), 10);
}

TEST(ImageTransformTest, GaussianBlurOnSmallImage)
{
    BitmapImage img;
    img.setSize(1, 1);
    img.data()[0] = {0, 0, 255};
    auto blurred = applyGaussian(img);
    EXPECT_EQ(blurred.data()[0].red, 255);
}