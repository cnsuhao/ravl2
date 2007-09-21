#if !defined(RAVL_NEWGRABFILEWRITER_HEADER)
#define RAVL_NEWGRABFILEWRITER_HEADER
//! rcsid="$Id: $"
//! author=
//! docentry=
//! lib=

#include "Ravl/Image/GrabfileWriter.hh"

namespace RavlImageN {

GrabfileWriterC* NewGrabfileWriter(const int version);
//: Creates a new grabfile writer.
// This allocates an new GrabfileWriter. The caller is responsible for deleting the allocated object.
//!param: version - The version of the writer to create.
//!return: A pointer to a newly allocated GrabfileWriter or 0 if there is no writer for the given <tt>version</tt>.
}

#endif // RAVL_NEWGRABFILEWRITER_HEADER
