#include "iostream"
#include <map>
#include <vector>
#include <stdexcept>
#include "TColor.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TString.h"

int GetPantoneColorOfTheYear(int year){
	if (year<2000 or year>2023)
		throw std::out_of_range((const char*)Form("Pantone Color of the year not defined for year %d",year));
	std::map<int, TColor*> pantoneMap = {
	  {2000, new TColor(155./255, 183./255, 212./255)},
	  {2001, new TColor(199./255, 67./255, 117./255)},
	  {2002, new TColor(191./255, 25./255, 50./255)},
	  {2003, new TColor(123./255,196./255, 196/255)},
	  {2004, new TColor(226./255, 88./255, 62./255)},
	  {2005, new TColor(83. /255, 176./255, 174./255)},
	  {2006, new TColor(222./255,205./255, 190./255)},
	  {2007, new TColor(155./255, 27./255, 48./255)},
	  {2008, new TColor(90./255,  91./255, 159./255)},
	  {2009, new TColor(240./255,192./255, 90./255)},
	  {2010, new TColor(69./255, 181./255, 170./255)},
	  {2011, new TColor(217./255, 79./255, 112./255)},
	  {2012, new TColor(221./255, 65./255, 36./255)},
	  {2013, new TColor(0./  255,152./255, 116./255)},
	  {2014, new TColor(173./255, 94./255, 153./255)},
	  {2015, new TColor(150./255, 79./255, 76./255)},
	  {2016, new TColor(147./255,169./255, 209./255)},
	  {2017, new TColor(136./255,176./255, 75./255)},
	  {2018, new TColor(95. /255,  75./255, 139./255)},
	  {2019, new TColor(255./255,111./255, 97./255)},
	  {2020, new TColor(15./255,  76./255, 129./255)},
	  {2021, new TColor(245./255, 223./255, 77./255)}, //they choosed two colors this year but TColor(147./255,149./255, 151./255) is grey
	  {2022, new TColor(186./255, 38./255, 73./255)},
	  {2023, new TColor(102./255, 103./255, 171./255)},
	};
	return pantoneMap[year]->GetNumber();
}

void drawPantoneExampleGraph() {
  short int FirstYear = 2000;
  short int Nyears = 23;
  std::vector<double> x(Nyears);
  std::vector<double> y(Nyears);

  // Set x values from 2000 to 2020
  for (int i = 0; i <= Nyears; i++) {
    x[i] = i;
  }


  auto mg = new TMultiGraph();

  // Set line color based on the map
  for (int i = 0; i <= Nyears; i++) {
  	// Set y values to the year
  	for (int j = 0; j <= Nyears; j++) {
    		y[j] = FirstYear+i;
  	}
  	TGraph *graph = new TGraph(Nyears, &x[0], &y[0]);
	graph->SetLineColor(GetPantoneColorOfTheYear(y[0]));
  	graph->SetLineWidth(10);
	mg->Add(graph);
  }

  // Draw the graph
  TCanvas *canvas = new TCanvas("canvas", "Pantone Colors", 800, 600);
  canvas->SetGrid();
  mg->Draw("AL");
  mg->GetYaxis()->SetTitle("Year");
  mg->SetTitle("Pantone Colors of the Year");
  canvas->Update();
  canvas->SaveAs("PantoneColors.pdf","pdf");
}

int main(){
	drawPantoneExampleGraph();
}
