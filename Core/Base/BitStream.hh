// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLBITSTREAM_HEADER
#define RAVLBITSTREAM_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Base/BitStream.hh"
//! lib=RavlCore
//! docentry="Ravl.Core.IO"
//! author="Charles Galambos"
//! date="04/06/99"
//! userlevel=Default

#include "Ravl/Stream.hh"
#include "Ravl/config.h"

namespace RavlN {
  //! userlevel=Develop
  //: Bit stream base.
  
  class BitStreamBaseC  {
  public:  
    BitStreamBaseC()
      : at(1024),
      buff(0)
      {}
    //: Default constructor.
    
    bool IsByteAligned() const { return at == 7; }
    //: Is byte aligned ?
    
    UIntT Mask(UIntT nbits) const 
      { return ((UIntT)1 << (nbits)) -1; }
  //: Create a mask nbits long.
    
  protected:
    IntT  at;   // Bit offset.
    UByteT buff;// Byte ptr.
#ifdef NEW_ANSI_DRAFT
    static const UIntT buffSize = 8;
#else 
    static const UIntT buffSize;
#endif
  };
  
  //! userlevel=Normal
  //: Input bit stream
  // 'at' points to the next bit to read.
  
  class IBitStreamC 
    : public BitStreamBaseC
  {
  public:
    IBitStreamC()
      {}
    //: Default constructor.
  
    IBitStreamC(const StringC &filename)
      : strm(filename)
      { at = -1; }
    //: Constructor.
  
    IBitStreamC(const IStreamC &strm)
      : strm(strm)
      {}
    //: Construct from a normal strm.
    
    inline bool ReadBit() { 
      if(at < 0) {
	strm.read((char *) &buff,1);
	at = buffSize - 1;
      }
      bool ret = (buff >> at) & 1;
      at--;
      return ret;
    }
    //: Read 1 bit from stream.
    
    inline bool PeekBit() {
      if(at < 0) {
	strm.read((char *) &buff,1);
	at = buffSize - 1;
      }
      bool ret = (buff >> at) & 1;
      return ret;
    }
    //: Look at the next bit to be read. but don't retrieve it.
    
    inline UByteT ReadUByte()  {
      UByteT ret;
      if(at < 0) {
	strm.read((char *) &ret,1);
      } else {
	ret = buff << (7-at); // Assumes byte is 0 padded. 
	strm.read((char *) &buff,1);
	ret |= buff >> (at+1);
      }
      //cerr << "Read UByteT: " << ((UIntT) ret) << " Bits:8 at(after):" << at << " \n";
      return ret;
    }
    //: Read a unsigned byte from stream.
  
    inline UByteT ReadUByte(IntT nbits) {
      UByteT ret;
      RavlAssert(nbits <= 8);
      if(at < 0) {
	strm.read((char *) &buff,1);
	at = buffSize-1;
      }
      IntT bitsInBuff = at + 1;
      if(bitsInBuff >= nbits) {
	// This remainder is in the buffer already.
	at -= nbits;
	ret = (buff >> (at+1)) & Mask(nbits) ;
	//cerr << "\nAll bits in buff :" << ((UIntT) ret) << " at:" << at <<" NBits:" << nbits <<" Mask:" << hex << Mask(nbits) <<"\n";
      } else {
	// This remainder goes over a byte boundry.
	at -= bitsInBuff;
	ret = ((buff >> (at+1)) & Mask(bitsInBuff)) << (nbits-bitsInBuff);
	nbits -= bitsInBuff;
	strm.read((char *) &buff,1);
	at = (buffSize-1) - nbits;
	ret |= (buff >> (at+1)) & Mask(nbits);
      }
      //cerr << "Read UIntT: " << hex << ((UIntT) ret) << " Bits:" << nbits << " at(after):" << at << " \n";
      return ret;
    }
    //: Read a bit vector.
    
    UIntT ReadUInt() { 
      UIntT ret;
#if RAVL_BIGENDIAN
      ((UByteT *)&ret)[1] = ReadUByte(); 
      ((UByteT *)&ret)[2] = ReadUByte();
      ((UByteT *)&ret)[3] = ReadUByte();
      ((UByteT *)&ret)[4] = ReadUByte();
#else
      ((UByteT *)&ret)[4] = ReadUByte(); 
      ((UByteT *)&ret)[3] = ReadUByte();
      ((UByteT *)&ret)[2] = ReadUByte();
      ((UByteT *)&ret)[1] = ReadUByte();
#endif
      return ret;
    }
    //: Read an 32-bit unsigned integer.
    // MSB First.
    
    UIntT ReadUInt(UIntT bits) { 
      RavlAssert(bits <= 32);
      UIntT ret = 0;
#if RAVL_BIGENDIAN
      //cerr << "Read UIntT: Bits:" << bits << " at(before):" << at << " \n";
      UByteT *place = &(((UByteT *)&ret)[3-(bits/8)]);
      UIntT rem = bits % 8;
      *place = ReadUByte(rem);
      place++;
      bits -= rem;
      while(bits > 0) {
	*(place++) = ReadUByte();
	bits -=8;
      }
      //cerr <<"Value :" << ret << "\n";
#else
      UByteT *place = &(((UByteT *)&ret)[bits/8]);
      UByteT rem = bits % 8;
      *place = ReadUByte(rem);
      bits -= rem;
      place--;
      while(bits > 7) {
	*place = ReadUByte();
	place--;
	bits -= 8;
      }
      // Read the remainder.
#endif
      return ret;
    }
    //: Read an unsigned integer.
    // MSB First.
    
    IntT ReadInt(UIntT bits) {
      UIntT val = ReadInt(bits);
      UIntT signbit = (1 << (bits-1));
      if(val & signbit) // Not the best way but it'll do for now.
	return signbit - (val & ~signbit);
      return val;
    }
    //: Read a signed integer.
    // MSB First.
    
    inline void DiscardBit() {
      if(at < 0) {
	strm.read((char *) &buff,1);
	at = buffSize - 1;
      }
      at--;
    }
    //: Discard 1 bit from stream.
  
    UByteT NextAlignedByte() {
      UByteT ret;
      strm.read((char *) &ret,1);
      at = -1 ;
      return ret;
    }
    //: Read next byte-aligned byte.
    // This will discard bits between current position
    // and next alignment.
    
    inline bool good() const
      { return strm.good(); }
    //: Is stream good ?
  protected:
    IStreamC strm;
  };
  
  //! userlevel=Normal
  //: Output bit stream.
  // 'at' points to next bit to be written.
  // Numbering from LSB=0
  
  class OBitStreamC 
    : public BitStreamBaseC
  {
  public:
    OBitStreamC() { 
      at = buffSize-1; 
      buff = 0;
    }
    //: Default constructor.
    
    OBitStreamC(const StringC &filename)
      : strm(filename)
    { 
      at = buffSize-1; 
      buff = 0;
    }
    //: Constructor.
    
    OBitStreamC(const OStreamC &strm)
      : strm(strm)
      {}
    //: Construct from a normal stream
    // NB. 'Flush' must be used before any write operations
    // are done on 'strm' after using the class.
    
    ~OBitStreamC();
    //: Close bit stream.
    
    inline void WriteBit(bool val) {
      at--;
      if(val) 
	buff |= 1 << (at+1);
      // Don't write 0's buffer defaults to 0.
      if(at < 0) {
	strm.write((const char *) &buff,1);
	buff = 0;
	at = buffSize-1;
      }
    }
    //: Write 1 bit to stream.
    
    inline void WriteUByte(UByteT byte) {
      //cerr << "Writing UByteT: " << hex << ((UIntT) byte) << " Bits:8 At:" << at << "\n";
      if(at == 7) {
	strm.write((const char *) &byte,1);
      } else {
	buff |= byte >> (buffSize-(at+1));  // Assumes byte is 0 padded.
	strm.write((const char *) &buff,1);
	buff = byte << (at+1);
      }
    }
    //: Write a byte to stream.
    
    inline void WriteUByte(UByteT data,IntT nbits) {
      //cerr << "Writing UIntT: " << hex << ((UIntT) *v) << " Bits:" << nbits << " at:" << at <<"\n";
      RavlAssert(nbits <= 8);
      // Write the remainder.
      IntT bitsInBuff = at+1;
      if(bitsInBuff >= nbits) {
	at -= nbits;
	buff |= (data & Mask(nbits)) << (at+1);
	if(at < 0) {
	  strm.write((const char *) &buff,1);
	  buff = 0;
	  at = buffSize-1;
	}
      } else {
	// at == -1
	buff |= (data >> (nbits-bitsInBuff)) & Mask(bitsInBuff);
	strm.write((const char *) &buff,1);
	nbits -= bitsInBuff;
	at = (buffSize-1)-nbits;
	buff = (data & Mask(nbits)) << (at+1);
      }
    }
    //: Write an array of n bits.
    
    void WriteUInt(UIntT data) { 
#if RAVL_BIGENDIAN
      WriteUByte(((const UByteT *)&data)[1]); 
      WriteUByte(((const UByteT *)&data)[2]);
      WriteUByte(((const UByteT *)&data)[3]);
      WriteUByte(((const UByteT *)&data)[4]);
#else
      WriteUByte(((const UByteT *)&data)[4]); 
      WriteUByte(((const UByteT *)&data)[3]);
      WriteUByte(((const UByteT *)&data)[2]);
      WriteUByte(((const UByteT *)&data)[1]);
#endif
    }
    //: Write an unsigned integer.
    // MSB First.
    
    void WriteUInt(UIntT data,UIntT bits) { 
#if RAVL_BIGENDIAN
      //cerr << "Writing UIntT: " << hex << data << " Bits:" << bits << " \n";
      UByteT *place = &((UByteT *)&data)[3-(bits/8)];
      UIntT rem = bits % 8;
      WriteUByte(*place,rem);
      place++;
      bits -= rem;
      while(bits > 0) {
	WriteUByte(*(place++));
	bits -=8;
      }
#else
      UByteT *place = &((UByteT *) &data)[bits/8];
      WriteUByte(*place,bits % 8);
      place--;
      while(bits > 7) {
	WriteUByte(*(place--)); 
	bits -= 8;
      }
#endif
    }
    //: Write an unsigned integer.
    // MSB First.
    
    void Flush() {
      if(at < 7) {
	strm.write((const char *) &buff,1);
	at = buffSize -1;
	buff = 0;
      }
    }
    //: Flush output buffer. (Use only before closing.)
    
    inline bool good() const
      { return strm.good(); }
    //: Is stream good ?
    
  protected:
    OStreamC strm; 
  };
}


#endif
