#include "HadronicWWCuts.C"

void runHadronicWWCuts(int sampleNumber, bool protonSyst=false, bool JECSystUp=false, bool JECSystDown=false, double unitarityCut=0,double min_mvvCut=999999){

	HadronicWWCuts t(sampleNumber,protonSyst,JECSystUp,JECSystDown,unitarityCut,min_mvvCut);
	t.Loop();
}