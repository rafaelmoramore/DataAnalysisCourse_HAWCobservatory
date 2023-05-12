void T4_71() // Este macro calcula la frecuencia de coincidencias cuádruples por WCD para evento 0 y 999 (utilizando un archivo escalar distinto al del ejercicio 5, para 4 nuevos subruns)
{
// --------- Archivos fuentes (4 subruns) e indicación de cada árbol ----------------------------
TFile *file = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/tdcscaler_run009776_00692.root");
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

// ----------- Creación de Histograma --------------------------------------
TH1F *h_0=new TH1F("Coinc. cuadruples (Ev 0)","Conteo de coincidencias cuadruples por WCD (primer evento)", 300,0.5,300.5);

TH1F *h_0_2=new TH1F("Coinc. cuadruples (Ev 0)-2","Conteo de coincidencias cuadruples por WCD (primer evento)", 300,0.5,300.5);

TH1F *h_0_3=new TH1F("Coinc. cuadruples (Ev 0)-3","Conteo de coincidencias cuadruples por WCD (primer evento)", 300,0.5,300.5);

TH1F *h_0_4=new TH1F("Coinc. cuadruples (Ev 0)-4","Conteo de coincidencias cuadruples por WCD (primer evento)", 300,0.5,300.5);

   THStack *hs = new THStack("hs","");
   
// ------------ Ciclo for para primer evento con subrun 1 --------------------------------
arbol->GetEntry(0);
for(Int_t i=0; i<nTanksInfo; i++) // ciclo for para eventos
   {
      h_0->Fill(channelIDInfo[i], (multiplicity4CountInfo[i])/24.0); //se llena el histograma 
   }

// ------------ Ciclo for para primer evento con subrun 2 --------------------------------
arbol2->GetEntry(0);
for(Int_t i=0; i<nTanksInfo; i++) // ciclo for para eventos
   {
      h_0_2->Fill(channelIDInfo[i], (multiplicity4CountInfo[i])/24.0); //se llena el histograma 
   }

// ------------ Ciclo for para primer evento con subrun 3 --------------------------------
arbol3->GetEntry(0);
for(Int_t i=0; i<nTanksInfo; i++) // ciclo for para eventos
   {
      h_0_3->Fill(channelIDInfo[i], (multiplicity4CountInfo[i])/24.0); //se llena el histograma 
   }

// ------------ Ciclo for para primer evento con subrun 4 --------------------------------
arbol4->GetEntry(0);
for(Int_t i=0; i<nTanksInfo; i++) // ciclo for para eventos
   {
      h_0_4->Fill(channelIDInfo[i], (multiplicity4CountInfo[i])/24.0); //se llena el histograma 
   }
hs->Add(h_0);
hs->Add(h_0_2);
hs->Add(h_0_3);
hs->Add(h_0_4);

// ------------- Dibujo de Histogramas --------------------------------------

   TCanvas *cs = new TCanvas("cs","cs");

h_0->SetMarkerStyle(4);
h_0->GetXaxis()->SetTitle("WCDs");
h_0->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_0->SetMarkerColor(kRed);
hs->Add(h_0);

h_0_2->SetMarkerStyle(4);
h_0_2->GetXaxis()->SetTitle("WCDs");
h_0_2->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_0_2->SetMarkerColor(kBlue);

h_0_3->SetMarkerStyle(4);
h_0_3->GetXaxis()->SetTitle("WCDs");
h_0_3->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_0_3->SetMarkerColor(kViolet);

h_0_4->SetMarkerStyle(4);
h_0_4->GetXaxis()->SetTitle("WCDs");
h_0_4->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_0_4->SetMarkerColor(kGreen);

c1->cd();
h_0->Draw("P");   // Mostrando resultados
h_0_2->Draw("SAME");   // Mostrando resultados
h_0_3->Draw("SAME");   // Mostrando resultados
h_0_4->Draw("SAME");   // Mostrando resultados


cs->Divide(2,2);
   cs->cd(1); hs->Draw("P"); //T.DrawTextNDC(.5,.95,"Default drawing option");
//   cs->cd(2); hs->Draw("nostack"); //T.DrawTextNDC(.5,.95,"Option \"nostack\"");
  // cs->cd(3); hs->Draw("nostackb"); //T.DrawTextNDC(.5,.95,"Option \"nostackb\"");
//   cs->cd(4); hs->Draw("lego1"); //T.DrawTextNDC(.5,.95,"Option \"lego1\"");
   return cs;

}
