#ifndef IMGIOSEQ_HEADER
#define IMGIOSEQ_HEADER 1
////////////////////////////////////////////////////
//! rcsid="$Id: ImgIOSeq.hh 40 2001-04-23 16:17:51Z craftit $"

#include "amma/DP/SPort.hh"
#include "amma/DP/FileSeq.hh"

template<class DataT>
class DPImageSeqBodyC 
  : public DPFileSequenceBodyC
{
public:
  DPImageSeqBaseBodyC();
  //: Default constructor.
  
protected:
  FileFormatBaseC format; // Format of stream.
};

#endif
