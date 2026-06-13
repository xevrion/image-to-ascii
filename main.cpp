#include <iostream>
using namespace std;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
  int width = 0;
  int height = 0;
  int channels = 0;
  // string Lmap = " .:-=+*#%@";
  string Lmap = "@%#*+=-:. ";

  // Load the pixel data (0 means "keep original number of channels")
  unsigned char *imgData = stbi_load("cat.jpg", &width, &height, &channels, 0);
  // unsigned char *imgData = stbi_load("dragon.jpg", &width, &height, &channels, 0);

  // Always check for allocation/loading failure
  if (imgData == nullptr) {
    std::cout << "Error: Failed to load image file." << std::endl;
    return -1;
  }

  // Success: Print image properties
  std::cout << "Successfully loaded image!" << std::endl;
  std::cout << "Width:    " << width << " px" << std::endl;
  std::cout << "Height:   " << height << " px" << std::endl;
  std::cout << "Channels: " << channels << " (3=RGB, 4=RGBA)" << std::endl;

  // // Optional: Access the first pixel's RGB data
  // if (channels >= 3) {
  //     int r = imgData[0];
  //     int g = imgData[1];
  //     int b = imgData[2];
  //     std::cout << "First pixel RGB: (" << r << ", " << g << ", " << b << ")"
  //     << std::endl;
  // }
  // 0.299×R + 0.587×G + 0.114×B
  for (int i = 0; i < height; i+=8) {
    for (int j = 0; j < width; j+=8) {
      int R = imgData[(i * width + j) * 3 + 0];
      int G = imgData[(i * width + j) * 3 + 1];
      int B = imgData[(i * width + j) * 3 + 2];
      // std::cout << "pixel RGB: (" << R << ", " << G << ", " << B << ")"<<endl;
                float Lumi = 0.299*R + 0.587*G + 0.114*B;
                // cout<<"Luminance: "<<0.299*R + 0.587*G + 0.114*B<<endl;
                int index = Lumi / 255.0 *9;
                cout << "\x1b[38;2;" << R << ";" << G << ";" << B << "m" << Lmap[index] << Lmap[index] << "\x1b[0m";
    }
    cout<<endl;
  }

  // CRITICAL: Free the memory allocated by stb_image
  stbi_image_free(imgData);

  return 0;
}
