/* @(#)omni.h	40.6 4/14/97 12:47:14 */
/* OMNI.H V5.1 */

#if !defined( __OMNI_LOADED )
#define __OMNI_LOADED 1

#if defined(_AIX43)
#include <sys/inttypes.h>
#endif /* _AIX43 */

#if !defined( __OMNI_CODES_LOADED )
#define OMNI_DU_DATALOST    0x0EB38008	/* info from sender possibly lost */
#define OMNI_DU_LINKLOST    0x0EB38014	/* link to OMdu server lost */
#define OMNI_DU_SENDERLOST  0x0EB3801C	/* sender service lost */
#endif

#define SEV_WARNING		0	/* Severity warning in log message */
					/* O%%iLogMessage.Severity value */
#define SEV_SUCCESS		1	/* Severity success in log message */
					/* O%%iLogMessage.Severity value */
#define SEV_ERROR		2	/* Severity error in log message */
					/* O%%iLogMessage.Severity value */
#define SEV_INFORMATION		3	/* Severity info. in log message */
					/* O%%iLogMessage.Severity value */
#define SEV_FATAL		4	/* Severity fatal in log message */
					/* O%%iLogMessage.Severity value */

#define ENT_TRANSACTION_SYSTEM	0	/* Log message entity */
					/* O%%iLogMessage.Entity value */
#define ENT_NETWORK		1	/* Log message entity */
					/* O%%iLogMessage.Entity value */
#define ENT_SECURITY		2	/* Log message entity */
					/* O%%iLogMessage.Entity value */
#define ENT_OPERATING_SYSTEM	3	/* Log message entity */
					/* O%%iLogMessage.Entity value */
#define ENT_TRACE		4	/* Log message entity */
					/* O%%iLogMessage.Entity value */
#define ENT_TABLES		5	/* Log message entity */
					/* O%%iLogMessage.Entity value */
#define ENT_TRANSACTION		6	/* Log message entity */
					/* O%%iLogMessage.Entity value */
#define ENT_OMDU		7	/* Messages from OMdu component */ 

#define USER_NAME_LENGTH	32	/* Login msg username field length */
#define USER_PASSWORD_LENGTH	32	/* Login msg password field length */
#define NEW_ENCRYPTION_METHOD   2       /* a constant indicating encryption method */

/*
    known omniapi get info information types
*/
#define OMNI_INFTYP_USERCODE 1		/* pick up the usercode */
#define OMNI_INFTYP_FACTYP_E0 2		/* retrieve the 1st ext. facility # */
#define OMNI_INFTYP_FACTYP_I0 3		/* retrieve the 1st int. facility # */

typedef	float			real32;
typedef	double			real64;

#if !defined( __INTS_LOADED )

#if !defined(_AIX43)            /* int8 already defined in /usr/include/sys/inttypes.h in AIX 4.3 */
typedef	char			int8;
typedef	short			int16;
typedef	int			int32;
#endif /* _AIX43 */

typedef	unsigned char		uint8;
typedef	unsigned short		uint16;
#if defined( _MSDOS )
typedef long			int32;
typedef unsigned long		uint32;
#else
typedef unsigned int		uint32;
#endif

/*
  OM defs for int64/uint64 bypassed for WinNT/MS DevStudio and Solaris.
  We can define our own which works with your particular C compiler .
  I presume that the developer will only use one particular compiler on one
  particular platform...
  Neil Cossor, ISE, 20000122
*/

#if defined( __hpux ) || defined( sun )	|| defined( _AIX )

    // add appropriate local 64-bit defns.. if we have LONGLONG options, use them, otherwise struct
    #ifdef LONGLONG
        #if !defined(_AIX43)   /* INT64 et al is already defined on AIX 4.3 */
	    typedef long long int64;
	#endif
	typedef unsigned long long uint64;  // correction 20000113
    #else
        #if !defined(_AIX43)   /* INT64 et al is already defined on AIX 4.3 */
	    typedef struct {
		int32	l0;	// big endian op. systems
		uint32	l1;
	    } int64;
	#endif

	typedef struct
	  {
	    uint32	l0;
	    uint32	l1;
	  } uint64;
    #endif

#else
  // Microsoft C supplies __int64's, IBM's VisualAge C++ provides long long's I believe
    typedef __int64 int64;
    typedef unsigned __int64 uint64;
#endif

// const used for arrays where we don't know at compile time how big they will be at runtime
// useful for Solaris compilers, which aren't happy with [] declarations
#define VARIABLE_LENGTH_ARRAY 1


#endif	/* __INTS_LOADED */

typedef char		omni_username[USER_NAME_LENGTH];
typedef char		omni_password[USER_PASSWORD_LENGTH];

typedef	struct
  {
    uint8 country_id_s[2];
    uint8 ex_customer_s[5];
    uint8 user_id_s[5];
  } omni_usercode;

typedef struct
  {
    uint32 status_u;
    uint16 msglen_n;
    int8 message_s[VARIABLE_LENGTH_ARRAY]; /* start of the message text */
  } omni_netwrksts;

typedef struct
  {
    int8 central_module_c;
    int8 server_type_c;
    uint16 broadcast_number_n;
    omni_netwrksts network_status_x;
  } omni_broadcast;

#endif
