
//! userlevel=Develop
//! example=fred.cc
//! author="Charles Galambos"
//! docentry="BannanaWorld"
//: The mother of all bananna's...

class BannanaC {
public:
  BannanaC();

  int LotsOfSugar()
    { return 1; }
  //: Is there lots of suger in banannas...
  // yes. well maybe repeated...
  
  enum HelloBT { Xb1,Xb2,Xb3, Some, Other, Enums };

  typedef enum FigE { X1,X2, XYZ, Bingo ,Bango } WapT;
  //: What a whopper.
  
  int Fred()
    { return 1; }
  //: Is fred a bannana ?
  // yes.
};


enum HelloT { X1,X2 };

//: My hello class comment.
//: second line
//! userlevel=Normal
//! example=x1.c;x2.c
//! file=right/here/right/now.cc
// some other text

class helloC;

//! docentry="SubClassWorld"
//: A class definition.
//! userlevel=Normal
// Dobe do [MyClassC]

template<class x>
class subClassC
  : public aclassC<x>,
    public BannanaC
{
public:
  subClassC() {}
  //! userlevel=Difficult
  //: Constructor
  
  void operator+(int i = 1 + 3);
  //! userlevel=Normal
  //: A plus operator.
  //!bug:No implementation
  
  //:------------------------------------------
  //: A Section.
  // Lots of stuff about this section
  
  bool Another(StringC x = StringC());
  //: Some info thats crap
  // Another  piece of text is --> [helloC] <-- [FredN]
  
  void Fred(StringC x = StringC());
  //! autoLink="on"
  //: Some more info..
  // Some auto linked text helloC is a word.
};

//! userlevel=Basic
//: HelloC ...
// Some detials about Helloc...

class helloC {
public:
  int aHello();
  // xxx

  int aWapBamBoggie();
  // xxx

  subClassC<PixelC> aWapBamBoggie(subClassC<IntT> val);
  // xxx
};

//! userlevel=Normal
//: A test namespace.
// Some detailed comment.

namespace FredN {
  
  //: Igloo's are great.
  // Cause they're made of ice.
  
  class IglooC 
    : public BannanaC
  {
  public:
    int IglooC();
    // xxx
    
    int aWapBamBoggie();
    // xxx
  };
  
  typedef int aglobal;
  //: Global typedef.
  // lalal

  int num;
  //: Variable in a namespace.
  // some details

  int MyFredNFunc();
  // xxx

  

  int MyFredNFunc2();
  // xxx
  

}

class Hello2C
  : private helloC
{
public:
  Hello2C()
    {}
  
  int aHello2();
  
};


//: Templates...
// Some comments
//!classbugs: AClass is completely broken.

template<class TypeT>
class aclassC 
  : protected helloC
{
public:
  typedef int anum;
  //: Anum comment
  
  anum method(int x,int y) { 
    return x;
  }
  //: XYZ <------------------------

};

typedef aclassC<PixelC> APixelClass;
