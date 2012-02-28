
#include	"Hand.hpp"

#define	ABS(n)	(((n) >= 0) ? (n) : -(n))

using namespace			CV;

CvSeq					*Hand::getContour(void)
{
	return (contour);
}

void					Hand::drawToImage(Image *image, bool focused)
{
	CvRect				rect = cvBoundingRect(contour, 0);

    CvScalar color = cvScalarAll(255);
  	if (focused)
  		color = CV_RGB(255, 0, 0);
	cvRectangle(*image,
		cvPoint(rect.x, rect.y),
		cvPoint((rect.x + rect.width),
			(rect.y + rect.height)),
		color);
	  cvDrawContours(*image,
			 contour,
			 cvScalarAll(255),
			 cvScalarAll(155),
			 -1, 1, 8);

	  while ((focused) && (defect))
	    {
	      CvPoint lastPoint = cvPoint(-1, -1);
	      CvConvexityDefect *d = CV_GET_SEQ_ELEM(CvConvexityDefect, defect, 0);

	      d = (CvConvexityDefect *)malloc(sizeof(CvConvexityDefect) * defect->total);
	      cvCvtSeqToArray(defect, d, CV_WHOLE_SEQ);

	      color = CV_RGB(255, 0, 0);
	      for (int i=0, k=defect->total; i<k; i++) {
	      	if (d[i].depth > 5) {
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

Hand::Hand(CvSeq *_contour, MemStorage &_defectst, CvSeq *_defect, CvSeq *_convexhull)
	: contour(_contour), defectst(_defectst), defect(_defect), convexhull(_convexhull)
{
}

Hand::~Hand(void)
{
}
