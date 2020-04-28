# Tests

- [Home](../README.md)

---

## Run all tests
```
$ augment -t
```

## Image
- Run all image tests
```
$ T=500 IMG=media/lena.jpg augment -t --gtest_filter=ImageTest.*
```
- `T=500` - pause in ms
- `IMG=media/lena.jpg` - test image


## Fix "Gtk-WARNING: cannot open display"

```
$ DISPLAY=:0.0 augment -t
```