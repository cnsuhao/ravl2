

namespace RavlGUIN {

  void LinkGladeXML();
  void LinkGladeWidget();
  void LinkGladeWindow();

  void LinkLibGlade() {
    LinkGladeXML();
    LinkGladeWidget();
    LinkGladeWindow();
  }

}
