
#pragma once

#include      <stdio.h>
#include			<opencv/cv.h>
#include			<opencv/highgui.h>
#include      <vector>
#include      "MemStorage.hpp"
#include      "Image.hpp"
#include      "Hand.hpp"

namespace			CV {

  class				HandDetector {
  protected:
    MemStorage            st;
    CvSeq                 *contour;
    std::vector<Hand *>   hands;


  public:
    std::vector<Hand *>   &getHands(void);

    HandDetector(Image *image);
    ~HandDetector(void);
  };

}