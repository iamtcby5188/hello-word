
#ifndef __MSGBUS_CALLBACK_H
#define __MSGBUS_CALLBACK_H 1

#include "msgbus/compile.h"
#include "msgbus/type.h"
#include "sdbus/callback.h"
#include "msgbus/message.h"

namespace msgbus{

enum DeliverType{
    DeliverDirect ,
    DeliverFanout 
} ;

typedef void (*HANDLER_CALLBACK)(const msgbus::string& name , const Message& message , void * client_data) ;

class MSGBUSAPI VectCallback : public sdbus::Callback{
public:
    VectCallback() ;
    virtual ~VectCallback() ;

    inline const msgbus::string& name() const {return sdbus::Callback::Name() ;}
    void name(const char * str) ;

    inline void * client_data() const {return client_data_ ;}
    inline void client_data(void * data) {client_data_ = data ;}

    inline HANDLER_CALLBACK handler() const {return handler_ ; }
    inline void handler(HANDLER_CALLBACK func) {handler_ = func ; }

    inline DeliverType type() const {return (DeliverType) sdbus::Callback::Type() ;}
    void type(DeliverType val) ;

    virtual void messages(const Message* msgs , int count) ;

    virtual void OnMsgs(const Message ** msgs , int count) ;
private:
    void * client_data_ ;
    sdbus::string name_ ;
    DeliverType type_ ;

    HANDLER_CALLBACK handler_ ;
} ;

class MSGBUSAPI Callback : public VectCallback{
public:
    virtual void message(const Message& msg) ;

    virtual void messages(const Message* msgs , int count) ;
} ;


}

#endif  /** __MSGBUS_CALLBACK_H */
