void T3E1_F14A_sinSelecc_2()
{
TFile *file = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/raw_run009776_00462.root");
TTree *arbol = (TTree*) file->Get("hits");
Int_t entradas = arbol->GetEntries();

UInt_t ChannelInfo = 0;
arbol->SetBranchAddress("Channel",&ChannelInfo);

double ChargeInfo = 0;
arbol->SetBranchAddress("CalibratedCharge",&ChargeInfo);

// Bool_t QualityInfo = 0;   Ya no hace falta. Se comenta ya que la da sin calidad
// arbol->SetBranchAddress("IsGood",&QualityInfo);

TH1F *histo=new TH1F("histo","Distribucion de carga en el PMT F14A (sin seleccion de calidad).", 500,0,1500);

for(Int_t i=0; i<entradas; i++) //loop para eventos
   {
    arbol->GetEntry(i); //se cargan las asignaciones de valores para este evento
   
    if(ChannelInfo == 69) // Desde HAWCSurvey.xml se buscó canal del PMT F14A, que fue id="69"
     {
      histo->Fill(ChargeInfo); //se llena el histograma
     } 
   // Bien pudiera hacerse también buscando la condición IsGood==1, FLAGS==0      
    }
TCanvas *c3 = new TCanvas("c3"); //Graficando
c3->SetLogy(); // Dando formato en escala log y modificando color y otros atributos
histo->SetLineWidth(4);
//c3.SetLineColor(KOrange - 10)
histo->GetXaxis()->SetTitle("Carga (PE)");
histo->GetYaxis()->SetTitle("Eventos");
histo->SetLineColor(kOrange);

histo->Draw();	// Mostrando resultados
}
