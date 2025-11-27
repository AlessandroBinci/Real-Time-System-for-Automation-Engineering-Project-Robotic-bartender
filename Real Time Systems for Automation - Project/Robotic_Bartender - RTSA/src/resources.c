/*
 * resources.c 
 * 
 * RT Assignment - Robotic Bartender
 *  Alessandro Binci – 0001189831
 *  Gianluca Vairo – 0001192707
 *  Pietro Luzzi – 0001176819
 *  
 *  DELETED THE HLP, USELESS TO OUR SIMULATION
 */

#include "resources.h"
#include "simulation.h"

int ResourceCount[N_TASKS];
/*int CurrentPriority[N_SEMAPHORES+1][N_TASKS];*/ /*not used because we deleted HLP protocol*/

/* changed because of the elimination of HLP */
RAPName_t RAPName[4] = {
	"No Shared Resources",
	"No Resource Access Protocol",
	"Non-Preemptive Critical Section Protocol",
	"Priority Inheritance Protocol"
};

/* changed because of the elimination of HLP */
void EntrySection(int semaphore, int task) {
	switch(ResourceAccessProtocol) {
	case NPP: /* Non-preemptive protocol */
		if(task>0) {
			ResourceCount[task]++;
			if(ResourceCount[task]==1)
				taskPrioritySet(0,TOP_PRIORITY);
		}
		break;
	case NOP: /* no protocol */
	case PIP: /* priority inheritance protocol */
		semTake(Semaphore[semaphore],WAIT_FOREVER);
		break;
	case NOR: /* no resources */
	default:
		break;
	}
}

/* changed because of the elimination of HLP */
void ExitSection(int semaphore, int task) {
	switch(ResourceAccessProtocol) {
	case NPP: /* Non-preemptive protocol */
		if(task>0) {
			ResourceCount[task]--;
			if(ResourceCount[task]==0)
				taskPrioritySet(0,TOP_PRIORITY+task);
		}
		break;
	case NOP: /* no protocol */
	case PIP: /* priority inheritance protocol */
		semGive(Semaphore[semaphore]);
		break;
	case NOR: /* no resources */
	default:
		break;
	}
}
