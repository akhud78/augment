#ifndef IMAGE_H
#define IMAGE_H

class Image {
    private:
        cv::Mat src_;
        
    public:
        void setData(const cv::Mat &src) { src_ = src; }
        cv::Mat getData() { return src_; }
        cv::Size getSize() { return src_.size(); }
        int show(int delay=0);
        void resize(int width, int height);
        void resize(double k);
        void crop(int width, int height, int x, int y);
        
        void flip(int code=1);          // -F --flip  horizontal code=1  
        void cropResize(double k);      // -C --crop
        void contrastBrightness(double alpha = 1.0, int beta = 0); // -L --lighting
        void smooth(int ksize = 31);    // -S --smooth
        void rotate(double angle);      // -R --rotate
        void shift(int tx, int ty = 0); // -H --shift
        void shear(double sh);          // -E --shear
};

#endif // IMAGE_H 
