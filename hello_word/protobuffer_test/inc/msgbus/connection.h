
#ifndef __MSGBUS_CONNECTION_H
#define __MSGBUS_CONNECTION_H 1

#include "msgbus/compile.h"
#include "msgbus/type.h"
#include "sdbus/connection.h"
#include "msgbus/message.h"
#include "msgbus/callback.h"

namespace msgbus{

class MSGBUSAPI Connection : public sdbus::Connection{
public:
    Connection() ;
    ~Connection() ;

    /*
        需要注意的是，这个版本为了兼容databus，url这个参数已经失效了。在clientcfg.xml中配置。
    */
    bool connect(const msgbus::string& url) ;
    void close() ;

    /*
        如果是设置某个topic的回调函数，那么会自动订阅该服务下，所有的主题。根据DataDictionary.xml
    */
    bool setHandler(const msgbus::string& name, HANDLER_CALLBACK callback, void *clientdata , DeliverType type = DeliverDirect);
    bool setHandler(Callback* cb) ;
    bool setHandler(VectCallback* vcb) ;

    bool send(const msgbus::string &name, const Message &message , DeliverType type = DeliverDirect);

    bool fanout(const msgbus::string& name , const Message &message) ;

    bool recv(Message& msg  ,  int timeout = 0);    

    void log_level(int level) {sdbus::Connection::LogLevel(level) ;}
    inline void log_tty_level(int level) {}

private:
    bool add_handler(VectCallback* vcb) ;
} ;

}
#endif  /** __MSGBUS_CONNECTION_H */
