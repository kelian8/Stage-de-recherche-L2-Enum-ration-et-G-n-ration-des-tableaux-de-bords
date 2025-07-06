#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <unordered_set>

//fonction permettant de passer d'une table de bordures à une liste de préfixes
std::vector<int> BorderToPlist(std::vector<int> b){
  std::vector<int> L; //liste vide à renvoyer qui servira de  resultat
  int l; //permet de stocker la valeur de b a l'indice i
  int i = b.size()-1; // indice permettant de parcourir la liste de la droite vers la gauche 
  
  while(i>0){
    l=b[i];
    
    if(l==0){
      i=i-1;
	}
    
    else{
      i=i-l;
	}
    
    L.insert(L.begin(), l); // ajoute l au debut de L
  }
  
  return L;
}

//////////////////

// fonction permettant de passer d'une table de préfixes à une liste de préfixes
std::vector<int> PrefixToList(const std::vector<int>& P) {
  std::vector<int> L;  //création d'une liste vide pour les résultats
  int i = P.size() - 1; //indice permettant de parcourir la liste de droite à gauche 

    while (i > 0) {
      std::vector<int> I; //liste pour stocker les indices de 1 à i respectant la condition
        for (int j = 1; j <= i; j++) {
	  if (j + P[j] - 1 >= i) {  //la condition
                I.push_back(j);
            }
        }

        int l;
        if (I.empty()) { // si la liste est vide l = 0 et on décremente i de 1
            l = 0;
            i = i - 1;
        } else {        //si elle n'est pas vide l = i - minI + 1 et on décremente i de minI-1
            int minI = *std::min_element(I.begin(), I.end());
            l = i - minI + 1;
            i = minI - 1;
        }
        
        L.insert(L.begin(), l);  // on ajoute l au début de L
    }

    return L;
}



//////////////////

//fonction permettant de construire  un alphabet [µ1,µ2,...µn-1]
std::vector<std::string> creaAlph(int n){
  std::vector<std::string> alphabet;
  for (int i =1;i<n;i++){
    alphabet.push_back("µ"+ std::to_string(i));   
      }

  return alphabet;
}


///////////////////

//fonction permettant de renvoyer la première lettre la première à ajouter au mot, contenue dans l'aphabet permettant de créer un 0 dans la table de bords 
std::string nobord(std::vector<std::string> w, std::vector<std::string> alphabet) {
    if (w.empty()) {
        return alphabet.size() > 0 ? alphabet[0] : "alphabet trop petit";
    }

    std::unordered_set<std::string> A_prime;
    int n = w.size();
    for (int j = 1; j < n; ++j) {
        bool is_border = true;
        for (int k = 0; k < j; ++k) {
            if (w[k] != w[n - j + k]) {
                is_border = false;
                break;
            }
        }
        if (is_border && j < n) {
            A_prime.insert(w[j]);
        }
    }

    // Choisir une lettre absente de A_prime et différente de w[n-1] si possible
    std::string last_letter = w[n-1];
    for (const auto& letter : alphabet) {
        if (A_prime.find(letter) == A_prime.end() && letter != last_letter) {
            return letter;
        }
    }
    // Si aucune lettre différente n’est disponible, prendre une lettre absente de A_prime
    for (const auto& letter : alphabet) {
        if (A_prime.find(letter) == A_prime.end()) {
            return letter;
        }
    }
    return "alphabet trop petit";
}

////////////////

//fonction permettant de passer d'une liste de préfixe à un mot crée sur un alphabet
std::string LPtoWord(std::vector<int> lp, std::vector<std::string> alpha){
  std::vector<std::string> w(100,"-1"); //créer un tableau vide de 100 case remplies de -1 pour stocker les lettres du mots dans l'ordre 
  w[0] = alpha[0]; //la première lettre du mot est la prmière lettre de l'alphabet 
  int pos=1; // donc on initialise la position a 1
  
  for(int i =0;i<lp.size();i++){ // on parcourt chaque valeurs de la liste de prefixe
    if (lp[i]>0){// on verifie si sa valeur est superieur a 0
      
      for(int j =0;j<lp[i];j++){// si oui on recopie les i-1 lettres precedentes 
	w[pos+j]=w[j];
      }

      pos=pos+lp[i];// on met a jour la position 
    }
    
    else{
      std::vector<std::string> w_slice(w.begin(), w.begin() + pos);//sinon on prends le sous mots actuellement construit et on le passe a nobord avec l'alphabet
      w[pos] = nobord(w_slice, alpha); // nobord renvoit une lettre de l'alphabet non presente dans le sous mot construit jusque la, ce qui permet de respecter un 0 dans la table de bord
      pos+=1;//on met a jour la position 
      }
  }
  std::string wres;
  for(int n=0;n<pos;n++){// on transforme le mot contenu dans le tableau sous forme de string 
    wres+= w[n];
  }
  return wres;// et on renvoit la string 
}


////////////////////////////////////

//fonction permettant de passer d'un mot à une table de bordures
std::vector<int> WtoB(std::string w){
  std::vector<int> res(w.size(),0);//initialistaion du tableau de bordures de taille=longueur de w avec des 0
  
  for(int i=1;i<w.size();i++){//boucle parcourant w
    int b=res[i-1];//bordure précedente
    while(b>0 and w[i]!=w[b]){//tant que la bordure est plus grande que 0 et que w[i]!=w[b]
      b=res[b-1];//on prend la bordure precedente.
    }
    //en gros on cherche la derniere bordure telle que la derniere lettre de cette bordure soit égale a la lettre de w a l'indice i, et si la bordure precedente est 0 alors ca veut dire que la bordure a l'indice i est 0.  
    if(w[b]==w[i]){//si on a trouvé que une telle bordure 
      res[i]=(b+1);//on rajoute la taille de la bordure trouvee + 1 a l'indice i du tableau
    }
    else{
      res[i]=0; //si aucune bordure n'a été trouvé, (cest a dire que la bordure precedente est 0 et que w[0]!=w[i]) on met 0 a l'indice i du tableau 
    }
  }
  return res;// on renvoit le tableau resultat
}


///////////////////////////

//fonction permettant de calculer la longueur du plus long bord du mot ua, où u est un mot,
// B est la table de bordures de u, et a est une lettre à ajouter.
int Border(std::vector<int> b, std::vector<std::string> u, std::string a){
  if(u.size()>0){
    int i =b[(u.size()-1)];
    while (i>-1 and i<u.size() and (u[i]!=a)){
      if (i==0){
	i=-1;
      }
      else{
	i=b[i-1];
      }
    }
    return i+1;
  }
  else{
    return 1;
  }
}

//fonction permettant de passer d'une liste de préfixes à un mot minimal (càd avec le moins de lettres différentes possible) sur un alphabet
std::string LtoMinW(std::vector<int> l, std::vector<std::string> alpha){
  std::vector<int> k(100,0);
  k[0]=0;
  
  std::vector<std::string> w(100,"-1");
  w[0]=alpha[0];
  
  std::vector<int> B(100,0);
  B[0]=0;

  int pos=1;
  
  for(int i =0; i <l.size();i++){
    
    if (l[i]>0){
      for (int j=0; j<l[i];j++){
	w[pos+j]=w[j];
	
	std::vector<std::string> w_slice(w.begin(), w.begin() + pos+j-1);
	B[pos+j]=Border(B, w_slice, w[pos+j]);
	k[pos+j]=k[B[pos+j-1]];
      }
      pos=pos+l[i];
    }
    else{
      k[pos]=1+k[B[pos-1]];
      w[pos]=alpha[k[pos]];
      pos+=1;
    }
  }
  std::string wres;
  for(int n=0;n<pos;n++){
    wres+= w[n];
  }
  return wres;
}


//////////////////

//fonction permttant de renvoyer les lettres interdites à placer à l'indice i d'un mot, pour pouvoir respecter le 0 à l'indice i de la table de bords
std::vector<std::string> bannedletter(std::vector<int> tb, std::string w,int i){//algo qui etant donné un tableau de bordures et un mot ainsi qu'un indice, renvoit un tableau  de lettre interdite à placer à l'indice i afin de respecter le tableau de bordures.
  std::vector<std::string> res;//création du tableau à renvoyer
  res.push_back(std::string(1,w[0]));// 1 ère lettre interdite : la première lettre du mot pour pas avoir une bordure à 1
  res.push_back(std::string(1,w[tb[i-1]]));// 2 ème lettre interdite : la lettre contenu dans le mot à l'indice tb[i-1], lettre interdite car elle continuerai la bordure précédente bordure   
  return res;
}


// Fonction récursive pour générer tous les mots p-canoniques
void generate_words(std::vector<int> tb, std::vector<std::string> alpha, std::string w, int i, int maxlet, std::vector<std::string>& res) {
  if (i == tb.size()) {//si on arrive à la fin du tableau de bordure 
    res.push_back(w); // Mot complet ajouté au résultat
    return;
  }

  if (tb[i] == 0) {//si on rencontre un zéro 
    
    std::vector<std::string> banl = bannedletter(tb, w, i);//tableau des lettres interdites 
    for (int j = 0; j < maxlet + 2 && j < alpha.size(); j++) {
      //On regarde quelles lettres peuvent ^etre utilisées , càd : non contenue dans dans banl et si c'est une nouvelle lettre, cela doit etre la lettre venant juste après la dernière lettre differente utilisée  dans l'alphabet (ex si la derniere lettre ajoutée est "b" alors on ne peut qu'ajouter "c" pas de "d" "z" etc)  
      if (std::find(banl.begin(), banl.end(), alpha[j]) == banl.end()) {//
        w += alpha[j];
	if(j==maxlet+1){ 
	   generate_words(tb, alpha, w, i + 1,maxlet+1, res);
	}
	else{
	  generate_words(tb, alpha, w, i + 1,maxlet, res);
	}
        w.pop_back(); // Retirer la lettre pour essayer la suivante
      }
    }
  }
  else {//si on rencontre autre chose qu'un zéro
    w += w[tb[i] - 1];// on ajoute la lettre a l'indice w[tb[i]-1] (càd à l'indice correspondant à la valeur i dans le tableau de bords -1) (ex si la valeur a l'indice i est 3 on va chercher la lettre a l'indice 3-1=2 dans w soit la lettre w[2])
    generate_words(tb, alpha, w, i + 1, maxlet, res);
  }
}

//fonction faisant appel à generate_words() et permettant de generer tous les mots p-canonniques correspondants a une table de bords donnée sur un alphabet donné
std::vector<std::string> BtoPW(std::vector<int> tb, std::vector<std::string> alpha) {
  std::vector<std::string> res; //tableau résultat
  int maxlet = 0;//nombre de lettre différente utilisée
  std::vector<std::string> banl; //tableau des lettres interdites
  std::string w; //mot vide pour l'instant
  w += alpha[0];// n'importe quel mot associé a une table non vide commence par la première lettre de l'alphabet
  generate_words(tb, alpha, w, 1, maxlet, res);//appel a la fonction generate_words
  return res;
}
