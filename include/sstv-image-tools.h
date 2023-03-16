#ifndef IMAGE_TOOLS_H_
#define IMAGE_TOOLS_H_

#include <Magick++.h>

#include <cstdint>
#include <string>
#include <utility>

class SstvImage {
 public:
  enum class Mode {
    ROBOT_8_BW,      // 160x120 (4:3) Black and White
    ROBOT_12_BW,     // 160x120 (4:3) Black and White
    ROBOT_24_BW,     // 320x240 (4:3) Black and White
    ROBOT_36_BW,     // 320x240 (4:3) Black and White
    ROBOT_12_COLOR,  // 160x120 (4:3) Color
    ROBOT_24_COLOR,  // 320x240 (4:3) Color
    ROBOT_36_COLOR,  // 320x240 (4:3) Color
    ROBOT_72_COLOR,  // 640x480 (4:3) Color
    CUSTOM_TEST
  };

  struct Color {
    float r = -1.0;
    float g = -1.0;
    float b = -1.0;
    float gray_scale_value = -1;
    Color(float r, float g, float b);  // 0 - 255
    Color(int gray_scale_value);       // 0.0 - 1.0, not yet implemented
    Magick::ColorRGB GetMagickColor() const;
  };

  struct Pixel {
    uint8_t r = -1;
    uint8_t g = -1;
    uint8_t b = -1;
  };

  /**
   * @brief Construct a new SSTV Image Tools object
   *
   * @param source_image_path The path to the image to be converted
   * @param destination_image_path *Optional* If not specified, the source image
   * will be overwritten
   * @exception SstvImageToolsException If the image cannot be read
   */
  SstvImage(SstvImage::Mode mode, std::string source_image_path,
            std::string destination_image_path = "", bool crop = true);
  ~SstvImage() {}

  void Write(); /** @todo should pass the destination path here*/

  void AddCallSign(const std::string &callsign,
                   const SstvImage::Color &fill_color = {0.0, 1.0, 0},
                   const SstvImage::Color &stroke_color = {1.0, 0, 0});

  void AddText(const std::vector<std::string> &text,
               const bool left_column = true,
               const SstvImage::Color fill_color = {0.0, 1.0, 0.0},
               const SstvImage::Color stroke_color = {1.0, 0.0, 0.0});

  void AdjustColors();

  bool GetPixel(const int x, const int y, SstvImage::Pixel &pixel);
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

 private:
  void Scale();

  std::pair<int, int> WorkspaceToImageCoordinates(int x, int y);

  int width_ = 0;
  int height_ = 0;
  double height_scaler_ = 1;
  const int kCallSignFontHeight_ = 25;
  const int kTextFontHeight_ = 10;

  std::string source_path_ = "";
  std::string destination_path_ = "";
  Magick::Image image_ = Magick::Image();
  SstvImage::Mode mode_;
  bool crop_;
};

class SstvImageToolsException : public std::exception {
 public:
  SstvImageToolsException(std::string message) : message_(message) {}
  ~SstvImageToolsException() throw() {}
  const char *what() const throw() { return message_.c_str(); }

 private:
  std::string message_;
};

bool ConvertToRobot8(std::string image_path);
bool ConvertToRobot36(std::string image_path);
bool ConvertToCustom8(std::string image_path);

bool Pixels(std::string image_path);

#endif