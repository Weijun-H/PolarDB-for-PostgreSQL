/*-------------------------------------------------------------------------
 *
 * polarx_locator.h
 *		 Locator utility functions 
 *
 * Portions Copyright (c) 2012-2018, PostgreSQL Global Development Group
 * Copyright (c) 2020, Apache License Version 2.0
 *
 * IDENTIFICATION
 *		  contrib/polarx/include/polarx/polarx_locator.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef POLARX_LOCATOR_H
#define POLARX_LOCATOR_H 

#include "nodes/relation.h"
#include "foreign/foreign.h"
#include "pgxc/locator.h"

typedef struct Distribution
{
	char     distributionType;
	Node            *distributionExpr;
	Bitmapset       *nodes;
	Bitmapset       *restrictNodes;
} Distribution;

extern List *GetRelationNodesWithDistribution(Distribution *distribution, Datum valueForDistCol,
						bool isValueNull,
						RelationAccessType accessType);
extern List *GetRelationNodesWithRelation(Relation relation, Datum valueForDistCol,
						bool isValueNull,
						RelationAccessType accessType,  int numDataNodes);
extern int GetRelationPartAttrNum(ForeignTable *table);
#endif		/* POLARX_LOCATOR_H */