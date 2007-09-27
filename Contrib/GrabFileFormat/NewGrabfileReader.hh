#if !defined(RAVL_NEWGRABFILEREADER_HEADER)
#define RAVL_NEWGRABFILEREADER_HEADER
//! rcsid="$Id: $"
//! lib=RawVid
//! author="Simon Tredwell"
//! docentry="Ravl.API.Images.Video.Video IO.RawVid"

#include "Ravl/Image/GrabfileReader.hh"

namespace RavlImageN {

GrabfileReaderC* NewGrabfileReader(const char* filename, bool legacy = false);
//: Creates a new grabfile reader.
// This allocates an new GrabfileReader. The caller is responsible for deleting the allocated object.
//!param: filename - The filename to create the reader for.
//!param: legacy - Create a reader for legacy files. (The <tt>filename</tt> will be ignored.)
//!return: A pointer to a newly allocated GrabfileReader or 0 if there is no reader available for the file <tt>filename</tt>.

}

#endif // RAVL_NEWGRABFILEREADER_HEADER
