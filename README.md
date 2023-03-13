# SSTV Image Tools C++ Library

Currently in development but it's functional. Will be used with the MWAV library to create SSTV images.

A simple library for manipulating images into common SSTV image formats using Magick++.

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
