#!/bin/bash

echo "Which queue do you want to run in?"
read queue
echo "How many events do you want on each run? (i.e. 50000, or 100000)"
read events
ev=${events:0:2}k
echo "How many runs do you want to do?"
read runs
echo "How many nodes do you want to run on?"
read nodes
echo "How many tasks do you want to run per core?"
read tasks
echo "How much memory (in megabytes) do you want to allocate to each node?"
read mem
echo "Enter a random integer 6 digits long for the seed"
read seed
echo "Enter your Rivanna username"
read user

<<<<<<< HEAD
mkdir -p output
=======
>>>>>>> e37554e825c002c0dc21fa7d9e6d70b510dc3be4
mkdir -p scripts
mkdir -p /bigtmp/$user
mkdir -p /bigtmp/$user/scripted

for i in $(seq 1 $runs);

do

echo "#!/bin/bash
#SBATCH --nodes=$nodes
#SBATCH --ntasks-per-core=$tasks
#SBATCH --mem-per-cpu=$mem
#SBATCH -t 120:00:00
#SBATCH -o output/ttbb$ev$i.txt
#SBATCH --mail-type=ALL
#SBATCH --mail-user=$user@virginia.edu
#SBATCH -p $queue
#SBATCH -A neuphysics

module load gcc

~/private/./mg5 scripts/ttbb$ev$i.sh" > scripts/ttbb$ev$i.slurm

echo "generate p p > t t~ b b~ [QCD]
output /bigtmp/$user/scripted/ttbb$ev$i
launch /bigtmp/$user/scripted/ttbb$ev$i
        set nevents $events
        set iseed $i*$seed" > scripts/ttbb$ev$i.sh

sbatch scripts/ttbb$ev$i.slurm

done


cd ~/private/output/scripted
jobs

