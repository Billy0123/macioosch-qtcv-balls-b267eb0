#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "cv_balls.h"

cv::Mat drawAsCirc(const cv::Mat image, int filtered_hue, int thresh_hue, int thresh_sat,
                     int thresh_val, int par_open, int par_close, int img_pos[])
{
    cv::Mat processed = cv::Mat(image);
    // processed is BGR

    cv::cvtColor(processed, processed, CV_BGR2HSV);
    // processed is HSV

    // HSV thresholding
    cv::Scalar hsv_min = cv::Scalar( filtered_hue-thresh_hue, thresh_sat, thresh_val, 0);
    cv::Scalar hsv_max = cv::Scalar( filtered_hue+thresh_hue, 256, 256, 0);
    cv::inRange(processed, hsv_min, hsv_max, processed);
    // processed is GRAY

    // remove false positives
    cv::dilate( processed, processed, cv::Mat(), cv::Point2i(-1,-1), par_close);
    cv::erode( processed, processed, cv::Mat(), cv::Point2i(-1,-1), par_close);

    // remove holes in balls
    cv::erode( processed, processed, cv::Mat(), cv::Point2i(-1,-1), par_open);
    cv::dilate( processed, processed, cv::Mat(), cv::Point2i(-1,-1), par_open);

    cv::Mat image_out;
    cv::cvtColor(image,image_out,CV_HSV2BGR);

    // find contours
    cv::Mat canny_output;
    cv::Canny(processed,canny_output,100,100);
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(canny_output,contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

    if (!contours.empty())
    {
        // find the largest contour
        int maxarea = 0, idx=0;
        for(int i=0; i < (int)contours.size(); i++)
            if(maxarea < (int)contours[i].size())
            {
                idx = i;
                maxarea = (int)contours[i].size();
            }

        if (!contours[idx].empty())
        {
            // calculate the bounding rect of the largest area contour and visualise it
            cv::Rect rect = cv::boundingRect(contours[idx]);
            cv::Point center = cv::Point( rect.x+rect.width/2, rect.y+rect.height/2);
            int radius = round((rect.width+rect.height)/4.0);
            cv::circle( image_out, center, radius, CV_RGB(255,0,0));

            img_pos[0] =  center.x-image.size[1]/2;
            img_pos[1] = -center.y+image.size[0]/2;
            img_pos[2] = 2.0*radius;
        }
    }

    return image_out;
}

bool ballRealPos(const int img_pos[], double real_diameter, double fov, int img_width, double real_pos[])
{
    double ball_angle = (fov*3.1416/180.0)*img_pos[2]/img_width;
    double mupi = real_diameter/img_pos[2];

    real_pos[0] = mupi*img_pos[0];
    real_pos[1] = mupi*img_pos[1];
    real_pos[2] = real_diameter/tan(ball_angle);

    return true;
}
