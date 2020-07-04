#
# Makefile for the Html C++ Library
#

ifndef HTML_WORK_DIR
HTML_WORK_DIR = $(shell pwd)
endif

HTML_SRC_DIR = $(HTML_WORK_DIR)/src
HTML_HEADERS_DIR = $(HTML_WORK_DIR)/headers
HTML_OBJS_DIR = $(HTML_WORK_DIR)/build

CPP = g++
CPPFLAGS = -std=c++11 -I $(HTML_HEADERS_DIR) -o0 -ggdb

HTML_SRC_FILES = $(wildcard $(HTML_SRC_DIR)/*.cpp)
HTML_OBJS = $(patsubst $(HTML_SRC_DIR)/%.cpp,$(HTML_OBJS_DIR)/%.o,$(HTML_SRC_FILES))

$(HTML_OBJS_DIR)/%.o: $(HTML_SRC_DIR)/%.cpp
	@test -d $(HTML_OBJS_DIR) || mkdir $(HTML_OBJS_DIR)
	@echo -n "- Compiling Html object "$^
	@$(CPP) $(CPPFLAGS) -c -o $@ $^ && echo " : Successful" || echo " : Failed"
	
Html: $(HTML_OBJS)

HtmlClean:
	@echo "Removing Html Objects"
	@rm -f $(HTML_OBJS_DIR)/*.o

