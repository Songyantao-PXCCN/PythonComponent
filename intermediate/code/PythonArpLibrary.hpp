#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Core/AppDomain.hpp"
#include "Arp/System/Core/Singleton.hxx"
#include "Arp/System/Core/Library.h"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeDomain.hpp"

namespace PythonArp
{

using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Commons::Meta::TypeSystem;

class PythonArpLibrary : public MetaLibraryBase, public Singleton<PythonArpLibrary>
{
public: // typedefs
    typedef Singleton<PythonArpLibrary> SingletonBase;

public: // construction/destruction
    PythonArpLibrary(AppDomain& appDomain);
    virtual ~PythonArpLibrary() = default;

public: // static operations (called through reflection)
    static void Main(AppDomain& appDomain);

private: // methods
    void InitializeTypeDomain();

private: // deleted methods
    PythonArpLibrary(const PythonArpLibrary& arg) = delete;
    PythonArpLibrary& operator= (const PythonArpLibrary& arg) = delete;

private:  // fields
    TypeDomain typeDomain;
};

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain);

///////////////////////////////////////////////////////////////////////////////
// inline methods of class PythonArpLibrary

} // end of namespace PythonArp
