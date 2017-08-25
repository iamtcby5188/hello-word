
#ifndef __MSGBUS_MESSAGE_H
#define __MSGBUS_MESSAGE_H 1

#include "msgbus/compile.h"
#include "msgbus/type.h"
#include "msgbus/variant.h"
#include "sdbus/message.h"

namespace msgbus{

class MSGBUSAPI Message : public sdbus::Message{
public:
    typedef Variant::VarType Type ;
    typedef Variant::Map    Map ;
    typedef Variant::List   List ;
    typedef Variant::Raw    Raw ;

    static const int FIELD_VOID = Variant::VAR_VOID ;

    static const int FIELD_BOOL = Variant::VAR_BOOL ;

    static const int FIELD_UINT8 = Variant::VAR_UINT8 ;
    static const int FIELD_UINT16 = Variant::VAR_UINT16 ;
    static const int FIELD_UINT32 = Variant::VAR_UINT32 ;
    static const int FIELD_UINT64 = Variant::VAR_UINT64 ;

    static const int FIELD_INT8 = Variant::VAR_INT8 ;
    static const int FIELD_INT16 = Variant::VAR_INT16 ;
    static const int FIELD_INT32 = Variant::VAR_INT32 ;
    static const int FIELD_INT64 = Variant::VAR_INT64 ;

    static const int FIELD_FLOAT = Variant::VAR_FLOAT ;
    static const int FIELD_DOUBLE = Variant::VAR_DOUBLE ;

    static const int FIELD_STRING = Variant::VAR_STRING ;
    static const int FIELD_RAW = Variant::VAR_RAW ;
    static const int FIELD_MESSAGE = Variant::VAR_MAP ;
    static const int FIELD_LIST = Variant::VAR_LIST ;

    Message() ;
    Message(const Message& msg) ;
    virtual ~Message() ;
    Message& operator=(const Message& msg) ;

    inline VariantMap* AddMap(const char *name) {return (VariantMap *)sdbus::Message::AddMap(name) ; }
    inline VariantList* AddList(const char *name) {return (VariantList *)sdbus::Message::AddList(name) ; }
    inline Variant* AddVariant(const char *name) {return (Variant *)sdbus::Message::AddVariant(name) ; }
} ;
}

#endif  /** __MSGBUS_MESSAGE_H */
