
#ifndef __MSGBUS_TYPE_H
#define __MSGBUS_TYPE_H 1

#include "msgbus/compile.h"
#include "sdbus/type.h"
#include "sdbus/string.h"

namespace msgbus{


typedef sdbus::int8_t           int8_t ;
typedef sdbus::uint8_t          uint8_t ;
typedef sdbus::int16_t          int16_t ;
typedef sdbus::uint16_t         uint16_t ;

typedef sdbus::int32_t          int32_t ;
typedef sdbus::uint32_t         uint32_t ;
typedef sdbus::int64_t          int64_t ;
typedef sdbus::uint64_t         uint64_t ;

typedef sdbus::uintptr_t        uintptr_t ;
typedef sdbus::intprt_t         intprt_t ;

using sdbus::atoi64 ;
using sdbus::U64FMT ;
using sdbus::I64FMT ;

typedef sdbus::string string ;
}

#endif  /** __MSGBUS_TYPE_H */
