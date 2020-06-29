#include "simulator.h"

int main(int argc,char **argv){

	if(argc==1){
		printf("Please, give the number of the products you want to create\n");
		return -1;
	}
	int products = atoi(argv[1]);
	if(products==0 || products>9000){
		printf("Wrong input // up to 9000 products\n");
		return -1;
	}
	int i;

	/* Create shared memory structures */
	//struct fitment
	if((shm_id = shmget(IPC_PRIVATE, sizeof(fitment), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((shar_mem = (fitment *)shmat(shm_id, 0, 0)) == (fitment *) -1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}
	//id
	if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((shar_mem->id = (uintptr_t)shmat(shm_id, 0, 0)) == -1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}
	//type
	if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((shar_mem->type = (uintptr_t)shmat(shm_id, 0, 0)) == -1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}

	//id counter
	if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((randId = (int *)shmat(shm_id, 0, 0)) == (int *)-1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}

	//(3 fitments of different type:controller->assembler)
	for(i=0;i<3;i++){
		if((shm_id = shmget(IPC_PRIVATE, sizeof(fitment ), IPC_CREAT|0600)) == -1){
			perror("shmget()");
			exit(EXIT_FAILURE);
		}
		if((contrToAss[i] = (fitment *)shmat(shm_id, 0, 0)) == (fitment *)-1){
			perror("shmat()");
			exit(EXIT_FAILURE);
		}
		if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
			perror("shmget()");
			exit(EXIT_FAILURE);
		}
		if((contrToAss[i]->id = (uintptr_t)shmat(shm_id, 0, 0)) == -1){
			perror("shmat()");
			exit(EXIT_FAILURE);
		}
		if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
			perror("shmget()");
			exit(EXIT_FAILURE);
		}
		if((contrToAss[i]->type = (uintptr_t)shmat(shm_id, 0, 0)) == -1){
			perror("shmat()");
			exit(EXIT_FAILURE);
		}
	}

	//flag to be Enqueued
	if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((toBeEnq = (int *)shmat(shm_id, 0, 0)) == (int *)-1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}
	*toBeEnq=1;

	//painting avg wait
	if((shm_id = shmget(IPC_PRIVATE, sizeof(double), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((paintingAVG = (double *)shmat(shm_id, 0, 0)) == (double *)-1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}
	*paintingAVG=0.0;

	//assemblement avg wait
	if((shm_id = shmget(IPC_PRIVATE, sizeof(double), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((assemblementAVG = (double *)shmat(shm_id, 0, 0)) == (double *)-1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}
	*assemblementAVG=0.0;

	if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((cntA = (int *)shmat(shm_id, 0, 0)) == (int *)-1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}
	*cntA=0;
	if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((cntB = (int *)shmat(shm_id, 0, 0)) == (int *)-1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}
	*cntB=0;
	if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((cntC = (int *)shmat(shm_id, 0, 0)) == (int *)-1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}
	*cntC=0;

	if((shm_id = shmget(IPC_PRIVATE, 2*products*sizeof(clock_t), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((timer = (clock_t *)shmat(shm_id, 0, 0)) == (clock_t *)-1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}

	if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((timer_ptr = (int *)shmat(shm_id, 0, 0)) == (int *)-1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}
	*timer_ptr=0;

	if((shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1){
		perror("shmget()");
		exit(EXIT_FAILURE);
	}
	if((timer_start = (int *)shmat(shm_id, 0, 0)) == (int *)-1){
		perror("shmat()");
		exit(EXIT_FAILURE);
	}
	*timer_start=0;



	/* Create semaphors */
	if((sem_Constr = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}

	if((sem_Fits = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}	

	if((sem_Fits1 = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}

	if((sem_Paint = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}
	if((sem_Cont = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}
	if((sem_Paint1 = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}
	if((sem_Cont00 = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}
	if((sem_Cont01 = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}
	if((sem_Cont10 = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}
	if((sem_Cont11 = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}
	if((sem_Cont20 = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}
	if((sem_Cont21 = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}
	if((sem_Cont1 = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}
	if((sem_Ass = semget(IPC_PRIVATE, 1, IPC_CREAT|0644)) == -1){
		perror("semget()");
		exit(EXIT_FAILURE);
	}

	unsigned short marker[1];
	marker[0] = 0;

	/* All sem's to 0 */
	semctl(sem_Constr, 1, SETALL, marker);
	semctl(sem_Fits, 1, SETALL, marker);
	semctl(sem_Fits1, 1, SETALL, marker);
	semctl(sem_Paint, 1, SETALL, marker);
	semctl(sem_Paint1, 1, SETALL, marker);
	semctl(sem_Cont, 1, SETALL, marker);
	semctl(sem_Cont1, 1, SETALL, marker);
	semctl(sem_Ass, 1, SETALL, marker);
	semctl(sem_Cont00, 1, SETALL, marker);
	semctl(sem_Cont01, 1, SETALL, marker);
	semctl(sem_Cont10, 1, SETALL, marker);
	semctl(sem_Cont11, 1, SETALL, marker);
	semctl(sem_Cont20, 1, SETALL, marker);
	semctl(sem_Cont21, 1, SETALL, marker);	

	/* Structs for semaphor */
	enter.sem_num = leave.sem_num = 0;
	enter.sem_flg = leave.sem_flg = SEM_UNDO;
	enter.sem_op = -1;              /* DOWN-Operation */
	leave.sem_op = 1;               /* UP-Operation */

	pid_t pid[4];
	for(i=0;i<4;i++){
		pid[i] = fork();
		if(pid[i] < 0){
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if(pid[i] == 0){
			switch(i){
				case 0:{
					theConstructor(products);
					break;
				}
				case 1:{
					thePainter(products);
					break;
				}
				case 2:{
					theController(products);
					break;
				}
				case 3:{
					theAssembler(products);
					break;
				}
			}
		}
	}

	for(i=0;i<4;i++)
		waitpid(pid[i],NULL,0);

	double pAVG = (double)(*paintingAVG/(3*products));
	printf("Average delay for the paint shop: %lf\n",pAVG);
	double aAVG = (double)(*assemblementAVG/products);
	printf("Average delay between the first fitment and the final product : %lf\n",aAVG);

	clear();

	return 0;
}

void clear(){ //destroy semaphores and shared memory

	semctl(sem_Fits, 0, IPC_RMID);
	semctl(sem_Fits1, 0, IPC_RMID);
	semctl(sem_Constr, 0, IPC_RMID);
	semctl(sem_Paint, 0, IPC_RMID);
	semctl(sem_Paint1, 0, IPC_RMID);
	semctl(sem_Cont, 0, IPC_RMID);
	semctl(sem_Cont1,0,IPC_RMID);
	semctl(sem_Ass,0,IPC_RMID);
	semctl(sem_Cont00, 0, IPC_RMID);
	semctl(sem_Cont01, 0, IPC_RMID);
	semctl(sem_Cont10, 0, IPC_RMID);
	semctl(sem_Cont11, 0, IPC_RMID);
	semctl(sem_Cont20, 0, IPC_RMID);
	semctl(sem_Cont21, 0, IPC_RMID);

	shmdt(contrToAss);
	shmdt(toBeEnq);
	shmdt(shar_mem);
	shmdt(randId);
	shmdt(paintingAVG);
	shmdt(assemblementAVG);
	shmdt(cntA);
	shmdt(cntB);
	shmdt(cntC);
	shmdt(timer_ptr);
	shmdt(timer_start);
	shmdt(timer);

	if (shmctl(shm_id,IPC_RMID,0) == -1)
		perror("shmctl");
}