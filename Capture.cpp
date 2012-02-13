
#include			"Capture.hpp"

using namespace			CV;

double				Capture::getProperty(int propertyId)
{
  return (cvGetCaptureProperty(capture, propertyId));
}

int				Capture::setCaptureProperty(int propertyId, double value)
{
  return (cvSetCaptureProperty(capture, propertyId, value));
}

int				Capture::grabFrame(void)
{
  return (cvGrabFrame(capture));
}

Image				*Capture::retrieveFrame(void)
{
  return (new Image(cvRetrieveFrame(capture), false));
}

Image				*Capture::queryFrame(void)
{
  return (new Image(cvQueryFrame(capture), false));
}

Capture::Capture(void)
  : capture(NULL)
{
}

Capture::~Capture(void)
{
  if (capture)
    cvReleaseCapture(&capture);
}
