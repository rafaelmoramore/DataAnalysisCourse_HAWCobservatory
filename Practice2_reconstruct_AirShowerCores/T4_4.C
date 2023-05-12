void T4_4() // Este macro realiza un histograma comparando el conteo de ocurrencias por WCD para el evento 0 y 999
{
// --------- Archivo fuente e indicación del árbol ----------------------
TFile *file = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/tdcscaler_run009776_00692.root");
TTree *arbol =(TTree*) file->Get("XCDF");
Int_t entradas = arbol->GetEntries();

// --------- Declaración de variables y sus ramas ----------------------
Int_t Canales = 1200; //total de PMTs sin importar si se inutiliza alguno
//Int_t Tanques = 300; // total de WCD
ULong64_t tankID = 0;

ULong64_t channelTankIDInfo[Canales]; // vector de long. Canales 
arbol->SetBranchAddress("scaler.channelTankID",channelTankIDInfo); //ya no requiere &

ULong64_t channelCountInfo[Canales]; // repeticiones de los disparos
arbol->SetBranchAddress("scaler.channelCount",channelCountInfo);

ULong64_t nChannelsInfo; // número de canal
arbol->SetBranchAddress("scaler.nChannels",&nChannelsInfo);

ULong64_t channelIDInfo[Canales]; 
arbol->SetBranchAddress("scaler.channelID",channelIDInfo);

//ULong64_t nTanksInfo; // número de tanque
//arbol->SetBranchAddress("scaler.nTanks",&nTanksInfo);

//ULong64_t tankIDInfo[Tanques];
//arbol->SetBranchAddress("scaler.tankID",tankIDInfo);

ULong64_t tankCountInfo = 0;

// ----------- Creación de Histogramas --------------------------------
TH1F *histo3=new TH1F("WCD Evento 0","Conteo de senales en cada WCD (primer evento)", 300,0.5,300.5);
TH1F *histo4=new TH1F("WCD Evemto 999","Conteo de senales en cada WCD (ultimo evento)", 300,0.5,300.5);

// ------------ Ciclo for para primer evento --------------------------
arbol->GetEntry(0);
// Se usa variable para agrupar canales por WCD
tankID = channelTankIDInfo[0];
tankCountInfo=0;

for(Int_t i=0; i<nChannelsInfo; i++)
   {	// filtra detectores
      if(tankID == channelTankIDInfo[i])
        {
         tankCountInfo = tankCountInfo + channelCountInfo[i];
        }
      else
        {
         histo3->SetBinContent(tankID, tankCountInfo/24.0);
        }
      histo3->SetBinContent(tankID, tankCountInfo/24.0);
      tankID = channelTankIDInfo[i];
      tankCountInfo = channelCountInfo[i];
   }

//  Int_t j = 0, y; // contador y variable para agrupar canales de 4 en 4 (cada WCD)
//for(Int_t i=0; i<nTanksInfo; i++)
//   {
//      y = channelCountInfo[j] +channelCountInfo[j+1] + channelCountInfo[j+2]+channelCountInfo[j+3];   
//        histo3->SetBinContent(channelTankIDInfo[i], y/24.0);
//        j = j+ 4;
//   }

// ------------ Ciclo for para último evento --------------------------
arbol->GetEntry(999);
// Se usa variable para agrupar canales por WCD
tankID = channelTankIDInfo[0];
tankCountInfo=0;

for(Int_t i=0; i<nChannelsInfo; i++)
   {	// filtra detectores
      if(tankID == channelTankIDInfo[i])
        {
         tankCountInfo = tankCountInfo + channelCountInfo[i];
        }
      else
        {
         histo3->SetBinContent(tankID, tankCountInfo/24.0);
        }
      histo4->SetBinContent(tankID, tankCountInfo/24.0);
      tankID = channelTankIDInfo[i];
      tankCountInfo = channelCountInfo[i];
   }

// ------------- Dibujo de Histogramas --------------------------------

TCanvas *c3 = new TCanvas("c3","c3");
TCanvas *c4 = new TCanvas("c4","c4");

histo3->SetMarkerStyle(46); // modificando color y otros atributos
histo3->SetMarkerColor(kRed);
histo3->GetXaxis()->SetTitle("WCDs");
histo3->GetYaxis()->SetTitle("Frecuencia [kHz]");
//histo3->SetLineColor(kRed);

histo4->SetMarkerStyle(46); // modificando color y otros atributos
histo4->SetMarkerColor(kBlue);
histo4->GetXaxis()->SetTitle("WCDs");
histo4->GetYaxis()->SetTitle("Frecuencia [kHz]");
//histo4->SetLineColor(kBlue);

c3->cd();
histo3->Draw("P");   // Mostrando resultados

c4->cd();
histo4->Draw("P");
}
