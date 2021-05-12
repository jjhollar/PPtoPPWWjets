#include "HadronicWWCuts.C"

void runHadronicWWCuts(int sampleNumber, bool protonSyst=false, bool JECSystUp=false, bool JECSystDown=false){

	HadronicWWCuts t(sampleNumber,protonSyst,JECSystUp,JECSystDown);
	t.Loop();
}