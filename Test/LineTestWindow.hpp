
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>
#include			"../Window.hpp"

namespace			CV {

  class				LineTestWindow : public Window {
  private:
    Image			*image;
    CvMemStorage		*storage;
    CvSeq			*lines;
    int				method;
    int				rho;
    int				theta;
    int				threshold;
    double			param1;
    double			param2;

  public:
    Image			*getImage(void);

    virtual void		showImage(Image *image);

    LineTestWindow(int _method, int _rho, int _theta, int _threshold,
		   double _param1 = 0, double _param2 = 0);
    ~LineTestWindow(void);
  };

}
