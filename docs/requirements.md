# Requirements

- [Home](../README.md)

---

- [Google Test](https://github.com/google/googletest/blob/master/googletest/README.md)
- OpenCV 4.1.1
- Boost 1.58

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

### Boost
```
sudo apt-get install libboost-all-dev
```

