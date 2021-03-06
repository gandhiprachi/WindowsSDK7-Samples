// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.


/****************************************************************************
						 Microsoft RPC
          
                         umarsh Example

    FILE:       umarshp.c

    PURPOSE:    Remote procedures that are linked with the server
                side of RPC distributed application

    FUNCTIONS:  ModifyMyWString() - Display the string passed in, modify it, and return
				ModifyMyString() - 
                Shutdown() - shuts down the server side

    COMMENTS:   Related to umarshs.c

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "umarshs.h"    // header file generated by MIDL compiler


/****************************************************************************

Function:   ModifyMyWString

Parameters: pStr : Pointer to pointer to UNICODE string

Returns:    none

Purpose:    Display the string passed in, modify it, and return

Comments:   This sample is meant to demonstrate a typical use of the
            represent_as attribute:  The client and server have different
            local views of the data, although the IDL file describes the
            wire contract.

****************************************************************************/
void ModifyMyWString(IN RPC_BINDING_HANDLE hBinding,
					 WCHAR_STRING * pStr)
{
    wprintf_s(L"\nModifyMyWString: received UNICODE string:\n%s\n\n", *pStr );
    wcscpy_s(*pStr, wcslen(*pStr),L"This string comes back on the wire as UNICODE");
    wprintf_s(L"ModifyMyWString: sending UNICODE string:\n%s\n\n", *pStr );

}

/****************************************************************************

Function:   ModifyMyString

Parameters: pStr : Pointer to pointer to UNICODE string

Returns:    none

Purpose:    Display the string passed in, modify it, and return

Comments:   This sample is meant to demonstrate a typical use of the
            represent_as attribute:  The client and server have different
            local views of the data, although the IDL file describes the
            wire contract.

****************************************************************************/
void ModifyMyString(IN RPC_BINDING_HANDLE hBinding,
					WCHAR_STRING * pStr)
{
    wprintf_s(L"\nModifyMyString: received UNICODE string:\n%s\n\n", *pStr );
    wcscpy_s(*pStr,wcslen(*pStr), L"This UNICODE string comes back on the wire as ASCII");
    wprintf_s(L"ModifyMyString: sending UNICODE string:\n%s\n\n", *pStr );

}


/****************************************************************************

Function:   Shutdown

Parameters: none

Returns:    none

Purpose:    Make the server stop listening for client applications.

Comments:   The two NULL parameters passed to RpcServerUnregisterIf are
            a show of brute force:  they tell the function to turn
            off all registered interfaces.  See the RPC API function
            reference for more information about these functions.

****************************************************************************/

void Shutdown(IN RPC_BINDING_HANDLE hBinding)
{
    RPC_STATUS status;

    printf_s("Calling RpcMgmtStopServerListening\n");
    status = RpcMgmtStopServerListening(NULL);
    printf_s("RpcMgmtStopServerListening returned: 0x%x\n", status);
    if (status) {
        exit(status);
    }

    printf_s("Calling RpcServerUnregisterIf\n");
    status = RpcServerUnregisterIf(NULL, NULL, FALSE);
    printf_s("RpcServerUnregisterIf returned 0x%x\n", status);
    if (status) {
        exit(status);
    }
}

/* end file umarshp.c */
