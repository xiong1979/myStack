
/******************************************************************************/
/*! \file
 * $Id: StateEng.h 2300 2016-8-12 10:10:20Z ryan.zq.xiong@philips.com $
 * $Revision: 2300 $
 * $Date: 2016-8-12 18:10:20  $
 * $Author: ryan.zq.xiong@philips.com $
 *
 * \brief the state machine for GPRS
 *
 * \par Owner
 *
 * \par Department
 *      Outdoor Venture
 *
 * \par Copyright
 *      Philips Company Confidential.
 *   \n Copyright (C) 2014 Koninklijke Philips Electronics N.V.
 *   \n All rights reserved.
 */
/******************************************************************************/

#ifndef _STATE_ENG_H
#define _STATE_ENG_H

/******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/

#include "Event.h"


typedef void (*FS_STATE)(tEvent e);
typedef void (*FS_ACTION)(tEvent e);

typedef struct __state_machine
{
	FS_STATE		State;
	FS_STATE		preState;
	FS_STATE		prePreState;
}StateMachine;


/******************************************************************************/
/* PUBLIC FUNCTION PROTOTYPES                                                */
/******************************************************************************/

#define NULL_ACTION(e)

#define  STATE_TRANS(StateMachine, DstState) \
		do \
		{ \
			StateMachine.State(EVT_EXIT); \
			StateMachine.prePreState = StateMachine.preState; \
			StateMachine.preState = StateMachine.State; \
			StateMachine.State = DstState; \
			StateMachine.State(EVT_ENTRY); \
		}while(0)

#define  STATE_INIT(StateMachine, InitState)	\
		do \
		{ \
			StateMachine.prePreState = InitState; \
			StateMachine.preState = InitState; \
			StateMachine.State = InitState; \
			StateMachine.State(EVT_ENTRY); \
		}while(0)
			
#define  STATE_ACTION(StateMachine, e)                  StateMachine.State(e)
#define  STATE_IS(StateMachine, state)                  ((state) == StateMachine.State)	
#define  STATE_PRE_IS(StateMachine, state)              ((state) == StateMachine.preState)
			
#define  DispatchEvent(StateMachine, e)                 STATE_ACTION(StateMachine, e)
#define  PostEvent(StateMachine, e)                     DispatchEvent(StateMachine, e)


#endif

/*! @} */


