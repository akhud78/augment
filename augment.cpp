// augment - Dataset augmentation
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>


void PrintHelp()
{
    std::cout <<
        "augment version        0.1\n"
        "usage: augment [options] -i infile\n"
        "options:\n"
        "-i --input <infile>    input image\n"
        "-F --flip              flip image\n"
        "-h --help              show help\n";
    exit(1);
}

int main(int argc, char *argv[])
{  
    const cv::String keys = 
        "{ help h  |        | print help  }"
        "{ @input  | <none> | input file  }"
        "{ t test  |        | run tests   }"
        ;
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Dataset augmentation v0.1");
    
    if (argc < 2 || parser.has("help")) {
      parser.printMessage();
      return 0;
    }    
    
    if (parser.has("test")) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    
    
    if (!parser.check()) {
        parser.printErrors();
        return -1;
    }
    
    return 0;
}

