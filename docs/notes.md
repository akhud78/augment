# Notes

- [Home](../README.md)

---

## Augmentation
- [How to prepare/augment images for neural network?](https://datascience.stackexchange.com/questions/5224/how-to-prepare-augment-images-for-neural-network)
    - rotation: random with angle between 0° and 360° (uniform)
    - translation: random with shift between -10 and 10 pixels (uniform)
    - rescaling: random with scale factor between 1/1.6 and 1.6 (log-uniform)
    - flipping: yes or no (bernoulli)
    - shearing: random with angle between -20° and 20° (uniform)
    - stretching: random with stretch factor between 1/1.3 and 1.3 (log-uniform)
- [Data Augmentation Benchmarking on CNN Training](https://gombru.github.io/2017/09/14/data_augmentation/)
    - Random Cropping
    - Mirroring
    - Rotation
    - Scaling
    - Color jitter
    - Saturation and Value jitter

## OpenCV
- [OpenCV Tutorials](https://docs.opencv.org/4.1.1/d9/df8/tutorial_root.html) 4.1.1

### Image Processing
- [Basic Drawing](https://docs.opencv.org/4.1.1/d3/d96/tutorial_basic_geometric_drawing.html)
- [Random generator and text with OpenCV](https://docs.opencv.org/4.1.1/df/d61/tutorial_random_generator_and_text.html)