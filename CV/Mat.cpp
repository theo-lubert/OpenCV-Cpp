
#include			"Mat.hpp"

using namespace			CV;

Mat::Mat(CvMat *_mat)
  : mat(_mat)
{
}

Mat::~Mat(void)
{
  if (mat)
    cvReleaseMat(&mat);
}
