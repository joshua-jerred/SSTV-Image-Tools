#include <array>
#include <iostream>
#include <string>

#include "sstv-image-tools.h"

int main() {
  std::array<std::string, 3> test_images = {"test1.png", "test2.png",
                                            "test3.jpg"};

  std::vector<std::string> data = {"PRES 1025mb", "TEMP 25.0c",
                                   "HUMID 50%", "ALT 102416ft" };

  std::vector<std::string> data2 = {"TESTING"};

  for (auto &image_path : test_images) { // Do this for each image
    SstvImage image(SstvImage::Mode::ROBOT_36_COLOR, image_path,
                    "converted_" + image_path);

    image.AddCallSign("N0CALL");
    image.AddText(data);
    image.AddText(data2, false, SstvImage::Color(0, 0, 0), SstvImage::Color(1, 1, 1));
    image.AdjustColors(); // Optional, needed if getting rgb pixel values

    SstvImage::Pixel pixel;
    if (!image.GetPixel(128, 91, pixel)) {
      std::cout << "Failed to get pixel" << std::endl;
    }

    std::cout << (int)pixel.r << " " << (int)pixel.g << " " << (int)pixel.b
              << std::endl;

    image.Write();
  }
  return 0;
}