#include "HadronicWWCuts.C"

void runHadronicWWCuts(int sampleNumber, bool protonSyst=false, bool JECSystUp=false, bool JECSystDown=false, double unitarityCut=0){

	HadronicWWCuts t(sampleNumber,protonSyst,JECSystUp,JECSystDown,unitarityCut);
	t.Loop();
}