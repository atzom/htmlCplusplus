#
# Makefile for the Html C++ Examples
#

HTML_WORK_DIR = $(shell dirname `pwd`)

include ../Makefile

EXAMPLES_BIN = bin

clean: HtmlClean
	@echo "Removing Examples"
	@rm -f $(EXAMPLES_BIN)/example*

example1: HtmlLib
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $@.cpp -L$(HTML_OBJS_DIR) -lhtmlCplusplus && echo " : Successful" || echo " : Failed"	

example2: HtmlLib
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $@.cpp -L$(HTML_OBJS_DIR) -lhtmlCplusplus && echo " : Successful" || echo " : Failed"	

example3: HtmlLib
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $@.cpp -L$(HTML_OBJS_DIR) -lhtmlCplusplus && echo " : Successful" || echo " : Failed"	

example4: HtmlLib
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $@.cpp -L$(HTML_OBJS_DIR) -lhtmlCplusplus && echo " : Successful" || echo " : Failed"	

example5: HtmlLib
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $@.cpp -L$(HTML_OBJS_DIR) -lhtmlCplusplus && echo " : Successful" || echo " : Failed"	

example6: HtmlLib
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $@.cpp -L$(HTML_OBJS_DIR) -lhtmlCplusplus && echo " : Successful" || echo " : Failed"	

example7: HtmlLib
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $@.cpp -L$(HTML_OBJS_DIR) -lhtmlCplusplus && echo " : Successful" || echo " : Failed"

example8: HtmlLib
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $@.cpp -L$(HTML_OBJS_DIR) -lhtmlCplusplus && echo " : Successful" || echo " : Failed"	
	

examples: HtmlLib example1 example2 example3 example4 example5 example6 example7 example8
