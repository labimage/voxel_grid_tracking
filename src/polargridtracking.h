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


#ifndef POLARGRIDTRACKING_H
#define POLARGRIDTRACKING_H

#include "cell.h"
#include "params_structs.h"

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <eigen3/Eigen/Dense>

namespace polar_grid_tracking {
class PolarGridTracking
{
public:
    PolarGridTracking(const uint32_t & rows, const uint32_t & cols);
    void getMeasurementModelFromPointCloud(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr & pointCloud, 
                                                 const t_Camera_params & cameraParams);
    
private:
    typedef Eigen::Matrix<Cell, Eigen::Dynamic, Eigen::Dynamic> CellGrid;
    CellGrid m_grid;
    
    
};
}

#endif // POLARGRIDTRACKING_H