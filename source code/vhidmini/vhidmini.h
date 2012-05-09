/*
<파워해커 라이센스>
현재 공개하는 소스는 EULA (End User License Agreement) 라이센스와 거의 비슷한
연구용으로만 사용하실 수 있으며 그 어떤 용도의 악용을 허용치 않습니다.

배포처: 파워해커(powerhacker.net)
제작자: AmesianX
*/

/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
    KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
    PURPOSE.

Module Name:


Abstract:


Author:

    Kumar Rajeev  

Environment:

    kernel mode only

Notes:


Revision History:


--*/
#ifndef _VHIDMINI_

#define _VHIDMINI_

#include <wdm.h>
#include <stdio.h>
#include "hidport.h"
#include "common.h"   //for control code definitions

#if DBG
#define DebugPrint(_x_)     { DbgPrint ("VHIDMINI:"); DbgPrint _x_; }
#else 
#define DebugPrint(_x_)     
#endif

#define VHID_POOL_TAG (ULONG) 'diHV'
#define VHID_HARDWARE_IDS    L"HID\\MyVirtualHidDevice\0\0"
#define VHID_HARDWARE_IDS_LENGTH sizeof (VHID_HARDWARE_IDS)

#define CONTROL_FEATURE_REPORT_ID       0x01
// #define INPUT_MOUSE_REPORT_BYTES     0x03    // 1 Bytes X-Y Relative Coords Mouse 0x03(Normal)
#define INPUT_MOUSE_REPORT_BYTES        0x05    // 2 Bytes X-Y Absolute Coords Mouse 0x05(Touch)
#define INPUT_KEYBOARD_REPORT_BYTES     0x08    // 

#define KEYBOARD    0xFF
#define MOUSE       0xEE

typedef UCHAR HID_REPORT_DESCRIPTOR, *PHID_REPORT_DESCRIPTOR;


/*
//
// This is the default report descriptor for the virtual Hid device returned
// by the mini driver in response to IOCTL_HID_GET_REPORT_DESCRIPTOR if the
// driver fails to read the report descriptor from registry. 
//
HID_REPORT_DESCRIPTOR           DefaultReportDescriptor[] = {
    0x06,0x00, 0xFF,                   // USAGE_PAGE (Vender Defined Usage Page)     
    0x09,0x01,                         // USAGE (Vendor Usage 0x01)      
    0xA1,0x01,                         // COLLECTION (Application)        
    0x85,CONTROL_FEATURE_REPORT_ID,    // REPORT_ID (1)                      
    0x09,0x01,                         // USAGE (Vendor Usage 0x01)              
    0x15,0x00,                         // LOGICAL_MINIMUM(0)                   
    0x26,0xff, 0x00,                   // LOGICAL_MAXIMUM(255)               
    0x75,0x08,                         // REPORT_SIZE (0x08)                     
    0x95,0x01,                         // REPORT_COUNT (0x01)                    
    0xB1,0x00,                         // FEATURE (Data,Ary,Abs)
    0x09,0x01,                         // USAGE (Vendor Usage 0x01)              
    0x75,0x08,                         // REPORT_SIZE (0x08)                     
    0x95,INPUT_REPORT_BYTES,           // REPORT_COUNT (0x01)                    
    0x81,0x00,                         // INPUT (Data,Ary,Abs)
    0xC0                               // END_COLLECTION                       
};
*/


/* Key Name    PS/2 Set 1 Make*    HID Usage ID */
unsigned char PS2toHID_KeyMapTable[] = {
/*	DO NOT USE	0x00	*/	0x00,
/*	Escape	0x01	*/	0x29,
/*	1 !	0x02	*/	0x1E,
/*	2 @	0x03	*/	0x1F,
/*	3 #	0x04	*/	0x20,
/*	4 $	0x05	*/	0x21,
/*	5 . 0x06	*/	0x22,
/*	6 ^	0x07	*/	0x23,
/*	7 &	0x08	*/	0x24,
/*	8 *	0x09	*/	0x25,
/*	9 (	0x0A	*/	0x26,
/*	0 )	0x0B	*/	0x27,
/*	- _	0x0C	*/	0x2D,
/*	= +	0x0D	*/	0x2E,
/*	Backspace	0x0E	*/	0x2A,
/*	Tab	0x0F	*/	0x2B,
/*	q Q	0x10	*/	0x14,
/*	w W	0x11	*/	0x1A,
/*	e E	0x12	*/	0x08,
/*	r R	0x13	*/	0x15,
/*	t T	0x14	*/	0x17,
/*	y Y	0x15	*/	0x1C,
/*	u U	0x16	*/	0x18,
/*	i I	0x17	*/	0x0C,
/*	o O	0x18	*/	0x12,
/*	p P	0x19	*/	0x13,
/*	[ {	0x1A	*/	0x2F,
/*	] }	0x1B	*/	0x30,
/*	Return	0x1C	*/	0x28,
/*	Left Control	0x1D	*/	0xE0,
/*	a A	0x1E	*/	0x04,
/*	s S	0x1F	*/	0x16,
/*	d D	0x20	*/	0x07,
/*	f F	0x21	*/	0x09,
/*	g G	0x22	*/	0x0A,
/*	h H	0x23	*/	0x0B,
/*	j J	0x24	*/	0x0D,
/*	k K	0x25	*/	0x0E,
/*	l L	0x26	*/	0x0F,
/*	; :	0x27	*/	0x33,
/*	' "	0x28	*/	0x34,
/*	` ~	0x29	*/	0x35,
/*	Left Shift	0x2A	*/	0xE1,
/*	\ |	0x2B	*/	0x31,
/*	Europe 1 (Note	0x2B	*/	0x32,
/*	z Z	0x2C	*/	0x1D,
/*	x X	0x2D	*/	0x1B,
/*	c C	0x2E	*/	0x06,
/*	v V	0x2F	*/	0x19,
/*	b B	0x30	*/	0x05,
/*	n N	0x31	*/	0x11,
/*	m M	0x32	*/	0x10,
/*	, <	0x33	*/	0x36,
/*	. >	0x34	*/	0x37,
/*	/ ?	0x35	*/	0x38,
/*	Right Shift	0x36	*/	0xE5,
/*	Keypad *	0x37	*/	0x55,
/*	Left Alt	0x38	*/	0xE2,
/*	Space	0x39	*/	0x2C,
/*	Caps Lock	0x3A	*/	0x39,
/*	F1	0x3B	*/	0x3A,
/*	F2	0x3C	*/	0x3B,
/*	F3	0x3D	*/	0x3C,
/*	F4	0x3E	*/	0x3D,
/*	F5	0x3F	*/	0x3E,
/*	F6	0x40	*/	0x3F,
/*	F7	0x41	*/	0x40,
/*	F8	0x42	*/	0x41,
/*	F9	0x43	*/	0x42,
/*	F10	0x44	*/	0x43,
/*	Num Lock	0x45	*/	0x53,
/*	Scroll Lock	0x46	*/	0x47,
/*	Keypad 7 Home	0x47	*/	0x5F,
/*	Keypad 8 Up	0x48	*/	0x60,
/*	Keypad 9 PageUp	0x49	*/	0x61,
/*	Keypad -	0x4A	*/	0x56,
/*	Keypad 4 Left	0x4B	*/	0x5C,
/*	Keypad 5	0x4C	*/	0x5D,
/*	Keypad 6 Right	0x4D	*/	0x5E,
/*	Keypad +	0x4E	*/	0x57,
/*	Keypad 1 End	0x4F	*/	0x59,
/*	Keypad 2 Down	0x50	*/	0x5A,
/*	Keypad 3 PageDn	0x51	*/	0x5B,
/*	Keypad 0 Insert	0x52	*/	0x62,
/*	Keypad . Delete	0x53	*/	0x63,
/*	UNASSIGNED	0x54	*/	0x00,
/*	UNASSIGNED	0x55	*/	0x00,
/*	Europe 2 (Note	0x56	*/	0x64,
/*	F11	0x57	*/	0x44,
/*	F12	0x58	*/	0x45,
/*	Keypad =	0x59	*/	0x67,
/*	UNASSIGNED	0x5A	*/	0x00,
/*	UNASSIGNED	0x5B	*/	0x00,
/*	Keyboard Int'l 6	0x5C	*/	0x8C,
/*	UNASSIGNED	0x5D	*/	0x00,
/*	UNASSIGNED	0x5E	*/	0x00,
/*	UNASSIGNED	0x5F	*/	0x00,
/*	DO NOT USE	0x60	*/	0x00,
/*	DO NOT USE	0x61	*/	0x00,
/*	UNASSIGNED	0x62	*/	0x00,
/*	UNASSIGNED	0x63	*/	0x00,
/*	F13	0x64	*/	0x68,
/*	F14	0x65	*/	0x69,
/*	F15	0x66	*/	0x6A,
/*	F16	0x67	*/	0x6B,
/*	F17	0x68	*/	0x6C,
/*	F18	0x69	*/	0x6D,
/*	F19	0x6A	*/	0x6E,
/*	F20	0x6B	*/	0x6F,
/*	F21	0x6C	*/	0x70,
/*	F22	0x6D	*/	0x71,
/*	F23	0x6E	*/	0x72,
/*	UNASSIGNED	0x6F	*/	0x00,
/*	Keyboard Intl'2	0x70	*/	0x88,
/*	UNASSIGNED	0x71	*/	0x00,
/*	UNASSIGNED	0x72	*/	0x00,
/*	Keyboard Int'l	0x73	*/	0x87,
/*	UNASSIGNED	0x74	*/	0x00,
/*	UNASSIGNED	0x75	*/	0x00,
/*	F24	0x76	*/	0x73,
/*	Keyboard Lang 4	0x77	*/	0x93,
/*	Keyboard Lang 3	0x78	*/	0x92,
/*	Keyboard Int'l4	0x79	*/	0x8A,
/*	DO NOT USE	0x7A	*/	0x00,
/*	Keyboard Int'l5	0x7B	*/	0x8B,
/*	DO NOT USE	0x7C	*/	0x00,
/*	Keyboard Int'l2	0x7D	*/	0x89,
/*	Keypad ,Brazilian Keypad	0x7E	*/	0x85,
/*	DO NOT USE	0x7F	*/	0x00 };


/* 1024x768 Absolute Coordinates Mouse */
/* Format: Total 6 Bytes Format */
/* 1 Bytes(ReportID) + 1 Bytes(Button-Bits + Padding) + 2 Bytes(X-Coord) + 2 Bytes(Y-Coord) */
/* Careful - if you don't use LOGICAL-PHYSICAL MIN-MAXIMUM pair, coordinates not recognized.. */
HID_REPORT_DESCRIPTOR           DefaultReportDescriptor[] = {
        // Keyboard ReportDescriptor
        0x05, 0x01,             // usage page (generic desktop)        Choose the usage page "keyboard" is on
        0x09, 0x06,             // usage (keyboard)                    Device is a keyboard
        0xA1, 0x01,             // collection (applicaton)             This collection comprises all the data words
        0x85, 0x03,             // REPORT_ID (3)
        0x05, 0x07,             // usage page (key codes)              Choose the key code usage page
        0x19, 0xE0,             // usage minimun (224)                 Choose key codes 224 to 231 which are modifier keys
        0x29, 0xE7,             // usage maximum (231)                 (left and right alt, shift, ctrl, and win)
        0x15, 0x00,             // logical mininum (0)                 Each of these eight key codes will report ranging in
        0x25, 0x01,             // logical maximum (1)                 value from zero to one
        0x75, 0x01,             // report size (1)                     Assign each of these keys a 1-bit report
        0x95, 0x08,             // report count (8)                    Report eight times
        0x81, 0x02,             // input (data, variable, absolute)    The defined byte above is an IN transaction
        0x95, 0x01,             // report count (1)
        0x75, 0x08,             // report size (8)                     Report eight bits one time
        0x81, 0x01,             // input (constant)                    Input the byte just described as a constant
        0x95, 0x05,             // report count (5)
        0x75, 0x01,             // report size (1)
        0x05, 0x08,             // usage page (page# for LEDs)         Choose LED usage page
        0x19, 0x01,             // usage minimum (1)
        0x29, 0x05,             // usage maximum (5)                   Define five LEDs
        0x91, 0x02,             // output (data, variable, absolute)   The defined bits above are an OUT transaction
        0x95, 0x01,             // report count (1)
        0x75, 0x03,             // report size (3)
        0x91, 0x01,             // output (constant)                   Three bit padding for the OUT transaction
        0x95, 0x06,             // report count (6)
        0x75, 0x08,             // report size (8)                     Report six bytes
        0x15, 0x00,             // logical minimum (0)
        0x25, 0x65,             // logical maximum (101)               The byte values can range from 0 to 101
        0x05, 0x07,             // usage page (key codes)              Change usage page to key codes
        0x19, 0x00,             // usage minimum (0)
        0x29, 0x65,             // usage maximum (101)                 Select key code range of 0 to 101
        0x81, 0x00,             // input (data, array)                 Input the above six bytes
        0xC0,                   // End collection                      End application collection

        0x05, 0x01,             // Usage Page (Generic Desktop),
        0x09, 0x02,             // Usage (Mouse),
        0xA1, 0x01,             // Collection (Application),
        0x85, 0x02,             // REPORT_ID (2)             
        0x09, 0x01,             // Usage (Pointer),
        0xA1, 0x00,             // Collection (Physical),
        0x05, 0x09,             // Usage Page (Buttons),
        0x19, 0x01,             // Usage Minimum (01),
        0x29, 0x03,             // Usage Maximun (03),
        0x15, 0x00,             // Logical Minimum (0),
        0x25, 0x01,             // Logical Maximum (1),
        0x95, 0x03,             // Report Count (3),
        0x75, 0x01,             // Report Size (1),
        0x81, 0x02,             // Input (Data, Variable, Absolute), ;3 button bits
        0x95, 0x01,             // Report Count (1),
        0x75, 0x05,             // Report Size (5),
        0x81, 0x01,             // Input (Constant), ;5 bit padding
        0x05, 0x01,             // Usage Page (Generic Desktop),
        0x09, 0x30,             // Usage (X),
        0x15, 0x00,             //   LOGICAL_MINIMUM (0)
        0x26, 0xFF, 0x03,       //   LOGICAL_MAXIMUM (1023)
        0x35, 0x00,             //   PHYSICAL_MINIMUM (0)
        0x46, 0xFF, 0x03,       //   PHYSICAL_MINIMUM (1023)
        0x75, 0x10,             //   REPORT_SIZE (16)
        0x95, 0x01,             //   REPORT_COUNT (1)
        0x81, 0x02,             //   INPUT (Data,Var,Abs)
        0x09, 0x31,             // Usage (Y),
        0x15, 0x00,             //   LOGICAL_MINIMUM (0)
        0x26, 0xFF, 0x02,       //   LOGICAL_MAXIMUM (767)
        0x35, 0x00,             //   PHYSICAL_MINIMUM (0)
        0x46, 0xFF, 0x02,       //   PHYSICAL_MINIMUM (767)
        0x75, 0x10,             //   REPORT_SIZE (16)
        0x95, 0x01,             //   REPORT_COUNT (1)
        0x81, 0x02,             //   INPUT (Data,Var,Abs)
        0xC0,                   // End Collection,
        0xC0,                   // End Collection,

        0x06,0x00, 0xFF,        // USAGE_PAGE (Vender Defined Usage Page)     
        0x09,0x01,              // USAGE (Vendor Usage 0x01)      
        0xA1,0x01,              // COLLECTION (Application)        
        0x85,0x01,              // REPORT_ID (1)
        0x09,0x01,              // USAGE (Vendor Usage 0x01)              
        0x15,0x00,              // LOGICAL_MINIMUM(0)                   
        0x26,0xff, 0x00,        // LOGICAL_MAXIMUM(255)               
        0x75,0x08,              // REPORT_SIZE (0x08)                     
        0x95,0x01,              // REPORT_COUNT (0x01)                    
        0xB1,0x00,              // FEATURE (Data,Ary,Abs)             
        0xC0                    // END_COLLECTION
};

//
// This is the default HID descriptor returned by the mini driver
// in response to IOCTL_HID_GET_DEVICE_DESCRIPTOR. The size
// of report descriptor is currently the size of DefaultReportDescriptor.
// If the report descriptor is successfully read from the registry, it is 
// modified to corresponding size of report descriptor.
//

HID_DESCRIPTOR              DefaultHidDescriptor = {
    0x09,      // length of HID descriptor
    0x21,      // descriptor type == HID  0x21
    0x0110,    // hid spec release
    0x00,      // country code == Not Specified
    0x01,      // number of HID class descriptors
    { 0x22,    // report descriptor type 0x22
    sizeof(DefaultReportDescriptor) }  // total length of report descriptor
};

//
//These are the device attributes returned by the mini driver in response 
// to IOCTL_HID_GET_DEVICE_ATTRIBUTES.
//

#define HIDMINI_PID        0xFEED
#define HIDMINI_VID        0xBEEF
#define HIDMINI_VERSION    0x0101

//
// These are the states FDO transition to upon
// receiving a specific PnP Irp. Refer to the PnP Device States
// diagram in DDK documentation for better understanding.
//

typedef enum _DEVICE_PNP_STATE {

    NotStarted = 0,         // Not started yet
    Started,                // Device has received the START_DEVICE IRP
    StopPending,            // Device has received the QUERY_STOP IRP
    Stopped,                // Device has received the STOP_DEVICE IRP
    RemovePending,          // Device has received the QUERY_REMOVE IRP
    SurpriseRemovePending,  // Device has received the SURPRISE_REMOVE IRP
    Deleted                 // Device has received the REMOVE_DEVICE IRP

} DEVICE_PNP_STATE;

BOOLEAN x = TRUE;

#define INITIALIZE_PNP_STATE(_Data_)    \
        (_Data_)->DevicePnPState =  NotStarted;\
        (_Data_)->PreviousPnPState = NotStarted;

#define SET_NEW_PNP_STATE(_Data_, _state_) \
        (_Data_)->PreviousPnPState =  (_Data_)->DevicePnPState;\
        (_Data_)->DevicePnPState = (_state_);

#define RESTORE_PREVIOUS_PNP_STATE(_Data_)   \
        (_Data_)->DevicePnPState =   (_Data_)->PreviousPnPState;\

typedef struct _DEVICE_EXTENSION {
    HID_DESCRIPTOR            HidDescriptor;
    PHID_REPORT_DESCRIPTOR    ReportDescriptor;
    BOOLEAN                   ReadReportDescFromRegistry;
    DEVICE_PNP_STATE    DevicePnPState;   // Track the state of the device
    DEVICE_PNP_STATE    PreviousPnPState; // Remembers the previous pnp state
} DEVICE_EXTENSION, * PDEVICE_EXTENSION;

typedef struct _READ_TIMER{
    
    KDPC             ReadTimerDpc;
    KTIMER          ReadTimer;
    PIRP              Irp;
  
} READ_TIMER, * PREAD_TIMER;


#define GET_MINIDRIVER_DEVICE_EXTENSION(DO) \
    ((PDEVICE_EXTENSION) \
    (((PHID_DEVICE_EXTENSION)(DO)->DeviceExtension)->MiniDeviceExtension))

#define GET_NEXT_DEVICE_OBJECT(DO) \
    (((PHID_DEVICE_EXTENSION)(DO)->DeviceExtension)->NextDeviceObject)

#define GET_PHYSICAL_DEVICE_OBJECT(DO) \
    (((PHID_DEVICE_EXTENSION)(DO)->DeviceExtension)->PhysicalDeviceObject)

//
// driver routines
//

NTSTATUS 
DriverEntry(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING registryPath
    );

NTSTATUS 
PnP(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS 
PnPComplete(
    IN PDEVICE_OBJECT   DeviceObject,
    IN PIRP             Irp,
    IN PVOID            Context
    );

NTSTATUS 
Power(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS 
SystemControl(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS  
AddDevice(
    IN PDRIVER_OBJECT DriverObject,
    IN PDEVICE_OBJECT FunctionalDeviceObject
    );

VOID 
Unload(
    IN PDRIVER_OBJECT DriverObject
    );

NTSTATUS 
InternalIoctl(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS 
GetHidDescriptor(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS 
GetReportDescriptor(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS 
GetAttributes(
    PDEVICE_OBJECT  DeviceObject,
    PIRP            Irp
    );

NTSTATUS 
GetDeviceAttributes(
    IN PDEVICE_OBJECT DeviceObject, 
    IN PIRP Irp);

NTSTATUS
GetSetFeature(
    IN PDEVICE_OBJECT DeviceObject, 
    IN PIRP Irp
    );

PCHAR
PnPMinorFunctionString(
    UCHAR MinorFunction
    );

NTSTATUS
HandleControlRequests(
    IN PHID_XFER_PACKET TransferPacket
    );

NTSTATUS
ReadDescriptorFromRegistry(
        IN PDEVICE_OBJECT       DeviceObject
        );

NTSTATUS 
ReadReport(
    IN PDEVICE_OBJECT DeviceObject, 
    IN PIRP Irp
    );

VOID 
ReadTimerDpcRoutine(   
    IN PKDPC Dpc,
    IN PVOID DeferredContext,
    IN PVOID SystemArgument1,
    IN PVOID SystemArgument2
    );

NTSTATUS
CheckRegistryForDescriptor(
        IN PDEVICE_OBJECT  DeviceObject
        );

#endif