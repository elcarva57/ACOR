// -- recibe AR en horas decimales y DEC en grados decimales, envia cadena tipo LX200
void Slew_F(double dRA, double dDec)
{
    //char *ptr;
    char aux[300];

    double dValue;			 			// temporary storage
    char cSign;	                        // declination sign
/*
    int HoraSlew;			 			// RA, hours
    double dRAMin;			 			// RA, minutes
    int nDecDeg;			 			// declination, degrees
    int nDecMin;			 			// declination, minutes
    char szCommand[128];				// command string
*/
    // New variables
    long RAHor;                         // RA,  hours
    long RAMin;                         // RA,  minutes
    long RASec;                         // RA,  seconds
    long RACse;                         // RA,  cents of second
    long DECGra;                        // DEC, degrees
    long DECMin;                        // DEC, minutes
    long DECSec;                        // DEC, seconds
    long DECCse;                        // DEC, cents of second

    dValue = dRA / 360 * 24;
    RAHor = dValue;

    dValue = (dValue - RAHor) * 60;
    RAMin = dValue;

    dValue = (dValue - RAMin) * 60;
    RASec = dValue;

    dValue = (dValue - RASec) * 100 + 0.5;
    RACse = dValue;

    if (RACse > 99) RACse = 99;

    if (dDec < 0.0)
    {
        dValue = -dDec;
        cSign = '-';
    }
    else
    {
        dValue = dDec;
        cSign = '+';
    }

    DECGra = dValue;

    dValue = (dValue - DECGra) * 60;
    DECMin = dValue;

    dValue = (dValue - DECMin) * 60;
    DECSec = dValue;

    dValue = (dValue - DECSec) * 100 + 0.5;
    DECCse = dValue;

    if (DECCse > 99) DECCse = 99;

    sprintf(carecta, " %02dh %02dm %02d.%02ds", RAHor, RAMin, RASec, RACse);
    sprintf(cdeclinacion, "%c%02dº %02d' %02d.%02d\"", cSign, DECGra, DECMin, DECSec, DECCse);

    if (CGEM)
    {
        if (Sincronizando)
        {
            // Change from GOTO to SYNC
            if (HPREC)
            {
                strcpy(aux, ArDecPrecToOrden(RAHor , RAMin , RASec , RACse,
                                             DECGra, DECMin, DECSec, DECCse, cSign));
                aux[0] = 's';
            }
            else
            {
                strcpy(aux, ArDecToOrden(RAHor , RAMin , RASec , RACse,
                                         DECGra, DECMin, DECSec, DECCse, cSign));
                aux[0] = 'S';
            }

            Sincronizando = false;
            Form1->CBSincronizar->State = cbUnchecked;

            // From sendClick()
            pedidaRaDe = false;
        }
        else
        {
            if (HPREC)
            {
                strcpy(aux, ArDecPrecToOrden(RAHor , RAMin , RASec , RACse,
                                             DECGra, DECMin, DECSec, DECCse, cSign));
            }
            else
            {
                strcpy(aux, ArDecToOrden(RAHor , RAMin , RASec , RACse,
                                         DECGra, DECMin, DECSec, DECCse, cSign));
            }
        }

        WriteHistory("Orden Sync: " + AnsiString(carecta) + " " +
                                    + cdeclinacion + " "
                                    + AnsiString(aux));
    }
    else
    {

        if (Sincronizando == true)
        {
            //           sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:CM#",
            sprintf( aux, ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:CM#",
                     RAHor, RAMin, cSign, DECGra, DECMin );
            Sincronizando = false;
            Form1->CBSincronizar->State = cbUnchecked;
        }
        else
            //           sprintf( &aux[2], ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:MS#",
            sprintf( aux, ":Sr %02d:%04.1lf#:Sd %c%02d\337%02d#:MS#",
                     RAHor, RAMin, cSign, DECGra, DECMin );
    }
    EnviaLX(aux);
}
