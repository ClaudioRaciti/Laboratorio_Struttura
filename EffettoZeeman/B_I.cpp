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


float I[19]={0. , 0.55 , 1.05 , 1.5 , 2.08 , 2.54 , 3.03 , 3.55 , 4.13 , 4.67 , 5.26 , 6.23 , 6.69 , 7.22 , 7.64 , 8.2 , 8.65 , 9.09 , 9.57};//A
float s_I[19]={0.03 , 0.0355 , 0.0405 , 0.045 , 0.0508 , 0.0554 , 0.0603 , 0.0655 , 0.0713 , 0.0767 , 0.0826 , 0.0923 , 0.0969 , 0.1022 , 0.1064 , 0.112 , 0.1165 , 0.1209 , 0.1257};
float B[19]={8.95 , 44.6 , 78 , 109 , 152 , 185 , 215 , 248 , 285 , 318 , 355 , 418 , 446 , 477 , 503 , 535 , 559 , 580 , 601}; // mT
float s_B[19];
for (int j=0;j<19;j++){
s_B[j]=1.;//mT
}




TCanvas *grafico = new TCanvas("grafico","ciclo di isteresi, salita",200,10,600,400);
grafico->SetFillColor(0);
grafico->cd();
TGraphErrors *punti = new TGraphErrors(19,I,B,s_I,s_B);
punti->SetMarkerSize(0.7);
punti->SetMarkerStyle(21);
punti->SetTitle("ciclo di isteresi - salita");
punti->GetXaxis()->SetTitle("I [A]");
punti->GetYaxis()->SetTitle("B [mT]");
punti->Draw("AP");



cout << "SALITA";
cout<< endl << "------ tried [0]*x+[1] -------";
TF1 *funz1 = new TF1("funz1","[0]*x+[1]",0.,7.22);

	funz1->SetParameter(0,1.);
	funz1->SetParameter(1,0.);

  funz1->SetLineColor(3);


  punti->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di liberta': " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;

cout << endl << "------ tried [0]*x+[1]+[2]*pow(x,2) -------";

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
const int dim=20.;
float I_2[dim]={9.57, 9.08 , 8.55 , 8.08 , 7.45 , 6.98 , 6.54 , 5.98 , 5.59 , 5.06 , 4.6 , 4.03 , 3.55 , 3.1 , 2.45 , 1.96 , 1.6 , 1.11 , 0.45 , 0.};//A
float s_I_2[dim]={0.1257 , 0.1208 , 0.1155 , 0.1108 , 0.1045 , 0.0998 , 0.0954 , 0.0898 , 0.0859 , 0.0806 , 0.076 , 0.0703 , 0.0655 , 0.061 , 0.0545 , 0.0496 , 0.046 , 0.0411 , 0.0345 , 0.03};
float B_2[dim]={601 , 583 , 560 , 534 , 499 , 472 , 445 , 409 , 385 , 351 , 324 , 287 , 259 , 228 , 182 , 152 , 123 , 88 , 42 , 10}; // mT
float s_B_2[dim];
for (int j=0;j<dim;j++){
s_B_2[j]=1.;//mT
}




TCanvas *grafico2 = new TCanvas("grafico2","ciclo di isteresi, discesa",200,10,600,400);
grafico2->SetFillColor(0);
grafico2->cd();
TGraphErrors *punti2 = new TGraphErrors(dim,I_2,B_2,s_I_2,s_B_2);
punti2->SetMarkerSize(0.7);
punti2->SetMarkerStyle(21);
punti2->SetTitle("ciclo di isteresi - discesa");
punti2->GetXaxis()->SetTitle("I [A]");
punti2->GetYaxis()->SetTitle("B [mT]");
punti2->Draw("AP");




/*cout<< "------ tried [0]*x+[1] -------";
TF1 *funz1 = new TF1("funz1","[0]*x+[1]",0.,7.22);

	funz1->SetParameter(0,1.);
	funz1->SetParameter(1,0.);

  funz1->SetLineColor(3);


  punti->Fit(funz1,"RM+");
  cout << "X^2: " << funz1->GetChisquare() << ", gradi di liberta': " << funz1->GetNDF() << " (p-value: " << funz1->GetProb() << ")." << endl;
*/
cout << endl << "DISCESA";
cout<< endl << endl << "------ tried [0]*x+[1]+[2]*pow(x,2) -------";

	funz2->SetParameter(0,1.);
	funz2->SetParameter(1,0.);
  funz2->SetParameter(2,0.1);
  funz2->SetLineColor(2);

  punti2->Fit(funz2,"RM+");
  cout << "X^2: " << funz2->GetChisquare() << ", gradi di liberta': " << funz2->GetNDF() << " (p-value: " << funz2->GetProb() << ")." << endl;


//SALITA secondo set

const int dim=11;
float I_3[dim]={0. , 1.08 , 2.01 , 3.02 , 4.13 , 5. , 5.99 , 7.08 , 8.15 , 9.03 , 9.56};//A
float s_I_3[dim]={0.03 , 0.0408 , 0.0501 , 0.0602 , 0.0713 , 0.08 , 0.0899 , 0.1008 , 0.1115 , 0.1203 , 0.1256};
float B_3[dim]={6.9 , 79 , 144 , 213 , 284 , 346 , 405 , 473 , 535 , 582 , 604}; // mT
float s_B_3[dim];
for (int j=0;j<dim;j++){
s_B_3[j]=1.;//mT
}


TCanvas *grafico3 = new TCanvas("grafico3","ciclo di isteresi, salita",200,10,600,400);
grafico3->SetFillColor(0);
grafico3->cd();
TGraphErrors *punti3 = new TGraphErrors(dim,I_3,B_3,s_I_3,s_B_3);
punti3->SetMarkerSize(0.7);
punti3->SetMarkerStyle(21);
punti3->SetTitle("ciclo di isteresi - salita");
punti3->GetXaxis()->SetTitle("I [A]");
punti3->GetYaxis()->SetTitle("B [mT]");
punti3->Draw("AP");

cout << endl << "SALITA";
cout<< endl << endl << "------ tried [0]*x+[1]+[2]*pow(x,2) -------";

	funz2->SetParameter(0,1.);
	funz2->SetParameter(1,0.);
  funz2->SetParameter(2,0.1);
  funz2->SetLineColor(2);

  punti3->Fit(funz2,"RM+");
  cout << "X^2: " << funz2->GetChisquare() << ", gradi di liberta': " << funz2->GetNDF() << " (p-value: " << funz2->GetProb() << ")." << endl;

//DISCESA secondo set

const int dim=11;
float I_4[dim]={9.56 , 9.04 , 8.18 , 6.9 , 6.1 , 4.98 , 4.18 , 2.93 , 2.07 , 0.96 , 0.};//A
float s_I_4[dim]={0.1256 , 0.1204 , 0.1118 , 0.099 , 0.091 , 0.0798 , 0.0718 , 0.0593 , 0.0507 , 0.0396 , 0.03};
float B_4[dim]={604 , 586 , 541 , 497 , 420 , 347 , 296 , 218 , 160 , 74 , 10}; // mT
float s_B_4[dim];
for (int j=0;j<dim;j++){
s_B_4[j]=1.;//mT
}


TCanvas *grafico4 = new TCanvas("grafico4","ciclo di isteresi, discesa",200,10,600,400);
grafico4->SetFillColor(0);
grafico4->cd();
TGraphErrors *punti4 = new TGraphErrors(dim,I_4,B_4,s_I_4,s_B_4);
punti4->SetMarkerSize(0.7);
punti4->SetMarkerStyle(21);
punti4->SetTitle("ciclo di isteresi - discesa");
punti4->GetXaxis()->SetTitle("I [A]");
punti4->GetYaxis()->SetTitle("B [mT]");
punti4->Draw("AP");

cout << endl << "DISCESA";
cout<< endl << endl << "------ tried [0]*x+[1]+[2]*pow(x,2) -------";

	funz2->SetParameter(0,1.);
	funz2->SetParameter(1,0.);
  funz2->SetParameter(2,0.1);
  funz2->SetLineColor(2);

  punti4->Fit(funz2,"RM+");
  cout << "X^2: " << funz2->GetChisquare() << ", gradi di liberta': " << funz2->GetNDF() << " (p-value: " << funz2->GetProb() << ")." << endl;
  cout<< endl << "------ tried [0]*x+[1] -------"<<endl;
  
  TF1 *funz3 = new TF1("funz3","[0]*x+[1]",0.,6.2);

	funz3->SetParameter(0,69.);
	funz3->SetParameter(1,10.);

  funz3->SetLineColor(3);

  punti4->Fit(funz3,"RM+");
  cout << "X^2: " << funz3->GetChisquare() << ", gradi di liberta': " << funz3->GetNDF() << " (p-value: " << funz3->GetProb() << ")." << endl;


}



