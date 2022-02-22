

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IStatsLibWrapper,0x78ad298c,0xfb2a,0x4435,0x86,0x14,0x78,0xa2,0x97,0xa7,0x23,0x48);


MIDL_DEFINE_GUID(IID, IID_IStatisticalTest,0xe9d506fb,0x0dc6,0x4e80,0x95,0xa0,0x60,0xfc,0x7f,0xce,0xdb,0xee);


MIDL_DEFINE_GUID(IID, LIBID_StatsATLCOMLib,0x19393278,0xb368,0x4b36,0x91,0xc4,0x7f,0xb4,0xeb,0x09,0x5c,0xcf);


MIDL_DEFINE_GUID(CLSID, CLSID_StatsLibWrapper,0xd81e7eb0,0x39a8,0x4785,0x97,0x0b,0x3f,0x4f,0x5a,0xe6,0x85,0x49);


MIDL_DEFINE_GUID(CLSID, CLSID_CTTest,0xa67772d3,0x83c6,0x4748,0x87,0xf1,0x9e,0x94,0x68,0x8f,0x54,0x77);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



