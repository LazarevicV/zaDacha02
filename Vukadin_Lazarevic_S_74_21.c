#include <stdio.h>
#include <stdlib.h>

typedef struct Korisnik
{
	char korisnicko_ime[40], sifra[40], email[40];
	int godina_rodjenja;
	float stanje_racuna;
}Korisnik;

Korisnik unesi_korisnika()
{
	Korisnik korisnik;
	printf("Unesite korisnicko ime:");
	fflush(stdin);
	gets(korisnik.korisnicko_ime);
	printf("Unesite email:");
	gets(korisnik.email);
	printf("Unesite sifru: ");
	gets(korisnik.sifra);
	printf("Unesite stanje na racunu:");
	scanf("%f", &korisnik.stanje_racuna);
	printf("Unesite godinu rodjenja:");
	scanf("%d", &korisnik.godina_rodjenja);
	return korisnik;
}

void ispisi_korisnika(Korisnik korisnik)
{
	printf("\nKorisnicko ime: %s\n",korisnik.korisnicko_ime);
	printf("Email: %s\n", korisnik.email);
	printf("Stanja racuna: %.2f\n", korisnik.stanje_racuna);
	printf("Godinja rodjenja: %d\n\n",korisnik.godina_rodjenja);
}

void ispisi_niz_korisnika(Korisnik niz[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Ispis %d. korisnika\n",i+1);
		ispisi_korisnika(niz[i]);
	}
}

void skini_novi_red_stringu(char tekst[])
{
	int n = strlen(tekst);
	tekst[n-1] = '\0';
}

int ucitaj_niz_iz_fajla(Korisnik niz[], const char naziv_fajla[])
{
	int brojac = 0;
	FILE *ulazni = fopen(naziv_fajla,"r");
	if (ulazni == NULL)
	{
		return 0;
	}
	Korisnik korisnik;
	while (!feof(ulazni))
	{
		fgets(korisnik.korisnicko_ime,40,ulazni);
		fgets(korisnik.email,40,ulazni);
		fgets(korisnik.sifra,40,ulazni);
		fscanf(ulazni, "%f\n", &korisnik.stanje_racuna);
		fscanf(ulazni, "%d\n", &korisnik.godina_rodjenja);

		skini_novi_red_stringu(korisnik.korisnicko_ime);
		skini_novi_red_stringu(korisnik.email);
		skini_novi_red_stringu(korisnik.sifra);
		niz[brojac] = korisnik;
		brojac++;
	}
	fclose(ulazni);
	return brojac;
}

int da_li_postoji_username(Korisnik niz[], int n, const char username[])
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(niz[i].korisnicko_ime, username) == 0)
			return 1;
		else return 0;
	}
}

int registruj_se(Korisnik niz[],int n)
{
	char potvrda_sifre[40];
	Korisnik korisnik = unesi_korisnika();
	printf("potvrdite sifru: ");
	fflush(stdin);
	gets(potvrda_sifre);
	for (int i = 0; i < n; i++)
	{
		if (strcmp(niz[i].korisnicko_ime,korisnik.korisnicko_ime) == 0)
		{
			printf("\nVec postoji korisnik sa istim korisnickim imenom!\n\n");
			return 0;
		}
		else if (strcmp(korisnik.sifra,potvrda_sifre) != 0)
		{
			printf("\nSifra nije dobra!\n\n");
			return 0;
		}
	}
	niz[n] = korisnik;
	return 1;
}

int login(Korisnik niz[], int n,const char korisnicko_ime[], const char sifra[])
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(niz[i].korisnicko_ime,korisnicko_ime) == 0 && strcmp(niz[i].sifra,sifra) == 0)
		{
			printf("\nUspesno ste se ulogovali!\n");
			return 1;
		}
	}
	printf("\nNiste se ulogovali!\n");
	return 0;
}

void snimi_u_fajl(Korisnik niz[], int n, const char naziv_fajla[])
{
	FILE *izlazni = fopen(naziv_fajla,"w");
	for (int i = 0; i < n; i++)
	{
		fprintf(izlazni, "%s\n", niz[i].korisnicko_ime);
		fprintf(izlazni, "%s\n", niz[i].email);
		fprintf(izlazni, "%s\n", niz[i].sifra);
		fprintf(izlazni, "%f\n", niz[i].stanje_racuna);
		fprintf(izlazni, "%d\n", niz[i].godina_rodjenja);
	}
	fclose(izlazni);
}

int main()
{
	Korisnik niz[50];
	int duzina_niza = ucitaj_niz_iz_fajla(niz, "korisnik.txt");
	while(1)
	{
		int opcija;
		printf("Izaberite opciju:\n");
		printf("Opcija 1 - Registracija\n");
		printf("Opcija 2 - Login\n");
		printf("Opcija 3 - Ispis svih korisnika\n");
		printf("Opcija 4 - Snimanje u fajl i kraj rada\n");
		printf("Opcija 5 - Da li postoji username\n");
		printf("Unesite opciju:");
		scanf("%d", &opcija);
		if (opcija == 1)
		{
			int provera = registruj_se(niz, duzina_niza);
			if (provera == 1)
			{
				printf("\nKorisnik je unesen u niz\n");
				duzina_niza++;
			}
		}
		else if (opcija == 2)
		{
			int korisnicko_ime[40], sifra[40];
			printf("Unesite korisnicko ime:");
			fflush(stdin);
			gets(korisnicko_ime);
			printf("Unesite sifru:");
			gets(sifra);
			login(niz, duzina_niza, korisnicko_ime, sifra);
		}
		else if (opcija == 3)
		{
			ispisi_niz_korisnika(niz, duzina_niza);
		}
		else if (opcija == 4)
		{
			snimi_u_fajl(niz, duzina_niza,"korisnik.txt");
			return 0;
		}
		else if (opcija == 5)
		{
			char korisnicko_ime;
			printf("Unesite username za proveru: ");
			fflush(stdin);
			gets(korisnicko_ime);
			int n = da_li_postoji_username(niz, duzina_niza, korisnicko_ime);
			if (n == 1)
			{
				printf("\nusername postoji!\n");
			}
			else if (n == 0)
				printf("\nusername ne postoji\n");
		}
		else
        {
            printf("\nNiste uneli postojecu opciju, probajte ponovo!\n\n");
        }
	}
	if (duzina_niza == 0)
        printf("fajl nije povezan");
	return 0;
}
