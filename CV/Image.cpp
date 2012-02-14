
#include			"Image.hpp"

using namespace			CV;

IplImage			*Image::getIplImage(void)
{
  return (image);
}

int				Image::save(const std::string &filename)
{
  return (cvSaveImage(filename.c_str(), image));
}

int				Image::save(const char *filename)
{
  return (cvSaveImage(filename, image));
}

Image				*Image::copy(void)
{
  return (new Image(cvCloneImage(image)));
}

Image				*Image::convert(int flags)
{
  Image				*tmp = new Image(image->width, image->height,
						 image->depth, image->nChannels);

  if (tmp)
    cvConvertImage(image, tmp->getIplImage(), flags);
  return (tmp);
}

Image				*Image::convertColor(int code, int depth, int channels)
{
  Image				*tmp = new Image(image->width, image->height,
						 depth, channels);

  if (tmp)
    cvCvtColor(image, tmp->getIplImage(), code);
  return (tmp);
}

Image::Image(const std::string &filename, int isColor, bool _needsRelease)
  : image(NULL), needsRelease(_needsRelease)
{
  image = cvLoadImage(filename.c_str(), isColor);
}

Image::Image(const char *filename, int isColor, bool _needsRelease)
  : image(NULL), needsRelease(_needsRelease)
{
  image = cvLoadImage(filename, isColor);
}

Image::Image(int width, int height, int depth, int channels)
  : image(NULL), needsRelease(true)
{
  image = cvCreateImage(cvSize(width, height), depth, channels);
}

Image::Image(IplImage *_image, bool _needsRelease)
  : image(_image), needsRelease(_needsRelease)
{
}

Image::~Image(void)
{
  if ((image) && (needsRelease))
    cvReleaseImage(&image);
}
