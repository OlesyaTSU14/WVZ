# Search for WWZ production in pp collisions at √s = 13TeV

Method development for improving the accuracy of LHC data analysis using machine learning tools. In particular, this study explores the statistical impact and systematic uncertainties affecting the accuracy of data analysis.

Here WVZ analysis is replicated [[1](https://cds.cern.ch/record/2314648/files/ATL-COM-PHYS-2018-420.pdf?)]. 

You must have access to the NR TSU server:

    ssh -XY -p 10023 user_name@92.63.70.26

Create and enter the working directory:

    mkdir myProject 
    cd myProject 
   
### BDT training:

    source /share/shared_data/root/bin/thisroot.sh
    root -x -b -q compact_teacher.cpp 2>&1 | tee BDT.log

#### Write BDT weights to ntuple:

    root -x -b -q compact_writer.cpp 2>&1 |tee writer2.log 

### TRExFitter [[2](https://trexfitter-docs.web.cern.ch/trexfitter-docs/)]:

#### Input histogram production:
First of all, we need to read the ntuples and turn them into histograms for further use within the framework. To do so, we make use of the n action (for example 3l2j region):
   
    trex-fitter n clear_full_old.config "Regions=three_lep_presel_2jets" | tee trex_n.log
   
#### Creating the workspace
The first step after creating/reading the histograms is to produce a workspace containing our fit model:
   
    trex-fitter wfs clear_full_old.config "Regions=three_lep_presel_2jets" | tee trex_w.log

   w - create the RooStats xmls and workspace
   
   f - fit the workspace
   
   s - calculate significance
   

#### Producing the first plots
Next up, we are going to visualize the regions we want to fit. Run the d action next to produce pre-fit plots:

    trex-fitter d compact.config "Regions=three_lep_presel_2jets" | tee trex_d.log
- the Plots/ folder contains plots showing data and MC per region you defined, as well as summary plots
- the Tables/ folder contains various tables in text or .tex format, showing you for example the yields per sample and per region

The plots produced include the effects from all systematics sources specified in the config in the bands drawn. As an example, here is the plot of the 3l2j region:

![Image alt](https://github.com/OlesyaTSU14/WVZ/blob/main/Plots/three_lep_presel_2jets.png)

#### Producing the post-fit plots
Time to see how our model describes data after the fit has been done. We use the p option to produce post-fit plots:

    trex-fitter p compact.config "Regions=three_lep_presel_2jets" | tee trex_p.log
    
![Image alt](https://github.com/OlesyaTSU14/WVZ/blob/main/Plots/three_lep_presel_2jets_postFit.png)

#### Ranking plot
To see which nuisance parameter has the largest impact on the uncertainty of our signal strength, we make use of the r action (see the TRExFitter readme for more information on this [[3](https://gitlab.cern.ch/TRExStats/TRExFitter/blob/master/README.md)]). For this tutorial, you can run them all at once:

    trex-fitter r compact.config "Regions=three_lep_presel_2jets"

For each nuisance parameter, we perform four fits. The specific nuisance parameter is fixed to one of these configurations per fit:

   pre-fit value + pre-fit uncertainty

   pre-fit value - pre-fit uncertainty

   post-fit value + post-fit uncertainty

   post-fit value - post-fit uncertainty



![Image alt](https://github.com/OlesyaTSU14/WVZ/blob/main/Plots/Ranking.png)



##### Good luck for you!


   




   
   



   

   

