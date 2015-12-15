# librairies de SuiteSparse
L1 = SuiteSparse/UMFPACK/Lib/libumfpack.a
L2 = SuiteSparse/CHOLMOD/Lib/libcholmod.a 
L3 = SuiteSparse/AMD/Lib/libamd.a 
L4 = SuiteSparse/CAMD/Lib/libcamd.a  
L5 = SuiteSparse/COLAMD/Lib/libcolamd.a 
L6 = SuiteSparse/CCOLAMD/Lib/libccolamd.a 
L7 = SuiteSparse/metis-4.0/libmetis.a
L8 = SuiteSparse/SuiteSparse_config/libsuitesparseconfig.a
LIB = $(L1) $(L2) $(L3) $(L4) $(L5) $(L6) $(L7) $(L8) -lm -lblas -llapack -lgfortran 

COPT = -O3

default: main

clean: 
	rm *.o 
	rm main

main: main.o prob.o time.o  umfpack.o issym.o normvec2.o amux.o vect_vect.o CtoF.o agmg.o AGMG/SRC/dagmg.o AGMG/SRC/dagmg_mumps.o
	cc $(COPT) $^ -o $@ $(LIB)
	
umfpack.o: umfpack.c
	cc $(COPT) -c $< -o $@ -ISuiteSparse/UMFPACK/Include \
-ISuiteSparse/SuiteSparse_config  -ISuiteSparse/AMD/Include

CtoF.o: CtoF.c
	cc $(COPT) -c $< -o $@  -ldxml

AGMG/SRC/dagmg.o: AGMG/SRC/dagmg.f90
	$(F90) -c dagmg.f90

AGMG/SRC/dagmg_mumps.o: AGMG/SRC/dagmg_mumps.f90
	$(F90) -c dagmg_mumps.f90
%.o: %.c
	cc $(COPT) -c $< -o $@
