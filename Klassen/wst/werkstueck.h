#ifndef WERKSTUECK_H
#define WERKSTUECK_H

#include <QString>
#include <QMessageBox>

#include "Defines/werkzeug.h"

#include "Funktionen/umwandeln.h"
#include "Funktionen/runden.h"
#include "Funktionen/myfunktion.h"
#include "Defines/def_fmc.h"
#include "Defines/def_ganx.h"
#include "Klassen/text_zeilenweise.h"
#include "../werkzeugmagazin.h"
#include "bohrung.h"
#include "rechtecktasche.h"
#include "nut.h"
#include "fraueseraufruf.h"
#include "fraesergerade.h"
#include "fraeserbogen.h"
#include "bohrraster.h"
#include "Defines/dateinamen.h"
#include "ganx_gruppen.h"


class werkstueck
{
public:
    werkstueck();
    werkstueck(QString neuer_name);

    void set_laenge(double l);
    void set_laenge(QString l);
    void set_breite(double b);
    void set_breite(QString b);
    void set_dicke(double d);
    void set_dicke(QString d);
    void neue_bearbeitung(QString text);
    void set_kante_vo(QString artiklenummer);
    void set_kante_hi(QString artiklenummer);
    void set_kante_li(QString artiklenummer);
    void set_kante_re(QString artiklenummer);
    QString get_kante_vo(QString drewi = "0");
    QString get_kante_hi(QString drewi = "0");
    QString get_kante_li(QString drewi = "0");
    QString get_kante_re(QString drewi = "0");
    QString get_kante_vo_ganx(QString drewi = "0");
    QString get_kante_hi_ganx(QString drewi = "0");
    QString get_kante_li_ganx(QString drewi = "0");
    QString get_kante_re_ganx(QString drewi = "0");

    inline void set_name(QString neuer_name)
    {
        name = neuer_name;
    }

    inline double get_laenge() const
    {
        return laenge;
    }
    inline QString get_laenge_qstring() const
    {
        return double_to_qstring(laenge);
    }
    inline double get_breite() const
    {
        return breite;
    }
    inline QString get_breite_qstring() const
    {
        return double_to_qstring(breite);
    }
    inline double get_dicke() const
    {
        return dicke;
    }
    inline QString get_dicke_qstring() const
    {
        return double_to_qstring(dicke);
    }
    inline QString get_name()
    {
        return name;
    } 
    inline text_zeilenweise get_bearb()
    {
        return bearbeitungen;
    }

    QString get_fmc(text_zeilenweise wkzmagazin, QString& info, \
                    QString drehwinkel = "0", QString zust_fkon = "orgi",\
                    bool formartierungen_aufbrechen = false,\
                    bool fkon_kantenschonend = false);
    QString get_ganx(text_zeilenweise wkzmagazin, QString& info ,QString drehwinkel = "0");
    QString get_ggf(text_zeilenweise wkzmagazin, QString& info ,QString drehwinkel = "0");
    QString get_eigenses_format(QString drehwinkel, QString ausgabeformat, \
                                text_zeilenweise wkzmagazin,\
                                bool formartierungen_aufbrechen = false,\
                                bool fkon_kantenschonend = false);

    QString suche_cad_fehler();

private:
    //Variabeln:
    double laenge;  //X-Wert
    double breite;  //Y-Wert
    double dicke;   //Z-Wert
    text_zeilenweise bearbeitungen;
    QString name;
    double schwellenwert_ay; //für fmc-Ausgabe, bis zu dieser Breite wird mit ay-Versatz ausgegeben
    QString kante_vo; //Kante an X
    QString kante_hi;
    QString kante_li; //Kante an Y
    QString kante_re;

    //Funktionen:


    QString warnungen_ganx(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin);
    QString warnungen_fmc(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin);
    QString warnungen_ggf(text_zeilenweise bearbeit,double tmp_l, double tmp_b, text_zeilenweise wkzmagazin);
    QString fehler_kein_WKZ(QString exportformat, text_zeilenweise bearbeitung);
    QString get_bearb_menschlich_lesbar(text_zeilenweise bearbeitung);

    void bearb_sortieren();
    text_zeilenweise bearb_drehen_90(text_zeilenweise bearb, double& tmp_l, double& tmp_b);
    text_zeilenweise bearb_optimieren_ganx(text_zeilenweise bearb);

    text_zeilenweise rasterbohrungen_finden_ganx(text_zeilenweise bearb, text_zeilenweise wkzmagazin,double tmp_l, double tmp_b);
    text_zeilenweise rasterbohrungen_finden_fmc(text_zeilenweise bearb, text_zeilenweise wkzmagazin,double tmp_l, double tmp_b);

    text_zeilenweise formartierung_zu_einzelfkon(text_zeilenweise bearb,double tmp_l, double tmp_b);
    text_zeilenweise kurze_an_ab_geraden(text_zeilenweise bearb, text_zeilenweise wkzmagazin);
    text_zeilenweise dubosplitten(text_zeilenweise bearb, text_zeilenweise wkzmagazin, double wstdicke);
    text_zeilenweise fkon_kantengut(text_zeilenweise bearb, text_zeilenweise wkzmagazin,double tmp_l, double tmp_b);

    QString get_fmc_dateitext(text_zeilenweise wkzmagazin,text_zeilenweise bearb , \
                              double tmp_l, double tmp_b, QString zust_fkon,\
                              QString drewi, bool formartierungen_aufbrechen,\
                              bool fkon_kantenschonend);
    QString get_ganx_dateitext(text_zeilenweise wkzmagazin,text_zeilenweise bearb ,\
                               double tmp_l, double tmp_b);
    QString get_ggf_dateitext(text_zeilenweise wkzmagazin,text_zeilenweise bearb ,\
                               double tmp_l, double tmp_b);
    QString get_eigen_dateitext(text_zeilenweise bearb ,double tmp_l, double tmp_b, \
                                QString ausgabeformat, text_zeilenweise wkzmagazin,\
                                bool formartierungen_aufbrechen,\
                                bool fkon_kantenschonend);

    QString kommentar_fmc(QString kom);
    QString kommentar_ggf(QString kom);
    QString fmc_kommentar_gute_seite(text_zeilenweise bearb);

    bool punkt_auf_wst(double x, double y, double l, double b, double tolleranz);
    void fraesergeraden_zusammenfassen();
    void hbemiduebeltiefe();



};

#endif // WERKSTUECK_H
