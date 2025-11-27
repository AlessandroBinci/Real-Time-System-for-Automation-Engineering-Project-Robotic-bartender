/* application.c
 *
 *  RT Assignment - Robotic Bartender
 *  Alessandro Binci – 0001189831
 *  Gianluca Vairo – 0001192707
 *  Pietro Luzzi – 0001176819
 *  
 *  MODIFIED THE NAMES AND THE BEHAVIOR OF THE DIFFERENT TASKS
 */

#include "application.h"
#include "dummyTask.h"
#include "resources.h"

/* Task 0 - OrderProcessingTask */
/* T = 6, C = 1.0, phase = 0 */
/* Uses: Counter (0.3 ticks) */
void OrderProcessingTask(int task) {
    get_busy(14 * OPSMSEC);         /* Generic work before critical section */
    EntrySection(2, task);          /* Counter (index 2) */
    get_busy(6 * OPSMSEC);          /* Simulated 0.3 ticks (circa) */
    ExitSection(2, task);
}

/* Task 1 - DrinkOptionTask */
/* T = 9, C = 2.0, phase = 2 */
/* Uses: Pouring Pump (0.5 ticks) */
void DrinkOptionTask(int task) {
    get_busy(30 * OPSMSEC);         /* Generic work before critical section */
    EntrySection(1, task);          /* Pouring Pump (index 1) */
    get_busy(10 * OPSMSEC);         /* Simulated 0.5 ticks (circa) */
    ExitSection(1, task);
}

/* Task 2 - DrinkPourTask */
/* T = 12, C = 3.0, phase = 4 */
/* Uses: Pouring Pump (1.0), Ice Machine (0.5), Counter (0.3) */
void DrinkPourTask(int task) {
    get_busy(10 * OPSMSEC);         /* Generic work before critical section */
    EntrySection(1, task);          /* Pouring Pump (index 1) */
    get_busy(25 * OPSMSEC);         /* Simulated 1.0 ticks (circa) */
    ExitSection(1, task);

    EntrySection(0, task);          /* Ice Machine (index 0) */
    get_busy(10 * OPSMSEC);         /* Simulated 0.5 ticks (circa) */
    ExitSection(0, task);

    EntrySection(2, task);          /* Counter (index 2) */
    get_busy(6 * OPSMSEC);          /* Simulated 0.3 ticks (circa) */
    ExitSection(2, task);
}

/* Task 3 - FeedbackTask */
/* T = 15, C = 1.0, phase = 5 */
/* Uses: Counter (0.3 ticks) */
void FeedbackTask(int task) {
    get_busy(14 * OPSMSEC);         /* Generic work before critical section */
    EntrySection(2, task);          /* Counter (index 2) */
    get_busy(6 * OPSMSEC);          /* Simulated 0.3 ticks (circa) */
    ExitSection(2, task);
}

/* Entry point for each task */
void APPLICATION(int task, int functionId) {
    switch (functionId) {
        case 0:
            OrderProcessingTask(task);
            break;
        case 1:
            DrinkOptionTask(task);
            break;
        case 2:
            DrinkPourTask(task);
            break;
        case 3:
            FeedbackTask(task);
            break;
        default:
            break;
    }
}
