
NAME		=	handdetection

CV_DIR		=	../CV
CV_SRCS		=	$(CV_DIR)/Window.cpp			\
			$(CV_DIR)/Image.cpp			\
			$(CV_DIR)/Mat.cpp			\
			$(CV_DIR)/MemStorage.cpp			\
			$(CV_DIR)/Capture.cpp			\
			$(CV_DIR)/CaptureFile.cpp		\
			$(CV_DIR)/VideoWriter.cpp		\
			$(CV_DIR)/Camera.cpp			\
			$(CV_DIR)/HandDetector.cpp		\
			$(CV_DIR)/Hand.cpp				\
			$(CV_DIR)/Test/AdaptiveThresholdTestWindow.cpp	\
			$(CV_DIR)/Test/ThresholdTestWindow.cpp	\
			$(CV_DIR)/Test/ContourTestWindow.cpp	\
			$(CV_DIR)/Test/LineTestWindow.cpp
			
LIBS		=	`pkg-config --libs opencv`
INCLUDES	=	-I. -I../

SRCS		=	main.cpp				\
			$(CV_SRCS)

OBJS		=	$(SRCS:.cpp=.o)
CXX		=	g++
CXXFLAGS	=	`pkg-config --cflags opencv` $(INCLUDES)
RM		=	rm -rf


all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CXX) -o $(NAME) $(LIBS) $(OBJS)

clean		:
			@echo "Removing temporary files"
			@$(RM) *~
			@$(RM) \#*#
			@echo "Removing object files"
			@$(RM) $(OBJS)

fclean		:	clean
			@echo "Removing binary file"
			@$(RM) $(NAME)

re		:	fclean all

rc		:	re
			@echo "Removing object files"
			@$(RM) $(OBJS)
			@echo "Removing temporary files"
			@$(RM) *~
			@$(RM) \#*#
