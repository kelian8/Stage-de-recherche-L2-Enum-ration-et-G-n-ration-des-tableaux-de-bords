/*  
std::string nobord(std::vector<std::string> w, std::vector<std::string> alphabet){
  for(int i =0;i<alphabet.size();i++){
    
    if (std::find(w.begin(), w.end(), alphabet[i]) == w.end()){
      //std::find(V.itera1,V.itera2,value) renvoit  V.ietra2 si la valeur value nest pas dans V et sinon l'indice de la 1 ere occurence de la valeur
      
	return alphabet[i];
	  }
  }
  return "alphabet trop petit";
}
*/



//////////////////
/*
void generate_string_combinations_helper(const std::string& str,const std::vector<std::string>& symbols,std::vector<std::string>& result,std::string current,size_t index,const std::vector<size_t> zero_indices) {
    if (index == zero_indices.size()) {
        result.push_back(current);
        return;
    }

    size_t zero_pos = zero_indices[index];
    for (const auto& symbol : symbols) {
        // Remplacer '0' par le symbole entier
        std::string temp = current;
        temp.replace(zero_pos, 1, symbol);
        generate_string_combinations_helper(str, symbols, result, temp, index + 1, zero_indices);
    }
}

std::vector<std::string> generate_string_combinations(const std::string& str,const std::vector<std::string>& symbols) {
  if (symbols.empty()) {
        for (char c : str) {
            if (c == '0') {
                return {};
            }
        }
    }

    std::vector<size_t> zero_indices;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '0') {
            zero_indices.push_back(i);
        }
    }

    std::vector<std::string> result;
    std::string current = str;

    if (zero_indices.empty()) {
        result.push_back(str);
        return result;
    }

    generate_string_combinations_helper(str, symbols, result, current, 0, zero_indices);
    return result;
} 


std::vector<std::string> TBtoPW(std::vector<int> tb, std::vector<std::string> alpha ){
  std::vector<std::string> res;
  std::string mot = LPtoWord(BorderToPlist(tb),alpha);
  std::vector<int> pos;
  for(int i =1; i<tb.size();i++){
    if (tb[i]==0){
      pos.push_back(i);
    }
  }
  for(int i=0;i<pos.size();i++){
    mot[pos[i]]='0';
  }
  res = generate_string_combinations(mot, alpha);
  for(int i =0;i<res.size();i++){
    if( WtoB(res[i])!=tb){
      res.erase(res.begin() + i);
      i--;
    }
    int maxj=0;
    for(int j=0;j<res[i].size();j++){

      std::string symbol(1, res[i][j]);
      auto itera = std::find(alpha.begin(), alpha.end(),symbol );
      int indice = std::distance(alpha.begin(), itera);
      if(indice>maxj+1){
	res.erase(res.begin()+i);
	i--;
	break;
      }
      else{
	if(maxj<indice){
	  maxj++;
	}
      }
    }
  }
  return res;
}
*/

std::vector<std::string> bannedletter(std::vector<int> tb, std::string w,int i){//algo qui etant donné un tableau de bordures et un mot ainsi qu'un indice, renvoit un tableau  de lettre interdite à placer à l'indice i afin de respecter le tableau de bordures.
  std::vector<std::string> res;//création du tableau à renvoyer
  res.push_back(std::string(1,w[0]));// 1 ère lettre interdite : la première lettre du mot pour pas avoir une bordure à 1
  res.push_back(std::string(1,w[tb[i-1]]));// 2 ème lettre interdite : la lettre contenu dans le mot à l'indice tb[i-1], lettre interdite car elle continuerai la bordure précédente bordure   
  return res;
}

/*
std::vector<std::string>  BtoPW(std::vector<int> tb , std::vector<std::string> alpha){
  std::vector<std::string> res;
  int maxlet =0;
  std::vector<int> pos;
  std::vector<std::string> banl;
  std::string w;
  w+=alpha[0];
  

  for(int i=1;i<tb.size();i++){
    
    if(tb[i]==0){
      banl=bannedletter(tb, w,i);
      
      for(int j=0; j<maxlet+2;j++){
	if(std::find(banl.begin(), banl.end(), alpha[j]) == banl.end()){
	  w+=alpha[j];
	}
      }
    }
    else{
      w+=w[tb[i]-1];
    }
  }
  res.push_back(w);


  return res;
}
  
*/


/*
std::vector<std::string>  BtoPW(std::vector<int> tb , std::vector<std::string> alpha){
  std::vector<std::string> res;
  int maxlet =0;
  std::vector<int> pos;
  std::vector<std::string> banl;
  std::string w;
  w+=alpha[0];
  

  for(int i=1;i<tb.size();i++){
    
    if(tb[i]==0){
      banl=bannedletter(tb, w,i);
      
      for(int j=0; j<maxlet+2;j++){
	if(std::find(banl.begin(), banl.end(), alpha[j]) == banl.end()){
	  w+=alpha[j];
	}
      }
    }
    else{
      w+=w[tb[i]-1];
    }
  }
  res.push_back(w);


  return res;
}
  
*/
