
#include			"ContourTestWindow.hpp"

using namespace			CV;

Image				*ContourTestWindow::getImage(void)
{
  return (image);
}

void				ContourTestWindow::showImage(Image *original, Image *img)
{
  if (image)
    delete image;
  image = original->copy();
  cvFindContours(img->getIplImage(), storage, &first_contour, header_size, mode, method, offset);
  if (first_contour) {
    // cvDrawContours(img,
    // 		   first_contour,
    // 		   cvScalarAll(255),
    // 		   cvScalarAll(255),
    // 		   100);
    CvScalar red = CV_RGB(250,0,0);
    CvScalar blue = CV_RGB(0,0,250);
    cvDrawContours(image->getIplImage(),
    		   first_contour,
    		   red,
    		   blue,
    		   1,
    		   2,
    		   CV_AA);
  }

  Window::showImage(image);
}

ContourTestWindow::ContourTestWindow(int _mode, int _method, CvPoint _offset)
  : Window("ContourTestWindow"), image(NULL), storage(), first_contour(NULL),
    header_size(sizeof(CvContour)), mode(_mode), method(_method), offset(_offset)
{
}

ContourTestWindow::~ContourTestWindow(void)
{
  if (image)
    delete image;
}
