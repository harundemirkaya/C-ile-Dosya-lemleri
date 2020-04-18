#include <stdio.h>
FILE *output; // Output dosyamızı main fonksiyonundan farklı bir fonksiyondada(romen) kullanacağımız için Global olarak tanımlıyoruz.
int romen(int sayi,FILE *output){
    int decimal[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1}; // Temel değerleri tanımlıyoruz.
    char *symbol[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"}; // Temel değerlere karşılık gelecek roma sembollerini tanımlıyoruz.
    int i = 0; // Döngülerde kullanılacak sayacımızı tanımlıyoruz.
    while(sayi){ // Decimal türünden roma türüne çevirme işlemlerimizi bu döngü içerisinde gerçekleştiriyoruz.
        while(sayi/decimal[i]){ 
            fprintf(output,"%s",symbol[i]); 
			sayi -= decimal[i];
        }
        i++; // Sayacımızı 1 arttırarak döngümüzün ilerlemesini ve en sonunda durmasını sağlıyoruz.
    }
}
int main() {
	//Dosyalarımızı tanımlıyoruz.
	FILE *input;
	input = fopen("input.txt","r");
	output = fopen("output.txt","w+");
	char c = fgetc(input); // C değişkeni tanımlayarak input dosyasındaki verileri karakter karakter okumak için ilk karakterden başlatıyoruz.
	int b=1; // İlk kelimeyi sayabilmemiz için tutulacak değişken. Yalnızca 1 defa kullanılacak ve kendini imha edecek.
	int i=0,kelimesay=0,paragrafsay=0,romensay=0; // Sayaçlarımızı tanımlıyoruz.
    int count[26] = {0}; // Harflerimizi saymamız için harf sayacı değişkenini tanımlıyoruz.
	int sayi=0; // Roma rakamına çevireceğimiz sayıyı bu değişkende tutup fonksiyona göndereceğiz.
	while(c!=EOF){ // Metin belgesinin sonuna gelene kadar dönecek.
		if(c==' '){ // Eğer aralarda boşluk varsa kelime olarak algılasın. Fakat kelime saymak için sadece bu algoritmayı kullanmıyoruz. Aşağıda algoritmayı geliştiriyoruz.
			kelimesay++;
		}
    if (c >= 'a' && c <= 'z'){ // Karakterimizin hangi harften olduğunu bulmak için döngüye sokuyoruz.
        count[c-'a']++; // Karakterimizin harf olarak algılanabilmesi için karakterimizden 'a' yı çıkarıyoruz. Eğer kullanmazsak çalışmaz. Çalışırsa doğru sonuç vermez.
	}
	if(c >= 'A' && c <= 'Z'){  // Yukarıda küçük harf tanımlaması için döngüye soktuk. Şimdide büyük harf tanımlaması için döngüye sokuyoruz.
		count[c-'A']++;
	}
	if(c=='\n'){	// Eğer alt satıra geçiyorsa bir sonraki karaktere baksın. Oda alt satıra geçmişse paragrafı 1 arttırsın.
		int c1 = fgetc(input);
		if(c1=='\n'){
		paragrafsay++;
		int c2=fgetc(input); // Bir diğer karaktere bakılsın. Eğer isalpha ise kelimeyi 2 arttırsın.(1 arttırırsak en sonda 1 sayı eksik sayıyor.)
		if(isalpha(c2)) kelimesay += 2;
		}
			if(isalpha(c1))
				kelimesay++; // İlk arttırdığımız karakter alt satır değilde isalpha ise direk kelimeyi 1 arttırsın.
		}
	char x; // Sayıyı tutmak için kullanacağız.
	if(isdigit(c)){ // Eğer karakterimiz sayı ise sayi değişkenine eklesin. 10 ile çarpsın. Girilen sayıları sürekli üstüne ekleyip tek bir sayı haline getirsin.
		x = c-'0';  // Böylelikle birleşik girilen sayıları tek bir sayı yapacak. 10 ile fazladan çarpılmış sayıyı fonksiyona sokmadan 10'a böldük. 
		sayi += x;
		sayi *= 10;
	}
	else {		// Eğer karakterimiz isdigit değilse;
		while(b!=0){	// Bu kısım yalnızca bir kere dönüp kendini imha edecek.
			kelimesay++; //  İlk kelimenin varlığını kontrol edip kelime ve paragraf sayısını bir kereliğie arttıracak.
			paragrafsay++;
			b--; // B değişkeni kendini bir azaltıp döngünün birdaha kullanılmamasını sağlıyor.
		}
		if(sayi != 0) { // Bu kısımda elde ettiğimiz sayıyı romen fonksiyonuna göndererek sayıyı romen sayıya çeviriyoruz.
			romensay++; // Kaç adet sayıyı roma rakamına çevirdiğimizi bir değişkende tutuyoruz.
			sayi /= 10; // Formülde 10 ile sürekli çarpmamız gerektiğinden son çarpımda fazladan 10 ile çarptık. Bu yüzden en son 10'a bölüyoruz.
			romen(sayi,output); // Sayıyı fonksiyona göndererek roma rakamına çevirme işlemini gerçekleştirdik.
			sayi=0; // Sayı değişkenini sıfırlayarak tekrardan kullanılmasını sağladık.
		}
	}
	if(isdigit(c)); // Roma rakamlarından sonra sayıyı tekrar yazdırmaması için isaplha şartı koyduk.
	else fprintf(output,"%c",c); // Burada input dosyasından okuduğumuz karakterleri output dosyasına yazdırdık.
	c = fgetc(input); // Burada döngünün ilerleyebilmesi için sürekli c değişkenine bir sonraki karakteri atıyoruz. Taki input dosyamızın tamamı okunana kadar.
	}
	// Output dosyamızın en altına toplam kelime sayısını, paragraf sayısını ve roma rakamına çevirdiğimiz sayı adedini yazıyoruz.
	printf("Succesfully !");
	fprintf(output,"\n\nKelime : %d\n",kelimesay);
	fprintf(output,"Paragraf : %d\n",paragrafsay);
	fprintf(output,"Cevrilen : %d",romensay);
	for (c = 0; c < 26; c++){
    	if (count[c] != 0)
        fprintf(output,"\n%c harfinden %d kez kullanıldı.",c+'a',count[c]);
    }
	// Açmış olduğumuz dosyaları kapatıyoruz.
	fclose(input);
	fclose(output);
	return 0;
}
