#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TF1.h>
#include <iomanip>
#include <math.h>
#include "RooStats/RooStatsUtils.h" //contiene la funzione per calcolare il p-value nel test z

using namespace std;


void magnetone_bohr_sigma()
{

int n_misure=12;

// ritardi in nanosecondi
float B[]={608.8,583.5,548.3,527.9,495.7,470,434.4,412.7,348.3,310.6,245.1,218.3};
float sB[]={16.3,15.1,13.6,12.7,11.5,10.6,9.4,8.8,7,6.1,4.8,4.4};

/*
//considero solo le prime 2 stime di csi

float csi[]{0.489219779407761,0.438582547359047,0.440370428982823,0.427303460776829,
0.360210660324028,0.358938387182202,0.354383377975486,0.355577500182261,
0.274919396760852,0.282720835641666,0.206521323553378,0.176836317174076};

float scsi[]={0.001391798045962,0.014664964827992,0.000665905521571,0.000142600654954,
0.021833054877229,0.014773857143212,0.005598888907919,0.011052429100492,
0.015444859639841,0.010213938483998,0.004077413296968,0.001955904000798};

*/

//le considero tutte e 3

float csi[]{0.48578528428009,0.482805250757303,0.451019459635291,0.442212667907886,
0.411947476823191,0.384288322485598,0.408137512767187,0.309904886207634,
0.29718086080439,0.246138408525821,0.20053016124464,0.179480611544589};

float scsi[]={0.005847641714487,0.07366653751138,0.016306498739486,0.022435111024063,
0.088521752187358,0.0454118315267,0.083430646641512,0.074035135512187,
0.041114625885227,0.059980609915766,0.011025450111591,0.004944393556169};




TCanvas *grafico = new TCanvas("grafico","csi/B",200,10,600,400);
grafico->SetFillColor(0);
grafico->cd();
TGraphErrors *punti = new TGraphErrors(n_misure,B,csi,sB,scsi);
punti->SetMarkerSize(0.7);
punti->SetMarkerStyle(21);
punti->SetTitle("csi/B");
punti->GetXaxis()->SetTitle("campo magnetico [mT]");
punti->GetYaxis()->SetTitle("csi");
punti->Draw("AP");




cout<<"fit con una retta"<<endl;
TF1 *funz1 = new TF1("funz1","[0]+[1]*x",100,800);

  funz1->SetParameter(0,0);//ci aspettiamo proporzionalità diretta
  
  funz1->SetLineColor(3);


  punti->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di liberta': " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;
  
  float p1=funz1->GetParameter(1)*1000; // il fit lo restituisce in 1/mT , moltoplicando per 1000 lo si trova in 1/T
  float sp1=funz1->GetParError(1)*1000;
  
    cout<<"il coefficiente di proporzionalità vale: ("<<p1<<"±"<<sp1<<") 1/T"<<endl;
    cout<<endl;

  float k=2.275e-23/2; // hc/2*mu*t*g espresso in J
  
  float m_bohr=k*p1; //misurato in J/T
  float sm_bohr=k*sp1;
  float m_bohr_teorico=9.27e-24;
  
      cout<<"la stima del magnetone di bohr vale: ("<<m_bohr<<"±"<<sm_bohr<<") 1/T"<<endl;
      cout<<"il valore teorico del magnetone di bohr è eh/2Me = 9,27*10^-24 J/T"<<endl;
      
      cout<<"Test Z"<<endl;
      float Z=(m_bohr-m_bohr_teorico)/sm_bohr;
      cout<<"Z = "<<Z<<"\t Zcritico=+-1,96 "<<endl;
      
      cout<<"il p-value vale: "<<2*RooStats::SignificanceToPValue(abs(Z))<<endl;//questa funzione dà solo la coda destra, quindi va ancora motilicata per 2, poi siccome Z è negativo bisogna prendere il valore assoluto, proprio perchè la funzione calcola la coda destra


}
