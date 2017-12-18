import sys

# Edit output directory

if (len(sys.argv) < 2):
    print "Error: no run number supplied!"
    sys.exit(-1)

run=int(sys.argv[1])

for line in open("e2GoodRuns.txt"):
    if line[0]=='#':
        continue
    words=line.split()
    if int(words[0])==run:
        nFiles=int(words[3])+1
        target=words[5]
        Ebeam=int(words[7])

        print "run ", run, "beam: ", Ebeam, "target: ", target, " nfiles: ", nFiles

        outfile=open("helium4_{0}".format(str(run)),'w')
        outfile.write("""PROJECT: e2a
JOBNAME: e2a_{0}
OS: centos7
TRACK: analysis
MEMORY: 2000 MB
CPU: 1
COMMAND: /lustre/expphy/work/halla/triton/Rey/CLAS/e2a_sim/script_e2a.csh

INPUT_FILES:\n
""".format(str(run)))

        # Print all the files
        for i in range(nFiles):
            outfile.write("/mss/clas/e2a/production/pass2/v1/{0}/{1}/BOS/bos_{2}_{3:02d}_v1.A00\n".format(str(Ebeam),target,str(run),i))

        outfile.write("""
OTHER_FILES:
/u/home/baraks/packages/ClasTool/bin/Linux64RHEL7/WriteRootDst
/lustre/expphy/work/halla/triton/Rey/CLAS/e2a_sim/write_tree_e2a

OUTPUT_DATA: particle_data.root
OUTPUT_TEMPLATE: /lustre/expphy/work/halla/triton/Rey/CLAS/e2a_sim/e2a_output_root/particle_data_{0}.root

SINGLE_JOB
""".format(str(run)))
        break
