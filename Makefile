#Shireen Bahadur                                                                               
#ssb160430@utdalas.edu                                                                         
#CS 3377.502                  

CXX = g++
CXXFLAGS = -Wno-write-strings
CPPFLAGS = -Wall -g -I /scratch/perkins/include
LDFLAGS = -L /scratch/perkins/lib
LDLIBS = -lcdk -lcurses


#                                                                                                            
# PROJECTNAME is a descriptive name used for the backup target                                               
# This should not contain spaces or special characters                                                       

EXECFILE = cdkprog6

OBJS = prog6.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
