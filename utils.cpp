#include <stdio.h>
#include <getopt.h>
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>

/*
Dataset augmentation v0.1
Usage: app [params] input 

    -h, --help (value:true)
        print help
    -t, --test
        run tests

    input (value:../media/lena.jpg)
        input file
*/

// https://docs.opencv.org/4.1.1/d0/d2e/classcv_1_1CommandLineParser.html
// ./augment -t --gtest_filter=UtilsTest.*
TEST(UtilsTest, CommandLineParser) {
    int argc = 3;
    char *argv[] = { (char*)"./app", 
                     (char*)"-t",
                     (char*)"dummy.jpg" 
                    };
    const cv::String keys = 
        "{ help h  |        | print help  }"
        "{ @input  | <none> | input file  }"
        "{ t test  |        | run tests   }"
        ;
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Dataset augmentation v0.1");
    
    for (auto i : argv) std::cout << i << ' ';
    std::cout << std::endl;
    
    if (parser.has("help")) {
      parser.printMessage();
    }    
    
    if (!parser.check()) {
        parser.printErrors();
        FAIL();
    }
}




