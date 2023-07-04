# WVZ

Here WVZ analysis is replicated [[1](https://cds.cern.ch/record/2314648/files/ATL-COM-PHYS-2018-420.pdf?)]. 

You must have access to the NI TSU server:

    ssh -XY -p 10023 user_name@92.63.70.26

Create and enter the working directory:

    mkdir myProject 
    cd myProject 
   
### BDT training:

    source /share/shared_data/root/bin/thisroot.sh
    root -x -b -q compact_teacher.cpp 2>&1 | tee BDT.log

#### Write BDT weight to ntuple:

    root -x -b -q compact_writer.cpp 2>&1 |tee writer2.log 

### TRExFitter [[2](https://trexfitter-docs.web.cern.ch/trexfitter-docs/)] (tutorial for 3l2j region):

#### Input histogram production:
First of all, we need to read the ntuples and turn them into histograms for further use within the framework. To do so, we make use of the n action:
   
    trex-fitter n clear_full_old.config "Regions=three_lep_presel_2jets" | tee trex_n.log
   
#### Creating the workspace
The first step after creating/reading the histograms is to produce a workspace containing our fit model:
   
   trex-fitter wfs clear_full_old.config "Regions=three_lep_presel_2jets" | tee trex_w.log

   w - create the RooStats xmls and workspace;
   f - fit the workspace;
   s - calculate significance;

#### Producing the first plots
Next up, we are going to visualize the regions we want to fit. Run the d action next to produce pre-fit plots:

   trex-fitter d compact.config "Regions=three_lep_presel_2jets" | tee trex_d.log

#### Producing the post-fit plots
Time to see how our model describes data after the fit has been done. We use the p option to produce post-fit plots:

   trex-fitter p compact.config "Regions=three_lep_presel_2jets" | tee trex_p.log

#### Ranking plot
To see which nuisance parameter has the largest impact on the uncertainty of our signal strength, we make use of the r action (see the TRExFitter readme for more information on this [[3] (https://gitlab.cern.ch/TRExStats/TRExFitter/blob/master/README.md)] ). For this tutorial, you can run them all at once:

   trex-fitter r compact.config "Regions=three_lep_presel_2jets"

   




   
   



   

   

