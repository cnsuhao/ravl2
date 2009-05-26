// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_LOTTERY_HEADER
#define RAVLPROB_LOTTERY_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"


#include "Ravl/RCHandleV.hh"
#include "Ravl/RCHash.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Class used to represent a a lottery
  // A lottery contains all the possible outcomes with their expected probabilities
  class LotteryBodyC
    : public RCBodyVC {
  public:
    LotteryBodyC(const StringC& type, const RCHashC<StringC,RealT>& outcomes);
    //: Constructor
    //!param: name - the type name for the lottery
    //!param: values - set of outcomes and their probabilities

    virtual ~LotteryBodyC();
    //: Destructor
    
    const StringC& Type() const;
    //: Get the type name of the lottery

    LotteryBodyC& operator*=(const LotteryBodyC& other);
    //: Compute the in place product of two lotteries
    //!param: other - the second lottery
    // Note that both lotteries must be of the same type

    StringC ToString() const;
    //: Create a string representation of the lottery

  private:
    void SetType(const StringC& type);
    //: Set the domain

    const RCHashC<StringC,RealT>& Outcomes() const;
    //: Get the set of outcomes

    void SetOutcomes(const RCHashC<StringC,RealT>& outcomes);
    //: Set the outcomes

  private:
    void Normalize();
    //: Ensure that the outcomes probabilities sum to 1

  private:
    StringC m_type;
    //: The type name of the lottery

    RCHashC<StringC,RealT> m_outcomes;
    //: The set of variables
  };

  //! userlevel=Normal
  //: Class used to represent a a lottery
  // A lottery contains all the possible outcomes with their expected probabilities
  //!cwiz:author
  
  class LotteryC
    : public RCHandleC<LotteryBodyC>
  {
  public:
    LotteryC()
    {}
    //: Default constructor makes invalid handle

    LotteryC(const StringC& type, const RCHashC<StringC,RealT>& outcomes)
      : RCHandleC<LotteryBodyC>(new LotteryBodyC(type, outcomes))
    {}

    const StringC& Type() const
    { return Body().Type(); }
    //: Get the type name of the lottery

    LotteryC operator*=(const LotteryC& other)
    { return Body().operator*=(other.Body()); }
    //: Compute the in place product of two lotteries
    //!param: other - the second lottery
    // Note that both lotteries must be of the same type

    StringC ToString() const
    { return Body().ToString(); }
    //: Create a string representation of the domain
    //!cwiz:author

  protected:
    LotteryC(LotteryBodyC &bod)
     : RCHandleC<LotteryBodyC>(bod)
    {}
    //: Body constructor. 
    
    LotteryC(const LotteryBodyC *bod)
     : RCHandleC<LotteryBodyC>(bod)
    {}
    //: Body constructor. 
    
    LotteryBodyC& Body()
    { return static_cast<LotteryBodyC &>(RCHandleC<LotteryBodyC>::Body()); }
    //: Body Access. 
    
    const LotteryBodyC& Body() const
    { return static_cast<const LotteryBodyC &>(RCHandleC<LotteryBodyC>::Body()); }
    //: Body Access. 
    
  };

}

#endif
