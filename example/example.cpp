#include <array>
#include <iostream>
#include <string>

#include "sstv-image-tools.h"

int main() {
  std::array<std::string, 3> test_images = {"test1.png", "test2.png",
                                            "test3.jpg"};

  for (auto &image_path : test_images) {
    SstvImage image(SstvImage::Mode::ROBOT_36_COLOR, image_path,
                    "converted_" + image_path);
    image.AddCallSign("N0CALL");

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