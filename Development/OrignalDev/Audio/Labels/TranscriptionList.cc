// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: Transcription.cc 3073 2003-06-13 07:18:32Z craftit $"
//! lib=RavlAudioUtil
//! file="Ravl/Audio/Util/TranscriptionList.cc"

#include "Jack/TranscriptionList.hh"
#include "Ravl/Stream.hh"
#include "Ravl/StringList.hh"
#include "Ravl/SArray1dIter.hh"

namespace RavlAudioN {
  
  TranscriptionBaseListC::TranscriptionBaseListC()
      {}
      
      TranscriptionBaseListC::TranscriptionBaseListC(StringC _label)
      : label(_label)
      {}
      
      TranscriptionBaseListC::TranscriptionBaseListC(const DListC<Tuple3C<IntT,RealRangeC,StringC> > &lst, StringC _label)
      : DListC<Tuple3C<IntT,RealRangeC,StringC> > (lst),
	label(_label)
      {}
    //: Constructor.
      
      bool TranscriptionBaseListC::AddEvent(IntT val, RealRangeC range, StringC comment){
      *this+=Tuple3C<IntT,RealRangeC,StringC>(val,range,comment);
      return true;
    }
    
    bool TranscriptionBaseListC::MergeSort(){
      Sort();
      while(true){
	//cerr << label << "  Merge";
	IntT temp = Merge();
	//cerr << "  Sort  ";
	Sort();
	//cerr << temp << "\n";
	if(temp == 0)
	  break;
	
      }
      return true;
    }
    
    StringC &TranscriptionBaseListC::Label()
    {return label;}
    
    
    bool TranscriptionBaseListC::Save(const StringC &filename, bool append){
      OStreamC out(filename,true,true,append);
      for(DLIterC<Tuple3C<IntT,RealRangeC,StringC> >  it(*this);it;it++)
        out << it.Data().Data2().Min() << ' ' << it.Data().Data2().Max() << ' ' << label << '\n';
      return true;
    }
    
    bool TranscriptionBaseListC::Test(RealT time,SArray1dC<UIntT> val){
      for(DLIterC<Tuple3C<IntT,RealRangeC,StringC> >  it(*this);it;it++){
	if(it.Data().Data2().Contains(time)){
	  for(SArray1dIterC<UIntT> jt(val);jt;jt++)
	    if(it.Data().Data1() == *jt)
	      return true;
	}
      }
      return false;
    }
      
      bool TranscriptionBaseListC::Sort()
    {
      
      DListC<Tuple3C<IntT,RealRangeC,StringC> > templist;
      DLIterC<Tuple3C<IntT,RealRangeC,StringC> > it(*this);
       
	  for(unsigned int i = 0;i<Size();i++){
	    RealT value = -1e999;
	    UIntT index = 0;
	    IntT count = 0;
	    for(it.First();it;it++){
	      if(it.Data().Data2().Min() > value){
		value = it.Data().Data2().Min();
		index = count;
	      }
	      count++;
	    }
	    templist.InsFirst(Nth(index));
	    Nth(index) = Tuple3C<IntT,RealRangeC,StringC>();
	  }
	  *this = TranscriptionBaseListC(templist,label);
	  return true;
    }
    
    IntT TranscriptionBaseListC::Merge()
    {
      
      DListC<Tuple3C<IntT,RealRangeC,StringC> > templist;
      
      DLIterC<Tuple3C<IntT,RealRangeC,StringC> > it(*this);
      DLIterC<Tuple3C<IntT,RealRangeC,StringC> > jt(*this);
      
      jt.First();
      jt.Next();
      
      IntT count = 0;
      for(it.First();jt.IsElm()&&it.IsElm();it.Next()){
	
	//requires sorting first
	
	if(it.Data().Data2().IsOverlapping(jt.Data().Data2()) && jt.Data().Data2().Min()!= it.Data().Data2().Max()){ //if labels are overlapping
	  count++;//count to saychange to be made
	  //cerr << it.Data().Data2() << "  " << it.Data().Data1() << "  "<< jt.Data().Data2()<<"  " << jt.Data().Data1() <<  "\n";
	  if(it.Data().Data1() == jt.Data().Data1()){ //if labels are of equal value merge
	    jt.Data().Data2().Min() = it.Data().Data2().Min();
	    if(it.Data().Data2().Max() > jt.Data().Data2().Max())
	      jt.Data().Data2().Max() = it.Data().Data2().Max();
	  }
	  else if(it.Data().Data1()>jt.Data().Data1()){//if label is greater in value
	    if(it.Data().Data2().Contains(jt.Data().Data2())){
	       jt.Data() = it.Data();
	    }
	    else{
	      jt.Data().Data2().Min() = it.Data().Data2().Max();
	      templist.InsLast(it.Data());
	    }
	  }
	  else{//if label is lower in value
	    Tuple3C<IntT,RealRangeC,StringC> temp = it.Data().Copy();
	    temp.Data2().Max() = jt.Data().Data2().Min();
	    templist.InsLast(temp);
	    if(it.Data().Data2().Max() > jt.Data().Data2().Max()){
	      it.Data().Data2().Min() = jt.Data().Data2().Max();
	      templist.InsLast(it.Data());
	    }
	  }
	}
	else
	  templist.InsLast(it.Data());
	jt.Next();
      }
      templist.InsLast(Last());
      //cerr << 1;
      *this = TranscriptionBaseListC(templist,label);
      
      return count;
    }
  
  //: Load from a file.
  
  LabelTranscriptionC::LabelTranscriptionC(const StringC &file,const StringC &nDataFile)
    : dataFile(nDataFile)
  { Load1(file); }

  //: Load transcription from file.
  
  bool LabelTranscriptionC::Load1(const StringC &fileName) {
    IStreamC inf(fileName);
    if(!inf)
      return false;
    Empty();
    StringC tmp;
    bool HTKFormat = false;
    bool first = true;
    while(inf) {
      readline(inf,tmp,'\n',true);
      StringListC fields(tmp);
      UIntT size = fields.Size();
      if(size == 0)
	continue; // Silently skip empty lines.
      if(size < 3) {
	//cerr << "WARNING: Unexpected number of fields. " << fields.Size() << " in " << fileName << " \n";
	continue;
      }
      
      Tuple3C<IntT,RealRangeC,StringC> temp;
      if(StringC(fields.Nth(0)) == "#!MLF!#" && first){
	readline(inf,tmp,'\n',true);
	readline(inf,tmp,'\n',true);
        HTKFormat = true;
        continue;
      }
      first = false;
      if(HTKFormat){
	    temp = Tuple3C<IntT,RealRangeC,StringC>(0,RealRangeC(fields.Nth(0).RealValue()*1e-7,fields.Nth(1).RealValue()*1e-7),StringC(""));
	    //cerr << temp << "\n";
      }
      else{
	   if(size == 3)
	    temp = Tuple3C<IntT,RealRangeC,StringC>(0,RealRangeC(fields.Nth(0).RealValue(),fields.Nth(1).RealValue()),StringC(""));
	   if(size == 4)
	    temp = Tuple3C<IntT,RealRangeC,StringC>(fields.Nth(3).IntValue(),RealRangeC(fields.Nth(0).RealValue(),fields.Nth(1).RealValue()),StringC(""));
	   if(size == 5)
	    temp = Tuple3C<IntT,RealRangeC,StringC>(fields.Nth(3).IntValue(),RealRangeC(fields.Nth(0).RealValue(),fields.Nth(1).RealValue()),fields.Nth(4));	 
      }
	   AddData(fields.Nth(2),temp.Data2(),temp.Data1(),temp.Data3());
	   
	   //cerr << fields.Nth(0) << "  " << fields.Nth(1) << "  "<< fields.Nth(2)<< "\n";
      }
    
    return true;
  }
  
  //: Save transcription to a file.
  bool LabelTranscriptionC::Save(const StringC &filename) {
   
   for(DLIterC<TranscriptionBaseListC> it(*this);it;it++)
     it.Data().Save(filename);
   
    return true;
  }
  
  bool LabelTranscriptionC::MergeSort(){
	for(DLIterC<TranscriptionBaseListC> it(*this);it;it++)
	  it.Data().MergeSort();
	return true;
      }
    
      bool LabelTranscriptionC::Test(StringC label, RealT time, SArray1dC<UIntT> val){
	for(DLIterC<TranscriptionBaseListC> it(*this);it;it++){
	  if(it.Data().Label()==label){
	    return it.Data().Test(time, val);
	  }
	}
	return false;
      }
    
      bool LabelTranscriptionC::AddLabel(StringC label){
	//cerr << "add label";
	InsLast(TranscriptionBaseListC(label));
	return true;
      }
    
      bool LabelTranscriptionC::AddData(StringC label, RealRangeC range, IntT value,StringC comment){
	bool labelfound = false;
	Tuple3C<IntT,RealRangeC,StringC> temp;
	temp = Tuple3C<IntT,RealRangeC,StringC>(value,range,comment);
	for(DLIterC<TranscriptionBaseListC> it(*this);it;it++){
	  if(it.Data().Label() == label){
	    it.Data().InsLast(temp);
	    labelfound = true;
	    break;
	  } 
	}
	if(!labelfound){
	  InsLast(TranscriptionBaseListC(label));
	  Last().InsLast(temp);
	}
	return labelfound;
      }
      

      LabelTranscriptionC::LabelTranscriptionC(const DListC<TranscriptionBaseListC> &lst)
      : DListC<TranscriptionBaseListC> (lst)
      {}
      //: Constructor
      
      StringC &LabelTranscriptionC::DataFile()
      { return dataFile; }
      //: Access data file.
    
      const StringC &LabelTranscriptionC::DataFile() const
      { return dataFile; }
      //: Access data file.
 
}
