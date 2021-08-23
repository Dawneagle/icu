#if U_PLATFORM_USES_ONLY_WIN32_API

// uprefs.cpp : Implementation of the APIs declared in uprefs.h

#include "uprefs.h"

U_NAMESPACE_USE

constexpr int32_t UPREFS_API_FAILURE = -1;

#define ALLOCATEMEMORY(var, type) (type)uprv_malloc(var * sizeof(type));

#define RETURN_FAILURE_STRING_WITH_STATUS_IF(value, error, status)      \
    if(value)                                                   \
    {                                                           \
        *status = error;                                        \
        return CharString();                                    \
    }

#define RETURN_FAILURE_WITH_STATUS_IF(condition, error)         \
    if(condition)                                               \
    {                                                           \
        *status = error;                                        \
        return UPREFS_API_FAILURE;                              \
    }

#define RETURN_VALUE_IF(condition, value)                       \
    if(condition)                                               \
    {                                                           \
        return value;                                           \
    }                                                           \

// -------------------------------------------------------
// ----------------- MAPPING FUNCTIONS--------------------
// -------------------------------------------------------

// Maps from a NLS Calendar ID (CALID) to a BCP47 Unicode Extension calendar identifier.
// 
// We map the NLS CALID from GetLocaleInfoEx to the calendar identifier
// used in BCP47 tag with Unicode Extensions.
//
// This does not return a full nor valid BCP47Tag, it only returns the option that the BCP47 tag
// would return after the "ca-" part
//
// For example:
//   CAL_GREGORIAN would return "gregory".
//   CAL_HIJRI would return "islamic".
// 
// These could be used in a BCP47 tag like this: "en-US-u-ca-gregory".
// Note that there are some NLS calendars that are not supported with the BCP47 U extensions,
// and vice-versa.
// 
// NLS CALID reference:https://docs.microsoft.com/en-us/windows/win32/intl/calendar-identifiers
CharString getCalendarBCP47FromNLSType(int32_t calendar, UErrorCode* status)
{
    switch(calendar){
        case CAL_GREGORIAN:
        case CAL_GREGORIAN_US:
        case CAL_GREGORIAN_ME_FRENCH:
        case CAL_GREGORIAN_ARABIC:
        case CAL_GREGORIAN_XLIT_ENGLISH:
        case CAL_GREGORIAN_XLIT_FRENCH:
            return CharString("gregory", *status);

        case CAL_JAPAN:
            return CharString("japanese", *status);

        case CAL_TAIWAN:
            return CharString("roc", *status);

        case CAL_KOREA:
            return CharString("dangi", *status);

        case CAL_HIJRI:
            return CharString("islamic", *status);

        case CAL_THAI:
            return CharString("buddhist", *status);

        case CAL_HEBREW:
            return CharString("hebrew", *status);

        case CAL_PERSIAN:
            return CharString("persian", *status);

        case CAL_UMALQURA:
            return CharString("islamic-umalqura", *status);

        default:
            return CharString();
    }
}

// Maps from a NLS Alternate sorting system to a BCP47 U extension sorting system.
// 
// We map the alternate sorting method from GetLocaleInfoEx to the sorting method
// used in BCP47 tag with Unicode Extensions.
//
// This does not return a full nor valid BCP47Tag, it only returns the option that the BCP47 tag
// would return after the "co-" part
//
// For example:
//   "phoneb" (parsed from "de-DE_phoneb") would return "phonebk".
//   "radstr" (parsed from "ja-JP_radstr") would return "unihan".
// 
// These could be used in a BCP47 tag like this: "de-DE-u-co-phonebk".
// Note that there are some NLS Alternate sort methods that are not supported with the BCP47 U extensions,
// and vice-versa.
CharString getSortingSystemBCP47FromNLSType(wchar_t* sortingSystem, UErrorCode* status) 
{
    if (wcscmp(sortingSystem, L"phoneb") == 0) // Phonebook style ordering (such as in German)
    {
        return CharString("phonebk", *status);
    }
    else if (wcscmp(sortingSystem, L"tradnl") == 0) // Traditional style ordering (such as in Spanish)
    {
        return CharString("trad", *status);
    }
    else if (wcscmp(sortingSystem, L"stroke") == 0) // Pinyin ordering for Latin, stroke order for CJK characters (used in Chinese)
    {
        return CharString("stroke", *status);
    }
    else if (wcscmp(sortingSystem, L"radstr") == 0) // Pinyin ordering for Latin, Unihan radical-stroke ordering for CJK characters (used in Chinese)
    {
        return CharString("unihan", *status);
    }
    else if (wcscmp(sortingSystem, L"pronun") == 0) // Phonetic ordering (sorting based on pronunciation)
    {
        return CharString("phonetic", *status);
    }
    else 
    {
        return CharString();
    }
}

// Maps from a NLS first day of week value to a BCP47 U extension first day of week.
// 
// NLS defines:
// 0 -> Monday, 1 -> Tuesday, ...  5 -> Saturday, 6 -> Sunday
//
// We map the first day of week from GetLocaleInfoEx to the first day of week
// used in BCP47 tag with Unicode Extensions.
//
// This does not return a full nor valid BCP47Tag, it only returns the option that the BCP47 tag
// would return after the "fw-" part
//
// For example:
//   1 (Tuesday) would return "tue".
//   6 (Sunday) would return "sun".
// 
// These could be used in a BCP47 tag like this: "en-US-u-fw-sun".
CharString getFirstDayBCP47FromNLSType(int32_t firstday, UErrorCode* status) 
{
    switch(firstday){
        case 0:
            return CharString("mon", *status);

        case 1:
            return CharString("tue", *status);

        case 2:
            return CharString("wed", *status);

        case 3:
            return CharString("thu", *status);

        case 4:
            return CharString("fri", *status);

        case 5:
            return CharString("sat", *status);

        case 6:
            return CharString("sun", *status);

        default:
            return CharString();
    }
}

// Maps from a NLS Measurement system to a BCP47 U extension measurement system.
// 
// NLS defines:
// 0 -> Metric system, 1 -> U.S. System
//
// This does not return a full nor valid BCP47Tag, it only returns the option that the BCP47 tag
// would return after the "ms-" part
//
// For example:
//   0 (Metric) would return "metric".
//   6 (U.S. System) would return "ussystem".
// 
// These could be used in a BCP47 tag like this: "en-US-u-ms-metric".
CharString getMeasureSystemBCP47FromNLSType(int32_t measureSystem, UErrorCode *status) 
{
    switch(measureSystem){
        case 0:
            return CharString("metric", *status);
        case 1:
            return CharString("ussystem", *status);
        default:
            return CharString();
    }
}

// -------------------------------------------------------
// --------------- END OF MAPPING FUNCTIONS --------------
// -------------------------------------------------------

// -------------------------------------------------------
// ------------------ HELPER FUCTIONS  -------------------
// -------------------------------------------------------
void WstrToUChar(char* dest, const wchar_t* str, size_t cch, UErrorCode* status) 
{
    int32_t i;
    for (i = 0; i <= cch; i++)
    {
        *(dest + i) = static_cast<char>(*(str + i));
    }
    *(dest + i) = '\0';
}

// Return the CLDR "h12" or "h23" format for the 12 or 24 hour clock.
// NLS only gives us a "time format" of a form similar to "h:mm:ss tt"
// The NLS "h" is 12 hour, and "H" is 24 hour, so we'll scan for the
// first h or H.
// Note that the NLS string could have sections escaped with single
// quotes, so be sure to skip those parts. Eg: "'Hours:' h:mm:ss"
// would skip the "H" in 'Hours' and use the h in the actual pattern.
CharString get12_or_24hourFormat(wchar_t* hourFormat, UErrorCode* status)
{
    bool isInEscapedString = false;
    for (int i = 0; i < wcslen(hourFormat); i++)
    {
        // Toggle escaped flag if in ' quoted portion
        if (hourFormat[i] == L'\'') 
        {
            isInEscapedString = !isInEscapedString;
        }
        if (!isInEscapedString) 
        {
            // Check for both so we can escape early
            if (hourFormat[i] == L'H') 
            {
                return CharString("h23", *status);
            }
            if (hourFormat[i] == L'h')
            {
                return CharString("h12", *status);
            }
        }
    }
    // default to a 24 hour clock as that's more common worldwide
    return CharString("h23", *status);
}

UErrorCode getUErrorCodeFromLastError()
{
    DWORD error = GetLastError();
    if (error == ERROR_INSUFFICIENT_BUFFER)
    {
        return U_BUFFER_OVERFLOW_ERROR;
    }
    else if (error == ERROR_INVALID_FLAGS)
    {
        return U_ILLEGAL_ARGUMENT_ERROR;
    }
    else if (error == ERROR_INVALID_PARAMETER)
    {
        return U_ILLEGAL_ARGUMENT_ERROR;
    }
    return U_INTERNAL_PROGRAM_ERROR;
}

int32_t GetLocaleInfoExWrapper(LPCWSTR lpLocaleName, LCTYPE LCType, LPWSTR lpLCData, int cchData, UErrorCode* errorCode)
{
    int32_t result = GetLocaleInfoEx(lpLocaleName, LCType, lpLCData, cchData);

    if (result == 0)
    {
        *errorCode = getUErrorCodeFromLastError();
        return UPREFS_API_FAILURE;
    }
    *errorCode = U_ZERO_ERROR;
    return result;
}

// This obtains data from NLS for the given LCTYPE for cases such as locale name, sorting method or currency.
// This function can be used with a null buffer to find out the needed buffer size.
int32_t GetLocaleInfoAsString(wchar_t* dataBuffer, int32_t bufferSize, PCWSTR localeName, LCTYPE type, UErrorCode* status)
{
    int32_t neededBufferSize = GetLocaleInfoExWrapper(localeName, type, nullptr, 0, status);
    RETURN_VALUE_IF(neededBufferSize < 0, -1);
    RETURN_VALUE_IF(dataBuffer == nullptr, neededBufferSize);

    int32_t result = GetLocaleInfoExWrapper(localeName, type, dataBuffer, neededBufferSize, status);
    RETURN_VALUE_IF(result < 0, -1);

    return neededBufferSize;
}

// Get data from GetLocaleInfoEx as an int for cases such as Calendar, First day of the week, and Measurement system
// This only works for LCTYPEs that start with LOCALE_I, such as LOCALE_IFIRSTDAYOFWEEK or LOCALE_ICALENDARTYPE,
// it will not work for LCTYPEs that start with LOCALE_S, such as LOCALE_SNAME or LOCALE_SINTLSYMBOL
// This allows us to then use defined constants such as CAL_GREGORIAN, and avoid unneeded allocations.
int32_t GetLocaleInfoAsInt(PCWSTR localeName, LCTYPE type, UErrorCode* status)
{
    int32_t result = 0;
    int32_t neededBufferSize = GetLocaleInfoExWrapper(localeName, 
                                                      type | LOCALE_RETURN_NUMBER, 
                                                      reinterpret_cast<PWSTR>(&result), 
                                                      sizeof(result) / sizeof(wchar_t), 
                                                      status);

    return result;
}

// Copies a string to a buffer if its size allows it and returns the size.
// The returned needed buffer size includes the terminating \0 null character.
// If the buffer's size is set to 0, the needed buffer size is returned before copying the string.
int32_t checkBufferCapacityAndCopy(const char* uprefsString, char* uprefsBuffer, int32_t bufferSize, UErrorCode* status)
{
    size_t neededBufferSize = strlen(uprefsString) + 1;

    RETURN_VALUE_IF(bufferSize == 0, static_cast<int32_t>(neededBufferSize));
    RETURN_FAILURE_WITH_STATUS_IF(neededBufferSize > bufferSize, U_BUFFER_OVERFLOW_ERROR);

    strcpy(uprefsBuffer, uprefsString);

    return static_cast<int32_t>(neededBufferSize);
}


CharString getLocaleBCP47Tag_impl(UErrorCode* status)
{
    // First part of a bcp47 tag looks like an NLS user locale, so we get the NLS user locale.
    int32_t neededBufferSize = GetLocaleInfoAsString(nullptr, 0, LOCALE_NAME_USER_DEFAULT, LOCALE_SNAME, status);
    if(U_FAILURE(*status) || neededBufferSize == -1)
    {
        return CharString();
    }

    wchar_t *NLSLocale = ALLOCATEMEMORY(neededBufferSize, wchar_t*);
    RETURN_FAILURE_STRING_WITH_STATUS_IF(NLSLocale == NULL, U_MEMORY_ALLOCATION_ERROR, status);
    
    int32_t result = GetLocaleInfoAsString(NLSLocale, neededBufferSize, LOCALE_NAME_USER_DEFAULT, LOCALE_SNAME, status);

    if(U_FAILURE(*status) || result == -1)
    {
        uprv_free(NLSLocale);
        return CharString();
    }

    // The NLS locale may include a non-default sort, such as de-DE_phoneb. We only want the locale name before the _.
    wchar_t * position = wcsstr(NLSLocale, L"_");
    if (position != nullptr)
    {
        position = L"\0";
    }
    CharString languageTag;
    wcstombs(languageTag.data(), NLSLocale, neededBufferSize);
    // WstrToUChar(languageTag, NLSLocale, neededBufferSize, status);
    uprv_free(NLSLocale);
    return languageTag;

}

CharString getCalendarSystem_impl(UErrorCode* status)
{
    int32_t NLSCalendar = GetLocaleInfoAsInt(LOCALE_NAME_USER_DEFAULT, LOCALE_ICALENDARTYPE, status);
    RETURN_VALUE_IF(U_FAILURE(*status), CharString());

    CharString calendar(getCalendarBCP47FromNLSType(NLSCalendar, status), *status);
    RETURN_FAILURE_STRING_WITH_STATUS_IF(strlen(calendar.data()) == 0, U_UNSUPPORTED_ERROR, status);

    return calendar;
}

CharString getSortingSystem_impl(UErrorCode* status)
{
    // In order to get the sorting system, we need to get LOCALE_SNAME, which appends the sorting system (if any) to the locale
    int32_t neededBufferSize = GetLocaleInfoAsString(nullptr, 0, LOCALE_NAME_USER_DEFAULT, LOCALE_SNAME, status);
    if(U_FAILURE(*status) || neededBufferSize == -1)
    {
        return CharString();
    }

    wchar_t *NLSsortingSystem = ALLOCATEMEMORY(neededBufferSize, wchar_t*);
    if(NLSsortingSystem == NULL)
    {
        *status = U_MEMORY_ALLOCATION_ERROR;
        return CharString();
    }
    int32_t result = GetLocaleInfoAsString(NLSsortingSystem, neededBufferSize, LOCALE_NAME_USER_DEFAULT, LOCALE_SNAME, status);

    if(U_FAILURE(*status) || result == -1)
    {
        uprv_free(NLSsortingSystem);
        return CharString();
    }   

    // We use LOCALE_SNAME to get the sorting method (if any). So we need to keep
    // only the sorting bit after the _, removing the locale name.
    // Example: from "de-DE_phoneb" we only want "phoneb"
    wchar_t * startPosition = wcsstr(NLSsortingSystem, L"_");

    // Note: not finding a "_" is not an error, it means the user has not selected an alternate sorting method, which is fine.
    if (startPosition != nullptr) 
    {
        NLSsortingSystem = startPosition + 1;
        CharString sortingSystem = getSortingSystemBCP47FromNLSType(NLSsortingSystem, status);

        if(strlen(sortingSystem.data()) == 0)
        {
            uprv_free(NLSsortingSystem);
            *status = U_UNSUPPORTED_ERROR;
            return CharString();
        }
        uprv_free(NLSsortingSystem);
        return sortingSystem;
    }
    uprv_free(NLSsortingSystem);
    return CharString();
}

int32_t getCurrencyCode_impl(char* currency, UErrorCode* status)
{
    int32_t neededBufferSize = GetLocaleInfoAsString(nullptr, 0, LOCALE_NAME_USER_DEFAULT, LOCALE_SINTLSYMBOL, status);
    if(U_FAILURE(*status) || neededBufferSize == -1)
    {
        currency = "";
        return -1;
    }
    
    wchar_t *NLScurrencyData = ALLOCATEMEMORY(neededBufferSize, wchar_t*);
    RETURN_FAILURE_WITH_STATUS_IF(NLScurrencyData == NULL, U_MEMORY_ALLOCATION_ERROR);
    int32_t result = GetLocaleInfoAsString(NLScurrencyData, neededBufferSize, LOCALE_NAME_USER_DEFAULT, LOCALE_SINTLSYMBOL, status);
    if(U_FAILURE(*status) || result == -1)
    {
        uprv_free(NLScurrencyData);
        currency = "";
        return -1;
    }   

    WstrToUChar(currency, NLScurrencyData, neededBufferSize, status);
    if(strlen(currency) == 0)
    {
        uprv_free(NLScurrencyData);
        *status = U_INTERNAL_PROGRAM_ERROR;
        currency = "";
        return -1;
    }

    // Since we retreived the currency code in caps, we need to make it lowercase for it to be in CLDR BCP47 U extensions format.
    T_CString_toLowerCase(currency);

    uprv_free(NLScurrencyData);
    return 0;
}

CharString getFirstDayOfWeek_impl(UErrorCode* status)
{
    int32_t NLSfirstDay = GetLocaleInfoAsInt(LOCALE_NAME_USER_DEFAULT, LOCALE_IFIRSTDAYOFWEEK, status);
    RETURN_VALUE_IF(U_FAILURE(*status), CharString());

    CharString firstDay = getFirstDayBCP47FromNLSType(NLSfirstDay, status);
    RETURN_FAILURE_STRING_WITH_STATUS_IF(strlen(firstDay.data()) == 0, U_UNSUPPORTED_ERROR, status);

    return firstDay;
}

CharString getHourCycle_impl(UErrorCode* status)
{
    int32_t neededBufferSize = GetLocaleInfoAsString(nullptr, 0, LOCALE_NAME_USER_DEFAULT, LOCALE_STIMEFORMAT, status);
    if(U_FAILURE(*status) || neededBufferSize == -1)
    {
        return CharString();
    }
    wchar_t *NLShourCycle = ALLOCATEMEMORY(neededBufferSize, wchar_t*);
    if(NLShourCycle == NULL)
    {
        *status = U_MEMORY_ALLOCATION_ERROR;
    }
    int32_t result = GetLocaleInfoAsString(NLShourCycle, neededBufferSize, LOCALE_NAME_USER_DEFAULT, LOCALE_STIMEFORMAT, status);
    if(U_FAILURE(*status) || result == -1)
    {
        uprv_free(NLShourCycle);
        return CharString();
    }   

    CharString hourCycle = get12_or_24hourFormat(NLShourCycle, status);
    if(strlen(hourCycle.data()) == 0)
    {
        uprv_free(NLShourCycle);
        *status = U_INTERNAL_PROGRAM_ERROR;
        return CharString();
    }
    uprv_free(NLShourCycle);
    return hourCycle;
}

CharString getMeasureSystem_impl(UErrorCode* status)
{
    int32_t NLSmeasureSystem = GetLocaleInfoAsInt(LOCALE_NAME_USER_DEFAULT, LOCALE_IMEASURE, status);
    RETURN_VALUE_IF(U_FAILURE(*status), CharString());

    CharString measureSystem = getMeasureSystemBCP47FromNLSType(NLSmeasureSystem, status);
    RETURN_FAILURE_STRING_WITH_STATUS_IF(strlen(measureSystem.data()) == 0, U_UNSUPPORTED_ERROR, status);

    return measureSystem;
}

void appendIfDataNotEmpty(CharString& dest, const char* firstData, const char* secondData, bool& warningGenerated, UErrorCode* status)
{
    if(*status == U_UNSUPPORTED_ERROR)
    {
        warningGenerated = true;
    }

    if(strlen(secondData) != 0)
    {
        dest.append(firstData, *status);
        dest.append(secondData, *status);
    }
}
// -------------------------------------------------------
// --------------- END OF HELPER FUNCTIONS ---------------
// -------------------------------------------------------


// -------------------------------------------------------
// ---------------------- APIs ---------------------------
// -------------------------------------------------------

// Gets the valid and canonical BCP47 tag with the user settings for Language, Calendar, Sorting, Currency,
// First day of week, Hour cycle, and Measurement system.
// Calls all of the other APIs
// Returns the needed buffer size for the BCP47 Tag. 
int32_t uprefs_getBCP47Tag(char* uprefsBuffer, int32_t bufferSize, UErrorCode* status)
{
    RETURN_FAILURE_WITH_STATUS_IF(uprefsBuffer == nullptr && bufferSize != 0, U_ILLEGAL_ARGUMENT_ERROR);

    CharString BCP47Tag;
    bool warningGenerated = false;

    CharString languageTag = getLocaleBCP47Tag_impl(status);
    RETURN_VALUE_IF(U_FAILURE(*status), UPREFS_API_FAILURE);
    BCP47Tag.append(languageTag.data(), *status);
    BCP47Tag.append("-u", *status);

    CharString calendar = getCalendarSystem_impl(status);
    RETURN_VALUE_IF(U_FAILURE(*status) && *status != U_UNSUPPORTED_ERROR, UPREFS_API_FAILURE);
    appendIfDataNotEmpty(BCP47Tag, "-ca-", calendar.data(), warningGenerated, status);
    
    CharString sortingSystem = getSortingSystem_impl(status);
    RETURN_VALUE_IF(U_FAILURE(*status) && *status != U_UNSUPPORTED_ERROR, UPREFS_API_FAILURE);
    appendIfDataNotEmpty(BCP47Tag, "-co-", sortingSystem.data(), warningGenerated, status);

    CharString currency;
    size_t currencyResult = getCurrencyCode_impl(currency.data(), status);
    RETURN_VALUE_IF(U_FAILURE(*status) && *status != U_UNSUPPORTED_ERROR || currencyResult == -1, UPREFS_API_FAILURE);
    appendIfDataNotEmpty(BCP47Tag, "-cu-", currency.data(), warningGenerated, status);

    CharString firstDay = getFirstDayOfWeek_impl(status);
    RETURN_VALUE_IF(U_FAILURE(*status) && *status != U_UNSUPPORTED_ERROR, UPREFS_API_FAILURE);
    appendIfDataNotEmpty(BCP47Tag, "-fw-", firstDay.data(), warningGenerated, status);

    CharString hourCycle = getHourCycle_impl(status);
    RETURN_VALUE_IF(U_FAILURE(*status) && *status != U_UNSUPPORTED_ERROR, UPREFS_API_FAILURE);
    appendIfDataNotEmpty(BCP47Tag, "-hc-", hourCycle.data(), warningGenerated, status);

    CharString measureSystem = getMeasureSystem_impl(status);
    RETURN_VALUE_IF(U_FAILURE(*status) && *status != U_UNSUPPORTED_ERROR, UPREFS_API_FAILURE);
    appendIfDataNotEmpty(BCP47Tag, "-ms-", measureSystem.data(), warningGenerated, status);

    if(warningGenerated)
    {
        *status = U_USING_FALLBACK_WARNING;
    }

    int32_t result = checkBufferCapacityAndCopy(BCP47Tag.data(), uprefsBuffer, bufferSize, status);

    return result;
}

// -------------------------------------------------------
// ---------------------- END OF APIs --------------------
// -------------------------------------------------------

#endif