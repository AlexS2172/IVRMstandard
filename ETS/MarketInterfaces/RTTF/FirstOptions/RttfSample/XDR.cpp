/////////////////////////////////////////////////////////////////////////////
//        File:	XDR.cpp
//      Author:	Changes and port by DD, original by Sun Microsystems.
//     Purpose: General purpose marshalling code.
//     Classes:
//   Copyright:	(c) Copyright 2000, First Options of Chicago
//				All rights reserved.
/////////////////////////////////////////////////////////////////////////////
//  Revision History:
/////////////////////////////////////////////////////////////////////////////

 /* @(#)xdr.c	2.1 88/07/29 4.0 RPCSRC */
 /*
  * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
  * unrestricted use provided that this legend is included on all tape
  * media and as a part of the software program in whole or part.  Users
  * may copy or modify Sun RPC without charge, but are not authorized
  * to license or distribute it to anyone else except as part of a product or
  * program developed by the user.
  *
  * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
  * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
  * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
  *
  * Sun RPC is provided with no support and without any obligation on the
  * part of Sun Microsystems, Inc. to assist in its use, correction,
  * modification or enhancement.
  *
  * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
  * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
  * OR ANY PART THEREOF.
  *
  * In no event will Sun Microsystems, Inc. be liable for any lost revenue
  * or profits or other special, indirect and consequential damages, even if
  * Sun has been advised of the possibility of such damages.
  *
  * Sun Microsystems, Inc.
  * 2550 Garcia Avenue
  * Mountain View, California  94043
  */
 #if !defined(lint) && defined(SCCSIDS)
 static char sccsid[] = "@(#)xdr.c 1.35 87/08/12";
 #endif

 /*
  * xdr.c, Generic XDR routines implementation.
  *
  * Copyright (C) 1986, Sun Microsystems, Inc.
  *
  * These are the "generic" xdr routines used to serialize and de-serialize
  * most common data items.  See xdr.h for more info on the interface to
  * xdr.
  */

 #include <stdio.h>

#if defined(__BORLANDC__)
	#include "xdr.h"
	#include <string.h>
#elif defined(_MSC_VER)
	#include "stdafx.h"
	
	#include "xdr.h"
//#endif

//#if defined(SUN)
//	#include <rpc/types.h>
//	#include <rpc/xdr.h>
//#endif

//#define DEBUG
#if defined(DEBUG)
	#undef DEBUG     // VCPP 6.0 defines DEBUG so undefine it so no reference to tprintf 
#endif

#if defined(DEBUG)
 void	tprintf(char *format, ...);
#endif

 /*
  * constants specific to the xdr "protocol"
  */
 #define XDR_FALSE	((long) 0)
 #define XDR_TRUE	((long) 1)
 #define LASTUNSIGNED	((u_int) 0-1)

 /*
  * for unit alignment
  */
 static char xdr_zero[BYTES_PER_XDR_UNIT] = { 0, 0, 0, 0 };

 /*
  * Free a data structure using XDR
  * Not a filter, but a convenient utility nonetheless
  */
 void
xdr_free(xdrproc_t proc, char *objp)
 {
	XDR x;

	x.x_op = XDR_FREE;
	(*proc)(&x, objp);
 }

 /*
  * XDR nothing
  */
 bool_t
xdr_void()
 {
	return (TRUE);
 }

 /*
  * XDR integers
  */
 bool_t
xdr_int(XDR *xdrs, int *ip)
 {

 #ifdef lint
	(void) (xdr_short(xdrs, (short *)ip));
	return (xdr_long(xdrs, (long *)ip));
 #else
	if (sizeof (int) == sizeof (long)) {
		return (xdr_long(xdrs, (long *)ip));
	} else {
		return (xdr_short(xdrs, (short *)ip));
	}
 #endif
 }

 /*
  * XDR unsigned integers
  */
 bool_t
xdr_u_int(XDR *xdrs, u_int *up)
 {

 #ifdef lint
	(void) (xdr_short(xdrs, (short *)up));
	return (xdr_u_long(xdrs, (u_long *)up));
 #else
	if (sizeof (u_int) == sizeof (u_long)) {
		return (xdr_u_long(xdrs, (u_long *)up));
	} else {
		return (xdr_short(xdrs, (short *)up));
	}
 #endif
 }

 /*
  * XDR long integers
  * same as xdr_u_long - open coded to save a proc call!
  */
 bool_t
xdr_long(XDR *xdrs, long *lp)
 {
	if (xdrs->x_op == XDR_ENCODE)
		return (XDR_PUTLONG(xdrs, lp));

	if (xdrs->x_op == XDR_DECODE)
		return (XDR_GETLONG(xdrs, lp));

	if (xdrs->x_op == XDR_FREE)
		return (TRUE);

	return (FALSE);
 }

 /*
  * XDR unsigned long integers
  * same as xdr_long - open coded to save a proc call!
  */
 bool_t
xdr_u_long(XDR *xdrs, u_long *ulp)
 {
	if (xdrs->x_op == XDR_DECODE)
		return (XDR_GETLONG(xdrs, (long *)ulp));
	if (xdrs->x_op == XDR_ENCODE)
		return (XDR_PUTLONG(xdrs, (long *)ulp));
	if (xdrs->x_op == XDR_FREE)
		return (TRUE);
	return (FALSE);
 }

 /*
  * XDR short integers
  */
 bool_t
xdr_short(XDR *xdrs, short *sp)
 {
	long l;

	switch (xdrs->x_op) {

	case XDR_ENCODE:
		l = (long) *sp;
		return (XDR_PUTLONG(xdrs, &l));

	case XDR_DECODE:
		if (!XDR_GETLONG(xdrs, &l)) {
			return (FALSE);
		}
		*sp = (short) l;
		return (TRUE);

	case XDR_FREE:
		return (TRUE);
	}
	return (FALSE);
 }

 /*
  * XDR unsigned short integers
  */
 bool_t
xdr_u_short(XDR *xdrs, u_short *usp)
 {
	long l;

	switch (xdrs->x_op) {

	case XDR_ENCODE:
		l = (long) *usp;
		return (XDR_PUTLONG(xdrs, &l));

	case XDR_DECODE:
		if (!XDR_GETLONG(xdrs, &l)) {
			return (FALSE);
		}
		*usp = (u_short) l;
		return (TRUE);

	case XDR_FREE:
		return (TRUE);
	}
	return (FALSE);
 }


 /*
  * XDR a char
  */
 bool_t
xdr_char(XDR *xdrs, char *cp)
 {
	int i;

	i = (*cp);
	if (!xdr_int(xdrs, &i)) {
		return (FALSE);
	}
/*	*cp = i;	04/12/99 BKASH Added cast to prevent compiler warning. */
	*cp = (char)i;
	return (TRUE);
 }

 /*
  * XDR an unsigned char
  */
 bool_t
xdr_u_char(XDR *xdrs, u_char *cp)
//xdr_u_char(XDR *xdrs, char *cp)
 {
	u_int u;

	u = (*cp);
	if (!xdr_u_int(xdrs, &u)) {
		return (FALSE);
	}
/*	*cp = u;	04/12/99 BKASH Added cast to prevent compiler warning. */
	*cp = (u_char)u;
	return (TRUE);
 }

 /*
  * XDR booleans
  */
 bool_t
xdr_bool(XDR *xdrs, bool_t *bp)
 {
	long lb;

	switch (xdrs->x_op) {

	case XDR_ENCODE:
		lb = *bp ? XDR_TRUE : XDR_FALSE;
		return (XDR_PUTLONG(xdrs, &lb));

	case XDR_DECODE:
		if (!XDR_GETLONG(xdrs, &lb)) {
			return (FALSE);
		}
		*bp = (lb == XDR_FALSE) ? FALSE : TRUE;
		return (TRUE);

	case XDR_FREE:
		return (TRUE);
	}
	return (FALSE);
 }

 /*
  * XDR enumerations
  */
 bool_t
xdr_enum(XDR *xdrs, enum_t *ep)
 {
 #ifndef lint
	enum sizecheck { SIZEVAL };	/* used to find the size of an enum */

	/*
	 * enums are treated as ints
	 */
	if (sizeof (enum sizecheck) == sizeof (long)) {
		return (xdr_long(xdrs, (long *)ep));
	} else if (sizeof (enum sizecheck) == sizeof (short)) {
		return (xdr_short(xdrs, (short *)ep));
	} else {
		return (FALSE);
	}
 #else
	(void) (xdr_short(xdrs, (short *)ep));
	return (xdr_long(xdrs, (long *)ep));
 #endif
 }

 /*
  * XDR opaque data
  * Allows the specification of a fixed size sequence of opaque bytes.
  * cp points to the opaque object and cnt gives the byte length.
  */
 bool_t
xdr_opaque(XDR *xdrs, caddr_t cp, u_int cnt)
 {
	u_int rndup;
	static char crud[BYTES_PER_XDR_UNIT];

	/*
	 * if no data we are done
	 */
	if (cnt == 0)
		return (TRUE);

	/*
	 * round byte count to full xdr units
	 */
	rndup = cnt % BYTES_PER_XDR_UNIT;
	if (rndup > 0)
		rndup = BYTES_PER_XDR_UNIT - rndup;

	if (xdrs->x_op == XDR_DECODE) {
		if (!XDR_GETBYTES(xdrs, cp, cnt)) {
			return (FALSE);
		}
		if (rndup == 0)
			return (TRUE);
		return (XDR_GETBYTES(xdrs, crud, rndup));
	}

	if (xdrs->x_op == XDR_ENCODE) {
		if (!XDR_PUTBYTES(xdrs, cp, cnt)) {
			return (FALSE);
		}
		if (rndup == 0)
			return (TRUE);
		return (XDR_PUTBYTES(xdrs, xdr_zero, rndup));
	}

	if (xdrs->x_op == XDR_FREE) {
		return (TRUE);
	}

	return (FALSE);
 }

 /*
  * XDR counted bytes
  * *cpp is a pointer to the bytes, *sizep is the count.
  * If *cpp is NULL maxsize bytes are allocated
  */
 bool_t
xdr_bytes(XDR *xdrs, char **cpp, u_int *sizep, u_int maxsize)
 {
	char *sp = *cpp;  /* sp is the actual string pointer */
	u_int nodesize;

	/*
	 * first deal with the length since xdr bytes are counted
	 */
	if (! xdr_u_int(xdrs, sizep)) {
		return (FALSE);
	}
	nodesize = *sizep;
	if ((nodesize > maxsize) && (xdrs->x_op != XDR_FREE)) {
		return (FALSE);
	}

	/*
	 * now deal with the actual bytes
	 */
	switch (xdrs->x_op) {

	case XDR_DECODE:
		if (nodesize == 0) {
			return (TRUE);
		}
		if (sp == NULL) {
			*cpp = sp = (char *)mem_alloc(nodesize);
			#if defined(DEBUG)
				tprintf("%s[%d] mem_alloc(%d) -> %p\n", __FILE__, __LINE__, nodesize, sp);
			#endif
		}
		if (sp == NULL) {
			(void) fprintf(stderr, "xdr_bytes: out of memory\n");
			return (FALSE);
		}
		/* fall into ... */

	case XDR_ENCODE:
		return (xdr_opaque(xdrs, sp, nodesize));

	case XDR_FREE:
		if (sp != NULL) {
			mem_free(sp, nodesize);
			#if defined(DEBUG)
				tprintf("%s[%d] mem_free(%d) -> %p\n", __FILE__, __LINE__, nodesize, sp);
			#endif
			*cpp = NULL;
		}
		return (TRUE);
	}
	return (FALSE);
 }

 /*
  * Implemented here due to commonality of the object.
  */
 bool_t
xdr_netobj(XDR *xdrs, struct netobj *np)
 {

	return (xdr_bytes(xdrs, &np->n_bytes, &np->n_len, MAX_NETOBJ_SZ));
 }

#if defined(XDR_UNION)
 /*
  * XDR a descriminated union
  * Support routine for discriminated unions.
  * You create an array of xdrdiscrim structures, terminated with
  * an entry with a null procedure pointer.  The routine gets
  * the discriminant value and then searches the array of xdrdiscrims
  * looking for that value.  It calls the procedure given in the xdrdiscrim
  * to handle the discriminant.  If there is no specific routine a default
  * routine may be called.
  * If there is no specific or default routine an error is returned.
  */
 bool_t
xdr_union(
	XDR		*xdrs,
	enum_t				*dscmp,		/* enum to decide which arm to work on */
	char				*unp,		/* the union itself */
	struct xdr_discrim	*choices,	/* [value, xdr proc] for each arm */
	xdrproc_t			dfault)	/* default xdr routine */
 {
	enum_t dscm;

	/*
	 * we deal with the discriminator;  it's an enum
	 */
	if (! xdr_enum(xdrs, dscmp)) {
		return (FALSE);
	}
	dscm = *dscmp;

	/*
	 * search choices for a value that matches the discriminator.
	 * if we find one, execute the xdr routine for that value.
	 */
	for (; choices->proc != NULL_xdrproc_t; choices++) {
		if (choices->value == dscm)
			return ((*(choices->proc))(xdrs, unp, LASTUNSIGNED));
	}

	/*
	 * no match - execute the default xdr routine if there is one
	 */
	return ((dfault == NULL_xdrproc_t) ? FALSE :
	    (*dfault)(xdrs, unp, LASTUNSIGNED));
 }
#endif

 /*
  * Non-portable xdr primitives.
  * Care should be taken when moving these routines to new architectures.
  */


 /*
  * XDR null terminated ASCII strings
  * xdr_string deals with "C strings" - arrays of bytes that are
  * terminated by a NULL character.  The parameter cpp references a
  * pointer to storage; If the pointer is null, then the necessary
  * storage is allocated.  The last parameter is the max allowed length
  * of the string as specified by a protocol.
  */
 bool_t
xdr_string(XDR *xdrs, char **cpp, u_int maxsize)
 {
	char *sp = *cpp;  /* sp is the actual string pointer */
	u_int size;
	u_int nodesize;

	/*
	 * first deal with the length since xdr strings are counted-strings
	 */
	switch (xdrs->x_op) {
	case XDR_FREE:
		if (sp == NULL) {
			return(TRUE);	/* already free */
		}
		/* fall through... */
	case XDR_ENCODE:
		size = strlen(sp);
		break;
	}
	if (! xdr_u_int(xdrs, &size)) {
		return (FALSE);
	}
	if (size > maxsize) {
		return (FALSE);
	}
	nodesize = size + 1;

	/*
	 * now deal with the actual bytes
	 */
	switch (xdrs->x_op) {

	case XDR_DECODE:
		if (nodesize == 0) {
			return (TRUE);
		}
		if (sp == NULL) {
			*cpp = sp = (char *)mem_alloc(nodesize);
			#if defined(DEBUG)
				tprintf("%s[%d] mem_alloc(%d) -> %p\n", __FILE__, __LINE__, nodesize, sp);
			#endif
		}
		if (sp == NULL) {
			(void) fprintf(stderr, "xdr_string: out of memory\n");
			return (FALSE);
		}
		sp[size] = 0;
		/* fall into ... */

	case XDR_ENCODE:
		return (xdr_opaque(xdrs, sp, size));

	case XDR_FREE:
		mem_free(sp, nodesize);
		#if defined(DEBUG)
			tprintf("%s[%d] mem_free(%d) -> %p\n", __FILE__, __LINE__, nodesize, sp);
		#endif
		*cpp = NULL;
		return (TRUE);
	}
	return (FALSE);
 }

 /*
  * Wrapper for xdr_string that can be called directly from
  * routines like clnt_call
  */
 bool_t
xdr_wrapstring(XDR *xdrs, char **cpp)
 {
	if (xdr_string(xdrs, cpp, LASTUNSIGNED)) {
		return (TRUE);
	}
	return (FALSE);
 }
