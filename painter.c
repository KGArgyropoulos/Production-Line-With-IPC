#include "simulator.h"

void thePainter(int products){

	int total_products=3*products;
	
	for(int i=0;i<total_products;i++){
		semop(sem_Paint, &enter, 1); // wait for new fitment
		fitment fit;
		fit.id = shar_mem->id;
		fit.type = shar_mem->type;
		paintIt(fit.type);

		semop(sem_Cont,&leave,1); // let the controller beggin
		semop(sem_Paint1,&enter,1); // wait till he completes

		semop(sem_Fits1, &leave, 1); // let the fitment continue
	}
	exit(0);
}

void paintIt(int type){

	switch (type){
		case 0:{
			usleep(10000); //0.01 second for type 1 fitments
			break;
		}
		case 1:{
			usleep(20000);  //0.02 seconds for type 2 fitments
			break;
		}
		case 2:{
			usleep(15000);  //0.015 second for type 3 fitments
			break;
		}
	}
}