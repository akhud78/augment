// augment - Dataset augmentation

#include <stdio.h>
#include <getopt.h>
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

#include "image.h"

namespace bfs = boost::filesystem;

cv::RNG rng;  // Random number generator

// Data augmentation options
struct AugmentOptions {
  bool flip     = false;  // F
  bool crop     = false;  // C
  bool lighting = false;  // L
  bool smooth   = false;  // S  
  bool rotate   = false;  // R
  bool shift    = false;  // H
  bool shear    = false;  // E
} augment;

std::string AugmentString() 
{
  std::string token = "_";
  if (augment.flip) {
    token += "F";
  }
  if (augment.crop) {
    token += "C";
  }
  if (augment.lighting) {
    token += "L";
  }
  if (augment.smooth) {
    token += "S";
  }
  if (augment.rotate) {
    token += "R";
  }
  if (augment.shift) {
    token += "H";
  }
  if (augment.shear) {
    token += "E";
  }
  return token;
} 

// Augment one image file with options
void AugmentFile(const std::string &input_file, const std::string &output_file)
{
  Image image;
  cv::Mat src = cv::imread(input_file, cv::IMREAD_COLOR);
  if (!src.data) return;  // no image data 
  image.setData(src);
  
  if (augment.flip) {
      if ( rng.uniform(0, 2) == 0 ) {    // return value from a-(b-1)
          image.flip();
      }
  }
  if (augment.crop) {
      double k = rng.uniform(0.7, 0.95); 
      image.cropResize(k);
  }
  if (augment.lighting) {
      double c = rng.uniform(0.7, 1.3);   // contrast 0.5, 1.5
      int b = rng.uniform(-20, 20);       // -30 +30      
      image.contrastBrightness(c, b);
  }
  if (augment.rotate) {
      double angle = rng.uniform(-10.0, +10.0);
      image.rotate(angle);
  }
  if (augment.shift) {
      int tx = rng.uniform(-10, +10);
      image.shift(tx, 0);
  }
  if (augment.shear) {
      double sh = rng.uniform(-0.1, +0.1);
      image.shear(sh);
  }
  if (augment.smooth) {
      int ksize = rng.uniform(3, 13);
      if (!(ksize % 2)) {         
          ksize++;   // even to odd
      }
      image.smooth(ksize); 
  }
  
  //image.show(500); 
  
  if ( !output_file.empty() ) {
      cv::Mat dst = image.getData();
      cv::imwrite(output_file, dst);
  }
} 

void PrintHelp()
{
  std::cout <<
    "augment version                0.1 (" << __DATE__ << ")\n"
    "usage: augment [options]       -i input_dir -o output_dir\n"
    "options:\n"
    "   -i --input <dir>            input directory\n"
    "   -o --output <dir>           output directory\n"
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
    "   ./augment -FCLSRHE -i ../images/c0 -o ../tmp/c0\n"; 
  exit(0);
}

int main(int argc, char *argv[])
{  
  if(argc == 1) {                   
    PrintHelp();
  }
  
  std::string input;
  std::string output;
  
  const char *short_opts = "FCLSRHEthi:o:";
  const option long_opts[] {
      { "input", required_argument, nullptr, 'i' },
      { "output", required_argument, nullptr, 'o' },
      { "test", no_argument, nullptr, 't' },
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
        augment.flip = true;
        break;
          
      case 'C':
        augment.crop = true;
        break;
          
      case 'L':
        augment.lighting = true;
        break;
          
      case 'R':
        augment.rotate = true;
        break;
          
      case 'H':
        augment.shift = true;
        break;
          
      case 'E':
        augment.shear = true;
        break;
          
      case 'S':
        augment.smooth = true;
        break;
          
      case 'i':
        input = std::string(optarg); 
        break;
          
      case 'o':
        output = std::string(optarg); 
        break;
          
      case 'h': // -h or --help
      case '?': // Unrecognized option
      default:
          PrintHelp();
          break;
    }
  }  
  
  rng.state = cv::getTickCount(); // seeed Random number generator !   
  bfs::path input_path(input);
  bfs::path output_path(output);
  
  // ./augment -FCLSRHE -i ../media -o ../tmp
  if (bfs::is_directory(input_path) && bfs::is_directory(output_path)) {
    std::string output_dir = output_path.string();
        
    std::vector<bfs::path> v;   
    std::copy(bfs::directory_iterator(input_path), bfs::directory_iterator(), 
        std::back_inserter(v));
    for (auto i : v) {
      output = output_dir + "/" + i.stem().string() + AugmentString() + 
        i.extension().string(); 
      AugmentFile(i.relative_path().string(), output);
    }
    
  } else {
    std::cout << ":-(\n";
  }
  
  std::cout << "That's all folks!\n";
  return 0;
}

