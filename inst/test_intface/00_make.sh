#!/bin/sh

CC=`${R_HOME}/bin/R CMD config CC`
FC=`${R_HOME}/bin/R CMD config FC`
FLIBS=`${R_HOME}/bin/R CMD config FLIBS`
LDFLAGS=`${R_HOME}/bin/R CMD config LDFLAGS`

${CC} -c *.c
${FC} -c *.f
${CC} -o xintface *.o ${LDFLAGS} ${FLIBS}

./xintface
rm -f *.o xintface > /dev/null
