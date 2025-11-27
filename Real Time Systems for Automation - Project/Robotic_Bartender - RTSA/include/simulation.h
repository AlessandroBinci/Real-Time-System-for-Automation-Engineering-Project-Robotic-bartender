/*
 * simulation.h 
 * 
 * RT Assignment - Robotic Bartender
 *  Alessandro Binci – 0001189831
 *  Gianluca Vairo – 0001192707
 *  Pietro Luzzi – 0001176819
 * 
 * ADDED A FEW ROWS OF CODE
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "vxWorks.h"
#include "taskLib.h"
#include "semLib.h"
#include "sysLib.h"
#include "wdLib.h"
#include "metascheduler.h"
#include "resources.h"
#include "application.h"

/* Global state arrays */
extern int Instance[], Phase[], Period[], JobReleaseCounter[], NotFinished[], ResourceCount[];
extern int Overruns[], ResponseTime[]; /* addedd to let become those global variable visible */
extern RAPName_t RAPName[];
extern TASK_ID MetaschedulerId, WorkerId[];

#define DEFAULT_TOTAL_SIMULATION_TICKS 250

/* Simulation control functions */
void StartSimulation();
void BatchModeSimulation(int sec);
void WdHandler(int ticks);
void CleanUp(void);

/* Output utilities */
void myLogMsg(char* format_string, 
              _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2, _Vx_usr_arg_t arg3, 
              _Vx_usr_arg_t arg4, _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6 );
void ShowJobNumber(int task);

/* Auxiliary function */
int Hyperperiod();

#endif /* SIMULATION_H_ */
