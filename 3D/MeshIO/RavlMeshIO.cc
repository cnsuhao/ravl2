
namespace Ravl3DN {

  extern void InitTriSetIO();

  extern void InitTriFormat();
  
  void InitRavlMeshIO() {
    InitTriFormat();
    InitTriSetIO();
  }
}
