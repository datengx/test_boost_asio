TARGETS=test_unique_pointer test_shared_pointer test_regexp test_ptree lexical concurrent

CC=gcc
CCOPTS=-Wall -Wextra -std=gnu++14
INC=

UNIQUE_POINTER_SOURCES_FILES=test_unique_pointer.cpp
REGEXP_SOURCE_FILES=test_regexp.cpp
SHARED_POINTER_SOURCES_FILES=test_shared_pointer.cpp
PTREE_SOURCES_FILES=test_ptree.cpp
LEXICAL_SOURCES_FILES=lexical.cpp
CONCURRENT_SOURCES_FILES=concurrent.cpp

DEP_OBJECT=
LIBS=-lstdc++ \
      $(shell pkg-config --libs boost)

all: rm_directory make_directory $(TARGETS)

make_directory:
	mkdir bin

rm_directory:
	rm -rf ./bin

clean: $(rm_directory)

# lexical:
# 	$(CC) $(CCOPTS) $(INC) -o lexical $(LEXICAL_SOURCES_FILES) $(DEP_OBJECT) $(LIBS)
# 	mv lexical ./bin
#
# test_ptree:
# 	$(CC) $(CCOPTS) $(INC) -o test_ptree $(PTREE_SOURCES_FILES) $(DEP_OBJECT) $(LIBS)
# 	mv test_ptree ./bin
#
# test_unique_pointer:
# 	$(CC) $(CCOPTS) $(INC) -o test_unique_pointer $(UNIQUE_POINTER_SOURCES_FILES) $(DEP_OBJECT) $(LIBS)
# 	mv test_unique_pointer ./bin
# test_regexp:
# 	$(CC) $(CCOPTS) $(INC) -o test_regexp $(REGEXP_SOURCE_FILES) $(DEP_OBJECT) $(LIBS)
# 	mv test_regexp ./bin
# test_shared_pointer:
# 	$(CC) $(CCOPTS) $(INC) -o test_shared_pointer $(SHARED_POINTER_SOURCES_FILES) $(DEP_OBJECT) $(LIBS)
# 	mv test_shared_pointer ./bin

# generic build rules
%: %.cpp
	# rm ./$@
	$(CC) $(CCOPTS) $(INC) -o $@ $< $(DEP_OBJECT) $(LIBS)
	mv $@ ./bin
