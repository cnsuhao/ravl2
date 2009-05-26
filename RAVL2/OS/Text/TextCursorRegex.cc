
#include "amma/TxCursor.hh"

StringC TextCursorC::Clip(const Regex &exp) {
  if(!IsElm())
    return StringC();
  assert((UIntT) Col < LineText().length());
  int len = exp.match(LineText().chars(),LineText().length(),Col);
  if(len < 1)
    return StringC();
  SubStringC txt = LineText().at((int)Col,(int) len);
  //SubStringC txt = LineText().at(exp,Col);
  Col += len;
  if(LineText().length() <= Col)
    NextLine();
  return StringC(txt);
}

BooleanT TextCursorC::Skip(const Regex &exp) {
  if(!IsElm())
    return FALSE;
  assert((UIntT) Col < LineText().length()); 
  int len = exp.match(LineText().chars(),LineText().length(),Col);
  if(len < 1)
    return FALSE;
  //cerr << "TextCursorC::Skip(), Len:" << len << " Col:" << Col << " >" << RestOfLine();
  Col += len;
  if(LineText().length() <= Col)
    NextLine();
  return TRUE;
}
