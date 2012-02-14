
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>
#include			"../Window.hpp"

namespace			CV {

  class				ContourTestWindow : public Window {
  private:
    Image			*image;
    CvMemStorage		*storage;
    CvSeq			*first_contour;
    int				header_size;
    int				mode;
    int				method;
    CvPoint			offset;

  public:
    Image			*getImage(void);

    void			showImage(Image *original, Image *image);

    ContourTestWindow(int mode, int method = CV_CHAIN_APPROX_SIMPLE,
		      CvPoint offset = cvPoint(0, 0));
    ~ContourTestWindow(void);
  };

}
