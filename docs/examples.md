# Examples

- [Home](../README.md)

---

```
$ ./augment -h
augment version                0.1 (May  3 2020)
usage: augment [options]       -i input_dir -o output_dir
options:
   -i --input <dir>            input directory
   -o --output <dir>           output directory
   -F --flip                   flip horizontal
   -C --crop                   crop and resize
   -L --lighting               contrast and brightness
   -S --smooth                 smooth
   -R --rotate                 rotate
   -H --shift                  shift horizontal
   -E --shear                  shear
   -t --test                   run tests
   -h --help                   show help
example:
   ./augment -FCLSRHE -i ../images/c0 -o ../tmp/c0
```