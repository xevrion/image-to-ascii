#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <thread>
#include <chrono>

int main() {
  int width = 0;
  int height = 0;
  int channels = 0;
  // string Lmap = " .:-=+*#%@";
  string Lmap = "@%#*+=-:. ";

  // open a video file
  cv::VideoCapture cap("video.mp4");
    if (!cap.isOpened()) {
        std::cout << "Error: Failed to open video file." << std::endl;
        return -1;
    }
double fps = cap.get(cv::CAP_PROP_FPS);
  cv::Mat frame;
  for (;;) {
    cap >> frame; // get a new frame from video
    if (frame.empty()) {
      break; // end of video
    }
    cout << "\x1b[2J\x1b[H";
    width = frame.cols;
    height = frame.rows;
    channels = frame.channels();

    std::cout << "Width:    " << width << " px" << std::endl;
    std::cout << "Height:   " << height << " px" << std::endl;
    std::cout << "Channels: " << channels << std::endl;

    // 0.299×R + 0.587×G + 0.114×B
    for (int i = 0; i < height; i += 8) {
      for (int j = 0; j < width; j += 8) {
        int R = frame.at<cv::Vec3b>(i, j)[2];
        int G = frame.at<cv::Vec3b>(i, j)[1];
        int B = frame.at<cv::Vec3b>(i, j)[0];
        // std::cout << "pixel RGB: (" << R << ", " << G << ", " << B <<
        // ")"<<endl;
        float Lumi = 0.299 * R + 0.587 * G + 0.114 * B;
        // cout<<"Luminance: "<<0.299*R + 0.587*G + 0.114*B<<endl;
        int index = Lumi / 255.0 * 9;
        cout << "\x1b[38;2;" << R << ";" << G << ";" << B << "m" << Lmap[index]
             << Lmap[index] << "\x1b[0m";
      }
      cout << endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 / fps)));
  }

  return 0;
}
