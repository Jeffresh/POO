#	$Id: Make_check.mk 283 2015-06-25 19:51:16Z gerardo $
#

CXX         := clang++
RTTIFLAG    := -fno-rtti
CXXFLAGS    := $(shell llvm-config --cxxflags) $(RTTIFLAG) 
LDFLAGS     := # -static
LLVMLDFLAGS := $(shell llvm-config --ldflags --system-libs --libs) $(LDFLAGS)

SOURCES   = fecha_check.cpp cadena_check.cpp
OBJECTS   = $(SOURCES:.cpp=.o)
EXES      = $(OBJECTS:.o=)
CLANGLIBS = -lclangFrontend \
	-lclangSerialization \
	-lclangDriver \
	-lclangTooling \
	-lclangParse \
	-lclangSema \
	-lclangAnalysis \
	-lclangEdit \
	-lclangAST \
	-lclangASTMatchers \
	-lclangLex \
	-lclangBasic \
	-lclangRewrite

.PHONY: clean all
all: $(EXES)

fecha_check: fecha_check.o
	$(CXX) -o $@ $< $(CLANGLIBS) $(LLVMLDFLAGS)

cadena_check: cadena_check.o
	$(CXX) -o $@ $< $(CLANGLIBS) $(LLVMLDFLAGS)

clean:
	${RM} $(EXES) $(OBJECTS)

