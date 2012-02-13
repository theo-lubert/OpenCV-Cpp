
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>

namespace			CV {

  class				Mat {
  protected:
    CvMat			*mat;

  public:
    Mat(CvMat *_mat);
    ~Mat(void);
  };

}
