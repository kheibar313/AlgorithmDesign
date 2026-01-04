این خروجی حاصل **۲۵۰ تست‌کیس** برای **۶ الگوریتم مرتب‌سازی** است که در درس طراحی الگوریتم
مطالعه کرده‌ایم 🧠📊

## نکات پیاده‌سازی
1. در پیاده‌سازی هر الگوریتم، صرفاً از خود همان الگوریتم استفاده شده است.  
   حتی برای مرتب‌سازی دو عدد نیز هیچ مقایسه‌ی ساده‌ی مستقیم (> یا <) انجام نشده،
   چون چنین کاری عملاً یک بهینه‌سازی خارج از چارچوب الگوریتم (مثلاً شبیه insertion sort)
   محسوب می‌شود. آگاهانه از این بهینه‌سازی‌ها صرف‌نظر شده تا «خود الگوریتم» سنجیده شود،
   نه زرنگی پیاده‌سازی.

2. راهنمای دیتا:
   - `start` و `end` بازه‌ی اعداد هر لیست هستند.
   - در هر بازه، **۲۵۰ لیست با جایگشت‌های متفاوت** تولید شده است.
   - نمونه‌ی یک لیست در بازه‌ی ۱۰ تا ۲۰:
     `{10, 14, 13, 19, 20, 18, 12, 11, 16, 17, 15}`


## خروجی تست‌ها (زمان بر حسب ns)

```
Number of repet: 250
Enter start: 1
Enter end: 10
Sort[0]: Insertion Sort              176500
Sort[1]: Bubble Sort                 317400
Sort[2]: Selection Sort              364600
Sort[3]: Quick Sort                  615300
Sort[4]: Heap Sort                   691700
Sort[5]: Merge Sort                 2577400


Number of repet: 250
Enter start: 10
Enter end: 20
Sort[0]: Insertion Sort              613400
Sort[1]: Bubble Sort                2074500
Sort[2]: Selection Sort             2148400
Sort[3]: Quick Sort                 2310900
Sort[4]: Heap Sort                  2978900
Sort[5]: Merge Sort                10729200


Number of repet: 250
Enter start: 20
Enter end: 30
Sort[0]: Insertion Sort             1288900
Sort[1]: Quick Sort                 3926800
Sort[2]: Selection Sort             4808800
Sort[3]: Bubble Sort                5119900
Sort[4]: Heap Sort                  5801600
Sort[5]: Merge Sort                16913800


Number of repet: 250
Enter start: 30
Enter end: 40
Sort[0]: Insertion Sort             2624900
Sort[1]: Quick Sort                 7394500
Sort[2]: Selection Sort            10994300
Sort[3]: Heap Sort                 11501500
Sort[4]: Bubble Sort               11664100
Sort[5]: Merge Sort                31763200


Number of repet: 250
Enter start: 40
Enter end: 50
Sort[0]: Insertion Sort             2805900
Sort[1]: Quick Sort                 6867300
Sort[2]: Heap Sort                 11134000
Sort[3]: Bubble Sort               13561000
Sort[4]: Selection Sort            13575700
Sort[5]: Merge Sort                29016600


Number of repet: 250
Enter start: 50
Enter end: 75
Sort[0]: Insertion Sort            11470600
Sort[1]: Quick Sort                25097200
Sort[2]: Heap Sort                 42590400
Sort[3]: Selection Sort            56506600
Sort[4]: Bubble Sort               66597600
Sort[5]: Merge Sort               101548900


Number of repet: 250
Enter start: 75
Enter end: 100
Sort[0]: Insertion Sort            23811500
Sort[1]: Quick Sort                37194200
Sort[2]: Heap Sort                 66899300
Sort[3]: Selection Sort           104544000
Sort[4]: Bubble Sort              122974400
Sort[5]: Merge Sort               152297300


Number of repet: 250
Enter start: 100
Enter end: 150
Sort[0]: Insertion Sort            73357100
Sort[1]: Quick Sort               112582900
Sort[2]: Heap Sort                204309200
Sort[3]: Selection Sort           420652400
Sort[4]: Merge Sort               426541200
Sort[5]: Bubble Sort              501425900


Number of repet: 250
Enter start: 150
Enter end: 200
Sort[0]: Insertion Sort           145519800
Sort[1]: Quick Sort               164486000
Sort[2]: Heap Sort                310940000
Sort[3]: Merge Sort               634289000
Sort[4]: Selection Sort           789563100
Sort[5]: Bubble Sort              979495000


Number of repet: 250
Enter start: 200
Enter end: 300
Sort[0]: Insertion Sort           484140600
Sort[1]: Quick Sort               497139400
Sort[2]: Heap Sort                941219200
Sort[3]: Merge Sort              1776404300
Sort[4]: Selection Sort          3162794000
Sort[5]: Bubble Sort             4039719400
```


## برداشت‌ها 🔍
1. تعداد عناصر لیست، تأثیر مستقیم و بسیار جدی روی زمان اجرا دارد.
2. ترکیب چند متد مرتب‌سازی (برای مدیریت حافظه و کاهش فراخوانی‌ها) در عمل مزیت محسوسی دارد.
3. در پیاده‌سازی، باید فراخوانی تابع را به حداقل رساند و بیشتر به حلقه‌ها تکیه کرد.
4. اگر فقط یک الگوریتم و بدون هیچ بهینه‌سازی خاصی انتخاب شود،  
   **Insertion Sort برنده‌ی این تست‌هاست** 🎉
5. از حدود اندازه‌ی ۳۰ به بعد، **Bubble Sort** عملاً از **Quick Sort** عقب می‌افتد.

### نکته‌ی جالب ⚠️
با وجود هزینه‌ی فراخوانی تابع، باز هم **Bubble Sort** و **Selection Sort** نسبت به  
**Heap Sort** و **Merge Sort** (با recursion و مدیریت حافظه‌ی سنگین) عقب می‌مانند.

## جمع‌بندی 🧩
در عمل:  
**پیچیدگی زمانی بهتر ≠ اجرای سریع‌تر**  
عددها اینجا حرف می‌زنند، نه شعارها.
