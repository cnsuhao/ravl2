#ifndef RAVL_ATTACHEDBUFFER3D_HH
#define	RAVL_ATTACHEDBUFFER3D_HH

#include "Ravl/Buffer3d.hh"
#include "Ravl/IndexRange3d.hh"

namespace RavlN {

  //: 2d Buffer from memory in a 1d buffer.
  
  template<typename DataT>
  class AttachedBuffer3dBodyC
   : public Buffer3dBodyC<DataT>
  {
  public:
    AttachedBuffer3dBodyC()
    {}
    //: Default Constructor
    
    AttachedBuffer3dBodyC(const BufferC<DataT> &buffer,
                          SizeT size1,SizeT size2,SizeT size3,
                          IntT byteStride1 = 0,IntT byteStride2 = 0)
      : Buffer3dBodyC<DataT>(buffer.ReferenceElm(),
                             size1,size2,size3,
                             (byteStride1 != 0) ? byteStride1 : (size3 * size2 * sizeof(DataT)),
                             (byteStride2 != 0) ? byteStride2 : (size3 * sizeof(DataT)),
                             false,false),
        m_buffer(buffer)
    {
      RavlAssert((byteStride1 % sizeof(DataT)) == 0);
      RavlAssert((byteStride2 % sizeof(DataT)) == 0);
    }
    //: Construct from a 1d buffer.
    
    AttachedBuffer3dBodyC(const BufferC<DataT> &buffer,
                          const IndexRange3dC &frame,
                          IntT byteStride1 = 0,IntT byteStride2 = 0)
      : Buffer3dBodyC<DataT>(buffer.ReferenceElm(),
                             frame.Is(),frame.Js(),frame.Ks(),
                             (byteStride1 != 0) ? byteStride1 : (frame.Js() * frame.Ks() * sizeof(DataT)),
                             (byteStride2 != 0) ? byteStride2 : (frame.Ks() * sizeof(DataT)),
                             false,false),
        m_buffer(buffer)
    {
      RavlAssert((byteStride1 % sizeof(DataT)) == 0);
      RavlAssert((byteStride2 % sizeof(DataT)) == 0);
    }
    //: Construct from a 1d buffer.

  protected:
    BufferC<DataT> m_buffer;
  };

    //: 2d Buffer from memory in a 1d buffer.

  template<typename DataT>
  class AttachedBuffer3dC
   : public Buffer3dC<DataT>
  {
  public:
    AttachedBuffer3dC()
    {}
    //: Default Constructor
    
    AttachedBuffer3dC(const BufferC<DataT> &buffer,SizeT size1,SizeT size2,SizeT size3,IntT byteStride1 = 0,IntT byteStride2 = 0)
      : Buffer3dC<DataT>(new AttachedBuffer3dBodyC<DataT>(buffer,size1,size2,size3,byteStride1,byteStride2))
    {}
    //: Construct from a 1d buffer.
    
    AttachedBuffer3dC(const BufferC<DataT> &buffer,const IndexRange3dC &frame,IntT byteStride1 = 0,IntT byteStride2 = 0)
      : Buffer3dC<DataT>(new AttachedBuffer3dBodyC<DataT>(buffer,frame,byteStride1,byteStride2))
    {}
    //: Construct from a 1d buffer.

  protected:
    AttachedBuffer3dC(AttachedBuffer3dBodyC<DataT> *body)
      : Buffer3dC<DataT>(body)
    {}
  
  };

}


#endif	

