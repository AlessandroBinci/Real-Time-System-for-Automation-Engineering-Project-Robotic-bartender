/*
 * metascheduler.c 
 * 
 * RT Assignment - Robotic Bartender
 *  Alessandro Binci – 0001189831
 *  Gianluca Vairo – 0001192707
 *  Pietro Luzzi – 0001176819
 * 
 * NOT MODIFIED
 */

#include "metascheduler.h"

/* Meta-scheduler variables */
int NotFinished[N_TASKS];
int InOverrun[N_TASKS];

/* Task information */
TASK_ID MetaschedulerId, WorkerId[N_TASKS];
int Period[N_TASKS] = TASK_PERIODS;
int Phase[N_TASKS] = TASK_PHASES;
int Instance[N_TASKS]; /* J[i,1], J[i,2], ... */
int JobReleaseCounter[N_TASKS]; /* J1, J2, ...*/
int Overruns[N_TASKS]; /* number of overruns of task in present simulation */
int ResponseTime[N_TASKS]; /* max response time of tasks in present simulation */

/* Meta-scheduler function definitions */
void AuxClkHandler() {
	taskResume(MetaschedulerId);
}

void MetaschedulerShell() {
	FOREVER {
		taskSuspend(0);
		Metascheduler();
	}
}

void Metascheduler() {
	int task, ResTime;
	for(task=0;task<N_TASKS;task++) {
		JobReleaseCounter[task]--;
		if(NotFinished[task]) {
			/* check if job has finished */
			if(taskIsSuspended(WorkerId[task])) {
				/* if job has finished, display response time and update statistics */
				NotFinished[task]=FALSE;
				ResTime = Period[task]*(1+InOverrun[task])-JobReleaseCounter[task];
				myLogMsg("Response Time [%d] = %d units\n", 
						(_Vx_usr_arg_t) task, 
						(_Vx_usr_arg_t) ResTime, 
						0, 0, 0, 0 );
				if(ResponseTime[task]<ResTime) {
					ResponseTime[task]=ResTime;
				}
				InOverrun[task]=0;
			}
		}
		/* if it is time to start a new period, reset parameters and check if overrun */
		if(JobReleaseCounter[task]==0) {
			NotFinished[task]=TRUE;
			JobReleaseCounter[task] = Period[task];
			if(taskIsSuspended(WorkerId[task]))
				/* If no overrun, resume task */
				taskResume(WorkerId[task]);
			else {
				myLogMsg("Task%d OVERRUN!!!\n", (_Vx_usr_arg_t) task, 0, 0, 0, 0, 0 );
				Overruns[task] ++;
				InOverrun[task]++;
			}
		}
	}
}
