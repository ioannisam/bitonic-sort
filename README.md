# Bitonic Sort using MPI
**Authors:** Ioannis Michalainas, Savvas Tzanetis

**Date:** December 2024

This is a serial implementation of the `Bitonic Sort` algorithm.
## Installation

### Prerequisites
1. A `C` compiler

After installing this library you should clone this repository and compile the source code using the included Makefile.

### Execution

1. Clone this repository
```bash
git clone -b serial https://github.com/ioannisam/bitonic-sort.git
```
2. Navigate to the correct directory
```bash
cd bitonic-sort
```
3. Compile the program using the included makefile
```bash
make
```

To run the executable you can run the command `make run`, which executes the algorithm with **4** processes and a sequence of **16 random** numbers (4 numbers per process). 
In order to tweak the ammount of processes or total numbers to sort you should run the following command:

```bash
./bin/serial {q} {p}
```
Where **2<sup>q</sup>** is the number of random integers per process and **2<sup>p</sup>** is the number of processes.

For example, in order to run **4 processes** with **4 integers** per process you need to run:

```bash
./bin/serial 2 2
```

## Appendix
For the *distributed* implementation, please refer to the `main` branch.
