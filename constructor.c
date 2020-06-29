#include "simulator.h"

void theConstructor(int products){

	/* Create processes */
	pid_t fits[3];
	for(int i=0;i<3;i++){
		fits[i] = fork();
		if(fits[i]<0){
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if(fits[i]==0){
			dothejob(i,products);
		}
	}

	int counter=0;
	int totalProducts = 3*products;

	while(counter<totalProducts){
		semop(sem_Fits, &leave, 1); // let the fitment get created
		semop(sem_Constr, &enter, 1); //wait for fitment to be ready
		counter++;
	}

	int status;
	for(int i=0;i<3;i++){
		while(1){
			waitpid(fits[i],&status,WUNTRACED);
			if(WIFSTOPPED(status)){
				kill(fits[i],SIGCONT);
				break;
			}
		}
	}
	exit(0);
}

void dothejob(int type,int products){

	int i;
	clock_t start;
	srand(time(NULL)^getpid());

	for(i=0;i<products;i++){
		start = clock();
		int randTime = rand() %1000000; //0-1 sec (or whatever)
		usleep(randTime);
		semop(sem_Fits, &enter, 1); // wait for factory
		shar_mem->id=getId(products);
		shar_mem->type=type;
		int clockFl=manageTime(type);
		if(manageTime(type)==1){
			timer[*timer_start] = clock();
			(*timer_start)++;			
		}

		*paintingAVG += ((double) (clock() - start)) / CLOCKS_PER_SEC;
		semop(sem_Paint,&leave,1); // let the painter beggin
		semop(sem_Fits1,&enter,1); // wait till he paints

		semop(sem_Constr, &leave, 1); // let the factory continue
	}

	raise(SIGSTOP);
	exit(0);
}

int getId(int products){

	(*randId) = rand()%9000+1000;
	return *randId;
}

int manageTime(int type){
	//ean to prostheteo dhmiourgei h auksanei megisto ksekina xrono-epestrepse 1
	//ean dhmiourgei 3ada afairese-epestrepse -1
	//alliws epestrepse 0
	switch(type){
		case 0:{
			if(*cntA==0 && *cntB!=0 && *cntC!=0){
				//newProduct
				(*cntB)--;
				(*cntC)--;
				return -1;
			}
			else{
				(*cntA)++;
				if(*cntA>*cntB && *cntA>*cntC)
					return 1;	//new clock
				return 0;
			}
			break;
		}
		case 1:{
			if(*cntB==0 && *cntA!=0 && *cntC!=0){
				//newProduct
				(*cntA)--;
				(*cntC)--;
				return -1;
			}
			else{
				(*cntB)++;
				if(*cntB>*cntA && *cntB>*cntC)
					return 1;	//newClock
				return 0;
			}
			break;
		}
		case 2:{
			if(*cntC==0 && *cntB!=0 && *cntA!=0){
				//newProduct
				(*cntB)--;
				(*cntA)--;
				return -1;
			}
			else{
				(*cntC)++;
				if(*cntC>*cntB && *cntC>*cntA)
					return 1;	//newClock
				return 0;
			}
			break;
		}
	}
}
