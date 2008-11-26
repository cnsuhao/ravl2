// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: DesignClassifierNeuralNetwork.cc,v 1.3 2004/03/18 17:14:37 ees1wc Exp $"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Classify/DesignClassifierNeuralNetwork.cc"

#include "Ravl/PatternRec/DesignClassifierNeuralNetwork.hh"
#include "Ravl/PatternRec/ClassifierNeuralNetwork.hh"
#include "Ravl/VirtualConstructor.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/PatternRec/DataSetVectorLabel.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/fann/fann.h"
#include "Ravl/PatternRec/DataSet2Iter.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/DList.hh"
#include "Ravl/Text/TextFile.hh"

namespace RavlN {
  
  //: Constructor.
  
  DesignClassifierNeuralNetworkBodyC::DesignClassifierNeuralNetworkBodyC(UIntT nLayers, UIntT nInputs, UIntT nHidden, UIntT nOutputs)
    : m_nLayers(nLayers), m_nInputs(nInputs), m_nHidden(nHidden), m_nOutputs(nOutputs)
  {}
  
  //: Load from stream.
  
  DesignClassifierNeuralNetworkBodyC::DesignClassifierNeuralNetworkBodyC(istream &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignClassifierNeuralNetworkBodyC::DesignClassifierNeuralNetworkBodyC(istream &), Unrecognised version number in stream. ");
    strm >> m_nLayers;
    strm >> m_nInputs;
    strm >> m_nHidden;
    strm >> m_nOutputs;
  }
  
  //: Load from binary stream.
  
  DesignClassifierNeuralNetworkBodyC::DesignClassifierNeuralNetworkBodyC(BinIStreamC &strm)
    : DesignClassifierSupervisedBodyC(strm)
  {
    int version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignClassifierNeuralNetworkBodyC::DesignClassifierNeuralNetworkBodyC(BinIStreamC &), Unrecognised version number in stream. ");
    strm >> m_nLayers;
    strm >> m_nInputs;
    strm >> m_nHidden;
    strm >> m_nOutputs;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignClassifierNeuralNetworkBodyC::Save (ostream &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    int version = 0;
    out << ' ' << version << ' ' << m_nLayers << ' ' << m_nInputs << ' ' << m_nHidden << ' ' << m_nOutputs;
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignClassifierNeuralNetworkBodyC::Save (BinOStreamC &out) const {
    if(!DesignClassifierSupervisedBodyC::Save(out))
      return false;
    int version = 0;
    out << version << m_nLayers << m_nInputs << m_nHidden << m_nOutputs;
    return true;
  }
  
  //: Create a clasifier.
  
  ClassifierC DesignClassifierNeuralNetworkBodyC::Apply(const SampleC<VectorC> &in,const SampleC<UIntT> &out) {
    RavlAssertMsg(in.Size() == out.Size(),"DesignClassifierNeuralNetworkBodyC::Apply(), Sample of vector and labels should be the same size.");

    //: Check input dimensionality
    if(in.First().Size() != m_nInputs)
      return ClassifierC();


    //: Need to convert our data set into a dataset for a neural net
    //: The easiest way for now is to save the data to file in the correct format for the library
    //: and then use the lib function to read it back in.  It sucks a little but it is only for training
    DataSet2C<SampleC<VectorC>, SampleC<UIntT> >dset(in, out);
    FilenameC tmpData = "/tmp/nndata";
    tmpData = tmpData.MkTemp();
    FilenameC tmpNN = "/tmp/nn";
    tmpNN = tmpNN.MkTemp();

    //: format of data
    //: data_set_size  number_of_inputs number_of_outputs
    //: input_data seperated by space
    //: output_data seperated by space
    //: ....
    //: ....
    
    {
      OStreamC os(tmpData);
      os << in.Size() << " " << m_nInputs << " " << m_nOutputs << endl;
      for(DataSet2IterC<SampleC<VectorC>, SampleC<UIntT> >it(dset);it;it++) {
	for(SArray1dIterC<RealT>vit(it.Data1());vit;vit++) {
	  os << *vit << " ";
	}
	os << " " << endl;
	
	VectorC nnOutput(m_nOutputs);
	nnOutput.Fill(-0.9);
	nnOutput[it.Data2()] = 0.9;
	for(SArray1dIterC<RealT>vit(nnOutput);vit;vit++) {
	  os << *vit << " ";
	}
	
	os << " " << endl;
      }
    }
    

    //: Next we can build the neural network
    const float desired_error = (const float) 0.001;
    const unsigned int max_epochs = 50000;
    const unsigned int epochs_between_reports = 10;


    struct fann *ann = fann_create_standard(m_nLayers, m_nInputs, m_nHidden, m_nOutputs);

    //: OK now we can train on the neural network
    struct fann_train_data *data = fann_read_train_from_file(tmpData.chars());
    
    //: OK some network settings.   We should really make these available through the interface but not yet/
    fann_set_activation_steepness_hidden(ann, 1);
    fann_set_activation_steepness_output(ann, 1);
    fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_train_stop_function(ann, FANN_STOPFUNC_BIT);
    fann_set_bit_fail_limit(ann, 0.01f);

    //: important to init on training data
    fann_init_weights(ann, data);

    //: do the training
    fann_train_on_data(ann, data, max_epochs, epochs_between_reports, desired_error);
    
    //: work out error on training data
    printf("Testing network. %f\n", fann_test_data(ann, data));

    //: and save network
    fann_save(ann, tmpNN.chars());
    
    //: destroy
    fann_destroy(ann);

    //: What we want to do is to load this into a string
    DListC<StringC> nn;
    {
      TextFileC file(tmpNN);
      for(UIntT i=1;i<=file.NoLines();i++) {
	StringC line = file[i];
	line.gsub(" ", "#");
	line = line.TopAndTail();
	nn.InsLast(line);
      }
    }
    //: return classifier
    tmpData.Remove();
    tmpNN.Remove();
    return ClassifierNeuralNetworkC(m_nLayers, m_nInputs, m_nHidden, m_nOutputs, nn);
  }
  
  //: Create a clasifier with weights for the samples.
  
  ClassifierC DesignClassifierNeuralNetworkBodyC::Apply(const SampleC<VectorC> &in,
							  const SampleC<UIntT> &out,
							  const SampleC<RealT> &weight) {
    RavlAssertMsg(0,"DesignClassifierNeuralNetworkBodyC::Apply(in,out,weight), Not implemented. Send a feature request! ");
    return ClassifierC();
  }
 
  //////////////////////////////////////////////////////////
  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignClassifierNeuralNetworkBodyC,DesignClassifierNeuralNetworkC,DesignClassifierSupervisedC);
  
}
