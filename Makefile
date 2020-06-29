all: simulator

simulator: simulator.o constructor.o painter.o controller.o assembler.o
	gcc simulator.c constructor.c painter.c controller.c assembler.c -o simulator -lpthread

simulator.o: simulator.c
	gcc -c simulator.c

constructor.o: constructor.c
	gcc -c constructor.c

painter.o: painter.c
	gcc -c painter.c

controller.o: controller.c
	gcc -c controller.c

assembler.o: assembler.c
	gcc -c assembler.c

clean:
	rm -rf *o simulator