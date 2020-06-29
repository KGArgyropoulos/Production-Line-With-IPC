#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <time.h>

int *randId;
int *toBeEnq;
double *paintingAVG,*assemblementAVG;
int *cntA,*cntB,*cntC;
int *timer_ptr,*timer_start;
clock_t *timer;

int sem_Constr,sem_Fits,sem_Fits1,sem_Paint,sem_Cont,sem_Cont1,sem_Ass,sem_Paint1;
int sem_Cont00,sem_Cont01,sem_Cont10,sem_Cont11,sem_Cont20,sem_Cont21;
struct sembuf enter, leave;

int shm_id;

typedef struct Node{
	int id;
	int type;
}fitment;

struct Node *shar_mem;
struct Node *contrToAss[3];

void clear();

//constuctor.c
void theConstructor(int );
void dothejob(int ,int );
int getId();
int manageTime(int );

//painter.c
void thePainter(int );
void paintIt(int );

//controller.c
void theController(int );
void contrA(int );
void contrB(int );
void contrC(int );

//assembler.c
void theAssembler(int );