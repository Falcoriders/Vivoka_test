/*CHARLES Jack-antoine*/
/*22.11.2019*/
/*Vivoka_test*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//FUNCTIONS
int rand_bounded(int min_b,int max_b)
{
    return(rand()%(max_b-min_b)+min_b);
}

//MAIN
int main()
{
    /*INITIALIZATIONS*/
    string name("Anonymous"); // nom du joueur
    string status("Lost"); // statut de la partie, pr�somption d'�chec

    srand(time(NULL)); // initialisation de rand
    int i; // variable de boucle
    int j; // variable de boucle
    int min_bound = 0; // borne minimum
    int max_bound = 100; // borne maximum
    int max_trial = 10; // nombre maximum d'essais
    int nb_trial = 0; // variable plusieurs fois manipul�e afin dec onnaitre les tentatives restantes et le nombre d'essais effectu�s
    int trial = 0; // valeur de la tentative du joueur
    int digit = rand_bounded(min_bound,max_bound+1); // donne les bornes du chiffre � trouver
    bool non_valid = 1; // aide � la v�rification de la validit� de la valeur de la tentative et pour l'affichage des meilleurs scores
    int cpt = 0; // un compteur qui servira dans la lecture des scores enregistr�s
    int score; // score � inscrire dans best_scores
    int best_scores[5] = {0}; // 0 �tant un score impossible

    /*START*/
    /*Name of the player*/
    cout << "What's your name ?" << endl;
    cin >> name;
    cout << "\nWelcome " << name << "." << endl;

    /*Game*/
    cout << "Guess the digit between 0 and 100 (both included)" << endl;
    do // boucle principale
    {
        do // verification de la validit� de la valeur de la tentative du joueur
        {
            cout << "\nRemaining trial(s) : " << max_trial-nb_trial << endl;
            cin >> trial;
            if(trial<=max_bound && trial>=min_bound)
            {
                non_valid = 0;
            }
            else
            {
                    cout << "Invalid entry, try again" << endl;
            }
        }while(non_valid);
        // Il aurait �t� encore plus pr�cis de v�rifier le type de l'entr�e grace � un outils similaire � "typeof"
        non_valid = 1; // remise � zero de la validit� pour le prochain (possible) essai
        if(trial<digit) // premier cas : la valeur de la tentative est inf�rieure � celle recherch�e
        {
            cout << "\nIt's more" << endl;
        }
        else
        {
            if(trial>digit) // deuxieme cas : la valeur de la tentative est sup�rieure � celle recherch�e
            {
                cout << "\nIt's less" << endl;
            }
            else  // dernier cas : la valeur de la tentative est �gale � celle recherch�e
            {
                cout << "\nBingo !" << endl;
                nb_trial=nb_trial+max_trial; // pour terminer la partie tout en conservant l'information sur le nombre d'essais effectu�s
                status = "Won"; // la partie est gagn�e

            }
        }
        nb_trial=nb_trial+1;
    }while(nb_trial<max_trial);

    /*END*/
    /*Date*/
    time_t now = time(0); // date du systeme
    char* date = ctime(&now); // conversion en caracteres

    /*Attitude if victory or not*/
    if(status=="Won") // en cas de victoire
    {
        nb_trial=nb_trial-max_trial; // recuperation de l'information sur le nombre de tentatives effectu�es
    }
    else
    {
            cout << "The answer was : " << digit << endl; // sinon affichage de la r�ponse
    }

    /*Score writing*/
    ofstream record_stream("record.txt", ios::app); // �criture du score dans un fichier
    if(record_stream) // test sur la bonne ouverture du fichier
    {
        cout << "Score recorded" << endl;
        record_stream << name << "\n" << date << nb_trial << "\n" << status << "\n\n" << endl;
    }
    else
    {
        cout << "Score recording error" << endl;
    }
    record_stream.close();

    /*Score reading and printing*/
    ifstream read_stream("record.txt");
    if(read_stream) // test sur la bonne ouverture du fichier
    {
        string ligne; // stockage de la ligne
        while(getline(read_stream, ligne)) // lecture jusqu'� la fin du fichier
        {
            if(ligne==name && ligne!="Anonymous") // lancement du compteur si la section de fichier correspond au joueur actuel
            {
                cpt = 3;
            }
            if(cpt>0) // d�cr�mentation du compteur
            {
                cpt = cpt-1;
            }
            if(cpt==1) // ligne correspondant au score
            {
                i = 0;
                read_stream >> score;
                do
                {
                    if(best_scores[i]==0) // s'il n'y a pas encore de score enregistr� � cet emplacement
                    {
                        best_scores[i] = score;
                        non_valid = 0; // ce score est enregistr� comme meilleur score, passage au suivant
                    }
                    else
                    {
                        if(best_scores[i]>score) // si le score est meilleur que celui enregistr�
                        {
                            for( j=4; j>i; j=j-1) // on d�cale les scores pour y inclure le "nouveau"
                            {
                                best_scores[j] = best_scores[j-1];
                            }
                            best_scores[i] = score;
                            non_valid = 0; // ce score est enregistr� comme meilleur score, passage au suivant
                        }
                    }
                    i = i+1; // comparaison avec le prochain score dans le tableau
                }while(non_valid);
                non_valid = 1;
            }

        }
        for( j=0; j<5; j=j+1) // affichage du tableau des scores
        {
            if(best_scores[j]!=0 && best_scores[j]!=10) // on n'affiche que les parties victorieuses
            {
                cout << best_scores[j] << endl;
            }
        }
    }
    else
    {
        cout << "Scores reading error" << endl;
    }
    read_stream.close();

    return 0;
}
