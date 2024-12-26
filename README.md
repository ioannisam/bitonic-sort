## Appendix
For more in-depth information about the project, please refer to the report.pdf document.

# Bitonic Sort using MPI
**Authors:** Ioannis Michalainas, Savvas Tzanetis

**Date:** December 2024

This project implements *distributed sorting* using the **Bitonic Sort** algorithm and the **Message Passing Interface (MPI)**. 
The primary objective is to sort a dataset of **N = 2<sup>q+p</sup>** numbers -where **2<sup>p</sup>** represents the total *processes* and **2<sup>q</sup>** the *numbers* assigned per process- utilizing inter-process communication. 
The implementation employs parallel processing to achieve efficient sorting, making it suitable for large-scale data sets.

## Installation

### Prerequisites
1. A `C` compiler
2. The `MPI` library

By running `mpirun --version` you can verify the installation. After installing this library you should clone this repository and compile the source code using the included Makefile:

### Execution

1. Clone this repository
```bash
git clone https://github.com/ioannisam/k-nn.git
```
2. Navigate to the correct directory
```bash
cd bitonic-sort
```
3. Compile the program using the included makefile
```bash
make
```

To run the executable you can either run the command `make run`, which executes the algorithm with **4** processes and a sequence of **16 random** numbers (4 numbers per process). In order to tweak the ammount of processes or total numbers to sort you should run the following command:

```bash
mpirun -np {np} ./bin/distributed {q} {p}
```
Where **np** is the number of processes, **2<sup>q</sup>** is the number of random integers per process and **2<sup>p</sup>** is also the number of processes.

For example, in order to run **4 processes** with **4 integers** per process you need to run:

```bash
mpirun -np 4 ./bin/distributed 2 2
```

## Performance
This distributed implementation (as well as any other algorithm for comparison) where run inside the **Aristotle Cluster** provided by the **Aristotle University of Thessaloniki**, with **4 cores**, splitting the load among **4 processes** or **ranks**.

 As a test, we sorted **33.554.432** ( or 2<sup>25</sup> ) random integers ranging between the numbers **1 - 999**. Note that the bitonic sorting algorithm can successfully sort only sequences in the **power of 2**.
| **Performance Table** | **Serial**            | **Distributed**      | **Quick Sort**     |
|-----------------------|-----------------------|----------------------|--------------------|
| **Time Complexity**   | O(nlog<sup>2</sup>(n))| O(log<sup>2</sup>(n))|  O(nlog(n))        |
| **Time**              | **1**min **51**sec    | **6**sec             | **1**min **24**sec |

## Appendix
For more in-depth information about the project, please refer to the `report.pdf` document.
