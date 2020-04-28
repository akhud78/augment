#ifndef IMAGE_H
#define IMAGE_H

class Image {
    private:
        cv::Mat src_;
        
    public:
        int show(int delay=0);
};

#endif // IMAGE_H 
