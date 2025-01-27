////////////////////////////////////////////////////////////////////////////////
//
//  Title     : clallserial.h
//  Created   : 12/03/2003 @ 14:27:00
//
//  This code was developed and donated to the Camera Link Committee by
//  National Instruments.
////////////////////////////////////////////////////////////////////////////////
#ifndef __clallserial_h__
#define __clallserial_h__

//==============================================================================
//  Macros and Constants
//==============================================================================
#if (defined(__cplusplus) || defined(__cplusplus__))
    #define USER_EXTERN_C extern "C"
#else
    #define USER_EXTERN_C
#endif

#ifdef CLALLSERIAL_EXPORTS
    #define CLALLSERIALEXPORT USER_EXTERN_C __declspec(dllexport)
#else
    #define CLALLSERIALEXPORT USER_EXTERN_C __declspec(dllimport)
#endif

#ifndef CLALLSERIALCC
    #define CLALLSERIALCC __stdcall
#endif

#ifndef _CL_hSerRef_DEFINED_
    #define _CL_hSerRef_DEFINED_
    typedef void*        hSerRef;
#endif

#ifndef _CL_INT32_DEFINED_
    #define _CL_INT32_DEFINED_
    typedef int          INT32;
#endif


#ifndef _CL_UINT32_DEFINED_
    #define _CL_UINT32_DEFINED_
    typedef unsigned int UINT32;
#endif

#ifndef _CL_INT8_DEFINED_
    #define _CL_INT8_DEFINED_
    typedef char         INT8;
#endif


//------------------------------------------------------------------------------
//  CL serial DLL versions
//------------------------------------------------------------------------------
#define CL_DLL_VERSION_NO_VERSION               1   // Not a CL dll
#define CL_DLL_VERSION_1_0                      2   // Oct 2000 compliant
#define CL_DLL_VERSION_1_1                      3   // Oct 2001 compliant


//------------------------------------------------------------------------------
//  Baud Rates
//------------------------------------------------------------------------------
#define CL_BAUDRATE_9600                        1
#define CL_BAUDRATE_19200                       2
#define CL_BAUDRATE_38400                       4
#define CL_BAUDRATE_57600                       8
#define CL_BAUDRATE_115200                      16
#define CL_BAUDRATE_230400                      32
#define CL_BAUDRATE_460800                      64
#define CL_BAUDRATE_921600                      128


//------------------------------------------------------------------------------
//  Error Codes
//------------------------------------------------------------------------------
#define CL_ERR_NO_ERR                               0
#define CL_ERR_BUFFER_TOO_SMALL                     -10001
#define CL_ERR_MANU_DOES_NOT_EXIST                  -10002
#define CL_ERR_PORT_IN_USE                          -10003
#define CL_ERR_TIMEOUT                              -10004
#define CL_ERR_INVALID_INDEX                        -10005
#define CL_ERR_INVALID_REFERENCE                    -10006
#define CL_ERR_ERROR_NOT_FOUND                      -10007
#define CL_ERR_BAUD_RATE_NOT_SUPPORTED              -10008
#define CL_ERR_OUT_OF_MEMORY                        -10009
#define CL_ERR_REGISTRY_KEY_NOT_FOUND               -10010
#define CL_ERR_UNABLE_TO_LOAD_DLL                   -10098
#define CL_ERR_FUNCTION_NOT_FOUND                   -10099


//==============================================================================
// Exported functions 
//==============================================================================
////////////////////////////////////////////////////////////////////////////////
//
//  clFlushPort
//
//  Description: Discards any bytes that are available in the input 
//  buffer.
//      
//  Parameters:
//      serialRef       input parameter - The value obtained by the clSerialInit function 
//                      that describes the port to be flushed.
//
//  Return Value:       CL_ERR_NO_ERR
//                      CL_ERR_INVALID_REFERENCE
//
////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT INT32 CLALLSERIALCC clFlushPort(hSerRef serialRef);


////////////////////////////////////////////////////////////////////////////////
//
//  clGetErrorText
//
//  Description:
//  Converts an error code to error text which you can
//  display in a dialog box or in the standard I/O window.  
//  Note: This function first looks up the error code in clserial.dll to determine
//  whether it is a standard Camera Link error. If it is a non-standard error, this function 
//  passes the error code to the manufacturer-specific DLL, which returns the
//  manufacturer-specific error code.
//
//  Parameters:
//      manuName            input parameter - The manufacturer name in a NULL-terminated
//                          buffer.  Manufacturer name is returned from clGetPortInfo.
//      errorCode           input parameter - The error code used to look up the 
//                          appropriate error text.  This code can be returned 
//                          from any function in this library.
//      errorText           output parameter - A caller-allocated buffer which will contain
//                          a NULL-terminated error description on return.
//      errorTextSize       input/output parameter - As an input, this value is the size,
//                          in bytes, of the errorText buffer that is passed in. On
//                          success, this value is the number of bytes 
//                          that have been written into the buffer, including the NULL
//                          termination character. On CL_ERR_BUFFER_TOO_SMALL error,
//                          this value is the size of the buffer required to write
//                          the data text.
//
//  Return Value:           CL_ERR_NO_ERR
//                          CL_ERR_MANU_DOES_NOT_EXIST
//                          CL_ERR_BUFFER_TOO_SMALL
//                          CL_ERR_ERROR_NOT_FOUND
//      
/////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT INT32 CLALLSERIALCC clGetErrorText(const INT8* manuName, INT32 errorCode, INT8* errorText, UINT32* errorTextSize);


////////////////////////////////////////////////////////////////////////////////
//
//  clGetNumPorts 
//
//  Description: Returns the number of Camera Link serial ports in 
//  this machine that are supported by clallserial.dll. 
//      
//  Parameters:
//      numPorts        output parameter - The number of Camera Link serial ports 
//                      in this machine supported by this DLL.
//
//  Return Value:       CL_ERR_NO_ERR
//
////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT INT32 CLALLSERIALCC clGetNumPorts(UINT32* Ports); 


////////////////////////////////////////////////////////////////////////////////
//
//  clGetNumBytesAvail 
//
//  Description: Outputs the number of bytes that are received, but not yet read out, at 
//  the port specified by serialRef.
//      
//  Parameters:
//      serialRef       input - The value obtained by the clSerialInit function.
//      numBytes        output - The number of bytes currently available to be 
//                      read from the port.
//
//  Return Value:       CL_ERR_NO_ERR
//                      CL_ERR_INVALID_REFERENCE
//
////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT INT32 CLALLSERIALCC clGetNumBytesAvail(hSerRef serialRef, UINT32* numBytes);


////////////////////////////////////////////////////////////////////////////////
//
//  clGetPortInfo
//
//  Description: This function provides information about the port specified by 
//  the index.      
//
//  Parameters:
//      serialIndex       input parameter - Zero-based index of the serial port you are   
//                        finding the name for. Use clGetNumSerialPorts to determine
//                        the valid range of serialIndex. This range will be 0 to 
//                        numSerialPorts-1. 
//      manufacturerName  output parameter - Pointer to a user-allocated buffer into 
//                        which the fucntion copies the manufacturer name.  The returned 
//                        name is NULL-terminated.  In the case that the DLL conforms to the 
//                        version 1.0 Camera Link Specification, this 
//                        parameter will contain the file name of the DLL rather than the 
//                        manufacturer name.
//      nameBytes         input/output parameter - As an input parameter, 
//                        this value is the size of the name buffer, including
//                        the NULL termination. As an output parameter, this value
//                        is the number of bytes written into the name buffer.
//                        If the provided name buffer is not large enough, this value
//                        is the number of required bytes.
//      portID            output parameter - The identifier for the port. For now, this 
//                        value is the interface name. In the future, there may be an 
//                        extension for multiple serial ports on one board.
//      IDBytes           input/output parameter. As an input parameter, this value is
//                        the size of the portID buffer, including
//                        the NULL termination. As an output parameter, this value is
//                        the number of bytes written into the portID buffer.
//                        If the provided portID buffer is not large enough, this value is
//                        the number of required bytes.
//
//  Return Value:         CL_ERR_NO_ERR
//                        CL_ERR_BUFFER_TOO_SMALL
//                        CL_ERR_INVALID_INDEX//
////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT INT32 CLALLSERIALCC clGetPortInfo(UINT32 serialIndex, INT8* manufacturerName, UINT32* nameBytes, INT8* portID, UINT32* IDBytes, UINT32* version);


////////////////////////////////////////////////////////////////////////////////
//
//  clGetSupportedBaudRates
//
//  Description:    Returns the valid baud rates of the interface.
//
//  Parameters:
//      serialRefPtr    input parameter - The value obtained from 
//                      clSerialInit function.
//      baudRates       output parameter -  Indicates which baud
//                      rates are supported by this serial interface. This 
//                      is represented as a bitfield. Refer to the CL_BAUDRATE_
//                      constants above for the supported baud rates.
//
//  Return Value:       CL_ERR_NO_ERR
//                      CL_ERR_INVALID_REFERENCE
//                      CL_ERR_FUNCTION_NOT_FOUND   
//      
/////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT INT32 CLALLSERIALCC clGetSupportedBaudRates(hSerRef serialRef, UINT32* baudRates);


//////////////////////////////////////////////////////////////////////////////////
//
//  clSerialClose
//
//  Description:    Closes the serial device and cleans up resources associated
//  with serialRef. Upon return, serialRef is no longer usable.
//
//  Parameters:
//    serialRef        input parameter - The value obtained from clSerialInit 
//                     function to clean up.
//                   
///////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT void CLALLSERIALCC clSerialClose(hSerRef serialRef);


////////////////////////////////////////////////////////////////////////////////
//
//  clSerialInit
//
//  Description:
//  Initializes the device referred to by serialIndex, and
//  returns a pointer to an internal serial reference structure.    
//
//  Parameters:
//      serialIndex     input parameter - Zero-based index value. If there are n
//                      serial devices in the system that is supported by this
//                      library, the range of serialIndex is 0 to (n-1).
//                      The order of the serial devices is vendor-specific. The 
//                      number of serial ports supported by this DLL is
//                      output by the clGetNumSerialPorts function.
//      serialRefPtr    output parameter - Upon a successful call, a pointer to the 
//                      vendor-specific reference to the current serial session 
//                      will be put into the value pointed to by serialRefPtr.
//
//  Return Value:           CL_ERR_NO_ERR
//                          CL_ERR_PORT_IN_USE
//                          CL_ERR_INVALID_INDEX
//                          CL_ERR_UNABLE_TO_OPEN_PORT
//      
////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT INT32 CLALLSERIALCC clSerialInit(UINT32 serialIndex, hSerRef* serialRefPtr);


////////////////////////////////////////////////////////////////////////////////
//
//  clSerialRead
//
//  Description: Reads from the serial device referenced by serialRef.
//
//  Parameters:
//    serialRef      input parameter - The value obtained from clSerialInit function
//    buffer         output parameter - Points to a user-allocated buffer.
//                   Upon a successful call, contains the data
//                   read from the serial device.
//    bufferSize     input-output parameter - As an input parameter, bufferSize contains the 
//                   buffer size to indicate the maximum number of bytes that
//                   the buffer can accomodate.
//                   Upon a successful call, bufferSize is the
//                   number of bytes that were read successfully from the
//                   serial device.
//    serialTimeout  input parameter - Indicates the timeout, in milliseconds
//
//  Return value    CL_ERR_NO_ERR
//                   CL_ERR_TIMEOUT
//                   CL_ERR_INVALID_REFERENCE
//   
////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT INT32 CLALLSERIALCC clSerialRead(hSerRef serialRef, INT8* buffer, UINT32* bufferSize, UINT32 serialTimeout);


////////////////////////////////////////////////////////////////////////////////
//
//  clSerialWrite
//
//  Description: This function writes data in buffer to the serial device 
//  referenced by serialRef.
//
//  Parameters:
//    serialRef      input parameter - The value obtained from clSerialInit function
//    buffer         input parameter - Contains data to write to the serial port
//    bufferSize     input/output parameter - As an input parameter, bufferSize contains the 
//                   number of bytes of data in the buffer to write to the
//                   serial device. Upon a successful call, bufferSize contains the
//                   number of bytes that was written successfully to the
//                   serial device.
//    serialTimeout  input parameter - Indicates the timeout, in miliseconds
//
//  Return value:    CL_ERR_NO_ERR
//                   CL_ERR_INVALID_REFERENCE
//                   CL_ERR_TIMEOUT
/////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT INT32 CLALLSERIALCC clSerialWrite(hSerRef serialRef, INT8* buffer, UINT32* bufferSize, UINT32 serialTimeout);


////////////////////////////////////////////////////////////////////////////////
//
//  clSetBaudRate
//
//  Description:     Sets the Baud Rate for the serial port of the
//                   selected port. Use clGetSupportedBaudRates to deterimine
//                   supported baud rates.
//      
//  Parameters:
//      serialRef    input parameter - The value obtained from 
//                   clSerialInit function.
//      baudRate     input parameter - The baud rate you want to use. This
//                   input expects the values represented by the CL_BAUDRATE
//                   constants.
//
//  Return Value:    CL_ERR_NO_ERR
//                   CL_ERR_INVALID_REFERENCE
//                   CL_ERR_BAUD_RATE_NOT_SUPPORTED
//
////////////////////////////////////////////////////////////////////////////////
CLALLSERIALEXPORT INT32 CLALLSERIALCC clSetBaudRate(hSerRef serialRef, UINT32 baudRate);

//==============================================================================
//  the endif
//==============================================================================
#endif
