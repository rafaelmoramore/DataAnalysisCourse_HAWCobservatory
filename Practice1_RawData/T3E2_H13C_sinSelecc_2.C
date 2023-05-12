void T3E2_H13C_sinSelecc_2()
{
TFile *file = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/raw_run009776_00462.root");
TTree *arbol = (TTree*) file->Get("hits");
Int_t entradas = arbol->GetEntries();

UInt_t ChannelInfo = 0;
arbol->SetBranchAddress("Channel",&ChannelInfo);

double ChargeInfo = 0;
arbol->SetBranchAddress("CalibratedCharge",&ChargeInfo);

// Bool_t QualityInfo = 0;
// arbol->SetBranchAddress("IsGood",&QualityInfo);

TH1F *histo=new TH1F("histo","Distribucion de carga en el PMT H13C (sin seleccion de calidad).", 500,0,1500);

for(Int_t i=0; i<entradas; i++) //loop para eventos
   {
    arbol->GetEntry(i); //se cargan las asignaciones de valores para este evento
   
    if(ChannelInfo == 183) // Desde Survey se halló canal id="183" para PMT H13C
     {
      histo->Fill(ChargeInfo); //se llena el histograma
     } 
      
    }
TCanvas *c4 = new TCanvas("c4"); //Graficando
c4->SetLogy(); // Dando formato en escala log y modificando color y otros atributos
//c4.SetLineColor(KOrange - 10)
histo->SetLineWidth(4);
histo->GetXaxis()->SetTitle("Carga (PE)");
histo->GetYaxis()->SetTitle("Eventos");
histo->SetLineColor(kGreen);

histo->Draw();	// Mostrando resultados
}
