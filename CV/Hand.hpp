
#pragma once

#include      <stdio.h>
#include			<opencv/cv.h>
#include			<opencv/highgui.h>
#include      "MemStorage.hpp"
#include      "Image.hpp"

namespace			CV {

  class				Hand {
  protected:
    CvSeq       *contour;
    MemStorage  defectst;
    CvSeq       *defect;
    CvSeq       *convexhull;

  public:
    CvSeq       *getContour(void);

    void        drawToImage(Image *image, bool focused = false);

    Hand(CvSeq *_contour, MemStorage &_defectst, CvSeq *_defect, CvSeq *_convexhull);
    ~Hand(void);
  };

}