#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>

#include "colors.h"
#include "image.h"

class DrawingTest : public ::testing::Test {
    public:
        Image image;
        int pause;

    protected:
        void SetUp() override {
            cv::Mat src(480, 640, CV_8UC3, COLORS_white);
            image.setData(src);
            pause = 2000; 
        }
};

// ./app --gtest_filter=DrawingTest.*
TEST_F(DrawingTest, show) {
    ASSERT_EQ(image.show(pause), 0);
}
