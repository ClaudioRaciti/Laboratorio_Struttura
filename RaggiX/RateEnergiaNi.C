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


void RateEnergiaNi(){

float energia [] = {8635.368173,8587.840155,8541.130282,8494.666841,8448.724031,8403.563789,
                8358.63365,8314.198964,8270.513406,8227.042809,8184.044085,8141.763022,
                8099.682864,8058.052472,8017.110102,7976.355577,7936.030073,7856.874913,
                7741.066112,7628.76485};
float err_energia[] = {19.69747867,19.47375489,19.25508247,19.03874405,18.82598719,
                18.61797596,18.41212806,18.20963255,18.01160026,17.81557512,17.62269123,17.43400935,
                17.2471915,17.06332012,16.88340882,16.70523023,16.5298182,16.18807769,15.69424159,
                15.22234013};
float rate[] = {1.309065238,1.111733322,1.432584264,1.531544884,1.951438237,2.568774594,
            6.71806433,13.90636136,22.08165606,28.32955507,32.82453848,30.5497888,
            27.19458578,16.99388624,6.620052984,2.297389334,1.457470826,1.457437874,
            1.48214021,1.383399209};
float err_rate[] = {0.02486095108,0.1234445438,0.1484434038,0.148214021,0.07415338385,
                0.1479455837,0.4943053776,0.3200761002,1.036304814,1.756404817,
                0.02145578557,1.700309971,0.9138961616,0.8385579435,0.3950640997,
                0.6176304288,0.1234787315,0.1235116842,0.09880934736,0.1976284585};

//Grafico passa alto
TCanvas *cG1f = new TCanvas("V_work","rate(V)",200,10,600,400);
// cG1f->SetLogx(1);
cG1f->SetFillColor(0);
cG1f->cd();
TGraphErrors *gG1f = new TGraphErrors(20,energia,rate,err_energia,err_rate);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("Rate(E) di K_alpha NaCl con Nichel");
gG1f->GetXaxis()->SetTitle("E [eV]");
gG1f->GetYaxis()->SetTitle("rate");
gG1f->Draw("AP");

cout << "\n\n --- Ipotesi  [0] --- \n" <<endl;


float start = 7.8e+3;
float stop = 8.6e+3;
TF1 *funz1 = new TF1("funz1","[0]*exp(-pow([1]-x,2)/(2*[2]))+[3]",start, stop);

// float r;
// float x_medio = 0;
// float y_medio = 0;
// int misure = 0;
// for (int i=0;i<51;i++){
//     if(V_work[i]>start && energia[i]<stop){
//         x_medio = x_medio + energia[i];
//         y_medio = y_medio + rate[i];
//         misure++;
//         // cout << energia[i]<<'\n';
//     }
// }
// x_medio=x_medio/misure;
// y_medio=y_medio/misure;

// float x_SQM = 0;

// float y_SQM = 0;
// float xy_scarti = 0;

// for (int i=0;i<51;i++){
//     if(energia[i]>start && energia[i]<stop){
//         x_SQM = x_SQM+pow(energia[i]-x_medio,2);
//         y_SQM = y_SQM+pow(rate[i]-y_medio,2);
//         xy_scarti = xy_scarti + (rate[i]-y_medio)*(energia[i]-x_medio);
//     }
// }

// // cout <<"valori: "<< x_SQM <<' '<< y_SQM<< ' ' <<xy_scarti<<endl;

// r=xy_scarti/pow(x_SQM*y_SQM,0.5);


funz1->SetParameter(0,32.);
funz1->SetParameter(1,8.2e+3);
funz1->SetParameter(2,1e4);
funz1->SetParameter(3,0.15);
funz1->SetParLimits(3,0.,10);
gG1f->Fit(funz1,"RM+");
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")."<< endl;


float energia2[] ={9417.970543,9249.945543,9087.980874,8931.757659,8780.979011};
float err_energia2[] = {23.55851913,22.70138567,21.88974707,21.12043866,20.39056621};
float rate2[] ={1.03732246,1.037054137,1.506513122,1.210388878,1.309223853};
float err_rate2[]={0.148038334,0.2470867233,0.3209181019,0.1729419853,0.1235116842};
TCanvas *cG2f = new TCanvas("Caccamo","Caccamo",200,10,600,400);
cG2f->SetFillColor(0);
cG2f->cd();
TGraphErrors *gG2f = new TGraphErrors(5,energia2,rate2,err_energia2,err_rate2);
gG2f->SetMarkerSize(0.6);
gG2f->SetMarkerStyle(21);
gG2f->SetTitle("Rate(E) di K_beta NaCl con Nichel");
gG2f->GetXaxis()->SetTitle("E [eV]");
gG2f->GetYaxis()->SetTitle("rate");
gG2f->Draw("AP");
float start = 8.7e+3;
float stop = 9.6e+3;
TF1 *funz2 = new TF1("funz2","[0]",start, stop);
funz2->SetParameter(0,32.);
gG2f->Fit(funz2,"RM+");
cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")."<< endl;


}



