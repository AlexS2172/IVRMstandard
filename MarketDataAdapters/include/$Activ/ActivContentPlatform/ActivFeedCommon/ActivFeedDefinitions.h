/**
 *	@file	ActivFeedDefinitions.h
 *
 *	@brief	Header file for activ feed definitions.
 *
 *  $Log: $
 */

#if !defined (ACTIV_ACTIV_FEED_DEFINITIONS_H)
#define ACTIV_ACTIV_FEED_DEFINITIONS_H

#include "ActivMiddleware/Activ.h"

namespace Activ
{

namespace Feed
{

typedef uint8_t EventType;					///< The event type type definition.

typedef uint16_t FieldId;					///< The field id type definition.

typedef uint8_t IndexNumber;				///< The index number type definition.
typedef uint8_t IndexType;					///< The index type definition.
typedef uint8_t IndexProperties;			///< The index properties definition.

typedef uint16_t PermissionId;				///< The permission id type definition.
typedef uint8_t PermissionLevel;			///< The permission level type definition.

typedef uint16_t RelationshipId;			///< The relationship id type definition.

typedef uint16_t TableId;					///< The table id type definition.
typedef uint16_t TableNo;					///< The table number type definition.
typedef uint8_t TableVersion;				///< The table version type definition.

typedef uint16_t UpdateId;					///< The update id type definition.

typedef uint32_t Context;					///< The symbol context type definition.

const TableNo TABLE_NO_UNDEFINED = ~0;		///< Table number undefined.
const Context CONTEXT_UNDEFINED = ~0;		///< Context undefined.

} // namespace Feed

} // namespace Activ

#endif // !defined (ACTIV_ACTIV_FEED_DEFINITIONS_H)
