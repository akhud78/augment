#include <stdio.h>
#include <random>

#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>

#include "colors.h"
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

// https://docs.opencv.org/4.1.1/d2/de8/group__core__array.html#gaca7be533e3dac7feb70fc60635adf441
void Image::flip(int code /* =1 */)  // 1 - horizontal flipping
{
    cv::flip(src_, src_, code);
}

void Image::resize(int width, int height)
{
    cv::resize(src_, src_, cv::Size(width, height));
}

void Image::resize(double k)
{
    cv::resize(src_, src_, cv::Size(), k, k);
}

// Changing the contrast and brightness of an image! 
// https://docs.opencv.org/4.1.1/d3/dc1/tutorial_basic_linear_transform.html
void Image::contrastBrightness(
        double alpha,           // = 1.0 - contrast
        int beta                // = 0   - brightness
        ) 
{
    src_.convertTo(src_, -1, alpha, beta);
} 

// https://docs.opencv.org/4.1.1/dc/dd3/tutorial_gausian_median_blur_bilateral_filter.html
void Image::smooth(int ksize /* = 31 */)    // kernel size
{
    cv::GaussianBlur(src_, src_, cv::Size( ksize, ksize ), 0, 0 );
}

// Crop image center and resize to original 
void Image::cropResize(double k)
{
    int src_w = src_.cols;
    int src_h = src_.rows;
    int roi_w = src_w * k;
    int roi_h = src_h * k;
    int x = (src_w -roi_w)/2;
    int y = (src_h -roi_h)/2; 
    try {
        cv::Mat roi = src_(cv::Rect(x, y, roi_w, roi_h));
        cv::resize(roi.clone(), src_, cv::Size(src_w, src_h));
    } catch (const cv::Exception& e) {
        std::cerr  << "Caught exception: " << e.what() << std::endl;
    }
}

// Rotate image
// https://docs.opencv.org/4.1.1/d4/d61/tutorial_warp_affine.html
// http://opencvexamples.blogspot.com/2014/01/rotate-image.html
void Image::rotate(double angle)
{
    cv::Point2f pt(src_.cols/2., src_.rows/2.);
    try {    
        cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);
        //cv::warpAffine(src_, src_, r, cv::Size(src_.cols, src_.rows));
        cv::warpAffine(src_, src_, r, cv::Size(src_.cols, src_.rows), cv::INTER_LINEAR, cv::BORDER_REPLICATE); 
    } catch (const cv::Exception& e) {
        std::cerr  << "Caught exception: " << e.what() << std::endl;
    }
}

// https://docs.opencv.org/4.1.1/da/d6e/tutorial_py_geometric_transformations.html
void Image::shift(int tx, int ty /* =0 */)
{
    // Translation
    cv::Mat r = (cv::Mat_<double>(2,3) << 1, 0, tx, 0, 1, ty);
    cv::warpAffine(src_, src_, r, cv::Size(src_.cols, src_.rows), cv::INTER_LINEAR, cv::BORDER_REPLICATE);
}

// https://blog.paperspace.com/data-augmentation-for-object-detection-rotation-and-shearing/
// https://stackabuse.com/affine-image-transformations-in-python-with-numpy-pillow-and-opencv/
// https://en.wikipedia.org/wiki/Shear_mapping
void Image::shear(double sh)
{
    // Horizontal Shear
    cv::Mat r = (cv::Mat_<double>(2,3) << 1, sh, 0, 0, 1, 0);
    cv::warpAffine(src_, src_, r, cv::Size(src_.cols, src_.rows), cv::INTER_LINEAR, cv::BORDER_REPLICATE);
}


class ImageTest : public ::testing::Test {
    public:
        Image image;
        int pause;
        cv::RNG rng;            // random number generator

    protected:
        void SetUp() override {
            cv::Mat src(480, 640, CV_8UC3, COLORS_red);
            cv::line(src, cv::Point(0,0), cv::Point(src.cols-1, src.rows-1), COLORS_blue, 10);
            if(const char* test_image = std::getenv("IMG")) 
                src = cv::imread(test_image, cv::IMREAD_COLOR);
            image.setData(src);
            
            pause = 100;
            if(const char* test_pause = std::getenv("T")) {
                // T=500 ./augment -t
                int t = atoi(test_pause);
                if (t > 0) 
                    pause = t;
            }
            rng.state = cv::getTickCount();   // seeed it ! 
        }
};

// T=500 IMG=../media/lena.jpg ./augment -t --gtest_filter=ImageTest.*
TEST_F(ImageTest, Show) {
    ASSERT_EQ(image.show(pause), 0);
}

// ./augment -t --gtest_filter=ImageTest.RandomFlip
TEST_F(ImageTest, RandomFlip) {
    // https://docs.opencv.org/4.1.1/d1/dd6/classcv_1_1RNG.html#acde197860cea91e5aa896be8719457ae
    if ( rng.uniform(0, 2) == 0 ) {    // return value from a-(b-1)
        image.flip();
    }
    image.show(pause);
}

// ./augment -t --gtest_filter=ImageTest.RandomContrastBrightness
TEST_F(ImageTest, RandomContrastBrightness) {
    double c = rng.uniform(0.5, 3.0);   // contrast 
    int b = rng.uniform(-50, 50);      
    image.contrastBrightness(c, b);
    image.show(pause);
}

// IMG=../media/lena.jpg ./augment -t --gtest_filter=ImageTest.RandomSmooth
TEST_F(ImageTest, RandomSmooth) {
    int ksize = rng.uniform(3, 13);
    if (!(ksize % 2)) {         
        ksize++;   // even to odd
    }
    image.smooth(ksize); 
    image.show(pause);
}

// T=500 IMG=../media/lena.jpg ./augment -t --gtest_filter=ImageTest.RandomCropResize
TEST_F(ImageTest, RandomCropResize) {
    double k = rng.uniform(0.7, 0.95);
    cv::Size s = image.getSize();
    std::cout << s << " " << k << std::endl; 
    image.cropResize(k);
    ASSERT_TRUE(image.getSize() == s);  // image size unchanged
    image.show(pause);
}

// T=500 IMG=../media/lena.jpg ./augment -t --gtest_filter=ImageTest.RandomRotate
TEST_F(ImageTest, RandomRotate) {
    double angle = rng.uniform(-10.0, +10.0);
    std::cout << angle << std::endl;
    image.rotate(angle);
    image.show(pause);
}

// T=500 IMG=../media/lena.jpg ./augment -t --gtest_filter=ImageTest.RandomShift
TEST_F(ImageTest, RandomShift) {
    int tx = rng.uniform(-10, +10);
    std::cout << tx << std::endl;
    image.shift(tx, 0);
    image.show(pause);
}

// T=500 IMG=../media/lena.jpg ./augment -t --gtest_filter=ImageTest.RandomShear
TEST_F(ImageTest, RandomShear) {
    double sh = rng.uniform(-0.1, +0.1);
    std::cout << sh << std::endl;
    image.shear(sh);
    image.show(pause);
}





