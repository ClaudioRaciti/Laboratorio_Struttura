#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TF1.h>
#include <iomanip>
#include <math.h>

using namespace std;


void B_unif()
{

//asse z, quindi la sonda di Hall e' al centro tra le espasioni polari e si scorre dal basso all'alto
float z[9]={0 , 0.2 , 0.4 , 0.6 , 0.8 , 1. , 1.2 , 1.4 , 1.6}; //cm
float s_z[9];
for (int j=0;j<9;j++){
s_z[j]=0.1;//cm
}
float B_z[9]={170 , 180 , 185 , 185 , 185 , 184 , 185 , 182 , 174}; // mT
float s_B_z[9];
for (int j=0;j<9;j++){
s_B_z[j]=1.;//mT
}

//asse principale, lungo la guida della lampada da claudio (porta) verso davide (finestre)
float x[15]={0. , 0.1 , 0.2 , 0.3 , 0.4 , 0.5 , 0.6 , 0.7 , 0.8 , 0.9 , 1., 1.1 , 1.2 ,	1.3 , 1.4}; //mm
float s_x[15];
for (int j=0;j<15;j++){
s_x[j]=0.1;//mm
}
float B_x[15]={167 , 178 , 182 , 184 , 185 , 185 , 185 , 185 , 184 , 185 , 185, 184 ,183 , 177 , 170}; // mT
float s_B_x[15];
for (int j=0;j<15;j++){
s_B_x[j]=1.;//mT
}

//asse secondario, quindi lungo asse ottico da parete con computer a parete con i prof
float y[14]={0. , 0.1 , 0.2 , 0.3 , 0.4 , 0.5 , 0.6 , 0.7 , 0.8 , 0.9 , 1., 1.1 , 1.2 ,	1.3}; //mm
float s_y[14];
for (int j=0;j<14;j++){
s_y[j]=0.1;//mm
}
float B_y[14]={154 , 175 , 180 , 184 , 185 , 185 , 185 , 185 , 185 , 184 , 182 , 178 , 176 , 169}; // mT
float s_B_y[14];
for (int j=0;j<14;j++){
s_B_y[j]=1.;//mT
}




TCanvas *graficoz = new TCanvas("graficoz","B_z",200,10,600,400);
graficoz->SetFillColor(0);
graficoz->cd();
TGraphErrors *punti_z = new TGraphErrors(9,z,B_z,s_z,s_B_z);
punti_z->SetMarkerSize(0.7);
punti_z->SetMarkerStyle(21);
punti_z->SetTitle("B(z)");
punti_z->GetXaxis()->SetTitle("z [cm]");
punti_z->GetYaxis()->SetTitle("B [mT]");
punti_z->Draw("ALP");

cout<< endl << "------ tried [0]*x+[1] -------";
TF1 *funz1 = new TF1("funz1","[0]*x+[1]",0.3,1.3);

	funz1->SetParameter(0,0.);
	funz1->SetParameter(1,180.);

  funz1->SetLineColor(3);


  punti_z->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di liberta': " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;


TCanvas *graficox = new TCanvas("graficox","B_x",200,10,600,400);
graficox->SetFillColor(0);
graficox->cd();
TGraphErrors *punti_x = new TGraphErrors(15,x,B_x,s_x,s_B_x);
punti_x->SetMarkerSize(0.7);
punti_x->SetMarkerStyle(21);
punti_x->SetTitle("B(x)");
punti_x->GetXaxis()->SetTitle("x [cm]");
punti_x->GetYaxis()->SetTitle("B [mT]");
punti_x->Draw("ALP");

cout<< endl << "------ tried [0]*x+[1] -------";
TF1 *funz1 = new TF1("funz1","[0]*x+[1]",0.2,1.2);

	funz1->SetParameter(0,0.);
	funz1->SetParameter(1,180.);

  funz1->SetLineColor(3);


  punti_x->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di liberta': " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;


TCanvas *graficoy = new TCanvas("graficoy","B_y",200,10,600,400);
graficoy->SetFillColor(0);
graficoy->cd();
TGraphErrors *punti_y = new TGraphErrors(14,y,B_y,s_y,s_B_y);
punti_y->SetMarkerSize(0.7);
punti_y->SetMarkerStyle(21);
punti_y->SetTitle("B(y)");
punti_y->GetXaxis()->SetTitle("y [cm]");
punti_y->GetYaxis()->SetTitle("B [mT]");
punti_y->Draw("ALP");

cout<< endl << "------ tried [0]*x+[1] -------";
TF1 *funz1 = new TF1("funz1","[0]*x+[1]",0.3,1.1);

	funz1->SetParameter(0,0.);
	funz1->SetParameter(1,180.);

  funz1->SetLineColor(3);


  punti_y->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di liberta': " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;


/*TF1 *funz1 = new TF1("funz1","[0]*x+[1]",0.,7.22);

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

