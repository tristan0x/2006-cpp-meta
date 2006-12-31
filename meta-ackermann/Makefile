## File    Makefile
## Made by Tristan Carel
## Mail    <tristan.carel@gmail.com>
##
## Started on  Thu Nov 24 05:39:49 2005 Tristan Carel
## Last update Thu Nov 24 21:43:26 2005 ken
##
## Copyright (C) 2005 Tristan Carel
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
##

CXX	= g++
CXXFLAGS= -Wall -pipe -ftemplate-depth-100000

SRC=						\
ackermann-meta.hcc				\
ackermann-naive.cc				\
ackermann-naive.hh

# tarball basename
ARCHIVE=meta-ackermann

# Extra files to add in the tarball
EXTRA_DIST = Makefile README AUTHORS
# binary
OUT=acker

# ---------------------------------------------------------------------------

# the C++ main code used to compile the metaprog version
META_MAIN =								\
\#include <iostream>\n							\
typedef unsigned long long ull;\n					\
\#include \"ackermann-meta.hcc\"\n					\
int	main()								\
{									\
  std::cout << ackermann_meta<M_VALUE, N_VALUE>::value << std::endl;	\
}

# the C++ main code used to compile the classical method.
NAIVE_MAIN =								\
\#include <iostream>\n							\
\#include <cstdlib>\n							\
typedef unsigned long long ull;\n					\
\#include \"ackermann-naive.hh\"\n					\
int	main(int argc, char **argv)					\
{									\
  ackermann_naive naive;						\
									\
  if (argc != 3)							\
    {									\
      std::cerr << \"Usage: \" << argv[0] << \" <M> <N>\" << std::endl;	\
      return 1;								\
    }									\
  std::cout << naive(std::atoi(argv[1]), std::atoi(argv[2])) << std::endl;	\
}

# ---------------------------------------------------------------------------
OBJ		= $(patsubst %.cc, %.o, $(filter %.cc, $(SRC)))
ACK_PARAMS	= -DM_VALUE=$M -DN_VALUE=$N

all: $(OUT)-$M-$N-meta $(OUT)-naive check

$(OUT)-$M-$N-meta: ackermann-meta.hcc
	@echo Compiling Metaprogramming version;		\
	(time							\
	/bin/echo -e "$(META_MAIN)" |				\
	$(CXX) $(ACK_PARAMS) $(CXXFLAGS) -x c++ -o $@ -)	\
	2>$@.stats && ./$@ >$@.out

$(OUT)-naive: ackermann-naive.o
	@/bin/echo -e "$(NAIVE_MAIN)" |				\
	$(CXX) $(CXXFLAGS) ackermann-naive.o -x c++ -o $@ -;	\
	echo "Executing Naive version";				\
	(time ./$@ $M $N) >$@.out 2>$@.stats

# interactively ask input parameters of ackerman
ask:
	@echo -n "enter M value : " ; read M ;	\
	echo -n "enter N value : " ; read N ;	\
	$(MAKE) M=$$M N=$$N all


check:
	@diff $(OUT)-naive.out $(OUT)-$M-$N-meta.out;			 \
	echo -n "Naive version	 : " ;					 \
	cat $(OUT)-naive.stats
	echo -n "MetaProg version : " ;					 \
	cat $(OUT)-$M-$N-meta.stats

# ---------------------------------------------------------------------------
ifeq ($(filter ask dist clean distclean,$(MAKECMDGOALS)),)
ifndef M
$(error "M's undefined!")
endif
ifndef N
$(error "N's undefined!")
endif
endif

# ---------------------------------------------------------------------------
.cc.o:
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -DM_VALUE=$M -DN_VALUE=$N

clean:
	$(RM) $(OBJ)

distclean: clean
	for bin in `find . -executable -type f`; do	\
		$(RM) "$$bin.out" ; \
		$(RM) "$$bin.stats" ; \
		$(RM) "$$bin" ; \
	done

dist: distclean
	${RM} -r ${ARCHIVE}				&&	\
	mkdir ${ARCHIVE}				&&	\
	cp -r   ${SRC} ${EXTRA_DIST} ${ARCHIVE}		&&	\
	tar --bzip2 -cf ${ARCHIVE}.tar.bz2 ${ARCHIVE}	&&	\
	$(RM) -r ${ARCHIVE}
