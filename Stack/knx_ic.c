#include "stateeng.h"

static StateMachine KnxIcStateMachine;
#define STATE_TO(State)  STATE_TRANS(&KnxIcStateMachine, State)
// millisecond
void Tmr_SetTime(uint16_t time)
{
  
}

void KnxIcReset(void)
{
  while (RESET_PIN == LOW);
  
}

void KnxIcWaitCtrlField(tEvent e)
{
  uint8_t Data;
  
  switch (Data)
  {

  case U_CONFIGURE_IND:
    break;
       
  // control  
  case U_RESET_IND:
    break;          
  case U_STATE_IND:
    break;          
  case L_DATA_CON:
    break;           
       
  
  
    // layer2
  case L_DATA_STANDARD_IND:
    break;  
  case L_DATA_EXTENDED_IND:
    break;   
  case L_POLL_DATA_IND:
    break;   
      
       
   
  }
    
}

void KnxIcWaitData(tEvent e)
{
  switch(e)
  {
  case E_ENTRY:
    // wait 3
    Tmr_SetTime(3);
    break;
    
  case E_TIMEOUT:
    // check reset pin
    // if (ResetPin == HIGH)
    {
      STATE_TO(
    }
    break;
    
  case E_EXIT:
    break;
  }  
}

void KnxIcResetPin(tEvent e)
{
  switch(e)
  {
  case E_ENTRY:
    //U_Reset_req();
    Tmr_SetTime(50);
    break;
    
  case E_TIMEOUT:
    // check reset pin
    // if (ResetPin == HIGH)
    {
      STATE_TO(
    }
    break;
    
  case E_EXIT:
    break;
  }
}

void KnxIcReset(tEvent e)
{
  switch(e)
  {
  case E_ENTRY:
    // wait 50 ms after reset pin is high
    Tmr_SetTime(50);
    break;
    
  case E_TIMEOUT:
    U_Reset_req();
    
    break;
    
  case E_EXIT:
    break;
  }
}


/*!
 *
 * Local Functions.
 *
 */

/**
 * Issues an internal Command, i.e. related to the interface IC, not EIB.
 *
 * @param frame Octets to be send.
 * @param length Number of octets.
 * @param desiredState Desired state to enter (in case of confirmed commands, we need to wait for an answer).
 *
 * @return boolean
 */
STATIC boolean KnxLL_InternalCommand(uint8_t const * frame, uint8_t length, KnxLL_StateType desiredState)
{
    boolean result;

    PORT_LOCK_TASK_LEVEL();
    if (KnxLL_GetState() != KNX_LL_STATE_IDLE) {
        PORT_UNLOCK_TASK_LEVEL();
        return FALSE;
    }
    KnxLL_SetState(desiredState);
    result = Port_Serial_Write(frame, (uint32_t)length);
    PORT_UNLOCK_TASK_LEVEL();
    TMR_START_DL_TIMER();
    return result;
}

STATIC boolean KnxLL_InternalCommandUnconfirmed(uint8_t const * frame, uint8_t length)
{
    return KnxLL_InternalCommand(frame, length, KNX_LL_STATE_IDLE);
}

STATIC boolean KnxLL_InternalCommandConfirmed(uint8_t const * frame, uint8_t length)
{
    return KnxLL_InternalCommand(frame, length, KNX_LL_STATE_AWAITING_RESPONSE_LOCAL);
}

STATIC void KnxLL_Expect(uint8_t service, uint8_t mask, uint8_t byteCount)
{
    KnxLL_Expectation.ExpectedService = service;
    KnxLL_Expectation.ExpectedMask = mask;
    KnxLL_Expectation.ExpectedByteCount = byteCount;
}

uint8_t KnxLL_Checksum(uint8_t const * frame, uint8_t length)
{
    uint8_t checksum = (uint8_t)0xff;
    uint8_t idx;

    for (idx = (uint8_t)0; idx < length; ++idx) {
        checksum ^= frame[idx];
    }

    return checksum;
}

void KnxLL_WriteFrame(uint8_t const * frame, uint8_t length)

{
    uint8_t idx;
    uint8_t checksum;
    char buffer[128];

    KNX_ASSERT_MODULE_IS_INITIALIZED(UART_BIF, KNX_SERVICE_LL_WRITE_FRAME);

    checksum = KnxLL_Checksum(frame, length);
    buffer[0] = U_L_DATASTART_REQ;
    buffer[1] = frame[0];
    for (idx = (uint8_t)2; idx < (length << 1); idx += (uint8_t)2) {
        buffer[idx] = U_L_DATACONT_REQ | (idx >> 1);
        buffer[idx + 1] = frame[idx >> 1];
    }
    buffer[idx] = U_L_DATAEND_REQ | (idx >> 1);
    buffer[idx + 1] = checksum;
    (void)Port_Serial_Write((uint8_t *)buffer, (uint32_t)(idx + (uint8_t)2));
    KnxLL_Expect((uint8_t)0x00, (uint8_t)0x00, length + (uint8_t)1);
    KnxLL_SetState(KNX_LL_STATE_AWAITING_RESPONSE_TRANSMISSION);
    KnxLL_ReceiverIndex = (uint8_t)0x00;
    TMR_START_DL_TIMER();
}


/**
 *
 *  Local unconfirmed services.
 *
 */
void U_ActivateBusmon_req(void)
{
    DBG_PRINTLN("U_ActivateBusmon_req");
    KnxLL_Buffer[0] = U_BUSMON_REQ;
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)1);
}

#if KNX_BUS_INTERFACE == KNX_BIF_NCN5120
void U_ActivateBusyMode_req(void)
{
    DBG_PRINTLN("U_ActivateBusyMode_req");
    KnxLL_Buffer[0] = U_SETBUSY_REQ;
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)1);
}

void U_ResetBusyMode_req(void)
{
    DBG_PRINTLN("U_ResetBusyMode_req");
    KnxLL_Buffer[0] = U_QUITBUSY_REQ;
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)1);
}
#endif /* KNX_BUS_INTERFACE */

#if KNX_BUS_INTERFACE == KNX_BIF_TPUART_2
void U_ActivateBusyMode_req(void)
{
    DBG_PRINTLN("U_ActivateBusyMode_req");
    KnxLL_Buffer[0] = U_ACTIVATEBUSYMODE_REQ;
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)1);
}


void U_ResetBusyMode_req(void)
{
    DBG_PRINTLN("U_ResetBusyMode_req");
    KnxLL_Buffer[0] = U_RESETBUSYMODE_REQ;
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)1);
}

void U_SetRepetition_req(uint8_t rst)
{
    DBG_PRINTLN("U_SetRepetition_req");
    KnxLL_Buffer[0] = U_MXRSTCNT_REQ;
    KnxLL_Buffer[1] = rst;
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)2);
}

void U_ActivateCRC_req(void)
{
    DBG_PRINTLN("U_ActivateCRC_req");
    KnxLL_Buffer[0] = U_ACTIVATECRC_REQ;
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)1);
}

void U_SetAddress_req(uint16_t address)
{
    DBG_PRINTLN("U_SetAddress_req");
    KnxLL_Buffer[0] = U_SETADDRESS_REQ;
    KnxLL_Buffer[1] = KNX_HIBYTE(address);
    KnxLL_Buffer[2] = KNX_LOBYTE(address);
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)3);
}
#endif /* KNX_BUS_INTERFACE */

#if KNX_BUS_INTERFACE == KNX_BIF_NCN5120
void U_SetRepetition_req(uint8_t rst)
{
    DBG_PRINTLN("U_SetRepetition_req");
    KnxLL_Buffer[0] = U_SETREPETITION_REQ;
    KnxLL_Buffer[1] = rst;
    KnxLL_Buffer[2] = (uint8_t)0x00; /* Dummy */
    KnxLL_Buffer[3] = (uint8_t)0x00; /* Dummy */
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)4);
}
#endif /* KNX_BUS_INTERFACE */

void U_Ackn_req(uint8_t what)
{

//    DBG_PRINTLN("U_Ackn_req");
    KnxLL_Buffer[0] = U_ACKN_REQ | (what & 0x07);
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)1);
}

/**
 *
 *  Local confirmed services.
 *
 */

void U_Reset_req(void)
{
    DBG_PRINTLN("U_Reset_req");
    KnxLL_Buffer[0] = U_RESET_REQ;
    (void)KnxLL_InternalCommandConfirmed(KnxLL_Buffer, (uint8_t)1);
    KnxLL_Expect(U_RESET_IND, (uint8_t)0xff, (uint8_t)1);
}

void U_State_req(void)
{
    DBG_PRINTLN("U_State_req");
    KnxLL_Buffer[0] = U_STATE_REQ;
    (void)KnxLL_InternalCommandConfirmed(KnxLL_Buffer, (uint8_t)1);
    KnxLL_Expect(U_STATE_IND, (uint8_t)0x07, (uint8_t)1);
}

#if KNX_BUS_INTERFACE == KNX_BIF_TPUART_2
void U_ProductID_req(void)
{
    DBG_PRINTLN("U_ProductID_req");
    KnxLL_Buffer[0] = U_PRODUCTID_REQUEST;
    (void)KnxLL_InternalCommandConfirmed(KnxLL_Buffer, (uint8_t)1);
    KnxLL_Expect((uint8_t)0x00, (uint8_t)0x00, (uint8_t)1);    /* Expect any single byte value. */
}
#endif /* KNX_BUS_INTERFACE */

#if KNX_BUS_INTERFACE == KNX_BIF_NCN5120
void U_SetAddress_req(uint16_t address) /* NB: TPUART2's SetAddress is unconfirmed! */
{
    DBG_PRINTLN("U_SetAddress_req");
    KnxLL_Buffer[0] = U_SETADDRESS_REQ;
    KnxLL_Buffer[1] = KNX_HIBYTE(address);
    KnxLL_Buffer[2] = KNX_LOBYTE(address);
    KnxLL_Buffer[3] = (uint8_t)0x00; /* Dummy */
    (void)KnxLL_InternalCommandConfirmed(KnxLL_Buffer, (uint8_t)4);
    KnxLL_Expect(U_CONFIGURE_IND, (uint8_t)0x83, (uint8_t)1);
}
#endif /* KNX_BUS_INTERFACE */

/**
 *  Transmission services.
 */


#if 0
void U_SystemState_req(void)
{
    DBG_PRINTLN("U_SystemState_req");
    KnxLL_Buffer[0] = U_SYSTEMSTAT_REQ;
    (void)KnxLL_InternalCommandConfirmed(KnxLL_Buffer, (uint8_t)2);
    KnxLL_Expect(U_SYSTEMSTAT_IND, (uint8_t)0xff, (uint8_t)2);
}

void U_StopMode_req(void)
{
    DBG_PRINTLN("U_StopMode_req");
    KnxLL_Buffer[0] = U_STOPMODE_REQ;
    (void)KnxLL_InternalCommandConfirmed(KnxLL_Buffer, (uint8_t)1);
    KnxLL_Expect(U_STOPMODE_IND, (uint8_t)0xff, (uint8_t)1);
}

void U_ExitStopMode_req(void)
{
    DBG_PRINTLN("U_ExitStopMode_req");
    KnxLL_Buffer[0] = U_EXITSTOPMODE_REQ;
    (void)KnxLL_InternalCommandConfirmed(KnxLL_Buffer, (uint8_t)1);
    KnxLL_Expect(U_RESET_IND, (uint8_t)0xff, (uint8_t)1);
}

void U_Configure_req(uint8_t conf)
{
    DBG_PRINTLN("U_Configure_req");
    KnxLL_Buffer[0] = U_CONFIGURE_REQ | (conf & 0x07);
    (void)KnxLL_InternalCommandConfirmed(KnxLL_Buffer, (uint8_t)1);
    KnxLL_Expect(U_CONFIGURE_IND, (uint8_t)0xff, (uint8_t)1);
}

void U_IntRegWr_req(uint8_t addr, uint8_t value)
{
    DBG_PRINTLN("U_IntRegWr_req");
    KnxLL_Buffer[0] = U_INTREGWR_REQ | (addr & 0x03);
    KnxLL_Buffer[1] = value;
    (void)KnxLL_InternalCommandUnconfirmed(KnxLL_Buffer, (uint8_t)2);
}

void U_IntRegRd_req(uint8_t addr)
{
    DBG_PRINTLN("U_IntRegRd_req");
    KnxLL_Buffer[0] = U_INTREGRD_REQ;
    (void)KnxLL_InternalCommandConfirmed(KnxLL_Buffer, (uint8_t)1);
    KnxLL_Expect((uint8_t)0x00, (uint8_t)0x00, (uint8_t)1);
}
#endif
