// Este código identifica cuando dos o tres PMTs en un mismo detector seleccionado reciben una señal dentro de una ventana de "coincidencia" de 20 ns y calcula con qué frecuencia sucedió

void Coincidencia_PMTs() 
{
TFile *file = TFile::Open("/home/rafael/Documents/labHAWC/Tareas/raw_run009776_00462.root");
TTree *arbol = (TTree*) file->Get("hits");
Int_t entradas = arbol->GetEntries();
// hasta este punto todo es igual a los anteriores macros para ramas (establecer ruta del archivo.root, arbol hits y definir entradas

UInt_t ChannelInfo = 0;  // definiendo variables y sus ramas como en los casos previos
arbol->SetBranchAddress("Channel",&ChannelInfo);

Bool_t QualityInfo = 0;
arbol->SetBranchAddress("IsGood",&QualityInfo);

UInt_t QualityInfo2 = 0;
arbol->SetBranchAddress("FLAGS",&QualityInfo2);

double t_Info = 0; // ahora, se requiere incluir también a la variable de tiempo
arbol->SetBranchAddress("CalibratedTime",&t_Info);
double t_ini = 0; // y su valor al momento de recibir la señal

UInt_t rep = 0; // repeticiones de los disparos en el mismo detector

double dif_t = abs(t_Info - t_ini); // intervalo temporal entre dos eventos
for(Int_t i=0; i<entradas; i++) //misma estructura de loop de eventos que en casos anteriores
   {
    arbol->GetEntry(i); //valores para el evento dado
   
    //seleccionando el detector R10
    if((ChannelInfo == 813 || ChannelInfo == 814 || ChannelInfo == 815) && QualityInfo == 1 && QualityInfo2 == 0 && dif_t <= 20) //canales correspondientes a PMT R10A, B y C
    
    //se limita selección a hits con calidad y con la condición de la ventana de tiempo
     {
      rep = rep + 1; //repeticiones acumuladas de disparos en R10
      t_ini = t_Info; // se guarda nuevo valor temporal
     }
    else
      t_ini = t_Info; // seguir conteo de tiempo 
    }
    
double frec = rep /0.250052; //frecuencia convertida en Hz dado el tiempo del último evento medido en hits con << hits->Show(-1) >> y tomando CalibratedTime *10^-9

// por último, se muestra por pantalla el resultado

std::cout << "Dos o tres PMTs (A, B, C) dentro del mismo detector (R10) reciben señales simultáneas (en ventanas menores a 20 ns) con una frecuencia de " << frec << " Hz." << '\n' << "Dichas coincidencias suceden  en total " << rep << " veces." << endl;
}
