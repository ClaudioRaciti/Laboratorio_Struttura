#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TF1.h>
#include <iomanip>
#include <math.h>
#include "RooStats/RooStatsUtils.h" //contiene la funzione per calcolare il p-value nel test z

using namespace std;


void attenuazione_spessore()
{

int n_misure=62;

float conteggi[]={20525,20829,7261,7338,2598,2578,1556,1590,1003,1059,840,873,672,696,578,550,407,
460,368,372,323,370,253,258,208,276,179,190,175,189,151,169,136,145,119,139,110,125,233,247,184,
193,189,212,155,165,152,150,139,126,105,128,122,147,133,131,132,143,101,97,105,104};

float spessore[]={0,0.1,0.25,0.35,0.5,0.6,0.75,0.85,1,1.1,1.25,1.35,1.5,1.6,1.75,1.85,2,2.1,2.25,
2.35,2.5,2.6,2.75,2.85,3,3.1,3.25,3.35,3.5,3.75,3.85};//mm
float sspessore[n_misure/2];
for(int j=0;j<n_misure/2;j++){
sspessore[j]=0.05;
}

float tempo[]={20.264,20.264,20.25,20.259,20.247,20.242,20.24,20.241,20.239,20.245,20.237,20.246,
20.25,20.246,20.243,20.248,20.245,20.244,20.243,20.243,20.242,20.242,20.242,20.244,20.242,
20.245,20.244,20.242,20.244,20.244,20.244,20.244,20.243,20.243,20.242,20.244,20.245,20.242,
40.391,40.387,40.389,40.387,40.386,40.392,40.388,40.386,40.393,40.393,40.39,40.386,40.378,
40.388,60.029,60.033,60.028,60.032,60.033,60.033,60.03,60.029,60.03,60.028};

float rate_grezzi[62];

for(int j=0;j<n_misure;j++){

rate_grezzi[j]=conteggi[j]/tempo[j];
}


float rate[n_misure/2] , srate[n_misure/2];

for(int j=0;j<n_misure/2;j++){

rate[j]=(rate_grezzi[2*j]+rate_grezzi[2*j+1])/2;
srate[j]=abs(rate_grezzi[2*j]-rate_grezzi[2*j+1])/2;
}

for(int j=0;j<n_misure/2;j++){

cout<<fixed<<setprecision(2)<<"spessore: ("<<spessore[j]<<"±"<<sspessore[j]<<") mm\t\trate: ("<<rate[j]<<"±"<<srate[j]<<") Hz"<<endl;
}


float LOG[n_misure/2] , sLOG[n_misure/2];

for(int j=0;j<n_misure/2;j++){

LOG[j]=log(rate[0]/rate[j]);
sLOG[j]=sqrt(pow(srate[0]/rate[0],2)+pow(srate[j]/rate[j],2));
}



cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;

cout<<"grafico fittato con la somma di esponenziali"<<endl;

TCanvas *grafico1 = new TCanvas("grafico","attenuazione",200,10,600,400);
grafico1->SetFillColor(0);
grafico1->cd();
TGraphErrors *punti = new TGraphErrors(n_misure/2,spessore,rate,sspessore,srate);
punti->SetMarkerSize(0.7);
punti->SetMarkerStyle(21);
punti->SetTitle("curva di attenuazione");
punti->GetXaxis()->SetTitle("spessore [mm]");
punti->GetYaxis()->SetTitle("rate [conteggi/s]");
punti->Draw("AP");



TF1 *funz1 = new TF1("funz1","[0]*exp(-[1]*x)+[2]*exp(-[3]*x)",-0.5 , 4);

  funz1->SetParameter(0,1000);
  funz1->SetParameter(1,0.25);
  funz1->SetParameter(2,36);
  funz1->SetParameter(3,1.23);
  
  funz1->SetLineColor(3);


  punti->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di liberta': " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;
  
  
  



cout<<"stesso grafico messo in scala logaritmica"<<endl;

TCanvas *grafico2 = new TCanvas("grafico2","attenuazione",200,10,600,400);
grafico2->SetFillColor(0);
grafico2->cd();
grafico2->SetLogy();
punti->Draw("AP");
punti->Fit(funz1,"RM+");

cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;


cout<<"grafico ln(R0/R)"<<endl;
  
TCanvas *grafico3 = new TCanvas("grafico","attenuazione",200,10,600,400);
grafico3->SetFillColor(0);
grafico3->cd();
TGraphErrors *punti3 = new TGraphErrors(n_misure/2,spessore,LOG,sspessore,sLOG);
punti3->SetMarkerSize(0.7);
punti3->SetMarkerStyle(21);
punti3->SetTitle("ln(R0/R) - spessore");
punti3->GetXaxis()->SetTitle("spessore [mm]");
punti3->GetYaxis()->SetTitle("ln(R0/R(s)");
punti3->Draw("AP");



TF1 *funz2 = new TF1("funz2","[0]+[1]*x",-0.1 , 0.5);

  funz2->SetParameter(0,0);
  funz2->SetParameter(1,0.18);
  
  
  funz2->SetLineColor(6);


  punti3->Fit(funz2,"RM+");
  cout << "X^2: " << funz2->GetChisquare() << ", gradi di liberta': " << funz2->GetNDF() << " (p-value: " << funz2->GetProb() << ")." << endl;
  
  
  
  TF1 *funz3 = new TF1("funz3","[0]+[1]*x",1.5 , 4);

  funz3->SetParameter(0,3);
  funz3->SetParameter(1,1.22);
  
  
  funz3->SetLineColor(4);


  punti3->Fit(funz3,"RM+");
  cout << "X^2: " << funz3->GetChisquare() << ", gradi di liberta': " << funz3->GetNDF() << " (p-value: " << funz3->GetProb() << ")." << endl;
  
  cout<<endl;
  cout<<endl;
  cout<<endl;
  cout<<endl;





float ua=10*funz2->GetParameter(1);
float sua=10*funz2->GetParError(1);
float ub=10*funz3->GetParameter(1);
float sub=10*funz3->GetParError(1); // valori espressi in cm^-1
/*
Siccome nella prima parte del grafico si perde la linearità già al 3°/4° punto è meglio trovare il coefficente angolare guardando solo i primi 2 punti anzichè fare il fit. In questo modo inoltre vengono delle enrgie esattamente sugli eV che ci si aspetta per l'emissini k-alpha e k-beta del rame. Se si rifacesse l'esperienza sarebbe utile prendere misure con spessori sotto gli 0.1mm
*/
float ua_bis=10*(LOG[1]-LOG[0])/(spessore[1]-spessore[0]);
float sua_bis=10*sqrt(pow(sLOG[1]/(spessore[1]-spessore[0]),2)+pow(sLOG[2]/(spessore[1]-spessore[0]),2)+pow((LOG[1]-LOG[0])/(spessore[1]-spessore[0])*(spessore[1]-spessore[0])*sspessore[1],2)+pow((LOG[1]-LOG[0])/(spessore[1]-spessore[0])*(spessore[1]-spessore[0])*sspessore[2],2));

cout<<"i coefficienti di attenuazione valgono:"<<endl;

cout<<"ua=("<<ua<<"±"<<sua<<")cm^-1"<<endl;
cout<<"ua_bis=("<<ua_bis<<"±"<<sua_bis<<")cm^-1"<<endl;
cout<<"ub=("<<ub<<"±"<<sub<<")cm^-1"<<endl;

cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;


float ro=2.7; //densità dell'alluminio in g/cm^3

float Ua=ua/ro;//cm^2/g
float sUa=sua/ro;

float Ua_bis=ua_bis/ro;
float sUa_bis=sua_bis/ro;

float Ub=ub/ro;
float sUb=sub/ro;


cout<<"i coefficienti di attenuazione normalizzati alla massa volumica dell'alluminio valgono: "<<endl;

cout<<"Ua=("<<Ua<<"±"<<sUa<<")cm^-1"<<endl;
cout<<"Ua_bis=("<<Ua_bis<<"±"<<sUa_bis<<")cm^-1"<<endl;
cout<<"Ub=("<<Ub<<"±"<<sUb<<")cm^-1"<<endl;




}
