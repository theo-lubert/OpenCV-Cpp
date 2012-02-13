
#include			"ThresholdTestWindow.hpp"

using namespace			CV;

Image				*ThresholdTestWindow::getImage(void)
{
  return (image);
}

void				ThresholdTestWindow::showImage(Image *img)
{
  if (image)
    delete image;
  image = new Image(img->getIplImage()->width, img->getIplImage()->height,
		    img->getIplImage()->depth, img->getIplImage()->nChannels);
  cvThreshold(img->getIplImage(), image->getIplImage(),
	      (double)threshold, (double)maxValue, thresholdType);
  Window::showImage(image);
}

ThresholdTestWindow::ThresholdTestWindow(int _threshold, int _maxValue, int _thresholdType)
  : Window("ThresholdTestWindow"), image(NULL), threshold(_threshold),
    maxValue(_maxValue), thresholdType(_thresholdType)
{
  createTrackbar("Threshold", &threshold, 255, NULL);
  setTrackbarPos("Threshold", threshold);

  createTrackbar("MaxValue", &maxValue, 255, NULL);
  setTrackbarPos("MaxValue", maxValue);
}

ThresholdTestWindow::~ThresholdTestWindow(void)
{
  if (image)
    delete image;
}
