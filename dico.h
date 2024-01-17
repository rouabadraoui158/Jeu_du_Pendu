//Primitives du Dictionnaire
#ifndef DEF_DICTIONNAIRE
#define DEF_DICTIONNAIRE
int piocherMot(char *motPioche);                
int nombreAleatoire(int nombreMax);       
      
void dicoAfficher(TArbre a);
void afficherMots(char *mot, TArbre a); 
        
void dicoInsererMot(char mot[], TArbre *a); 
void insererMot(char *mot, TArbre *a);

int dicoNbOccMot(char mot[],TArbre noeud);       
int dicoNbMotsDifferents(TArbre a);        
int dicoNbMotsTotal(TArbre a); 
 
void lettrespercentage( TArbre a);           
#endif


