#include <stdio.h>
FILE *output; // Output dosyam�z� main fonksiyonundan farkl� bir fonksiyondada(romen) kullanaca��m�z i�in Global olarak tan�ml�yoruz.
int romen(int sayi,FILE *output){
    int decimal[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1}; // Temel de�erleri tan�ml�yoruz.
    char *symbol[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"}; // Temel de�erlere kar��l�k gelecek roma sembollerini tan�ml�yoruz.
    int i = 0; // D�ng�lerde kullan�lacak sayac�m�z� tan�ml�yoruz.
    while(sayi){ // Decimal t�r�nden roma t�r�ne �evirme i�lemlerimizi bu d�ng� i�erisinde ger�ekle�tiriyoruz.
        while(sayi/decimal[i]){ 
            fprintf(output,"%s",symbol[i]); 
			sayi -= decimal[i];
        }
        i++; // Sayac�m�z� 1 artt�rarak d�ng�m�z�n ilerlemesini ve en sonunda durmas�n� sa�l�yoruz.
    }
}
int main() {
	//Dosyalar�m�z� tan�ml�yoruz.
	FILE *input;
	input = fopen("input.txt","r");
	output = fopen("output.txt","w+");
	char c = fgetc(input); // C de�i�keni tan�mlayarak input dosyas�ndaki verileri karakter karakter okumak i�in ilk karakterden ba�lat�yoruz.
	int b=1; // �lk kelimeyi sayabilmemiz i�in tutulacak de�i�ken. Yaln�zca 1 defa kullan�lacak ve kendini imha edecek.
	int i=0,kelimesay=0,paragrafsay=0,romensay=0; // Saya�lar�m�z� tan�ml�yoruz.
    int count[26] = {0}; // Harflerimizi saymam�z i�in harf sayac� de�i�kenini tan�ml�yoruz.
	int sayi=0; // Roma rakam�na �evirece�imiz say�y� bu de�i�kende tutup fonksiyona g�nderece�iz.
	while(c!=EOF){ // Metin belgesinin sonuna gelene kadar d�necek.
		if(c==' '){ // E�er aralarda bo�luk varsa kelime olarak alg�las�n. Fakat kelime saymak i�in sadece bu algoritmay� kullanm�yoruz. A�a��da algoritmay� geli�tiriyoruz.
			kelimesay++;
		}
    if (c >= 'a' && c <= 'z'){ // Karakterimizin hangi harften oldu�unu bulmak i�in d�ng�ye sokuyoruz.
        count[c-'a']++; // Karakterimizin harf olarak alg�lanabilmesi i�in karakterimizden 'a' y� ��kar�yoruz. E�er kullanmazsak �al��maz. �al���rsa do�ru sonu� vermez.
	}
	if(c >= 'A' && c <= 'Z'){  // Yukar�da k���k harf tan�mlamas� i�in d�ng�ye soktuk. �imdide b�y�k harf tan�mlamas� i�in d�ng�ye sokuyoruz.
		count[c-'A']++;
	}
	if(c=='\n'){	// E�er alt sat�ra ge�iyorsa bir sonraki karaktere baks�n. Oda alt sat�ra ge�mi�se paragraf� 1 artt�rs�n.
		int c1 = fgetc(input);
		if(c1=='\n'){
		paragrafsay++;
		int c2=fgetc(input); // Bir di�er karaktere bak�ls�n. E�er isalpha ise kelimeyi 2 artt�rs�n.(1 artt�r�rsak en sonda 1 say� eksik say�yor.)
		if(isalpha(c2)) kelimesay += 2;
		}
			if(isalpha(c1))
				kelimesay++; // �lk artt�rd���m�z karakter alt sat�r de�ilde isalpha ise direk kelimeyi 1 artt�rs�n.
		}
	char x; // Say�y� tutmak i�in kullanaca��z.
	if(isdigit(c)){ // E�er karakterimiz say� ise sayi de�i�kenine eklesin. 10 ile �arps�n. Girilen say�lar� s�rekli �st�ne ekleyip tek bir say� haline getirsin.
		x = c-'0';  // B�ylelikle birle�ik girilen say�lar� tek bir say� yapacak. 10 ile fazladan �arp�lm�� say�y� fonksiyona sokmadan 10'a b�ld�k. 
		sayi += x;
		sayi *= 10;
	}
	else {		// E�er karakterimiz isdigit de�ilse;
		while(b!=0){	// Bu k�s�m yaln�zca bir kere d�n�p kendini imha edecek.
			kelimesay++; //  �lk kelimenin varl���n� kontrol edip kelime ve paragraf say�s�n� bir kereli�ie artt�racak.
			paragrafsay++;
			b--; // B de�i�keni kendini bir azalt�p d�ng�n�n birdaha kullan�lmamas�n� sa�l�yor.
		}
		if(sayi != 0) { // Bu k�s�mda elde etti�imiz say�y� romen fonksiyonuna g�ndererek say�y� romen say�ya �eviriyoruz.
			romensay++; // Ka� adet say�y� roma rakam�na �evirdi�imizi bir de�i�kende tutuyoruz.
			sayi /= 10; // Form�lde 10 ile s�rekli �arpmam�z gerekti�inden son �arp�mda fazladan 10 ile �arpt�k. Bu y�zden en son 10'a b�l�yoruz.
			romen(sayi,output); // Say�y� fonksiyona g�ndererek roma rakam�na �evirme i�lemini ger�ekle�tirdik.
			sayi=0; // Say� de�i�kenini s�f�rlayarak tekrardan kullan�lmas�n� sa�lad�k.
		}
	}
	if(isdigit(c)); // Roma rakamlar�ndan sonra say�y� tekrar yazd�rmamas� i�in isaplha �art� koyduk.
	else fprintf(output,"%c",c); // Burada input dosyas�ndan okudu�umuz karakterleri output dosyas�na yazd�rd�k.
	c = fgetc(input); // Burada d�ng�n�n ilerleyebilmesi i�in s�rekli c de�i�kenine bir sonraki karakteri at�yoruz. Taki input dosyam�z�n tamam� okunana kadar.
	}
	// Output dosyam�z�n en alt�na toplam kelime say�s�n�, paragraf say�s�n� ve roma rakam�na �evirdi�imiz say� adedini yaz�yoruz.
	printf("Succesfully !");
	fprintf(output,"\n\nKelime : %d\n",kelimesay);
	fprintf(output,"Paragraf : %d\n",paragrafsay);
	fprintf(output,"Cevrilen : %d",romensay);
	for (c = 0; c < 26; c++){
    	if (count[c] != 0)
        fprintf(output,"\n%c harfinden %d kez kullan�ld�.",c+'a',count[c]);
    }
	// A�m�� oldu�umuz dosyalar� kapat�yoruz.
	fclose(input);
	fclose(output);
	return 0;
}
