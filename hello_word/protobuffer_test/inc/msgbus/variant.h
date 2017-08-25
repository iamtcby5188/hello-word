
#ifndef __MSGBUS_VARIANT_H
#define __MSGBUS_VARIANT_H 1

#include "msgbus/compile.h"
#include "msgbus/type.h"
#include "sdbus/variant.h"

namespace msgbus{

class Variant ;
class VariantMap ;
class VariantList ;
typedef sdbus::string VariantRaw ;

class MSGBUSAPI VariantList : public sdbus::VariantList{
public:
    VariantList() ;
    VariantList(const VariantList& list) ;
    virtual ~VariantList() ;

    inline size_t size() const {return this->Size() ;}
    void push_back(const Variant& var) ;
    inline void clear() {sdbus::VariantList::Clear() ;}

    inline VariantMap * AddMap() {return (VariantMap *)sdbus::VariantList::AddMap() ;}
    inline VariantList * AddList() {return (VariantList *)sdbus::VariantList::AddList() ;}
    inline Variant * AddVariant() {return (Variant *)sdbus::VariantList::AddVariant() ;}

    VariantList& operator=(const VariantList& list) ;

    class iterator ;
    class MSGBUSAPI const_iterator{
    public:
        const_iterator() ;
        const_iterator(const const_iterator& iter) ;
        const_iterator(const iterator& iter) ;

        const_iterator& operator=(const const_iterator& iter) ;
        const_iterator& operator=(const iterator& iter) ;

        bool operator==(const const_iterator& iter) const ;
        bool operator!=(const const_iterator& iter) const ;

        bool operator==(const iterator& iter) const ;
        bool operator!=(const iterator& iter) const ;

        const Variant * operator->() const ;
        const Variant& operator*() const ;

        const_iterator& operator++() ;
        const_iterator& operator++(int step) ;
        const_iterator& operator--() ;
        const_iterator& operator--(int step) ;

        operator bool() const ;

        friend class VariantList ;
    protected:
        Variant * variants_ ;
        int index_ ;
        int size_ ;

        void copy(const const_iterator& iter) ;
        bool equal(const const_iterator& iter) const ;
        void init() ;
    } ;

    class MSGBUSAPI iterator : public const_iterator{ 
    public:
        iterator() ;
        iterator(const iterator& iter) ;
        iterator& operator=(const iterator& iter) ;

        bool operator==(const iterator& iter) const ;
        bool operator!=(const iterator& iter) const ;
        Variant * operator->() ;

        Variant& operator*();
        iterator& operator++() ;
        iterator operator++(int step) ;
        iterator& operator--() ;
        iterator operator--(int step) ;
    };

    /*
        ¼æÈÝstd::list£¬±ÜÃâÊ¹ÓÃ
    */
    const_iterator begin() const ;
    iterator begin() ;

    const_iterator end() const ;
    iterator end() ;

    inline const Variant * operator[](size_t index) const {return (const Variant *)Get(index) ;}
    inline Variant * operator[](size_t index)  {return (Variant *)Get(index) ;}

    static const VariantList EMPTY ;
} ;

class MSGBUSAPI VariantMap : public sdbus::VariantMap{
public:
    VariantMap() ;
    VariantMap(const VariantMap& map) ;
    VariantMap& operator=(const VariantMap& map) ;
    virtual ~VariantMap() ;

    inline VariantMap* AddMap(const char *name) {return (VariantMap *)sdbus::VariantMap::AddMap(name) ;}
    inline VariantList* AddList(const char *name){return (VariantList *)sdbus::VariantMap::AddList(name) ;}
    inline Variant* AddVariant(const char *name) {return (Variant *)sdbus::VariantMap::AddVariant(name) ;}

    class iterator ;
    class MSGBUSAPI const_iterator{
    public:
        const_iterator() ;
        const_iterator(const const_iterator& iter) ;
        const_iterator(const iterator& iter) ;

        const_iterator& operator=(const const_iterator& iter) ;
        const_iterator& operator=(const iterator& iter) ;

        bool operator==(const const_iterator& iter) const ;
        bool operator!=(const const_iterator& iter) const ;

        bool operator==(const iterator& iter) const ;
        bool operator!=(const iterator& iter) const ;

        const Variant * operator->() const ;
        const Variant& operator*() const ;

        const_iterator& operator++() ;
        const_iterator& operator++(int step) ;
        const_iterator& operator--() ;
        const_iterator& operator--(int step) ;

        operator bool() const ;

        friend class VariantMap ;
    protected:
        Variant * variants_ ;
        int index_ ;
        int size_ ;

        void copy(const const_iterator& iter) ;
        bool equal(const const_iterator& iter) const ;
        void init() ;
    } ;

    class MSGBUSAPI iterator : public const_iterator{ 
    public:
        iterator() ;
        iterator(const iterator& iter) ;
        iterator& operator=(const iterator& iter) ;

        bool operator==(const iterator& iter) const ;
        bool operator!=(const iterator& iter) const ;
        Variant * operator->() ;

        Variant& operator*();
        iterator& operator++() ;
        iterator operator++(int step) ;
        iterator& operator--() ;
        iterator operator--(int step) ;
    };

    const_iterator begin() const ;
    iterator begin() ;

    const_iterator end() const ;
    iterator end() ;

    inline void clear() {sdbus::VariantMap::Clear() ; }
    inline bool empty() const {return sdbus::VariantMap::Empty()  ;}

    inline iterator find(const std::string& name) {return find(name.c_str()) ;}
    iterator find(const char * name) ;

    inline const_iterator find(const std::string& name) const {return find(name.c_str()) ;}
    const_iterator find(const char * name) const;


    static const VariantMap EMPTY ;
} ;

class MSGBUSAPI Variant : public sdbus::Variant{
public:
    Variant() {}
    ~Variant() {}

    typedef enum{
    
        VAR_UNKNOWN = sdbus::Variant::VAR_UNKNOWN ,
        VAR_VOID = VAR_UNKNOWN ,

        VAR_INT8 = sdbus::Variant::VAR_INT8 ,
        VAR_UINT8 = sdbus::Variant::VAR_UINT8 ,
        VAR_INT16 = sdbus::Variant::VAR_INT16 ,
        VAR_UINT16 = sdbus::Variant::VAR_UINT16 ,
        VAR_INT32 = sdbus::Variant::VAR_INT32 ,
        VAR_UINT32 = sdbus::Variant::VAR_UINT32 ,
        VAR_INT64 = sdbus::Variant::VAR_INT64 ,
        VAR_UINT64 = sdbus::Variant::VAR_UINT64 ,

        VAR_FLOAT = sdbus::Variant::VAR_FLOAT ,
        VAR_DOUBLE = sdbus::Variant::VAR_DOUBLE ,

        VAR_STRING = sdbus::Variant::VAR_STRING ,
        VAR_RAW = sdbus::Variant::VAR_RAW ,

        VAR_MAP = sdbus::Variant::VAR_MAP ,
        VAR_LIST = sdbus::Variant::VAR_LIST     
    }VarType ;

    typedef sdbus::Variant::Map Map ;
    typedef sdbus::Variant::List List ;
    typedef VariantRaw Raw ;

    static const Variant EMPTY ;
} ;

}

#endif  /** __MSGBUS_VARIANT_H */
