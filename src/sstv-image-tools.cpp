#include "sstv-image-tools.h"

#include <Magick++/Color.h>
#include <iostream>
#include <list>

SstvImage::Color::Color(int red, int green, int blue) {
  this->r = red;
  this->g = green;
  this->b = blue;
}

SstvImage::SstvImage(SstvImage::Mode mode, std::string source_image_path,
                     std::string destination_image_path, bool crop)
    : mode_(mode), crop_(crop) {
  source_path_ = source_image_path;
  if (destination_image_path == "") {
    destination_path_ = source_image_path;
  } else {
    destination_path_ = destination_image_path;
  }
  try {
    image_.read(source_image_path);
    Scale();
  } catch (Magick::Exception &error_) {
    throw SstvImageToolsException("Failed to read image: " + source_image_path);
  }
}

void SstvImage::Write() {
  try {
    image_.write(destination_path_);
  } catch (Magick::Exception &error_) {
    throw SstvImageToolsException("Failed to write image: " +
                                  destination_path_);
  }
}

void SstvImage::AddCallSign(const std::string &callsign,
                            const SstvImage::Color &color) {
  (void)color;

  int font_size = 20 * height_scaler_;

  Magick::DrawableFont font("Arial-Bold");
  Magick::DrawablePointSize point_size(font_size);
  Magick::DrawableText text(0, 0 + font_size, callsign);
  Magick::DrawableStrokeColor stroke_color("red");
  Magick::DrawableFillColor fill("green");

  std::vector<Magick::Drawable> draw_list({font, point_size, text, stroke_color,
                                             fill});

  image_.draw(draw_list);
}

bool SstvImage::GetPixel(int x, int y, SstvImage::Pixel &pixel) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    return false;
  }
  
  MagickCore::Quantum *pixels = image_.getPixels(0, 0, width_, height_);
  unsigned index = (y * width_ + x) * image_.channels();

  pixel.r = pixels[index];
  pixel.g = pixels[index + 1];
  pixel.b = pixels[index + 2];
  return true;
}

void SstvImage::Scale() {
  width_ = 0;
  height_ = 0;
  int scale_factor = 1;
  switch (mode_) {
    case SstvImage::Mode::ROBOT_8_BW:
    case SstvImage::Mode::ROBOT_12_BW:
    case SstvImage::Mode::ROBOT_12_COLOR:
      width_ = 160;
      height_ = 120;
      scale_factor = 1.2;
      break;
    case SstvImage::Mode::ROBOT_24_BW:
    case SstvImage::Mode::ROBOT_36_BW:
    case SstvImage::Mode::ROBOT_24_COLOR:
    case SstvImage::Mode::ROBOT_36_COLOR:
      width_ = 320;
      height_ = 240;
      scale_factor = 1.0;
      break;
    case SstvImage::Mode::ROBOT_72_COLOR:
      width_ = 640;
      height_ = 480;
      break;
    default:
      throw SstvImageToolsException("Not yet implemented");
  }

  height_scaler_ = (height_ / 100.0) * scale_factor;

  Magick::Geometry crop_size(width_, height_);
  if (crop_) {
    crop_size.fillArea(true);
    image_.resize(crop_size);
    image_.extent(crop_size, Magick::CenterGravity);
    

  } else {
    crop_size.aspect(true);
    image_.resize(crop_size);
  }
}


















bool ConvertToRobot8(std::string image_path) {
  Magick::Image image;
  Magick::Geometry crop_size(160, 120);
  crop_size.aspect(true);
  try {
    image.read(image_path);
    image.scale(crop_size);
    image.quantizeColorSpace(Magick::GRAYColorspace);
    image.quantizeColors(8);
    image.quantize();
    image.write(image_path + ".r8.png");
  } catch (Magick::Exception &error_) {
    std::cout << "Caught exception: " << error_.what() << std::endl;
    return 1;
  }
  return 0;
}

bool ConvertToRobot36(std::string image_path) {
  Magick::Image image;
  Magick::Geometry crop_size(320, 240);
  crop_size.aspect(true);
  try {
    image.read(image_path);
    image.scale(crop_size);
    image.quantizeColorSpace(Magick::YUVColorspace);
    image.quantize();
    image.write(image_path + ".r36.png");
  } catch (Magick::Exception &error_) {
    std::cout << "Caught exception: " << error_.what() << std::endl;
    return 1;
  }
  return 0;
}

bool ConvertToCustom8(std::string image_path) {
  Magick::Image image;
  try {
    image.read(image_path);
    Magick::Geometry crop_size(400, 400);
    crop_size.aspect(true);
    image.scale(crop_size);
    image.crop(crop_size);
    image.quantizeColorSpace(Magick::GRAYColorspace);
    image.quantizeColors(200);
    image.quantize();
    image.write(image_path + ".c8.png");
  } catch (Magick::Exception &error_) {
    std::cout << "exception: " << error_.what() << std::endl;
    return 1;
  }
  return 0;
}

bool Pixels(std::string image_path) {
  Magick::Image image;
  try {
    image.read(image_path);
    Magick::Pixels view(image);
  } catch (Magick::Exception &error_) {
    std::cout << "exception: " << error_.what() << std::endl;
    return 1;
  }
  return 0;
}