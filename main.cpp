#include "package_outils.cpp"

#include "vector"
#include <stdio.h>
#include <string>
#include <iostream>


int main(){
  printf( "ca commence \n");
  
  std::vector<int> tb = {0,1,0,1,2};

  std::vector<int> tp = {5,0,0,1,0};
  
  std::vector<int> lp = BorderToPlist(tb);

   std::vector<int> lp2 = PrefixToList(tp);

  printf("Avec BorderToLPlist : [");
    
  for (int i=0; i<lp.size();i++){
    std::cout << lp[i];
    if (i!=(lp.size()-1)){
      printf(",");
    }
  }
  
  printf("] \n");


  printf("Avec PrefixToList : [");
    
  for (int i=0; i<lp2.size();i++){
    std::cout << lp2[i];
    if (i!=(lp2.size()-1)){
      printf(",");
    }
  }
  
  printf("] \n");


  std::vector<std::string> alphabet = creaAlph(26);

  
  
  std::string w = LPtoWord(lp, alphabet);
  printf("voici le mot : ");
  std::cout << w ;

  printf("\n");


  printf("***********************************************************\n");
  
  
  std::vector<std::string> wtest = {"µ1","µ1","µ2","µ1","µ3"};
  printf("test nobord([µ1,µ1,µ2,µ1,µ3], alphabet) : ");
  std::cout<<nobord(wtest, alphabet);

  printf("\n");

  printf("***********************************************************\n");

  std::string w2 = "ababbba";
  
  printf("test WtoB avec ");
  std::cout<<w2;

  printf("\n");

  printf("[");
  std::vector<int> tbw = WtoB(w2);
    
  for (int i=0; i<tbw.size();i++){
    std::cout << tbw[i];
    if (i!=(tbw.size()-1)){
      printf(",");
    }
  }
  
  printf("] \n");


  printf("***********************************************************\n");

  printf("test de LtoMinW avec liste de préfixes = ");
  std::vector<int> tb2 = {0,0,1,2,0};
  std::vector<int> lp3 = BorderToPlist(tbw);

  printf("[");
   
  for (int i=0; i<lp3.size();i++){
    std::cout << lp3[i];
    if (i!=(lp3.size()-1)){
      printf(",");
    }
  }
  
  printf("] \n");
  
  std::string w3 = LtoMinW(lp3,alphabet);
  std::cout<<w3;
  
  printf("\n");
  
  printf("***********************************************************\n");
  /*
  std::vector<int> tb3 = {0,0,1,2,3};
  std::vector<std::string> alpha2= {"a","b","c","d","e","f"};
  std::vector<std::string> listemotsp = TBtoPW(tb3,alpha2);
  
  printf("voici la liste  de taille  ");
  std::cout<<listemotsp.size();
  printf(", correspondant a la table de bordure : [");
  for (int i=0; i<tb3.size();i++){
    std::cout << tb3[i];
    if (i!=(tb3.size()-1)){
      printf(",");
    }
  }
  printf("]");
  printf(" sur l'alphabet : [");
  for (int i=0; i<alpha2.size();i++){
    std::cout << alpha2[i];
    if (i!=(alpha2.size()-1)){
      printf(",");
    }
  }
  printf("]");
  printf(": \n");
  printf("[");
  for (int i=0; i<listemotsp.size();i++){
    std::cout << listemotsp[i];
    if (i!=(listemotsp.size()-1)){
      printf(",");
    }
  }
  printf("]\n");

  printf("***********************************************************\n");
  */

  std::vector<int> tb3 = {0,0,0,1,2,0,0};
  std::vector<std::string> alpha2= {"a","b","c","d"};
  std::vector<std::string> listemotsp = BtoPW(tb3,alpha2);

  printf("voici la liste  de taille  ");
  std::cout<<listemotsp.size();
  printf(", correspondant a la table de bordure : [");
  for (int i=0; i<tb3.size();i++){
    std::cout << tb3[i];
    if (i!=(tb3.size()-1)){
      printf(",");
    }
  }
  printf("]");
  printf(" sur l'alphabet : [");
  for (int i=0; i<alpha2.size();i++){
    std::cout << alpha2[i];
    if (i!=(alpha2.size()-1)){
      printf(",");
    }
  }
  printf("]");
  printf(": \n");
  printf("[");
  for (int i=0; i<listemotsp.size();i++){
    std::cout << listemotsp[i];
    if (i!=(listemotsp.size()-1)){
      printf(",");
    }
  }
  printf("]\n");

  for(int i=0;i<listemotsp.size();i++){
    std::cout<<listemotsp[i];
    printf(" correspond à ce tableau : ");
    std::vector<int> tbmotp = WtoB(listemotsp[i]);
     printf("[");
     for (int j=0; j<tbmotp.size();j++){
       std::cout << tbmotp[j];
       if (j!=(tbmotp.size()-1)){
	 printf(",");
       }
     }
     printf("]\n");
  }

  printf("***********************************************************\n");
  
  
  printf("ca finit \n");
  
  return 0;
    
    }


