#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>

#include "image.h"

int Image::show(int delay /* =0 */) 
{
    if (src_.empty())
        return -1;
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Image", src_);   
    cv::waitKey(delay);
    return 0;  
}

class ImageTest : public ::testing::Test {
    public:
        Image image;
        int pause;

    protected:
        void SetUp() override {
            pause = 200;
        }
};

// ./app --gtest_filter=ImageTest.*
TEST_F(ImageTest, DISABLED_show) {
    ASSERT_EQ(image.show(pause), 0);
}
