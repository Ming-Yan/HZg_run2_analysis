// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME RootDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "interface/FinalModelConstruction.h"
#include "interface/InitialFit.h"
#include "interface/LinearInterp.h"
#include "interface/Normalization_8TeV.h"
#include "interface/Packager.h"
#include "interface/RooGaussBern2D.h"
#include "interface/WSTFileWrapper.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *FinalModelConstruction_Dictionary();
   static void FinalModelConstruction_TClassManip(TClass*);
   static void delete_FinalModelConstruction(void *p);
   static void deleteArray_FinalModelConstruction(void *p);
   static void destruct_FinalModelConstruction(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FinalModelConstruction*)
   {
      ::FinalModelConstruction *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FinalModelConstruction));
      static ::ROOT::TGenericClassInfo 
         instance("FinalModelConstruction", "interface/FinalModelConstruction.h", 25,
                  typeid(::FinalModelConstruction), DefineBehavior(ptr, ptr),
                  &FinalModelConstruction_Dictionary, isa_proxy, 0,
                  sizeof(::FinalModelConstruction) );
      instance.SetDelete(&delete_FinalModelConstruction);
      instance.SetDeleteArray(&deleteArray_FinalModelConstruction);
      instance.SetDestructor(&destruct_FinalModelConstruction);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FinalModelConstruction*)
   {
      return GenerateInitInstanceLocal((::FinalModelConstruction*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FinalModelConstruction*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FinalModelConstruction_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FinalModelConstruction*)0x0)->GetClass();
      FinalModelConstruction_TClassManip(theClass);
   return theClass;
   }

   static void FinalModelConstruction_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *InitialFit_Dictionary();
   static void InitialFit_TClassManip(TClass*);
   static void delete_InitialFit(void *p);
   static void deleteArray_InitialFit(void *p);
   static void destruct_InitialFit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::InitialFit*)
   {
      ::InitialFit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::InitialFit));
      static ::ROOT::TGenericClassInfo 
         instance("InitialFit", "interface/InitialFit.h", 17,
                  typeid(::InitialFit), DefineBehavior(ptr, ptr),
                  &InitialFit_Dictionary, isa_proxy, 0,
                  sizeof(::InitialFit) );
      instance.SetDelete(&delete_InitialFit);
      instance.SetDeleteArray(&deleteArray_InitialFit);
      instance.SetDestructor(&destruct_InitialFit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::InitialFit*)
   {
      return GenerateInitInstanceLocal((::InitialFit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::InitialFit*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *InitialFit_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::InitialFit*)0x0)->GetClass();
      InitialFit_TClassManip(theClass);
   return theClass;
   }

   static void InitialFit_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *LinearInterp_Dictionary();
   static void LinearInterp_TClassManip(TClass*);
   static void delete_LinearInterp(void *p);
   static void deleteArray_LinearInterp(void *p);
   static void destruct_LinearInterp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LinearInterp*)
   {
      ::LinearInterp *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::LinearInterp));
      static ::ROOT::TGenericClassInfo 
         instance("LinearInterp", "interface/LinearInterp.h", 14,
                  typeid(::LinearInterp), DefineBehavior(ptr, ptr),
                  &LinearInterp_Dictionary, isa_proxy, 0,
                  sizeof(::LinearInterp) );
      instance.SetDelete(&delete_LinearInterp);
      instance.SetDeleteArray(&deleteArray_LinearInterp);
      instance.SetDestructor(&destruct_LinearInterp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LinearInterp*)
   {
      return GenerateInitInstanceLocal((::LinearInterp*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LinearInterp*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *LinearInterp_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::LinearInterp*)0x0)->GetClass();
      LinearInterp_TClassManip(theClass);
   return theClass;
   }

   static void LinearInterp_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Normalization_8TeV_Dictionary();
   static void Normalization_8TeV_TClassManip(TClass*);
   static void *new_Normalization_8TeV(void *p = 0);
   static void *newArray_Normalization_8TeV(Long_t size, void *p);
   static void delete_Normalization_8TeV(void *p);
   static void deleteArray_Normalization_8TeV(void *p);
   static void destruct_Normalization_8TeV(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Normalization_8TeV*)
   {
      ::Normalization_8TeV *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Normalization_8TeV));
      static ::ROOT::TGenericClassInfo 
         instance("Normalization_8TeV", "interface/Normalization_8TeV.h", 19,
                  typeid(::Normalization_8TeV), DefineBehavior(ptr, ptr),
                  &Normalization_8TeV_Dictionary, isa_proxy, 0,
                  sizeof(::Normalization_8TeV) );
      instance.SetNew(&new_Normalization_8TeV);
      instance.SetNewArray(&newArray_Normalization_8TeV);
      instance.SetDelete(&delete_Normalization_8TeV);
      instance.SetDeleteArray(&deleteArray_Normalization_8TeV);
      instance.SetDestructor(&destruct_Normalization_8TeV);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Normalization_8TeV*)
   {
      return GenerateInitInstanceLocal((::Normalization_8TeV*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Normalization_8TeV*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Normalization_8TeV_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Normalization_8TeV*)0x0)->GetClass();
      Normalization_8TeV_TClassManip(theClass);
   return theClass;
   }

   static void Normalization_8TeV_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Packager_Dictionary();
   static void Packager_TClassManip(TClass*);
   static void delete_Packager(void *p);
   static void deleteArray_Packager(void *p);
   static void destruct_Packager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Packager*)
   {
      ::Packager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Packager));
      static ::ROOT::TGenericClassInfo 
         instance("Packager", "interface/Packager.h", 17,
                  typeid(::Packager), DefineBehavior(ptr, ptr),
                  &Packager_Dictionary, isa_proxy, 0,
                  sizeof(::Packager) );
      instance.SetDelete(&delete_Packager);
      instance.SetDeleteArray(&deleteArray_Packager);
      instance.SetDestructor(&destruct_Packager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Packager*)
   {
      return GenerateInitInstanceLocal((::Packager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Packager*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Packager_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Packager*)0x0)->GetClass();
      Packager_TClassManip(theClass);
   return theClass;
   }

   static void Packager_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_RooGaussBern2D(void *p = 0);
   static void *newArray_RooGaussBern2D(Long_t size, void *p);
   static void delete_RooGaussBern2D(void *p);
   static void deleteArray_RooGaussBern2D(void *p);
   static void destruct_RooGaussBern2D(void *p);
   static void streamer_RooGaussBern2D(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooGaussBern2D*)
   {
      ::RooGaussBern2D *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooGaussBern2D >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooGaussBern2D", ::RooGaussBern2D::Class_Version(), "interface/RooGaussBern2D.h", 12,
                  typeid(::RooGaussBern2D), DefineBehavior(ptr, ptr),
                  &::RooGaussBern2D::Dictionary, isa_proxy, 16,
                  sizeof(::RooGaussBern2D) );
      instance.SetNew(&new_RooGaussBern2D);
      instance.SetNewArray(&newArray_RooGaussBern2D);
      instance.SetDelete(&delete_RooGaussBern2D);
      instance.SetDeleteArray(&deleteArray_RooGaussBern2D);
      instance.SetDestructor(&destruct_RooGaussBern2D);
      instance.SetStreamerFunc(&streamer_RooGaussBern2D);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooGaussBern2D*)
   {
      return GenerateInitInstanceLocal((::RooGaussBern2D*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooGaussBern2D*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *WSTFileWrapper_Dictionary();
   static void WSTFileWrapper_TClassManip(TClass*);
   static void delete_WSTFileWrapper(void *p);
   static void deleteArray_WSTFileWrapper(void *p);
   static void destruct_WSTFileWrapper(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WSTFileWrapper*)
   {
      ::WSTFileWrapper *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::WSTFileWrapper));
      static ::ROOT::TGenericClassInfo 
         instance("WSTFileWrapper", "interface/WSTFileWrapper.h", 12,
                  typeid(::WSTFileWrapper), DefineBehavior(ptr, ptr),
                  &WSTFileWrapper_Dictionary, isa_proxy, 0,
                  sizeof(::WSTFileWrapper) );
      instance.SetDelete(&delete_WSTFileWrapper);
      instance.SetDeleteArray(&deleteArray_WSTFileWrapper);
      instance.SetDestructor(&destruct_WSTFileWrapper);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WSTFileWrapper*)
   {
      return GenerateInitInstanceLocal((::WSTFileWrapper*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::WSTFileWrapper*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *WSTFileWrapper_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::WSTFileWrapper*)0x0)->GetClass();
      WSTFileWrapper_TClassManip(theClass);
   return theClass;
   }

   static void WSTFileWrapper_TClassManip(TClass* ){
   }

} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr RooGaussBern2D::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooGaussBern2D::Class_Name()
{
   return "RooGaussBern2D";
}

//______________________________________________________________________________
const char *RooGaussBern2D::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooGaussBern2D*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooGaussBern2D::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooGaussBern2D*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooGaussBern2D::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooGaussBern2D*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooGaussBern2D::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooGaussBern2D*)0x0)->GetClass(); }
   return fgIsA;
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FinalModelConstruction(void *p) {
      delete ((::FinalModelConstruction*)p);
   }
   static void deleteArray_FinalModelConstruction(void *p) {
      delete [] ((::FinalModelConstruction*)p);
   }
   static void destruct_FinalModelConstruction(void *p) {
      typedef ::FinalModelConstruction current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FinalModelConstruction

namespace ROOT {
   // Wrapper around operator delete
   static void delete_InitialFit(void *p) {
      delete ((::InitialFit*)p);
   }
   static void deleteArray_InitialFit(void *p) {
      delete [] ((::InitialFit*)p);
   }
   static void destruct_InitialFit(void *p) {
      typedef ::InitialFit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::InitialFit

namespace ROOT {
   // Wrapper around operator delete
   static void delete_LinearInterp(void *p) {
      delete ((::LinearInterp*)p);
   }
   static void deleteArray_LinearInterp(void *p) {
      delete [] ((::LinearInterp*)p);
   }
   static void destruct_LinearInterp(void *p) {
      typedef ::LinearInterp current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LinearInterp

namespace ROOT {
   // Wrappers around operator new
   static void *new_Normalization_8TeV(void *p) {
      return  p ? new(p) ::Normalization_8TeV : new ::Normalization_8TeV;
   }
   static void *newArray_Normalization_8TeV(Long_t nElements, void *p) {
      return p ? new(p) ::Normalization_8TeV[nElements] : new ::Normalization_8TeV[nElements];
   }
   // Wrapper around operator delete
   static void delete_Normalization_8TeV(void *p) {
      delete ((::Normalization_8TeV*)p);
   }
   static void deleteArray_Normalization_8TeV(void *p) {
      delete [] ((::Normalization_8TeV*)p);
   }
   static void destruct_Normalization_8TeV(void *p) {
      typedef ::Normalization_8TeV current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Normalization_8TeV

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Packager(void *p) {
      delete ((::Packager*)p);
   }
   static void deleteArray_Packager(void *p) {
      delete [] ((::Packager*)p);
   }
   static void destruct_Packager(void *p) {
      typedef ::Packager current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Packager

//______________________________________________________________________________
void RooGaussBern2D::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooGaussBern2D.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      y.Streamer(R__b);
      polParamsMean.Streamer(R__b);
      polParamsSigma.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, RooGaussBern2D::IsA());
   } else {
      R__c = R__b.WriteVersion(RooGaussBern2D::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      y.Streamer(R__b);
      polParamsMean.Streamer(R__b);
      polParamsSigma.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooGaussBern2D(void *p) {
      return  p ? new(p) ::RooGaussBern2D : new ::RooGaussBern2D;
   }
   static void *newArray_RooGaussBern2D(Long_t nElements, void *p) {
      return p ? new(p) ::RooGaussBern2D[nElements] : new ::RooGaussBern2D[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooGaussBern2D(void *p) {
      delete ((::RooGaussBern2D*)p);
   }
   static void deleteArray_RooGaussBern2D(void *p) {
      delete [] ((::RooGaussBern2D*)p);
   }
   static void destruct_RooGaussBern2D(void *p) {
      typedef ::RooGaussBern2D current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RooGaussBern2D(TBuffer &buf, void *obj) {
      ((::RooGaussBern2D*)obj)->::RooGaussBern2D::Streamer(buf);
   }
} // end of namespace ROOT for class ::RooGaussBern2D

namespace ROOT {
   // Wrapper around operator delete
   static void delete_WSTFileWrapper(void *p) {
      delete ((::WSTFileWrapper*)p);
   }
   static void deleteArray_WSTFileWrapper(void *p) {
      delete [] ((::WSTFileWrapper*)p);
   }
   static void destruct_WSTFileWrapper(void *p) {
      typedef ::WSTFileWrapper current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WSTFileWrapper

namespace {
  void TriggerDictionaryInitialization_RootDict_Impl() {
    static const char* headers[] = {
"interface/FinalModelConstruction.h",
"interface/InitialFit.h",
"interface/LinearInterp.h",
"interface/Normalization_8TeV.h",
"interface/Packager.h",
"interface/RooGaussBern2D.h",
"interface/WSTFileWrapper.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5//include",
"/afs/cern.ch/user/m/milee/CMSSW_7_4_7/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include",
"/afs/cern.ch/user/m/milee/CMSSW_7_4_7/src/flashggFinalFit/Signal/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$interface/FinalModelConstruction.h")))  FinalModelConstruction;
class __attribute__((annotate("$clingAutoload$interface/InitialFit.h")))  InitialFit;
class __attribute__((annotate("$clingAutoload$interface/LinearInterp.h")))  LinearInterp;
class __attribute__((annotate("$clingAutoload$interface/FinalModelConstruction.h")))  Normalization_8TeV;
class __attribute__((annotate("$clingAutoload$interface/Packager.h")))  Packager;
class __attribute__((annotate("$clingAutoload$interface/RooGaussBern2D.h")))  RooGaussBern2D;
class __attribute__((annotate("$clingAutoload$interface/Packager.h")))  WSTFileWrapper;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "interface/FinalModelConstruction.h"
#include "interface/InitialFit.h"
#include "interface/LinearInterp.h"
#include "interface/Normalization_8TeV.h"
#include "interface/Packager.h"
#include "interface/RooGaussBern2D.h"
#include "interface/WSTFileWrapper.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FinalModelConstruction", payloadCode, "@",
"InitialFit", payloadCode, "@",
"LinearInterp", payloadCode, "@",
"Normalization_8TeV", payloadCode, "@",
"Packager", payloadCode, "@",
"RooGaussBern2D", payloadCode, "@",
"WSTFileWrapper", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("RootDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_RootDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_RootDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_RootDict() {
  TriggerDictionaryInitialization_RootDict_Impl();
}
