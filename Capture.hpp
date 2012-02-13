
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>
#include			"Image.hpp"

namespace			CV {

  class				Capture {
  protected:
    CvCapture			*capture;

  public:
    double			getProperty(int propertyId);
    int				setCaptureProperty(int propertyId, double value);
    int				grabFrame(void);
    Image			*retrieveFrame(void);
    Image			*queryFrame(void);

    Capture(void);
    ~Capture(void);
  };

}
