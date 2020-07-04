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
LDFLAGS = -shared

LIB_NAME = htmlCplusplus
LIB_FILE = lib$(LIB_NAME).so

HTML_SRC_FILES = $(wildcard $(HTML_SRC_DIR)/*.cpp)
HTML_OBJS = $(patsubst $(HTML_SRC_DIR)/%.cpp,$(HTML_OBJS_DIR)/%.o,$(HTML_SRC_FILES))

$(HTML_OBJS_DIR)/%.o: $(HTML_SRC_DIR)/%.cpp
	@test -d $(HTML_OBJS_DIR) || mkdir $(HTML_OBJS_DIR)
	@echo -n "- Compiling Html object "$@
	@$(CPP) $(CPPFLAGS) -fPIC -c -o $@ $^ && echo " : Successful" || echo " : Failed"
	
Html: $(HTML_OBJS)

HtmlClean:
	@echo "Removing Html Objects"
	@rm -f $(HTML_OBJS_DIR)/*.o
	@rm -f $(HTML_OBJS_DIR)/$(LIB_FILE)

HtmlLib: Html
	@echo -n "- Creating Html Shared Library "
	@$(CPP) $(CPPFLAGS) $(LDFLAGS) -fPIC -o $(HTML_OBJS_DIR)/$(LIB_FILE) $(HTML_OBJS) && echo " : Successful" || echo " : Failed"
