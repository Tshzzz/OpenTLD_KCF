/*  Copyright 2011 AIT Austrian Institute of Technology
*
*   This file is part of OpenTLD.
*
*   OpenTLD is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   OpenTLD is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with OpenTLD.  If not, see <http://www.gnu.org/licenses/>.
*
*/

/*
 * MedianFlowTracker.h
 *
 *  Created on: Nov 17, 2011
 *      Author: Georg Nebehay
 */

#ifndef MEDIANFLOWTRACKER_H_
#define MEDIANFLOWTRACKER_H_

#include <opencv/cv.h>

#include "../../3rdparty/kcf/kcf.h"

namespace tld
{

class Tracker
{
public:
    cv::Rect *trackerBB;
    Tracker();
    virtual ~Tracker();
    void cleanPreviousData();
    void tracker_init(cv::Mat &org,cv::Rect *init_bb);
    KCF_Tracker kcf;
    void tracking(const cv::Mat &currImg);
    void update_pos(cv::Mat img, cv::Rect *init_bb);//void updateTrackerPosition();
};

} /* namespace tld */
#endif /* MEDIANFLOWTRACKER_H_ */
