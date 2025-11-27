# Robotic Bartender - Real-Time System Simulation

**Course:** Real-Time Systems for Automation (RTSA)  
**University:** University of Bologna  
**Authors:** 
* Alessandro Binci
* Gianluca Vairo
* Pietro Luzzi

---

## Project Overview
This project simulates a **Robotic Bartender** control system running on the **VxWorks** Real-Time Operating System (RTOS). 

The application consists of a set of periodic tasks that manage the order processing, drink preparation, and user feedback. The main goal is to analyze the system's schedulability and behavior under different **Resource Access Protocols (RAP)**, preventing priority inversion phenomena.

The simulation allows verifying the feasibility of the task set and measuring worst-case response times and deadline misses (overruns).

---

## System Model

### Scheduling Policy
The system uses a **Fixed Priority** preemptive scheduler. Priorities are assigned according to the **Rate Monotonic (RM)** policy (shorter period = higher priority).

### Task Set
The application defines 4 periodic tasks. Computation times ($C_i$) are simulated using busy-wait loops calibrated via `OPSMSEC`.

| ID | Task Name | Period ($T_i$) | WCET ($C_i$) | Priority | Description |
|:--:|:---------:|:--------------:|:------------:|:--------:|:------------|
| $\tau_0$ | **OrderProcessing** | 6 ticks | 1.0 | High | Processes incoming orders. |
| $\tau_1$ | **DrinkOption** | 9 ticks | 2.0 | Mid-High | Selects the drink type. |
| $\tau_2$ | **DrinkPour** | 12 ticks | 3.0 | Mid-Low | Controls pumps and ice machine. |
| $\tau_3$ | **Feedback** | 15 ticks | 1.0 | Low | Provides status feedback. |

### Shared Resources
The tasks compete for 3 shared resources protected by binary semaphores.

| ID | Resource Name | Used By |
|:--:|:-------------:|:-------:|
| R0 | **Ice Machine** | $\tau_2$ |
| R1 | **Pouring Pump**| $\tau_1, \tau_2$ |
| R2 | **Counter** | $\tau_0, \tau_2, \tau_3$ |

---

## Resource Access Protocols (RAP)

To manage critical sections and avoid unbounded priority inversion, the simulation implements the following protocols (selectable at runtime):

1.  **NOP (No Protocol):** Standard semaphores. Susceptible to unbounded priority inversion and deadlocks.
2.  **NPP (Non-Preemptive Protocol):** A task inside a critical section runs at the highest system priority, disabling preemption.
3.  **PIP (Priority Inheritance Protocol):** Uses VxWorks `SEM_INVERSION_SAFE`. A low-priority task holding a resource inherits the priority of the highest-priority task blocked on that resource.

*(Note: The Highest Locker Priority (HLP) protocol was analyzed but excluded from the final simulation implementation).*

---

## Project Structure

* `application.c/h`: Defines the behavior of the periodic tasks and their critical sections.
* `resources.c/h`: Wrapper functions for semaphore management (`EntrySection`/`ExitSection`) implementing the logic for NPP and PIP.
* `metascheduler.c`: Handles the periodic activation of tasks and collects timing statistics (Response Times, Overruns).
* `simulation.c`: Main entry point. Sets up the VxWorks tasks, semaphores, and watchdog timers.
* `dummyTask.c`: Calibration functions to simulate CPU load.

---

## How to Run

This project is designed to be compiled and run using **WindRiver Workbench** (targeting a VxWorks 7 simulator or similar BSP).

### 1. Setup the Project
Since project files (`.wpj`, `.wr`) are environment-specific, they are not included. Follow these steps to build from source:
1. Open **WindRiver Workbench**.
2. Create a new **VxWorks Downloadable Kernel Module (DKM)** project.
3. Import all files from the `src/` and `include/` folders of this repository into the new project.
4. Build the project.

### 2. Start the Simulation
Once the kernel is running and the module is loaded:

#### Option A: Single Run
Run the simulation for a specific duration (or 0 for one hyperperiod).
```c
-> StartSimulation(0)

## Option B: Batch Mode (Testing all Protocols)
To verify the system behavior under all implemented protocols (NOP, NPP, PIP) sequentially:
```c
-> BatchModeSimulation(0)

## Expected output and results
### Example of batch simulation output
Starting hyperperiod batch simulations
0: No Resource Access Protocol
...
Task1 OVERRUN!!!
...
2: Non-Preemptive Critical Section Protocol
Response Time [0] = 6 units
Response Time [1] = 9 units
Response Time [2] = 12 units
Response Time [3] = 15 units
Overruns: 0 0 0 0

#### Observation:
Without a protocol (NOP), priority inversion may cause high-priority tasks to miss deadlines (Overruns > 0). Using NPP or PIP resolves these inversions, ensuring all tasks meet their deadlines.

## References
Course: Real-Time Systems for Automation (M3), Prof. Paolo Torroni.
Theory: * Hard Real-Time Computing Systems, G. Buttazzo (2011).
VxWorks 7 Programmer's Guide.



