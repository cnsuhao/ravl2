// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: exSample.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/exSample.cc"
//! author="Kieron Messer"
//! docentry="Ravl.API.Pattern Recognition.Data Set"
//! userlevel=Normal

//: Using SampleC and related classes.

#include"Ravl/PatternRec/SampleVector.hh"
#include"Ravl/PatternRec/SampleLabel.hh"

using namespace RavlN;

int main() {

  SampleVectorC input;
  SampleLabelC output;
  
  VectorC v(2);
  v[0] = 0.0; v[1] = 1.0;
  
  input.Append(v);
  output.Append(0);

  cerr << "Input size: " << input.Size() << "\n";
  cerr << "Output size: " << output.Size() << "\n";
  
  return 0;
}
 
