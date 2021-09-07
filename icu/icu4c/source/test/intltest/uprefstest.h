#ifndef UPREFSTEST_H
#define UPREFSTEST_H

#include "unicode/platform.h"
#if U_PLATFORM_USES_ONLY_WIN32_API
#define UPREFS_TEST 1


#include "windows.h"
#include "intltest.h"
#include "uprefs.h"

class UPrefsTest: public IntlTest {
public:
    std::wstring UPrefsTest::language = L"";
    std::wstring UPrefsTest::currency = L"";
    std::wstring UPrefsTest::hourCycle = L"";
    int32_t UPrefsTest::firstday = 0;
    int32_t UPrefsTest::measureSystem = 0;
    CALID UPrefsTest::calendar = 0;
    UPrefsTest();
    virtual ~UPrefsTest();

    virtual void runIndexedTest(int32_t index, UBool exec, const char *&name, char *par = NULL);
    int32_t MockGetLocaleInfoEx(LPCWSTR lpLocaleName, LCTYPE LCType, LPWSTR lpLCData, int cchData, UErrorCode* status);
    void TestGetBCP47Tag1();
    void TestBCP47TagWithSorting();
    void TestBCP47TagChineseSimplified();
    void TestBCP47TagChineseSortingStroke();
    void TestBCP47TagJapanCalendar();
    void TestUseNeededBuffer();
    void TestGetNeededBuffer();
    void TestGetUnsupportedSorting();
    void Get24HourCycleMixed1();
    void Get24HourCycleMixed2();
    void Get24HourCycleMixed3();
    void Get24HourCycleMixed();
    void Get12HourCycleMixed();
    void Get12HourCycleMixed2();
    void Get12HourCycle();
    void Get12HourCycle2();   
};

#endif //UPREFSTEST_H
#endif //U_PLATFORM_USES_ONLY_WIN32_API