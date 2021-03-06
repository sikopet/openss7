/*****************************************************************************

 @(#) src/snmp/ds0Bundle.h

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2015  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation; version 3 of the License.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
 details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>, or
 write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA.

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 *****************************************************************************/

#ifndef __LOCAL_DS0BUNDLE_H__
#define __LOCAL_DS0BUNDLE_H__

/*
 * This file was generated by mib2c and is intended for use as a mib module
 * for the ucd-snmp snmpd agent.
 */

extern const char sa_program[];
extern int sa_fclose;			/* default close files between requests */
extern int sa_changed;			/* indication to reread MIB configuration */
extern int sa_stats_refresh;		/* indications that statistics, the mib or its tables need to be refreshed */
extern int sa_request;			/* request number for per-request actions */

/* our storage structure(s) */
struct ds0Bundle_data {
	struct ds0Bundle_data *ds0Bundle_old;
	uint ds0Bundle_rsvs;
	uint ds0Bundle_tsts;
	uint ds0Bundle_sets;
	uint ds0Bundle_request;
	long dsx0BundleNextIndex;	/* ReadWrite */
};
struct dsx0BondingTable_data {
	struct dsx0BondingTable_data *dsx0BondingTable_old;
	uint dsx0BondingTable_rsvs;
	uint dsx0BondingTable_tsts;
	uint dsx0BondingTable_sets;
	uint dsx0BondingTable_request;
	uint dsx0BondingTable_refs;
	uint dsx0BondingTable_id;
	long ifIndex;			/* ReadOnly */
	long dsx0BondMode;		/* Create */
	long dsx0BondStatus;		/* ReadOnly */
	long dsx0BondRowStatus;		/* Create */
};
struct dsx0BundleTable_data {
	struct dsx0BundleTable_data *dsx0BundleTable_old;
	uint dsx0BundleTable_rsvs;
	uint dsx0BundleTable_tsts;
	uint dsx0BundleTable_sets;
	uint dsx0BundleTable_request;
	uint dsx0BundleTable_refs;
	uint dsx0BundleTable_id;
	long dsx0BundleIndex;		/* NoAccess */
	long dsx0BundleIfIndex;		/* ReadOnly */
	uint8_t *dsx0BundleCircuitIdentifier;	/* Create */
	size_t dsx0BundleCircuitIdentifierLen;
	long dsx0BundleRowStatus;	/* Create */
};

/* storage declarations */
extern struct ds0Bundle_data *ds0BundleStorage;
extern struct header_complex_index *dsx0BondingTableStorage;
extern struct header_complex_index *dsx0BundleTableStorage;

/* enum definitions from the covered mib sections */

#define DSX0BONDMODE_NONE                        1
#define DSX0BONDMODE_OTHER                       2
#define DSX0BONDMODE_MODE0                       3
#define DSX0BONDMODE_MODE1                       4
#define DSX0BONDMODE_MODE2                       5
#define DSX0BONDMODE_MODE3                       6

#define DSX0BONDSTATUS_IDLE                      1
#define DSX0BONDSTATUS_CALLSETUP                 2
#define DSX0BONDSTATUS_DATATRANSFER              3

/* notifications */

/* scalars accessible only for notify */

/* object id definitions */
extern oid ds0BondingGroup_oid[11];
extern oid ds0BundleConfigGroup_oid[11];
extern oid ds0BundleCompliance_oid[11];

/* function prototypes */
/* trap function prototypes */

/* variable function prototypes */
void init_ds0Bundle(void);
void deinit_ds0Bundle(void);
int term_ds0Bundle(int majorID, int minorID, void *serverarg, void *clientarg);
FindVarMethod var_ds0Bundle;
struct ds0Bundle_data *ds0Bundle_create(void);
struct ds0Bundle_data *ds0Bundle_duplicate(struct ds0Bundle_data *);
int ds0Bundle_destroy(struct ds0Bundle_data **);
int ds0Bundle_add(struct ds0Bundle_data *);
void parse_ds0Bundle(const char *, char *);
SNMPCallback store_ds0Bundle;
void refresh_ds0Bundle(int);
FindVarMethod var_dsx0BondingTable;
struct dsx0BondingTable_data *dsx0BondingTable_create(void);
struct dsx0BondingTable_data *dsx0BondingTable_duplicate(struct dsx0BondingTable_data *);
int dsx0BondingTable_destroy(struct dsx0BondingTable_data **);
int dsx0BondingTable_add(struct dsx0BondingTable_data *);
int dsx0BondingTable_del(struct dsx0BondingTable_data *);
void parse_dsx0BondingTable(const char *, char *);
SNMPCallback store_dsx0BondingTable;
void refresh_dsx0BondingTable(int);
FindVarMethod var_dsx0BundleTable;
struct dsx0BundleTable_data *dsx0BundleTable_create(void);
struct dsx0BundleTable_data *dsx0BundleTable_duplicate(struct dsx0BundleTable_data *);
int dsx0BundleTable_destroy(struct dsx0BundleTable_data **);
int dsx0BundleTable_add(struct dsx0BundleTable_data *);
int dsx0BundleTable_del(struct dsx0BundleTable_data *);
void parse_dsx0BundleTable(const char *, char *);
SNMPCallback store_dsx0BundleTable;
void refresh_dsx0BundleTable(int);

WriteMethod write_dsx0BondMode;
WriteMethod write_dsx0BondRowStatus;
WriteMethod write_dsx0BundleNextIndex;
WriteMethod write_dsx0BundleCircuitIdentifier;
WriteMethod write_dsx0BundleRowStatus;
#endif				/* __LOCAL_DS0BUNDLE_H__ */
