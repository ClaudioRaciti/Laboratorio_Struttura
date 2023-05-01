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


void fitVWork(){

float HV_work [] = {390,392,394,397,399,402,404,406,409,411,413,416,418,421,423,425,428,430,432,435,437,440,442,444,447,449,451,454,456,459,461,463,466,468,471,473,
                475,478,480,485,490,494,499,504,509,513,518,523,528,532,537,542};
float err_HV_work[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
float rate[] = {4.945975479,9.257425743,17.3019802,29.8019802,53.31683168,92.12871287,142.970297,204.8019802,267.6732673,325.3217822,377.2772277,424.6534653,483.0940594,
        524.7524752,573.3168317,644.7772277,729.009901,828.2920792,932.0792079,1028.762376,1124.80198,1185.798809,1243.884314,1286.380137,1315.562343,1290.103645,
        1336.908851,1388.131022,1403.171653,1416.545309,1407.661211,1428.451202,1434.713503,1436.219315,1452.387005,1450.253635,1458.276136,1455.654703,1461.813701,
        1466.668324,1477.749825,1479.687496,1472.192971,1487.304653,1493.811839,1490.594425,1488.845289,1483.261236,1485.308666,1477.558871,1485.01552,1480.871623};
float err_rate[] = {0.5985789766,0.6435643564,1.113861386,1.831683168,3.217821782,0.9405940594,3.861386139,2.277227723,0.9405940594,3.292079208,1.089108911,2.772277228,
            1.806930693,0.4455445545,0.9405940594,3.094059406,4.405940594,0.5198019802,1.188118812,0.4455445545,1.534653465,0.08029597548,7.273207897,0.9194934807,
            0.09995100167,3.431390083,33.73362199,2.80675581,5.044958085,1.670579807,4.239794912,6.6979231,3.387369797,2.660811575,2.337695441,5.524318216,5.712033017,
            2.391047131,9.493732978,0.06738687906,6.769993612,1.478069689,8.921427174,9.58822577,2.045740813,0.1595567978,3.043671536,2.192413099,11.26380527,
            0.436299267,6.20822548,740.4358115};

//Grafico passa alto
TCanvas *cG1f = new TCanvas("V_work","rate(V)",200,10,600,400);
// cG1f->SetLogx(1);
cG1f->SetFillColor(0);
cG1f->cd();
TMultiGraph *mg = new TMultiGraph();
TGraphErrors *gG1f = new TGraphErrors(51,HV_work,rate,err_HV_work,err_rate);
gG1f->SetMarkerSize(0.6);
gG1f->SetMarkerStyle(21);
gG1f->SetTitle("rate(V)");
gG1f->GetXaxis()->SetTitle("log(V)");
gG1f->GetYaxis()->SetTitle("rate");
gG1f->Draw("AP");

cout << "\n\n --- Ipotesi  [0] --- \n" <<endl;


float start = 470;
float stop = 540;
TF1 *funz1 = new TF1("funz1","[0]",start, stop);

float r;
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


funz1->SetParameter(0,1000.);
funz1->SetParameter(1,0.);
gG1f->Fit(funz1,"RM+");
cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << "). r ="<< r << endl;


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
retta2->Draw("same");

}



