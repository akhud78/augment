# Examples

- [Home](../README.md)

---
## Options

```
augment version                0.9 (May 14 2020)
Image Data Augmentation for Deep Learning
usage: augment [options]       -i input_dir -o output_dir
options:
   -i --input <dir>            input directory
   -o --output <dir>           output directory
   -r --recursive              recurse into directories
   -F --flip                   flip horizontal
   -C --crop                   crop and resize
   -L --lighting               contrast and brightness
   -S --smooth                 smooth
   -R --rotate                 rotate
   -H --shift                  shift horizontal
   -E --shear                  shear
   -t --test                   run tests
   -h --help                   show help
examples:
   augment -FS -i media -o tmp
   augment -CLR -ri media/test -o tmp
   augment -HE -ri media/test -o tmp
```
## Data Augmentation
- Recursively scan subdirectories in `train_delta`.
- Write images in `train_aug`. Create subdirectories.
- Crop, lighting and rotate images.
```
$ augment -CLR -ri train_delta/ -o train_aug/
Processed images	1538
Elapsed time (s)	8.05955
```
- Shift and shear images.
```
$ augment -HE -ri train_delta/ -o train_aug/
Processed images	1538
Elapsed time (s)	8.30386
```
```
$ ls -1 train_aug/c0/ | head -4
img_51761_CLR.jpg
img_51761_HE.jpg
img_51770_CLR.jpg
img_51770_HE.jpg
```