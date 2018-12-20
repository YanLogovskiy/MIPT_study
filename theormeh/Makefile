SOURSES= main_euler_dissip.c math_func.c diff_eq_models.c makeSimulation.c
HEADERS= math_func.h diff_eq_models.h makeSimulation.h

all:	simulator

simulator:	$(SOURSES) $(HEADERS)
	gcc	$(SOURSES) $(HEADERS) -o simulator -lm
