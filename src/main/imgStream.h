#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <queue>
#include <assert.h>
using namespace std;
using namespace cv;
enum ImgMethod
{
    IMACQ_CAM, //!< Images
    IMACQ_IMGS, //!< Camera
    IMACQ_VID, //!< Video
};


class imgStream{

public:
    VideoCapture *capture;
    int method;
    string imgPath;
    queue<string> imgName;
    Mat currImage;
    int imgNum;
    int currFrame;
    imgStream();
    imgStream(int Method,string path);
    ~imgStream();
    int getCurrImage();
    void initImageStream();
    void exitImageStream();
    void getImgFromPath(string path);

};
