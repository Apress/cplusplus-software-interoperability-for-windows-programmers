

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for StatsATLCOM.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __StatsATLCOM_i_h__
#define __StatsATLCOM_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IStatsLibWrapper_FWD_DEFINED__
#define __IStatsLibWrapper_FWD_DEFINED__
typedef interface IStatsLibWrapper IStatsLibWrapper;

#endif 	/* __IStatsLibWrapper_FWD_DEFINED__ */


#ifndef __IStatisticalTest_FWD_DEFINED__
#define __IStatisticalTest_FWD_DEFINED__
typedef interface IStatisticalTest IStatisticalTest;

#endif 	/* __IStatisticalTest_FWD_DEFINED__ */


#ifndef __StatsLibWrapper_FWD_DEFINED__
#define __StatsLibWrapper_FWD_DEFINED__

#ifdef __cplusplus
typedef class StatsLibWrapper StatsLibWrapper;
#else
typedef struct StatsLibWrapper StatsLibWrapper;
#endif /* __cplusplus */

#endif 	/* __StatsLibWrapper_FWD_DEFINED__ */


#ifndef __CTTest_FWD_DEFINED__
#define __CTTest_FWD_DEFINED__

#ifdef __cplusplus
typedef class CTTest CTTest;
#else
typedef struct CTTest CTTest;
#endif /* __cplusplus */

#endif 	/* __CTTest_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IStatsLibWrapper_INTERFACE_DEFINED__
#define __IStatsLibWrapper_INTERFACE_DEFINED__

/* interface IStatsLibWrapper */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IStatsLibWrapper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("78ad298c-fb2a-4435-8614-78a297a72348")
    IStatsLibWrapper : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DescriptiveStatistics( 
            /* [in] */ VARIANT vData,
            /* [optional][in] */ VARIANT vKeys,
            /* [retval][out] */ VARIANT *pvResults) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LinearRegression( 
            /* [in] */ VARIANT vXs,
            /* [in] */ VARIANT vYs,
            /* [retval][out] */ VARIANT *pvResults) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStatsLibWrapperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStatsLibWrapper * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStatsLibWrapper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStatsLibWrapper * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IStatsLibWrapper * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IStatsLibWrapper * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IStatsLibWrapper * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IStatsLibWrapper * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DescriptiveStatistics )( 
            IStatsLibWrapper * This,
            /* [in] */ VARIANT vData,
            /* [optional][in] */ VARIANT vKeys,
            /* [retval][out] */ VARIANT *pvResults);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LinearRegression )( 
            IStatsLibWrapper * This,
            /* [in] */ VARIANT vXs,
            /* [in] */ VARIANT vYs,
            /* [retval][out] */ VARIANT *pvResults);
        
        END_INTERFACE
    } IStatsLibWrapperVtbl;

    interface IStatsLibWrapper
    {
        CONST_VTBL struct IStatsLibWrapperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStatsLibWrapper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStatsLibWrapper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStatsLibWrapper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStatsLibWrapper_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IStatsLibWrapper_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IStatsLibWrapper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IStatsLibWrapper_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IStatsLibWrapper_DescriptiveStatistics(This,vData,vKeys,pvResults)	\
    ( (This)->lpVtbl -> DescriptiveStatistics(This,vData,vKeys,pvResults) ) 

#define IStatsLibWrapper_LinearRegression(This,vXs,vYs,pvResults)	\
    ( (This)->lpVtbl -> LinearRegression(This,vXs,vYs,pvResults) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStatsLibWrapper_INTERFACE_DEFINED__ */


#ifndef __IStatisticalTest_INTERFACE_DEFINED__
#define __IStatisticalTest_INTERFACE_DEFINED__

/* interface IStatisticalTest */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IStatisticalTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e9d506fb-0dc6-4e80-95a0-60fc7fcedbee")
    IStatisticalTest : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SummaryDataTTest( 
            /* [in] */ DOUBLE mu0,
            /* [in] */ DOUBLE xbar,
            /* [in] */ DOUBLE sx,
            /* [in] */ DOUBLE n,
            /* [retval][out] */ VARIANT *pvResults) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OneSampleTTest( 
            /* [in] */ DOUBLE mu0,
            /* [in] */ VARIANT vX1,
            /* [retval][out] */ VARIANT *pvResults) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TwoSampleTTest( 
            /* [in] */ VARIANT vX1,
            /* [in] */ VARIANT vX2,
            /* [retval][out] */ VARIANT *pvResults) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStatisticalTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStatisticalTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStatisticalTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStatisticalTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IStatisticalTest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IStatisticalTest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IStatisticalTest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IStatisticalTest * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SummaryDataTTest )( 
            IStatisticalTest * This,
            /* [in] */ DOUBLE mu0,
            /* [in] */ DOUBLE xbar,
            /* [in] */ DOUBLE sx,
            /* [in] */ DOUBLE n,
            /* [retval][out] */ VARIANT *pvResults);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OneSampleTTest )( 
            IStatisticalTest * This,
            /* [in] */ DOUBLE mu0,
            /* [in] */ VARIANT vX1,
            /* [retval][out] */ VARIANT *pvResults);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TwoSampleTTest )( 
            IStatisticalTest * This,
            /* [in] */ VARIANT vX1,
            /* [in] */ VARIANT vX2,
            /* [retval][out] */ VARIANT *pvResults);
        
        END_INTERFACE
    } IStatisticalTestVtbl;

    interface IStatisticalTest
    {
        CONST_VTBL struct IStatisticalTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStatisticalTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStatisticalTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStatisticalTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStatisticalTest_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IStatisticalTest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IStatisticalTest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IStatisticalTest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IStatisticalTest_SummaryDataTTest(This,mu0,xbar,sx,n,pvResults)	\
    ( (This)->lpVtbl -> SummaryDataTTest(This,mu0,xbar,sx,n,pvResults) ) 

#define IStatisticalTest_OneSampleTTest(This,mu0,vX1,pvResults)	\
    ( (This)->lpVtbl -> OneSampleTTest(This,mu0,vX1,pvResults) ) 

#define IStatisticalTest_TwoSampleTTest(This,vX1,vX2,pvResults)	\
    ( (This)->lpVtbl -> TwoSampleTTest(This,vX1,vX2,pvResults) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStatisticalTest_INTERFACE_DEFINED__ */



#ifndef __StatsATLCOMLib_LIBRARY_DEFINED__
#define __StatsATLCOMLib_LIBRARY_DEFINED__

/* library StatsATLCOMLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_StatsATLCOMLib;

EXTERN_C const CLSID CLSID_StatsLibWrapper;

#ifdef __cplusplus

class DECLSPEC_UUID("d81e7eb0-39a8-4785-970b-3f4f5ae68549")
StatsLibWrapper;
#endif

EXTERN_C const CLSID CLSID_CTTest;

#ifdef __cplusplus

class DECLSPEC_UUID("a67772d3-83c6-4748-87f1-9e94688f5477")
CTTest;
#endif
#endif /* __StatsATLCOMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

unsigned long             __RPC_USER  VARIANT_UserSize64(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal64(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal64(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree64(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


