#include "imgStream.h"

imgStream::imgStream()
{
    method = IMACQ_CAM;
    initImageStream();
}

imgStream::imgStream(int Method,string path)
{
    method = Method;
    imgPath = path;
    initImageStream();
}

void imgStream::initImageStream()
{
    if(method == IMACQ_CAM)
        capture = new VideoCapture(0);
    if(method == IMACQ_VID)
        capture = new VideoCapture(imgPath);
    if(method == IMACQ_IMGS)
    {
        capture == NULL;
        getImgFromPath(imgPath);
    }

}


void imgStream::getImgFromPath(string path)
{
    ifstream infile (path+"/image.txt");
    string s;
    while(getline(infile,s))
    {
        imgName.push(path+'/'+s);
    }

}


int imgStream::getCurrImage()
{

    if(method != IMACQ_IMGS)
        capture->read(currImage);
    else
    {
        if(imgName.empty() == true)
            return 0;
        string img_name = imgName.front();
        currImage = imread(img_name);
        imgName.pop();

    }
    return 1;
}


void imgStream::exitImageStream()
{
    if(method != IMACQ_IMGS)
        delete capture;
}

imgStream::~imgStream()
{
    exitImageStream();
}
