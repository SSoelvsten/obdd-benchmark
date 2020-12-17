# Grendel
This folder contains the generation of shell scripts, with which one can run the
benchmarks on the GRENDEL-S cluster running the SLURM queueing system at [CSCAA,
Aarhus University](http://www.cscaa.dk/). Since _COOM_ makes use of disk, then
one needs to use the newly acquired _q48_ nodes with 3.0 GHz CPUs, 384 GB of
memory, and 3.5 TB of SSD disk available for temporary files in a _scratch/_
directory.

With `grendel_build.sh` we provide a script to compile all the benchmarks on the
CPU in question. This way, we are sure to compile it for the right instruction
set.

```bash
sbatch -p q48 grendel/grendel_build.sh
```

The shell scripts running each instance of a benchmark can be generated by
running the Python 3 script `grendel_gen.py`

```bash
cd grendel && python3 grendel_gen.py
```

Then one can schedule all the generated shell files from the root directory of
this repository with

```bash
for f in grendel/*_*_*.sh; do sbatch -p q48 $f; done
```

Or with `grendel/<package>_*_*.sh` or `grendel/*_<benchmark>_*.sh` one
can schedule only a particular subset of them to be run. The output of these
runs will be appended to files at `/out/<benchmark>/<package>_<N>.out`.