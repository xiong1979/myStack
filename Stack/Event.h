

/******************************************************************************/
/*! \file
 * $Id: Event.h 2300 2016-8-12 10:10:20Z ryan.zq.xiong@philips.com $
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

#ifndef _EVENT_H
#define _EVENT_H

/******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/

typedef enum __eventid
{
  //  inner events  
  E_ENTRY,
  
  // user events begin
  EVT_GET_RESP,
  
  E_TIMEOUT,
  
  EVT_GPRS_RESTART,
  EVT_GPRS_DEACT,
  EVT_GPRS_INITED,
  
  EVT_SOCK_SEND_DATA,
  
  EVT_SOCK_REQUEST_CONNECT,
  
  EVT_SOCK_CONNECTED,  
  EVT_SOCK_DISCONNECTED,
  
  EVT_SEND_DATA,
  EVT_SEND_ACK,
  
  EVT_PARAM_CHANGED,
  EVT_PARAM_RESPONSE,
  EVT_SEND_OK,
  EVT_GET_PACKET, 
  EVT_SEND_TIME_OUT,
  EVT_GET_RESPONSE, 
  
  EVT_APP_TIMEOUT,
  EVT_APP_ACK,
  EVT_APP_DIM,
  EVT_APP_ALARM,
  
  EVT_UP_DATA,
  EVT_UP_FINISH,
  
  // user events end

  //  inner events
  E_EXIT,
 
}tEvent;

/*
typedef struct __event
{
  tEventID ID;  
}tEvent;
*/
/******************************************************************************/
/* PUBLIC FUNCTION PROTOTYPES                                                */
/******************************************************************************/




#endif

/*! @} */

