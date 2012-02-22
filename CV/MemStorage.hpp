
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>

namespace			CV {

  class				MemStorage {
  private:
    int				blockSize;
    CvMemStorage	*mem;

  public:
  	CvMemStorage	*getMemStorage(void);

  	operator		CvMemStorage*();

    MemStorage(int _blockSize = 0);
    ~MemStorage(void);
  };

}
