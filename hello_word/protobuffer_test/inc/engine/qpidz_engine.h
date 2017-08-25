
#ifndef __QPIDZ_ENGINE_H
#define __QPIDZ_ENGINE_H 1

#include "sdbus/compile.h"
#include "sdbus/engine.h"


#if (OSTYPE == OSTYPE_WINDOWS)
    #ifdef QPIDZ_ENGINE_EXPORTS
        #define QPIDZENGINEAPI __declspec(dllexport)
    #else
        //默认使用动态库
        #ifdef QPIDZ_ENGINE_STATIC_LINK
            #define QPIDZENGINEAPI
        #else
            #define QPIDZENGINEAPI __declspec(dllimport)
        #endif
    #endif

#else
    #define QPIDZENGINEAPI
#endif

namespace engine{
namespace qpidz{

QPIDZENGINEAPI sdbus::Engine * QpidzEngineCreator() ;
QPIDZENGINEAPI void QpidzEngineDestroyer(sdbus::Engine * engine) ;

QPIDZENGINEAPI bool QpidzEngineInitializer(sdbus::Engine * engine , const sdbus::string& url) ;
QPIDZENGINEAPI void QpidzEngineFinalizer(sdbus::Engine * engine) ;

QPIDZENGINEAPI bool QpidzEngineAddHandler(sdbus::Engine * engine , const sdbus::string& name , int type , sdbus::Callback * cb) ;
QPIDZENGINEAPI void QpidzEngineDelHandler(sdbus::Engine * engine , const sdbus::Callback * cb) ;

QPIDZENGINEAPI bool QpidzEngineAsyncSend(sdbus::Engine * engine , const sdbus::string& name , const sdbus:: Message& msg) ;
QPIDZENGINEAPI bool QpidzEngineSyncSend(sdbus::Engine * engine , const sdbus::string& name , const sdbus:: Message& request , sdbus::Message& response , int timeout) ;

QPIDZENGINEAPI bool QpidzEnginePublish(sdbus::Engine * engine , const sdbus::string& topic , const sdbus::Message& msg) ;    

QPIDZENGINEAPI bool QpidzEngineSetOptions(sdbus::Engine * engine , const sdbus::Options& options) ;
QPIDZENGINEAPI const sdbus::Options& QpidzEngineGetOptions(sdbus::Engine * engine ) ;


class QPIDZENGINEAPI QpidzEngine : public sdbus::Engine{
public:
    QpidzEngine() ;
} ;

QPIDZENGINEAPI const char * Version() ;

QPIDZENGINEAPI void LogLevel(int level) ;


class QPIDZENGINEAPI EngineInitializer{
public:
    EngineInitializer()
    {
        sdbus::RegisterEngine("qpidz" , engine::qpidz::QpidzEngine()) ;
    }

    ~EngineInitializer()
    {
        sdbus::UnregisterEngine("qpidz") ;
    }
} ;

}
}


#endif  /** __QPID_ENGINE_H */