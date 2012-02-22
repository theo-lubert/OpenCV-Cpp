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

#define	ABS(n)	(((n) >= 0) ? (n) : -(n))

void				printContours(CV::Image *image, CV::Image *gray)
{
  CV::MemStorage			st;
  CV::MemStorage			defectst;
  CvSeq				*contour;

  int				*hull;
  CvSeq				*defect;
  CvSeq				*convexhull;
  CvPoint			*points;
  CvConvexityDefect		*d;

  cvFindContours(*gray, st, &contour);
  // contour = cvApproxPoly(contour, sizeof(CvContour), st, CV_POLY_APPROX_DP, 30, 1);
  while (contour)
    {
      convexhull = cvConvexHull2(contour, NULL,
				 CV_COUNTER_CLOCKWISE,
				 0);

      CvScalar color = cvScalarAll(255);
      defect = cvConvexityDefects(contour,
				  convexhull,
				  defectst);
      CvRect rect = cvBoundingRect(contour, 0);
      if ((defect->total >= 0)
	  && (rect.width > 100) && (rect.height > 100)
	  && (rect.width < 400) && (rect.height < 400))
	{
	  cvRectangle(*image,
		      cvPoint(rect.x, rect.y),
		      cvPoint((rect.x + rect.width),
			      (rect.y + rect.height)),
		      color);
	  cvDrawContours(*image,
			 contour,
			 color,
			 cvScalarAll(155),
			 -1, 1, 8);

	  while (defect)
	    {
	      CvPoint lastPoint = cvPoint(-1, -1);
	      CvConvexityDefect *d = CV_GET_SEQ_ELEM(CvConvexityDefect, defect, 0);

	      d = (CvConvexityDefect *)malloc(sizeof(CvConvexityDefect) * defect->total);
	      cvCvtSeqToArray(defect, d, CV_WHOLE_SEQ);

	      color = CV_RGB(255, 0, 0);
	      for (int i=0, k=defect->total; i<k; i++) {
		if (d[i].depth > 10) {
		  cvLine(*image, *(d[i].start), *(d[i].end), color);
		  cvCircle(*image, *(d[i].depth_point), 5, color, 1, CV_AA);
		  if ((lastPoint.x >= 0)
		  	&& (ABS(pow(((d[i].start->x - lastPoint.x)), 2) + pow((d[i].start->y - lastPoint.y), 2)) < 20)) {
		  	CvPoint p = cvPoint(((d[i].start->x + lastPoint.x) / 2.0), ((d[i].start->y + lastPoint.y) / 2.0));
		  	cvCircle(*image, p, 10, color, -1, CV_AA);
		  } else {
			cvCircle(*image, *(d[i].start), 10, color, -1, CV_AA);
		  }
		  lastPoint = *(d[i].end);
		}
		if ((lastPoint.x >= 0) || (defect->h_next == NULL)) {
		  cvCircle(*image, lastPoint, 10, color, -1, CV_AA);
		}
	      }
	      defect = defect->h_next;
	    }
	}

      contour = contour->h_next;
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
	  printContours(frame, twin.getImage());
	  win.showImage(frame);
	  delete gray;
	  delete frame;
	}
      key = cvWaitKey(10);
    }

  return 0;
}
