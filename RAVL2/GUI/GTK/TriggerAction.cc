
#include "Ravl/GUI/TriggerAction.hh"
#include "Ravl/XMLFactoryRegister.hh"

namespace RavlGUIN {

  //: XML factory constructor
  TriggerShowWidgetBodyC::TriggerShowWidgetBodyC(const XMLFactoryContextC &context)
  {
    context.UseComponent("TargetWidget",m_targetWidget);
  }

  void TriggerShowWidgetBodyC::Invoke() {
    m_targetWidget.Show();
  }

  static XMLFactoryRegisterHandleConvertC<TriggerShowWidgetC,TriggerC> g_registerXMLFactoryShowWidget("RavlGUIN::TriggerShowWidgetC");

  // ------------------------------------------------------------------------

  TriggerHideWidgetBodyC::TriggerHideWidgetBodyC(const XMLFactoryContextC &context)
  {
    context.UseComponent("TargetWidget",m_targetWidget);
  }
  //: XML factory constructor

  void TriggerHideWidgetBodyC::Invoke() {
    m_targetWidget.Hide();
  }

  static XMLFactoryRegisterHandleConvertC<TriggerHideWidgetC,TriggerC> g_registerXMLFactoryHideWidget("RavlGUIN::TriggerHideWidgetC");

  void LinkTriggerAction()
  {}
}
