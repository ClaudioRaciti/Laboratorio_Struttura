#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TF1.h>
#include <iomanip>
#include <math.h>

using namespace std;


void B_I()
{


float I[19]={0. , 0.55 , 1.05 , 1.5 , 2.08 , 2.54 , 3.03 , 3.55 , 4.13 , 4.67 , 5.26 , 6.23 , 6.69 , 7.22 , 7.64 , 8.2 , 8.65 , 9.09 , 9.57};
float s_I[19]={0.03 , 0.0355 , 0.0405 , 0.045 , 0.0508 , 0.0554 , 0.0603 , 0.0655 , 0.0713 , 0.0767 , 0.0826 , 0.0923 , 0.0969 , 0.1022 , 0.1064 , 0.112 , 0.1165 , 0.1209 , 0.1257};// in teoria con un certo ritardo avrebbe dovuto accendersi sempre lo stesso canale e quindi la dispersione sarebbe dovuta sempre essere 1 canale. Tuttavia in un paio di casi un paio di segnali sono finiti in altri canali quindi la dispersione � leggermente maggiore di 1

float B[19]={8.95 , 44.6 , 78 , 109 , 152 , 185 , 215 , 248 , 285 , 318 , 355 , 418 , 446 , 477 , 503 , 535 , 559 , 580 , 601}; // in nanosecondi
float s_B[19];
for (int j=0;j<19;j++){
s_B[j]=1.;//i moduli di delay avevano una risoluzione di sensibilita di 0.5 ns
}




TCanvas *grafico = new TCanvas("grafico","retta di calibrazione",200,10,600,400);
grafico->SetFillColor(0);
grafico->cd();
TGraphErrors *punti = new TGraphErrors(19,I,B,s_I,s_B);
punti->SetMarkerSize(0.7);
punti->SetMarkerStyle(21);
punti->SetTitle("retta di calibrazione");
punti->GetXaxis()->SetTitle("I [A]");
punti->GetYaxis()->SetTitle("B [mT]");
punti->Draw("AP");





TF1 *funz1 = new TF1("funz1","[0]*x+[1]",0.,7.22);

	funz1->SetParameter(0,1.);
	funz1->SetParameter(1,0.);

  funz1->SetLineColor(3);


  punti->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di liberta': " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;

TF1 *funz2 = new TF1("funz2","[0]*x+[1]+[2]*pow(x,2)",0.,10.);

	funz2->SetParameter(0,1.);
	funz2->SetParameter(1,0.);
  funz2->SetParameter(2,0.1);

  funz2->SetLineColor(2);


  punti->Fit(funz2,"RM+");
  cout << "X^2: " << funz2->GetChisquare() << ", gradi di liberta': " << funz2->GetNDF() << " (p-value: " << funz2->GetProb() << ")." << endl;

/*TF1 *funz3 = new TF1("funz2","[0]*x+[1]+[2]*pow(x,2)+[3]*pow(x,3)",0.,10.);

	funz3->SetParameter(0,1.);
	funz3->SetParameter(1,0.);
  funz3->SetParameter(2,0.1);

  funz3->SetLineColor(1);


  punti->Fit(funz3,"RM+");
  cout << "X^2: " << funz3->GetChisquare() << ", gradi di liberta': " << funz3->GetNDF() << " (p-value: " << funz3->GetProb() << ")." << endl;
*/
}



