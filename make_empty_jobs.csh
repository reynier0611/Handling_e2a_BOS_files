#!/bin/csh
foreach run (`cat e2GoodRuns.txt | awk '{ if ($6 == "empty") print $1 }'`)
python write_job.py $run
mv job_${run} jobscripts/
end
