#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <queue>
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

    imgStream();
    imgStream(int Method,string path);
    ~imgStream();
    int getCurrImage();
    void initImageStream();
    void exitImageStream();
    void getImgFromPath(string path);

};
