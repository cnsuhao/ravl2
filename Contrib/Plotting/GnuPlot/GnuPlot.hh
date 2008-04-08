#ifndef GNUPLOT_HH
#define GNUPLOT_HH
////////////////////////////////////////////////////////////////////////////
//! author="Kieron Messer, Bill Christmas"
//! date=""
//! userlevel=Normal
//! docentry="Ravl.API.GUI.Plotting"
//! file=""
//! rcsid="$id$"

#include "Ravl/RCHash.hh"
#include "Ravl/RealRange2d.hh"
#include "Ravl/DList.hh"
#include "Ravl/String.hh"
// --------------------------------------------------------------------------
// **********  GnuPlotC  **************************************************
// --------------------------------------------------------------------------


namespace RavlN {
  class FilenameC;
  class Point2dC;
}

namespace RavlGUIN {

using namespace RavlN;

typedef DListC<Point2dC> PlotT;

//: Use GnuPlot to plot graphs
// <p> This is a simple wrapper for doing basic 2D plots using GnuPlot.
// However more or less any GnuPlot command can be incorporated via the <code>Set()</code> method.</p>
// <p> Multiple plots on the canvas are specified by giving each plot an integer index.</p>
// <p> Plots will autorange except where ranges are specified.</p>
// <p> See the <a href="http://www.gnuplot.info/docs/gnuplot.pdf">GnuPlot</a> manual for full details.</p>
//

class GnuPlotC {
  
    
  public:
    //:-----------------------------------------------
    //: Constructors, copies, assigment, and destructor
    GnuPlotC();
    //: default contructor
  
    //:-------
    //: Adding to plot
    void Set(const StringC &command, const StringC &value);
    //: General method to invoke <a href="http://www.gnuplot.info/docs/gnuplot.pdf">any GnuPlot command</a>

    void AddPoint(IntT n, const Point2dC &pt);
    //: Add a point to plot n

    void AddPoint(IntT n, RealT x, RealT y);
    //: Add a point to plot n

    void AddKey(IntT n, const StringC &key)
      { keys[n] = key; }
    //: Add key title for plot n

    //:-------
    //: Creating plot from current data
    bool Plot(const StringC &outfile="") const;
    //: Plot the current data
    // Specify outfile if file is needed<br>
    // Default is X11 terminal; use <code>View..()</code> or <code>Terminal()</code> to set other formats 

    void View(const FilenameC &file);
    //: As <code>Plot()</code>, but save the plot as a file and view it with corresponding tool.
    // The default file format is pdf, viewed with xpdf.
    // If <code>file</code> has suffix ".ps" or ".png", plot is saved accordingly and displayed with gv or xv.

    void Terminal(const StringC &term) {Set("terminal", term);}
    //: Set the terminal parameters for other  output file or display type
    // For choice of paramters, see section on "terminal" in 
    // <a href="http://www.gnuplot.info/docs/gnuplot.pdf">manual</a>

    //:-------
    //: Setting canvas parameters
    void Title(const StringC &title) {Set("title", title);}
    //: Set the graph title

    void Xlabel(const StringC &xlabel) {Set("xlabel", xlabel);}
    //: Set the x-label axis

    void Ylabel(const StringC &ylabel) {Set("ylabel", ylabel);}
    //: Set the y-label axis

    void Xlo(RealT lo) {range.LCol() = lo;}
    //: Set the x-axis lower limit

    void Xhi(RealT hi) {range.RCol() = hi;}
    //: Set the x-axis upper limit

    void Ylo(RealT lo) {range.BRow() = lo;}
    //: Set the y-axis lower limit

    void Yhi(RealT hi) {range.TRow() = hi;}
    //: Set the y-axis upper limit

    void Size(RealT sz)
      {Set("size", StringC(sz));}
    //: Set display size <i>relative to</i> default size

    void Size(RealT vsz, RealT hsz)
      {Set("size", StringC(vsz)+", "+StringC(hsz));}
    //: Set display size <i>relative to</i> default size

    void With(const StringC &with) {Set("with", with);}
    //: Set the plotting style
    // Default is "lines".  Style must be one of:<br>
    // <code> lines points linespoints impulses dots steps fsteps histeps errorbars labels xerrorbars yerrorbars xyerrorbars errorlines xerrorlines yerrorlines xyerrorlines boxes histograms filledcurves boxerrorbars boxxyerrorbars financebars candlesticks vectors image rgbimage pm3d </code> <br>
    // (See <a href="http://www.gnuplot.info/docs/gnuplot.pdf">manual</a> for more info)

  protected:
    //: Class members
    RCHashC<StringC, StringC>list;
    //: Holding gnuplots commands
    RCHashC<IntT, PlotT> plots;
    //: Holds points for each graph
    RCHashC<IntT, StringC> keys;
    //: Holds key titles for each graph
    RealRange2dC range;
    //: Store the range
    
   
};

}

#endif
