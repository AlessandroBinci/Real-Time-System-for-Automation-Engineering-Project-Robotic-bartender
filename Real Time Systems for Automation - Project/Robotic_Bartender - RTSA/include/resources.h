/*
 * resources.h 
 * 
 * RT Assignment - Robotic Bartender
 *  Alessandro Binci – 0001189831
 *  Gianluca Vairo – 0001192707
 *  Pietro Luzzi – 0001176819
 *  
 *  DELATED THE HLP, USELESS TO OUR SIMULATION
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include "taskLib.h"
#include "semLib.h"
#include "application.h" /* addedd to avoid errors */


typedef const char RAPName_t[100];
extern int Ceiling[];
extern int ResourceAccessProtocol;
extern SEM_ID Semaphore[];

/* Resource Access Protocol */ /* changed because we deleted HLP*/
#define NOR 0 /* no resources */
#define NOP 1 /* no protocol */
#define NPP 2 /* Non-Preemptive Critical Section Protocol */
#define PIP 3 /* Priority Inheritance Protocol */

/* Resource access procedures */
void EntrySection(int semaphore, int task);
void ExitSection(int semaphore, int task);

#endif /* RESOURCES_H_ */
