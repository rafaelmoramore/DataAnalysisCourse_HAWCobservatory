void T4_6() // Fluctuaciones en PMTs: diferencia entre el primer y último evento en histogramas de conteos
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

ULong64_t nChannelsInfo; // número de canal
arbol->SetBranchAddress("scaler.nChannels",&nChannelsInfo);

// ----------- Creación de Histogramas -------------------------------
TH1F *histo1=new TH1F("PMTs Evento 0","Tasa de senales por PMT (primer evento)", 1200,0.5,1200.5);
TH1F *histo2=new TH1F("PMTs Evento 999","Tasa de senales por PMT (ultimo evento)", 1200,0.5,1200.5);
TH1F *histo21=new TH1F("Diferencia 0-999","Fluctuacion entre el primer y ultimo evento en la tasa de senales por PMT", 1200,0.5,1200.5);
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
// ------------- RESTA DE HISTOGRAMAS --------------------------------

histo21->Add(histo1,histo2,1,-1);
//Bool_t TH1::Add(const TH1*histo1, const TH1*histo2, Double_t c1 = 1, Double_t c2 = -1);
//histo21 = c1*histo1 + c2*histo2;

// ------------- Dibujo de Histogramas -------------------------------
TCanvas *c21 = new TCanvas("c21,c21"); //Graficando


histo21->SetMarkerStyle(46); // modificando color y otros atributos
histo21->SetMarkerColor(kBlue);
histo21->GetXaxis()->SetTitle("PMTs");
histo21->GetYaxis()->SetTitle("Frecuencia [kHz]");

c21->cd();
histo21->Draw("P");   // Mostrando resultados
}
