// augment - Dataset augmentation
#include <stdio.h>
#include <getopt.h>
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include "image.h"

/*
    ./augment --flip --crop --lighting --smooth --rotate --shift --shear -d ../output -i ../media/img100*.jpg 
    ./augment -F -C -L -S -R -H -E -d ../output ../media/img100*.jpg 
    augment -FCLSRHE -d ../output ../media/img100*.jpg
    img10001.jpg -> img10001_FELCSRD.jpg  
*/


void PrintHelp()
{
    std::cout <<
        "augment version                0.1 (" << __DATE__ << ")\n"
        "usage: augment [options]       -i infile -o outfile\n"
        "options:\n"
        "   -i --input <infile>         input image file\n"
        "   -o --output <outfile>       output image file\n"
        "   -F --flip                   flip horizontal\n"
        "   -C --crop                   crop and resize\n"
        "   -L --lighting               contrast and brightness\n"
        "   -S --smooth                 smooth\n"
        "   -R --rotate                 rotate\n"
        "   -H --shift                  shift horizontal\n"
        "   -E --shear                  shear\n"   
        "   -t --test                   run tests\n"                     
        "   -h --help                   show help\n"
        "example:\n"
        "   augment -FCL -i lena.jpg -o lena_fcl.jpg\n";
    exit(0);
}

int main(int argc, char *argv[])
{  
    if(argc == 1) {                   
        PrintHelp();
    }
    
    cv::String infile;
    cv::String outfile;
    bool is_flip = false;
    bool is_crop = false;
    bool is_lighting = false;
    bool is_smooth = false;
    bool is_rotate = false;
    bool is_shift = false;
    bool is_shear = false;
    
    const char *short_opts = "FCLSRHEthi:o:";
    const option long_opts[] {
        { "input", required_argument, nullptr, 'i' },
        { "output", required_argument, nullptr, 'o' },
        { "flip", no_argument, nullptr, 'F' },
        { "crop", no_argument, nullptr, 'C' },
        { "lighting", no_argument, nullptr, 'L' },
        { "smooth", no_argument, nullptr, 'S' },
        { "rotate", no_argument, nullptr, 'R' },
        { "shift", no_argument, nullptr, 'H' },
        { "shear", no_argument, nullptr, 'E' },
        { "help", no_argument, nullptr, 'h' },
        { nullptr, no_argument, nullptr, 0 }     // last zero
    }; 
    
    int opt = 0;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch (opt) { 
            
            case 't':
                ::testing::InitGoogleTest(&argc, argv);
                return RUN_ALL_TESTS();
            
            case 'F':
                is_flip = true;
                break;
                
            case 'C':
                is_crop = true;
                break;
                
            case 'L':
                is_lighting = true;
                break;
                
            case 'R':
                is_rotate = true;
                break;
                
            case 'H':
                is_shift = true;
                break;
                
            case 'E':
                is_shear = true;
                break;
                
            case 'S':
                is_smooth = true;
                break;
                
            case 'i':
                infile = std::string(optarg); 
                break;
                
            case 'o':
                outfile = std::string(optarg); 
                break;
                
            case 'h': // -h or --help
            case '?': // Unrecognized option
            default:
                PrintHelp();
                break;
        }
    }  
    
    // ./augment -F -i ../tmp/lena.jpg -o ../tmp/lena_f.jpg
    // ./augment -C -i ../tmp/lena.jpg -o ../tmp/lena_c.jpg
    // ./augment -L -i ../tmp/lena.jpg -o ../tmp/lena_l.jpg
    // ./augment -FCL -i ../tmp/lena.jpg -o ../tmp/lena_fcl.jpg
    // ./augment -R -i ../tmp/lena.jpg -o ../tmp/lena_r.jpg
    
    // ./augment -H -i ../tmp/lena.jpg -o ../tmp/lena_h.jpg
    // ./augment -E -i ../tmp/lena.jpg -o ../tmp/lena_e.jpg
    // ./augment -S -i ../tmp/lena.jpg -o ../tmp/lena_s.jpg
    
    if ( !infile.empty() ) {
        Image image;
        cv::Mat src = cv::imread(infile, cv::IMREAD_COLOR);
        image.setData(src);
        
        cv::RNG rng; 
        rng.state = cv::getTickCount();   // seeed it ! 
        
        if (is_flip) {
            if ( rng.uniform(0, 2) == 0 ) {    // return value from a-(b-1)
                image.flip();
            }
        }
        if (is_crop) {
            double k = rng.uniform(0.7, 0.95); 
            image.cropResize(k);
        }
        if (is_lighting) {
            double c = rng.uniform(0.5, 1.5);   // contrast 
            int b = rng.uniform(-30, 30);      
            image.contrastBrightness(c, b);
        }
        if (is_rotate) {
            double angle = rng.uniform(-10.0, +10.0);
            image.rotate(angle);
        }
        if (is_shift) {
            int tx = rng.uniform(-10, +10);
            image.shift(tx, 0);
        }
        if (is_shear) {
            double sh = rng.uniform(-0.1, +0.1);
            image.shear(sh);
        }
        if (is_smooth) {
            int ksize = rng.uniform(3, 13);
            if (!(ksize % 2)) {         
                ksize++;   // even to odd
            }
            image.smooth(ksize); 
        }
        
        image.show(500);
        
        if ( !outfile.empty() ) {
            cv::Mat dst = image.getData();
            cv::imwrite(outfile, dst);
            
        }
    }
    
    
    return 0;
}

