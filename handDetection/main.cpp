#include <stdio.h>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "CV/Window.hpp"
#include "CV/Test/AdaptiveThresholdTestWindow.hpp"
#include "CV/Test/ThresholdTestWindow.hpp"
#include "CV/Test/LineTestWindow.hpp"
#include "CV/Test/ContourTestWindow.hpp"
#include "CV/Camera.hpp"
#include "CV/HandDetector.hpp"

#define	ABS(n)	(((n) >= 0) ? (n) : -(n))


double x = -1;
double y = -1;

bool				isContourMatchFocusPoint(CvSeq *contour, CvPoint point)
{
	if (contour)
	{
	    CvRect rect = cvBoundingRect(contour, 0);
		return ((rect.x <= point.x) && (rect.y <= point.y)
			&& (rect.x + rect.width >= point.x) && (rect.y + rect.height >= point.y));
	}
	return (false);
}

void			callback(int event, int _x, int _y, int flags, void*)
{
	if (event == CV_EVENT_LBUTTONUP)
	{
		x = _x;
		y = _y;
	}
}

int				main(int ac, char **av)
{
  int				camIdx = 0;
  if (ac > 1)
    camIdx = atoi(av[1]);

  cvInitSystem(ac, av);

 CV::ThresholdTestWindow	twin(80, 255, CV_THRESH_BINARY);
  CV::Window			win("Hand detection");
  CV::Camera			cam(camIdx, 0);
  CV::Image			*frame;
  char				key = 0;

  cvSetMouseCallback("Hand detection", &callback);
  while (key != 27) // ESC
    {
      if ((frame = cam.queryFrame()) != NULL)
	{
	  CV::Image			*gray = frame->convertColor(CV_BGR2GRAY, 8, 1);

	  cvSmooth(*gray, *gray);
	  twin.showImage(gray);
	  // cvThreshold(gray->getIplImage(), gray->getIplImage(),
		      // 80.0, 255.0, CV_THRESH_BINARY);
	  // printContours(frame, gray);

	  // printContours(frame, twin.getImage());
	  if (x >= 0)
	  {
		  cvCircle(*frame, cvPoint(x, y), 10, cvScalarAll(255), 2, CV_AA);
		  cvCircle(*frame, cvPoint(x, y), 10, CV_RGB(255, 0, 0), 1, CV_AA);
		}

	  CV::HandDetector detector(twin.getImage());

  	  CV::Hand	*focusedHand = NULL;
	  for (int i=0, k=detector.getHands().size(); i<k; i++)
	  {
	  	CV::Hand	*hand = detector.getHands()[i];
      	bool focused = isContourMatchFocusPoint(hand->getContour(), cvPoint(x, y));
      	if (focused)
      	{
      		if (focusedHand)
      		{
      			CvRect	saveRect = cvBoundingRect(focusedHand->getContour(), 0);
	      		CvRect	rect = cvBoundingRect(hand->getContour(), 0);

	      		if (((rect.width * rect.height) < (saveRect.width * saveRect.height)))
		      		focusedHand = hand;
	     	} else {
	     		focusedHand = hand;
	     	}
      	} else {
	  		hand->drawToImage(frame);
		}
	  }
	  if (focusedHand)
	  	focusedHand->drawToImage(frame, true);

	  win.showImage(frame);
	  delete gray;
	  delete frame;
	}
      key = cvWaitKey(10);
    }

  return 0;
}
