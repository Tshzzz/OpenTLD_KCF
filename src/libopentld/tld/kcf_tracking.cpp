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
 * MedianFlowTracker.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: Georg Nebehay
 */

#include "kcf_tracking.h"


using namespace cv;

namespace tld
{

Tracker::Tracker()
{
    trackerBB = NULL;
}

Tracker::~Tracker()
{
    cleanPreviousData();
}

void Tracker::cleanPreviousData()
{
    delete trackerBB;
    trackerBB = NULL;
}

void Tracker::tracker_init(Mat &org, Rect *init_bb)
{
    Rect tmpBB = Rect(init_bb->x, init_bb->y, init_bb->width, init_bb->height);
    kcf.init(org,tmpBB);
}

void Tracker::update_pos(Mat img,Rect *init_bb)
{

    Rect bbox = Rect(init_bb->x, init_bb->y, init_bb->width, init_bb->height);
    double x1 = bbox.x, x2 = bbox.x + bbox.width, y1 = bbox.y, y2 = bbox.y + bbox.height;
    if (x1 < 0) x1 = 0.;
    if (x2 > img.cols-1) x2 = img.cols - 1;
    if (y1 < 0) y1 = 0;
    if (y2 > img.rows-1) y2 = img.rows - 1;
    BBox_c new_pos;
    new_pos.w = x2-x1;
    new_pos.h = y2-y1;
    new_pos.cx = x1 + new_pos.w/2.;
    new_pos.cy = y1 + new_pos.h/2.;
    //trackerBB = new Rect(init_bb->x, init_bb->y, init_bb->width + init_bb->x, init_bb->height + init_bb->y);
    kcf.updateTrackerPosition(new_pos);
    //kcf.setTrackerPose(new_pos,img);
}

void Tracker::tracking(const Mat &currMat)
{

    //if(prevBB != NULL)
    //{
        Mat tmp;
        currMat.copyTo(tmp);


        kcf.track(tmp);

        BBox_c bb = kcf.getBBox();
        int bb_w = (int)bb.w;
        int bb_h = (int)bb.h;
        int bb_x = (int) bb.cx - bb.w/2;
        int bb_y = (int) bb.cy - bb.h/2;
        if(bb_x < 1 || bb_y < 1 || bb_w <= 1 || bb_h <= 1 || bb_w + bb_x > currMat.cols ||
                bb_h + bb_y  > currMat.rows
                ||bb_x != bb_x || bb_y != bb_y || bb_w != bb_w || bb_h != bb_h) //x!=x is check for nan
        {
                   //Leave it empty
            //printf("=============== %d %d %d %d \n", currMat.rows , bb_h , currMat.cols , bb_w); //<< <<endl;
        }
        else
        {
            //trackerBB = new Rect(bb.cx - bb.w/2., bb.cy - bb.h/2., bb.w, bb.h);
            //if(bb.cx < 1.0)
            trackerBB = new Rect(bb_x, bb_y, bb_w, bb_h);
            //printf("%d %d %d %d \n",bb_rows , bb_col ,bb_x ,bb_y);
            //printf("------------%f %f %f %f \n", bb.cx - bb.w/2., bb.cy - bb.h/2., bb.w, bb.h);
            //cv::rectangle(tmp, cv::Rect(bb.cx - bb.w/2., bb.cy - bb.h/2., bb.w, bb.h), CV_RGB(0,255,0), 2);
            //imshow("test",tmp);
            //waitKey(0);
        }


    //}
}

} /* namespace tld */


