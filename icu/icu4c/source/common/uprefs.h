#include <windows.h>
#include "unicode/utypes.h"
#include "unicode/ustring.h"
#include "cmemory.h"
#include "charstr.h"
#include "cstring.h"

#define UPREFS_API U_CFUNC U_EXPORT

/**
* Gets the valid and canonical BCP47 tag with the user settings for Language, Calendar, Sorting, Currency,
* First day of week, Hour cycle, and Measurement system when available.
*
* @param uprefsBuffer Pointer to a buffer in which this function retrieves the requested locale information.
*                     This pointer is not used if bufferSize is set to 0.
* @param bufferSize Size, in characters, of the data buffer indicated by uprefsBuffer. Alternatively, the application
*                   can set this parameter to 0. In this case, the function does not use the uprefsBuffer parameter
*                   and returns the required buffer size, including the terminating null character.
* @param status: Pointer to a UErrorCode. The resulting value will be U_ZERO_ERROR if the call was successful or will
*                contain an error or warning code. If the status is U_USING_FALLBACK_WARNING, it means at least one of the
                 settings was not succesfully mapped between NLS and CLDR, so it will not be shown on the BCP47 tag.
* @return The needed buffer size, including the terminating \0 null character if the call was successful, should be ignored 
*         if status was not U_ZERO_ERROR.
*/
int32_t uprefs_getBCP47Tag(char* uprefsBuffer, int32_t bufferSize, UErrorCode* status);
