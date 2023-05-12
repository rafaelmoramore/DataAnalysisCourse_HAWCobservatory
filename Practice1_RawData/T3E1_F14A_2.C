void T3E1_F14A_2()
{
TFile *file = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/raw_run009776_00462.root");
TTree *arbol = (TTree*) file->Get("hits");
Int_t entradas = arbol->GetEntries();

UInt_t ChannelInfo = 0;
arbol->SetBranchAddress("Channel",&ChannelInfo);

double ChargeInfo = 0;
arbol->SetBranchAddress("CalibratedCharge",&ChargeInfo);

Bool_t QualityInfo = 0;
arbol->SetBranchAddress("IsGood",&QualityInfo);

UInt_t QualityInfo2 = 0;
arbol->SetBranchAddress("FLAGS",&QualityInfo2);

TH1F *histo=new TH1F("histo","Distribucion de carga en el PMT F14A (con seleccion de calidad).", 500,0,1500);

for(Int_t i=0; i<entradas; i++) //loop para eventos
   {
    arbol->GetEntry(i); //se cargan las asignaciones de valores para este evento
   
    if(ChannelInfo == 69 && QualityInfo == 1 && QualityInfo2 == 0) // Desde archivo HAWCSurvey.xml se buscó el canal del PMT F14A, que fue id="69"
     {
      histo->Fill(ChargeInfo); //se llena el histograma
     } 
    }
TCanvas *c2 = new TCanvas("c2"); //Graficando
c2->SetLogy(); // Dando formato en escala log y modificando color y otros atributos
//c2.SetLineColor(kOrange - 10);
histo->SetLineWidth(4);
histo->GetXaxis()->SetTitle("Carga (PE)");
histo->GetYaxis()->SetTitle("Eventos");
histo->SetLineColor(kOrange);

histo->Draw();	// Mostrando resultados
}
