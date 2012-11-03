#ifndef CV_BALLS_H
#define CV_BALLS_H

#include <opencv2/core/core.hpp>

cv::Mat drawAsCirc(const cv::Mat image, int filtered_hue, int thresh_hue, int thresh_sat,
                     int thresh_val, int par_open, int par_close, int img_pos[]);
bool ballRealPos(const int img_pos[], double real_diameter, double fov, int img_width, double real_pos[]);

#endif // CV_BALLS_H
