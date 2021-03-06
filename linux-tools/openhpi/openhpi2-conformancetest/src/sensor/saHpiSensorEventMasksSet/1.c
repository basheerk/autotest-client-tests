/*
 * (C) Copyright IBM Corp. 2004, 2005
 * Copyright (c) 2005, Intel Corporation
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 *
 * Author(s):
 *      Carl McAdams <carlmc@us.ibm.com>
 *      Xiaowei Yang <xiaowei.yang@intel.com>
 *
 * Spec:        HPI-B.01.01
 * Function:    saHpiSensorEventMasksSet
 * Description:   
 *   Call saHpiSensorEventMasksSet passing in a bad ResourceID.
 *   Expected return: SA_ERR_HPI_INVALID_RESOURCE.
 * Line:        P29-44:P29-46
 */
#include <stdio.h>
#include "saf_test.h"

int Test_Rdr(SaHpiSessionIdT session,
	     SaHpiResourceIdT resourceId, SaHpiRdrT rdr)
{
	SaErrorT status;
	int retval = SAF_TEST_NOTSUPPORT;
	SaHpiSensorNumT s_num = 0;
	SaHpiEventStateT AssertEventMask = 0x0000;
	SaHpiEventStateT DeassertEventMask = 0x0000;

	if (rdr.RdrType == SAHPI_SENSOR_RDR) {
		s_num = rdr.RdrTypeUnion.SensorRec.Num;
		//
		//  Call saHpiSensorEventMasksSet passing in a bad ResourceId
		//
		status = saHpiSensorEventMasksSet(session,
						  INVALID_RESOURCE_ID,
						  s_num,
						  SAHPI_SENS_ADD_EVENTS_TO_MASKS,
						  AssertEventMask,
						  DeassertEventMask);
		if (status != SA_ERR_HPI_INVALID_RESOURCE) {
			e_print(saHpiSensorEventMasksSet,
				SA_ERR_HPI_INVALID_RESOURCE, status);
			retval = SAF_TEST_FAIL;
		} else
			retval = SAF_TEST_PASS;
	}

	return (retval);
}

int Test_Resource(SaHpiSessionIdT session,
		  SaHpiRptEntryT report, callback2_t func)
{
	int retval = SAF_TEST_UNKNOWN;

	if (report.ResourceCapabilities & SAHPI_CAPABILITY_SENSOR)
		retval = do_resource(session, report, func);
	else			//Resource Does not support Sensors
		retval = SAF_TEST_NOTSUPPORT;
	return (retval);
}

/**********************************************************
*   Main Function
*      takes no arguments
*      
*       returns: SAF_TEST_PASS when successfull
*                SAF_TEST_FAIL when an unexpected error occurs
*************************************************************/
int main(int argc, char **argv)
{
	int retval = SAF_TEST_UNKNOWN;

	retval = process_all_domains(Test_Resource, Test_Rdr, NULL);

	return (retval);
}
