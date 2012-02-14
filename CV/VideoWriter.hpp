
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>

namespace			CV {

  class				VideoWriter {
  private:
    CvVideoWriter		*writer;

  public:
    int				writeFrame(const IplImage *image);

    VideoWriter(const char *name, int fourcc, double fps, CvSize frame_size, int is_color = 1);
    ~VideoWriter(void);
  };

}
