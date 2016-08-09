#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TMath.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "PulseShape.h"
#endif

void new_template_maker() {

  TFile *f = new TFile("test_input.root","update");
  TTree *t0 = new TTree("NEW_Dat_Bar_PulseInfo","NEW_Dat_Bar_PulseInfo");
  TTree *t1 = new TTree("NEW_Dat_End_PulseInfo","NEW_Dat_End_PulseInfo");
  TTree *t2 = new TTree("NEW_MC_Bar_PulseInfo","NEW_MC_Bar_PulseInfo");
  TTree *t3 = new TTree("NEW_MC_End_PulseInfo","NEW_MC_End_PulseInfo");

  float minCharge, maxCharge;
  float timeSlew;
  float pulseFrac[10], pulseFracDeriv[10];

  t0->Branch("minCharge", &minCharge, "minCharge/F");
  t0->Branch("maxCharge", &maxCharge, "maxCharge/F");
  t0->Branch("timeSlew",  &timeSlew,  "timeSlew/F");
  t0->Branch("pulseFrac", &pulseFrac, "pulseFrac[10]/F");
  t0->Branch("pulseFracDeriv", &pulseFracDeriv, "pulseFracDeriv[10]/F");

  //miao's
  double Lwidthdb[58], MPdb[58], Gsigmadb[58], Asymmdb[58];
  double Lwidthde[58], MPde[58], Gsigmade[58], Asymmde[58];
  double Lwidthmb[58], MPmb[58], Gsigmamb[58], Asymmmb[58];
  double Lwidthme[58], MPme[58], Gsigmame[58], Asymmme[58]; 
  
  Lwidthdb[0] = 0.215959; MPdb[0] = 4.111022; Gsigmadb[0] = 0.374303; Asymmdb[0] = 0.073503;
  Lwidthdb[1] = 0.198001; MPdb[1] = 4.115118; Gsigmadb[1] = 0.350332; Asymmdb[1] = 0.053384;
  Lwidthdb[2] = 0.188862; MPdb[2] = 4.114232; Gsigmadb[2] = 0.336443; Asymmdb[2] = 0.038027;
  Lwidthdb[3] = 0.185129; MPdb[3] = 4.108383; Gsigmadb[3] = 0.327478; Asymmdb[3] = 0.026739;
  Lwidthdb[4] = 0.181890; MPdb[4] = 4.104200; Gsigmadb[4] = 0.321306; Asymmdb[4] = 0.017689;
  Lwidthdb[5] = 0.179821; MPdb[5] = 4.099644; Gsigmadb[5] = 0.317612; Asymmdb[5] = 0.010538;
  Lwidthdb[6] = 0.177513; MPdb[6] = 4.095475; Gsigmadb[6] = 0.314497; Asymmdb[6] = 0.003105;
  Lwidthdb[7] = 0.176039; MPdb[7] = 4.091068; Gsigmadb[7] = 0.313479; Asymmdb[7] = -0.001240;
  Lwidthdb[8] = 0.178009; MPdb[8] = 4.087542; Gsigmadb[8] = 0.314415; Asymmdb[8] = 0.000759;
  Lwidthdb[9] = 0.178281; MPdb[9] = 4.085370; Gsigmadb[9] = 0.312949; Asymmdb[9] = -0.001893;
  Lwidthdb[10] = 0.175860; MPdb[10] = 4.081874; Gsigmadb[10] = 0.312963; Asymmdb[10] = -0.007429;
  Lwidthdb[11] = 0.174366; MPdb[11] = 4.078066; Gsigmadb[11] = 0.312851; Asymmdb[11] = -0.012083;
  Lwidthdb[12] = 0.172471; MPdb[12] = 4.075371; Gsigmadb[12] = 0.312877; Asymmdb[12] = -0.016768;
  Lwidthdb[13] = 0.171657; MPdb[13] = 4.071528; Gsigmadb[13] = 0.312696; Asymmdb[13] = -0.019433;
  Lwidthdb[14] = 0.170760; MPdb[14] = 4.068827; Gsigmadb[14] = 0.312384; Asymmdb[14] = -0.022630;
  Lwidthdb[15] = 0.171032; MPdb[15] = 4.064607; Gsigmadb[15] = 0.311835; Asymmdb[15] = -0.025098;
  Lwidthdb[16] = 0.168632; MPdb[16] = 4.063191; Gsigmadb[16] = 0.313429; Asymmdb[16] = -0.027476;
  Lwidthdb[17] = 0.166720; MPdb[17] = 4.062288; Gsigmadb[17] = 0.314564; Asymmdb[17] = -0.030467;
  Lwidthdb[18] = 0.167278; MPdb[18] = 4.057081; Gsigmadb[18] = 0.313482; Asymmdb[18] = -0.032067;
  Lwidthdb[19] = 0.165759; MPdb[19] = 4.055446; Gsigmadb[19] = 0.314496; Asymmdb[19] = -0.034766;
  Lwidthdb[20] = 0.166802; MPdb[20] = 4.051591; Gsigmadb[20] = 0.313770; Asymmdb[20] = -0.036324;
  Lwidthdb[21] = 0.164608; MPdb[21] = 4.051366; Gsigmadb[21] = 0.315673; Asymmdb[21] = -0.039590;
  Lwidthdb[22] = 0.168553; MPdb[22] = 4.043757; Gsigmadb[22] = 0.311362; Asymmdb[22] = -0.041565;
  Lwidthdb[23] = 0.168388; MPdb[23] = 4.039630; Gsigmadb[23] = 0.311757; Asymmdb[23] = -0.042275;
  Lwidthdb[24] = 0.167983; MPdb[24] = 4.036637; Gsigmadb[24] = 0.311450; Asymmdb[24] = -0.047211;
  Lwidthdb[25] = 0.171281; MPdb[25] = 4.028895; Gsigmadb[25] = 0.308067; Asymmdb[25] = -0.047357;
  Lwidthdb[26] = 0.172129; MPdb[26] = 4.024321; Gsigmadb[26] = 0.307783; Asymmdb[26] = -0.051227;
  Lwidthdb[27] = 0.172416; MPdb[27] = 4.022428; Gsigmadb[27] = 0.306638; Asymmdb[27] = -0.054742;
  Lwidthdb[28] = 0.172366; MPdb[28] = 4.016832; Gsigmadb[28] = 0.307480; Asymmdb[28] = -0.057634;
  Lwidthdb[29] = 0.172143; MPdb[29] = 4.013188; Gsigmadb[29] = 0.306482; Asymmdb[29] = -0.061578;
  Lwidthdb[30] = 0.180685; MPdb[30] = 3.997646; Gsigmadb[30] = 0.298799; Asymmdb[30] = -0.053321;
  Lwidthdb[31] = 0.174811; MPdb[31] = 4.007235; Gsigmadb[31] = 0.303835; Asymmdb[31] = -0.067263;
  Lwidthdb[32] = 0.176704; MPdb[32] = 4.001268; Gsigmadb[32] = 0.301789; Asymmdb[32] = -0.059100;
  Lwidthdb[33] = 0.172156; MPdb[33] = 4.002347; Gsigmadb[33] = 0.307992; Asymmdb[33] = -0.059113;
  Lwidthdb[34] = 0.175280; MPdb[34] = 3.995795; Gsigmadb[34] = 0.303899; Asymmdb[34] = -0.058104;
  Lwidthdb[35] = 0.165097; MPdb[35] = 4.010842; Gsigmadb[35] = 0.315692; Asymmdb[35] = -0.069500;
  Lwidthdb[36] = 0.169927; MPdb[36] = 4.002876; Gsigmadb[36] = 0.311762; Asymmdb[36] = -0.065178;
  Lwidthdb[37] = 0.166279; MPdb[37] = 4.006304; Gsigmadb[37] = 0.314961; Asymmdb[37] = -0.057836;
  Lwidthdb[38] = 0.162020; MPdb[38] = 4.007150; Gsigmadb[38] = 0.318909; Asymmdb[38] = -0.065248;
  Lwidthdb[39] = 0.165264; MPdb[39] = 4.003862; Gsigmadb[39] = 0.315423; Asymmdb[39] = -0.067554;
  Lwidthdb[40] = 0.164111; MPdb[40] = 4.003995; Gsigmadb[40] = 0.317951; Asymmdb[40] = -0.062092;
  Lwidthdb[41] = 0.169446; MPdb[41] = 3.996420; Gsigmadb[41] = 0.312451; Asymmdb[41] = -0.063517;
  Lwidthdb[42] = 0.172228; MPdb[42] = 3.989507; Gsigmadb[42] = 0.312457; Asymmdb[42] = -0.056949;
  Lwidthdb[43] = 0.164391; MPdb[43] = 3.999021; Gsigmadb[43] = 0.317537; Asymmdb[43] = -0.058873;
  Lwidthdb[44] = 0.145888; MPdb[44] = 4.021312; Gsigmadb[44] = 0.338352; Asymmdb[44] = -0.062904;
  Lwidthdb[45] = 0.156763; MPdb[45] = 4.004841; Gsigmadb[45] = 0.330080; Asymmdb[45] = -0.055556;
  Lwidthdb[46] = 0.159887; MPdb[46] = 3.994624; Gsigmadb[46] = 0.325714; Asymmdb[46] = -0.058794;
  Lwidthdb[47] = 0.167083; MPdb[47] = 3.989678; Gsigmadb[47] = 0.317960; Asymmdb[47] = -0.060819;
  Lwidthdb[48] = 0.169669; MPdb[48] = 3.980298; Gsigmadb[48] = 0.314242; Asymmdb[48] = -0.051998;
  Lwidthdb[49] = 0.148449; MPdb[49] = 4.012281; Gsigmadb[49] = 0.337511; Asymmdb[49] = -0.066666;
  Lwidthdb[50] = 0.173675; MPdb[50] = 3.973717; Gsigmadb[50] = 0.311611; Asymmdb[50] = -0.052075;
  Lwidthdb[51] = 0.146288; MPdb[51] = 4.013180; Gsigmadb[51] = 0.340461; Asymmdb[51] = -0.063476;
  Lwidthdb[52] = 0.173571; MPdb[52] = 3.957516; Gsigmadb[52] = 0.315720; Asymmdb[52] = -0.026286;
  Lwidthdb[53] = 0.161006; MPdb[53] = 3.995364; Gsigmadb[53] = 0.326801; Asymmdb[53] = -0.042460;
  Lwidthdb[54] = 0.149055; MPdb[54] = 4.000422; Gsigmadb[54] = 0.337669; Asymmdb[54] = -0.057944;
  Lwidthdb[55] = 0.157643; MPdb[55] = 3.986312; Gsigmadb[55] = 0.335216; Asymmdb[55] = -0.066825;
  Lwidthdb[56] = 0.177746; MPdb[56] = 3.972989; Gsigmadb[56] = 0.307199; Asymmdb[56] = -0.043230;
  Lwidthdb[57] = 0.173350; MPdb[57] = 3.964460; Gsigmadb[57] = 0.313604; Asymmdb[57] = -0.044612;

  PulseShape pulse;

  for (int i=0; i<58; i++) {
    pulse.setParams(Lwidthdb[i], MPdb[i], Gsigmadb[i], Asymmdb[i]);

    minCharge=20+10*i;
    maxCharge=30+10*i;
    timeSlew=0;

    for (int j=0; j<10; j++) {
      pulse.setBin(j);

      pulseFrac[j]=pulse.compute(timeSlew);
      pulseFracDeriv[j]=(pulse.compute(0.01)-pulse.compute(-0.01))/(0.02/25.);

    }
    t0->Fill();
  }
  
  Lwidthde[0] = 0.265905; MPde[0] = 4.042637; Gsigmade[0] = 0.389489; Asymmde[0] = 0.114431;
  Lwidthde[1] = 0.223738; MPde[1] = 4.058252; Gsigmade[1] = 0.372269; Asymmde[1] = 0.081369;
  Lwidthde[2] = 0.196620; MPde[2] = 4.073799; Gsigmade[2] = 0.360820; Asymmde[2] = 0.052814;
  Lwidthde[3] = 0.179471; MPde[3] = 4.084904; Gsigmade[3] = 0.351502; Asymmde[3] = 0.032049;
  Lwidthde[4] = 0.167524; MPde[4] = 4.094949; Gsigmade[4] = 0.342793; Asymmde[4] = 0.016753;
  Lwidthde[5] = 0.160277; MPde[5] = 4.099983; Gsigmade[5] = 0.336994; Asymmde[5] = 0.007340;
  Lwidthde[6] = 0.153828; MPde[6] = 4.105906; Gsigmade[6] = 0.330161; Asymmde[6] = -0.001743;
  Lwidthde[7] = 0.151804; MPde[7] = 4.106699; Gsigmade[7] = 0.327155; Asymmde[7] = -0.005414;
  Lwidthde[8] = 0.153506; MPde[8] = 4.106480; Gsigmade[8] = 0.326057; Asymmde[8] = -0.005052;
  Lwidthde[9] = 0.151495; MPde[9] = 4.108183; Gsigmade[9] = 0.323885; Asymmde[9] = -0.008647;
  Lwidthde[10] = 0.149190; MPde[10] = 4.107730; Gsigmade[10] = 0.321467; Asymmde[10] = -0.014244;
  Lwidthde[11] = 0.147638; MPde[11] = 4.106060; Gsigmade[11] = 0.320224; Asymmde[11] = -0.018823;
  Lwidthde[12] = 0.147134; MPde[12] = 4.103817; Gsigmade[12] = 0.318518; Asymmde[12] = -0.022298;
  Lwidthde[13] = 0.145603; MPde[13] = 4.102467; Gsigmade[13] = 0.318531; Asymmde[13] = -0.025630;
  Lwidthde[14] = 0.143665; MPde[14] = 4.102093; Gsigmade[14] = 0.318834; Asymmde[14] = -0.029152;
  Lwidthde[15] = 0.143729; MPde[15] = 4.100042; Gsigmade[15] = 0.317798; Asymmde[15] = -0.031907;
  Lwidthde[16] = 0.142679; MPde[16] = 4.099208; Gsigmade[16] = 0.317706; Asymmde[16] = -0.034758;
  Lwidthde[17] = 0.142366; MPde[17] = 4.097427; Gsigmade[17] = 0.317340; Asymmde[17] = -0.037085;
  Lwidthde[18] = 0.140709; MPde[18] = 4.096322; Gsigmade[18] = 0.317557; Asymmde[18] = -0.040115;
  Lwidthde[19] = 0.141259; MPde[19] = 4.094025; Gsigmade[19] = 0.317120; Asymmde[19] = -0.042508;
  Lwidthde[20] = 0.139953; MPde[20] = 4.094108; Gsigmade[20] = 0.317546; Asymmde[20] = -0.044836;
  Lwidthde[21] = 0.139651; MPde[21] = 4.092359; Gsigmade[21] = 0.317477; Asymmde[21] = -0.047670;
  Lwidthde[22] = 0.139679; MPde[22] = 4.090029; Gsigmade[22] = 0.316912; Asymmde[22] = -0.051614;
  Lwidthde[23] = 0.137092; MPde[23] = 4.090362; Gsigmade[23] = 0.318431; Asymmde[23] = -0.055375;
  Lwidthde[24] = 0.139826; MPde[24] = 4.084902; Gsigmade[24] = 0.315886; Asymmde[24] = -0.059485;
  Lwidthde[25] = 0.139265; MPde[25] = 4.083724; Gsigmade[25] = 0.315444; Asymmde[25] = -0.063777;
  Lwidthde[26] = 0.139705; MPde[26] = 4.081266; Gsigmade[26] = 0.314798; Asymmde[26] = -0.068750;
  Lwidthde[27] = 0.143037; MPde[27] = 4.075022; Gsigmade[27] = 0.312134; Asymmde[27] = -0.073488;
  Lwidthde[28] = 0.140326; MPde[28] = 4.075019; Gsigmade[28] = 0.313851; Asymmde[28] = -0.077454;
  Lwidthde[29] = 0.140321; MPde[29] = 4.072924; Gsigmade[29] = 0.313633; Asymmde[29] = -0.083129;
  Lwidthde[30] = 0.138929; MPde[30] = 4.072996; Gsigmade[30] = 0.314711; Asymmde[30] = -0.084285;
  Lwidthde[31] = 0.138480; MPde[31] = 4.071797; Gsigmade[31] = 0.315128; Asymmde[31] = -0.085638;
  Lwidthde[32] = 0.139634; MPde[32] = 4.069440; Gsigmade[32] = 0.314175; Asymmde[32] = -0.088140;
  Lwidthde[33] = 0.142005; MPde[33] = 4.065506; Gsigmade[33] = 0.312039; Asymmde[33] = -0.091154;
  Lwidthde[34] = 0.141657; MPde[34] = 4.064791; Gsigmade[34] = 0.312403; Asymmde[34] = -0.091306;
  Lwidthde[35] = 0.139064; MPde[35] = 4.067531; Gsigmade[35] = 0.314408; Asymmde[35] = -0.091329;
  Lwidthde[36] = 0.138958; MPde[36] = 4.066129; Gsigmade[36] = 0.314645; Asymmde[36] = -0.091590;
  Lwidthde[37] = 0.138342; MPde[37] = 4.066057; Gsigmade[37] = 0.314944; Asymmde[37] = -0.092972;
  Lwidthde[38] = 0.134574; MPde[38] = 4.068492; Gsigmade[38] = 0.318068; Asymmde[38] = -0.091124;
  Lwidthde[39] = 0.141687; MPde[39] = 4.061128; Gsigmade[39] = 0.312079; Asymmde[39] = -0.094937;
  Lwidthde[40] = 0.136809; MPde[40] = 4.065562; Gsigmade[40] = 0.316742; Asymmde[40] = -0.092790;
  Lwidthde[41] = 0.136862; MPde[41] = 4.063725; Gsigmade[41] = 0.316803; Asymmde[41] = -0.093451;
  Lwidthde[42] = 0.136935; MPde[42] = 4.063386; Gsigmade[42] = 0.316783; Asymmde[42] = -0.093408;
  Lwidthde[43] = 0.141921; MPde[43] = 4.058919; Gsigmade[43] = 0.311659; Asymmde[43] = -0.099131;
  Lwidthde[44] = 0.134735; MPde[44] = 4.063913; Gsigmade[44] = 0.318901; Asymmde[44] = -0.092367;
  Lwidthde[45] = 0.133890; MPde[45] = 4.066013; Gsigmade[45] = 0.318655; Asymmde[45] = -0.093966;
  Lwidthde[46] = 0.134311; MPde[46] = 4.063195; Gsigmade[46] = 0.318930; Asymmde[46] = -0.094529;
  Lwidthde[47] = 0.137013; MPde[47] = 4.057767; Gsigmade[47] = 0.317558; Asymmde[47] = -0.098736;
  Lwidthde[48] = 0.135377; MPde[48] = 4.059878; Gsigmade[48] = 0.318830; Asymmde[48] = -0.097444;
  Lwidthde[49] = 0.132908; MPde[49] = 4.062384; Gsigmade[49] = 0.321981; Asymmde[49] = -0.092629;
  Lwidthde[50] = 0.134887; MPde[50] = 4.061768; Gsigmade[50] = 0.318825; Asymmde[50] = -0.096242;
  Lwidthde[51] = 0.136089; MPde[51] = 4.056148; Gsigmade[51] = 0.319115; Asymmde[51] = -0.098120;
  Lwidthde[52] = 0.131460; MPde[52] = 4.061431; Gsigmade[52] = 0.322185; Asymmde[52] = -0.095117;
  Lwidthde[53] = 0.126071; MPde[53] = 4.066094; Gsigmade[53] = 0.327439; Asymmde[53] = -0.093793;
  Lwidthde[54] = 0.145901; MPde[54] = 4.042741; Gsigmade[54] = 0.312382; Asymmde[54] = -0.102888;
  Lwidthde[55] = 0.134361; MPde[55] = 4.055407; Gsigmade[55] = 0.321407; Asymmde[55] = -0.094374;
  Lwidthde[56] = 0.132428; MPde[56] = 4.057151; Gsigmade[56] = 0.324119; Asymmde[56] = -0.095372;
  Lwidthde[57] = 0.131553; MPde[57] = 4.058329; Gsigmade[57] = 0.323948; Asymmde[57] = -0.093456;

  t1->Branch("minCharge", &minCharge, "minCharge/F");
  t1->Branch("maxCharge", &maxCharge, "maxCharge/F");
  t1->Branch("timeSlew",  &timeSlew,  "timeSlew/F");
  t1->Branch("pulseFrac", &pulseFrac, "pulseFrac[10]/F");
  t1->Branch("pulseFracDeriv", &pulseFracDeriv, "pulseFracDeriv[10]/F");

  for (int i=0; i<58; i++) {
    pulse.setParams(Lwidthde[i], MPde[i], Gsigmade[i], Asymmde[i]);

    minCharge=20+10*i;
    maxCharge=30+10*i;
    timeSlew=0;

    for (int j=0; j<10; j++) {
      pulse.setBin(j);

      pulseFrac[j]=pulse.compute(timeSlew);
      pulseFracDeriv[j]=(pulse.compute(0.01)-pulse.compute(-0.01))/(0.02/25.);

    }
    t1->Fill();
  }
  
  Lwidthmb[0] = 0.201978; MPmb[0] = 4.148154; Gsigmamb[0] = 0.456533; Asymmmb[0] = 0.142273;
  Lwidthmb[1] = 0.183631; MPmb[1] = 4.130868; Gsigmamb[1] = 0.445519; Asymmmb[1] = 0.146587;
  Lwidthmb[2] = 0.173678; MPmb[2] = 4.116817; Gsigmamb[2] = 0.438951; Asymmmb[2] = 0.148417;
  Lwidthmb[3] = 0.168240; MPmb[3] = 4.104118; Gsigmamb[3] = 0.433627; Asymmmb[3] = 0.148211;
  Lwidthmb[4] = 0.162949; MPmb[4] = 4.096574; Gsigmamb[4] = 0.431255; Asymmmb[4] = 0.148286;
  Lwidthmb[5] = 0.158108; MPmb[5] = 4.090421; Gsigmamb[5] = 0.429557; Asymmmb[5] = 0.148315;
  Lwidthmb[6] = 0.155013; MPmb[6] = 4.084619; Gsigmamb[6] = 0.427617; Asymmmb[6] = 0.147389;
  Lwidthmb[7] = 0.153005; MPmb[7] = 4.079644; Gsigmamb[7] = 0.425356; Asymmmb[7] = 0.145642;
  Lwidthmb[8] = 0.150252; MPmb[8] = 4.076807; Gsigmamb[8] = 0.424404; Asymmmb[8] = 0.145715;
  Lwidthmb[9] = 0.146553; MPmb[9] = 4.074744; Gsigmamb[9] = 0.423440; Asymmmb[9] = 0.146523;
  Lwidthmb[10] = 0.144028; MPmb[10] = 4.071946; Gsigmamb[10] = 0.421999; Asymmmb[10] = 0.145930;
  Lwidthmb[11] = 0.142711; MPmb[11] = 4.069007; Gsigmamb[11] = 0.419544; Asymmmb[11] = 0.144473;
  Lwidthmb[12] = 0.141493; MPmb[12] = 4.067764; Gsigmamb[12] = 0.416944; Asymmmb[12] = 0.142689;
  Lwidthmb[13] = 0.141730; MPmb[13] = 4.066008; Gsigmamb[13] = 0.412969; Asymmmb[13] = 0.139556;
  Lwidthmb[14] = 0.143179; MPmb[14] = 4.063463; Gsigmamb[14] = 0.408011; Asymmmb[14] = 0.132513;
  Lwidthmb[15] = 0.143296; MPmb[15] = 4.062955; Gsigmamb[15] = 0.404938; Asymmmb[15] = 0.127672;
  Lwidthmb[16] = 0.145334; MPmb[16] = 4.060715; Gsigmamb[16] = 0.400256; Asymmmb[16] = 0.119411;
  Lwidthmb[17] = 0.145477; MPmb[17] = 4.060194; Gsigmamb[17] = 0.397163; Asymmmb[17] = 0.113250;
  Lwidthmb[18] = 0.143215; MPmb[18] = 4.061318; Gsigmamb[18] = 0.396044; Asymmmb[18] = 0.112670;
  Lwidthmb[19] = 0.140170; MPmb[19] = 4.062351; Gsigmamb[19] = 0.395755; Asymmmb[19] = 0.114367;
  Lwidthmb[20] = 0.138559; MPmb[20] = 4.062980; Gsigmamb[20] = 0.394711; Asymmmb[20] = 0.114461;
  Lwidthmb[21] = 0.137636; MPmb[21] = 4.063234; Gsigmamb[21] = 0.393346; Asymmmb[21] = 0.111563;
  Lwidthmb[22] = 0.139688; MPmb[22] = 4.061722; Gsigmamb[22] = 0.390625; Asymmmb[22] = 0.100774;
  Lwidthmb[23] = 0.142693; MPmb[23] = 4.061273; Gsigmamb[23] = 0.387558; Asymmmb[23] = 0.084215;
  Lwidthmb[24] = 0.142604; MPmb[24] = 4.060753; Gsigmamb[24] = 0.386380; Asymmmb[24] = 0.080084;
  Lwidthmb[25] = 0.144420; MPmb[25] = 4.060173; Gsigmamb[25] = 0.384452; Asymmmb[25] = 0.069181;
  Lwidthmb[26] = 0.144041; MPmb[26] = 4.060635; Gsigmamb[26] = 0.383916; Asymmmb[26] = 0.063183;
  Lwidthmb[27] = 0.145158; MPmb[27] = 4.060428; Gsigmamb[27] = 0.382655; Asymmmb[27] = 0.051741;
  Lwidthmb[28] = 0.144846; MPmb[28] = 4.059800; Gsigmamb[28] = 0.382187; Asymmmb[28] = 0.049206;
  Lwidthmb[29] = 0.145205; MPmb[29] = 4.058485; Gsigmamb[29] = 0.381157; Asymmmb[29] = 0.045249;
  Lwidthmb[30] = 0.145743; MPmb[30] = 4.057239; Gsigmamb[30] = 0.380329; Asymmmb[30] = 0.040238;
  Lwidthmb[31] = 0.144766; MPmb[31] = 4.057137; Gsigmamb[31] = 0.380080; Asymmmb[31] = 0.036229;
  Lwidthmb[32] = 0.145428; MPmb[32] = 4.055351; Gsigmamb[32] = 0.378863; Asymmmb[32] = 0.032392;
  Lwidthmb[33] = 0.146233; MPmb[33] = 4.053768; Gsigmamb[33] = 0.377872; Asymmmb[33] = 0.029951;
  Lwidthmb[34] = 0.145221; MPmb[34] = 4.053903; Gsigmamb[34] = 0.378157; Asymmmb[34] = 0.028300;
  Lwidthmb[35] = 0.144129; MPmb[35] = 4.053053; Gsigmamb[35] = 0.378589; Asymmmb[35] = 0.029734;
  Lwidthmb[36] = 0.142821; MPmb[36] = 4.054106; Gsigmamb[36] = 0.378944; Asymmmb[36] = 0.026221;
  Lwidthmb[37] = 0.141791; MPmb[37] = 4.053823; Gsigmamb[37] = 0.379569; Asymmmb[37] = 0.027046;
  Lwidthmb[38] = 0.140719; MPmb[38] = 4.053392; Gsigmamb[38] = 0.379914; Asymmmb[38] = 0.026981;
  Lwidthmb[39] = 0.139826; MPmb[39] = 4.053783; Gsigmamb[39] = 0.380223; Asymmmb[39] = 0.025609;
  Lwidthmb[40] = 0.138521; MPmb[40] = 4.052938; Gsigmamb[40] = 0.380626; Asymmmb[40] = 0.024999;
  Lwidthmb[41] = 0.137406; MPmb[41] = 4.053105; Gsigmamb[41] = 0.381172; Asymmmb[41] = 0.026247;
  Lwidthmb[42] = 0.136850; MPmb[42] = 4.052406; Gsigmamb[42] = 0.381033; Asymmmb[42] = 0.024020;
  Lwidthmb[43] = 0.136885; MPmb[43] = 4.051885; Gsigmamb[43] = 0.380482; Asymmmb[43] = 0.022427;
  Lwidthmb[44] = 0.135645; MPmb[44] = 4.052662; Gsigmamb[44] = 0.381559; Asymmmb[44] = 0.022812;
  Lwidthmb[45] = 0.133831; MPmb[45] = 4.053264; Gsigmamb[45] = 0.382754; Asymmmb[45] = 0.023013;
  Lwidthmb[46] = 0.132910; MPmb[46] = 4.053403; Gsigmamb[46] = 0.383522; Asymmmb[46] = 0.021847;
  Lwidthmb[47] = 0.131347; MPmb[47] = 4.054167; Gsigmamb[47] = 0.383824; Asymmmb[47] = 0.022792;
  Lwidthmb[48] = 0.130868; MPmb[48] = 4.054418; Gsigmamb[48] = 0.384175; Asymmmb[48] = 0.020562;
  Lwidthmb[49] = 0.129297; MPmb[49] = 4.054587; Gsigmamb[49] = 0.384718; Asymmmb[49] = 0.022846;
  Lwidthmb[50] = 0.128355; MPmb[50] = 4.054418; Gsigmamb[50] = 0.385518; Asymmmb[50] = 0.021018;
  Lwidthmb[51] = 0.128158; MPmb[51] = 4.054816; Gsigmamb[51] = 0.385345; Asymmmb[51] = 0.016289;
  Lwidthmb[52] = 0.128229; MPmb[52] = 4.053150; Gsigmamb[52] = 0.385069; Asymmmb[52] = 0.019468;
  Lwidthmb[53] = 0.125798; MPmb[53] = 4.056017; Gsigmamb[53] = 0.386994; Asymmmb[53] = 0.019764;
  Lwidthmb[54] = 0.126237; MPmb[54] = 4.054120; Gsigmamb[54] = 0.386657; Asymmmb[54] = 0.023578;
  Lwidthmb[55] = 0.126488; MPmb[55] = 4.054996; Gsigmamb[55] = 0.386408; Asymmmb[55] = 0.017098;
  Lwidthmb[56] = 0.124827; MPmb[56] = 4.054506; Gsigmamb[56] = 0.386559; Asymmmb[56] = 0.020731;
  Lwidthmb[57] = 0.123800; MPmb[57] = 4.055361; Gsigmamb[57] = 0.387378; Asymmmb[57] = 0.022329;

  t2->Branch("minCharge", &minCharge, "minCharge/F");
  t2->Branch("maxCharge", &maxCharge, "maxCharge/F");
  t2->Branch("timeSlew",  &timeSlew,  "timeSlew/F");
  t2->Branch("pulseFrac", &pulseFrac, "pulseFrac[10]/F");
  t2->Branch("pulseFracDeriv", &pulseFracDeriv, "pulseFracDeriv[10]/F");

  for (int i=0; i<58; i++) {
    pulse.setParams(Lwidthmb[i], MPmb[i], Gsigmamb[i], Asymmmb[i]);

    minCharge=20+10*i;
    maxCharge=30+10*i;
    timeSlew=0;

    for (int j=0; j<10; j++) {
      pulse.setBin(j);

      pulseFrac[j]=pulse.compute(timeSlew);
      pulseFracDeriv[j]=(pulse.compute(0.01)-pulse.compute(-0.01))/(0.02/25.);

    }
    t2->Fill();
  }
  
  Lwidthme[0] = 0.188894; MPme[0] = 4.130555; Gsigmame[0] = 0.482460; Asymmme[0] = 0.124535;
  Lwidthme[1] = 0.170983; MPme[1] = 4.115428; Gsigmame[1] = 0.468343; Asymmme[1] = 0.133268;
  Lwidthme[2] = 0.161272; MPme[2] = 4.101664; Gsigmame[2] = 0.461214; Asymmme[2] = 0.137380;
  Lwidthme[3] = 0.155289; MPme[3] = 4.089149; Gsigmame[3] = 0.455933; Asymmme[3] = 0.139421;
  Lwidthme[4] = 0.149883; MPme[4] = 4.081056; Gsigmame[4] = 0.453386; Asymmme[4] = 0.140973;
  Lwidthme[5] = 0.145240; MPme[5] = 4.074598; Gsigmame[5] = 0.451391; Asymmme[5] = 0.142292;
  Lwidthme[6] = 0.141898; MPme[6] = 4.069519; Gsigmame[6] = 0.449158; Asymmme[6] = 0.142730;
  Lwidthme[7] = 0.139136; MPme[7] = 4.065495; Gsigmame[7] = 0.446646; Asymmme[7] = 0.143103;
  Lwidthme[8] = 0.135672; MPme[8] = 4.064186; Gsigmame[8] = 0.444794; Asymmme[8] = 0.144519;
  Lwidthme[9] = 0.132154; MPme[9] = 4.063075; Gsigmame[9] = 0.442574; Asymmme[9] = 0.146050;
  Lwidthme[10] = 0.130071; MPme[10] = 4.060736; Gsigmame[10] = 0.439044; Asymmme[10] = 0.146477;
  Lwidthme[11] = 0.128542; MPme[11] = 4.060151; Gsigmame[11] = 0.435447; Asymmme[11] = 0.146483;
  Lwidthme[12] = 0.126737; MPme[12] = 4.061268; Gsigmame[12] = 0.431399; Asymmme[12] = 0.146973;
  Lwidthme[13] = 0.125855; MPme[13] = 4.061509; Gsigmame[13] = 0.426811; Asymmme[13] = 0.146192;
  Lwidthme[14] = 0.125596; MPme[14] = 4.060758; Gsigmame[14] = 0.422790; Asymmme[14] = 0.144604;
  Lwidthme[15] = 0.124783; MPme[15] = 4.060489; Gsigmame[15] = 0.419971; Asymmme[15] = 0.143206;
  Lwidthme[16] = 0.123830; MPme[16] = 4.060212; Gsigmame[16] = 0.417868; Asymmme[16] = 0.141871;
  Lwidthme[17] = 0.121521; MPme[17] = 4.060890; Gsigmame[17] = 0.416964; Asymmme[17] = 0.143655;
  Lwidthme[18] = 0.118956; MPme[18] = 4.061720; Gsigmame[18] = 0.416962; Asymmme[18] = 0.145152;
  Lwidthme[19] = 0.114871; MPme[19] = 4.063636; Gsigmame[19] = 0.417782; Asymmme[19] = 0.148301;
  Lwidthme[20] = 0.112603; MPme[20] = 4.064169; Gsigmame[20] = 0.418225; Asymmme[20] = 0.149653;
  Lwidthme[21] = 0.111208; MPme[21] = 4.063128; Gsigmame[21] = 0.417895; Asymmme[21] = 0.149698;
  Lwidthme[22] = 0.111253; MPme[22] = 4.061324; Gsigmame[22] = 0.417063; Asymmme[22] = 0.148405;
  Lwidthme[23] = 0.109676; MPme[23] = 4.061248; Gsigmame[23] = 0.417619; Asymmme[23] = 0.149312;
  Lwidthme[24] = 0.109287; MPme[24] = 4.060214; Gsigmame[24] = 0.417236; Asymmme[24] = 0.148773;
  Lwidthme[25] = 0.110258; MPme[25] = 4.056482; Gsigmame[25] = 0.416057; Asymmme[25] = 0.145585;
  Lwidthme[26] = 0.109558; MPme[26] = 4.055057; Gsigmame[26] = 0.416299; Asymmme[26] = 0.145442;
  Lwidthme[27] = 0.109715; MPme[27] = 4.052114; Gsigmame[27] = 0.415506; Asymmme[27] = 0.142802;
  Lwidthme[28] = 0.111051; MPme[28] = 4.049110; Gsigmame[28] = 0.414160; Asymmme[28] = 0.140169;
  Lwidthme[29] = 0.112528; MPme[29] = 4.045294; Gsigmame[29] = 0.412512; Asymmme[29] = 0.136746;
  Lwidthme[30] = 0.113121; MPme[30] = 4.042309; Gsigmame[30] = 0.411927; Asymmme[30] = 0.133697;
  Lwidthme[31] = 0.114672; MPme[31] = 4.038687; Gsigmame[31] = 0.410110; Asymmme[31] = 0.127961;
  Lwidthme[32] = 0.119905; MPme[32] = 4.033238; Gsigmame[32] = 0.405743; Asymmme[32] = 0.115087;
  Lwidthme[33] = 0.125421; MPme[33] = 4.028152; Gsigmame[33] = 0.401232; Asymmme[33] = 0.098679;
  Lwidthme[34] = 0.124976; MPme[34] = 4.027282; Gsigmame[34] = 0.401329; Asymmme[34] = 0.098112;
  Lwidthme[35] = 0.124973; MPme[35] = 4.026373; Gsigmame[35] = 0.400677; Asymmme[35] = 0.096678;
  Lwidthme[36] = 0.116329; MPme[36] = 4.030587; Gsigmame[36] = 0.407103; Asymmme[36] = 0.118396;
  Lwidthme[37] = 0.112626; MPme[37] = 4.032547; Gsigmame[37] = 0.409561; Asymmme[37] = 0.125550;
  Lwidthme[38] = 0.110072; MPme[38] = 4.033680; Gsigmame[38] = 0.411485; Asymmme[38] = 0.130077;
  Lwidthme[39] = 0.106655; MPme[39] = 4.035540; Gsigmame[39] = 0.413218; Asymmme[39] = 0.136085;
  Lwidthme[40] = 0.106224; MPme[40] = 4.034337; Gsigmame[40] = 0.412941; Asymmme[40] = 0.135040;
  Lwidthme[41] = 0.103305; MPme[41] = 4.036554; Gsigmame[41] = 0.414232; Asymmme[41] = 0.138316;
  Lwidthme[42] = 0.102192; MPme[42] = 4.036097; Gsigmame[42] = 0.414926; Asymmme[42] = 0.139084;
  Lwidthme[43] = 0.099649; MPme[43] = 4.039373; Gsigmame[43] = 0.416594; Asymmme[43] = 0.143713;
  Lwidthme[44] = 0.099857; MPme[44] = 4.038540; Gsigmame[44] = 0.416260; Asymmme[44] = 0.143195;
  Lwidthme[45] = 0.098922; MPme[45] = 4.038363; Gsigmame[45] = 0.415974; Asymmme[45] = 0.144158;
  Lwidthme[46] = 0.096832; MPme[46] = 4.040360; Gsigmame[46] = 0.417449; Asymmme[46] = 0.146380;
  Lwidthme[47] = 0.094991; MPme[47] = 4.041224; Gsigmame[47] = 0.418301; Asymmme[47] = 0.147757;
  Lwidthme[48] = 0.093528; MPme[48] = 4.041209; Gsigmame[48] = 0.419411; Asymmme[48] = 0.149419;
  Lwidthme[49] = 0.094035; MPme[49] = 4.040953; Gsigmame[49] = 0.418195; Asymmme[49] = 0.147781;
  Lwidthme[50] = 0.092793; MPme[50] = 4.042149; Gsigmame[50] = 0.418913; Asymmme[50] = 0.149421;
  Lwidthme[51] = 0.092800; MPme[51] = 4.039295; Gsigmame[51] = 0.418402; Asymmme[51] = 0.147933;
  Lwidthme[52] = 0.092108; MPme[52] = 4.039563; Gsigmame[52] = 0.419212; Asymmme[52] = 0.148876;
  Lwidthme[53] = 0.091138; MPme[53] = 4.041056; Gsigmame[53] = 0.419087; Asymmme[53] = 0.150294;
  Lwidthme[54] = 0.090935; MPme[54] = 4.042657; Gsigmame[54] = 0.419890; Asymmme[54] = 0.150972;
  Lwidthme[55] = 0.089794; MPme[55] = 4.043337; Gsigmame[55] = 0.419403; Asymmme[55] = 0.151992;
  Lwidthme[56] = 0.088960; MPme[56] = 4.043213; Gsigmame[56] = 0.419493; Asymmme[56] = 0.152149;
  Lwidthme[57] = 0.088180; MPme[57] = 4.043233; Gsigmame[57] = 0.419903; Asymmme[57] = 0.153297;
  //end miao's

  t3->Branch("minCharge", &minCharge, "minCharge/F");
  t3->Branch("maxCharge", &maxCharge, "maxCharge/F");
  t3->Branch("timeSlew",  &timeSlew,  "timeSlew/F");
  t3->Branch("pulseFrac", &pulseFrac, "pulseFrac[10]/F");
  t3->Branch("pulseFracDeriv", &pulseFracDeriv, "pulseFracDeriv[10]/F");

  for (int i=0; i<58; i++) {
    pulse.setParams(Lwidthme[i], MPme[i], Gsigmame[i], Asymmme[i]);

    minCharge=20+10*i;
    maxCharge=30+10*i;
    timeSlew=0;

    for (int j=0; j<10; j++) {
      pulse.setBin(j);

      pulseFrac[j]=pulse.compute(timeSlew);
      pulseFracDeriv[j]=(pulse.compute(0.01)-pulse.compute(-0.01))/(0.02/25.);

    }
    t3->Fill();
  }

  f->Write();
  f->Close();
  
}
