#Project name, used for naming zip
PROJECT = Final_Project_Wilson_Andrew

#Final executable name
BIN = Escape

#automatically includes all cpp files in directory
SRCEXT = cpp
SOURCES = $(wildcard *.$(SRCEXT))
OBJECTS = $(SOURCES:%.$(SRCEXT)=$(OBJ)/%.o)

OBJ=./obj

#generates dependencies automatically, adopted from https://stackoverflow.com/a/21086223
CXX = g++
CXXFLAGS = -std=c++11 -MD -MP -g
$(BIN): $(OBJECTS)
	${CXX} ${CXXFLAGS} -o $@ $^

#this puts all object files into their own directory, adpoted from https://codereview.stackexchange.com/questions/74136/makefile-that-places-object-files-into-an-alternate-directory-bin
$(OBJECTS): $(OBJ)/%.o: %.$(SRCEXT)
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c -o $@ $<

-include $(SOURCES:%.$(SRCEXT)=%.d)

#allows memory leak checking with "make valgrind"
.PHONY : valgrind
valgrind:
	@valgrind --leak-check=full --track-origins=yes ./$(BIN)

#zips all cpp hpp pdf and makefiles with "make zip"
.PHONY : zip
zip:
	zip $(PROJECT).zip *.cpp *.hpp *.pdf makefile

#makes "make clean" work on Windows too, adapted from https://stackoverflow.com/questions/2463037/calling-windows-commands-e-g-del-from-a-gnu-makefile
#ifeq ($(OS),Windows_NT)
#    RM = cmd /C del /Q /F
#else
    RM = rm -rf
#endif

#removes binary, .d (dependency), .o files
.PHONY : clean
clean:
	$(RM) $(BIN) $(BIN).exe $(OBJ)