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


using namespace std;

void multiple_lhe() {

	int files;
	string events;
//	cout << "How many events are in your repeated lhe files? (In the form 10k, 100k, etc.)" << endl;
	cin >> events;
//	cout << "How many lhe files of same size do you have?" << endl;
	cin >> files;
	
	for(i = 1; i <= files; i++) {
		 
	Double_t m, px, py, pz, pt, p, et, e, eta, phi, wgt,
	am, apx, apy, apz, ap, apt, aet, ae, aeta, aphi, awgt;
	Int_t status, id, aid, astatus;
	string line;
	int counter = 0;
	double value;
	vector <double> weight;
	vector<vector<double> > data;
	
	string in = "../lhefiles/events_" + events + "_" + to_string(i) + ".lhe";
	TString out = "../output/tree_" + events + "_" + to_string(i) + ".root";
	cout <<"Input File: " << in << " : Output File: " << out << endl;
	ifstream fin(in);
	
	while (getline(fin,line)) {
	               
    if(line == "  <event>") {
		counter++;
	}
	
	if((counter >= 1 && line.find("#aMCatNLO") != 0 && line != "  </event>" && line.find("   <wgt") == 0 && line != "  <event>" && line[15] == '1' && line[4] == 'w') || (counter >= 1 && line.find("#aMCatNLO") != 0 && line != "  </event>" && line != "  </rwgt>" && line == "  <event>" && line != "  <event>" && line[15] == '1' && line[4] == 'w')) {
		weight.push_back(stod(line.substr(line.find('>')+2, line.rfind('<')-line.find('>')-3)));
	}
	
	if((counter >= 1 && line.find("#aMCatNLO") != 0 && line != "  </event>" && line != "  </rwgt>" && line != "  <rwgt>" && line.find("   <wgt") != 0 && line[2] == ' ' && line[9] == ' ' && line != "  <event>") || (counter >= 1 && line == "  <event>" && line != "  <event>" )) {
		data.push_back(vector<double>());
        istringstream ss(line);
        while (ss >> value)
        {
            data.back().push_back(value); //enter data from text file into array
        }
	}
  }
  
	fin.close();

	
	TFile f(out,"RECREATE");    //creates a .root file to write data to.
 
    TTree * tree = new TTree("tree","Tree"); //create tree and branches
	
	tree->Branch("id",&id,"id/I");
	tree->Branch("m",&m,"m/D");
	tree->Branch("p",&p,"p/D"); 
	tree->Branch("pt",&pt,"pt/D");
	tree->Branch("e",&e,"e/D");
	tree->Branch("et",&et,"et/D");
	tree->Branch("eta",&eta,"eta/D");
	tree->Branch("phi",&phi,"phi/D");
	tree->Branch("px",&px,"px/D");
	tree->Branch("py",&py,"py/D");
	tree->Branch("pz",&pz,"pz/D");
	tree->Branch("wgt",&wgt,"wgt/D");
	tree->Branch("status",&status,"status/I");
	tree->Branch("am",&am,"am/D");
	tree->Branch("ap",&ap,"ap/D"); 
	tree->Branch("apt",&apt,"apt/D");
	tree->Branch("ae",&ae,"ae/D");
	tree->Branch("aet",&aet,"aet/D");
	tree->Branch("aeta",&aeta,"aeta/D");
	tree->Branch("aphi",&aphi,"aphi/D");
	tree->Branch("apx",&apx,"apx/D");
	tree->Branch("apy",&apy,"apy/D");
	tree->Branch("apz",&apz,"apz/D");
	tree->Branch("aid",&aid,"aid/I");
	tree->Branch("awgt",&awgt,"awgt/D");
	tree->Branch("astatus",&astatus,"astatus/I");

	for(int i = 0; i < data.size(); i++)  {     
									// Fills tree with all column entries in array.
									// ( PX = 6, PY = 7, PZ = 8, E = 9, M = 10,..., weight is in weight vector in c++ (starting at 0) notation)

		id = data[i][0];
		
		if(id >= 0) {
		m=data[i][10];
		p=sqrt(pow(data[i][6],2)+pow(data[i][7],2)+pow(data[i][8],2));
		pt=sqrt(pow(data[i][6],2)+pow(data[i][7],2));
		e=data[i][9];
		et=sqrt(pow(pt,2)+pow(m,2));
		eta=atanh(data[i][8]/p);
		px=data[i][6];
		py=data[i][7];
		pz=data[i][8];
		status=data[i][1];
		if(i < weight.size()) {
		wgt = weight[i];
	}
		if(px > 0 && py < 0) { //different depending on what quadrant of momentum space it lies in
			phi=-(atan(data[i][7]/data[i][6])-(M_PI/2));
		}
		
		else if(px < 0 && py < 0) {
			phi=-(atan(data[i][7]/data[i][6])+(M_PI/2));
		}
		
		else {
			phi=atan(data[i][7]/data[i][6]);
		}
		tree->Fill();
	}
	
	else if(id <= 0) {
		am=data[i][10];
		ap=sqrt(pow(data[i][6],2)+pow(data[i][7],2)+pow(data[i][8],2));
		apt=sqrt(pow(data[i][6],2)+pow(data[i][7],2));
		ae=data[i][9];
		aet=sqrt(pow(apt,2)+pow(am,2));
		aeta=atanh(data[i][8]/ap);
		apx=data[i][6];
		apy=data[i][7];
		apz=data[i][8];
		astatus=data[i][1];
		if(i < weight.size()) {
		awgt = weight[i];
	}
		if(apx > 0 && apy < 0) { //different depending on what quadrant of momentum space it lies in
			aphi=-(atan(data[i][7]/data[i][6])-(M_PI/2));
		}
		
		else if(apx < 0 && apy < 0) {
			aphi=-(atan(data[i][7]/data[i][6])+(M_PI/2));
		}
		
		else {
			aphi=atan(data[i][7]/data[i][6]);
		}
		tree->Fill();
	}
	}

tree->Write(); //Writes tree to output file for later use
}
}
	
