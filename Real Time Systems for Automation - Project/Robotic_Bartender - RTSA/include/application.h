/*
 * applications.h
 *
 *  RT Assignment - Robotic Bartender
 *  Alessandro Binci – 0001189831
 *  Gianluca Vairo – 0001192707
 *  Pietro Luzzi – 0001176819
 *  
 *  MODIFIED SOME PIECES OF CODE
 */

#ifndef APPLICATIONS_H_
#define APPLICATIONS_H_

#include "resources.h"
#include "dummyTask.h"

extern int Overruns[], ResponseTime[];

/* Application Parameters */

/* Total number of  tasks */
#define N_PERIODIC_TASKS 4
#define N_TASKS (N_PERIODIC_TASKS)

/* Number of shared semaphores (which are the resources) */
#define N_SEMAPHORES 3

/* Task priorities */
#define TOP_PRIORITY 110

/* Periods of periodic tasks (in ticks) */
#define TASK_PERIODS {6, 9, 12, 15}

/* Phases of periodic tasks (in ticks) */
#define TASK_PHASES {0, 2, 4, 5}

/* Resource ceiling priorities (ice machine, pouring pump, counter) */
#define CEILINGS {TOP_PRIORITY, TOP_PRIORITY + 1, TOP_PRIORITY + 2}

/* Application selector */
#define ROBOTIC_BAR_APPLICATION

/* Response time clean-up log string and arguments -> commented because of some error issue, the arguments were too much */
/* To do the same thing we have modified the simulation.c */
/*
#define CLEAN_UP_STRING "Simulation ended. Response times: %d, %d, %d, %d. Overruns: %d, %d, %d, %d.\n"
#define CLEAN_UP_PARAMS (_Vx_usr_arg_t) ResponseTime[0], (_Vx_usr_arg_t) ResponseTime[1], (_Vx_usr_arg_t) ResponseTime[2], (_Vx_usr_arg_t) ResponseTime[3], \
                         (_Vx_usr_arg_t) Overruns[0], (_Vx_usr_arg_t) Overruns[1], (_Vx_usr_arg_t) Overruns[2], (_Vx_usr_arg_t) Overruns[3]
*/

/* Task Function Declarations */

void APPLICATION(int task, int functionId);  /* Entry point for each periodic task */

#endif /* APPLICATIONS_H_ */
