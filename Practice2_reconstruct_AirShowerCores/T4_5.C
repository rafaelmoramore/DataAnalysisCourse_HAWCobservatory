void T4_5() // Este macro calcula la frecuencia de 2, 3 y 4 coincidencias por WCD para evento 0 y 999
{
// --------- Archivo fuente e indicación del árbol ----------------------------
TFile *file = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/tdcscaler_run009776_00692.root");
TTree *arbol =(TTree*) file->Get("XCDF");
Int_t entradas = arbol->GetEntries();

// --------- Declaración de variables y sus ramas ----------------------------
Int_t Canales = 1200; //total de PMTs sin importar si se inutiliza alguno
Int_t Tanques = 300; //total de WCD sin importar si se inutiliza alguno

ULong64_t channelIDInfo[Canales];
arbol->SetBranchAddress("scaler.channelID",channelIDInfo);

ULong64_t channelTankIDInfo[Canales]; // vector de long. Tanques 
arbol->SetBranchAddress("scaler.channelTankID",channelTankIDInfo); //ya no requiere &

//ULong64_t channelCountInfo[Canales];// repeticiones de los disparos
//arbol->SetBranchAddress("scaler.channelCount",channelCountInfo);

ULong64_t nTanksInfo; // número de tanques
arbol->SetBranchAddress("scaler.nTanks",&nTanksInfo);

ULong64_t multiplicity2CountInfo[Tanques];// coincidencias dobles
arbol->SetBranchAddress("scaler.multiplicity2Count",multiplicity2CountInfo);

ULong64_t multiplicity3CountInfo[Tanques]; // coincidencias triples
arbol->SetBranchAddress("scaler.multiplicity3Count",multiplicity3CountInfo);

ULong64_t multiplicity4CountInfo[Tanques]; // coincidencias cuádruples
arbol->SetBranchAddress("scaler.multiplicity4Count",multiplicity4CountInfo);

// ----------- Creación de Histograma --------------------------------------
TH1F *h_0_d=new TH1F("Coinc. dobles (Ev 0)","Conteo de coincidencias dobles por WCD (primer evento)", 300,0.5,300.5);
TH1F *h_999_d=new TH1F("Coinc. dobles (Ev 999)","Conteo de coincidencias dobles por WCD (ultimo evento)", 300,0.5,300.5);

TH1F *h_0_t=new TH1F("Coinc. triples (Ev 0)","Conteo de coincidencias triples por WCD (primer evento)", 300,0.5,300.5);
TH1F *h_999_t=new TH1F("Coinc. triples (Ev 999)","Conteo de coincidencias triples por WCD (ultimo evento)", 300,0.5,300.5);

TH1F *h_0_c=new TH1F("Coinc. cuadruples (Ev 0)","Conteo de coincidencias cuadruples por WCD (primer evento)", 300,0.5,300.5);
TH1F *h_999_c=new TH1F("Coinc. cuadruples (Ev 999)","Conteo de coincidencias cuadruples por WCD (ultimo evento)", 300,0.5,300.5);

// ------------ Ciclo for para primer evento con multiplicidad doble --------------------------------
arbol->GetEntry(0);
for(Int_t i=0; i<nTanksInfo; i++) // ciclo for para eventos
   {
      h_0_d->SetBinContent(channelIDInfo[i], (multiplicity2CountInfo[i])/24.0); //se llena el histograma 
   }

// ------------ Ciclo for para último evento con multiplicidad doble --------------------------------
arbol->GetEntry(999);
for(Int_t i=0; i<nTanksInfo; i++)
   {        
      h_999_d->SetBinContent(channelIDInfo[i], (multiplicity2CountInfo[i])/24.0); //se llena el histograma
   }

// ------------ Ciclo for para primer evento con multiplicidad triple --------------------------------
arbol->GetEntry(0);
for(Int_t i=0; i<nTanksInfo; i++) // ciclo for para eventos
   {
      h_0_t->SetBinContent(channelIDInfo[i], (multiplicity3CountInfo[i])/24.0); //se llena el histograma 
   }

// ------------ Ciclo for para último evento con multiplicidad triple --------------------------------
arbol->GetEntry(999);
for(Int_t i=0; i<nTanksInfo; i++)
   {        
      h_999_t->SetBinContent(channelIDInfo[i], (multiplicity3CountInfo[i])/24.0); //se llena el histograma
   }


// ------------ Ciclo for para primer evento con multiplicidad cuádruple --------------------------------
arbol->GetEntry(0);
for(Int_t i=0; i<nTanksInfo; i++) // ciclo for para eventos
   {
      h_0_c->SetBinContent(channelIDInfo[i], (multiplicity4CountInfo[i])/24.0); //se llena el histograma 
   }

// ------------ Ciclo for para último evento con multiplicidad cuádruple --------------------------------
arbol->GetEntry(999);
for(Int_t i=0; i<nTanksInfo; i++)
   {        
      h_999_c->SetBinContent(channelIDInfo[i], (multiplicity4CountInfo[i])/24.0); //se llena el histograma
   }

// ------------- Dibujo de Histogramas --------------------------------------

TCanvas *c1 = new TCanvas("c1,c1");
TCanvas *c2 = new TCanvas("c2,c2");

TCanvas *c3 = new TCanvas("c3,c3");
TCanvas *c4 = new TCanvas("c4,c4");

TCanvas *c5 = new TCanvas("c5,c5");
TCanvas *c6 = new TCanvas("c6,c6");

h_0_d->SetMarkerStyle(42);
h_0_d->SetMarkerColor(kViolet);
h_0_d->GetXaxis()->SetTitle("WCDs");
h_0_d->GetYaxis()->SetTitle("Frecuencia [kHz]");

h_999_d->SetMarkerStyle(42);
h_999_d->GetXaxis()->SetTitle("WCDs");
h_999_d->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_999_d->SetMarkerColor(kBlue);;


h_0_t->SetMarkerStyle(42);
h_0_t->GetXaxis()->SetTitle("WCDs");
h_0_t->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_0_t->SetMarkerColor(kViolet);

h_999_t->SetMarkerStyle(42);
h_999_t->GetXaxis()->SetTitle("WCDs");
h_999_t->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_999_t->SetMarkerColor(kBlue);


h_0_c->SetMarkerStyle(42);
h_0_c->GetXaxis()->SetTitle("WCDs");
h_0_c->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_0_c->SetMarkerColor(kViolet);

h_999_c->SetMarkerStyle(42);
h_999_c->GetXaxis()->SetTitle("WCDs");
h_999_c->GetYaxis()->SetTitle("Frecuencia [kHz]");
h_999_c->SetMarkerColor(kBlue);

c1->cd();
h_0_d->Draw("P");   // Mostrando resultados
c2->cd();
h_999_d->Draw("P");

c3->cd();
h_0_t->Draw("P");   // Mostrando resultados
c4->cd();
h_999_t->Draw("P");

c5->cd();
h_0_c->Draw("P");   // Mostrando resultados
c6->cd();
h_999_c->Draw("P");

//std::cout << "Las coincidencias dobles, triples y cuádruples para el evento 0 se dan con una frecuencia de " <<  << " kHz." << '\n' << endl;
//std::cout << "Las coincidencias dobles, triples y cuádruples para el evento 999 se dan con una frecuencia de " <<  << " kHz." << '\n' << endl;
}
