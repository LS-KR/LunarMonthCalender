// LunarCalenderDay.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <time.h>

#pragma warning(disable:4996)

typedef struct {
    int Month;
    int Day;
    bool IsLeap;
} LunarDate;

class Lunar
{
public:
    LunarDate GetLunarDate(int year, int month, int day);
    int GetOriginalSource(int year, int month, int day);
    std::string GetString(LunarDate ld);
    bool IsLeap(int year, int month, int day);
private:
    unsigned int LunarCalendarDay;
    int LunarCalendar(int year, int month, int day);
protected:
    unsigned int LunarCalendarTable[199] = {
    0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A,/*1901-1910*/
    0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754,/*1911-1920*/
    0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E,/*1921-1930*/
    0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48,/*1931-1940*/
    0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51,/*1941-1950*/
    0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x6AD53C,/*1951-1960*/
    0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46,/*1961-1970*/
    0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50,/*1971-1980*/
    0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB,/*1981-1990*/
    0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645,/*1991-2000*/
    0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E,/*2001-2010*/
    0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9,/*2011-2020*/
    0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43,/*2021-2030*/
    0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C,/*2031-2040*/
    0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37,/*2041-2050*/
    0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42,/*2051-2060*/
    0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B,/*2061-2070*/
    0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6,/*2071-2080*/
    0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E,/*2081-2090*/
    0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5          /*2091-2099*/
    };
    unsigned int MonthAdd[12] = { 0,31,59,90,120,151,181,212,243,273,304,334 };
    unsigned int MonthAddLeap[12] = { 0,31,60,91,121,152,182,213,244,274,305,335 };
};

int Lunar::LunarCalendar(int year, int month, int day)
{
    //StaticDayCount记录大小月的天数 29 或30
    //index 记录从哪个月开始来计算。
    //flag 是用来对闰月的特殊处理。
    int Spring_NY, Sun_NY, StaticDayCount;
    int index, flag;
    if (((LunarCalendarTable[year - 1901] & 0x0060) >> 5) == 1)
        Spring_NY = (LunarCalendarTable[year - 1901] & 0x001F) - 1;
    else
        Spring_NY = (LunarCalendarTable[year - 1901] & 0x001F) + 30;
    Sun_NY = MonthAdd[month - 1] + day - 1;
    if ((!(year % 4)) && (month > 2))
        Sun_NY++;
    //判断日期是否再春节后
    if (Sun_NY >= Spring_NY)
    {
        Sun_NY -= Spring_NY;
        month = 1;
        index = 1;
        flag = 0;
        if ((LunarCalendarTable[year - 1901] & (0x80000 >> (index - 1))) == 0)
            StaticDayCount = 29;
        else
            StaticDayCount = 30;
        while (Sun_NY >= StaticDayCount)
        {
            Sun_NY -= StaticDayCount;
            index++;
            if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
            {
                flag = ~flag;
                if (flag == 0)
                    month++;
            }
            else
                month++;
            if ((LunarCalendarTable[year - 1901] & (0x80000 >> (index - 1))) == 0)
                StaticDayCount = 29;
            else
                StaticDayCount = 30;
        }
        day = Sun_NY + 1;
    }
    else
    {
        Spring_NY -= Sun_NY;
        year--;
        month = 12;
        if (((LunarCalendarTable[year - 1901] & 0xF00000) >> 20) == 0)
            index = 12;
        else
            index = 13;
        flag = 0;
        if ((LunarCalendarTable[year - 1901] & (0x80000 >> (index - 1))) == 0)
            StaticDayCount = 29;
        else
            StaticDayCount = 30;
        while (Spring_NY > StaticDayCount)
        {
            Spring_NY -= StaticDayCount;
            index--;
            if (flag == 0)
                month--;
            if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
                flag = ~flag;
            if ((LunarCalendarTable[year - 1901] & (0x80000 >> (index - 1))) == 0)
                StaticDayCount = 29;
            else
                StaticDayCount = 30;
        }
        day = StaticDayCount - Spring_NY + 1;
    }
    LunarCalendarDay |= day;
    LunarCalendarDay |= (month << 6);
    if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
        return 1;
    else
        return 0;
}

int Lunar::GetOriginalSource(int year, int month, int day)
{
    LunarCalendarDay = 0;
    LunarCalendar(year, month, day);
    return LunarCalendarDay;
}

LunarDate Lunar::GetLunarDate(int year, int month, int day)
{
    LunarDate lunardate;
    lunardate.Day = 0;
    lunardate.Month = 0;
    lunardate.IsLeap = false;
    if ((year < 1901) || (year > 2099))
        return lunardate;
    if ((month <= 0) || (month > 12)) 
        return lunardate;
    if ((month == 2) && ((day <= 0) || (day > 29)))
        return lunardate;
    else if (((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12)) && ((day <= 0) || (day > 31)))
        return lunardate;
    else if (((month == 4) || (month == 6) || (month == 9) || (month == 11)) && ((day <= 0) || (day > 30))) 
        return lunardate;
    LunarCalendarDay = 0;
    lunardate.IsLeap = LunarCalendar(year, month, day);
    lunardate.Month = (LunarCalendarDay & 0x3C0) >> 6;
    lunardate.Day = (LunarCalendarDay & 0x3F);
    return lunardate;
}

std::string Lunar::GetString(LunarDate ld)
{
    const std::string ChDay[] = { "*","初一","初二","初三","初四","初五",
                           "初六","初七","初八","初九","初十",
                           "十一","十二","十三","十四","十五",
                           "十六","十七","十八","十九","二十",
                           "廿一","廿二","廿三","廿四","廿五",
                           "廿六","廿七","廿八","廿九","三十"
    };
    const std::string ChMonth[] = { "*","正","二","三","四","五","六","七","八","九","十","冬","腊" };
    std::string cr = ((ld.IsLeap) ? "閏" : "") + ChDay[ld.Month] + "月" + ChMonth[ld.Day];
    return cr;
}

bool Lunar::IsLeap(int year, int month, int day)
{
    LunarCalendarDay = 0;
    return LunarCalendar(year, month, day);
}

int main()
{
    const char* ChDay[] = { "*","初一","初二","初三","初四","初五",
                           "初六","初七","初八","初九","初十",
                           "十一","十二","十三","十四","十五",
                           "十六","十七","十八","十九","二十",
                           "廿一","廿二","廿三","廿四","廿五",
                           "廿六","廿七","廿八","廿九","三十"
    };
    const char* ChMonth[] = { "*","正","二","三","四","五","六","七","八","九","十","冬","腊" };
    struct tm* Local;
    long t;
    int year, month, day;
    char str[13] = "";
    std::cout << "Input the time(yyyy mm dd):";
    std::cin >> year >> month >> day;
    Lunar l;
    LunarDate ld = l.GetLunarDate(year, month, day);
    std::cout << ((ld.IsLeap == true) ? "閏" : "") << ChMonth[ld.Month] << "月" << ChDay[ld.Day] << std::endl;
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
