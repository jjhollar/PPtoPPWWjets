#include "HadronicWWCuts.C"

void runHadronicWWCuts(int sampleNumber){

	HadronicWWCuts t(sampleNumber);
	t.Loop();
}