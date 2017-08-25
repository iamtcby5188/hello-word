
#ifndef __QPID_ENGINE_H
#define __QPID_ENGINE_H 1

#include "sdbus/compile.h"
#include "sdbus/engine.h"


#if (OSTYPE == OSTYPE_WINDOWS)
    #ifdef QPID_ENGINE_EXPORTS
        #define QPIDENGINEAPI __declspec(dllexport)
    #else
        //默认使用动态库
        #ifdef QPID_ENGINE_STATIC_LINK
            #define QPIDENGINEAPI
        #else
            #define QPIDENGINEAPI __declspec(dllimport)
        #endif
    #endif

#else
    #define QPIDENGINEAPI
#endif

namespace engine{
namespace qpid{

QPIDENGINEAPI sdbus::Engine * QpidEngineCreator() ;
QPIDENGINEAPI void QpidEngineDestroyer(sdbus::Engine * engine) ;

QPIDENGINEAPI bool QpidEngineInitializer(sdbus::Engine * engine , const sdbus::string& url) ;
QPIDENGINEAPI void QpidEngineFinalizer(sdbus::Engine * engine) ;

QPIDENGINEAPI bool QpidEngineAddHandler(sdbus::Engine * engine , const sdbus::string& name , int type , sdbus::Callback * cb) ;
QPIDENGINEAPI void QpidEngineDelHandler(sdbus::Engine * engine , const sdbus::Callback * cb) ;

QPIDENGINEAPI bool QpidEngineAsyncSend(sdbus::Engine * engine , const sdbus::string& name , const sdbus:: Message& msg) ;
QPIDENGINEAPI bool QpidEngineSyncSend(sdbus::Engine * engine , const sdbus::string& name , const sdbus:: Message& request , sdbus::Message& response , int timeout) ;

QPIDENGINEAPI bool QpidEnginePublish(sdbus::Engine * engine , const sdbus::string& topic , const sdbus::Message& msg) ;    

QPIDENGINEAPI bool QpidEngineSetOptions(sdbus::Engine * engine , const sdbus::Options& options) ;
QPIDENGINEAPI const sdbus::Options& QpidEngineGetOptions(sdbus::Engine * engine ) ;


class QPIDENGINEAPI QpidEngine : public sdbus::Engine{
public:
    QpidEngine() ;
} ;

QPIDENGINEAPI const char * Version() ;

QPIDENGINEAPI void LogLevel(int level) ;


class QPIDENGINEAPI EngineInitializer{
public:
    EngineInitializer()
    {
        sdbus::RegisterEngine("qpid" , engine::qpid::QpidEngine()) ;
    }

    ~EngineInitializer()
    {
        sdbus::UnregisterEngine("qpid") ;
    }
} ;

}
}


#endif  /** __QPID_ENGINE_H */