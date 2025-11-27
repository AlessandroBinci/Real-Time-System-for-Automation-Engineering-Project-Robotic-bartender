# Robotic Bartender - Real-Time System Simulation

**Course:** Real-Time Systems for Automation (RTSA)  
**University:** University of Bologna  
**Authors:** 
* Alessandro Binci
* Gianluca Vairo
* Pietro Luzzi

**[Read the Full Project Report](docs/RTSA_Project_Report.pdf)**

---

## Project Overview
This project simulates a **Robotic Bartender** control system running on the **VxWorks** Real-Time Operating System (RTOS). 

The application coordinates multiple robotic operations (ordering, pouring, mixing) with shared resource access under strict real-time constraints. The main goal is to analyze the system's schedulability and prevent priority inversion using specific **Resource Access Protocols (RAP)**.

The simulation allows verifying the feasibility of the task set and measuring worst-case response times and deadline misses (overruns).

---

## System Model

### Scheduling Policy
The system uses a **Fixed Priority** preemptive scheduler. Priorities are assigned according to the **Rate Monotonic (RM)** policy (shorter period = higher priority).

### Task Set
The application defines 4 periodic tasks. Computation times ($C_i$) are simulated using busy-wait loops calibrated via `OPSMSEC`.

| ID | Task Name | Period ($T_i$) | WCET ($C_i$) | Phase ($\phi_i$) | Priority | Description |
|:--:|:---------:|:--------------:|:------------:|:----------------:|:--------:|:------------|
| $\tau_0$ | **Order Processing** | 6 ticks | 1.0 | 0 | High | Receives drink orders (gin, wine, beer). |
| $\tau_1$ | **Drink Option** | 9 ticks | 2.0 | 2 | Mid-High | Handles optional specifications (e.g., tonic/lemon). |
| $\tau_2$ | **Drink Pour** | 12 ticks | 3.0 | 4 | Mid-Low | Pours the selected drink using pumps/machines. |
| $\tau_3$ | **Feedback** | 15 ticks | 1.0 | 5 | Low | Notifies the user that the drink is ready. |

### Shared Resources
The tasks compete for 3 shared resources protected by binary semaphores.

| ID | Resource Name | Used By | Usage Context |
|:--:|:-------------:|:-------:|:--------------|
| R0 | **Ice Machine** | $\tau_2$ | Pouring Phase |
| R1 | **Pouring Pump**| $\tau_1, \tau_2$ | Option & Pour Phases |
| R2 | **Counter** | $\tau_0, \tau_2, \tau_3$ | Order, Pour & Feedback |

---

## Resource Access Protocols (RAP)

To manage critical sections and avoid unbounded priority inversion, the simulation implements the following protocols (selectable at runtime):

1.  **NOP (No Protocol):** Standard semaphores. Susceptible to unbounded priority inversion and deadlocks.
2.  **NPP (Non-Preemptive Protocol):** A task inside a critical section runs at the highest system priority, disabling preemption.
3.  **PIP (Priority Inheritance Protocol):** Uses VxWorks `SEM_INVERSION_SAFE`. A low-priority task holding a resource inherits the priority of the highest-priority task blocked on that resource.

*(Note: The Highest Locker Priority (HLP) protocol was analyzed but excluded from the final simulation implementation).*

---

## 📊 Feasibility Analysis

We performed a theoretical feasibility analysis using the **Rate Monotonic** utilization bound and **Response Time Analysis (RTA)**.

* **Total Processor Utilization ($U$):**
  $$U = \sum \frac{C_i}{T_i} = \frac{1}{6} + \frac{2}{9} + \frac{3}{12} + \frac{1}{15} \approx \mathbf{0.7056}$$
  
* **Schedulability Result:** The system is fully schedulable ($U \le N(2^{1/N}-1)$ holds).
  
* **Max Blocking Times:**
  * **PIP:** ~1.0 ticks
  * **NPP:** ~3.0 ticks

For detailed timing diagrams (SystemViewer traces) and analysis of Synchronous vs. Phased activation, please refer to the [Project Report](docs/RTSA_Project_Report.pdf).

---

## Project Structure

* `src/application.c/h`: Defines the behavior of the periodic tasks and their critical sections.
* `src/resources.c/h`: Wrapper functions for semaphore management (`EntrySection`/`ExitSection`) implementing the logic for NPP and PIP.
* `src/metascheduler.c`: Handles the periodic activation of tasks and collects timing statistics (Response Times, Overruns).
* `src/simulation.c`: Main entry point. Sets up the VxWorks tasks, semaphores, and watchdog timers.
* `src/dummyTask.c`: Calibration functions to simulate CPU load.
* `docs/`: Contains the detailed project report and analysis.

---

## How to Run

This project is designed to be compiled and run using **WindRiver Workbench** (targeting a VxWorks 7 simulator or similar BSP).

### 1. Setup the Project
Since project files (`.wpj`, `.wr`) are environment-specific, they are not included.
Follow these steps to build from source:
1. Open **WindRiver Workbench**.
2. Create a new **VxWorks Downloadable Kernel Module (DKM)** project.
3. Import all files from the `src/` and `include/` folders of this repository into the new project.
4. Build the project.

### 2. Start the Simulation
Once the kernel is running and the module is loaded (from the VxWorks kernel shell):

#### Option A: Single Run
Run the simulation for a specific duration (or 0 for one hyperperiod).
```c
-> StartSimulation(0)
```

## Option B: Batch Mode (Testing all Protocols)
To verify the system behavior under all implemented protocols (NOP, NPP, PIP) sequentially:
```c
-> BatchModeSimulation(0)
```

## Expected output and results
### Example of batch simulation output
Starting hyperperiod batch simulations
```c
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
```

#### Observation:
Without a protocol (NOP), priority inversion may cause high-priority tasks to miss deadlines (Overruns > 0). Using NPP or PIP resolves these inversions, ensuring all tasks meet their deadlines.

## References
- Course: Real-Time Systems for Automation (M3), Prof. Paolo Torroni.

- Theory: Hard Real-Time Computing Systems, G. Buttazzo (2011).

- VxWorks 7 Programmer's Guide.



