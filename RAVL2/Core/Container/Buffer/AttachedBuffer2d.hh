#ifndef RAVL_ATTACHEDBUFFER2D_HH
#define	RAVL_ATTACHEDBUFFER2D_HH

#include "Ravl/Buffer2d.hh"

namespace RavlN {

  //: 2d Buffer from memory in a 1d buffer.
  
  template<typename DataT>
  class AttachedBuffer2dBodyC
   : public Buffer2dBodyC<DataT>
  {
  public:
    AttachedBuffer2dBodyC()
    {}
    //: Default Constructor
    
    AttachedBuffer2dBodyC(const BufferC<DataT> &buffer,SizeT size1,SizeT size2,IntT byteStride = 0)
      : Buffer2dBodyC<DataT>(buffer.ReferenceElm(),size1,size2,(byteStride != 0) ? byteStride : (size2 * sizeof(DataT)),
                             false,false),
        m_buffer(buffer)
    { RavlAssert((byteStride % sizeof(DataT)) == 0); }
    //: Construct from a 1d buffer.
    
  protected:
    BufferC<DataT> m_buffer;
  };

    //: 2d Buffer from memory in a 1d buffer.

  template<typename DataT>
  class AttachedBuffer2dC
   : public Buffer2dC<DataT>
  {
  public:
    AttachedBuffer2dC()
    {}
    //: Default Constructor
    
    AttachedBuffer2dC(const BufferC<DataT> &buffer,SizeT size1,SizeT size2,IntT byteStride = 0)
      : Buffer2dC<DataT>(new AttachedBuffer2dBodyC<DataT>(buffer,size1,size2,byteStride))
    {}
    //: Construct from a 1d buffer.

  protected:
    AttachedBuffer2dC(AttachedBuffer2dBodyC<DataT> *body)
      : Buffer2dC<DataT>(body)
    {}
  };

}


#endif	

