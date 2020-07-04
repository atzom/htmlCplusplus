#
# Makefile for the Html C++ Examples
#

HTML_WORK_DIR = $(shell dirname `pwd`)

include ../Makefile

EXAMPLES_BIN = bin

clean: HtmlClean
	@echo "Removing Examples"
	@rm -f $(EXAMPLES_BIN)/example*

example1: Html
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $(HTML_OBJS) $@.cpp && echo " : Successful" || echo " : Failed"

example2: Html
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $(HTML_OBJS) $@.cpp && echo " : Successful" || echo " : Failed"

example3: Html
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $(HTML_OBJS) $@.cpp && echo " : Successful" || echo " : Failed"

example4: Html
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $(HTML_OBJS) $@.cpp && echo " : Successful" || echo " : Failed"

example5: Html
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $(HTML_OBJS) $@.cpp && echo " : Successful" || echo " : Failed"

example6: Html
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $(HTML_OBJS) $@.cpp && echo " : Successful" || echo " : Failed"	

example7: Html
	@test -d $(EXAMPLES_BIN) || mkdir $(EXAMPLES_BIN)
	@echo -n "- Compiling Example "$@
	@$(CPP) $(CPPFLAGS) -o $(EXAMPLES_BIN)/$@ $(HTML_OBJS) $@.cpp && echo " : Successful" || echo " : Failed"	
	

examples: example1 example2 example3 example4 example5 example6 example7