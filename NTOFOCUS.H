/* $Id: ntofocus.h,v 1.1.1.1 2005/01/29 18:21:19 Astrorafael Exp $ */

//---------------------------------------------------------------------------
#ifndef ntofocusH
#define ntofocusH
//---------------------------------------------------------------------------

typedef short pixel_t;   /* assume 16 bit signed pixels (AUDINE) */

/* Constantes de volcado a fichero de log */

#define AF_LOG_NINGUNO   0
#define AF_LOG_ERROR     1
#define AF_LOG_AVISO     2
#define AF_LOG_INFO      3
#define AF_LOG_DEBUG     4
#define AF_LOG_VERBORREA 5


#ifdef __cplusplus
extern "C" {
#endif

/************************/
/* ANALISIS Y AUDITORIA */
/************************/

/* Cambia el nivel de log del fichero */
void __declspec(dllimport)
AF_SetLogLevel(int level);

/* Habilita (1) o desabilita (0) la exportacion de datasets para R */
void __declspec(dllimport)
AF_EnableDataSets(int flag);

/***********************/
/* CALIBRACION INICIAL */
/***********************/

/* Inicializa o reinicia el estado interno del proceso de calibracion */
void __declspec(dllimport)
AF_InitCalibration(void);


/*  Establece la imagen actual para operar con ella */
void __declspec(dllimport)
AF_SetImage(pixel_t* img, int width, int height);


/* Establece la zona del fondo de cielo necesaria para el calculo del centroide */
void __declspec(dllimport)
AF_SetSkyRegion(int x1, int y1, int x2, int y2);


/* Establece la caja de cálculo del centroide */
void __declspec(dllimport)
AF_SetCentroidRegion(int x1, int y1, int x2, int y2);


/* calcula el HFD */
/* si hay algun error devuelve un HFD negativo (-1.0 o -0.99999) */
/* El nombre del fichero se imprime al log si no es NULL */
double __declspec(dllimport)
AF_HFD(const char* file);


/* recupera el centroide calculado para pintarlo en la imagen */
/* se debe llamar despues de AF_HFD() */
void __declspec(dllimport)
AF_GetCentroid(double* xc, double* yc);


/* Añade una medida (focuserPos, hfd) al array de medidas */
void __declspec(dllimport)
AF_AddMeasurement(int focuserPos, double hfd);

/* Halla la V con las medidas añadidas */
/* devuelve 0 si todo bien y -1 si hay error */
int __declspec(dllimport)
AF_FitParams();

/**********************************/
/* OPCIONES DEL PROCESO DE AJUSTE */
/**********************************/

typedef struct {
  int    bfp;    /* best focus position found during callibration */
  double pid;    /* position intercept difference */
  double nfHFD;  /* near focus HFD rounded */
  struct {
    double slope;  /* estimated left slope */
    double slope_dev; /* estimated left slope standard deviation */
    double x0;     /* estimated left x0 */
    double x0_dev; /* estimated left x0 standard deviation */
    double rse;    /* residual standard error */
    int npoints;   /* points used for fitting the left side */
    int nreject;   /* points rejected on the left side */
  } left;
  struct {
    double slope;  /* estimated right slope */
    double slope_dev; /* estimated right slope standard deviation */
    double x0;     /* estimated right x0 */
    double x0_dev; /* estimated right x0 standard deviation */
    double rse;    /* residual standard error */
    int npoints;   /* points used for fitting the right side */
    int nreject;   /* points rejected on the right side */
  } right;
} FitResult;


/* devuelve los resultados del ajuste en la estructura FitResult */
void __declspec(dllimport)
AF_GetFitResult(FitResult* fr);

/* establece el nivel de Near Focus para el ajuste de AF_FitParam() */
void __declspec(dllimport)
AF_SetNearFocusHFD(double level);

/* maxinmo nivel de error estandar de residuos admisible */
void __declspec(dllimport)
AF_SetMaxRSE(double rse);

/* máxomo numero de mediciones discordantes a examinat en cada lado */
/* devuelve -1 si hay 2*outliers + 1 > tamaño del vector de medidas */
int __declspec(dllimport)
AF_SetMaxOutliers(unsigned int);

/***************************************************/
/* FUNCIONES DE GESTION DEL FICHERO DE CALIBRACION */
/***************************************************/

/* añade al final del fichero de calibracion la curva recien hallada */
/* Devuelve 0 si OK y -1 si hay error */
/* label es una etiqueta informativa de hasta 16 caracteres max. o bien NULL */
int __declspec(dllimport)
AF_Save(const char* label);

/* carga el final del fichero de calibracion la curva identificada por la fecha
y hora en formato YYYY-MM-DDTHH:MM:SS   */
/* Devuelve 0 si OK y -1 si hay error */
int __declspec(dllimport)
AF_Load(const char* timestamp);

/* borra del fichero de calibracion la curva identificada por la fecha
y hora en formato YYYY-MM-DDTHH:MM:SS   */
/* Devuelve 0 si OK y -1 si hay error */
int __declspec(dllimport)
AF_Delete(const char* timestamp);

/**************************/
/* FUNCIONES DE REENFOQUE */
/**************************/

/* Hay que llamarla cuando se quiera empezar el proceso de reenfoque */
void __declspec(dllimport)
AF_InitRefocus(void);


/* Es importante mirar los códigos de retorno */
int __declspec(dllimport)
AF_NextPosition(int* position, double hfd);

/* codigos de retorno de AF_NextPosition() */
#define AF_ACT_ERROR -1		/* No hacer nada. Algo malo paso */
#define AF_ACT_PARAR  0		/* No hacer nada. Hemos terminado */
#define AF_ACT_HFD    1		/* calcular otra HFD en la misma posicion */
#define AF_ACT_POS    2		/* mover a posicion sugerida */
#define AF_ACT_FREE   3		/* app mueve posicion foco a discreccion */

#ifdef __cplusplus
};
#endif
 

#endif
