#pragma once
#include "PythonArpComponent.hpp"

/* Define macros for inline documentation. */
#define ArpPyDoc_VAR(name) static char name[]
#define ArpPyDoc_STRVAR(name,str) ArpPyDoc_VAR(name) = ArpPyDoc_STR(str)
#ifdef Arp_WITH_DOC_STRINGS
#define ArpPyDoc_STR(str) str
#else
#define ArpPyDoc_STR(str) ""
#endif