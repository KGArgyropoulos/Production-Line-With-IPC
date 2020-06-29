#include "simulator.h"

void theController(int products){

	/* Create processes */
	//process to control type A fitments
	pid_t typeA = fork();
	if(typeA<0){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(typeA==0)
		contrA(products);

	//process to control type B fitments
	pid_t typeB = fork();
	if(typeB<0){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(typeB==0)
		contrB(products);

	//process to control type C fitments
	pid_t typeC = fork();
	if(typeC<0){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(typeC==0)
		contrC(products);	

	int total_products=3*products;
	int counterA=0;
	int counterB=0;
	int counterC=0;
	
	for(int i=0;i<total_products;i++){
		semop(sem_Cont, &enter, 1); // wait for new fitment
		fitment fit;
		fit.type = shar_mem->type;

		switch(fit.type){
			case 0:{
				semop(sem_Cont00,&leave,1);
				semop(sem_Cont01,&enter,1);
				counterA++;
				break;
			}
			case 1:{
				semop(sem_Cont10,&leave,1);
				semop(sem_Cont11,&enter,1);
				counterB++;
				break;
			}
			case 2:{
				semop(sem_Cont20,&leave,1);
				semop(sem_Cont21,&enter,1);
				counterC++;
				break;
			}
		}

		if(counterA>0 && counterB>0 && counterC>0){
			*toBeEnq=0;
			semop(sem_Cont00,&leave,1);
			semop(sem_Cont01,&enter,1);
			semop(sem_Cont10,&leave,1);
			semop(sem_Cont11,&enter,1);
			semop(sem_Cont20,&leave,1);
			semop(sem_Cont21,&enter,1);
			*toBeEnq=1;
			counterA--;
			counterB--;
			counterC--;
			//send to the assembler**
			semop(sem_Ass,&leave,1); //let the assembler start
			semop(sem_Cont1,&enter,1); //wait for him to finish
		}

		semop(sem_Paint1, &leave, 1); // let the painter continue
	}

	int status;
	while(1){
		waitpid(typeA,&status,WUNTRACED);
		if(WIFSTOPPED(status)){
			kill(typeA,SIGCONT);
			break;
		}
	}
	while(1){
		waitpid(typeB,&status,WUNTRACED);
		if(WIFSTOPPED(status)){
			kill(typeB,SIGCONT);
			break;
		}
	}
	while(1){
		waitpid(typeC,&status,WUNTRACED);
		if(WIFSTOPPED(status)){
			kill(typeC,SIGCONT);
			break;
		}
	}
	exit(0);
}

void contrA(int products){

	//create private array
	fitment fits[products];
	int index=0,checked=0;
	for(int i=0;i<2*products;i++){
		semop(sem_Cont00,&enter,1);
		if(*toBeEnq){
			fits[index].id = shar_mem->id;
			fits[index].type = shar_mem->type;
			index++;
		}
		else{
			contrToAss[0]->id = fits[checked].id;
			contrToAss[0]->type = fits[checked].type;
			checked++;
			usleep(20000); //0.02 second for type 1 fitments
		}
		semop(sem_Cont01,&leave,1);
	}

	raise(SIGSTOP);
	exit(0);
}

void contrB(int products){

	//create private array
	fitment fits[products];
	int index=0,checked=0;
	for(int i=0;i<2*products;i++){
		semop(sem_Cont10,&enter,1);
		if(*toBeEnq){
			fits[index].id = shar_mem->id;
			fits[index].type = shar_mem->type;
			index++;
		}
		else{
			contrToAss[1]->id = fits[checked].id;
			contrToAss[1]->type = fits[checked].type;
			checked++;
			usleep(40000);  //0.04 seconds for type 2 fitments
		}
		semop(sem_Cont11,&leave,1);
	}

	raise(SIGSTOP);
	exit(0);
}

void contrC(int products){

	fitment fits[products];
	int index=0,checked=0;
	for(int i=0;i<2*products;i++){
		semop(sem_Cont20,&enter,1);
		if(*toBeEnq){
			fits[index].id = shar_mem->id;
			fits[index].type = shar_mem->type;
			index++;
		}
		else{
			contrToAss[2]->id = fits[checked].id;
			contrToAss[2]->type = fits[checked].type;
			checked++;
			usleep(30000);  //0.03 second for type 3 fitments
		}
		semop(sem_Cont21,&leave,1);
	}

	raise(SIGSTOP);
	exit(0);
}