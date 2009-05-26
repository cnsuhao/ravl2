#include "Ravl/Plot/GnuPlot.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/Point2d.hh"

namespace RavlGUIN {
using namespace RavlConstN;

GnuPlotC::GnuPlotC()
//==========================================
  : range(nanReal, nanReal, nanReal, nanReal)
{
  //: Set up some sensible default value
  Terminal("x11 persist raise");
  Size(1.0);
  Title("GnuPlot");
  Xlabel("x-label");
  Ylabel("y-label");
  With("lines");
}

void
GnuPlotC::Set(const StringC & com, const StringC &val)
//====================================================
{
  list.Insert(com, val);
}


void
GnuPlotC::AddPoint(IntT i, const Point2dC &pt)
//====================================
{
  plots[i].InsLast(pt);
}

void
GnuPlotC::AddPoint(IntT i, RealT x, RealT y)
//==========================================
{
  Point2dC pt(x, y);
  plots[i].InsLast(pt);
}


bool
GnuPlotC::Plot(const StringC &outfile) const
//===================
{
  if(plots[0].Size()==0) {
    RavlIssueWarning("bool GnuPlotC::Plot() const: No points defined");
    return false;
  }
  
  FilenameC tmpGnu = "/tmp/gnu";
  tmpGnu = tmpGnu.MkTemp();
  RCHashC<IntT, StringC>names(plots.Size());
  {
   
    OStreamC ofsGnu(tmpGnu);
 
    //: Print out the data
    for(HashIterC<IntT, PlotT>it(plots);it;it++) {
      FilenameC tmpData = "/tmp/data" + StringC(it.Key());
      tmpData = tmpData.MkTemp();
      names[it.Key()] = tmpData;
      OStreamC ofsData(tmpData);
      for(DLIterC<Point2dC>pt(*it);pt.IsElm();pt.Next()) ofsData << *pt << endl;
    }
    
    //: Print out the commands
    ofsGnu << "set title \'" << list["title"] << "\'" << endl;
    ofsGnu << "set xlabel \'" << list["xlabel"] << "\'" << endl;
    ofsGnu << "set ylabel \'" << list["ylabel"] << "\'" << endl;
    if (!outfile.IsEmpty())  ofsGnu << "set output \'" << outfile << "\'" << endl;
    ofsGnu << "set size " << list["size"] << endl;
    ofsGnu << "set terminal " << list["terminal"] << endl;
    ofsGnu << "set grid" << endl;
    ofsGnu << "plot ";
    
    //: output ranges
    ofsGnu << "[" << (IsNan(range.LCol()) ? " " : StringC(range.LCol()))
           << ":" << (IsNan(range.RCol()) ? " " : StringC(range.RCol())) << "]"
           << "[" << (IsNan(range.TRow()) ? " " : StringC(range.TRow()))
           << ":" << (IsNan(range.BRow()) ? " " : StringC(range.BRow())) << "] ";

    StringC with = list["with"];
    IntT max=0;
    for(HashIterC<IntT, PlotT>it(plots);it;it++) if (it.Key()>max) max = it.Key();

    for(HashIterC<IntT, PlotT>it(plots);it;it++) {
      FilenameC tmpData = names[it.Key()];
      ofsGnu << "\'" << tmpData << "\' title \"" << keys[it.Key()] << "\" with " << with;
      if(it.Key()<max) ofsGnu << ", ";
      //else ofsGnu << endl;
    }    
  }
  
  //: Run gnuplot
  StringC com = "gnuplot " + tmpGnu;
  cout << com << endl;
  system(com);

  //: Then remove tmp files
  if(!tmpGnu.Remove()) {
    return false;
  }
  for(HashIterC<IntT, PlotT>it(plots);it;it++) {
    FilenameC tmpData = names[it.Key()];
    if(!tmpData.Remove())
      return false;
  }
  
  //: return success
  return true;
}

void
GnuPlotC::View(const FilenameC &out) 
//==============
{
  StringC com;
  if (out.Extension() == "png") {
    Terminal("png");
    Plot(out);
    com = "xv " + out + "&";
  }
  else if(out.Extension() == "ps") {
    Terminal("postscript landscape colour");
    Plot(out);
    com = "gv " + out + "&";
  }
  else {
    Terminal("postscript landscape colour");
    FilenameC tmpGnu = "/tmp/gnu";
    tmpGnu = tmpGnu.MkTemp();
    Plot(tmpGnu);
    com = "ps2pdf " + tmpGnu + " " + out + " && xpdf " + out + "&";
  }
  cerr << "command: " << com << endl;
  system(com);
}


}
