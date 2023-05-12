void T3E2_H13C_2()
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

TH1F *histo=new TH1F("histo","Distribucion de carga en el PMT H13C (con seleccion de calidad).", 500,0,1500);

for(Int_t i=0; i<entradas; i++) //loop para eventos
   {
    arbol->GetEntry(i); //se cargan las asignaciones de valores para cada evento
   
    if(ChannelInfo == 183 && QualityInfo == 1 && QualityInfo2 == 0) // Desde Survey se halló id="183" para PMT H13C
     {
      histo->Fill(ChargeInfo); //se llena el histograma
     } 
           
    }
TCanvas *c = new TCanvas("c"); //Graficando
c->SetLogy(); // Dando formato en escala log y modificando color y otros atributos
//c.SetLineColor(kOrange-10)
histo->SetLineWidth(4);
histo->GetXaxis()->SetTitle("Carga (PE)");
histo->GetYaxis()->SetTitle("Eventos");
histo->SetLineColor(kGreen);

histo->Draw();	// Mostrando resultados
}
