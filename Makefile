aprox: main.o splines.o points.o aproksymator_na_bazie.o src/gaus/libge.a
	$(CC) -o aprox  main.o splines.o points.o aproksymator_na_bazie.o -L src/gaus -l ge

intrp: main.o splines.o points.o interpolator.o src/gaus/libge.a
	$(CC) -o intrp  main.o splines.o points.o interpolator.o -L src/gaus -l ge

prosta: main.o splines.o points.o prosta.o
	$(CC) -o prosta  main.o splines.o points.o prosta.o	

main.o: src/points.h src/splines.h src/makespl.h
	$(CC) -I src -c src/main.c

splines.o: src/splines.h
	$(CC) -I src -c src/splines.c

points.o: src/points.h
	$(CC) -I src -c src/points.c

aproksymator_na_bazie.o: src/makespl.h src/points.h src/gaus/piv_ge_solver.h
	$(CC) -I src/gaus -I src -c src/aproksymator_na_bazie.c

interpolator.o: src/makespl.h src/points.h src/gaus/piv_ge_solver.h
	$(CC) -I src/gaus  -I src -c src/interpolator.c

.PHONY: clean

clean:
	-rm *.o aprox intrp prosta
