/*
 * dummyTask.h 
 *  
 *  RT Assignment - Robotic Bartender
 *  Alessandro Binci – 0001189831
 *  Gianluca Vairo – 0001192707
 *  Pietro Luzzi – 0001176819
 *  
 *  MODIFIED TO ADAPT THE OPSMSEC TO OUR DEVICE, OTHER PARTS OF THE CODE IS THE SAME
 */

#ifndef DUMMYTASK_H_
#define DUMMYTASK_H_

/* used to adapt the value to our system, just changed the name, done for clarity */
#define PC

/* dummy task parameters, do not change them */
#define LOWER_LIMIT 1000
#define UPPER_LIMIT 2000
#define UP 1
#define DOWN 0

/* approximately OPSMSEC cycles correspond to 1 msec computation on target architecture*/
#ifdef MACBOOK
#define OPSMSEC 446000
#else
#ifdef IMAC
#define OPSMSEC 730000
#else
#ifdef PC
#define OPSMSEC 600000 /* to modify it later (maybe), actually is good for the system in which we are doing simulations */
#endif
#endif
#endif

/* only for event tracing purposes */
void all_done(void);

/* to simulate actual computation: keeps CPU busy for n cycles */
void get_busy(int n);

#endif /* DUMMYTASK_H_ */
