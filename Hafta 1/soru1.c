#include <stdio.h>

int main()
{
    int n = 10;
    int dizi[10];

    printf("Lutfen dizinin 10 elemanini giriniz:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. eleman: ", i + 1);
        scanf("%d", &dizi[i]);
    }

    printf("\nGirdiginiz elemanlar:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", dizi[i]);
    }
    printf("\n");

    return 0;
}

/*
Zaman Maliyeti: Programda ardışık iki adet döngü bulunmaktadır. İlk döngü kullanıcıdan veri almak için "n" defa, ikinci döngü ise verileri yazdırmak için "n" defa çalışır. Döngü değişkeninin atanması, koşul kontrolü ve artırma işlemleri sabit zamanlıdır. Genel toplamda "n" eleman için gerçekleştirilen işlem sayısı "n" ile doğru orantılıdır.

Zaman Karmaşıklığı: Zaman maliyeti denklemi T(n) içindeki en büyük dereceli değişken "n"dir. Big-O gösteriminde katsayılar ve sabit değerler ihmal edildiği için programın zaman karmaşıklığı O(n) olarak ifade edilir.

Alan Karmaşıklığı: Program, "n" adet tamsayı tutan bir dizi ve i gibi birkaç adet ekstra tamsayı değişkeni barındırır. Dizideki eleman sayısını temsil eden "n" arttıkça bellekte ayrılması gereken alan da aynı oranda doğrusal olarak artar. Bu nedenle programın alan karmaşıklığı O(n) seviyesindedir.
*/