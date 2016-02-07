//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "conf_meteo.h"
#include "socket.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TFConfigMeteo *FConfigMeteo;

/*

*/

FILE *conf_ema;
extern char Meteo[200];
extern char dir_trab[250];
char ConfMeteo[800];
char temp[300];
extern bool OrdenCalibrar;
extern bool PedidoNiveles;
extern int Referencia[];   //referencia de los zener de ema.cfg
int  Ref[6];   // referencia zeners auxiliar
extern int Puerto;
extern bool Guardarjpg;

char bmp_ane[100],bmp_tem[100],bmp_plu[100],bmp_llu[100],bmp_bar[100];
char jpg_ane[100],jpg_tem[100],jpg_plu[100],jpg_llu[100],jpg_bar[100];
char jpg2_ane[100],jpg2_tem[100],jpg2_plu[100],jpg2_llu[100],jpg2_bar[100];

extern CSocket *S1;

typedef struct {
  int kpluvio;
  int alerta_nube;
  int bar_ofset;
  int bar_altura;
  int RefZener[6];
//  int MinFichero;
  int luzIR_ofset;
  int luzUV_ofset;
  int kmecanico;
  int k1termico;
  int k2termico;
  char direc_datos[100];
  char direc_jpg[100];
}CONF_METEO;

extern CONF_METEO confEMA;
extern char dir_trab[250];

extern char Buf_Meteo[500][16];
extern int indice_meteo;



 

//-------------------------------------------------------
// Lectura del fichero de configuracion
//-------------------------------------------------------
void LeerConfMeteo()
{
  int k1, sens;
  char auxi[10];
  char temp[300];
  FILE *conf;


  strcpy(temp,  dir_trab);
  strcat(temp, "ema.cfg");

   if((conf = fopen(temp, "rt")) != NULL)
   {
      fread(ConfMeteo, 400, 1, conf);
      fclose(conf);

      auxi[0]= ConfMeteo[5];
      auxi[1]= ConfMeteo[6];
      auxi[2]= ConfMeteo[7];
      auxi[3]= 0;
      confEMA.kpluvio = atoi(auxi);

      auxi[0]= ConfMeteo[9];
      auxi[1]= ConfMeteo[10];
      auxi[2]= ConfMeteo[11];
      auxi[3]= 0;
      confEMA.alerta_nube = atoi(auxi);

      auxi[0]= ConfMeteo[13];
      auxi[1]= ConfMeteo[14];
      auxi[2]= ConfMeteo[15];
      auxi[3]= 0;
      confEMA.bar_ofset = atoi(auxi);

      auxi[0]= ConfMeteo[17];
      auxi[1]= ConfMeteo[18];
      auxi[2]= ConfMeteo[19];
      auxi[3]= 0;
      confEMA.bar_altura = atoi(auxi);

      k1 = 21;    //posicion donde empiezan las lecturas en la cadena
      for (sens = 0; sens<6; sens++){
        auxi[0]= ConfMeteo[k1];
        k1++;
        auxi[1]= ConfMeteo[k1];
        k1++;
        auxi[2]= ConfMeteo[k1];
        k1++;
        auxi[3]= 0;
        confEMA.RefZener[sens] = atoi(auxi);  // Se recupera la Referencia guardada
        k1++;
      }

      auxi[0]= ConfMeteo[45];
      auxi[1]= 0;
//      confEMA.MinFichero = atoi(auxi);

      auxi[0]= ConfMeteo[49];
      auxi[1]= ConfMeteo[50];
      auxi[2]= ConfMeteo[51];
      auxi[3]= 0;
      confEMA.luzIR_ofset = atoi(auxi);

      auxi[0]= ConfMeteo[53];
      auxi[1]= ConfMeteo[54];
      auxi[2]= ConfMeteo[55];
      auxi[3]= 0;
      confEMA.luzUV_ofset = atoi(auxi);

      auxi[0]= ConfMeteo[58];
      auxi[1]= ConfMeteo[59];
      auxi[2]= ConfMeteo[60];
      auxi[3]= 0;
      confEMA.kmecanico = atoi(auxi);

      auxi[0]= ConfMeteo[62];
      auxi[1]= ConfMeteo[63];
      auxi[2]= ConfMeteo[64];
      auxi[3]= ConfMeteo[65];
      auxi[4]= 0;
      confEMA.k1termico = atoi(auxi);

      auxi[0]= ConfMeteo[67];
      auxi[1]= ConfMeteo[68];
      auxi[2]= ConfMeteo[69];
      auxi[3]= ConfMeteo[70];
      auxi[4]= 0;
      confEMA.k2termico = atoi(auxi);

      auxi[0]= ConfMeteo[71];
      auxi[1]= ConfMeteo[72];
      auxi[2] = 0;
      Puerto = atoi(auxi);

      strcpy(confEMA.direc_datos,  &ConfMeteo[110]);
      strcpy(confEMA.direc_jpg,  &ConfMeteo[210]);
      if (ConfMeteo[75]=='1') Guardarjpg = true;
       else Guardarjpg = false;
   }
   else
   {
        confEMA.kpluvio = 84;
        confEMA.alerta_nube = 125;
        confEMA.bar_ofset = -6;
        confEMA.bar_altura = 620;
//        confEMA.MinFichero = 5;
        confEMA.luzIR_ofset = 8;
        confEMA.luzUV_ofset = 13;
        confEMA.kmecanico  = 10;
        confEMA.k1termico  = 120;
        confEMA.k2termico  = 1345;
        strcpy(confEMA.direc_datos, "c:\\");
        strcpy(confEMA.direc_jpg, "c:\\");

        confEMA.RefZener[0] = 1;
        confEMA.RefZener[1] = 1;
        confEMA.RefZener[2] = 1;
        confEMA.RefZener[3] = 1;
        confEMA.RefZener[4] = 1;
        confEMA.RefZener[5] = 1;
        Puerto = 1;

   }

   strcpy(bmp_ane, confEMA.direc_jpg);
   strcat(bmp_ane, "Anemometro.bmp");
   strcpy(bmp_tem, confEMA.direc_jpg);
   strcat(bmp_tem, "temperatura.bmp");
   strcpy(bmp_plu, confEMA.direc_jpg);
   strcat(bmp_plu, "pluviometria.bmp");
   strcpy(bmp_llu, confEMA.direc_jpg);
   strcat(bmp_llu, "lluvia_nubes.bmp");
   strcpy(bmp_bar, confEMA.direc_jpg);
   strcat(bmp_bar, "barometro.bmp");

   strcpy(jpg_ane, confEMA.direc_jpg);
   strcat(jpg_ane, "Anem.jpg");
   strcpy(jpg_tem, confEMA.direc_jpg);
   strcat(jpg_tem, "temp.jpg");
   strcpy(jpg_plu, confEMA.direc_jpg);
   strcat(jpg_plu, "pluv.jpg");
   strcpy(jpg_llu, confEMA.direc_jpg);
   strcat(jpg_llu, "lluv.jpg");
   strcpy(jpg_bar, confEMA.direc_jpg);
   strcat(jpg_bar, "baro.jpg");

   strcpy(jpg2_ane, confEMA.direc_jpg);
   strcat(jpg2_ane, "Anemometro.jpg");
   strcpy(jpg2_tem, confEMA.direc_jpg);
   strcat(jpg2_tem, "temperatura.jpg");
   strcpy(jpg2_plu, confEMA.direc_jpg);
   strcat(jpg2_plu, "pluviometria.jpg");
   strcpy(jpg2_llu, confEMA.direc_jpg);
   strcat(jpg2_llu, "lluvia_nubes.jpg");
   strcpy(jpg2_bar, confEMA.direc_jpg);
   strcat(jpg2_bar, "barometro.jpg");

}

//---------------------------------------------------------------------------
// Creación ventana configuracion meteo.
//  Se lee el fichero de configuracion para presentarlo
//---------------------------------------------------------------------------
__fastcall TFConfigMeteo::TFConfigMeteo(TComponent* Owner)
  : TForm(Owner)
{
  LeerConfMeteo();

  EKPluvio->Text =  confEMA.kpluvio;
  ELimiteNubes->Text = confEMA.alerta_nube;
  EOffset_Bar->Text = confEMA.bar_ofset;
  EAltura_Bar->Text = confEMA.bar_altura;
  Ezener1->Text =  confEMA.RefZener[0];
  Ezener2->Text =  confEMA.RefZener[1];
  Ezener3->Text =  confEMA.RefZener[2];
  Ezener4->Text =  confEMA.RefZener[3];
  Ezener5->Text =  confEMA.RefZener[4];
  Ezener6->Text =   confEMA.RefZener[5];
  EOffset_IR->Text = confEMA.luzIR_ofset;
  EOffset_UV->Text = confEMA.luzUV_ofset;
  EKAnem_mec->Text = confEMA.kmecanico;
  EK1Anem_term->Text = confEMA.k1termico;
  EK2Anem_term->Text = confEMA.k2termico;

  if (Guardarjpg)  CBGuardarJPG->State = cbChecked;
     else CBGuardarJPG->State = cbUnchecked;


  char aux[22];
  memset(aux, ' ', sizeof(aux));
  strncpy(&aux[0], &ConfMeteo[90],10);
  strncpy(&aux[12], &ConfMeteo[80],8);
  aux[20]= 0;
  PFechaConf->Caption = AnsiString("Ultima Modificacion:  ") + aux;

  LeerNivelesMeteo();

  EDirectorio->Text = confEMA.direc_datos;
  Ejpg->Text = confEMA.direc_jpg;
}

//---------------------------------------------------------------------------
// Lee cadena Meteo recibida de la estacion y la presenta en la ventana de configuracion.
//---------------------------------------------------------------------------
void __fastcall TFConfigMeteo::BCalAnemTClick(TObject *Sender)
{
  int sens, pos, npos,kk;
  char aux[60];

  memset(aux, ' ', sizeof(aux));
 // npos = 0; //21 a 44 posicion donde empiezan las lecturas en la cadena

  if(Application->MessageBox("Va a calibrar el anemometro termico. ¿Esta el aire en reposo?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
  {
     return;
  }

  kk = 21; //posicion donde empiezan las lecturas en la cadena
  for (sens = 0; sens<6; sens++) // se saca nueva Referencia del fichero
  {
     aux[0]= Meteo[kk];
     kk++;
     aux[1]= Meteo[kk];
     kk++;
     aux[2]= Meteo[kk];
     kk++;
     aux[3]= 0;
     Ref[sens] = atoi(aux);
     kk++;
  }

  Ezener1->Text =  Ref[0];
  Ezener2->Text =  Ref[1];
  Ezener3->Text =  Ref[2];
  Ezener4->Text =  Ref[3];
  Ezener5->Text =  Ref[4];
  Ezener6->Text =  Ref[5];

  strcpy(aux,"(E000)");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);


}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Guarda en el fichero ema.cfg la configuracion presente en la ventana de configuracion.
//---------------------------------------------------------------------------
void __fastcall TFConfigMeteo::BAjustes_MeteoClick(TObject *Sender)
{

  if(Application->MessageBox("¿Desea guardar ajustes?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
  {
     return;
  }
   strcpy(&ConfMeteo[0], "cfg:");
   strncpy(&ConfMeteo[5], EKPluvio->Text.c_str(),3);
   strncpy(&ConfMeteo[9], ELimiteNubes->Text.c_str(),3);
   strncpy(&ConfMeteo[13], EOffset_Bar->Text.c_str(),3);
   strncpy(&ConfMeteo[17], EAltura_Bar->Text.c_str(),3);

   strncpy(&ConfMeteo[21], Ezener1->Text.c_str(),3);
   strncpy(&ConfMeteo[25], Ezener2->Text.c_str(),3);
   strncpy(&ConfMeteo[29], Ezener3->Text.c_str(),3);
   strncpy(&ConfMeteo[33], Ezener4->Text.c_str(),3);
   strncpy(&ConfMeteo[37], Ezener5->Text.c_str(),3);
   strncpy(&ConfMeteo[41], Ezener6->Text.c_str(),3);

//   strncpy(&ConfMeteo[45], EMinFichero->Text.c_str(),1);

   strncpy(&ConfMeteo[49], EOffset_IR->Text.c_str(),3);
   strncpy(&ConfMeteo[53], EOffset_UV->Text.c_str(),3);
   strncpy(&ConfMeteo[58], EKAnem_mec->Text.c_str(),3);
   strncpy(&ConfMeteo[62], EK1Anem_term->Text.c_str(),4);
   strncpy(&ConfMeteo[67], EK2Anem_term->Text.c_str(),4);

   strcpy(&ConfMeteo[80], TimeToStr(Time()).c_str());
   strcpy(&ConfMeteo[90], DateToStr(Date()).c_str());

   strcpy(&ConfMeteo[110], EDirectorio->Text.c_str() );
   strcpy(&ConfMeteo[210], Ejpg->Text.c_str() );

  strcpy(temp,  dir_trab);
  strcat(temp, "ema.cfg");

   if((conf_ema = fopen(temp, "wt")) != NULL)
   {
      fwrite(ConfMeteo, sizeof(ConfMeteo), 1, conf_ema);
      fclose(conf_ema);
   }

   //Refresca la matriz de configuracion con los nuevos datos
   confEMA.kpluvio = atoi(EKPluvio->Text.c_str());
   confEMA.alerta_nube = atoi(ELimiteNubes->Text.c_str());
   confEMA.bar_ofset = atoi(EOffset_Bar->Text.c_str());
   confEMA.bar_altura = atoi(EAltura_Bar->Text.c_str());

   for (int sens = 0; sens<6; sens++) // se actualiza Referencia
   {
    // Referencia[sens] = Ref[sens];
     confEMA.RefZener[sens] = Ref[sens];
   }
   confEMA.luzIR_ofset = atoi(EOffset_IR->Text.c_str());
   confEMA.luzUV_ofset = atoi(EOffset_UV->Text.c_str());
   confEMA.kmecanico = atoi(EKAnem_mec->Text.c_str());
   confEMA.k1termico = atoi(EK1Anem_term->Text.c_str());
   confEMA.k2termico = atoi(EK2Anem_term->Text.c_str());
   strcpy(confEMA.direc_datos,  EDirectorio->Text.c_str());
   strcpy(confEMA.direc_jpg,  Ejpg->Text.c_str());
}
//---------------------------------------------------------------------------


void __fastcall TFConfigMeteo::BOkDirectorioClick(TObject *Sender)
{
char temp[300];

  if (CBGuardarJPG->State == cbChecked) ConfMeteo[75] = '1';
    else ConfMeteo[75]= '0';

//      FConfigMeteo->CBGuardarJPG->State = cbChecked;
  //       else FConfigMeteo->CBGuardarJPG->State = cbUnchecked;

   strcpy(&ConfMeteo[110], "                                    ");
   strcpy(&ConfMeteo[110], EDirectorio->Text.c_str() );
   strcpy(confEMA.direc_datos, EDirectorio->Text.c_str());

   strcpy(&ConfMeteo[210], "                                    ");
   strcpy(&ConfMeteo[210], Ejpg->Text.c_str() );
   strcpy(confEMA.direc_jpg, Ejpg->Text.c_str());

   strcpy(temp,  dir_trab);
   strcat(temp, "ema.cfg");

   if((conf_ema = fopen(temp, "wt")) != NULL)
   {
      fwrite(ConfMeteo, sizeof(ConfMeteo), 1, conf_ema);
      fclose(conf_ema);
   }
}
//---------------------------------------------------------------------------

void __fastcall TFConfigMeteo::BSalirClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------


void __fastcall TFConfigMeteo::BSendMeteoClick(TObject *Sender)
{
//char aux[300];

/*  aux[0] = 4;   //mensaje al puerto auxiliar (D) del COR
  aux[1] = 0;
  strcpy(&aux[2], EEnvMeteo->Text.c_str());

  S1->Escribir(aux, strlen(&aux[2]) + 2, S1->IPRabbit);      //sizeof(
*/

  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  EEnvMeteo->Text.c_str());
}
//---------------------------------------------------------------------------




void __fastcall TFConfigMeteo::BGrabarClick(TObject *Sender)
{
  char aux[300], auxb[20];
  int porcent;

  strcpy(aux,"(L");
  porcent = (255 * atoi(ELimiteLluvia->Text.c_str()))/100;
  if (porcent > 255) porcent = 255;
  sprintf(auxb,"%03d", porcent);
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(N");
  porcent = (255 * atoi(ELimiteNubes->Text.c_str()))/100;
  if (porcent > 255) porcent = 255;
  sprintf(auxb,"%03d", porcent);
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(V");
  sprintf(auxb,"%03d",atoi(ELimiteKmh->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(T");
  sprintf(auxb,"%03d",atoi(ELimiteEspera->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(F");
  sprintf(auxb,"%03d",atoi(ELimiteFuente->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(C");
  sprintf(auxb,"%03d",atoi(ELimiteRocio->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

}
//---------------------------------------------------------------------------

void LeerNivelesMeteo()
{
  char aux[50];

  PedidoNiveles = true;

  strcpy(aux,"(l)");
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(n)");
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(v)");
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(t)");
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(f)");
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(c)");
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);
}

//---------------------------------------------------------------------------
void __fastcall TFConfigMeteo::BLeerClick(TObject *Sender)
{
  LeerNivelesMeteo();
}
//---------------------------------------------------------------------------

void __fastcall TFConfigMeteo::BAjuste_Meteo_FlashClick(TObject *Sender)
{
  char aux[300], auxb[20];
  int porcent;

  if(Application->MessageBox("¿Desea guardar los ajustes en la estacion?", "ATENCION", MB_OKCANCEL ) == IDCANCEL )
  {
     return;
  }

  strcpy(aux,"(P");
  sprintf(auxb,"%03d",atoi( EKPluvio->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(B");
  sprintf(auxb,"%03d",atoi( EOffset_Bar->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(M");
  sprintf(auxb,"%03d",atoi( EAltura_Bar->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(O");
  sprintf(auxb,"%03d",atoi( EOffset_IR->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(U");
  sprintf(auxb,"%03d",atoi( EOffset_UV->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(A");
  sprintf(auxb,"%03d",atoi(EKAnem_mec->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(G");
  sprintf(auxb,"%03d",atoi( EK1Anem_term->Text.c_str()));
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

  strcpy(aux,"(D");
  sprintf(auxb,"%03d",atoi( EK2Anem_term->Text.c_str())/10);
  strcat(aux, auxb);
  strcat(aux, ")");
  aux[6] = 0;
  indice_meteo++;
  strcpy(Buf_Meteo[indice_meteo],  aux);

}
//---------------------------------------------------------------------------


