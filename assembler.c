#include "simulator.h"

void theAssembler(int products){

	for(int i=0;i<products;i++){
		semop(sem_Ass,&enter,1);
		char newId[13];
		sprintf(newId,"%d%d%d",contrToAss[0]->id,contrToAss[1]->id,contrToAss[2]->id);
		usleep(100000); //0.1 second for the assemblement
		printf("Created %s\n",newId);
		*assemblementAVG += ((double) (clock() - timer[*timer_ptr])) / CLOCKS_PER_SEC;
		(*timer_ptr)++;

		semop(sem_Cont1,&leave,1);
	}

	exit(0);
}