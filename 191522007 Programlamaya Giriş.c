#include <stdio.h>
FILE *output; // Output dosyamýzý main fonksiyonundan farklý bir fonksiyondada(romen) kullanacaðýmýz için Global olarak tanýmlýyoruz.
int romen(int sayi,FILE *output){
    int decimal[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1}; // Temel deðerleri tanýmlýyoruz.
    char *symbol[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"}; // Temel deðerlere karþýlýk gelecek roma sembollerini tanýmlýyoruz.
    int i = 0; // Döngülerde kullanýlacak sayacýmýzý tanýmlýyoruz.
    while(sayi){ // Decimal türünden roma türüne çevirme iþlemlerimizi bu döngü içerisinde gerçekleþtiriyoruz.
        while(sayi/decimal[i]){ 
            fprintf(output,"%s",symbol[i]); 
			sayi -= decimal[i];
        }
        i++; // Sayacýmýzý 1 arttýrarak döngümüzün ilerlemesini ve en sonunda durmasýný saðlýyoruz.
    }
}
int main() {
	//Dosyalarýmýzý tanýmlýyoruz.
	FILE *input;
	input = fopen("input.txt","r");
	output = fopen("output.txt","w+");
	char c = fgetc(input); // C deðiþkeni tanýmlayarak input dosyasýndaki verileri karakter karakter okumak için ilk karakterden baþlatýyoruz.
	int b=1; // Ýlk kelimeyi sayabilmemiz için tutulacak deðiþken. Yalnýzca 1 defa kullanýlacak ve kendini imha edecek.
	int i=0,kelimesay=0,paragrafsay=0,romensay=0; // Sayaçlarýmýzý tanýmlýyoruz.
    int count[26] = {0}; // Harflerimizi saymamýz için harf sayacý deðiþkenini tanýmlýyoruz.
	int sayi=0; // Roma rakamýna çevireceðimiz sayýyý bu deðiþkende tutup fonksiyona göndereceðiz.
	while(c!=EOF){ // Metin belgesinin sonuna gelene kadar dönecek.
		if(c==' '){ // Eðer aralarda boþluk varsa kelime olarak algýlasýn. Fakat kelime saymak için sadece bu algoritmayý kullanmýyoruz. Aþaðýda algoritmayý geliþtiriyoruz.
			kelimesay++;
		}
    if (c >= 'a' && c <= 'z'){ // Karakterimizin hangi harften olduðunu bulmak için döngüye sokuyoruz.
        count[c-'a']++; // Karakterimizin harf olarak algýlanabilmesi için karakterimizden 'a' yý çýkarýyoruz. Eðer kullanmazsak çalýþmaz. Çalýþýrsa doðru sonuç vermez.
	}
	if(c >= 'A' && c <= 'Z'){  // Yukarýda küçük harf tanýmlamasý için döngüye soktuk. Þimdide büyük harf tanýmlamasý için döngüye sokuyoruz.
		count[c-'A']++;
	}
	if(c=='\n'){	// Eðer alt satýra geçiyorsa bir sonraki karaktere baksýn. Oda alt satýra geçmiþse paragrafý 1 arttýrsýn.
		int c1 = fgetc(input);
		if(c1=='\n'){
		paragrafsay++;
		int c2=fgetc(input); // Bir diðer karaktere bakýlsýn. Eðer isalpha ise kelimeyi 2 arttýrsýn.(1 arttýrýrsak en sonda 1 sayý eksik sayýyor.)
		if(isalpha(c2)) kelimesay += 2;
		}
			if(isalpha(c1))
				kelimesay++; // Ýlk arttýrdýðýmýz karakter alt satýr deðilde isalpha ise direk kelimeyi 1 arttýrsýn.
		}
	char x; // Sayýyý tutmak için kullanacaðýz.
	if(isdigit(c)){ // Eðer karakterimiz sayý ise sayi deðiþkenine eklesin. 10 ile çarpsýn. Girilen sayýlarý sürekli üstüne ekleyip tek bir sayý haline getirsin.
		x = c-'0';  // Böylelikle birleþik girilen sayýlarý tek bir sayý yapacak. 10 ile fazladan çarpýlmýþ sayýyý fonksiyona sokmadan 10'a böldük. 
		sayi += x;
		sayi *= 10;
	}
	else {		// Eðer karakterimiz isdigit deðilse;
		while(b!=0){	// Bu kýsým yalnýzca bir kere dönüp kendini imha edecek.
			kelimesay++; //  Ýlk kelimenin varlýðýný kontrol edip kelime ve paragraf sayýsýný bir kereliðie arttýracak.
			paragrafsay++;
			b--; // B deðiþkeni kendini bir azaltýp döngünün birdaha kullanýlmamasýný saðlýyor.
		}
		if(sayi != 0) { // Bu kýsýmda elde ettiðimiz sayýyý romen fonksiyonuna göndererek sayýyý romen sayýya çeviriyoruz.
			romensay++; // Kaç adet sayýyý roma rakamýna çevirdiðimizi bir deðiþkende tutuyoruz.
			sayi /= 10; // Formülde 10 ile sürekli çarpmamýz gerektiðinden son çarpýmda fazladan 10 ile çarptýk. Bu yüzden en son 10'a bölüyoruz.
			romen(sayi,output); // Sayýyý fonksiyona göndererek roma rakamýna çevirme iþlemini gerçekleþtirdik.
			sayi=0; // Sayý deðiþkenini sýfýrlayarak tekrardan kullanýlmasýný saðladýk.
		}
	}
	if(isdigit(c)); // Roma rakamlarýndan sonra sayýyý tekrar yazdýrmamasý için isaplha þartý koyduk.
	else fprintf(output,"%c",c); // Burada input dosyasýndan okuduðumuz karakterleri output dosyasýna yazdýrdýk.
	c = fgetc(input); // Burada döngünün ilerleyebilmesi için sürekli c deðiþkenine bir sonraki karakteri atýyoruz. Taki input dosyamýzýn tamamý okunana kadar.
	}
	// Output dosyamýzýn en altýna toplam kelime sayýsýný, paragraf sayýsýný ve roma rakamýna çevirdiðimiz sayý adedini yazýyoruz.
	printf("Succesfully !");
	fprintf(output,"\n\nKelime : %d\n",kelimesay);
	fprintf(output,"Paragraf : %d\n",paragrafsay);
	fprintf(output,"Cevrilen : %d",romensay);
	for (c = 0; c < 26; c++){
    	if (count[c] != 0)
        fprintf(output,"\n%c harfinden %d kez kullanýldý.",c+'a',count[c]);
    }
	// Açmýþ olduðumuz dosyalarý kapatýyoruz.
	fclose(input);
	fclose(output);
	return 0;
}
