// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include"Ravl/PatternRec/SampleVector.hh"
#include"Ravl/PatternRec/SampleLabel.hh"

using namespace RavlN;

int main() {

  
  SampleVectorC input;
  SampleLabelC output;
  
  VectorC v(2);
  v[0] = 0.0; v[1] = 1.0;
  
  input.Insert(v);
  output.Insert(0);

  cerr << "Input size: " << input.Size() << "\n";
  cerr << "Output size: " << output.Size() << "\n";
  
  cout << input.Pick() << endl;
  cout << output.Pick() << endl;
  
  return 0;
}
 
