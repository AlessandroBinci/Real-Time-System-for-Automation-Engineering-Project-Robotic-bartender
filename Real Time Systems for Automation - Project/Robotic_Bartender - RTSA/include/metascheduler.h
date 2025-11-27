/*
 * metascheduler.h 
 * 
 * RT Assignment - Robotic Bartender
 *  Alessandro Binci – 0001189831
 *  Gianluca Vairo – 0001192707
 *  Pietro Luzzi – 0001176819
 * 
 * NOT MODIFIED
 */

#ifndef METASCHEDULER_H_
#define METASCHEDULER_H_

#include "application.h"
#include "simulation.h"

/* Meta-scheduler function declarations */
void AuxClkHandler(void);
void MetaschedulerShell();
void Metascheduler();
void TaskShell(int task);

#endif /* METASCHEDULER_H_ */
