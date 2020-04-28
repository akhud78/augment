#ifndef IMAGE_H
#define IMAGE_H

class Image {
    private:
        cv::Mat src_;
        
    public:
        void setData(const cv::Mat &src) { src_ = src; }
        cv::Mat getData() { return src_; }
        int show(int delay=0);
};

#endif // IMAGE_H 
