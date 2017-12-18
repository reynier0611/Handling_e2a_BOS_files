Instructions from Barak:

Hi Rey,

You can find the code that will analyze the BOS files and create new ROOT files for 'easy' analysis here:

/u/home/baraks/packages/Analyser/my_analysis/e2a_sim/write_tree_e2a.cxx

You can use the 'Makefile' in the same directory to compile it.
The code requires two libraries, the CLASTOOL libraries and the Analyser library.
You can just link to the ones in my directory (since there is not much point in
simply copying the packages and recompiling them). You can do this by adding the
following to your .cshrc file:

setenv OS_NAME Linux64RHEL7
setenv CLASTOOL /u/home/baraks/packages/ClasTool
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${CLASTOOL}/slib/${OS_NAME}:/u/home/baraks/packages/Analyser/analysis_lib/slib


Then you can run the 'write_tree_e2a' executable on any CLASTOOL converted BOS
file to create a file called 'particle_data.root'. Since the BOS files are
located on the tape silo, though, it is easier to do the on the batch farm.
See here for an example:

/u/home/baraks/packages/Analyser/my_analysis/e2a_sim/farm_data/helium4_17908

The output from running this job is located here:

/lustre/expphy/volatile/halla/gmp12/baraks/analysis_out/e2a/4He/particle_data_17908.root

There is an (rapidly evolving) analysis code in that directory as well.

========================================================================
write_job.py

python script by Axel. Run by doing: python write_job.py "run_number"
Need to have file: e2GoodRuns.txt in the same directory, for write_job.py
uses it as an input. This code produces the job script for a given
run.
 
========================================================================
make_empty_jobs.csh

c shell script by Axel. Run by doing: ./make_empty_jobs.csh

this creates all the job files required for empty runs.
Can use it as a template to create jobs for any specified
conditions.

