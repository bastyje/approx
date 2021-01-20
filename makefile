OBJDIR=bin/obj/
TARGETDIR=bin/
SRCDIR=src/

$(TARGETDIR)aprox: $(OBJDIR)main.o $(OBJDIR)splines.o $(OBJDIR)points.o $(OBJDIR)lst_sqrs_approx.o $(SRCDIR)gaus/libge.a
	$(CC) -o $@  $^ -L src/gaus -l ge 

$(TARGETDIR)aprox_baza: $(OBJDIR)main.o $(OBJDIR)splines.o $(OBJDIR)points.o $(OBJDIR)aproksymator_na_bazie.o $(SRCDIR)gaus/libge.a
	$(CC) -o $@  $^ -L src/gaus -l ge 

$(TARGETDIR)intrp: $(OBJDIR)main.o $(OBJDIR)splines.o $(OBJDIR)points.o $(OBJDIR)interpolator.o $(SRCDIR)gaus/libge.a
	$(CC) -o $@  $^ -L src/gaus -l ge 

$(TARGETDIR)prosta: $(OBJDIR)main.o $(OBJDIR)splines.o $(OBJDIR)points.o $(OBJDIR)prosta.o
	$(CC) -o $@  $^

$(TARGETDIR)gen: $(SRCDIR)gen/gen.c
	$(CC) -o $@  $^ -lm

$(OBJDIR)main.o: $(SRCDIR)points.h $(SRCDIR)splines.h $(SRCDIR)makespl.h
	$(CC) -I $(SRCDIR) -c $(SRCDIR)main.c -o $@

$(OBJDIR)splines.o: $(SRCDIR)splines.h
	$(CC) -I $(SRCDIR) -c $(SRCDIR)splines.c -o $@

$(OBJDIR)points.o: $(SRCDIR)points.h
	$(CC) -I $(SRCDIR) -c $(SRCDIR)points.c -o $@

$(OBJDIR)lst_sqrs_approx.o: $(SRCDIR)makespl.h $(SRCDIR)points.h $(SRCDIR)gaus/piv_ge_solver.h
	$(CC) -I $(SRCDIR)gaus -I $(SRCDIR) -c $(SRCDIR)lst_sqrs_approx.c -o $@

$(OBJDIR)interpolator.o: $(SRCDIR)makespl.h $(SRCDIR)points.h $(SRCDIR)gaus/piv_ge_solver.h
	$(CC) -I $(SRCDIR)gaus  -I $(SRCDIR) -c $(SRCDIR)interpolator.c -o $@

$(OBJDIR)aproksymator_na_bazie.o: $(SRCDIR)makespl.h $(SRCDIR)points.h $(SRCDIR)gaus/piv_ge_solver.h
	$(CC) -I $(SRCDIR)gaus -I $(SRCDIR) -c $(SRCDIR)aproksymator_na_bazie.c -o $@

$(OBJDIR)prosta.o: $(SRCDIR)makespl.h $(SRCDIR)points.h
	$(CC) -I $(SRCDIR)gaus -I $(SRCDIR) -c $(SRCDIR)prosta.c -o $@

.PHONY: clean

clean:
	-rm $(OBJDIR)*.o $(TARGETDIR)aprox $(TARGETDIR)intrp $(TARGETDIR)prosta $(TARGETDIR)gen $(TARGETDIR)aprox_baza
