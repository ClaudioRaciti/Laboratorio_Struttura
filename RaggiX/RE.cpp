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
#include <TLatex.h>


using namespace std;


void RE(){

float E [] = {8780.979011 , 8731.783356 , 8683.443736 , 8635.368173 , 8587.840155 , 8541.130282 , 8494.666841 , 8448.724031 , 8403.563789 , 8358.63365 , 8314.198964 , 8270.513406 , 8227.042809 , 8184.044085 , 8141.763022 , 8099.682864 , 8058.052472 , 8017.110102 , 7976.355577 , 7936.030073 , 7896.364642 , 7817.794716 , 7741.066112};
float err_E[] = {20.39056621 , 20.15510826 , 19.9250331 , 19.69747867 , 19.47375489 , 19.25508247 , 19.03874405 , 18.82598719 , 18.61797596 , 18.41212806 , 18.20963255 , 18.01160026 , 17.81557512 , 17.62269123 , 17.43400935 , 17.2471915 , 17.06332012 , 16.88340882 , 16.70523023 , 16.5298182 , 16.35814191 , 16.02061365 , 15.69424159};
float rate[] = {3.556864376 , 3.828765803 , 3.260254565 , 3.654613669 , 3.630654261 , 3.310024051 , 3.285320494 , 4.223354125 , 5.335558316 , 11.46245059 , 24.25493891 , 42.46676162 , 49.63943495 , 53.93928936 , 44.06564968 , 32.05872673 , 15.3629609 , 8.916211306 , 4.273293153 , 3.23584626 , 3.210971903 , 3.236006126 , 3.013452016};
float err_rate[] = {0.345719233 , 0.074010603 , 0.29670621 , 0.296588978 , 0.222910286 , 0.296338956 , 0.370444747 , 0.122968787 , 0.592709642 , 0.345849802 , 1.387353584 , 1.870159484 , 0.246962363 , 0.304362453 , 2.172556116 , 0.784023172 , 0.197973744 , 0.072774717 , 0.617527912 , 0.123505582 , 0.147882135 , 0.172916358 , 0.395133668};

//Grafico passa alto
TCanvas *cG1f = new TCanvas("R_E","rate(E)",200,10,600,400);
// cG1f->SetLogx(1);
cG1f->SetFillColor(0);
cG1f->cd();
//TMultiGraph *mg = new TMultiGraph();
TGraphErrors *gG1f = new TGraphErrors(23,E,rate,err_E,err_rate);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("rate(E) K_{#alpha} NaCl");
gG1f->GetXaxis()->SetTitle("E");
gG1f->GetYaxis()->SetTitle("rate");
gG1f->Draw("AP");

cout << "\n\n --- Ipotesi  gaus --- \n" <<endl;

float start = 7740.;
float stop = 8650.;
TF1 *funz1 = new TF1("funz1","[0]*exp(-pow([1]-x,2)/(2*[2]))+[3]",start, stop);

funz1->SetParameter(0,50.);
funz1->SetParameter(1,8200.);
funz1->SetParameter(2,1e4);
funz1->SetParameter(3,1.);
funz1->SetParLimits(3,0.,10.);
funz1->SetLineColor(1);

gG1f->Fit(funz1,"RM+");
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
/*
TF1 *funz2 = new TF1("funz2","[0]/(1+exp((x-[1])/[2]))+[3]",0.55,2.570);// 2.9361 sarebbe il rate di fondo

  funz2->SetParameter(0,2.18626e+003);
  funz2->SetParameter(1, 6.74578e-001);
  funz2->SetParameter(2,-3.43136e-001);
  funz2->SetParameter(3, 5.49379e+002);
  funz2->SetLineColor(3);


  gG1f->Fit(funz2,"RM+");
  cout << "X^2: " << funz2->GetChisquare() << ", gradi di liberta': " << funz2->GetNDF() << " (p-value: " << funz2->GetProb() << ")." << endl;
*/

float E_beta [] = {9773.599713 , 9712.301379 , 9653.227908 , 9592.398824 , 9533.405351 , 9475.499705 , 9417.970543 , 9361.155489 , 9305.375407 , 9249.945543 , 9195.191547 , 9141.423199 , 9087.980874 , 9035.178862 , 8983.316406 , 8931.757659 , 8880.80612 , 8830.751013 , 8780.979011};
float err_E_beta[] = {25.42347111 , 25.09709433 , 24.78450383 , 24.46461345 , 24.15630491 , 23.85552834 , 23.55851913 , 23.26696902 , 22.98244332 , 22.70138567 , 22.42540076 , 22.15597565 , 21.88974707 , 21.62823845 , 21.37286364 , 21.12043866 , 20.87241099 , 20.63012594 , 20.39056621};
float rate_beta[] = {2.667775497 , 3.161650189 , 3.161822234 , 3.088000826 , 3.013550863 , 3.11241634 , 3.2854108 , 3.482460929 , 3.408575956 , 4.199104387 , 5.977670191 , 10.32481655 , 10.62148009 , 12.85563867 , 8.966742034 , 8.027862859 , 6.990070642 , 5.704438512 , 4.223121121};
float err_rate_beta[] = {0.444565181 , 0.197369768 , 0.049481556 , 0.271516984 , 0.296562274 , 0.049326571 , 0.222321032 , 0.272108778 , 0.098462819 , 0.741118911 , 0.444620097 , 0.197859079 , 0.345815631 , 0.581768702 , 0.61776466 , 0.370516747 , 0.419898236 , 0.319063018 , 0.320537512};

//Grafico passa alto
TCanvas *cG2f = new TCanvas("R_E_beta","rate(E)_beta",200,10,600,400);
// cG1f->SetLogx(1);
cG2f->SetFillColor(0);
cG2f->cd();
//TMultiGraph *mg = new TMultiGraph();
TGraphErrors *gG2f = new TGraphErrors(19,E_beta,rate_beta,err_E_beta,err_rate_beta);
gG2f->SetMarkerSize(0.6);
gG2f->SetMarkerStyle(21);
gG2f->SetTitle("rate(E) K_{#beta} NaCl");
gG2f->GetXaxis()->SetTitle("E");
gG2f->GetYaxis()->SetTitle("rate");
gG2f->Draw("AP");

cout << "\n\n --- Ipotesi  gaus --- \n" <<endl;

float start = 8770.;
float stop = 9780.;
//TF1 *funz1 = new TF1("funz2","[0]*exp(-pow([1]-x,2)/(2*[2]))+[3]",start, stop);
TF1 *funz2 = new TF1("funz2","[0]*exp(-pow([1]-x,2)/(2*[2]))+[3]",8770, 9780);

funz2->SetParameter(0,11);
funz2->SetParameter(1,9000.);
funz2->SetParameter(2,3000.);
funz2->SetParameter(3,3.);
funz2->SetParLimits(3,0.,10.);
//funz1->SetParameter(3,1.);
//funz1->SetParLimits(3,0.,10.);
//commento
funz2->SetLineColor(1);

gG2f->Fit(funz2,"RM+");
cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;

}
