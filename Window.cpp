
#include			"Window.hpp"

using namespace			CV;

void				Window::destroyAll(void)
{
  cvDestroyAllWindows();
}

void				Window::showImage(Image *image)
{
  cvShowImage(name.c_str(), image->getIplImage());
}

int				Window::createTrackbar(const char *trackbarName, int *value,
						       int count, CvTrackbarCallback onChange)

{
  return (cvCreateTrackbar(trackbarName, name.c_str(), value, count, onChange));
}

int				Window::getTrackbarPos(const char *trackbarName)
{
  return (cvGetTrackbarPos(trackbarName, name.c_str()));
}

void				Window::setTrackbarPos(const char *trackbarName, int pos)
{
  cvSetTrackbarPos(trackbarName, name.c_str(), pos);
}

Window::Window(const std::string &_name, int _flags)
  : name(_name), flags(_flags)
{
  cvNamedWindow(name.c_str(), flags);
}

Window::Window(const char *_name, int _flags)
  : name(_name), flags(_flags)
{
  cvNamedWindow(name.c_str(), flags);
}

Window::~Window(void)
{
  cvDestroyWindow(name.c_str());
}
