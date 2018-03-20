
typedef enum 
{
  ACK_dont_care,
  ACK_requested
}ACK_TYPE;

typedef enum
{
  ADDR_individual,
  ADDR_group
}ADDR_TYPE;

typedef uint16_t ADDRESS;

typedef enum
{
  FRAME_Stardand,
  FRAME_EXTEND
}FRAME_FORMAT;

typedef uint8_t* LSDU;

typedef enum
{
  PRIO_SYSTEM,
  PRIO_NORMAL,
  PRIO_URGENT,
  PRIO_LOW
}PRIORITY;

typedef enum
{
  OK,
  NOT_OK
}STATUS;



/*
ack_request:
This parameter shall be used to indicate whether a Layer-2 acknowledge is mandatory or optional.
address_type:
This parameter shall be used to indicate whether the Destination Address is an Individual Address or a Group Address.
destination_address:
This parameter shall be used to indicate the Destination Address of the Frame to be transmitted; it shall be either an Individual Address or a Group Address.
frame_format:
This parameter shall be used to indicate whether the Frame to be transmitted shall be a standard Frame or an extended Frame.
lsdu:
This parameter shall be used to contain the user data to be transferred by Layer-2.
octet_count:
This parameter shall be used to indicate the length information of the requested Frame.
priority:
This parameter shall be used to indicate the priority that shall be used to the transmit the requested Frame; it shall be “system”, “urgent”, “normal” or “low”.
source_address
Individual Address of the device that requests the L_Data-service.
*/
L_Data_req(ACK_TYPE ack_request, ADDR_TYPE address_type, ADDRESS destination_address, 
              FRAME_FORMAT frame_format, LSDU lsdu, uint16_t octet_count, PRIORITY priority, ADDRESS source_address)
{
  
}

/*
address_type:
This parameter shall indicate whether destination_address is an Individual Address or a Group Address.
destination_address:
This parameter shall be used to indicate the Destination Address of the requested Frame; it shall either be an Individual Address or a Group Address.
frame_format:
This parameter shall be used to indicate whether the transmitted Frame is a standard Frame or an extended Frame.
octet_count:
This parameter shall be used to indicate the length information of the transmitted Frame.
priority:
This parameter shall be used to indicate the priority that is used to transmit the requested Frame; it shall be “system”, “urgent”, “normal” or “low”.
source_address
This parameter shall be used to indicate the Source Address of the requested Frame; it shall be the Individual Address of the device that requests the service primitive.
lsdu:
This parameter shall be the user data transferred by Layer-2.
l_status:
ok: this value of this parameter shall be used to indicate that the transmission of the LSDU has been successful
not_ok: this value of this parameter shall be used to indicate that the transmission of the LSDU did not succeed
*/
L_Data_con(ADDR_TYPE address_type, ADDRESS destination_address, 
              FRAME_FORMAT frame_format, LSDU lsdu, uint16_t octet_count, PRIORITY priority, ADDRESS source_address, STATUS l_status)
{
  
}


/*
ack_request:
This parameter shall be used to indicate whether a Layer-2 acknowledge is mandatory or optional.
address_type:
This parameter shall indicate whether destination_address is an Individual Address or a Group Address.
destination_address:
This parameter shall be used to indicate the Destination Address of this Frame. It shall be the Individual Address of this device or a Group Address of this device.
frame_format:
This parameter shall be used to indicate whether the received Frame is a standard Frame or an extended Frame.
lsdu:
This parameter shall be used to contain the user data that is received by Layer-2.
octet_count:
This parameter shall be used to indicate the length information of the received Frame.
priority:
This parameter shall be used to indicate the priority of the received Frame; it shall be “system”, “urgent”, “normal” or “low”.
source_address:
This parameter shall be used to indicate the Source Address of the received Frame; it shall be the Individual Address of the device that has transmitted the Frame.
*/
L_Data_ind(ACK_TYPE ack_request, ADDR_TYPE address_type, ADDRESS destination_address, 
              FRAME_FORMAT frame_format, LSDU lsdu, uint16_t octet_count, PRIORITY priority, ADDRESS source_address)
{
  
}

/*
ack_request:
This parameter shall be used to indicate whether a Layer-2 acknowledge is mandatory or optional.
address_type:
This parameter shall be set to “Group Address”
destination_address:
This parameter shall be used to indicate the Destination Address of the Frame to be transmitted; it shall be the system broadcast address 0000h
frame_format:
This parameter shall be used to indicate whether the Frame to be transmitted shall be a standard Frame or an extended Frame.
lsdu:
This parameter shall be used to contain the user data to be transferred by Layer-2.
octet_count:
This parameter shall be used to indicate the length information of the requested Frame.
priority:
This parameter shall be used to indicate the priority that shall be used to the transmit the requested Frame; it shall be “system”, “urgent”, “normal” or “low”.
*/
L_SystemBroadcast.req(ACK_TYPE ack_request, ADDR_TYPE address_type, ADDRESS destination_address, 
              FRAME_FORMAT frame_format, LSDU lsdu, uint16_t octet_count, PRIORITY priority)
{
  
}

/*
address_type:
This parameter shall be set to “Group Address”.
destination_address:
This parameter shall be used to indicate the Destination Address of the transmitted Frame; it shall be the system broadcast address 0000h
frame_format:
This parameter shall be used to indicate whether the transmitted Frame is a standard Frame or an extended Frame.
octet_count:
This parameter shall be used to indicate the length information of the transmitted Frame.
priority:
This parameter shall be used to indicate the priority that is used to transmit the requested Frame; it shall be “system”, “urgent”, “normal” or “low”.
source_address
This parameter shall be used to indicate the Source Address of the requested Frame; it shall be the Individual Address of the device that requests the service primitive.
lsdu:
This parameter shall be the user data transferred by Layer-2
l_status:
ok: this value of this parameter shall be used to indicate that the transmission of the LSDU has been successful
not_ok: this value of this parameter shall be used to indicate that the transmission of the LSDU did not succeed  
  */
L_SystemBroadcast_con(ADDR_TYPE address_type, ADDRESS destination_address, 
              FRAME_FORMAT frame_format, LSDU lsdu, uint16_t octet_count, PRIORITY priority, ADDRESS source_address, STATUS l_status)
{
  
}
/*
ack_request:
This parameter shall be used to indicate whether a Layer-2 acknowledge is mandatory or optional.
address_type:
This parameter shall be set to “Group Address”.
destination_address:
This parameter shall be used to indicate the Destination Address of the received Frame; it shall be the system broadcast address 0000h
frame_format:
This parameter shall be used to indicate whether the received Frame is a standard Frame or an extended Frame.
lsdu:
This parameter shall be used to contain the user data that is received by Layer-2.
octet_count:
This parameter shall be used to indicate the length information of the received Frame.
priority:
This parameter shall be used to indicate the priority of the received Frame; it shall be “system”, “urgent”, “normal” or “low”.
source_address:
This parameter shall be used to indicate the Source Address of the received Frame; it shall be the Individual Address of the device that has transmitted the Frame.

*/
L_SystemBroadcast.ind(ACK_TYPE ack_request, ADDR_TYPE address_type, ADDRESS destination_address, 
              FRAME_FORMAT frame_format, LSDU lsdu, uint16_t octet_count, PRIORITY priority, ADDRESS source_address)
{
  
}

/*
destination:
a poll group address
no_of_expected_poll_data:
number of expected poll data cycles
*/
L_Poll_Data.req(ADDRESS destination, no_of_expected_poll_data)

/*
poll_data_sequence:
sequence of Poll_Data octets and FILL octets
l_status:
ok: valid poll_data_sequence
not_ok: invalid poll_data_sequence, i.e. collision occurred during transmission of a FILL, or at least one Poll_Data not correct
*/
L_Poll_Data.con(l_status, poll_data_sequence)

/*
Poll_Data:
The value of the Poll_Data octet to be transmitted in the L_Poll_Data_Response Frame.
L_Poll_Update.con() Indicates that the L_Poll_Update.req has been accepted by the local Layer-2.
*/
L_Poll_Update.req(Poll_Data)

/*
l_status:
information whether a Frame error, bit error or a parity error is detected in the received Frame. Additional information about the number of already received Frames may also be contained.
LPDU:
all octets of the received Frame
time_stamp:
timing information, when the start bit of the Frame was received
*/
L_Busmon.ind(l_status, time_stamp, LPDU)
{
}

/*
a Frame is received that contains the Individual Address of the local Layer-2 as Source Address.
*/
L_Service_Information.ind() 