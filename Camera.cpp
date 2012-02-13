
#include			"Camera.hpp"

using namespace			CV;

Camera::Camera(int _index, int _type)
  : Capture(), index(_index), type(_type)
{
  capture = cvCaptureFromCAM(type + index);
}

Camera::~Camera(void)
{
}
