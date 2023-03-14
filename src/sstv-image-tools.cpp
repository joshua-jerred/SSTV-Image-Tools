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
    throw SstvImageToolsException("Failed to read image: " + source_image_path +
                                  " " + error_.what());
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

  int font_size = 25 * height_scaler_;

  std::vector<Magick::Drawable> draw_list(
    {Magick::DrawableFont("Arial-Bold"), 
    Magick::DrawablePointSize(font_size), 
    Magick::DrawableText(0, 0 + font_size * 0.8, callsign),
    Magick::DrawableStrokeColor("red"),
    Magick::DrawableStrokeWidth(2),
    Magick::DrawableStrokeAntialias(true),
    Magick::DrawableFillColor("green")}
);

  image_.draw(draw_list);
}

bool SstvImage::GetPixel(const int x, const int y, SstvImage::Pixel &pixel) {
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

void SstvImage::AdjustColors() {
    /*
  This is a hack to deal with the color space issues. Not a fan of this solution.
  */
  image_.quantizeColorSpace(Magick::RGBColorspace);
  image_.quantizeColors(256);
  image_.quantize();
  image_.modifyImage();
  image_.gamma(1.7);
  image_.enhance();
  image_.write("tmp.png");
  image_.read("tmp.png");
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

  //image_.enhance();
  /*
  image_.quantizeColorSpace(Magick::RGBColorspace);
  image_.quantizeColors(256);
  image_.quantize();
  image_.modifyImage();
  image_.colorSpace(Magick::sRGBColorspace);
  image_.type(Magick::TrueColorType);
  if (image_.colorSpace() == Magick::sRGBColorspace){
    std::cout << "sRGBColorspace" << std::endl;
  } else if (image_.colorSpace() == Magick::RGBColorspace) {
    std::cout << "RGBColorspace" << std::endl;
  } else if (image_.colorSpace() == Magick::CMYColorspace) {
    std::cout << "CMYColorspace" << std::endl;
  } else if (image_.colorSpace() == Magick::GRAYColorspace) {
    std::cout << "GRAYColorspace" << std::endl;
  } else {
    std::cout << "Unknown colorspace" << std::endl;
  }

  std::cout << "Channels: " << image_.channels() << std::endl;
  image_.channel(Magick::RedChannel);
  */

  //image_.quantizeColorSpace(Magick::RGBColorspace); // THESE
  //image_.quantizeColors(256); // THESE
  //image_.quantize(); // THESE
  //image_.normalize();
  //image_.enhance(); Made things a lot worse

  /*
  Known working solution:
  image_.quantizeColorSpace(Magick::RGBColorspace);
  image_.quantizeColors(256);
  image_.quantize();
  image_.modifyImage();
  */
}