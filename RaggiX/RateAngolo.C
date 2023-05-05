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


void RateAngolo(){

int n_misure=20;

float angolo [] = {0.2574360647,0.2588934146,0.2603420379,0.2617993878,0.2632567377,
            0.264705361,0.2661627109,0.2676200609,0.2690686841,0.2705260341,0.271983384,
            0.273432007,0.2748893572,0.2763467071,0.2777953304,0.2792526803,0.2807100302,
            0.2836160034,0.2879793266,0.2923426497};
float err_angolo[] = {0.001454441043,0.001454441043,0.001454441043,0.001454441043,
                0.001454441043,0.001454441043,0.001454441043,0.001454441043,0.001454441043,
                0.001454441043,0.001454441043,0.001454441043,0.001454441043,0.001454441043,
                0.001454441043,0.001454441043,0.001454441043,0.001454441043,0.001454441043,
                0.001454441043};
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
TGraphErrors *gG1f = new TGraphErrors(n_misure,angolo,rate,err_angolo,err_rate);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("Rate(theta) K alpha NaCl");
gG1f->GetXaxis()->SetTitle("theta [rad]");
gG1f->GetYaxis()->SetTitle("rate [conteggi/s]");
gG1f->Draw("AP");

cout << "\n\n --- Ipotesi  [0] --- \n" <<endl;


float start = 0.255;
float stop = 0.29;
TF1 *funz1 = new TF1("funz1","[0]*exp(-pow([1]-x,2)/(2*[2]*[2]))+[3]",start, stop);

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


funz1->SetParameter(0,35.);
funz1->SetParameter(1,0.272);
funz1->SetParameter(2,3e-3);
funz1->SetParameter(3,1.);
funz1->SetParLimits(2,0,100);
funz1->SetParLimits(3,0.,10);
gG1f->Fit(funz1,"RM+");
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")."<< endl;

cout<<endl;
cout<<endl;



float theta=funz1->GetParameter(1);
float stheta=funz1->GetParError(1);

cout<<"l'angolo per il quale si ha il picco e': ("<<theta<<"+-"<<stheta<<") rad"<<endl;

float lambda=0.154; //nm lunghezza d'onda della radiazione K-alpha 
float d=lambda/(2*sin(theta));

float sd=abs((lambda/2)*cos(theta)/pow(sin(theta),2))*stheta;

cout<<endl;
cout<<"la distanza interplanare d vale: ("<<d<<"+-"<<sd<<") nm"<<endl;



float angolo2[] ={0.3577924967,0.3665191429,0.3752457892,0.3767031391,0.3781517624,
            0.3796091123,0.3810664622,0.3825150855,0.3839724354,0.3854297854,0.3868784086,
            0.3883357586,0.3897931085,0.3912417318,0.3926990817,0.3941564316,0.3956050549,
            0.3970624048,0.3985197548,0.399968378,0.401425728,0.4043317012,0.407246401,
            0.4101523742,0.4145156973,0.4188790205};
float err_angolo2[] = {0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861,
0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861,
0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861,
0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861,
0.00145444104332861,0.00145444104332861,0.00145444104332861,0.00145444104332861};
float rate2[] ={2.593470862,2.494936021,5.28558019,9.707538781,10.12618897,17.46104699,
            23.39077619,31.66133872,73.4154429,194.5174694,269.3506845,531.081097,
            607.8046068,708.2294535,497.0500308,296.0812089,141.2595022,28.72382593,
            14.17596554,14.44908548,12.74386799,12.99112796,12.42435166,11.55955145,
            9.707297175,10.96917137};
float err_rate2[]={0.1231151305,0.1235116842,0.6426877673,0.1729078154,0.1469379104,
            0.3678743818,0.517542322,0.2446226565,1.979814013,1.233518763,4.6070314,
            1.153082051,2.393329967,0.4657695654,5.960530858,2.373188384,1.062891067,
            1.011911289,0.1958242615,0.1238533131,0.1963206848,0.739979417,0.123195644,
            0.04939979252,0.07386174393,0.84321434};
TCanvas *cG2f = new TCanvas("Caccamo","Caccamo",200,10,600,400);
cG2f->SetFillColor(0);
cG2f->cd();
TGraphErrors *gG2f = new TGraphErrors(26,angolo2,rate2,err_angolo2,err_rate2);
gG2f->SetMarkerSize(0.6);
gG2f->SetMarkerStyle(21);
gG2f->SetTitle("Rate(theta) K alpha FLi");
gG2f->GetXaxis()->SetTitle("theta [rad]");
gG2f->GetYaxis()->SetTitle("rate");
gG2f->Draw("AP");
float start = 0.38;
float stop = 0.41;
TF1 *funz2 = new TF1("funz2","[0]*exp(-pow([1]-x,2)/(2*[2]))+[3]",start, stop);
funz2->SetParameter(0,700.);
funz2->SetParameter(1,0.39);
funz2->SetParameter(2,0.);
funz2->SetParameter(3,12.);
funz2->SetParLimits(0,0.,8000.);
funz2->SetParLimits(2,0.,5.);
funz2->SetParLimits(3,0.,30.);
gG2f->Fit(funz2,"RM+");
cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")."<< endl;
float theta=funz2->GetParameter(1);
float stheta=funz2->GetParError(1);

cout<<"l'angolo per il quale si ha il picco e': ("<<theta<<"+-"<<stheta<<") rad"<<endl;

float lambda=0.154; //nm lunghezza d'onda della radiazione K-alpha 
float d=lambda/(2*sin(theta));

float sd=abs((lambda/2)*cos(theta)/pow(sin(theta),2))*stheta;

cout<<endl;
cout<<"la distanza interplanare d vale: ("<<d<<"+-"<<sd<<") nm"<<endl;


}



