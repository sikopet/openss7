/*****************************************************************************

 @(#) $RCSfile$ $Name$($Revision$) $Date$

 -----------------------------------------------------------------------------

 Copyright (c) 2001-2007  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2000  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, version 3 of the license.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 details.

 You should have received a copy of the GNU General Public License along with
 this program.  If not, see <http://www.gnu.org/licenses/>, or write to the
 Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

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

 -----------------------------------------------------------------------------

 Last Modified $Date$ by $Author$

 -----------------------------------------------------------------------------

 $Log$
 *****************************************************************************/

#ident "@(#) $RCSfile$ $Name$($Revision$) $Date$"

static char const ident[] = "$RCSfile$ $Name$($Revision$) $Date$";

/* psaprelease2.c - PPM: respond to release */

#ifndef	lint
static char *rcsid =
    "Header: /xtel/isode/isode/psap2-lpp/RCS/psaprelease2.c,v 9.0 1992/06/16 12:31:57 isode Rel";
#endif

/* 
 * Header: /xtel/isode/isode/psap2-lpp/RCS/psaprelease2.c,v 9.0 1992/06/16 12:31:57 isode Rel
 *
 * Contributed by The Wollongong Group, Inc.
 *
 *
 * Log: psaprelease2.c,v
 * Revision 9.0  1992/06/16  12:31:57  isode
 * Release 8.0
 *
 */

/*
 *				  NOTICE
 *
 *    Acquisition, use, and distribution of this module and related
 *    materials are subject to the restrictions of a license agreement.
 *    Consult the Preface in the User's Manual for the full terms of
 *    this agreement.
 *
 */

/* LINTLIBRARY */

#include <stdio.h>
#include <signal.h>
#define	LPP
#include "PS-types.h"
#include "ppkt.h"
#include "tailor.h"

/*    P-RELEASE.RESPONSE */

int
PRelResponse(sd, status, data, ndata, pi)
	int sd;
	int status;
	PE *data;
	int ndata;
	struct PSAPindication *pi;
{
	SBV smask;
	int result;
	register struct psapblk *pb;

	if (status != SC_ACCEPT)
		return psaplose(pi, PC_PARAMETER, NULLCP, "must accept release request");
	if (data == NULL || ndata <= 0 || data[0] == NULLPE || ndata > NPDATA_PS)
		return psaplose(pi, PC_PARAMETER, NULLCP, "bad release user data");
	if (data[0]->pe_context != PCI_ACSE)
		return psaplose(pi, PC_PARAMETER, NULLCP, "wrong context for release user data");
	missingP(pi);

	smask = sigioblock();

	psapFsig(pb, sd);

	result = PRelResponseAux(pb, data[0], pi);

	freepblk(pb);

	(void) sigiomask(smask);

	return result;
}

/*  */

static int
PRelResponseAux(pb, data, pi)
	register struct psapblk *pb;
	PE data;
	struct PSAPindication *pi;
{
	int result;
	PE pe;
	PS ps;
	register struct type_PS_ReleaseResponse__PDU *pdu;

	if ((pdu = (struct type_PS_ReleaseResponse__PDU *) malloc(sizeof *pdu))
	    == NULL)
		return psaplose(pi, PC_CONGEST, NULLCP, "out of memory");
	pdu->reference = pb->pb_reliability == LOW_QUALITY ? pb->pb_reference : NULLRF;
	pdu->user__data = data;

	pe = NULLPE;
	result = encode_PS_ReleaseResponse__PDU(&pe, 1, 0, NULLCP, pdu);

	pdu->reference = NULL;
	pdu->user__data = NULLPE;
	free_PS_ReleaseResponse__PDU(pdu);

	if (result != NOTOK) {
		PLOGP(psap2_log, PS_PDUs, pe, "ReleaseResponse-PDU", 0);

		if ((result = pe2ps(ps = pb->pb_stream, pe)) == NOTOK)
			(void) pslose(pi, ps->ps_errno);
		else
			result = OK;
	} else
		(void) psaplose(pi, PC_CONGEST, NULLCP, "error encoding PDU: %s", PY_pepy);

	if (pe)
		pe_free(pe);

	return result;
}