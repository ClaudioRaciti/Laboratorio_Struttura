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


void MuB_longitudinale(){

float E [] = {7.0439E-05,6.1616E-05,5.8110E-05,5.5275E-05,5.2048E-05,5.1240E-05,4.4104E-05,4.3202E-05,3.1957E-05,3.0602E-05	};
float err_E[] = {9.2410E-06,1.0207E-05,4.9685E-06,4.7239E-06,4.7342E-06,1.3780E-05,9.9386E-06,2.1734E-05,3.3779E-05,1.0756E-05};
float B[] = {0.6066205453,0.5746486366,0.5255993906,0.4939155668,0.4670144214,0.4349676366,0.4090880477,0.3755199337,0.3175685163,0.2819511605};
float err_B[] = {0.01619702778,0.01471422047,0.01265055913,0.01144424162,0.01049308467,0.009442876751,0.00865727081,0.007717058845,0.006289706222,0.005527464713};
TCanvas *cG1f = new TCanvas("V_work","rate(V)",200,10,600,400);
// cG1f->SetLogx(1);
cG1f->SetFillColor(0);
cG1f->cd();
TGraphErrors *gG1f = new TGraphErrors(10,B,E,err_B,err_E);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("E(B)");
gG1f->GetYaxis()->SetTitle("E [eV]");
gG1f->GetXaxis()->SetTitle("B(T)");
gG1f->Draw("AP");

cout << "\n\n --- Ipotesi [1]+ 2.0023*[0]*x --- \n" <<endl;


float start = 0.2;
float stop = 0.7;
TF1 *funz1 = new TF1("funz1","[1]+2.0023*[0]*x",start, stop);

// float r;
// float x_medio = 0;
// float y_medio = 0;
// int misure = 0;
// for (int i=0;i<51;i++){
//     if(V_work[i]>start && angolo[i]<stop){
//         x_medio = x_medio + angolo[i];
//         y_medio = y_medio + rate[i];
//         misure++;
//         // cout << angolo[i]<<'\n';
//     }
// }
// x_medio=x_medio/misure;
// y_medio=y_medio/misure;

// float x_SQM = 0;

// float y_SQM = 0;
// float xy_scarti = 0;

// for (int i=0;i<51;i++){
//     if(angolo[i]>start && angolo[i]<stop){
//         x_SQM = x_SQM+pow(angolo[i]-x_medio,2);
//         y_SQM = y_SQM+pow(rate[i]-y_medio,2);
//         xy_scarti = xy_scarti + (rate[i]-y_medio)*(angolo[i]-x_medio);
//     }
// }

// // cout <<"valori: "<< x_SQM <<' '<< y_SQM<< ' ' <<xy_scarti<<endl;

// r=xy_scarti/pow(x_SQM*y_SQM,0.5);


funz1->SetParameter(0,0.);
gG1f->Fit(funz1,"RM+");
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")."<< endl;
}