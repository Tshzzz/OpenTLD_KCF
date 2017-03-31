#include <opencv2/opencv.hpp>
#include <iostream>

#include "imgStream.h"
#include <TLD.h>

using namespace std;
using namespace cv;

cv::Mat imgDisplay,tmp;
cv::Rect initRect;
int initBreak;
static void on_mouse(int event,int x,int y,int flags,void *ustc);
void configureTracker(tld::TLD *tracker,Mat grey);

int main(int argc, char **argv)
{
    imgStream *test;
    int initWaitKey = 0;
    if(argc != 3)
    {
        test = new imgStream();
        initWaitKey = 20;
    }
    else
    {
        int method = IMACQ_CAM;
        if(strcmp(argv[1], "-IMG") == 0)
        {
            method = IMACQ_IMGS;
            initWaitKey = 0;
        }
        if(strcmp(argv[1], "-VID") == 0)
        {
            method = IMACQ_VID;
            initWaitKey = 0;
        }
        if(strcmp(argv[1], "-CAM") == 0)
        {
            method = IMACQ_CAM;
            initWaitKey = 20;
        }
        string imgPath(argv[2]);
        test = new imgStream(method,imgPath);
        cout <<imgPath<<endl;
    }

    int seed = 0;
    srand(seed);
    initBreak = 0;
    namedWindow("img");
    setMouseCallback("img",on_mouse,0);
    while(test->getCurrImage() == 1)
    {
        test->currImage.copyTo(imgDisplay);
        test->currImage.copyTo(tmp);
        if(initBreak == 1)
            break;
        imshow("img",tmp);
        waitKey(initWaitKey);
    }

    Mat grey(imgDisplay.rows,imgDisplay.cols, CV_8UC1);
    cvtColor(imgDisplay,grey,CV_BGR2GRAY);

    tld::TLD *trackerTLD = new tld::TLD();
    configureTracker(trackerTLD,grey);
    trackerTLD->selectObject(grey,imgDisplay,&initRect);

    cv::Mat imageCurr;
    while (test->getCurrImage() == 1)
    {
        test->currImage.copyTo(imageCurr);
        imageCurr.copyTo(imgDisplay);
        double tic = cvGetTickCount();
        trackerTLD->processImage(imageCurr);
        double toc = (cvGetTickCount() - tic) / cvGetTickFrequency();
        toc = toc / 1000000;
        float fps = 1 / toc;
        ostringstream getString;
        getString <<"fps: "<<fps;
        cv::putText(imgDisplay,getString.str(),Point(20,30),FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255,255));
        if(trackerTLD->currBB != NULL)
            cv::rectangle(imgDisplay,Rect(trackerTLD->currBB->x,trackerTLD->currBB->y,trackerTLD->currBB->width,trackerTLD->currBB->height),Scalar(0,255,0,255),4);
        cv::imshow("img", imgDisplay);
        char key = cv::waitKey(20);
        if (key == 'q')
        {
            break;
        }
    }
    delete trackerTLD;
    delete test;
    return 0;
}


void configureTracker(tld::TLD *tracker , Mat grey)
{

    tracker->alternating = false;
    tracker->trackerEnabled = true;
    tracker->learningEnabled = true;
    tracker->detectorCascade->varianceFilter->enabled = true;
    tracker->detectorCascade->ensembleClassifier->enabled = true;
    tracker->detectorCascade->nnClassifier->enabled = true;

    // classifier
    tracker->detectorCascade->useShift = true;
    tracker->detectorCascade->shift = 0.1;
    tracker->detectorCascade->minScale = -10;
    tracker->detectorCascade->maxScale = 10;
    tracker->detectorCascade->minSize = 25;
    tracker->detectorCascade->numTrees = 10;
    tracker->detectorCascade->numFeatures = 13;
    tracker->detectorCascade->nnClassifier->thetaTP = 0.65;
    tracker->detectorCascade->nnClassifier->thetaFP = 0.5;

    tracker->detectorCascade->imgWidth = grey.cols;
    tracker->detectorCascade->imgHeight = grey.rows;
    tracker->detectorCascade->imgWidthStep = grey.step;

}


static void on_mouse(int event,int x,int y,int flags,void *ustc)
{
    static Point pre_pt(-1,-1);
    static Point cur_pt(-1,-1);
    char temp[16];

    if (event == CV_EVENT_LBUTTONDOWN)
    {
        pre_pt = Point(x,y);
    }
    else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))
    {
        tmp.copyTo(imgDisplay);
        cur_pt = Point(x,y);
        rectangle(imgDisplay,pre_pt,cur_pt,Scalar(0,255,0,0),2,8,0);
        imshow("img",imgDisplay);
    }
    else if (event == CV_EVENT_LBUTTONUP)
    {
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = Point(x,y);
        rectangle(tmp,pre_pt,cur_pt,Scalar(0,255,0,0),2,8,0);
        imshow("img",tmp);
        int width = abs(pre_pt.x - cur_pt.x);
        int height = abs(pre_pt.y - cur_pt.y);
        if (width == 0 || height == 0)
        {
            printf("width == 0 || height == 0");
            return;
        }
        initRect = Rect(min(cur_pt.x,pre_pt.x),min(cur_pt.y,pre_pt.y),width,height);
        initBreak = 1;
    }
    waitKey(1);
}
