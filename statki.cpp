#include<iostream>
#include<string>
#include<limits>
#include<random>

using namespace std;

void ustaw_statki(int plansza[10][10], string komorki[10][10], int ilumasztowiec)
{
	double wktorastrone = 0;
	int pomoctabela = 0, pomocwpisanie = 0;
	string komorka;
	bool sprawdzacz = 0, sprawdzaczkomorka = 0, sprawdzaczsciana = 0;

	// Ustawianie kierunku masztowca
	cout << "W jaki spos�b chcesz ustawi� " << ilumasztowiec << "masztowiec? (1 = w g�r�, 2 = w prawo, 3 = w d�, 4 = w lewo): ";
	cin >> wktorastrone;

	while ((wktorastrone != 1 && wktorastrone != 2 && wktorastrone != 3 && wktorastrone != 4)) // Sprawdzanie, czy u�ytkownik poda� odpowiedni kierunek
	{
		if (!cin)
		{
			cout << "Nie poda�e� liczby! Spr�buj ponownie: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			cout << "Poda�e� niew�a�ciw� liczb�! Spr�buj ponownie: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		cin >> wktorastrone;
	}

	// Ustawianie pierwszej kom�rki masztowca
	cout << "Podaj kom�rk�, w kt�rej chcesz umie�ci� pierwsz� cz�� " << ilumasztowiec << "masztowca (Podaj ma�� liter�, a nast�pnie liczb�, np. d6): ";
	cin >> komorka;

	while (sprawdzacz != 1) // Sprawdzanie, czy wpisana kom�rka jest mo�liwa
	{
		sprawdzacz = 0;
		sprawdzaczkomorka = 0;
		sprawdzaczsciana = 0;
		pomocwpisanie = 0;

		// Sprawdzanie, czy u�ytkownik wpisa� mo�liw� kom�rk�
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (komorka.compare(komorki[i][j]) == 0)
				{
					sprawdzaczkomorka = 1;
					break;
				}
			}
		}

		// Zmiana zmiennnej komorka z np. a1 na a0
		if (komorka.length() == 2)
			komorka = komorka[0] + to_string(stoi(komorka.substr(1, 1)) - 1);
		else
			komorka = komorka[0] + to_string(stoi(komorka.substr(1, 2)) - 1);

		// Sprawdzanie, czy w dan� kom�rk� mo�na wpisa� statek pod wzgl�dem �cian
		if (wktorastrone == 1) // Dla g�ry
		{
			for (int i = ilumasztowiec - 1; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					string a(1, 'a' + j);
					if (komorka == a + to_string(i))
					{
						sprawdzaczsciana = 1;
						break;
					}
				}
			}
		}
		else if (wktorastrone == 2) // Dla prawa
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 11 - ilumasztowiec; j++)
				{
					string a(1, 'a' + j);
					if (komorka == a + to_string(i))
					{
						sprawdzaczsciana = 1;
						break;
					}
				}
			}
		}
		else if (wktorastrone == 3) // Dla do�u
		{
			for (int i = 0; i < 11 - ilumasztowiec; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					string a(1, 'a' + j);
					if (komorka == a + to_string(i))
					{
						sprawdzaczsciana = 1;
						break;
					}
				}
			}
		}
		else if (wktorastrone == 4) // Dla lewa
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = ilumasztowiec - 1; j < 10; j++)
				{
					string a(1, 'a' + j);
					if (komorka == a + to_string(i))
					{
						sprawdzaczsciana = 1;
						break;
					}
				}
			}
		}

		// Sprawdzanie, czy w dan� kom�rk� mo�na wpisa� statek pod wzgl�dem innych statk�w
		if (wktorastrone == 1) // Dla g�ry
		{
			for (int i = 0; i < ilumasztowiec; i++)
			{
				if (plansza[stoi(komorka.substr(1, 1)) - i][static_cast<int>(komorka[0]) - 97] == 0)
					pomocwpisanie++;
			}
		}
		else if (wktorastrone == 2) // Dla prawa
		{
			for (int i = 0; i < ilumasztowiec; i++)
			{
				if (plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 + i] == 0)
					pomocwpisanie++;
			}
		}
		else if (wktorastrone == 3) // Dla do�u
		{
			for (int i = 0; i < ilumasztowiec; i++)
			{
				if (plansza[stoi(komorka.substr(1, 1)) + i][static_cast<int>(komorka[0]) - 97] == 0)
					pomocwpisanie++;
			}
		}
		else if (wktorastrone == 4) // Dla lewa
		{
			for (int i = 0; i < ilumasztowiec; i++)
			{
				if (plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 - i] == 0)
					pomocwpisanie++;
			}
		}

		if (sprawdzaczkomorka == 0)
		{
			cout << "Nie mo�na wpisa� statku w to miejsce, gdy� poda�e� niew�a�ciw� kom�rk�! Spr�buj ponownie: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> komorka;
		}
		else if (sprawdzaczsciana == 0)
		{
			cout << "Nie mo�na wpisa� statku w to miejsce, gdy� statek wyjdzie poza plansz�! Spr�buj ponownie: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> komorka;
		}
		else if (pomocwpisanie != ilumasztowiec)
		{
			cout << "Nie mo�na wpisa� statku w to miejsce, gdy� to pole jest ju� zaj�te! Spr�buj ponownie: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> komorka;
		}
		else if (sprawdzaczkomorka == 1 && sprawdzaczsciana == 1 && pomocwpisanie == ilumasztowiec)
			sprawdzacz = 1;
	}

	// Wpisanie statk�w i p�l naoko�o nich
	if (wktorastrone == 1) // W g�r�
	{
		for (int i = 0; i < ilumasztowiec; i++) // Wpisanie statku
			plansza[stoi(komorka.substr(1, 1)) - i][static_cast<int>(komorka[0]) - 97] = ilumasztowiec;

		for (int i = -1; i <= 1; i++) // Wpisanie p�l naoko�o statku
		{
			if (static_cast<int>(komorka[0]) - 97 == 0 && i == -1) // Lewa �ciana
				continue;
			else if (static_cast<int>(komorka[0]) - 97 == 9 && i == 1) // Prawa �ciana
				continue;
			else
			{
				for (int j = -1; j <= ilumasztowiec; j++)
				{
					if (stoi(komorka.substr(1, 1)) == 9 && j == -1) // Dolna �ciana
						continue;
					else if (stoi(komorka.substr(1, 1)) == ilumasztowiec - 1 && j == ilumasztowiec) // G�rna �ciana
						continue;
					else if (i == 0 && j >= 0 && j <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
						continue;
					else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
					{
						if (plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 + i] == 0)
							plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 + i] = 5;
					}
				}
			}
		}
	}

	else if (wktorastrone == 2) // W prawo
	{
		for (int i = 0; i < ilumasztowiec; i++) // Wpisanie statku
			plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 + i] = ilumasztowiec;

		for (int i = -1; i <= ilumasztowiec; i++) // Wpisanie p�l naoko�o statku
		{
			if (static_cast<int>(komorka[0]) - 97 == 0 && i == -1) // Lewa �ciana
				continue;
			else if (static_cast<int>(komorka[0]) - 97 == 10 - ilumasztowiec && i == ilumasztowiec) // Prawa �ciana
				continue;
			else
			{
				for (int j = -1; j <= 1; j++)
				{
					if (stoi(komorka.substr(1, 1)) == 9 && j == -1) // Dolna �ciana
						continue;
					else if (stoi(komorka.substr(1, 1)) == 0 && j == 1) // G�rna �ciana
						continue;
					else if (j == 0 && i >= 0 && i <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
						continue;
					else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
					{
						if (plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 + i] == 0)
							plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 + i] = 5;
					}
				}
			}
		}
	}

	else if (wktorastrone == 3) // W d�
	{
		for (int i = 0; i < ilumasztowiec; i++) // Wpisanie statku
			plansza[stoi(komorka.substr(1, 1)) + i][static_cast<int>(komorka[0]) - 97] = ilumasztowiec;

		for (int i = -1; i <= 1; i++) // Wpisanie p�l naoko�o statku
		{
			if (static_cast<int>(komorka[0]) - 97 == 0 && i == -1) // Lewa �ciana
				continue;
			else if (static_cast<int>(komorka[0]) - 97 == 9 && i == 1) // Prawa �ciana
				continue;
			else
			{
				for (int j = -1; j <= ilumasztowiec; j++)
				{
					if (stoi(komorka.substr(1, 1)) == 10 - ilumasztowiec && j == ilumasztowiec) // Dolna �ciana
						continue;
					else if (stoi(komorka.substr(1, 1)) == 0 && j == -1) // G�rna �ciana
						continue;
					else if (i == 0 && j >= 0 && j <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
						continue;
					else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
					{
						if (plansza[stoi(komorka.substr(1, 1)) + j][static_cast<int>(komorka[0]) - 97 + i] == 0)
							plansza[stoi(komorka.substr(1, 1)) + j][static_cast<int>(komorka[0]) - 97 + i] = 5;
					}
				}
			}
		}
	}

	else if (wktorastrone == 4) // W lewo
	{
		for (int i = 0; i < ilumasztowiec; i++) // Wpisanie statku
			plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 - i] = ilumasztowiec;

		for (int i = -1; i <= ilumasztowiec; i++) // Wpisanie p�l naoko�o statku
		{
			if (static_cast<int>(komorka[0]) - 97 == ilumasztowiec - 1 && i == ilumasztowiec) // Lewa �ciana
				continue;
			else if (static_cast<int>(komorka[0]) - 97 == 9 && i == -1) // Prawa �ciana
				continue;
			else
			{
				for (int j = -1; j <= 1; j++)
				{
					if (stoi(komorka.substr(1, 1)) == 9 && j == -1) // Dolna �ciana
						continue;
					else if (stoi(komorka.substr(1, 1)) == 0 && j == 1) // G�rna �ciana
						continue;
					else if (j == 0 && i >= 0 && i <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
						continue;
					else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
					{
						if (plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 - i] == 0)
							plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 - i] = 5;
					}
				}
			}
		}
	}
}

void ustaw_statki_losowo(int plansza[10][10], int ilumasztowiec)
{
	int wktorastrone = 0;
	int pomocwpisanie = 0;
	string komorka, pomoc;
	bool sprawdzacz = 0, sprawdzaczsciana = 0;

	// Generowanie losowej kom�rki i kierunku 
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution <int> wspolrzedna(0, 9);
	uniform_int_distribution <int> kierunek(1, 4);

	while (sprawdzacz != 1) // Sprawdzanie, czy wpisana kom�rka jest mo�liwa
	{
		sprawdzacz = 0;
		sprawdzaczsciana = 0;
		pomocwpisanie = 0;

		// Losowanie kom�rki i kierunku
		pomoc = (1, 'a' + wspolrzedna(generator));
		komorka = pomoc + to_string(wspolrzedna(generator));
		wktorastrone = kierunek(generator);

		// Sprawdzanie, czy w dan� kom�rk� mo�na wpisa� statek pod wzgl�dem �cian
		if (wktorastrone == 1) // Dla g�ry
		{
			for (int i = ilumasztowiec - 1; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					string a(1, 'a' + j);
					if (komorka == a + to_string(i))
					{
						sprawdzaczsciana = 1;
						break;
					}
				}
			}
		}
		else if (wktorastrone == 2) // Dla prawa
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 11 - ilumasztowiec; j++)
				{
					string a(1, 'a' + j);
					if (komorka == a + to_string(i))
					{
						sprawdzaczsciana = 1;
						break;
					}
				}
			}
		}
		else if (wktorastrone == 3) // Dla do�u
		{
			for (int i = 0; i < 11 - ilumasztowiec; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					string a(1, 'a' + j);
					if (komorka == a + to_string(i))
					{
						sprawdzaczsciana = 1;
						break;
					}
				}
			}
		}
		else if (wktorastrone == 4) // Dla lewa
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = ilumasztowiec - 1; j < 10; j++)
				{
					string a(1, 'a' + j);
					if (komorka == a + to_string(i))
					{
						sprawdzaczsciana = 1;
						break;
					}
				}
			}
		}

		// Sprawdzanie, czy w dan� kom�rk� mo�na wpisa� statek pod wzgl�dem innych statk�w
		if (wktorastrone == 1) // Dla g�ry
		{
			for (int i = 0; i < ilumasztowiec; i++)
			{
				if (plansza[stoi(komorka.substr(1, 1)) - i][static_cast<int>(komorka[0]) - 97] == 0)
					pomocwpisanie++;
			}
		}
		else if (wktorastrone == 2) // Dla prawa
		{
			for (int i = 0; i < ilumasztowiec; i++)
			{
				if (plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 + i] == 0)
					pomocwpisanie++;
			}
		}
		else if (wktorastrone == 3) // Dla do�u
		{
			for (int i = 0; i < ilumasztowiec; i++)
			{
				if (plansza[stoi(komorka.substr(1, 1)) + i][static_cast<int>(komorka[0]) - 97] == 0)
					pomocwpisanie++;
			}
		}
		else if (wktorastrone == 4) // Dla lewa
		{
			for (int i = 0; i < ilumasztowiec; i++)
			{
				if (plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 - i] == 0)
					pomocwpisanie++;
			}
		}

		if (sprawdzaczsciana == 1 && pomocwpisanie == ilumasztowiec)
			sprawdzacz = 1;
		else
			sprawdzacz = 0;	
	}

	// Wpisanie statk�w i p�l naoko�o nich
	if (wktorastrone == 1) // W g�r�
	{
		for (int i = 0; i < ilumasztowiec; i++) // Wpisanie statku
			plansza[stoi(komorka.substr(1, 1)) - i][static_cast<int>(komorka[0]) - 97] = ilumasztowiec;

		for (int i = -1; i <= 1; i++) // Wpisanie p�l naoko�o statku
		{
			if (static_cast<int>(komorka[0]) - 97 == 0 && i == -1) // Lewa �ciana
				continue;
			else if (static_cast<int>(komorka[0]) - 97 == 9 && i == 1) // Prawa �ciana
				continue;
			else
			{
				for (int j = -1; j <= ilumasztowiec; j++)
				{
					if (stoi(komorka.substr(1, 1)) == 9 && j == -1) // Dolna �ciana
						continue;
					else if (stoi(komorka.substr(1, 1)) == ilumasztowiec - 1 && j == ilumasztowiec) // G�rna �ciana
						continue;
					else if (i == 0 && j >= 0 && j <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
						continue;
					else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
					{
						if (plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 + i] == 0)
							plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 + i] = 5;
					}
				}
			}
		}
	}

	else if (wktorastrone == 2) // W prawo
	{
		for (int i = 0; i < ilumasztowiec; i++) // Wpisanie statku
			plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 + i] = ilumasztowiec;

		for (int i = -1; i <= ilumasztowiec; i++) // Wpisanie p�l naoko�o statku
		{
			if (static_cast<int>(komorka[0]) - 97 == 0 && i == -1) // Lewa �ciana
				continue;
			else if (static_cast<int>(komorka[0]) - 97 == 10 - ilumasztowiec && i == ilumasztowiec) // Prawa �ciana
				continue;
			else
			{
				for (int j = -1; j <= 1; j++)
				{
					if (stoi(komorka.substr(1, 1)) == 9 && j == -1) // Dolna �ciana
						continue;
					else if (stoi(komorka.substr(1, 1)) == 0 && j == 1) // G�rna �ciana
						continue;
					else if (j == 0 && i >= 0 && i <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
						continue;
					else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
					{
						if (plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 + i] == 0)
							plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 + i] = 5;
					}
				}
			}
		}
	}

	else if (wktorastrone == 3) // W d�
	{
		for (int i = 0; i < ilumasztowiec; i++) // Wpisanie statku
			plansza[stoi(komorka.substr(1, 1)) + i][static_cast<int>(komorka[0]) - 97] = ilumasztowiec;

		for (int i = -1; i <= 1; i++) // Wpisanie p�l naoko�o statku
		{
			if (static_cast<int>(komorka[0]) - 97 == 0 && i == -1) // Lewa �ciana
				continue;
			else if (static_cast<int>(komorka[0]) - 97 == 9 && i == 1) // Prawa �ciana
				continue;
			else
			{
				for (int j = -1; j <= ilumasztowiec; j++)
				{
					if (stoi(komorka.substr(1, 1)) == 10 - ilumasztowiec && j == ilumasztowiec) // Dolna �ciana
						continue;
					else if (stoi(komorka.substr(1, 1)) == 0 && j == -1) // G�rna �ciana
						continue;
					else if (i == 0 && j >= 0 && j <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
						continue;
					else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
					{
						if (plansza[stoi(komorka.substr(1, 1)) + j][static_cast<int>(komorka[0]) - 97 + i] == 0)
							plansza[stoi(komorka.substr(1, 1)) + j][static_cast<int>(komorka[0]) - 97 + i] = 5;
					}
				}
			}
		}
	}

	else if (wktorastrone == 4) // W lewo
	{
		for (int i = 0; i < ilumasztowiec; i++) // Wpisanie statku
			plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 - i] = ilumasztowiec;

		for (int i = -1; i <= ilumasztowiec; i++) // Wpisanie p�l naoko�o statku
		{
			if (static_cast<int>(komorka[0]) - 97 == ilumasztowiec - 1 && i == ilumasztowiec) // Lewa �ciana
				continue;
			else if (static_cast<int>(komorka[0]) - 97 == 9 && i == -1) // Prawa �ciana
				continue;
			else
			{
				for (int j = -1; j <= 1; j++)
				{
					if (stoi(komorka.substr(1, 1)) == 9 && j == -1) // Dolna �ciana
						continue;
					else if (stoi(komorka.substr(1, 1)) == 0 && j == 1) // G�rna �ciana
						continue;
					else if (j == 0 && i >= 0 && i <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
						continue;
					else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
					{
						if (plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 - i] == 0)
							plansza[stoi(komorka.substr(1, 1)) - j][static_cast<int>(komorka[0]) - 97 - i] = 5;
					}
				}
			}
		}
	}
}

void wypisz_plansze(int plansza[10][10])
{
	system("cls"); // Wyczyszczenie konsoli

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout.width(1);
			cout << plansza[i][j] << " ";
		}
		cout << endl;
	}
}

void wypisz_plansze2(int plansza[10][10])
{
	system("cls"); // Wyczyszczenie konsoli

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++) // Wypisanie indeks�w na g�rze (a, b, c, ...)
		{
			if (i == 0)
			{
				if (j == 10)
					continue;
				if(j == 0)
					cout << "   " << static_cast<char>('a' + j);
				else
					cout << " " << static_cast<char>('a' + j);
			}
				
			else
			{
				if (j == 0) // Wypisanie indeks�w na prawej �cianie (1, 2, 3, ...)
				{
					if (i == 10)
						cout << i << " ";
					else
						cout << " " << i << " ";
				}
				else // Wypisanie planszy
				{
					if (plansza[i - 1][j - 1] == 0) // Wypisanie element�w pustych
						cout << ". ";
					else if (plansza[i - 1][j - 1] == 5) // Wypisanie "obw�dki" statku
						cout << "x ";
					else // Wypisanie statku
						cout << plansza[i - 1][j - 1] << " ";
				}
			}
		}
		cout << endl;
	}
}

int main()
{
	int gracz1statki[10][10] = {}, gracz2statki[10][10] = {};

	// Wype�nienie tabel zerami
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gracz1statki[i][j] = 0;
			gracz2statki[i][j] = 0;
		}
	}

	string komorki[10][10];

	// Wype�nienie tabeli mo�liwymi kom�rkami do wykorzystania
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			string a(1, 'a' + j);
			komorki[i - 1][j] = a + to_string(i);
			//cout << "W indeksie " << i - 1 << " " << j << " jest komorka " << komorki[i - 1][j] << endl;
		}
	}

	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, 4);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, 3);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, 3);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, 2);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, 2);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, 2);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, 1);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, 1);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, 1);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, 1);
	wypisz_plansze2(gracz1statki);

	for (int i = 1; i <= 4; i++)
		for (int j = 4; j >= i; j--)
			ustaw_statki_losowo(gracz2statki, i);

	wypisz_plansze2(gracz2statki);

	system("pause");
}