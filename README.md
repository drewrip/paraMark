# paraMark

Simple benchmarking program adapted for use with MPI written in C++.


## Compiling with mpic++:

```
mpic++ paraMark.cpp -o paraMark
```

## Running using Hydra:

```
mpiexec -n [number or processes] -f [hosts file] paraMark
```

-n = number of processors including the cores
-f = file that contains the host names of the nodes you want to run on (one per line)
