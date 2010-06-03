
namespace RavlGUIN {
  extern void LinkTriggerAction();
  extern void LinkFileChooserButton();
  extern void LinkFileChooserDialog();

  void LinkRavlGUI() {
    LinkTriggerAction();
    LinkFileChooserButton();
    LinkFileChooserDialog();
  }
}
