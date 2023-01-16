#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TCanvas.h"
#include <cmath>
#include <algorithm>
#include <iterator>

// Fit Function
double fitFunction(Double_t *x, Double_t *par) {
  return par[0]+(par[1])/(1+(x[0]/par[2]));
}
 
void TvsWfit7W()
{
  
  TFile *input = new TFile("7Whistos.root", "READ");
  
    TProfile *h1 = (TProfile*)input->Get("h1");
    TProfile *h2 = (TProfile*)input->Get("h2");
    TProfile *h3 = (TProfile*)input->Get("h3");
    TProfile *h4 = (TProfile*)input->Get("h4");
    
    h1->SetStats(0);


    TCanvas *c2 = new TCanvas("c2","Sample text", 0, 100, 700, 500);
    c2->SetFillColor(0);
    c2->SetFrameFillColor(0);
    c2->SetGrid();
    
    //Create a TF1 with range 0 to 1 and 2 parameters
    TF1 *fitFcn1 = new TF1("fitFcn1",fitFunction, 0.7, 10.5 ,3);
    TF1 *fitFcn2 = new TF1("fitFcn2",fitFunction, 0.7, 10.5 ,3);
    TF1 *fitFcn3 = new TF1("fitFcn3",fitFunction, 0.7, 10.5 ,3);
    TF1 *fitFcn4 = new TF1("fitFcn4",fitFunction, 0.7, 10.5 ,3);
    

    fitFcn1->SetLineWidth(2);
    fitFcn2->SetLineWidth(2);
    fitFcn3->SetLineWidth(2);
    fitFcn4->SetLineWidth(2);
      
    fitFcn1->SetLineColor(kBlack);
    fitFcn2->SetLineColor(kRed);
    fitFcn3->SetLineColor(kGreen);
    fitFcn4->SetLineColor(kBlue);
    
    fitFcn1->SetParameters(27,12.5,0.9);
    fitFcn2->SetParameters(18.5,38.7,0.6);
    fitFcn3->SetParameters(26.8, 25.6, 0.7);
    fitFcn4->SetParameters(24.4, 20.9, 0.7);
    
    h1->Draw("hist p");
    h2->Draw("hist p same");
    h3->Draw("hist p same");
    h4->Draw("hist p same");
    
    h1->Fit("fitFcn1", "R+");
    h2->Fit("fitFcn2", "R+");
    h3->Fit("fitFcn3", "R+");
    h4->Fit("fitFcn4", "R+");
    
    fitFcn1->Draw("same");
    fitFcn2->Draw("same");
    fitFcn3->Draw("same");
    fitFcn4->Draw("same");
    
    h1->SetMinimum(10);
    h1->SetMaximum(60);
    
    //Draw the legend;
    TLegend *legend=new TLegend(0.65,0.7,0.90,0.9);
    legend->SetTextFont(60);
    legend->SetTextSize(0.03);
    legend->AddEntry(h1,"HICOMP LD Foam Foam with 2mm hole","p");
    legend->AddEntry(h2,"HICOMP LD Foam without a hole","p");
    legend->AddEntry(h3,"AL fins 27x6.6x0.1 mm","p");
    legend->AddEntry(h4,"AL fins on 20x6.6x0.1  mm","p");
    legend->Draw("e");

    //Configuring specific display style
    //gStyle->SetOptFit(1111);
    // gStyle->SetOptStat(0);
    
    //Using TLatex to annotate the canvas
    TLatex latex;
    latex.SetTextSize(0.05);
    latex.SetTextAlign(13);  //align at top
    latex.DrawLatex(0.6,47.5,"P = 0.7W");
    //input->Close();
    
}

