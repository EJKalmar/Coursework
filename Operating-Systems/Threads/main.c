/*
 * assign2.c
 *
 * Name: Jonathan Kalmar
 * Student Number: V00762777
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include "train.h"
#include "queue.h"
#include <semaphore.h>

/*
 * If you uncomment the following line, some debugging
 * output will be produced.
 *
 * Be sure to comment this line out again before you submit 
 */

//#define DEBUG	1

void ArriveBridge (TrainInfo *train);
void CrossBridge (TrainInfo *train);
void LeaveBridge (TrainInfo *train);

pthread_mutex_t bridge;
pthread_cond_t east_west[2];

queue* westbound;
queue* eastbound;

int occupied = 0;
int order = 0;

/*
 * This function is started for each thread created by the
 * main thread.  Each thread is given a TrainInfo structure
 * that specifies information about the train the individual 
 * thread is supposed to simulate.
 */
void * Train ( void *arguments )
{
	TrainInfo	*train = (TrainInfo *)arguments;

	/* Sleep to simulate different arrival times */
	usleep (train->length*SLEEP_MULTIPLE);

	ArriveBridge (train);
	CrossBridge  (train);
	LeaveBridge  (train); 

	/* I decided that the paramter structure would be malloc'd 
	 * in the main thread, but the individual threads are responsible
	 * for freeing the memory.
	 *
	 * This way I didn't have to keep an array of parameter pointers
	 * in the main thread.
	 */
	free (train);
	return NULL;
}

/*
 * You will need to add code to this function to ensure that
 * the trains cross the bridge in the correct order.
 */
void ArriveBridge ( TrainInfo *train )
{
	printf ("Train %2d arrives going %s\n", train->trainId, 
			(train->direction == DIRECTION_WEST ? "West" : "East"));
	pthread_mutex_lock(&bridge);
	if (train->direction == DIRECTION_WEST){
		enqueue(westbound, train->trainId);
		//Wait until the bridge is unoccupied & it's your turn to go.
		while(occupied == 1 || westbound->front->data != train->trainId){
			pthread_cond_wait(&east_west[1], &bridge);
		}
		dequeue(westbound);
	}
	else if (train->direction == DIRECTION_EAST){
		enqueue(eastbound, train->trainId);
		//Wait until the bridge is unoccupied & it's your turn to go.
		while(occupied == 1 || eastbound->front->data != train->trainId){
			pthread_cond_wait(&east_west[0], &bridge);
		}
		dequeue(eastbound);
	}
	occupied = 1;
	pthread_mutex_unlock(&bridge);
}

//simulate crossing the bridge
void CrossBridge ( TrainInfo *train )
{
	printf ("Train %2d is ON the bridge (%s)\n", train->trainId,
			(train->direction == DIRECTION_WEST ? "West" : "East"));
	fflush(stdout);
	
	/* 
	 * This sleep statement simulates the time it takes to 
	 * cross the bridge.  Longer trains take more time.
	 */
	usleep (train->length*SLEEP_MULTIPLE);
	printf ("Train %2d is OFF the bridge(%s)\n", train->trainId, 
			(train->direction == DIRECTION_WEST ? "West" : "East"));
	fflush(stdout);
}

//make the bridge available to waiting trains, with a priority on eastbound traffic
void LeaveBridge ( TrainInfo *train )
{	
	pthread_mutex_lock(&bridge);
	occupied = 0;
	if(westbound->length == 0){
		pthread_cond_broadcast(&east_west[0]);
		order = 0;
	}
	else if(eastbound->length == 0){
		pthread_cond_broadcast(&east_west[1]);
		order = 0;
	}
	else if (order == 0){
		if(train->direction == DIRECTION_EAST){
				order = 1;
		}
		pthread_cond_broadcast(&east_west[0]);
	}
	else if (order == 1){
		order = 0;
		pthread_cond_broadcast(&east_west[1]);
	}
	pthread_mutex_unlock(&bridge);
}

int main ( int argc, char *argv[] )
{
	int		trainCount = 0;
	char 		*filename = NULL;
	pthread_t	*tids;
	int		i;

		
	/* Parse the arguments */
	if ( argc < 2 )
	{
		printf ("Usage: part1 n {filename}\n\t\tn is number of trains\n");
		printf ("\t\tfilename is input file to use (optional)\n");
		exit(0);
	}
	
	if ( argc >= 2 )
	{
		trainCount = atoi(argv[1]);
	}
	if ( argc == 3 )
	{
		filename = argv[2];
	}	
	
	initTrain(filename);
	/*
	 * Since the number of trains to simulate is specified on the command
	 * line, we need to malloc space to store the thread ids of each train
	 * thread.
	 */
	tids = (pthread_t *) malloc(sizeof(pthread_t)*trainCount);

	//initialize mutex lock
	if (pthread_mutex_init(&bridge, NULL)){
		printf("Failed creation of mutex locks\n");
		return 0;
	}
	
	//create and initialize eastbound & westbound train queues
	eastbound = malloc(sizeof(queue));
	westbound = malloc(sizeof(queue));
	initialize(eastbound);
	initialize(westbound);
	
	/*
	 * Create all the train threads pass them the information about
	 * length and direction as a TrainInfo structure
	 */
	for (i=0;i<trainCount;i++)
	{
		TrainInfo *info = createTrain();
		
		printf ("Train %2d headed %s length is %d\n", info->trainId,
			(info->direction == DIRECTION_WEST ? "West" : "East"),
			info->length );

		if ( pthread_create (&tids[i],0, Train, (void *)info) != 0 )
		{
			printf ("Failed creation of Train.\n");
			exit(0);
		}
	}

	/*
	 * This code waits for all train threads to terminate
	 */
	for (i=0;i<trainCount;i++)
	{
		pthread_join (tids[i], NULL);
	}
	
	free(tids);
	return 0;
}

