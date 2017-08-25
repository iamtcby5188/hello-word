#ifndef __ZMQ_ENGINE_H
#define __ZMQ_ENGINE_H 1

#include "sdbus/compile.h"
#include "sdbus/engine.h"

#if defined _WIN32
#   if defined ZMQMOK_STATIC
#       define ZMQMOK_EXPORT
#   elif defined ZMQ_ENGINE_EXPORTS
#       define ZMQMOK_EXPORT __declspec(dllexport)
#   else
#       define ZMQMOK_EXPORT __declspec(dllimport)
#   endif
#else
#   if defined __SUNPRO_C  || defined __SUNPRO_CC
#       define ZMQMOK_EXPORT __global
#   elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
#       define ZMQMOK_EXPORT __attribute__ ((visibility("default")))
#   else
#       define ZMQMOK_EXPORT
#   endif
#endif


namespace engine{

namespace zmq{

ZMQMOK_EXPORT sdbus::Engine * ZmqEngineCreator() ;
ZMQMOK_EXPORT void ZmqEngineDestroyer(sdbus::Engine * engine) ;

ZMQMOK_EXPORT bool ZmqEngineInitializer(sdbus::Engine * engine , const sdbus::string& url) ;
ZMQMOK_EXPORT void ZmqEngineFinalizer(sdbus::Engine * engine) ;

ZMQMOK_EXPORT bool ZmqEngineAddHandler(sdbus::Engine * engine , const sdbus::string& name , int type , sdbus::Callback * cb) ;
ZMQMOK_EXPORT void ZmqEngineDelHandler(sdbus::Engine * engine , const sdbus::Callback * cb) ;

ZMQMOK_EXPORT bool ZmqEngineAsyncSend(sdbus::Engine * engine , const sdbus::string& name , const sdbus:: Message& msg) ;
ZMQMOK_EXPORT bool ZmqEngineSyncSend(sdbus::Engine * engine , const sdbus::string& name , const sdbus:: Message& request , sdbus::Message& response , int timeout) ;

ZMQMOK_EXPORT bool ZmqEnginePublish(sdbus::Engine * engine , const sdbus::string& topic , const sdbus::Message& msg) ;    

ZMQMOK_EXPORT bool ZmqEngineSetOptions(sdbus::Engine * engine , const sdbus::Options& options) ;
ZMQMOK_EXPORT const sdbus::Options& ZmqEngineGetOptions(sdbus::Engine * engine ) ;

class ZMQMOK_EXPORT ZmqEngine : public sdbus::Engine{
public:
    ZmqEngine() ;
    ~ZmqEngine();
} ;

ZMQMOK_EXPORT const char * Version() ;

ZMQMOK_EXPORT void LogLevel(int level) ;



class ZMQMOK_EXPORT EngineInitializer
{
public:
    EngineInitializer()
    {
        sdbus::RegisterEngine("zmq" , engine::zmq::ZmqEngine()) ;
    }

    ~EngineInitializer()
    {
        sdbus::UnregisterEngine("zmq") ;
    }
} ;

}//end namespace zero

namespace zbroker
{
ZMQMOK_EXPORT int create_broker( char *url,size_t len,size_t limit = 512 );   
}//end namespace zbroker

namespace zraw
{

}//end namespace zraw

}//end engine

#endif /** __ZMQ_ENGINE_H */