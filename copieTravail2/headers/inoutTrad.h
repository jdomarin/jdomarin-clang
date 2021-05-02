

 // bijection de [|0...4|] -> [|'A'...'E'|] sinon -> '\0'
 char ctol(int c);

 // bijection de [|0...4|] -> [|'1'...'5'|] sinon -> '\0'
 char ctoch(int c);

 // bijection de [|'A'...'E'|] -> [|0...4|] et [|'a'...'e'|] -> [|0...4|] sinon -> -1
 int ltoc(char c);

 // bijection [|'1'...'5'|] -> [|0...4|] sinon -> -1
 int chtoc(char c);

