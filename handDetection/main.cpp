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

int				cvSeqSize(CvSeq *seq){
  int				count;

  for(count = 0; seq != NULL; seq = seq->h_next) {
    count++;
  }
  return count;
}

void				printContours(CV::Image *image, CV::Image *gray)
{
  CvMemStorage			*storage = cvCreateMemStorage(0);
  CvMemStorage			*st = cvCreateMemStorage(0);
  CvMemStorage			*defectst = cvCreateMemStorage(0);
  CvSeq				*contour;

  int				*hull;
  int				hullsize;
  CvSeq				*defect;
  CvSeq				*convexhull;
  CvPoint			*points;
  CvConvexityDefect		*d;

  cvFindContours(gray->getIplImage(), st, &contour);
  contour = cvApproxPoly(contour, sizeof(CvContour), st, CV_POLY_APPROX_DP, 5, 1);
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
      if ((defect->total >= 3)
	  && (rect.width > 100) && (rect.height > 100)
	  && (rect.width < 400) && (rect.height < 400))
	{
	  cvRectangle(image->getIplImage(),
		      cvPoint(rect.x, rect.y),
		      cvPoint((rect.x + rect.width),
			      (rect.y + rect.height)),
		      color);
	  cvDrawContours(image->getIplImage(),
			 contour,
			 color,
			 cvScalarAll(155),
			 -1, 1, 8);

	  while (defect)
	    {
	      CvConvexityDefect *d = CV_GET_SEQ_ELEM(CvConvexityDefect, defect, 0);

	      d = (CvConvexityDefect *)malloc(sizeof(CvConvexityDefect) * defect->total);
	      cvCvtSeqToArray(defect, d, CV_WHOLE_SEQ);

	      color = CV_RGB(255, 0, 0);
	      for (int i=0, k=defect->total; i<k; i++) {
		cvLine(image->getIplImage(), *(d[i].start), *(d[i].end), color);
		cvCircle(image->getIplImage(), *(d[i].depth_point), 5, color, 1, CV_AA);
		cvCircle(image->getIplImage(), *(d[i].start), 5, color, -1, CV_AA);
		if (defect->h_next == NULL) {
		  cvCircle(image->getIplImage(), *(d[i].end), 5, color, -1, CV_AA);
		}
	      }
	      defect = defect->h_next;
	    }
	}

      contour = contour->h_next;
    }
  cvReleaseMemStorage(&st);
  cvReleaseMemStorage(&defectst);
}

int				main(int ac, char **av)
{
  int				camIdx = 0;
  if (ac > 1)
    camIdx = atoi(av[1]);

  cvInitSystem(ac, av);

  // CV::ThresholdTestWindow	twin(80, 255, CV_THRESH_BINARY);
  // CV::ContourTestWindow		cwin(CV_RETR_TREE, CV_CHAIN_APPROX_TC89_KCOS);
  CV::Window			win("Hand detection");
  CV::Camera			cam(camIdx);
  CV::Image			*frame;
  char				key = 0;

  while (key != 27) // ESC
    {
      if ((frame = cam.queryFrame()) != NULL)
	{
	  CV::Image			*gray = frame->convertColor(CV_BGR2GRAY, 8, 1);

	  cvSmooth(gray->getIplImage(), gray->getIplImage());
	  // win.showImage(gray);
	  // cwin.showImage(frame, win.getImage());
	  cvThreshold(gray->getIplImage(), gray->getIplImage(),
		      80.0, 255.0, CV_THRESH_BINARY);
	  printContours(frame, gray);
	  win.showImage(frame);
	  delete gray;
	  delete frame;
	}
      key = cvWaitKey(10);
    }

  return 0;
}
