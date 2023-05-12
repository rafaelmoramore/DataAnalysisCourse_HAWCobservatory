void T4_7() // Este macro calcula la frecuencia de coincidencias cuádruples por WCD para evento 0 y 999 (utilizando un archivo escalar distinto al del ejercicio 5, para 4 nuevos subruns)
{
// --------- Archivos fuentes (4 subruns) e indicación de cada árbol ----------------------------
TFile *file = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/tdcscaler_run009776_00346.root");
TTree *arbol =(TTree*) file->Get("XCDF");

TFile *file2 = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/tdcscaler_run009776_00001.root");
TTree *arbol2 =(TTree*) file2->Get("XCDF");

TFile *file3 = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/tdcscaler_run009776_00173.root");
TTree *arbol3 =(TTree*) file3->Get("XCDF");

TFile *file4 = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/tdcscaler_run009776_00519.root");
TTree *arbol4 =(TTree*) file4->Get("XCDF");

Int_t entradas = arbol->GetEntries();

// --------- Declaración de variables y sus ramas ----------------------------
Int_t Canales = 1200; //total de PMTs sin importar si se inutiliza alguno
Int_t Tanques = 300; //total de WCD sin importar si se inutiliza alguno

ULong64_t channelIDInfo[Canales];
arbol->SetBranchAddress("scaler.channelID",channelIDInfo);

ULong64_t channelTankIDInfo[Canales]; // vector de long. Tanques 
arbol->SetBranchAddress("scaler.channelTankID",channelTankIDInfo); //ya no requiere &

ULong64_t nTanksInfo; // número de tanques
arbol->SetBranchAddress("scaler.nTanks",&nTanksInfo);

ULong64_t multiplicity4CountInfo[Tanques]; // coincidencias cuádruples
arbol->SetBranchAddress("scaler.multiplicity4Count",multiplicity4CountInfo);

// ---Para segundo subrun
ULong64_t channelIDInfo2[Canales];
arbol2->SetBranchAddress("scaler.channelID",channelIDInfo2);

ULong64_t channelTankIDInfo2[Canales]; // vector de long. Tanques 
arbol2->SetBranchAddress("scaler.channelTankID",channelTankIDInfo2); //ya no requiere &

ULong64_t nTanksInfo2; // número de tanques
arbol2->SetBranchAddress("scaler.nTanks",&nTanksInfo2);

ULong64_t multiplicity4CountInfo2[Tanques]; // coincidencias cuádruples
arbol2->SetBranchAddress("scaler.multiplicity4Count",multiplicity4CountInfo2);

// ---Para tercer subrun
ULong64_t channelIDInfo3[Canales];
arbol3->SetBranchAddress("scaler.channelID",channelIDInfo3);

ULong64_t channelTankIDInfo3[Canales]; // vector de long. Tanques 
arbol3->SetBranchAddress("scaler.channelTankID",channelTankIDInfo3); //ya no requiere &

ULong64_t nTanksInfo3; // número de tanques
arbol3->SetBranchAddress("scaler.nTanks",&nTanksInfo3);

ULong64_t multiplicity4CountInfo3[Tanques]; // coincidencias cuádruples
arbol3->SetBranchAddress("scaler.multiplicity4Count",multiplicity4CountInfo3);

// ---Para cuarto subrun
ULong64_t channelIDInfo4[Canales];
arbol4->SetBranchAddress("scaler.channelID",channelIDInfo4);

ULong64_t channelTankIDInfo4[Canales]; // vector de long. Tanques 
arbol4->SetBranchAddress("scaler.channelTankID",channelTankIDInfo4); //ya no requiere &

ULong64_t nTanksInfo4; // número de tanques
arbol4->SetBranchAddress("scaler.nTanks",&nTanksInfo4);

ULong64_t multiplicity4CountInfo4[Tanques]; // coincidencias cuádruples
arbol4->SetBranchAddress("scaler.multiplicity4Count",multiplicity4CountInfo4);
// ----------- Creación de Histograma --------------------------------------
TH1F *h_0=new TH1F("1.Subrun 346 (Ev 0)","Conteo de coincidencias cuadruples por WCD (primer evento)", 300,0.5,300.5);
TH1F *h_999=new TH1F("1.Subrun 346 (Ev 999)","Conteo de coincidencias cuadruples por WCD (ultimo evento)", 300,0.5,300.5);

TH1F *h_0_2=new TH1F("2.Subrun 1 (Ev 0)-2","Conteo de coincidencias cuadruples por WCD (primer evento)", 300,0.5,300.5);
TH1F *h_999_2=new TH1F("2.Subrun 1 (Ev 999)-2","Conteo de coincidencias cuadruples por WCD (ultimo evento)", 300,0.5,300.5);

TH1F *h_0_3=new TH1F("3. Subrun 173 (Ev 0)-3","Conteo de coincidencias cuadruples por WCD (primer evento)", 300,0.5,300.5);
TH1F *h_999_3=new TH1F("3. Subrun 173 (Ev 999)-3","Conteo de coincidencias cuadruples por WCD (ultimo evento)", 300,0.5,300.5);

TH1F *h_0_4=new TH1F("4. Subrun 519 (Ev 0)-4","Conteo de coincidencias cuadruples por WCD (primer evento)", 300,0.5,300.5);
TH1F *h_999_4=new TH1F("4. Subrun 519 (Ev 999)-4","Conteo de coincidencias cuadruples por WCD (ultimo evento)", 300,0.5,300.5);

// ------------ Ciclo for para primer evento con subrun 1 --------------------------------
arbol->GetEntry(0);
for(Int_t i=0; i<nTanksInfo; i++) // ciclo for para eventos
   {
      h_0->SetBinContent(channelIDInfo[i], (multiplicity4CountInfo[i])/24.0); //se llena el histograma 
   }

// ------------ Ciclo for para último evento con subrun 1 --------------------------------
arbol->GetEntry(999);
for(Int_t i=0; i<nTanksInfo; i++)
   {        
      h_999->SetBinContent(channelIDInfo[i], (multiplicity4CountInfo[i])/24.0); //se llena el histogr.
   }

// ------------ Ciclo for para primer evento con subrun 2 --------------------------------
arbol2->GetEntry(0);
for(Int_t i=0; i<nTanksInfo2; i++) // ciclo for para eventos
   {
    h_0_2->SetBinContent(channelIDInfo2[i], (multiplicity4CountInfo2[i])/24.0); //se llena el histogr. 
   }

// ------------ Ciclo for para último evento con subrun 2 --------------------------------
arbol2->GetEntry(999);
for(Int_t i=0; i<nTanksInfo2; i++)
   {        
    h_999_2->SetBinContent(channelIDInfo2[i], (multiplicity4CountInfo2[i])/24.0); //se llena el histogr
   }


// ------------ Ciclo for para primer evento con subrun 3 --------------------------------
arbol3->GetEntry(0);
for(Int_t i=0; i<nTanksInfo3; i++) // ciclo for para eventos
   {
      h_0_3->SetBinContent(channelIDInfo3[i], (multiplicity4CountInfo3[i])/24.0); //se llena el histogr
   }

// ------------ Ciclo for para último evento con subrun 3 --------------------------------
arbol3->GetEntry(999);
for(Int_t i=0; i<nTanksInfo3; i++)
   {        
    h_999_3->SetBinContent(channelIDInfo3[i], (multiplicity4CountInfo3[i])/24.0); //se llena el histo
   }

// ------------ Ciclo for para primer evento con subrun 4 --------------------------------
arbol4->GetEntry(0);
for(Int_t i=0; i<nTanksInfo4; i++) // ciclo for para eventos
   {
      h_0_4->SetBinContent(channelIDInfo4[i], (multiplicity4CountInfo4[i])/24.0); //se llena el histograma 
   }

// ------------ Ciclo for para último evento con subrun 4 --------------------------------
arbol4->GetEntry(999);
for(Int_t i=0; i<nTanksInfo4; i++)
  {        
  h_999_4->SetBinContent(channelIDInfo4[i], (multiplicity4CountInfo4[i])/24.0); //se llena el histogr
  }


// ------------- Dibujo de Histogramas --------------------------------------

TCanvas *c1 = new TCanvas("c1,c1");
TCanvas *c2 = new TCanvas("c2,c2");
TCanvas *c3 = new TCanvas("c3,c3");
TCanvas *c4 = new TCanvas("c4,c4");
TCanvas *c5 = new TCanvas("c5,c5");
TCanvas *c6 = new TCanvas("c6,c6");
TCanvas *c7 = new TCanvas("c7,c7");
TCanvas *c8 = new TCanvas("c8,c8");

h_0->SetMarkerStyle(4);
h_0->GetXaxis()->SetTitle("WCDs");
h_0->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_0->SetMarkerColor(kRed);

h_999->SetMarkerStyle(4);
h_999->GetXaxis()->SetTitle("WCDs");
h_999->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_999->SetMarkerColor(kRed);

h_0_2->SetMarkerStyle(4);
h_0_2->GetXaxis()->SetTitle("WCDs");
h_0_2->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_0_2->SetMarkerColor(kBlue);

h_999_2->SetMarkerStyle(4);
h_999_2->GetXaxis()->SetTitle("WCDs");
h_999_2->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_999_2->SetMarkerColor(kBlue);

h_0_3->SetMarkerStyle(4);
h_0_3->GetXaxis()->SetTitle("WCDs");
h_0_3->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_0_3->SetMarkerColor(kViolet);

h_999_3->SetMarkerStyle(4);
h_999_3->GetXaxis()->SetTitle("WCDs");
h_999_3->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_999_3->SetMarkerColor(kViolet);

h_0_4->SetMarkerStyle(4);
h_0_4->GetXaxis()->SetTitle("WCDs");
h_0_4->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_0_4->SetMarkerColor(kGreen);

h_999_4->SetMarkerStyle(4);
h_999_4->GetXaxis()->SetTitle("WCDs");
h_999_4->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_999_4->SetMarkerColor(kGreen);

c1->cd();
h_0->Draw("P");   // Mostrando resultados
c2->cd();
h_999->Draw("P");

c3->cd();
h_0_2->Draw("P");   // Mostrando resultados
c4->cd();
h_999_2->Draw("P");

c5->cd();
h_0_3->Draw("P");   // Mostrando resultados
c6->cd();
h_999_3->Draw("P");

c7->cd();
h_0_4->Draw("P");   // Mostrando resultados
c8->cd();
h_999_4->Draw("P");
}
