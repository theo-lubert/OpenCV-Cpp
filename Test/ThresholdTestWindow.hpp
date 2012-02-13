
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>
#include			"../Window.hpp"

namespace			CV {

  class				ThresholdTestWindow : public Window {
  private:
    Image			*image;
    int				threshold;
    int				maxValue;
    int				thresholdType;

  public:
    Image			*getImage(void);

    virtual void		showImage(Image *image);

    ThresholdTestWindow(int _threshold, int _maxValue, int _thresholdType = CV_THRESH_BINARY);
    ~ThresholdTestWindow(void);
  };

}
