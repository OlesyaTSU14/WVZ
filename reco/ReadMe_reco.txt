ReadMe_reco

Lets do some example of reconstruction procedure on lxplus using Athena Fraemwork.

connect to lxplus

  ssh cern_username@lxplus.cern.ch

Go to your eos directory

  cd /eos/user/username_first_letter/username

Setup Athena:

  mkdir reco 
  cd reco            # reco starts from here, in every connection to lxplus
  setupATLAS         # also need once in every connection 
  lsetup asetup      #also need once in every connection
  asetup Athena,23.0.15 #(23.0.15 its a version), you can write latest, or any other. And also setup in every connection

Now check my_reco_script.sh and run
  source my_reco_script.sh

Enjoy to read logs.

To check reco results you can read/process output AOD file (See ATAS tutorial how to...).

For development You can make your fork of Athena in Gitlab (more details: https://atlassoftwaredocs.web.cern.ch/gittutorial/).
And then init your workspace using first_time_setup.sh and make_installed.sh in reco folder, and then run my_reco_script.sh

