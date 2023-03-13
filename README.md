# SSTV Image Tools C++ Library

Currently in development but it's functional. Will be used with the MWAV library to create SSTV images.

A simple library for manipulating images into common SSTV image formats using Magick++.

# Convert an image to the size specified by the SSTV mode and add a call sign
```cpp
  SstvImage image(SstvImage::Mode::ROBOT_36_COLOR, "test1.png");
  image.AddCallSign("N0CALL");
  image.Write("converted_test1.png");
```
test1.png             |  converted_test1.png
:-------------------------:|:-------------------------:
<img src="https://user-images.githubusercontent.com/19292194/224849070-d1468c89-010d-46bd-af68-72c0e7516e87.png" width="450">  |  <img src="https://user-images.githubusercontent.com/19292194/224849046-d80b2945-028a-4301-9520-3f03c7a88681.png" width="300">

# Get RGB values of specific pixels
```cpp
  SstvImage image(SstvImage::Mode::ROBOT_36_COLOR, "example/test1.png");
  /* 
    From this point forward image is the size of the specified mode.
    For example, Robot36 is 320x256.
  */
  image.AddCallSign("N0CALL");

  SstvImage::Pixel pixel;
  pixel = image.GetPixel(128, 91, pixel); // Get Pixel returns false if the pixel is out of bounds

  std::cout << (int)pixel.r << " " << (int)pixel.g << " " << (int)pixel.b << std::endl;
  // 0 191 0
```

Basic Features:
- Overlay call sign and ~~message text~~
- Convert the image to the proper color space
- Get the values for individual pixels
- ~~Add Data to the image~~

***

Supported SSTV Image Formats:
- Robot24
- Robot36
- Robot72
- ~~Robot8 B/W~~
- ~~Robot16 B/W~~

Tested with jpeg, and png images, support for other Magick++ supported formats has not been tested.

Magick++ (7.1) with ``libjpeg62-dev``, ``libpng-dev``, ``libfreetype6-dev`` is required.

***

Example Image Sources:
|Image File|Source|License|
|:--------:|:----:|:-----:|
|`example/test1.png`|[Wikipedia](https://en.wikipedia.org/wiki/File:Philips_PM5544.svg)|GNU 1.2|
|`example/test2.png`|[Wikipedia](https://en.wikipedia.org/wiki/File:TwibrightLinksTestCard.png)|GNU 1.2|
|`example/test3.jpg`|[Wikipedia](https://en.wikipedia.org/wiki/File:SMPTE_Color_Bars.svg)|Public Domain|
