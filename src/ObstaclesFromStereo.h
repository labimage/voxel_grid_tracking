/*
 *  Copyright 2013 Néstor Morales Hernández <nestor@isaatc.ull.es>
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


#ifndef OBSTACLESFROMSTEREO_H
#define OBSTACLESFROMSTEREO_H

#include <opencv2/opencv.hpp>

#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include <Eigen/Dense>
#include <string>
#include <vector>

#include "params_structs.h"

using namespace polar_grid_tracking;

class ObstaclesFromStereo {
public:
    typedef enum t_Method { SGBM = 0, STEREOVAR = 1};
    
    ObstaclesFromStereo(const cv::Size & size);
    ~ObstaclesFromStereo();
    
    void generatePointClouds(const cv::Mat & leftImg, const cv::Mat & rightImg, const cv::Mat & mask);
    
    void setCameraParams(const t_Camera_params & leftCameraParams, const t_Camera_params & rightCameraParams);
    void setSGBMParams(const t_SGBM_params & params) { m_SGBM_params = params; }
    void setMethod(const t_Method & method) { m_method = method; };
    void setGroundThresh(const double & groundThresh) { m_groundThresh = groundThresh; }
    void setBackGroundThresh(const double & backgroundThresh) { m_backgroundThresh = backgroundThresh; }
    void setLeafSize(const double & leafSize) { m_leafSize = leafSize; }
    
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr getPointCloud() { return m_pointCloud; }
    
    static void readi3DPostCalibrationFile(const std::string & fileName, std::vector<t_Camera_params> & cameraParams);
    static void getParamsFromDublinDataset(const std::string & planeFilename, std::vector<t_Camera_params> & params,
                                           double baseline = 0.0995964, double focalLength = 519.546875, cv::Size sz = cv::Size(640, 480));
    static void getFGMask(const std::string & fileName, cv::Mat & fgMask, const cv::Size & sz);
    
private:
    void setParamsGeometry(t_Camera_params & params);
    void filterMasked(const pcl::PointCloud<pcl::PointXYZRGBL>::Ptr & inputCloud, pcl::PointCloud<pcl::PointXYZRGB>::Ptr & outputCloud);
    void removeGround(pcl::PointCloud<pcl::PointXYZRGBL>::Ptr & pointCloud);
    void downsample(pcl::PointCloud<pcl::PointXYZRGB>::Ptr & pointCloud);
    
    t_Camera_params m_leftCameraParams;
    t_Camera_params m_rightCameraParams;
    
    t_SGBM_params m_SGBM_params;
    t_Method m_method;
    
    double m_groundThresh;
    double m_backgroundThresh;
    double m_leafSize;
    
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr m_pointCloud;
    
    cv::Size m_size;
};

#endif // OBSTACLESFROMSTEREO_H