
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>
#include			"../Window.hpp"

namespace			CV {

  class				AdaptiveThresholdTestWindow : public Window {
  private:
    Image			*image;
    int				threshold;
    int				maxValue;
    int				adaptiveMethod;
    int				thresholdType;
    int				blockSize;
    double			param1;

  public:
    Image			*getImage(void);

    virtual void		showImage(Image *image);

    AdaptiveThresholdTestWindow(double _maxValue, int _adaptiveMethod = CV_ADAPTIVE_THRESH_MEAN_C,
				int _thresholdType = CV_THRESH_BINARY, int _blockSize = 3,
				double _param1 = 5);
    ~AdaptiveThresholdTestWindow(void);
  };

}
