#ifndef __KNX_IC__
#define __KNX_IC__

/**
 *
 * Services from Host-Controller.
 *
 */
/* INTERNAL COMMANDS ?DEVICE SPECIFIC */
#define U_RESET_REQ             ((uint8_t)0x01)
#define U_STATE_REQ             ((uint8_t)0x02)

#if KNX_BUS_INTERFACE == KNX_BIF_NCN5120
#define U_SETBUSY_REQ           ((uint8_t)0x03)
#define U_QUITBUSY_REQ          ((uint8_t)0x04)
#endif /* KNX_BUS_INTERFACE */

#define U_BUSMON_REQ            ((uint8_t)0x05)

#if KNX_BUS_INTERFACE == KNX_BIF_TPUART_2
#define U_PRODUCTID_REQUEST     ((uint8_t)0x14)
#define U_ACTIVATEBUSYMODE_REQ  ((uint8_t)0x15)
#define U_RESETBUSYMODE_REQ     ((uint8_t)0x16)
#define U_MXRSTCNT_REQ          ((uint8_t)0x18)
#define U_ACTIVATECRC_REQ       ((uint8_t)0x19)
#define U_SETADDRESS_REQ        ((uint8_t)0x1C)
#endif /* KNX_BUS_INTERFACE */

#if KNX_BUS_INTERFACE == KNX_BIF_NCN5120
#define U_L_DATAOFFSET_REQ      ((uint8_t)0x08) /* 08 - 0C */
#define U_SYSTEMSTAT_REQ        ((uint8_t)0x0D)
#define U_STOPMODE_REQ          ((uint8_t)0x0E)
#define U_EXITSTOPMODE_REQ      ((uint8_t)0x0F)
#endif /* KNX_BUS_INTERFACE */

#define U_ACKN_REQ              ((uint8_t)0x10) /* 10 - 17 */

#if KNX_BUS_INTERFACE == KNX_BIF_NCN5120
#define U_CONFIGURE_REQ         ((uint8_t)0x18) /* 18 - 1F */
#define U_INTREGWR_REQ          ((uint8_t)0x28) /* 28 - 2B */
#define U_INTREGRD_REQ          ((uint8_t)0x38) /* 38 - 3B */
#endif /* KNX_BUS_INTERFACE */

#define U_POLLINGSTATE_REQ      ((uint8_t)0xE0) /* E0 - EE */


/* KNX TRANSMIT DATA COMMANDS */
#define U_L_DATASTART_REQ       ((uint8_t)0x80)
#define U_L_DATACONT_REQ        ((uint8_t)0x80) /* 81 - BF */
#define U_L_DATAEND_REQ         ((uint8_t)0x40) /* 47 - 7F */

#if KNX_BUS_INTERFACE == KNX_BIF_NCN5120 /* TODO: �berpr�fen!!!*/
#define U_SETADDRESS_REQ        ((uint8_t)0xF1)
#define U_SETREPETITION_REQ     ((uint8_t)0xF2)
#endif


/**
 *
 * Services to Host-Controller.
 *
 */
#define L_ACKN_IND              ((uint8_t)0x00)

#define U_CONFIGURE_IND         ((uint8_t)0x01)

#define U_RESET_IND             ((uint8_t)0x03)
#define U_STATE_IND             ((uint8_t)0x07)
#define L_DATA_CON              ((uint8_t)0x0b)
#define L_DATA_EXTENDED_IND     ((uint8_t)0x10)

#define U_FRAMESTATE_IND        ((uint8_t)0x13)
#define U_STOPMODE_IND          ((uint8_t)0x2b)
#define U_SYSTEMSTAT_IND        ((uint8_t)0x4b)

#define L_DATA_STANDARD_IND     ((uint8_t)0x90)

#define U_FRAMEEND_IND          ((uint8_t)0xcb)

#define L_POLL_DATA_IND         ((uint8_t)0xf0)

/*
** Global Types.
*/
typedef enum tagKnxLL_StateType {
    KNX_LL_STATE_IDLE,
    KNX_LL_STATE_RECEIVING,
    KNX_LL_STATE_SENDING,
    KNX_LL_STATE_AWAITING_RESPONSE_LOCAL,
    KNX_LL_STATE_AWAITING_RESPONSE_TRANSMISSION,
    KNX_LL_STATE_AWAITING_RECEIPTION,
    KNX_LL_STATE_TIMED_OUT
} KnxLL_StateType;


/**
 *  Local unconfirmed services.
 */
void U_ActivateBusmon_req(void);

#if KNX_BUS_INTERFACE == KNX_BIF_TPUART_2
void U_ActivateBusyMode_req(void);
void U_ResetBusyMode_req(void);
void U_SetRepetition_req(uint8_t rst);
void U_ActivateCRC_req(void);
#endif /* KNX_BUS_INTERFACE */

#if KNX_BUS_INTERFACE == KNX_BIF_TPUART_2 || KNX_BUS_INTERFACE == KNX_BIF_NCN5120
void U_SetRepetition_req(uint8_t rst);
#endif /* KNX_BUS_INTERFACE */

#if KNX_BUS_INTERFACE == KNX_BIF_NCN5120

#endif /* KNX_BUS_INTERFACE */

void U_Ackn_req(uint8_t what);

/**
 *  Global Function-like Macros.
 */



/**
 *  Global Functions.
 */
void KnxLL_FeedReceiver(uint8_t byte);
void KnxLL_Init(void);
void KnxLL_Task(void);
void KnxLL_WriteFrame(uint8_t const * frame, uint8_t length);
boolean KnxLL_IsBusy(void);
KnxLL_StateType KnxLL_GetState(void);
void KnxLL_SetState(KnxLL_StateType state);
void KnxLL_BusyWait(void);
boolean KnxLL_IsConfirmed(void);
void KnxLL_TimeoutCB(void);
uint8_t KnxLL_Checksum(uint8_t const * frame, uint8_t length);

/**
 *  Local confirmed services.
 */

void U_Reset_req(void);
void U_State_req(void);

#if KNX_BUS_INTERFACE == KNX_BIF_TPUART_2
void U_ProductID_req(void);
#endif /* KNX_BUS_INTERFACE */

#if KNX_BUS_INTERFACE == KNX_BIF_NCN5120
void U_SetAddress_req(uint16_t address);
#endif /* KNX_BUS_INTERFACE */

#if KNX_BUS_INTERFACE == KNX_BIF_NCN5120

#endif /* KNX_BUS_INTERFACE */

#endif
