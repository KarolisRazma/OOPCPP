RM = del
CC = g++
TARGET = game.exe
MAIN_CPP = main.cpp
MAIN_OBJ = main.o
VIDEOGAME_CPP = VideoGame.cpp
VIDEOGAME_OBJ = VideoGame.o
CHECK_CPP = Check.cpp
CHECK_OBJ = Check.o
TEST_TARGET = test.exe
TEST_CPP = test.cpp 
TEST_OBJ = test.o
TEST_OUT = test_out.txt

DOCS = doc
DOCS_HTML = doc\html
DOCS_HTML_SEARCH = doc\html\search

FLAGS = -std=c++11 -Wall
DOXYGEN = doxygen Doxyfile

all : $(TARGET) doc build_test run_test 

rebuild : clean all

$(TARGET) : $(MAIN_OBJ) $(VIDEOGAME_OBJ) $(CHECK_OBJ)
	$(CC) $(FLAGS) $(MAIN_OBJ) $(VIDEOGAME_OBJ) $(CHECK_OBJ) -o $(TARGET)

$(MAIN_OBJ) : $(MAIN_CPP)
	$(CC) $(FLAGS) -c $(MAIN_CPP) -o $(MAIN_OBJ)

$(VIDEOGAME_OBJ) : $(VIDEOGAME_CPP) 
	$(CC) $(FLAGS) -c $(VIDEOGAME_CPP) -o $(VIDEOGAME_OBJ)

$(CHECK_OBJ) : $(CHECK_CPP) 
	$(CC) $(FLAGS) -c $(CHECK_CPP) -o $(CHECK_OBJ)

$(TEST_OBJ) : $(TEST_CPP)
	$(CC) $(FLAGS) -c  $(TEST_CPP) -o $(TEST_OBJ)

build_test : $(TEST_OBJ) $(VIDEOGAME_OBJ) $(CHECK_OBJ)
	$(CC) $(FLAGS) $(TEST_OBJ) $(VIDEOGAME_OBJ) $(CHECK_OBJ) -o $(TEST_TARGET)

run_test: $(TEST_TARGET)
	$(TEST_TARGET) >> $(TEST_OUT) && $(TEST_TARGET)

deploy: 
	git add --all
	git commit -m "Commit by makefile, into new repository for correct usage of github"
	git push -f origin main

doc :
	$(DOXYGEN)

clean :
	$(RM) $(MAIN_OBJ)
	$(RM) $(VIDEOGAME_OBJ)
	$(RM) $(CHECK_OBJ)
	$(RM) $(TEST_OBJ)
	$(RM) $(TARGET)
	$(RM) $(TEST_TARGET)
	$(RM) $(TEST_OUT)
	$(RM) $(DOCS)
	$(RM) $(DOCS_HTML)
	$(RM) $(DOCS_HTML_SEARCH)

.PHONY : all doc rebuild build_test run_test clean deploy 