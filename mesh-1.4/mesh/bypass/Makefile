-include ../Makefile.config
-include Makefile.config

BYPASS_DIR=../../bypass
BYPASS=BYPASS_LIBRARY_DIR=${BYPASS_DIR}/lib ${BYPASS_DIR}/src/bypass
BYPASSFLAGS=

CXXFLAGS=${CXXDEFS} -I${BYPASS_DIR}/src -D_REENTRANT -DUSE_PTHREADS

MAKELIBFLAGS=-L${BYPASS_DIR}/src ${XLINKER} -Bdynamic -lpthread ${EXTRALIBS} -shared

all: mesh_agent.so

%_agent.C: %.bypass
	${BYPASS} ${BYPASSFLAGS} -agent $<

%.o: %.C
	${CXX} ${CXXFLAGS} $< -c -o $@

%.so: %.o
	${CXX} $< ${MAKELIBFLAGS} -lbypass -o $@

install: all
	cp mesh_agent.so $(PREFIX)lib
	chmod 0755 $(PREFIX)lib/mesh_agent.so
	chown root:root $(PREFIX)lib/mesh_agent.so

clean:
	rm -rf core *_shadow* *_agent* *.o *.so *.h ii_files

distclean: clean
	rm -f Makefile.config

.PHONY = all install clean distclean

