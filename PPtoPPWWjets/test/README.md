## Running HadronicWWCuts on HTCondor

	cd PPtoPPWWjets/PPtoPPWWjets/test

Change the content of runHadronicWWCuts.sub, to include the sample numbers you want to run, and your email for notifications:

	queue sampleNumber in (<list of your sample numbers separated by a comma>)
	notify_user			= <your email address>

Then to submit:
	
	condor_submit runHadronicWWCuts.sub
