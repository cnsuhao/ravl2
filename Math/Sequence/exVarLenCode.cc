
#include "Ravl/VarLenCode.hh"  
#include "Ravl/DList.hh"    
#include "Ravl/DLIter.hh"  
#include "Ravl/EntryPnt.hh"
#include "Ravl/BitStream.hh"
#include "Ravl/Option.hh"
#include "Ravl/OS/Filename.hh"


int exVarLenCode (int argc, char** argv)
{

  OptionC opt(argc, argv);
  FilenameC streamfile (opt.String("strm", NULL, "bitsream file name"));

  // build table
  VariableLengthCodeC code_table(3);
  code_table.Add("0", 0);
  code_table.Add("10", 1);
  code_table.Add("11", 2);

  // build encoder lookup table;
  SArray1dC< SArray1dC <bool > > encoder_table(3);
  SArray1dC< bool> token0(1); token0[0] = 0;
  encoder_table[0] = token0;
  SArray1dC< bool> token1(2); token1[0] = 1; token1[1] = 0;
  encoder_table[1] = token1;
  SArray1dC< bool> token2(2); token2[0] = 1; token2[1] = 1;
  encoder_table[2] = token2;
  VariableLengthEncoderC encoder(encoder_table);

  // build example bitstream 
  OBitStreamC ostrm(streamfile);
  encoder.Put(2, ostrm);
  encoder.Put(0, ostrm);
  encoder.Put(0, ostrm);
  encoder.Put(1, ostrm);
  encoder.Put(1, ostrm);
  ostrm.Flush();
  ostrm.~OBitStreamC();

  // input bitstream
  IBitStreamC istrm(streamfile);

  // decode bitstream
  VariableLengthCodeIterC decoder(code_table);
  while(istrm.good()){ // 8 extra 0's are output at the end..
    decoder.NextToken(istrm); 
    cout <<  decoder.Data() << " ";
  }
  cout << "\n";

  return 0;
}



//: This puts a wrapper around the main program that catches
//: exceptions and turns them into readable error messages.

RAVL_ENTRY_POINT(exVarLenCode);
