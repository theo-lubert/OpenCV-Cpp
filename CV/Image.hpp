
#pragma once

#include			<opencv/cv.h>
#include			<opencv/highgui.h>

namespace			CV {

  class				Image {
  protected:
    IplImage			*image;
    bool			needsRelease;

  public:
    IplImage			*getIplImage(void);

    int				save(const std::string &filename);
    int				save(const char *filename);

    Image			*copy(void);
    Image			*convert(int flags);
    Image			*convertColor(int code, int depth, int channels);

    Image(const std::string &filename, int isColor = CV_LOAD_IMAGE_COLOR, bool _needsRelease = true);
    Image(const char *filename, int isColor = CV_LOAD_IMAGE_COLOR, bool _needsRelease = true);
    Image(int width, int height, int depth, int channels);
    Image(IplImage *_image, bool _needsRelease = true);
    ~Image(void);
  };

}
