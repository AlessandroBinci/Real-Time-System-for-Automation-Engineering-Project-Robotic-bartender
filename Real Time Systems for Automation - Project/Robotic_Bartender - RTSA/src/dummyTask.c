/*
 * dummyTask.c 
 *  RT Assignment - Robotic Bartender
 *  Alessandro Binci – 0001189831
 *  Gianluca Vairo – 0001192707
 *  Pietro Luzzi – 0001176819
 * 
 * NOT MODIFIED
 */

#include "dummyTask.h"

void all_done(void) {}

void get_busy(int n) {
	int i, r=LOWER_LIMIT, going=UP;
	for(i=0;i<n;i++) {
		if(going==UP) {
			if(r<UPPER_LIMIT)
				r++;
			else
				going=DOWN;
		}
		else {
			if(r>LOWER_LIMIT)
				r--;
			else
				going=UP;
		}
	}
	all_done();
}
