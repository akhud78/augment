# Requirements

- [Home](../README.md)

---

- [Google Test](https://github.com/google/googletest/blob/master/googletest/README.md)
    - [Googletest Primer](https://github.com/google/googletest/blob/master/googletest/docs/primer.md)
    - [Advanced googletest Topics](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md)
* OpenCV 4.1.1

### Google Test
```
sudo apt-get install libgtest-dev
sudo apt-get install cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
 
# copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
sudo cp *.a /usr/lib
```

