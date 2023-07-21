#!/bin/bash

# Input HITs-file for processing
input_file_HITS='/eos/atlas/atlascerngroupdisk/data-art/grid-input/CampaignInputs/mc21/HITS/mc21_13p6TeV.601229.PhPy8EG_A14_ttbar_hdamp258p75_SingleLep.simul.HITS.e8453_s3873/50events.HITS.pool.root'
#input_file_HITS='/eos/atlas/atlascerngroupdisk/data-art/grid-input/CampaignInputs/mc21/HITS/mc21_13p6TeV.601229.PhPy8EG_A14_ttbar_hdamp258p75_SingleLep.simul.HITS.e8453_s3873/100events.HITS.pool.root'

OutputAOD='AOD_test.root'

N_events=50 #!!!!!!!!!!check number of events at the name of input file. !!!!!!!
#also you can process less N_events

# run directory (to keep all the run garbage)
run_dir=/run/test_run

if [ ! -d "${run_dir}" ] ; then
    mkdir ${run_dir}
elif [ -d "${run_dir}" ] ; then
    rm -fr ../run/${run_dir}/*
fi

cd ${run_dir}

Reco_tf.py  \
  --inputHITSFile ${input_file_HITS} \
  --multithreaded True \
  --autoConfiguration='everything' \
  --conditionsTag='OFLCOND-MC21-SDR-RUN3-10' \
  --outputESDFile ESD.pool.root \
  --outputAODFile ${OutputAOD} \
  --preExec='all:from AthenaMonitoring.DQMonFlags import DQMonFlags; DQMonFlags.doHLTMon=False;rec.doTrigger=False; rec.doJetMissingETTag.set_Value_and_Lock(False); rec.doTau.set_Value_and_Lock(False);' \
  --steering='doRAWtoALL' \
  --maxEvents ${N_events} \


cd ../
