// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2010, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/XMPP/LMConnection.hh"
#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/CallMethodPtrs.hh"
#include "Ravl/XMLFactoryRegister.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN { namespace XMPPN {



  static LmHandlerResult InternalMessageHandler(LmMessageHandler *handler,
                                                LmConnection     *connection,
                                                LmMessage        *message,
                                                gpointer          user_data)
  {
    RavlAssert(user_data != 0);
    return reinterpret_cast<LMConnectionC *>(user_data)->MessageHandler(handler,connection,message);
  }

  //! Constructor
  LMConnectionC::LMConnectionC(const char *server,const char *user,const char *password,const char *resource)
    : m_server(server),
      m_user(user),
      m_password(password),
      m_resource(resource),
      m_dumpRaw(true),
      m_sigTextMessage("",""),
      m_context(0),
      m_mainLoop(0),
      m_conn(0),
      m_defaultHandler(0)
  {
    Init(true);
  }

  //! Factory constructor
  LMConnectionC::LMConnectionC(const XMLFactoryContextC &factory)
   : m_server(factory.AttributeString("server","jabber.org").data()),
     m_user(factory.AttributeString("user","auser").data()),
     m_password(factory.AttributeString("password","apassword").data()),
     m_resource(factory.AttributeString("resource","default").data()),
     m_dumpRaw(factory.AttributeBool("dumpRaw",false)),
     m_sigTextMessage("",""),
     m_context(0),
     m_mainLoop(0),
     m_conn(0),
     m_defaultHandler(0)

  {
    Init(factory.AttributeBool("useOwnThread",true));
  }


  //! Destructor
  LMConnectionC::~LMConnectionC()
  {
    lm_connection_unregister_message_handler(m_conn,m_defaultHandler,LM_MESSAGE_TYPE_MESSAGE);
    lm_message_handler_unref (m_defaultHandler);
    lm_connection_close (m_conn, NULL);
    lm_connection_unref (m_conn);

    if(m_mainLoop != 0) {
      g_main_loop_unref(m_mainLoop);
    }
    g_main_context_unref(m_context);
  }

  //: Called when owner handles drop to zero.
  void LMConnectionC::ZeroOwners() {
    if(m_mainLoop != 0) {
      g_main_loop_quit(m_mainLoop);
    }
  }

  // GLib main event loop if needed.
  int LMConnectionC::MainLoop() {
    ONDEBUG(std::cerr << "Starting main loop \n");
    g_main_context_push_thread_default (m_context);

    g_main_loop_run(m_mainLoop);
    ONDEBUG(std::cerr << "Done main loop. \n");
    return 0;
  }

  //! Start the server
  int LMConnectionC::Init(bool inOwnThread) {
    // Make sure threads are enabled.
    g_thread_init(0);

    if(inOwnThread) {
      m_context = g_main_context_new ();
      m_mainLoop = g_main_loop_new(m_context,false);
      m_conn = lm_connection_new_with_context (m_server.data(),m_context);
      LaunchThread(TriggerPtr(CBRefT(this),&LMConnectionC::MainLoop));
    } else {
      m_context = g_main_context_default ();
      g_main_context_ref(m_context);
      m_conn = lm_connection_new_with_context (m_server.data(),m_context);
    }
    return true;
  }

  //! Start opening
  bool LMConnectionC::Open() {
    GError *error = NULL;
    std::string jid = m_user + "@" + m_server;
    lm_connection_set_jid (m_conn, jid.data());

    if (!lm_connection_open_and_block (m_conn, &error)) {
      g_error ("Connection failed to open: %s", error->message);
      return false;
    }


    if (!lm_connection_authenticate_and_block (m_conn, m_user.data(), m_password.data(),m_resource.data(), &error)) {
      g_error ("Connection failed to authenticate: %s",error->message);
      return false;
    }

    lm_connection_set_keep_alive_rate(m_conn,20);

    m_defaultHandler = lm_message_handler_new (&InternalMessageHandler, (gpointer)this, NULL);
    lm_connection_register_message_handler (m_conn, m_defaultHandler,
                                            LM_MESSAGE_TYPE_MESSAGE,
                                            LM_HANDLER_PRIORITY_NORMAL);
    lm_connection_register_message_handler (m_conn, m_defaultHandler,
                                            LM_MESSAGE_TYPE_PRESENCE,
                                            LM_HANDLER_PRIORITY_NORMAL);
    lm_connection_register_message_handler (m_conn, m_defaultHandler,
                                            LM_MESSAGE_TYPE_IQ,
                                            LM_HANDLER_PRIORITY_NORMAL);

    // Let server know we want messages.
    LmMessage *m  = lm_message_new (NULL, LM_MESSAGE_TYPE_PRESENCE);
    if (!lm_connection_send (m_conn, m, &error)) {
      g_error ("Connection failed to send presence message: %s",
          error->message);
    }
    lm_message_unref (m);

    return true;
  }

  //! Test if we have a connection.
  bool LMConnectionC::IsConnected() const
  {
    if(m_conn == 0)
      return false;
    return lm_connection_is_open(m_conn);
  }

  //! Send a text message to someone.
  bool LMConnectionC::SendText(const char *to,const char *message)
  {
    GError *error = NULL;
    LmMessage *m = lm_message_new (to, LM_MESSAGE_TYPE_MESSAGE);
    lm_message_node_add_child (m->node, "body", message);

    if (!lm_connection_send (m_conn, m, &error)) {
      g_print ("Error while sending message to '%s':\n%s\n",
          to, error->message);
    }

    lm_message_unref (m);
    return true;
  }

  LmHandlerResult LMConnectionC::MessageHandler(LmMessageHandler *handler,
                                         LmConnection     *connection,
                                         LmMessage        *m)
  {
    LmMessageNode *body_node;
    ONDEBUG(std::cerr << "Got message! Type:" << lm_message_get_sub_type (m) << "  \n");
    if(m_dumpRaw) {
      std::cerr << "LMConnection Message: "<< lm_message_node_to_string(m->node) << "\n";
    }
    if ((lm_message_get_sub_type (m) != LM_MESSAGE_SUB_TYPE_CHAT &&
         lm_message_get_sub_type (m) != LM_MESSAGE_SUB_TYPE_NORMAL)) {
            return LM_HANDLER_RESULT_ALLOW_MORE_HANDLERS;
    }

    body_node = lm_message_node_get_child (m->node, "body");
    if (!body_node) {
      ONDEBUG(std::cerr << "No body for message. \n");
      return LM_HANDLER_RESULT_ALLOW_MORE_HANDLERS;
    }
    m_sigTextMessage(lm_message_node_get_attribute (m->node, "from"),lm_message_node_get_value (body_node));

    return LM_HANDLER_RESULT_REMOVE_MESSAGE;
  }


  XMLFactoryRegisterC<LMConnectionC> g_xmlFactoryRegister("RavlN::XMPPN::LMConnectionC");

  void LinkRavlXMPPLMConnection()
  {}

}}
