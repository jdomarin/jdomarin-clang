

char ctol(int c){
  char res = '\0';
  switch(c){
  case 0 :
   res = 'A';
   break;
  case 1 :
   res = 'B';
   break;
  case 2 :
   res = 'C';
   break;
  case 3 :
   res = 'D';
   break;
  case 4 :
   res = 'E';
   break;
  };
  return res;
 } // [|0...4|] -> [|'A'...'E'|] sinon -> '\0'

 char ctoch(int c){
  char res = '\0';
  switch(c){
  case 0 :
   res = '1';
   break;
  case 1 :
   res = '2';
   break;
  case 2 :
   res = '3';
   break;
  case 3 :
   res = '4';
   break;
  case 4 :
   res = '5';
   break;
  };
  return res;
 } // [|0...4|] -> [|'1'...'5'|] sinon -> '\0'

 int ltoc(char c){
  int res = -1;
  switch(c){
  case 'A' :
  case 'a' :
   res = 0;
   break;
  case 'B' :
  case 'b' :
   res = 1;
   break;
  case 'C' :
  case 'c' :
   res = 2;
   break;
  case 'D' :
  case 'd' :
   res = 3;
   break;
  case 'E' :
  case 'e' :
   res = 4;
   break;
  };
  return res;
 } // [|'A'...'E'|] -> [|0...4|] et [|'a'...'e'|] -> [|0...4|] sinon -> -1

 int chtoc(char c){
  int res = -1;
  switch(c){
  case '1' :
   res = 0;
   break;
  case '2' :
   res = 1;
   break;
  case '3' :
   res = 2;
   break;
  case '4' :
   res = 3;
   break;
  case '5' :
   res = 4;
   break;
  };
  return res;
 } // [|'1'...'5'|] -> [|0...4|] sinon -> -1


