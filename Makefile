##----------------------------------------------------------------------------
# Created with genmake.pl v1.1 on Sat Oct 10 11:11:54 2015
# genmake.pl home: http://muquit.com/muquit/software/
# Copryright: GNU GPL (http://www.gnu.org/copyleft/gpl.html)
##----------------------------------------------------------------------------
rm=/bin/rm -f
CXX= g++
DEFS=  
PROGNAME= main
INCLUDES=  -I. -I /usr/include/
LIBS= -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

WARN=-Wall -Wextra
OPT=-o2
STD=-std=c++0x
DEFINES= $(INCLUDES) $(DEFS) -DSYS_UNIX=1
CXXFLAGS= -g $(DEFINES) $(OPT) $(STD) $(WARN)

SRCS = main.cpp utilities.cpp 

OBJS = main.o utilities.o 

.c.o:
	$(rm) $@
	$(CXX) $(CXXFLAGS) -c $*.c

all: $(PROGNAME)

$(PROGNAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

clean:
	$(rm) $(OBJS) $(PROGNAME) core *~
