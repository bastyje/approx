aprox: main.o splines.o points.o aproksymator_na_bazie.o src/gaus/libge.a
	$(CC) -o bin/aprox  bin/obj/main.o bin/obj/splines.o bin/obj/points.o bin/obj/lst_sqrs_approx.o -L src/gaus -l ge

intrp: main.o splines.o points.o interpolator.o src/gaus/libge.a
	$(CC) -o bin/intrp  bin/obj/main.o bin/obj/splines.o bin/obj/points.o bin/obj/interpolator.o -L src/gaus -l ge

prosta: main.o splines.o points.o prosta.o
	$(CC) -o bin/prosta  bin/obj/main.o bin/obj/splines.o bin/obj/points.o bin/obj/prosta.o	

gen:
	$(CC) -o bin/gen src/gen/gen.c

main.o: src/points.h src/splines.h src/makespl.h
	$(CC) -I src -c src/main.c -o bin/obj/main.o

splines.o: src/splines.h
	$(CC) -I src -c src/splines.c -o bin/obj/splines.o

points.o: src/points.h
	$(CC) -I src -c src/points.c -o bin/obj/points.o

lst_sqrs_approx.o: src/makespl.h src/points.h src/gaus/piv_ge_solver.h
	$(CC) -I src/gaus -I src -c src/lst_sqrs_approx.c -o bin/obj/lst_sqrs_approx.o

interpolator.o: src/makespl.h src/points.h src/gaus/piv_ge_solver.h
	$(CC) -I src/gaus  -I src -c src/interpolator.c -o bin/obj/interpolator.o

.PHONY: clean

clean:
	-rm bin/obj/*.o bin/aprox bin/intrp bin/prosta bin/gen
