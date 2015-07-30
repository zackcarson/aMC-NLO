#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <TH1.h>
#include <math.h>
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "TMath.h"

void lheplot() {
	
	Double_t m, px, py, pz, pt, p, et, e, eta, phi, wgt,
	am, apx, apy, apz, apt, ap, aet, ae, aeta, aphi, awgt,
	tdeltaphi, bdeltaphi;
	Int_t status, id, aid, astatus;
	
//	gStyle->SetOptStat(0); //Removes statistics legend
	gStyle->SetLineScalePS(1.0);
	
	
	TFile * f = new TFile("tree.root");  //Opens up the previously created tree_ttbb.root file

	TTree * tree = (TTree * )f->Get("tree"); //Grab the Tree
	
	tree->SetBranchAddress("m",&m);
	tree->SetBranchAddress("p",&p);
	tree->SetBranchAddress("pt", &pt);
	tree->SetBranchAddress("e",&e);
	tree->SetBranchAddress("et",&et);
	tree->SetBranchAddress("eta",&eta);
	tree->SetBranchAddress("phi",&phi);
	tree->SetBranchAddress("px",&px);
	tree->SetBranchAddress("py",&py);
	tree->SetBranchAddress("pz",&pz);
	tree->SetBranchAddress("wgt",&wgt);
	tree->SetBranchAddress("status", &status);
	tree->SetBranchAddress("id", &id);
	tree->SetBranchAddress("ap",&ap);
	tree->SetBranchAddress("apt", &apt);
	tree->SetBranchAddress("ae",&ae);
	tree->SetBranchAddress("aet",&aet);
	tree->SetBranchAddress("aeta",&aeta);
	tree->SetBranchAddress("aphi",&aphi);
	tree->SetBranchAddress("apx",&apx);
	tree->SetBranchAddress("apy",&apy);
	tree->SetBranchAddress("apz",&apz);
	tree->SetBranchAddress("awgt",&awgt);
	tree->SetBranchAddress("astatus", &astatus);
	tree->SetBranchAddress("aid", &aid);




	

	// PLOTTING BOTTOM //
	
	if(tree->GetEntries() != 0) { //Only plot if it is non-empty
		
	TCanvas * canb = new TCanvas("canb","canb",0,0,1800,800);
	
	TH1D * hbp = new TH1D("Bottom Total Momentum","hbp",sqrt(tree->GetEntries()),floor(tree->GetMinimum("p")),ceil(tree->GetMaximum("p")));
	TH1D * hbpt = new TH1D("Bottom Transverse Momentum","hbpt",sqrt(tree->GetEntries()), floor(tree->GetMinimum("pt")),ceil(tree->GetMaximum("pt")));
	TH1D * hbe = new TH1D("Bottom Total Energy","hbe",sqrt(tree->GetEntries()),floor(tree->GetMinimum("e")),ceil(tree->GetMaximum("e")));
	TH1D * hbet = new TH1D("Bottom Transverse Energy","hbet",sqrt(tree->GetEntries()),floor(tree->GetMinimum("et")),ceil(tree->GetMaximum("et")));
	TH1D * hbeta = new TH1D("Bottom Pseudorapidity","hbeta",sqrt(tree->GetEntries()),-9,9); 
	TH1D * hbphi = new TH1D("Bottom Azimuthal Angle","hbphi",sqrt(tree->GetEntries()),-4,4);
	
	hbp->Sumw2(); 
	hbpt->Sumw2();
	hbe->Sumw2();
	hbet->Sumw2();
	hbeta->Sumw2();
	hbphi->Sumw2();
	
	for(Long64_t i = 0; i < tree->GetEntries(); i++) {   
		tree->GetEntry(i);
		if(status == 1 && id == 5) { //only plot if it is a final state particle
		hbp->Fill(p);
		hbpt->Fill(pt);
		hbe->Fill(e);
		hbet->Fill(et);
		hbeta->Fill(eta);
		hbphi->Fill(phi);
	}
}
	
	TH1D * hbpt2 = (TH1D*)hbpt->Clone("hbpt_errors"); 
	TH1D * hbp2 = (TH1D*)hbp->Clone("hbp_errors");
	TH1D * hbet2 = (TH1D*)hbet->Clone("hbet_errors");
	TH1D * hbe2 = (TH1D*)hbe->Clone("hbe_errors");
	TH1D * hbeta2 = (TH1D*)hbeta->Clone("hbeta_errors");
	TH1D * hbphi2 = (TH1D*)hbphi->Clone("hbphi_errors");
	
	TLegend * legbPT = new TLegend(0.78,.67,.98,0.77); 
	TLegend * legbP = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbET = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbE = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbETA = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbPHI = new TLegend(0.78,.67,.98,0.77);
	
	legbPT->AddEntry(hbpt,"Bottom Quarks","f");
	legbP->AddEntry(hbp,"Bottom Quarks","f");
	legbET->AddEntry(hbet,"Bottom Quarks","f");
	legbE->AddEntry(hbe,"Bottom Quarks","f");
	legbETA->AddEntry(hbeta,"Bottom Quarks","f");
	legbPHI->AddEntry(hbphi,"Bottom Quarks","f");
	legbPT->AddEntry(hbpt2,"Uncertainty","f");
	legbP->AddEntry(hbp2,"Uncertainty","f");
	legbET->AddEntry(hbet2,"Uncertainty","f");
	legbE->AddEntry(hbe2,"Uncertainty","f");
	legbETA->AddEntry(hbeta2,"Uncertainty","f");
	legbPHI->AddEntry(hbphi2,"Uncertainty","f");
	
	hbpt->GetXaxis()->SetTitle("b    p_{T} [GeV]");   
	hbp->GetXaxis()->SetTitle("b    p [GeV]");
	hbet->GetXaxis()->SetTitle("b    E_{T} [GeV]");
	hbe->GetXaxis()->SetTitle("b    E [GeV]");
	hbeta->GetXaxis()->SetTitle("b    #eta");
	hbphi->GetXaxis()->SetTitle("b    #phi");
	hbpt->GetYaxis()->SetTitle("Number of Events");
	hbp->GetYaxis()->SetTitle("Number of Events");
	hbet->GetYaxis()->SetTitle("Number of Events");
	hbe->GetYaxis()->SetTitle("Number of Events");
	hbeta->GetYaxis()->SetTitle("Number of Events");
	hbphi->GetYaxis()->SetTitle("Number of Events");
	hbpt->SetTitle("Transverse Momentum");
	hbp->SetTitle("Total Momentum");
	hbet->SetTitle("Transverse Energy");
	hbe->SetTitle("Total Energy");
	hbphi->SetTitle("Azimuthal Angle");
	hbeta->SetTitle("Pseudorapidity");
	hbpt->SetFillColor(kGray);
	hbp->SetFillColor(kGray);
	hbet->SetFillColor(kGray);
	hbe->SetFillColor(kGray);
	hbeta->SetFillColor(kGray);
	hbphi->SetFillColor(kGray);
	hbpt->SetLineColor(kBlack);
	hbp->SetLineColor(kBlack);
	hbet->SetLineColor(kBlack);
	hbe->SetLineColor(kBlack);
	hbeta->SetLineColor(kBlack);
	hbphi->SetLineColor(kBlack);
	hbpt->SetMarkerSize(0);
	hbp->SetMarkerSize(0);
	hbet->SetMarkerSize(0);
	hbe->SetMarkerSize(0);
	hbeta->SetMarkerSize(0);
	hbphi->SetMarkerSize(0);
	hbpt2->SetFillStyle(3154);
	hbp2->SetFillStyle(3154);
	hbet2->SetFillStyle(3154);
	hbe2->SetFillStyle(3154);
	hbeta2->SetFillStyle(3154);
	hbphi2->SetFillStyle(3154);
	hbpt2->SetFillColor(kOrange+10);
	hbp2->SetFillColor(kOrange+10);
	hbet2->SetFillColor(kOrange+10);
	hbe2->SetFillColor(kOrange+10);
	hbeta2->SetFillColor(kOrange+10);
	hbphi2->SetFillColor(kOrange+10);
	hbpt2->SetMarkerSize(0);
	hbp2->SetMarkerSize(0);
	hbet2->SetMarkerSize(0);
	hbe2->SetMarkerSize(0);
	hbeta2->SetMarkerSize(0);
	hbphi->SetMarkerSize(0);
	
	hbp->Rebin(30); 
	hbpt->Rebin(30); 
	hbe->Rebin(30); 
	hbet->Rebin(30); 
	hbeta->Rebin(30); 
	hbphi->Rebin(30); 
	hbp2->Rebin(30); 
	hbpt2->Rebin(30); 
	hbe2->Rebin(30); 
	hbet2->Rebin(30); 
	hbeta2->Rebin(30); 
	hbphi2->Rebin(30);
	
	
	canb->Divide(3,2,.01,.01); 
	
	canb->cd(1)->SetLogy();  
	
	hbpt->Draw("hist");
	hbpt2->Draw("e2 same");
	legbPT->Draw();


	canb->cd(4)->SetLogy();

	hbp->Draw("hist");
	hbp2->Draw("e2 same");
	legbP->Draw();
	
	
	canb->cd(2)->SetLogy();

	hbet->Draw("hist");
	hbet2->Draw("e2 same");
	legbET->Draw();
	

	canb->cd(5)->SetLogy();

	hbe->Draw("hist");
	hbe2->Draw("e2 same");
	legbE->Draw();


	canb->cd(3)->SetLogy();

	hbeta->Draw("hist");
	hbeta2->Draw("e2 same");
	legbETA->Draw();


	canb->cd(6)->SetLogy();

	hbphi->Draw("hist");
	hbphi2->Draw("e2 same");
	legbPHI->Draw();

	canb->SaveAs("bottom.pdf"); 
	
}






// PLOTTING BOTTOM BAR //
	
	if(tree->GetEntries() != 0) { //Only plot if it is non-empty
		
	TCanvas * canbb = new TCanvas("canbb","canbb",0,0,1800,800);
	
	TH1D * hbbp = new TH1D("Anti-Bottom Total Momentum","hbbp",sqrt(tree->GetEntries()),floor(tree->GetMinimum("aap")),ceil(tree->GetMaximum("ap")));
	TH1D * hbbpt = new TH1D("Anti-Bottom Transverse Momentum","hbbpt",sqrt(tree->GetEntries()), floor(tree->GetMinimum("apt")),ceil(tree->GetMaximum("apt")));
	TH1D * hbbe = new TH1D("Anti-Bottom Total Energy","hbbe",sqrt(tree->GetEntries()),floor(tree->GetMinimum("ae")),ceil(tree->GetMaximum("ae")));
	TH1D * hbbet = new TH1D("Anti-Bottom Transverse Energy","hbbet",sqrt(tree->GetEntries()),floor(tree->GetMinimum("aet")),ceil(tree->GetMaximum("aet")));
	TH1D * hbbeta = new TH1D("Anti-Bottom Pseudorapidity","hbbeta",sqrt(tree->GetEntries()),-9,9); 
	TH1D * hbbphi = new TH1D("Anti-Bottom Azimuthal Angle","hbbphi",sqrt(tree->GetEntries()),-4,4);
	
	hbbp->Sumw2(); 
	hbbpt->Sumw2();
	hbbe->Sumw2();
	hbbet->Sumw2();
	hbbeta->Sumw2();
	hbbphi->Sumw2();
	
	for(Long64_t i = 0; i < tree->GetEntries(); i++) {   
		tree->GetEntry(i);
		if(status == 1 && id == -5) { //only plot if it is a final state particle
		hbbp->Fill(ap);
		hbbpt->Fill(apt);
		hbbe->Fill(ae);
		hbbet->Fill(aet);
		hbbeta->Fill(aeta);
		hbbphi->Fill(aphi);
	}
}
	
	TH1D * hbbpt2 = (TH1D*)hbbpt->Clone("hbbpt_errors"); 
	TH1D * hbbp2 = (TH1D*)hbbp->Clone("hbbp_errors");
	TH1D * hbbet2 = (TH1D*)hbbet->Clone("hbbet_errors");
	TH1D * hbbe2 = (TH1D*)hbbe->Clone("hbbe_errors");
	TH1D * hbbeta2 = (TH1D*)hbbeta->Clone("hbbeta_errors");
	TH1D * hbbphi2 = (TH1D*)hbbphi->Clone("hbbphi_errors");
	
	TLegend * legbbPT = new TLegend(0.78,.67,.98,0.77); 
	TLegend * legbbP = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbbET = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbbE = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbbETA = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbbPHI = new TLegend(0.78,.67,.98,0.77);
	
	legbbPT->AddEntry(hbbpt,"Anti-Bottom Quarks","f");
	legbbP->AddEntry(hbbp,"Anti-Bottom Quarks","f");
	legbbET->AddEntry(hbbet,"Anti-Bottom Quarks","f");
	legbbE->AddEntry(hbbe,"Anti-Bottom Quarks","f");
	legbbETA->AddEntry(hbbeta,"Anti-Bottom Quarks","f");
	legbbPHI->AddEntry(hbbphi,"Anti-Bottom Quarks","f");
	legbbPT->AddEntry(hbbpt2,"Uncertainty","f");
	legbbP->AddEntry(hbbp2,"Uncertainty","f");
	legbbET->AddEntry(hbbet2,"Uncertainty","f");
	legbbE->AddEntry(hbbe2,"Uncertainty","f");
	legbbETA->AddEntry(hbbeta2,"Uncertainty","f");
	legbbPHI->AddEntry(hbbphi2,"Uncertainty","f");
	
	hbbpt->GetXaxis()->SetTitle("#bar{b}    p_{T} [GeV]");   
	hbbp->GetXaxis()->SetTitle("#bar{b}    p [GeV]");
	hbbet->GetXaxis()->SetTitle("#bar{b}    E_{T} [GeV]");
	hbbe->GetXaxis()->SetTitle("#bar{b}    E [GeV]");
	hbbeta->GetXaxis()->SetTitle("#bar{b}    #eta");
	hbbphi->GetXaxis()->SetTitle("#bar{b}    #phi");
	hbbpt->GetYaxis()->SetTitle("Number of Events");
	hbbp->GetYaxis()->SetTitle("Number of Events");
	hbbet->GetYaxis()->SetTitle("Number of Events");
	hbbe->GetYaxis()->SetTitle("Number of Events");
	hbbeta->GetYaxis()->SetTitle("Number of Events");
	hbbphi->GetYaxis()->SetTitle("Number of Events");
	hbbpt->SetTitle("Transverse Momentum");
	hbbp->SetTitle("Total Momentum");
	hbbet->SetTitle("Transverse Energy");
	hbbe->SetTitle("Total Energy");
	hbbphi->SetTitle("Azimuthal Angle");
	hbbeta->SetTitle("Pseudorapidity");
	hbbpt->SetFillColor(kGray);
	hbbp->SetFillColor(kGray);
	hbbet->SetFillColor(kGray);
	hbbe->SetFillColor(kGray);
	hbbeta->SetFillColor(kGray);
	hbbphi->SetFillColor(kGray);
	hbbpt->SetLineColor(kBlack);
	hbbp->SetLineColor(kBlack);
	hbbet->SetLineColor(kBlack);
	hbbe->SetLineColor(kBlack);
	hbbeta->SetLineColor(kBlack);
	hbbphi->SetLineColor(kBlack);
	hbbpt->SetMarkerSize(0);
	hbbp->SetMarkerSize(0);
	hbbet->SetMarkerSize(0);
	hbbe->SetMarkerSize(0);
	hbbeta->SetMarkerSize(0);
	hbbphi->SetMarkerSize(0);
	hbbpt2->SetFillStyle(3154);
	hbbp2->SetFillStyle(3154);
	hbbet2->SetFillStyle(3154);
	hbbe2->SetFillStyle(3154);
	hbbeta2->SetFillStyle(3154);
	hbbphi2->SetFillStyle(3154);
	hbbpt2->SetFillColor(kOrange+10);
	hbbp2->SetFillColor(kOrange+10);
	hbbet2->SetFillColor(kOrange+10);
	hbbe2->SetFillColor(kOrange+10);
	hbbeta2->SetFillColor(kOrange+10);
	hbbphi2->SetFillColor(kOrange+10);
	hbbpt2->SetMarkerSize(0);
	hbbp2->SetMarkerSize(0);
	hbbet2->SetMarkerSize(0);
	hbbe2->SetMarkerSize(0);
	hbbeta2->SetMarkerSize(0);
	hbbphi->SetMarkerSize(0);
	
	hbbp->Rebin(30); 
	hbbpt->Rebin(30); 
	hbbe->Rebin(30); 
	hbbet->Rebin(30); 
	hbbeta->Rebin(30); 
	hbbphi->Rebin(30); 
	hbbp2->Rebin(30); 
	hbbpt2->Rebin(30); 
	hbbe2->Rebin(30); 
	hbbet2->Rebin(30); 
	hbbeta2->Rebin(30); 
	hbbphi2->Rebin(30);
	
	
	canbb->Divide(3,2,.01,.01); 
	
	canbb->cd(1)->SetLogy();  
	
	hbbpt->Draw("hist");
	hbbpt2->Draw("e2 same");
	legbbPT->Draw();


	canbb->cd(4)->SetLogy();

	hbbp->Draw("hist");
	hbbp2->Draw("e2 same");
	legbbP->Draw();
	
	
	canbb->cd(2)->SetLogy();

	hbbet->Draw("hist");
	hbbet2->Draw("e2 same");
	legbbET->Draw();
	

	canbb->cd(5)->SetLogy();

	hbbe->Draw("hist");
	hbbe2->Draw("e2 same");
	legbbE->Draw();


	canbb->cd(3)->SetLogy();

	hbbeta->Draw("hist");
	hbbeta2->Draw("e2 same");
	legbbETA->Draw();


	canbb->cd(6)->SetLogy();

	hbbphi->Draw("hist");
	hbbphi2->Draw("e2 same");
	legbbPHI->Draw();

	canbb->SaveAs("anti-bottom.pdf"); 
	
}



	

	
	// PLOTTING BOTTOM AND BOTTOM BAR //
	
	if(tree->GetEntries() != 0) { //Only plot if it is non-empty
		
	TCanvas * canbbb = new TCanvas("canbbb","canbbb",0,0,1800,800);
	
	TH1D * hbbbp = new TH1D("b + #bar{b} Total Momentum","hbbbp",sqrt(tree->GetEntries()),floor(tree->GetMinimum("p")),ceil(tree->GetMaximum("p")));
	TH1D * hbbbpt = new TH1D("b + #bar{b} Transverse Momentum","hbbbpt",sqrt(tree->GetEntries()), floor(tree->GetMinimum("pt")),ceil(tree->GetMaximum("pt")));
	TH1D * hbbbe = new TH1D("b + #bar{b} Total Energy","hbbbe",sqrt(tree->GetEntries()),floor(tree->GetMinimum("e")),ceil(tree->GetMaximum("e")));
	TH1D * hbbbet = new TH1D("b + #bar{b} Transverse Energy","hbbbet",sqrt(tree->GetEntries()),floor(tree->GetMinimum("et")),ceil(tree->GetMaximum("et")));
	TH1D * hbbbeta = new TH1D("b + #bar{b} Pseudorapidity","hbbbeta",sqrt(tree->GetEntries()),-9,9); 
	TH1D * hbbbphi = new TH1D("b + #bar{b} Azimuthal Angle","hbbbphi",sqrt(tree->GetEntries()),-4,4);
	
	hbbbp->Sumw2(); 
	hbbbpt->Sumw2();
	hbbbe->Sumw2();
	hbbbet->Sumw2();
	hbbbeta->Sumw2();
	hbbbphi->Sumw2();
	
	for(Long64_t i = 0; i < tree->GetEntries(); i++) {   
		tree->GetEntry(i);
		if(status == 1 && id == 5) { //only plot if it is a final state particle
		hbbbp->Fill(p);
		hbbbpt->Fill(pt);
		hbbbe->Fill(e);
		hbbbet->Fill(et);
		hbbbeta->Fill(eta);
		hbbbphi->Fill(phi);
	}
	if(status == 1 && id == -5) {
		hbbbp->Fill(ap);
		hbbbpt->Fill(apt);
		hbbbe->Fill(ae);
		hbbbet->Fill(aet);
		hbbbeta->Fill(aeta);
		hbbbphi->Fill(aphi);
	}
}

	
	TH1D * hbbbpt2 = (TH1D*)hbbbpt->Clone("hbbbpt_errors"); 
	TH1D * hbbbp2 = (TH1D*)hbbbp->Clone("hbbbp_errors");
	TH1D * hbbbet2 = (TH1D*)hbbbet->Clone("hbbbet_errors");
	TH1D * hbbbe2 = (TH1D*)hbbbe->Clone("hbbbe_errors");
	TH1D * hbbbeta2 = (TH1D*)hbbbeta->Clone("hbbbeta_errors");
	TH1D * hbbbphi2 = (TH1D*)hbbbphi->Clone("hbbbphi_errors");
	
	TLegend * legbbbPT = new TLegend(0.78,.67,.98,0.77); 
	TLegend * legbbbP = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbbbET = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbbbE = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbbbETA = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbbbPHI = new TLegend(0.78,.67,.98,0.77);
	
	legbbbPT->AddEntry(hbbbpt,"b + #bar{b} Quarks","f");
	legbbbP->AddEntry(hbbbp,"b + #bar{b} Quarks","f");
	legbbbET->AddEntry(hbbbet,"b + #bar{b} Quarks","f");
	legbbbE->AddEntry(hbbbe,"b + #bar{b} Quarks","f");
	legbbbETA->AddEntry(hbbbeta,"b + #bar{b} Quarks","f");
	legbbbPHI->AddEntry(hbbbphi,"b + #bar{b} Quarks","f");
	legbbbPT->AddEntry(hbbbpt2,"Uncertainty","f");
	legbbbP->AddEntry(hbbbp2,"Uncertainty","f");
	legbbbET->AddEntry(hbbbet2,"Uncertainty","f");
	legbbbE->AddEntry(hbbbe2,"Uncertainty","f");
	legbbbETA->AddEntry(hbbbeta2,"Uncertainty","f");
	legbbbPHI->AddEntry(hbbbphi2,"Uncertainty","f");
	
	hbbbpt->GetXaxis()->SetTitle("b + #bar{b}    p_{T} [GeV]");   
	hbbbp->GetXaxis()->SetTitle("b + #bar{b}    p [GeV]");
	hbbbet->GetXaxis()->SetTitle("b + #bar{b}    E_{T} [GeV]");
	hbbbe->GetXaxis()->SetTitle("b + #bar{b}    E [GeV]");
	hbbbeta->GetXaxis()->SetTitle("b + #bar{b}    #eta");
	hbbbphi->GetXaxis()->SetTitle("b + #bar{b}    #phi");
	hbbbpt->GetYaxis()->SetTitle("Number of Events");
	hbbbp->GetYaxis()->SetTitle("Number of Events");
	hbbbet->GetYaxis()->SetTitle("Number of Events");
	hbbbe->GetYaxis()->SetTitle("Number of Events");
	hbbbeta->GetYaxis()->SetTitle("Number of Events");
	hbbbphi->GetYaxis()->SetTitle("Number of Events");
	hbbbpt->SetTitle("Transverse Momentum");
	hbbbp->SetTitle("Total Momentum");
	hbbbet->SetTitle("Transverse Energy");
	hbbbe->SetTitle("Total Energy");
	hbbbphi->SetTitle("Azimuthal Angle");
	hbbbeta->SetTitle("Pseudorapidity");
	hbbbpt->SetFillColor(kGray);
	hbbbp->SetFillColor(kGray);
	hbbbet->SetFillColor(kGray);
	hbbbe->SetFillColor(kGray);
	hbbbeta->SetFillColor(kGray);
	hbbbphi->SetFillColor(kGray);
	hbbbpt->SetLineColor(kBlack);
	hbbbp->SetLineColor(kBlack);
	hbbbet->SetLineColor(kBlack);
	hbbbe->SetLineColor(kBlack);
	hbbbeta->SetLineColor(kBlack);
	hbbbphi->SetLineColor(kBlack);
	hbbbpt->SetMarkerSize(0);
	hbbbp->SetMarkerSize(0);
	hbbbet->SetMarkerSize(0);
	hbbbe->SetMarkerSize(0);
	hbbbeta->SetMarkerSize(0);
	hbbbphi->SetMarkerSize(0);
	hbbbpt2->SetFillStyle(3154);
	hbbbp2->SetFillStyle(3154);
	hbbbet2->SetFillStyle(3154);
	hbbbe2->SetFillStyle(3154);
	hbbbeta2->SetFillStyle(3154);
	hbbbphi2->SetFillStyle(3154);
	hbbbpt2->SetFillColor(kOrange+10);
	hbbbp2->SetFillColor(kOrange+10);
	hbbbet2->SetFillColor(kOrange+10);
	hbbbe2->SetFillColor(kOrange+10);
	hbbbeta2->SetFillColor(kOrange+10);
	hbbbphi2->SetFillColor(kOrange+10);
	hbbbpt2->SetMarkerSize(0);
	hbbbp2->SetMarkerSize(0);
	hbbbet2->SetMarkerSize(0);
	hbbbe2->SetMarkerSize(0);
	hbbbeta2->SetMarkerSize(0);
	hbbbphi->SetMarkerSize(0);
	
	hbbbp->Rebin(30); 
	hbbbpt->Rebin(30); 
	hbbbe->Rebin(30); 
	hbbbet->Rebin(30); 
	hbbbeta->Rebin(30); 
	hbbbphi->Rebin(30); 
	hbbbp2->Rebin(30); 
	hbbbpt2->Rebin(30); 
	hbbbe2->Rebin(30); 
	hbbbet2->Rebin(30); 
	hbbbeta2->Rebin(30); 
	hbbbphi2->Rebin(30);
	
	
	canbbb->Divide(3,2,.01,.01); 
	
	canbbb->cd(1)->SetLogy();  
	
	hbbbpt->Draw("hist");
	hbbbpt2->Draw("e2 same");
	legbbbPT->Draw();


	canbbb->cd(4)->SetLogy();

	hbbbp->Draw("hist");
	hbbbp2->Draw("e2 same");
	legbbbP->Draw();
	
	
	canbbb->cd(2)->SetLogy();

	hbbbet->Draw("hist");
	hbbbet2->Draw("e2 same");
	legbbbET->Draw();
	

	canbbb->cd(5)->SetLogy();

	hbbbe->Draw("hist");
	hbbbe2->Draw("e2 same");
	legbbbE->Draw();


	canbbb->cd(3)->SetLogy();

	hbbbeta->Draw("hist");
	hbbbeta2->Draw("e2 same");
	legbbbETA->Draw();


	canbbb->cd(6)->SetLogy();

	hbbbphi->Draw("hist");
	hbbbphi2->Draw("e2 same");
	legbbbPHI->Draw();

	canbbb->SaveAs("bottom_anti-bottom.pdf"); 
	
}








		// PLOTTING TOP//

if(tree->GetEntries() != 0) {
	
	TCanvas * cant = new TCanvas("cant","cant",0,0,1800,800); //Repeat the same as above for top
	
	TH1D * htp = new TH1D("Top Total Momentum","htp",sqrt(tree->GetEntries()),floor(tree->GetMinimum("p")),ceil(tree->GetMaximum("p")));
	TH1D * htpt = new TH1D("Top Transverse Momentum","htpt",sqrt(tree->GetEntries()), floor(tree->GetMinimum("pt")),ceil(tree->GetMaximum("pt")));
	TH1D * hte = new TH1D("Top Total Energy","hte",sqrt(tree->GetEntries()),floor(tree->GetMinimum("e")),ceil(tree->GetMaximum("e")));
	TH1D * htet = new TH1D("Top Transverse Energy","htet",sqrt(tree->GetEntries()),floor(tree->GetMinimum("et")),ceil(tree->GetMaximum("et")));
	TH1D * hteta = new TH1D("Top Pseudorapidity","hteta",sqrt(tree->GetEntries()),-9,9);
	TH1D * htphi = new TH1D("Top Azimuthal Angle","htphi",sqrt(tree->GetEntries()),-4,4);
	
	htp->Sumw2(); 
	htpt->Sumw2();
	hte->Sumw2();
	htet->Sumw2();
	hteta->Sumw2();
	htphi->Sumw2();
	
	for(Long64_t i = 0; i < tree->GetEntries(); i++) {   
		tree->GetEntry(i);
		if(status == 1 && id == 6) { //only plot if it is a final state particle
		htp->Fill(p);
		htpt->Fill(pt);
		hte->Fill(e);
		htet->Fill(et);
		hteta->Fill(eta);
		htphi->Fill(phi);
	}
}
	
	TH1D * htpt2 = (TH1D*)htpt->Clone("htpt_errors"); 
	TH1D * htp2 = (TH1D*)htp->Clone("htp_errors");
	TH1D * htet2 = (TH1D*)htet->Clone("htet_errors");
	TH1D * hte2 = (TH1D*)hte->Clone("hte_errors");
	TH1D * hteta2 = (TH1D*)hteta->Clone("hteta_errors");
	TH1D * htphi2 = (TH1D*)htphi->Clone("htphi_errors");
	
	TLegend * legtPT = new TLegend(0.78,.67,.98,0.77); 
	TLegend * legtP = new TLegend(0.78,.67,.98,0.77);
	TLegend * legtET = new TLegend(0.78,.67,.98,0.77);
	TLegend * legtE = new TLegend(0.78,.67,.98,0.77);
	TLegend * legtETA = new TLegend(0.78,.67,.98,0.77);
	TLegend * legtPHI = new TLegend(0.78,.67,.98,0.77);
	legtPT->AddEntry(htpt,"Top Quarks","f");
	legtP->AddEntry(htp,"Top Quarks","f");
	legtET->AddEntry(htet,"Top Quarks","f");
	legtE->AddEntry(hte,"Top Quarks","f");
	legtETA->AddEntry(hteta,"Top Quarks","f");
	legtPHI->AddEntry(htphi,"Top Quarks","f");
	legtPT->AddEntry(htpt2,"Uncertainty","f");
	legtP->AddEntry(htp2,"Uncertainty","f");
	legtET->AddEntry(htet2,"Uncertainty","f");
	legtE->AddEntry(hte2,"Uncertainty","f");
	legtETA->AddEntry(hteta2,"Uncertainty","f");
	legtPHI->AddEntry(htphi2,"Uncertainty","f");
	
	htpt->GetXaxis()->SetTitle("t    p_{T} [GeV]");   
	htp->GetXaxis()->SetTitle("t    p [GeV]");
	htet->GetXaxis()->SetTitle("t    E_{T} [GeV]");
	hte->GetXaxis()->SetTitle("t    E [GeV]");
	hteta->GetXaxis()->SetTitle("t    #eta");
	htphi->GetXaxis()->SetTitle("t    #phi");
	htpt->GetYaxis()->SetTitle("Number of Events");
	htp->GetYaxis()->SetTitle("Number of Events");
	htet->GetYaxis()->SetTitle("Number of Events");
	hte->GetYaxis()->SetTitle("Number of Events");
	hteta->GetYaxis()->SetTitle("Number of Events");
	htphi->GetYaxis()->SetTitle("Number of Events");
	htpt->SetTitle("Transverse Momentum");
	htp->SetTitle("Total Momentum");
	htet->SetTitle("Transverse Energy");
	hte->SetTitle("Total Energy");
	htphi->SetTitle("Azimuthal Angle");
	hteta->SetTitle("Pseudorapidity");
	htpt->SetFillColor(kGray);
	htp->SetFillColor(kGray);
	htet->SetFillColor(kGray);
	hte->SetFillColor(kGray);
	hteta->SetFillColor(kGray);
	htphi->SetFillColor(kGray);
	htpt->SetLineColor(kBlack);
	htp->SetLineColor(kBlack);
	htet->SetLineColor(kBlack);
	hte->SetLineColor(kBlack);
	hteta->SetLineColor(kBlack);
	htphi->SetLineColor(kBlack);
	htpt->SetMarkerSize(0);
	htp->SetMarkerSize(0);
	htet->SetMarkerSize(0);
	hte->SetMarkerSize(0);
	hteta->SetMarkerSize(0);
	htphi->SetMarkerSize(0);
	htpt2->SetFillStyle(3154);
	htp2->SetFillStyle(3154);
	htet2->SetFillStyle(3154);
	hte2->SetFillStyle(3154);
	hteta2->SetFillStyle(3154);
	htphi2->SetFillStyle(3154);
	htpt2->SetFillColor(kOrange+10);
	htp2->SetFillColor(kOrange+10);
	htet2->SetFillColor(kOrange+10);
	hte2->SetFillColor(kOrange+10);
	hteta2->SetFillColor(kOrange+10);
	htphi2->SetFillColor(kOrange+10);
	htpt2->SetMarkerSize(0);
	htp2->SetMarkerSize(0);
	htet2->SetMarkerSize(0);
	hte2->SetMarkerSize(0);
	hteta2->SetMarkerSize(0);
	htphi->SetMarkerSize(0);
	
	htp->Rebin(30); 
	htpt->Rebin(30); 
	hte->Rebin(30); 
	htet->Rebin(30); 
	hteta->Rebin(30); 
	htphi->Rebin(30); 
	htp2->Rebin(30); 
	htpt2->Rebin(30); 
	hte2->Rebin(30); 
	htet2->Rebin(30); 
	hteta2->Rebin(30); 
	htphi2->Rebin(30);
	
	cant->Divide(3,2,.01,.01); 
	
	cant->cd(1)->SetLogy();  
	
	htpt->Draw("hist");
	htpt2->Draw("e2 same");
	legtPT->Draw();


	cant->cd(4)->SetLogy();

	htp->Draw("hist");
	htp2->Draw("e2 same");
	legtP->Draw();
	
	
	cant->cd(2)->SetLogy();

	htet->Draw("hist");
	htet2->Draw("e2 same");
	legtET->Draw();
	

	cant->cd(5)->SetLogy();

	hte->Draw("hist");
	hte2->Draw("e2 same");
	legtE->Draw();


	cant->cd(3)->SetLogy();
	
	hteta->Draw("hist");
	hteta2->Draw("e2 same");
	legtETA->Draw();


	cant->cd(6)->SetLogy();

	htphi->Draw("hist");
	htphi2->Draw("e2 same");
	legtPHI->Draw(); 
 
	cant->SaveAs("top.pdf");
	
}





// PLOTTING ANTI TOP //
		
if(tree->GetEntries() != 0) {
	
	TCanvas * cantb = new TCanvas("cantb","cantb",0,0,1800,800); //Repeat the same as above for top
	
	TH1D * htbp = new TH1D("Anti-Top Total Momentum","htbp",sqrt(tree->GetEntries()),floor(tree->GetMinimum("ap")),ceil(tree->GetMaximum("ap")));
	TH1D * htbpt = new TH1D("Anti-Top Transverse Momentum","htbpt",sqrt(tree->GetEntries()), floor(tree->GetMinimum("apt")),ceil(tree->GetMaximum("apt")));
	TH1D * htbe = new TH1D("Anti-Top Total Energy","htbe",sqrt(tree->GetEntries()),floor(tree->GetMinimum("ae")),ceil(tree->GetMaximum("ae")));
	TH1D * htbet = new TH1D("Anti-Top Transverse Energy","htbet",sqrt(tree->GetEntries()),floor(tree->GetMinimum("aet")),ceil(tree->GetMaximum("aet")));
	TH1D * htbeta = new TH1D("Anti-Top Pseudorapidity","htbeta",sqrt(tree->GetEntries()),-9,9);
	TH1D * htbphi = new TH1D("Anti-Top Azimuthal Angle","htbphi",sqrt(tree->GetEntries()),-4,4);
	
	htbp->Sumw2(); 
	htbpt->Sumw2();
	htbe->Sumw2();
	htbet->Sumw2();
	htbeta->Sumw2();
	htbphi->Sumw2();
	
	for(Long64_t i = 0; i < tree->GetEntries(); i++) {   
		tree->GetEntry(i);
		if(status == 1 && id == -6) { //only plot if it is a final state particle
		htbp->Fill(ap);
		htbpt->Fill(apt);
		htbe->Fill(ae);
		htbet->Fill(aet);
		htbeta->Fill(aeta);
		htbphi->Fill(aphi);
	}
}
	
	TH1D * htbpt2 = (TH1D*)htbpt->Clone("htbpt_errors"); 
	TH1D * htbp2 = (TH1D*)htbp->Clone("htbp_errors");
	TH1D * htbet2 = (TH1D*)htbet->Clone("htbet_errors");
	TH1D * htbe2 = (TH1D*)htbe->Clone("htbe_errors");
	TH1D * htbeta2 = (TH1D*)htbeta->Clone("htbeta_errors");
	TH1D * htbphi2 = (TH1D*)htbphi->Clone("htbphi_errors");
	
	TLegend * legtbPT = new TLegend(0.78,.67,.98,0.77); 
	TLegend * legtbP = new TLegend(0.78,.67,.98,0.77);
	TLegend * legtbET = new TLegend(0.78,.67,.98,0.77);
	TLegend * legtbE = new TLegend(0.78,.67,.98,0.77);
	TLegend * legtbETA = new TLegend(0.78,.67,.98,0.77);
	TLegend * legtbPHI = new TLegend(0.78,.67,.98,0.77);
	legtbPT->AddEntry(htbpt,"Anti-Top Quarks","f");
	legtbP->AddEntry(htbp,"Anti-Top Quarks","f");
	legtbET->AddEntry(htbet,"Anti-Top Quarks","f");
	legtbE->AddEntry(htbe,"Anti-Top Quarks","f");
	legtbETA->AddEntry(htbeta,"Anti-Top Quarks","f");
	legtbPHI->AddEntry(htbphi,"Anti-Top Quarks","f");
	legtbPT->AddEntry(htbpt2,"Uncertainty","f");
	legtbP->AddEntry(htbp2,"Uncertainty","f");
	legtbET->AddEntry(htbet2,"Uncertainty","f");
	legtbE->AddEntry(htbe2,"Uncertainty","f");
	legtbETA->AddEntry(htbeta2,"Uncertainty","f");
	legtbPHI->AddEntry(htbphi2,"Uncertainty","f");
	 
	htbpt->GetXaxis()->SetTitle("#bar{t}    p_{T} [GeV]");   
	htbp->GetXaxis()->SetTitle("#bar{t}    p [GeV]");
	htbet->GetXaxis()->SetTitle("#bar{t}    E_{T} [GeV]");
	htbe->GetXaxis()->SetTitle("#bar{t}    E [GeV]");
	htbeta->GetXaxis()->SetTitle("#bar{t}    #eta");
	htbphi->GetXaxis()->SetTitle("#bar{t}    #phi");
	htbpt->GetYaxis()->SetTitle("Number of Events");
	htbp->GetYaxis()->SetTitle("Number of Events");
	htbet->GetYaxis()->SetTitle("Number of Events");
	htbe->GetYaxis()->SetTitle("Number of Events");
	htbeta->GetYaxis()->SetTitle("Number of Events");
	htbphi->GetYaxis()->SetTitle("Number of Events");
	htbpt->SetTitle("Transverse Momentum");
	htbp->SetTitle("Total Momentum");
	htbet->SetTitle("Transverse Energy");
	htbe->SetTitle("Total Energy");
	htbphi->SetTitle("Azimuthal Angle");
	htbeta->SetTitle("Pseudorapidity");
	htbpt->SetFillColor(kGray);
	htbp->SetFillColor(kGray);
	htbet->SetFillColor(kGray);
	htbe->SetFillColor(kGray);
	htbeta->SetFillColor(kGray);
	htbphi->SetFillColor(kGray);
	htbpt->SetLineColor(kBlack);
	htbp->SetLineColor(kBlack);
	htbet->SetLineColor(kBlack);
	htbe->SetLineColor(kBlack);
	htbeta->SetLineColor(kBlack);
	htbphi->SetLineColor(kBlack);
	htbpt->SetMarkerSize(0);
	htbp->SetMarkerSize(0);
	htbet->SetMarkerSize(0);
	htbe->SetMarkerSize(0);
	htbeta->SetMarkerSize(0);
	htbphi->SetMarkerSize(0);
	htbpt2->SetFillStyle(3154);
	htbp2->SetFillStyle(3154);
	htbet2->SetFillStyle(3154);
	htbe2->SetFillStyle(3154);
	htbeta2->SetFillStyle(3154);
	htbphi2->SetFillStyle(3154);
	htbpt2->SetFillColor(kOrange+10);
	htbp2->SetFillColor(kOrange+10);
	htbet2->SetFillColor(kOrange+10);
	htbe2->SetFillColor(kOrange+10);
	htbeta2->SetFillColor(kOrange+10);
	htbphi2->SetFillColor(kOrange+10);
	htbpt2->SetMarkerSize(0);
	htbp2->SetMarkerSize(0);
	htbet2->SetMarkerSize(0);
	htbe2->SetMarkerSize(0);
	htbeta2->SetMarkerSize(0);
	htbphi->SetMarkerSize(0);
	
	htbp->Rebin(30); 
	htbpt->Rebin(30); 
	htbe->Rebin(30); 
	htbet->Rebin(30); 
	htbeta->Rebin(30); 
	htbphi->Rebin(30); 
	htbp2->Rebin(30); 
	htbpt2->Rebin(30); 
	htbe2->Rebin(30); 
	htbet2->Rebin(30); 
	htbeta2->Rebin(30); 
	htbphi2->Rebin(30);
	
	cantb->Divide(3,2,.01,.01); 
	
	cantb->cd(1)->SetLogy();  
	
	htbpt->Draw("hist");
	htbpt2->Draw("e2 same");
	legtbPT->Draw();


	cantb->cd(4)->SetLogy();

	htbp->Draw("hist");
	htbp2->Draw("e2 same");
	legtbP->Draw();
	
	
	cantb->cd(2)->SetLogy();

	htbet->Draw("hist");
	htbet2->Draw("e2 same");
	legtbET->Draw();
	

	cantb->cd(5)->SetLogy();

	htbe->Draw("hist");
	htbe2->Draw("e2 same");
	legtbE->Draw();


	cantb->cd(3)->SetLogy();
	
	htbeta->Draw("hist");
	htbeta2->Draw("e2 same");
	legtbETA->Draw();


	cantb->cd(6)->SetLogy();

	htbphi->Draw("hist");
	htbphi2->Draw("e2 same");
	legtbPHI->Draw(); 
 
	cantb->SaveAs("anti-top.pdf");
	
}





		// PLOTTING TOP + ANTI TOP //
		
if(tree->GetEntries() != 0) {
	
	TCanvas * canttb = new TCanvas("canttb","canttb",0,0,1800,800); //Repeat the same as above for top
	
	TH1D * httbp = new TH1D("t + #bar{t} Total Momentum","httbp",sqrt(tree->GetEntries()),floor(tree->GetMinimum("p")),ceil(tree->GetMaximum("p")));
	TH1D * httbpt = new TH1D("t + #bar{t} Transverse Momentum","httbpt",sqrt(tree->GetEntries()), floor(tree->GetMinimum("pt")),ceil(tree->GetMaximum("pt")));
	TH1D * httbe = new TH1D("t + #bar{t} Total Energy","httbe",sqrt(tree->GetEntries()),floor(tree->GetMinimum("e")),ceil(tree->GetMaximum("e")));
	TH1D * httbet = new TH1D("t + #bar{t} Transverse Energy","httbet",sqrt(tree->GetEntries()),floor(tree->GetMinimum("et")),ceil(tree->GetMaximum("et")));
	TH1D * httbeta = new TH1D("t + #bar{t} Pseudorapidity","httbeta",sqrt(tree->GetEntries()),-9,9);
	TH1D * httbphi = new TH1D("t + #bar{t} Azimuthal Angle","httbphi",sqrt(tree->GetEntries()),-4,4);
	
	httbp->Sumw2(); 
	httbpt->Sumw2();
	httbe->Sumw2();
	httbet->Sumw2();
	httbeta->Sumw2();
	httbphi->Sumw2();
	
	for(Long64_t i = 0; i < tree->GetEntries(); i++) {   
		tree->GetEntry(i);
		if(status == 1 && id == 6) { //only plot if it is a final state particle
		httbp->Fill(p);
		httbpt->Fill(pt);
		httbe->Fill(e);
		httbet->Fill(et);
		httbeta->Fill(eta);
		httbphi->Fill(phi);
	}
		if(status == 1 && id == -6) { //only plot if it is a final state particle
		httbp->Fill(ap);
		httbpt->Fill(apt);
		httbe->Fill(ae);
		httbet->Fill(aet);
		httbeta->Fill(aeta);
		httbphi->Fill(aphi);
	}
}
	
	TH1D * httbpt2 = (TH1D*)httbpt->Clone("httbpt_errors"); 
	TH1D * httbp2 = (TH1D*)httbp->Clone("httbp_errors");
	TH1D * httbet2 = (TH1D*)httbet->Clone("httbet_errors");
	TH1D * httbe2 = (TH1D*)httbe->Clone("httbe_errors");
	TH1D * httbeta2 = (TH1D*)httbeta->Clone("httbeta_errors");
	TH1D * httbphi2 = (TH1D*)httbphi->Clone("httbphi_errors");
	
	TLegend * legttbPT = new TLegend(0.78,.67,.98,0.77); 
	TLegend * legttbP = new TLegend(0.78,.67,.98,0.77);
	TLegend * legttbET = new TLegend(0.78,.67,.98,0.77);
	TLegend * legttbE = new TLegend(0.78,.67,.98,0.77);
	TLegend * legttbETA = new TLegend(0.78,.67,.98,0.77);
	TLegend * legttbPHI = new TLegend(0.78,.67,.98,0.77);
	legttbPT->AddEntry(httbpt,"t + #bar{t} Quarks","f");
	legttbP->AddEntry(httbp,"t + #bar{t} Quarks","f");
	legttbET->AddEntry(httbet,"t + #bar{t} Quarks","f");
	legttbE->AddEntry(httbe,"t + #bar{t} Quarks","f");
	legttbETA->AddEntry(httbeta,"t + #bar{t} Quarks","f");
	legttbPHI->AddEntry(httbphi,"t + #bar{t} Quarks","f");
	legttbPT->AddEntry(httbpt2,"Uncertainty","f");
	legttbP->AddEntry(httbp2,"Uncertainty","f");
	legttbET->AddEntry(httbet2,"Uncertainty","f");
	legttbE->AddEntry(httbe2,"Uncertainty","f");
	legttbETA->AddEntry(httbeta2,"Uncertainty","f");
	legttbPHI->AddEntry(httbphi2,"Uncertainty","f");
	
	httbpt->GetXaxis()->SetTitle("t + #bar{t}    p_{T} [GeV]");   
	httbp->GetXaxis()->SetTitle("t + #bar{t}    p [GeV]");
	httbet->GetXaxis()->SetTitle("t + #bar{t}    E_{T} [GeV]");
	httbe->GetXaxis()->SetTitle("t + #bar{t}    E [GeV]");
	httbeta->GetXaxis()->SetTitle("t + #bar{t}    #eta");
	httbphi->GetXaxis()->SetTitle("t + #bar{t}    #phi");
	httbpt->GetYaxis()->SetTitle("Number of Events");
	httbp->GetYaxis()->SetTitle("Number of Events");
	httbet->GetYaxis()->SetTitle("Number of Events");
	httbe->GetYaxis()->SetTitle("Number of Events");
	httbeta->GetYaxis()->SetTitle("Number of Events");
	httbphi->GetYaxis()->SetTitle("Number of Events");
	httbpt->SetTitle("Transverse Momentum");
	httbp->SetTitle("Total Momentum");
	httbet->SetTitle("Transverse Energy");
	httbe->SetTitle("Total Energy");
	httbphi->SetTitle("Azimuthal Angle");
	httbeta->SetTitle("Pseudorapidity");
	httbpt->SetFillColor(kGray);
	httbp->SetFillColor(kGray);
	httbet->SetFillColor(kGray);
	httbe->SetFillColor(kGray);
	httbeta->SetFillColor(kGray);
	httbphi->SetFillColor(kGray);
	httbpt->SetLineColor(kBlack);
	httbp->SetLineColor(kBlack);
	httbet->SetLineColor(kBlack);
	httbe->SetLineColor(kBlack);
	httbeta->SetLineColor(kBlack);
	httbphi->SetLineColor(kBlack);
	httbpt->SetMarkerSize(0);
	httbp->SetMarkerSize(0);
	httbet->SetMarkerSize(0);
	httbe->SetMarkerSize(0);
	httbeta->SetMarkerSize(0);
	httbphi->SetMarkerSize(0);
	httbpt2->SetFillStyle(3154);
	httbp2->SetFillStyle(3154);
	httbet2->SetFillStyle(3154);
	httbe2->SetFillStyle(3154);
	httbeta2->SetFillStyle(3154);
	httbphi2->SetFillStyle(3154);
	httbpt2->SetFillColor(kOrange+10);
	httbp2->SetFillColor(kOrange+10);
	httbet2->SetFillColor(kOrange+10);
	httbe2->SetFillColor(kOrange+10);
	httbeta2->SetFillColor(kOrange+10);
	httbphi2->SetFillColor(kOrange+10);
	httbpt2->SetMarkerSize(0);
	httbp2->SetMarkerSize(0);
	httbet2->SetMarkerSize(0);
	httbe2->SetMarkerSize(0);
	httbeta2->SetMarkerSize(0);
	httbphi->SetMarkerSize(0);
	
	httbp->Rebin(30); 
	httbpt->Rebin(30); 
	httbe->Rebin(30); 
	httbet->Rebin(30); 
	httbeta->Rebin(30); 
	httbphi->Rebin(30); 
	httbp2->Rebin(30); 
	httbpt2->Rebin(30); 
	httbe2->Rebin(30); 
	httbet2->Rebin(30); 
	httbeta2->Rebin(30); 
	httbphi2->Rebin(30);
	
	canttb->Divide(3,2,.01,.01); 
	
	canttb->cd(1)->SetLogy();  
	
	httbpt->Draw("hist");
	httbpt2->Draw("e2 same");
	legttbPT->Draw();


	canttb->cd(4)->SetLogy();

	httbp->Draw("hist");
	httbp2->Draw("e2 same");
	legttbP->Draw();
	
	
	canttb->cd(2)->SetLogy();

	httbet->Draw("hist");
	httbet2->Draw("e2 same");
	legttbET->Draw();
	

	canttb->cd(5)->SetLogy();

	httbe->Draw("hist");
	httbe2->Draw("e2 same");
	legttbE->Draw();


	canttb->cd(3)->SetLogy();
	
	httbeta->Draw("hist");
	httbeta2->Draw("e2 same");
	legttbETA->Draw();


	canttb->cd(6)->SetLogy();

	httbphi->Draw("hist");
	httbphi2->Draw("e2 same");
	legttbPHI->Draw(); 
 
	canttb->SaveAs("top_anti-top.pdf");
	
}









	//PLOTTING bottom-pair comparism //
		
	TCanvas * canbp = new TCanvas("canbp","canbp",0,0,1800,1800); //bottom pair comparison
	
	TH1D * hbdeltaeta = new TH1D("Bottom-Pair #Delta#eta","hbdeltaeta",sqrt(tree->GetEntries()),-15,15);
	TH1D * hbdeltaphi = new TH1D("Bottom-Pair #Delta#phi","hbdeltaphi",sqrt(tree->GetEntries()),0,3.5);
	TH1D * hbdeltar = new TH1D("Bottom-Pair #DeltaR","hbdeltar",sqrt(tree->GetEntries()),0,15);
	TH1D * hbinmass = new TH1D("Bottom-Pair Invariant Mass","hbinmass",sqrt(tree->GetEntries()),0,1600);
	
	hbdeltaeta->Sumw2(); 
	hbdeltaphi->Sumw2();
	hbdeltar->Sumw2();
	hbinmass->Sumw2();

	for(Long64_t i = 0; i < tree->GetEntries(); i++) {   
		tree->GetEntry(i);
		if(status == 1 && id == 5) { //only plot if they are final state particles
		hbdeltaeta->Fill((eta-aeta));
		bdeltaphi=abs(phi-aphi);
		if(bdeltaphi >= M_PI) {
			hbdeltaphi->Fill((2*M_PI-bdeltaphi));
		}
		else {
			hbdeltaphi->Fill((bdeltaphi));
		}
		hbdeltar->Fill(sqrt(pow((eta-aeta),2)+pow((phi-aphi),2)));
		hbinmass->Fill(sqrt((pow(m,2)+pow(am,2))+2*(e*ae-px*apx-py*apy-pz*apz))); 
	}
	}
	
	TH1D * hbdeltaeta2 = (TH1D*)hbdeltaeta->Clone("hbdeltaeta_errors"); 
	TH1D * hbdeltaphi2 = (TH1D*)hbdeltaphi->Clone("hbdeltaphi_errors");
	TH1D * hbdeltar2 = (TH1D*)hbdeltar->Clone("hbdeltar_errors");
	TH1D * hbinmass2 = (TH1D*)hbinmass->Clone("hbinmass_errors");

	
	TLegend * legbdeltaeta = new TLegend(0.78,.67,.98,0.77); 
	TLegend * legbdeltaphi = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbdeltar = new TLegend(0.78,.67,.98,0.77);
	TLegend * legbinmass = new TLegend(0.78,.67,.98,0.77);
	legbdeltaeta->AddEntry(hbdeltaeta,"Bottom-Anti-Bottom Pairs","f");
	legbdeltaphi->AddEntry(hbdeltaphi,"Bottom-Anti-Bottom Pairs","f");
	legbdeltar->AddEntry(hbdeltar,"Bottom-Anti-Bottom Pairs","f");
	legbinmass->AddEntry(hbinmass,"Bottom-Anti-Bottom Pairs","f");
	legbdeltaeta->AddEntry(hbdeltaeta2,"Uncertainty","f");
	legbdeltaphi->AddEntry(hbdeltaphi2,"Uncertainty","f");
	legbdeltar->AddEntry(hbdeltar2,"Uncertainty","f");
	legbinmass->AddEntry(hbinmass2,"Uncertainty","f");

	
	hbdeltaeta->GetXaxis()->SetTitle("b & #bar{b}    #Delta#eta");   
	hbdeltaphi->GetXaxis()->SetTitle("b & #bar{b}    #Delta#phi");
	hbdeltar->GetXaxis()->SetTitle("b & #bar{b}    #DeltaR");
	hbinmass->GetXaxis()->SetTitle("b & #bar{b}    M [GeV]");
	hbdeltaeta->GetYaxis()->SetTitle("Number of Events");
	hbdeltaphi->GetYaxis()->SetTitle("Number of Events");
	hbdeltar->GetYaxis()->SetTitle("Number of Events");
	hbinmass->GetYaxis()->SetTitle("Number of Events");
	hbdeltaeta->SetTitle("#Delta#eta");
	hbdeltaphi->SetTitle("#Delta#phi");
	hbdeltar->SetTitle("#DeltaR");
	hbinmass->SetTitle("Invariant Mass");
	hbdeltaeta->SetFillColor(kGray);
	hbdeltaphi->SetFillColor(kGray);
	hbdeltar->SetFillColor(kGray);
	hbinmass->SetFillColor(kGray);
	hbdeltaeta->SetLineColor(kBlack);
	hbdeltaphi->SetLineColor(kBlack);
	hbdeltar->SetLineColor(kBlack);
	hbinmass->SetLineColor(kBlack);
	hbdeltaeta->SetMarkerSize(0);
	hbdeltaphi->SetMarkerSize(0);
	hbdeltar->SetMarkerSize(0);
	hbinmass->SetMarkerSize(0);
	hbdeltaeta2->SetFillStyle(3154);
	hbdeltaphi2->SetFillStyle(3154);
	hbdeltar2->SetFillStyle(3154);
	hbinmass2->SetFillStyle(3154);
	hbdeltaeta2->SetFillColor(kOrange+10);
	hbdeltaphi2->SetFillColor(kOrange+10);
	hbdeltar2->SetFillColor(kOrange+10);
	hbinmass2->SetFillColor(kOrange+10);
	hbdeltaeta2->SetMarkerSize(0);
	hbdeltaphi2->SetMarkerSize(0);
	hbdeltar2->SetMarkerSize(0);
	hbinmass2->SetMarkerSize(0);
	
	hbdeltaeta->Rebin(30);
	hbdeltaphi->Rebin(30);
	hbdeltar->Rebin(30);
	hbinmass->Rebin(30);
	hbdeltaeta2->Rebin(30);
	hbdeltaphi2->Rebin(30);
	hbdeltar2->Rebin(30);
	hbinmass2->Rebin(30);
	
	canbp->Divide(2,2,.01,.01); 
	
	
	canbp->cd(1)->SetLogy();  
	
	hbdeltaeta->Draw("hist");
	hbdeltaeta2->Draw("e2 same");
	legbdeltaeta->Draw();


	canbp->cd(2)->SetLogy();

	hbdeltaphi->Draw("hist");
	hbdeltaphi2->Draw("e2 same");
	legbdeltaphi->Draw();
	
	
	canbp->cd(3)->SetLogy();

	hbdeltar->Draw("hist");
	hbdeltar2->Draw("e2 same");
	legbdeltar->Draw();
	

	canbp->cd(4)->SetLogy();

	hbinmass->Draw("hist");
	hbinmass2->Draw("e2 same");
	legbinmass->Draw();

	canbp->SaveAs("bottom_pair.pdf"); 
	
	
	
	
		//PLOTTING top-pair comparism //
		
	TCanvas * cantp = new TCanvas("cantp","cantp",0,0,1800,1800); //bottom pair comparison
	
	TH1D * htdeltaeta = new TH1D("Top-Pair #Delta#eta","htdeltaeta",sqrt(tree->GetEntries()),-15,15);
	TH1D * htdeltaphi = new TH1D("Top-Pair #Delta#phi","htdeltaphi",sqrt(tree->GetEntries()),0,3.5);
	TH1D * htdeltar = new TH1D("Top-Pair #DeltaR","htdeltar",sqrt(tree->GetEntries()),0,15);
	TH1D * htinmass = new TH1D("Top-Pair Invariant Mass","htinmass",sqrt(tree->GetEntries()),0,2500);
	
	htdeltaeta->Sumw2(); 
	htdeltaphi->Sumw2();
	htdeltar->Sumw2();
	htinmass->Sumw2();

	for(Long64_t i = 0; i < tree->GetEntries(); i++) {   
		tree->GetEntry(i);
		if(status == 1 && id == 6) { //only plot if they are final state particles
		htdeltaeta->Fill((eta-aeta));
		tdeltaphi=abs(phi-aphi);
		if((tdeltaphi) >= M_PI) {
			htdeltaphi->Fill((2*M_PI-tdeltaphi));
		}
		else {
			htdeltaphi->Fill((tdeltaphi));
		}
		htdeltar->Fill(sqrt(pow((eta-aeta),2)+pow((phi-aphi),2)));
		htinmass->Fill(sqrt((pow(m,2)+pow(am,2))+2*(e*ae-px*apx-py*apy-pz*apz))); 
	}
	}
	
	TH1D * htdeltaeta2 = (TH1D*)htdeltaeta->Clone("htdeltaeta_errors"); 
	TH1D * htdeltaphi2 = (TH1D*)htdeltaphi->Clone("htdeltaphi_errors");
	TH1D * htdeltar2 = (TH1D*)htdeltar->Clone("htdeltar_errors");
	TH1D * htinmass2 = (TH1D*)htinmass->Clone("htinmass_errors");

	
	TLegend * legtdeltaeta = new TLegend(0.78,.67,.98,0.77); 
	TLegend * legtdeltaphi = new TLegend(0.78,.67,.98,0.77);
	TLegend * legtdeltar = new TLegend(0.78,.67,.98,0.77);
	TLegend * legtinmass = new TLegend(0.78,.67,.98,0.77);
	legtdeltaeta->AddEntry(htdeltaeta,"Top-Anti-Top Pairs","f");
	legtdeltaphi->AddEntry(htdeltaphi,"Top-Anti-Top Pairs","f");
	legtdeltar->AddEntry(htdeltar,"Top-Anti-Top Pairs","f");
	legtinmass->AddEntry(htinmass,"Top-Anti-Top Pairs","f");
	legtdeltaeta->AddEntry(htdeltaeta2,"Uncertainty","f");
	legtdeltaphi->AddEntry(htdeltaphi2,"Uncertainty","f");
	legtdeltar->AddEntry(htdeltar2,"Uncertainty","f");
	legtinmass->AddEntry(htinmass2,"Uncertainty","f");

	
	htdeltaeta->GetXaxis()->SetTitle("t & #bar{t}    #Delta#eta");   
	htdeltaphi->GetXaxis()->SetTitle("t & #bar{t}    #Delta#phi");
	htdeltar->GetXaxis()->SetTitle("t & #bar{t}    #DeltaR");
	htinmass->GetXaxis()->SetTitle("t & #bar{t}    M [GeV]");
	htdeltaeta->GetYaxis()->SetTitle("Number of Events");
	htdeltaphi->GetYaxis()->SetTitle("Number of Events");
	htdeltar->GetYaxis()->SetTitle("Number of Events");
	htinmass->GetYaxis()->SetTitle("Number of Events");
	htdeltaeta->SetTitle("#Delta#eta");
	htdeltaphi->SetTitle("#Delta#phi");
	htdeltar->SetTitle("#DeltaR");
	htinmass->SetTitle("Invariant Mass");
	htdeltaeta->SetFillColor(kGray);
	htdeltaphi->SetFillColor(kGray);
	htdeltar->SetFillColor(kGray);
	htinmass->SetFillColor(kGray);
	htdeltaeta->SetLineColor(kBlack);
	htdeltaphi->SetLineColor(kBlack);
	htdeltar->SetLineColor(kBlack);
	htinmass->SetLineColor(kBlack);
	htdeltaeta->SetMarkerSize(0);
	htdeltaphi->SetMarkerSize(0);
	htdeltar->SetMarkerSize(0);
	htinmass->SetMarkerSize(0);
	htdeltaeta2->SetFillStyle(3154);
	htdeltaphi2->SetFillStyle(3154);
	htdeltar2->SetFillStyle(3154);
	htinmass2->SetFillStyle(3154);
	htdeltaeta2->SetFillColor(kOrange+10);
	htdeltaphi2->SetFillColor(kOrange+10);
	htdeltar2->SetFillColor(kOrange+10);
	htinmass2->SetFillColor(kOrange+10);
	htdeltaeta2->SetMarkerSize(0);
	htdeltaphi2->SetMarkerSize(0);
	htdeltar2->SetMarkerSize(0);
	htinmass2->SetMarkerSize(0);

	htdeltaeta->Rebin(30);
	htdeltaphi->Rebin(30);
	htdeltar->Rebin(30);
	htinmass->Rebin(30);
	htdeltaeta2->Rebin(30);
	htdeltaphi2->Rebin(30);
	htdeltar2->Rebin(30);
	htinmass2->Rebin(30);
	
	cantp->Divide(2,2,.01,.01); 
	
	
	cantp->cd(1)->SetLogy();  
	
	htdeltaeta->Draw("hist");
	htdeltaeta2->Draw("e2 same");
	legtdeltaeta->Draw();


	cantp->cd(2)->SetLogy();

	htdeltaphi->Draw("hist");
	htdeltaphi2->Draw("e2 same");
	legtdeltaphi->Draw();
	
	
	cantp->cd(3)->SetLogy();

	htdeltar->Draw("hist");
	htdeltar2->Draw("e2 same");
	legtdeltar->Draw();
	

	cantp->cd(4)->SetLogy();

	htinmass->Draw("hist");
	htinmass2->Draw("e2 same");
	legtinmass->Draw();

	cantp->SaveAs("top_pair.pdf");

}
