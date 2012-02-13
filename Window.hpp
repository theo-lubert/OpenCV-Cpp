
#pragma once

#include			<string>
#include			<opencv/cv.h>
#include			<opencv/highgui.h>
#include			"Image.hpp"

#define				DEFAULT_FALGS	CV_WINDOW_AUTOSIZE

namespace			CV {

  class				Window {
  private:
    std::string			name;
    int				flags;

  public:
    static void			destroyAll(void);

    virtual void		showImage(Image *image);
    int				createTrackbar(const char *trackbarName, int *value,
					       int count, CvTrackbarCallback onChange = NULL);
    int				getTrackbarPos(const char *trackbarName);
    void			setTrackbarPos(const char *trackbarName, int pos);

    Window(const std::string &_name, int _flags = DEFAULT_FALGS);
    Window(const char *_name, int _flags = DEFAULT_FALGS);
    ~Window(void);
  };

}
