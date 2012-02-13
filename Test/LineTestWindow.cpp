
#include			"LineTestWindow.hpp"

using namespace			CV;

Image				*LineTestWindow::getImage(void)
{
  return (image);
}

void				correctVar(int *var, int min, int max)
{
  *var = (*var < min) ? min : *var;
  *var = (*var > max) ? max : *var;
}

void				LineTestWindow::showImage(Image *img)
{
  correctVar(&rho, 1, 360);
  correctVar(&theta, 1, 360);
  correctVar(&threshold, 1, 255);
  setTrackbarPos("Rho", rho);
  setTrackbarPos("Theta", theta);
  setTrackbarPos("Threshold", threshold);

  if (image)
    delete image;
  if (storage)
    cvReleaseMemStorage(&storage);
  storage = cvCreateMemStorage(0);
  image = new Image(img->getIplImage()->width, img->getIplImage()->height,
		    8, 1);
  cvCanny(img->getIplImage(), image->getIplImage(), 50, 200, 3);
  lines = cvHoughLines2(image->getIplImage(), storage,
  			method,
  			rho,
  			((double)theta)/180.0,
  			threshold,
  			param1,
  			param2);


  cvSet(image->getIplImage(), cvScalar(0, 0, 0));

  for (int i=0; i<lines->total; i++)
    {
      CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
      cvLine(image->getIplImage(), line[0], line[1], CV_RGB(255,255,255), 3, 8);
    }
  Window::showImage(image);
}

LineTestWindow::    LineTestWindow(int _method, int _rho, int _theta, int _threshold,
				   double _param1, double _param2)
  : Window("LineTestWindow"), image(NULL), storage(NULL), lines(NULL),
    method(_method), rho(_rho), theta(_theta),
    threshold(_threshold), param1(_param1), param2(_param2)
{
  createTrackbar("Rho", &rho, 360, NULL);
  setTrackbarPos("Rho", rho);

  createTrackbar("Theta", &theta, 360, NULL);
  setTrackbarPos("Theta", theta);

  createTrackbar("Threshold", &threshold, 255, NULL);
  setTrackbarPos("Threshold", threshold);
}

LineTestWindow::~LineTestWindow(void)
{
  if (image)
    delete image;
}
