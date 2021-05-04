
#include <iostream>
#include <string>
#include "Service.h"
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
using namespace std;
/*
void effectuerMoyenne(){
    Service s;
    double longitude, latitude, rayon;
    string dateDeb, dateFin, info_user;
    cout<<"Veuillez-renseigner les informations suivantes:"<<endl;

    cout<<"Latitude : "<<endl;
    getline(cin, info_user);
    latitude=stoi(info_user);
    cin.ignore();

    cout<<"Longitude : "<<endl;
    getline(cin,info_user);
    longitude=stoi(info_user);
    cin.ignore();

    cout<<"Rayon : "<<endl;
    getline(cin,info_user);
    rayon=stoi(info_user);
    cin.ignore();

    cout<<"Date de début : "<<endl;
    getline(cin,info_user) ;
    dateDeb=info_user;
    cin.ignore();

    cout<<"Date de fin : "<<endl;
    getline(cin,info_user);
    dateFin=info_user;

    double resultat=s.calculerMoyenneQualiteAir(longitude, latitude, rayon, dateDeb, dateFin);
    cout<<"La moyenne de la qualité de l'air dans la zone spécifiée durant la période de "+ dateDeb + " à "+dateFin+" est de "+resultat+ " (indice ATMO)";

}
*/
Service service = Service();

void initialiserDonnees(const string dataset) {

    string nomFichier = dataset + "/measurements.csv";
    string fichierCapteurs = dataset + "/sensors.csv";
    ifstream fluxLecture, fluxLectureCapteurs;
    fluxLecture.open(nomFichier);
    fluxLectureCapteurs.open(fichierCapteurs);
    string strLigne, date, id, idAjoute, datePrev, ozone, soufre, azote, PM, sensorID, buffer, derniereMesure;
    bool premierCapteurVu = false;
    double latitude, longitude;
    Capteur *capteur = nullptr;
    size_t offset = 0;
    while (!fluxLecture.eof()) {
        getline(fluxLecture, date, ' '); //date initialisée
        getline(fluxLecture, strLigne, ';');
        getline(fluxLecture, id, ';'); //id initialisé
        if (idAjoute != id) {
            if (premierCapteurVu) {
                capteur->setDerniereMesure(datePrev);
            } else {
                premierCapteurVu = true;
            }

            getline(fluxLectureCapteurs, sensorID, ';');
            getline(fluxLectureCapteurs, buffer, ';');
            latitude = stod(buffer, &offset);
            getline(fluxLectureCapteurs, buffer, ';');
            longitude = stod(buffer, &offset);
            getline(fluxLectureCapteurs, buffer); //aller à la ligne suivante
            Capteur c = Capteur(sensorID, longitude, latitude, false, date);
            capteur = &c;
            service.listeCapteurs.push_back(*capteur);

            idAjoute = id;
        }

        datePrev = date;
        getline(fluxLecture, strLigne, ';');
        getline(fluxLecture, ozone, ';');
        getline(fluxLecture, strLigne);
        getline(fluxLecture, strLigne, 'N');
        getline(fluxLecture, strLigne, ';');
        getline(fluxLecture, azote, ';');
        getline(fluxLecture, strLigne);
        getline(fluxLecture, strLigne, 'O');
        getline(fluxLecture, strLigne, ';');
        getline(fluxLecture, soufre, ';');
        getline(fluxLecture, strLigne);
        getline(fluxLecture, strLigne, 'P');
        getline(fluxLecture, strLigne, ';');
        getline(fluxLecture, PM, ';');

        Mesure mesure = Mesure(date, id, stod(PM, &offset), stod(ozone, &offset), stod(soufre, &offset),
                               stod(azote, &offset));
        capteur->addMesure(mesure);

        getline(fluxLecture, strLigne);
    }
    capteur->setDerniereMesure(date);

}



void menuGeneral()
{
    char choix_user;
    string info_user;
    double donnee_user;

    cout << "Bienvenue dans le Menu Principal"<<endl;

    do{
        cout<<"--------------MENU-----------------"<<endl;
        cout<<"Choississez parmi les propositions suivantes"<<endl;
        cout<<"1: Calculer Moyenne "<<endl;
        cout<<"0: Quitter "<<endl;

        cout<<"Votre choix: ";
        cin >> choix_user;
        cout<<"------------------------------------------"<<endl;
        cout<<endl;

        switch(choix_user){
            case '0' :
                cout<<"A bientôt !"<<endl;
                break;
            case '1' :
                //effectuerMoyenne();
                break;

            default : //si l'utilisateur a rentré n'importe quoi
                cout << "Votre choix est incorrect. Pour rappel, vous avez ces possibilités: 0,1"<<endl;
        }
    }while (choix_user !='0');
    return;
} //-------------------------------------------------------------------------- Fin de menuGénéral



void afficher(string chaine){


}



int main(int argc, char *argv[]) {
    initialiserDonnees(argv[1]);
    for(auto & capteur : service.listeCapteurs) {
        cout << capteur << endl;
    }
    menuGeneral();
    return 0;
}