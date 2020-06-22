#include "PythonArpLibrary.hpp"
#include "Arp/System/Core/CommonTypeName.hxx"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "PythonArpComponent.hpp"

namespace PythonArp
{

PythonArpLibrary::PythonArpLibrary(AppDomain& appDomain)
    : MetaLibraryBase(appDomain, ARP_VERSION_CURRENT, typeDomain)
    , typeDomain(CommonTypeName<PythonArpLibrary>().GetNamespace())
{
    this->componentFactory.AddFactoryMethod(CommonTypeName<::PythonArp::PythonArpComponent>(), &::PythonArp::PythonArpComponent::Create);
    this->InitializeTypeDomain();
}

void PythonArpLibrary::Main(AppDomain& appDomain)
{
    SingletonBase::CreateInstance(appDomain);
}

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain)
{
    PythonArpLibrary::Main(appDomain);
    return  PythonArpLibrary::GetInstance();
}

} // end of namespace PythonArp
