---
title:  One-sided communication
author: CSC Training
date:   2019-02
lang:   en
---


# One-sided communication

- Two components of message-passing: sending and receiving
    - Sends and receives need to match
- One-sided communication:
    - Only single process calls data movement functions - remote memory
      access (RMA)
    - Communication patterns specified by only a single process
    - Always non-blocking


# Why one-sided communication?

- Certain algorithms featuring irregular and/or dynamic communication
  patterns easier to implement
    - A priori information of sends and receives is not needed
- Potentially reduced overhead and improved scalability
- Hardware support for remote memory access has been restored in most
  current-generation architectures


# Origin and target

- Key terms of one-sided communication:

    Origin
      : a process which calls data movement function

    Target
      : a process whose memory is accessed


# Remote memory access window

- Window is a region in process's memory which is made available
  for remote operations
- Windows are created by collective calls
- Windows may be different in different processes

![](img/one-sided-window.png){.center}


# Data movement operations

- PUT data to the memory in target process
    - From local buffer in origin to the window in target
- GET data from the memory of target process
    - From the window in target to the local buffer in origin
- ACCUMULATE data in target process
    - Use local buffer in origin and update the data (e.g. add the data
      from origin) in the window of the target
    - One-sided reduction


# Synchronization

- Communication takes place within *epoch*s
    - Synchronization calls start and end an *epoch*
    - There can be multiple data movement calls within epoch
    - An epoch is specific to particular window
- Active synchronization:
    - Both origin and target perform synchronization calls
- Passive synchronization:
    - No MPI calls at target process


# One-sided communication in a nutshell

<div class="column">
- Define memory window
- Start an epoch
    - Target: exposure epoch
    - Origin: access epoch
- GET, PUT, and/or ACCUMULATE data
- Complete the communications by ending the epoch
</div>

<div class="column">
![](img/one-sided-epoch.png)
</div>


# Key MPI functions for one-sided communication {.section}


# Creating an window {.split-definition}

`MPI_Win_create(base, size, disp_unit, info, comm, win)`
  : `base`{.input}
    : (pointer to) local memory to expose for RMA

    `size`{.input}
    : size of a window in bytes

    `disp_unit`{.input}
    : local unit size for displacements in bytes

    `info`{.input}
    : hints for implementation

    `comm`{.input}
    : communicator

    `win`{.output}
    : handle to window

- The window object is deallocated with `MPI_Win_free(win)`


# Starting and ending an epoch

`MPI_Win_fence(assert, win)`
  : `assert`{.input}
    : optimize for specific usage. Valid values are "0", `MPI_MODE_NOSTORE`,
      `MPI_MODE_NOPUT`, `MPI_MODE_NOPRECEDE`, `MPI_MODE_NOSUCCEED`

    `win`{.input}
    : window handle

- Used both for starting and ending an epoch
    - Should both precede and follow data movement calls
- Collective, barrier-like operation


# Data movement: Put {.split-definition}

`MPI_Put(origin, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win)`
  : `origin`{.input}
    : (pointer to) local data to be sent to target

    `origin_count`{.input}
    : number of elements to put

    `origin_datatype`{.input}
    : MPI datatype for local data

    `target_rank`{.input}
    : rank of the target task

    `target_disp`{.input}
    : starting point in target window

    `target_count`{.input}
    : number of elements in target

    `target_datatype`{.input}
    : MPI datatype for remote data

    `win`{.input}
    : RMA window


# Data movement: Get {.split-definition}

`MPI_Get(origin, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win)`
  : `origin`{.input}
    : (pointer to) local buffer in which to receive the data

    `origin_count`{.input}
    : number of elements to get

    `origin_datatype`{.input}
    : MPI datatype for local data

    `target_rank`{.input}
    : rank of the target task

    `target_disp`{.input}
    : starting point in target window

    `target_count`{.input}
    : number of elements from target

    `target_datatype`{.input}
    : MPI datatype for remote data

    `win`{.input}
    : RMA window


# Data movement: Accumulate {.split-def-3}

`MPI_Accumulate(origin, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win)`
  : `origin`{.input}
    : (pointer to) local data to be accumulated

    `origin_count`{.input}
    : number of elements to put

    `origin_datatype`{.input}
    : MPI datatype for local data

    `target_rank`{.input}
    : rank of the target task

    `target_disp`{.input}
    : starting point in target window

    `target_count`{.input}
    : number of elements for target

    `target_datatype`{.input}
    : MPI datatype for remote data

    `op`{.input}
    : accumulation operation (as in `MPI_Reduce`)

    `win`{.input}
    : RMA window


# Simple example: Put

```c
int data;
MPI_Win window;

...

data = rank;
// Create window
MPI_Win_create(&data, sizeof(int), sizeof(int), MPI_INFO_NULL,
               MPI_COMM_WORLD, &window);

...
MPI_Win_fence(0, window);
if (rank == 0)
    MPI_Put(&data, 1, MPI_INT, 1, 0, 1, MPI_INT, window);
MPI_Win_fence(0, window);
...

MPI_Win_free(&window);
```


# Limitations for data access

- Compatibility of local and remote operations when multiple processes
  access a window during an epoch

![](img/one-sided-limitations.png)


# Advanced synchronization:

- Assert argument in `MPI_Win_fence`:

    `MPI_MODE_NOSTORE`
    : The local window was not updated by local stores (or local get or
      receive calls) since last synchronization

    `MPI_MODE_NOPUT`
    : The local window will not be updated by put or accumulate calls after
      the fence call, until the ensuing (fence) synchronization

    `MPI_MODE_NOPRECEDE`
    : The fence does not complete any sequence of locally issued RMA calls

    `MPI_MODE_NOSUCCEED`
    : The fence does not start any sequence of locally issued RMA calls


# Advanced synchronization

- More control on epochs can be obtained by starting and ending the
  exposure and access epochs separately
- Target: Exposure epoch
    - Start: `MPI_Win_post`
    - End: `MPI_Win_wait`
- Origin: Access epoch
    - Start: `MPI_Win_start`
    - End: `MPI_Win_complete`


# Enhancements in MPI-3

- New window creation function: `MPI_Win_allocate`
    - Allocate memory and create window at the same time
- Dynamic windows: `MPI_Win_create_dynamic`, `MPI_Win_attach`,
  `MPI_Win_detach`
  - Non-collective exposure of memory


# Enhancements in MPI-3

- New data movement operations: `MPI_Get_accumulate`, `MPI_Fetch_and_op`,
  `MPI_Compare_and_swap`
- New memory model `MPI_Win_allocate_shared`
    - Allocate memory which is shared between MPI tasks
- Enhancements for passive target synchronization


# Performance considerations

- Performance of the one-sided approach is highly implementation-dependent
- Maximize the amount of operations within an epoch
- Provide the assert parameters for `MPI_Win_fence`


# OSU benchmark example

![](img/osu-benchmark.png)


# Summary

- One-sided communication allows communication patterns to be specified
  from a single process
- Can reduce synchronization overheads and provide better performance
  especially on recent hardware
- Basic concepts:
    - Origin and target process
    - Creation of the memory window
    - Communication epoch
    - Data movement operations
