#include <iostream>           // ci serve per stampare a video il testo
//#include <TGraphErrors.h>     // ci serve per istanziare grafici
//#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
//#include <TCanvas.h>          // ci serve per disegnare i grafici
//#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;


void fitRI(){

float I [] = {0.181 , 0.183 , 0.185 , 0.187 , 0.191 , 0.193 , 0.196 , 0.203 , 0.207 , 0.209 , 0.212 , 0.216 , 0.219 , 0.222 , 0.228 , 0.24 , 0.31 , 0.363 , 0.509 , 0.574 , 0.65 , 0.732 , 0.842 , 0.941 , 1.028 , 1.323 , 1.544 , 2.049 , 2.589};
float err_I[] = {0.002 , 0.002 , 0.002 , 0.002 , 0.005 , 0.002 , 0.002 , 0.002 , 0.0015 , 0.001 , 0.002 , 0.002 , 0.001 , 0.002 , 0.002 , 0.002 , 0.0085 , 0.01 , 0.002 , 0.002 , 0.003 , 0.002 , 0.002 , 0.003 , 0.002 , 0.002 , 0.002 , 0.002 , 0.001};
float rate[] = {613.6356322 , 617.9969396 , 626.3513935 , 627.1997468 , 647.1125695 , 643.473914 , 659.3440937 , 676.217608 , 684.2767606 , 700.4839943 , 703.4400874 , 712.4134529 , 726.2764387 , 730.1466558 , 757.0018607 , 770.601236 , 976.8319763 , 1113.944614 , 1437.393637 , 1472.516434 , 1604.285884 , 1747.045796 , 1925.506232 , 2053.076488 , 2159.892982 , 2445.139288 , 2580.33689 , 2696.968964 , 2667.77338};
float err_rate[] = {1.380657645 , 3.504615233 , 0.179017199 , 3.971264257 , 0.219217064 , 2.725493739 , 8.836154064 , 1.244747012 , 6.88446923 , 3.104534228 , 2.482913559 , 3.444599533 , 0.996288601 , 1.393324449 , 2.71981321 , 8.520185561 , 8.364174685 , 0.832933231 , 0.26966064 , 5.836623237 , 13.0899852 , 11.84008028 , 6.060008868 , 2.8868604 , 2.857621092 , 0.158973104 , 5.1609459 , 0.255718593 , 4.516605764};

//Grafico passa alto
TCanvas *cG1f = new TCanvas("R_I","rate(I)",200,10,600,400);
// cG1f->SetLogx(1);
cG1f->SetFillColor(0);
cG1f->cd();
//TMultiGraph *mg = new TMultiGraph();
TGraphErrors *gG1f = new TGraphErrors(29,I,rate,err_I,err_rate);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("rate(I)");
gG1f->GetXaxis()->SetTitle("I");
gG1f->GetYaxis()->SetTitle("rate");
gG1f->Draw("AP");

cout << "\n\n --- Ipotesi  [0]*x+[1] --- \n" <<endl;

float start = 0.180;
float stop = 0.50;
TF1 *funz2 = new TF1("funz1","[0]*x+[1]",start, stop);

/*float r;
float x_medio = 0;
float y_medio = 0;
int misure = 0;
for (int i=0;i<51;i++){
    if(V_work[i]>start && HV_work[i]<stop){
        x_medio = x_medio + HV_work[i];
        y_medio = y_medio + rate[i];
        misure++;
        // cout << HV_work[i]<<'\n';
    }
}
x_medio=x_medio/misure;
y_medio=y_medio/misure;

float x_SQM = 0;

float y_SQM = 0;
float xy_scarti = 0;

for (int i=0;i<51;i++){
    if(HV_work[i]>start && HV_work[i]<stop){
        x_SQM = x_SQM+pow(HV_work[i]-x_medio,2);
        y_SQM = y_SQM+pow(rate[i]-y_medio,2);
        xy_scarti = xy_scarti + (rate[i]-y_medio)*(HV_work[i]-x_medio);
    }
}

// cout <<"valori: "<< x_SQM <<' '<< y_SQM<< ' ' <<xy_scarti<<endl;

r=xy_scarti/pow(x_SQM*y_SQM,0.5);

*/
funz1->SetParameter(0,1000.);
funz1->SetParameter(1,0.25);
gG1f->Fit(funz1,"RM+");
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << endl;

TF1 *funz2 = new TF1("funz2","[0]/(1+exp((x-[1])/[2]))+[3]",0.55,2.570);// 2.9361 sarebbe il rate di fondo

  funz2->SetParameter(0,2.18626e+003);
  funz2->SetParameter(1, 6.74578e-001);
  funz2->SetParameter(2,-3.43136e-001);
  funz2->SetParameter(3, 5.49379e+002);
  funz2->SetLineColor(3);


  gG1f->Fit(funz2,"RM+");
  cout << "X^2: " << funz2->GetChisquare() << ", gradi di liberta': " << funz2->GetNDF() << " (p-value: " << funz2->GetProb() << ")." << endl;

/*
start = 420;
stop = 445;
TF1 *funz2 = new TF1("funz2","[0]+[1]*x",start,stop);
x_medio=0;
y_medio=0;
misure=0;
x_SQM=0;
y_SQM=0;
xy_scarti=0;
for (int i=0;i<51;i++){
    if(V_work[i]>start && HV_work[i]<stop){
        x_medio = x_medio + HV_work[i];
        y_medio = y_medio + rate[i];
        misure++;
        // cout << HV_work[i]<<'\n';
    }
}
x_medio=x_medio/misure;
y_medio=y_medio/misure;
for (int i=0;i<51;i++){
    if(HV_work[i]>start && HV_work[i]<stop){
        x_SQM = x_SQM+pow(HV_work[i]-x_medio,2);
        y_SQM = y_SQM+pow(rate[i]-y_medio,2);
        xy_scarti = xy_scarti + (rate[i]-y_medio)*(HV_work[i]-x_medio);
    }
}

// cout <<"valori: "<< x_SQM <<' '<< y_SQM<< ' ' <<xy_scarti<<endl;

r=xy_scarti/pow(x_SQM*y_SQM,0.5);


funz2->SetParameter(0,1000.);
funz2->SetParameter(1,0.);
gG1f->Fit(funz2,"RM+");
cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF()
    << " (Probability: " << funz2->GetProb() << "). r ="<< r << endl;

float intersection;
intersection=(funz1->GetParameter(0)-funz2->GetParameter(0))/funz2->GetParameter(1);
cout<<"intersection at:"<<intersection<<endl;


// start = 420;
// stop = 500;
// TF1 *funz3 = new TF1("funz3","[0]/(1+exp(([1]-x)/[2]))",start,stop);
// funz3->SetParameter(0,1000.);
// funz3->SetParameter(1,450.);
// funz3->SetParameter(2,5.);
// gG1f->Fit(funz3,"RM+");
// cout << "Chi^2:" << funz3->GetChisquare() << ", number of DoF: " << funz3->GetNDF()
//     << " (Probability: " << funz3->GetProb() << ")."<< endl;


TF1 *retta1 = new TF1("retta1"," 1.47047e+003",420,540);
TF1 *retta2 = new TF1("retta2","-1.44106e+004+3.54466e+001*x",420,460);


retta1->Draw("same");
retta2->Draw("same");*/

}



