/* 
 * FreeModbus Libary: A portable Modbus implementation for Modbus ASCII/RTU.
 * Copyright (c) 2006 Christian Walter <wolti@sil.at>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * File: $Id: mbconfig.h,v 1.15 2010/06/06 13:54:40 wolti Exp $
 */

#ifndef _MB_CONFIG_H
#define _MB_CONFIG_H

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif
/* ----------------------- Defines ------------------------------------------*/

/*! \brief If Modbus RTU support is enabled. */
#define MB_RTU_ENABLED                          (  1 )

/*! \brief Maximum number of Modbus functions codes the protocol stack
 *    should support.
 *
 * The maximum number of supported Modbus functions must be greater than
 * the sum of all enabled functions in this file and custom function
 * handlers. If set to small adding more functions will fail.
 */
#define MB_FUNC_HANDLERS_MAX                    ( 2 )// 4


/*! \brief If the <em>Read Holding Registers</em> function should be enabled. */
#define MB_FUNC_READ_HOLDING_ENABLED            (  1 )

/*! \brief If the <em>Write Multiple registers</em> function should be enabled. */
#define MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED  (  1 )


/*! @} */
#ifdef __cplusplus
    PR_END_EXTERN_C
#endif
#endif
