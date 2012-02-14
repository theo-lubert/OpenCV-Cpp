
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>
#include			"Capture.hpp"

namespace			CV {

  class				CaptureFile : public Capture {
  private:
    std::string			name;

  public:
    CaptureFile(const std::string &_name);
    CaptureFile(const char *_name);
    ~CaptureFile(void);
  };

}
