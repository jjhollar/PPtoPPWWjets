#include "HadronicWWCuts.C"

void runHadronicWWCuts(int sampleNumber, bool protonSyst=false, bool JECSystUp=false, bool JECSystDown=false, double unitarityCut=999999,double min_mvvCut=0,double gen_xi_min=0,double gen_xi_max=0){

	HadronicWWCuts t(sampleNumber,protonSyst,JECSystUp,JECSystDown,unitarityCut,min_mvvCut,gen_xi_min,gen_xi_max);
	t.Loop();
}