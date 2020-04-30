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

/*
    ./augment --flip --crop --lighting --smooth --rotate --shift --shear -d ../output -i ../media/img100*.jpg 
    ./augment -F -C -L -S -R -H -E -d ../output ../media/img100*.jpg 
    ./augment -FCLSRHE -d ../output ../media/img100*.jpg
    img10001.jpg -> img10001_FELCSRD.jpg  
*/

// ./augment -t --gtest_filter=UtilsTest.Getopt
TEST(UtilsTest, Getopt) {
    int argc = 3;
    char *argv[] = { (char*)"./app", 
                     (char*)"-Fi",
                     (char*)"dummy.jpg" 
                    };
                    

    const char *short_opts = "Fi:";
    const option long_opts[] {
        { "flip", no_argument, nullptr, 'F' },
        { "input", required_argument, nullptr, 'i' },
        { nullptr, no_argument, nullptr, 0 }     // last zero
    };  
    
    if(argc == 1) {            // without parameters      
      // ...
    }     
    
    for (auto i : argv) std::cout << i << ' ';
    std::cout << std::endl;

    int opt = 0;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch (opt) { 
            case 'F':
                std::cout << "Flip is set to true\n";
                break;
                
            case 'i':
                std::cout << "Input file set to: " << std::string(optarg) << std::endl;
                break;
                
            case 'h': // -h or --help
            case '?': // Unrecognized option
            default:
                //PrintHelp();
                FAIL();
                break;
        }
    }   
}


