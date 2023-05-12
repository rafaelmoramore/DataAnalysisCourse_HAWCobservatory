void T4_3() // Este macro realiza un histograma comparando el conteo de ocurrencias por PMT para el evento 0 y 999
{
// --------- Archivo fuente e indicación del árbol --------------------
TFile *file = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/tdcscaler_run009776_00692.root");
TTree *arbol =(TTree*) file->Get("XCDF");
Int_t entradas = arbol->GetEntries();

// --------- Declaración de variables y sus ramas ----------------------
Int_t Canales = 1200; //total de PMT sin importar que se inutilicen algunos cuantos

ULong64_t channelIDInfo[Canales]; //este objeto es un vector 
arbol->SetBranchAddress("scaler.channelID",channelIDInfo); //Nota de sintaxis: ya no requiere &

ULong64_t channelCountInfo[Canales]; // repeticiones de los disparos
arbol->SetBranchAddress("scaler.channelCount",channelCountInfo);

ULong64_t nChannelsInfo; // número de canales
arbol->SetBranchAddress("scaler.nChannels",&nChannelsInfo);

// ----------- Creación de Histogramas -------------------------------
TH1F *histo1=new TH1F("PMTs Evento 0","Tasa de senales por PMT (primer evento)", 1200,0.5,1200.5);
TH1F *histo2=new TH1F("PMTs Evento 999","Tasa de senales por PMT (ultimo evento)", 1200,0.5,1200.5);

// ------------ Ciclo for para primer evento -------------------------
arbol->GetEntry(0);

for(Int_t i=0; i<nChannelsInfo; i++) // ciclo for para eventos
   {        // se llena el histograma
        histo1->SetBinContent(channelIDInfo[i], (channelCountInfo[i])/24.0);
   }

// tomando los valores scaler.GPSSecond = 1293625808 para evento 0
// scaler.GPSSecond = 1293625832 para evento 999
// -> diferencia = 24, entre los 1000 eventos * 1000 Hz = 24

// ------------ Ciclo for para último evento -------------------------
arbol->GetEntry(999);

for(Int_t i=0; i<nChannelsInfo; i++)
   {        // se llena el histograma
        histo2->SetBinContent(channelIDInfo[i], (channelCountInfo[i])/24.0);
   }
// ------------- Dibujo de Histogramas -------------------------------
TCanvas *c1 = new TCanvas("c1,c1"); //Graficando
TCanvas *c2 = new TCanvas("c2,c2");

histo1->SetMarkerStyle(46); // modificando color y otros atributos
histo1->SetMarkerColor(kViolet);
histo1->GetXaxis()->SetTitle("PMTs");
histo1->GetYaxis()->SetTitle("Frecuencia [kHz]");
//histo1->SetLineColor(kViolet);

histo2->SetMarkerStyle(46);
histo2->GetXaxis()->SetTitle("PMTs");
histo2->GetYaxis()->SetTitle("Frecuencia [kHz]");
histo2->SetMarkerColor(kGreen);
//histo2->SetLineColor(kGreen);

c1->cd();
histo1->Draw("P");   // Mostrando resultados
c2->cd();
histo2->Draw("P");
}
