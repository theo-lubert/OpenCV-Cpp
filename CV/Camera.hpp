
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>
#include			"Capture.hpp"

namespace			CV {

  class				Camera : public Capture {
  private:
    int				index;
    int				type;

  public:
    Camera(int _index = 0, int _type = CV_CAP_V4L);
    ~Camera(void);
  };

}
