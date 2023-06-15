# LunarMonthCalender

## C++ 部分

~~全局变量`LunarCalenderDay`用于存储农历日期, 其中, 第6\~9个比特位为月份, 第0\~5个比特位为日期(从低至高数)~~  
~~函数`LunarCalender(int year, int month, int day)`用于判断是否为闰月, 并将公历日期转化为农历日期(存储在`LunarCalenderDay`中)~~  

~~也可以封装一个类使其能够直接返回农历日期, 并且可读性更高~~  

已经封装成类了  
现在的用法是:直接声明一个`Lunar`类项然后`GetLunarDate(int year, int month, int day)`
``` c++
Lunar l;
LunarDate ld = l.GetLunarDate(2022, 7, 19);
```


## C# 部分

C#部分存在一个名为`Lunar`的类, 其内部定义的函数可以将公历日期转化为农历日期, 或者其他形式的日期  
例如, 可以使用下面的代码块获取农历日期:  
```csharp
Lunar.LunarDate ld = new Lunar.GetLunarDate(2022, 3, 29);
```
或者使用下面的代码块直接获取当日农历日期:
```csharp
Lunar.LunarDate ld = Lunar.GetLunarDate();
```
其中, `LunarDate`类中的属性`Month`为农历月, `Day`为农历日, `IsLeap`为是否为闰月, 其定义如下(`Program.cs`中也有):
```csharp
public struct LunarDate
{
    public int Month;
    public int Day;
    public bool IsLeap;
}
```

同样, 也可以使用下面的代码块确定某个日期是否在农历的闰月中:
```csharp
bool isLeapMonth = Lunar.IsLeap(2022, 3, 29);
```
或者使用下面的代码块直接获取当日时候在农历的闰月中:
```csharp
bool isLeapMonth = Lunar.IsLeap();
```

除此以外, 还可以使用下面的代码块直接获取当前日期的农历日期的字符串表示: 
```csharp
string ldstr = Lunar.GetString(Lunar.Lang.Chinese, 2022, 3, 29);
```

## Java 部分

存在一个名为`LunarMonthCalendar`的类, 可将公历日期转化为农历日期.  
例如:  

``` java
LunarMonthCalendar.LunarDate ld = new LunarMonthCalendar.LunarDate();
ld = LunarMonthCalendar.GetLunarDate(2000, 4, 5);
```
其中`LunarDate`类中的属性`Month`为农历月, `Day`为农历日, `IsLeap`为是否为闰月. 定义如下:  

```java
public static class LunarDate {
    public int Month;
    public int Day;
    public boolean IsLeap;
}
```

也可使用单一`IsLeap()`判定是否为闰月  

```java
boolean isleap = LunarMonthCalendar.IsLeap(2000, 4, 5);
```

## Kotlin 部分

直接运行就行

## Python 部分

直接运行就行  
不要瞎改  
