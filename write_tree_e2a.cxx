#if !defined(__CINT__)
#include "TIdentificator.h"
#include "TClasTool.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "Riostream.h"
#include "TMath.h"
#endif


void write_tree_e2a(int argc, char **argv)
{
  // Create a tree to analyze physics variables
  
#if defined(__CINT__)
  gROOT->Reset();
  gSystem->Load("libClasTool.so");
  gSystem->Load("libTIdentificator.so");
#endif
  
  TClasTool *input = new TClasTool();
  
  input->InitDSTReader("ROOTDSTR");
    
  if(argc == 1) {
    char File[200];
    system("ls -1 *.root > dataFiles.txt");
    ifstream in("dataFiles.txt", ios::in);
    if (!in) {
      cerr << "File Not Opened!" << endl;
      exit(1);
    }
    while (in >> File) {
      input->Add(File);
    }
    in.close();
    system("rm dataFiles.txt");
  } 
  else 
    {
      for(int kklk=1; kklk<argc; kklk++)
	input->Add(argv[kklk]);
    }
  
  TIdentificator *t = new TIdentificator(input);
  
  TFile *output = new TFile("particle_data.root", "RECREATE", "Data of the Tree");
  TTree *tree = new TTree("data", "Tree that holds the data");

  //Reconstructed Variables
  //Write information for all events with at least 1 entry in EVNT Bank
  Int_t gPart;
  Int_t CCPart;
  Int_t DCPart;
  Int_t ECPart;
  Int_t SCPart;
  Float_t Stat[50];
  Int_t StatCC[50];
  Int_t StatDC[50];
  Int_t StatEC[50];
  Int_t StatSC[50];
  Int_t DC_Status[50];
  Int_t SC_Status[50];
  Int_t SC_Pad[50];

  Float_t EC_in[50];
  Float_t EC_out[50];
  Float_t EC_tot[50];
  Float_t EC_U[50];
  Float_t EC_V[50];
  Float_t EC_W[50];
  Float_t EC_X[50];
  Float_t EC_Y[50];
  Float_t EC_Z[50];
  Float_t Nphe[50];
  Float_t CC_Chi2[50];
  Float_t CC_Time[50];
  Float_t CC_Path[50];
  Float_t SC_Time[50];
  Float_t SC_Path[50];

  Float_t charge[50];
  Int_t id[50]; //Id in EVNT bank
  Float_t beta[50];
  Float_t mass[50];
  Float_t p[50];
  Float_t px[50];
  Float_t py[50];
  Float_t pz[50];
  Float_t theta[50];
  Float_t phi[50];
  Float_t z[50];
  Float_t theta_pq[50];

  Int_t NRun;
  Float_t STT;

  Float_t Xb;
  Float_t Q2;
  Float_t W;
  Float_t Nu;
  Float_t Yb;

  //Reconstructed Branches
  tree->Branch("gPart",&gPart,"gPart/I");
  tree->Branch("CCPart",&CCPart,"CCPart/I");
  tree->Branch("DCPart",&DCPart,"DCPart/I");
  tree->Branch("ECPart",&ECPart,"ECPart/I");
  tree->Branch("SCPart",&SCPart,"SCPart/I");
  tree->Branch("Stat",Stat,"Stat[gPart]/F");
  tree->Branch("StatCC",StatCC,"StatCC[gPart]/I");
  tree->Branch("StatDC",StatDC,"StatDC[gPart]/I");
  tree->Branch("StatEC",StatEC,"StatEC[gPart]/I");
  tree->Branch("StatSC",StatSC,"StatSC[gPart]/I");
  tree->Branch("DC_Status",DC_Status,"DC_Status[gPart]/I");
  tree->Branch("SC_Status",SC_Status,"SC_Status[gPart]/I");
  tree->Branch("SC_Pad",SC_Pad,"SC_Pad[gPart]/I");
  tree->Branch("EC_in",EC_in,"EC_in[gPart]/F");
  tree->Branch("EC_out",EC_out,"EC_out[gPart]/F");
  tree->Branch("EC_tot",EC_tot,"EC_tot[gPart]/F");
  tree->Branch("EC_U",EC_U,"EC_U[gPart]/F");
  tree->Branch("EC_V",EC_V,"EC_V[gPart]/F");
  tree->Branch("EC_W",EC_W,"EC_W[gPart]/F");
  tree->Branch("EC_X",EC_X,"EC_X[gPart]/F");
  tree->Branch("EC_Y",EC_Y,"EC_Y[gPart]/F");
  tree->Branch("EC_Z",EC_Z,"EC_Z[gPart]/F");
  tree->Branch("Nphe",Nphe,"Nphe[gPart]/F");
  tree->Branch("CC_Chi2",CC_Chi2,"CC_Chi2[gPart]/F");
  tree->Branch("CC_Time",CC_Time,"CC_Time[gPart]/F");
  tree->Branch("CC_Path",CC_Path,"CC_Path[gPart]/F");
  tree->Branch("SC_Time",SC_Time,"SC_Time[gPart]/F");
  tree->Branch("SC_Path",SC_Path,"SC_Path[gPart]/F");
  tree->Branch("Charge",charge,"charge[gPart]/F");
  tree->Branch("particle",id, "id[gPart]/I");
  tree->Branch("Beta",beta,"beta[gPart]/F");
  tree->Branch("Mass",mass,"mass[gPart]/F");
  tree->Branch("Momentum",p,"p[gPart]/F");
  tree->Branch("Momentumx",px,"px[gPart]/F");
  tree->Branch("Momentumy",py,"py[gPart]/F");
  tree->Branch("Momentumz",pz,"pz[gPart]/F");
  tree->Branch("Theta",theta,"theta[gPart]/F");
  tree->Branch("Phi",phi,"phi[gPart]/F");
  tree->Branch("TargetZ",z,"z[gPart]/F");
  tree->Branch("Thetapq",theta_pq,"theta_pq[gPart]/F");
  tree->Branch("NRun",&NRun,"NRun/I");
  tree->Branch("STT",&STT,"STT/F");
  tree->Branch("BjorkenX",&Xb,"Xb/F");
  tree->Branch("Q2",&Q2,"Q2/F");
  tree->Branch("W",&W,"W/F");
  tree->Branch("Nu",&Nu,"Nu/F");
  tree->Branch("Yb",&Yb,"Yb/F");
 
  Int_t nEntries = input->GetEntries();
  cout << "Total Entries = "<<nEntries<<endl;
  
  for (Int_t k = 0; k < nEntries; k++) {
    
    if(k%10000 == 0) cout << "Events Processed: "<< k << endl;
    input->Next();

    //Reconstucted Variables
    gPart = t->gPart();
    CCPart = t->CCPart();
    DCPart = t->DCPart();
    ECPart = t->ECPart();
    SCPart = t->SCPart();
    
    for (Int_t i = 0; i < TMath::Min(gPart, 50); i++) {

      Stat[i] = t->Status(i);
      StatCC[i] = t->StatCC(i);
      StatDC[i] = t->StatDC(i);
      StatEC[i] = t->StatEC(i);
      StatSC[i] = t->StatSC(i);
      DC_Status[i] = t->DCStatus(i);
      SC_Status[i] = t->SCStatus(i);
      SC_Pad[i] = t->SCpdht(i);

      EC_in[i] = t->Ein(i);
      EC_out[i] = t->Eout(i);
      EC_tot[i] = t->Etot(i);
      EC_U[i] = t->EC_U(i);
      EC_V[i] = t->EC_V(i);
      EC_W[i] = t->EC_W(i);
      EC_X[i] = t->EC_X(i);
      EC_Y[i] = t->EC_Y(i);
      EC_Z[i] = t->EC_Z(i);
      Nphe[i] = t->Nphe(i);
      CC_Chi2[i] = t->Chi2CC(i);
      CC_Time[i] = t->TimeCC(i);
      CC_Path[i] = t->PathCC(i);
      SC_Time[i] = t->TimeSC(i);
      SC_Path[i] = t->PathSC(i);

      charge[i] = t->Charge(i);
      id[i] = t->Id(i);
      beta[i] = t->Betta(i);
      mass[i] = TMath::Sqrt(t->Mass2(i));
      p[i] = t->Momentum(i);
      px[i] = t->Px(i);
      py[i] = t->Py(i);
      pz[i] = t->Pz(i);
      theta[i]= t->FidTheta(i);
      phi[i]= t->FidPhi(i);
      z[i] = t->Z(i);
      theta_pq[i] = (TMath::ACos(t->CosThetaPQ(i)) * TMath::RadToDeg());
      
    }
    
    if(gPart>0 && gPart<50){
      NRun = t->NRun();
      STT = t->STT();

      Xb = t->Xb();
      Q2 = t->Q2();
      W = t->W();
      Nu = t->Nu();
      Yb = t->Yb();
      
      tree->Fill();
    }
  }
  
  output->Write();
  output->Close();
  cout << "Done." << endl;
}


#if !defined(__CINT__)
int main(int argc, char **argv)
{
  write_tree_e2a(argc,argv);
  return 0;
}
#endif
