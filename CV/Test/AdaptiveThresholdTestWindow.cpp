
#include			"AdaptiveThresholdTestWindow.hpp"

using namespace			CV;

Image				*AdaptiveThresholdTestWindow::getImage(void)
{
  return (image);
}

void				AdaptiveThresholdTestWindow::showImage(Image *img)
{
  if (image)
    {
      delete image;
      image = NULL;
    }
  image = new Image(img->getIplImage()->width, img->getIplImage()->height,
		    img->getIplImage()->depth, img->getIplImage()->nChannels);

  blockSize += (blockSize % 2) ? 0 : 1;
  if (blockSize < 3)
    blockSize = 3;
  setTrackbarPos("BlockSize", blockSize);

  cvAdaptiveThreshold(img->getIplImage(), image->getIplImage(),
		      (double)maxValue, adaptiveMethod, thresholdType, blockSize, param1);
  Window::showImage(image);
}

AdaptiveThresholdTestWindow::AdaptiveThresholdTestWindow(double _maxValue, int _adaptiveMethod,
							 int _thresholdType, int _blockSize,
							 double _param1)
  : Window("AdaptiveThresholdTestWindow"), image(NULL),
    maxValue(_maxValue), adaptiveMethod(_adaptiveMethod),
    thresholdType(_thresholdType), blockSize(_blockSize), param1(_param1)
{
  createTrackbar("MaxValue", &maxValue, 255, NULL);
  setTrackbarPos("MaxValue", maxValue);

  createTrackbar("BlockSize", &blockSize, 75, NULL);
  setTrackbarPos("BlockSize", blockSize);
}

AdaptiveThresholdTestWindow::~AdaptiveThresholdTestWindow(void)
{
  if (image)
    delete image;
}
