#include<iostream>
#include<string>
#include<limits>
#include<random>
#include<vector>
#include<windows.h>
#include<cstdlib>

using namespace std;

void ustaw_statki(int plansza[10][10], string komorki[10][10], vector<vector<string>> &komorkistatki, int ilumasztowiec)
{
	double wktorastrone = 0;
	int pomoctabela = 0, pomocwpisanie = 0;
	string komorka;
	bool sprawdzacz = 0, sprawdzaczkomorka = 0, sprawdzaczsciana = 0;

	if (ilumasztowiec == 1)
		wktorastrone = 1;
	else
	{
		// Ustawianie kierunku masztowca
		cout << "W jaki spos�b chcesz ustawi� " << ilumasztowiec << "masztowiec? (1 = w g�r�, 2 = w prawo, 3 = w d�, 4 = w lewo): ";
		cin >> wktorastrone;
	}

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

		// Wypisanie b��d�w
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

	vector<string> pomoc;
	// Wpisanie statk�w i p�l naoko�o nich
	if (wktorastrone == 1) // W g�r�
	{
		for (int i = 0; i < ilumasztowiec; i++) // Wpisanie statku
		{
			plansza[stoi(komorka.substr(1, 1)) - i][static_cast<int>(komorka[0]) - 97] = ilumasztowiec;
			pomoc.push_back(komorka[0] + to_string(stoi(komorka.substr(1, 1)) - i));
		}
		// Wstawienie do tabeli komorkistatki informacji o d�ugo�ci masztowca, w kt�r� stron� by� wpisany oraz o tym, kt�ra kom�rka by�a wpisana jako pierwsza
		pomoc.push_back(to_string(ilumasztowiec) + to_string(wktorastrone));
		pomoc.push_back(komorka);
		komorkistatki.push_back(pomoc);

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
		{
			plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 + i] = ilumasztowiec;
			string a(1, komorka[0] + i);
			pomoc.push_back(a + komorka.substr(1, 1));
		}
		// Wstawienie do tabeli komorkistatki informacji o d�ugo�ci masztowca, w kt�r� stron� by� wpisany oraz o tym, kt�ra kom�rka by�a wpisana jako pierwsza
		pomoc.push_back(to_string(ilumasztowiec) + to_string(wktorastrone));
		pomoc.push_back(komorka);
		komorkistatki.push_back(pomoc);

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
		{
			plansza[stoi(komorka.substr(1, 1)) + i][static_cast<int>(komorka[0]) - 97] = ilumasztowiec;
			pomoc.push_back(komorka[0] + to_string(stoi(komorka.substr(1, 1)) + i));
		}
		// Wstawienie do tabeli komorkistatki informacji o d�ugo�ci masztowca, w kt�r� stron� by� wpisany oraz o tym, kt�ra kom�rka by�a wpisana jako pierwsza
		pomoc.push_back(to_string(ilumasztowiec) + to_string(wktorastrone));
		pomoc.push_back(komorka);
		komorkistatki.push_back(pomoc);

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
		{
			plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 - i] = ilumasztowiec;
			string a(1, komorka[0] - i);
			pomoc.push_back(a + komorka.substr(1, 1));
		}
		// Wstawienie do tabeli komorkistatki informacji o d�ugo�ci masztowca, w kt�r� stron� by� wpisany oraz o tym, kt�ra kom�rka by�a wpisana jako pierwsza
		pomoc.push_back(to_string(ilumasztowiec) + to_string(wktorastrone));
		pomoc.push_back(komorka);
		komorkistatki.push_back(pomoc);

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

void ustaw_statki_losowo(int plansza[10][10], vector<vector<string>> &komorkistatki, int ilumasztowiec)
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
		if (ilumasztowiec == 1)
			wktorastrone = 1;
		else
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

	vector<string> pomockomorki;
	// Wpisanie statk�w i p�l naoko�o nich
	if (wktorastrone == 1) // W g�r�
	{
		for (int i = 0; i < ilumasztowiec; i++) // Wpisanie statku
		{
			plansza[stoi(komorka.substr(1, 1)) - i][static_cast<int>(komorka[0]) - 97] = ilumasztowiec;
			pomockomorki.push_back(komorka[0] + to_string(stoi(komorka.substr(1, 1)) - i));
		}
		// Wstawienie do tabeli komorkistatki informacji o d�ugo�ci masztowca, w kt�r� stron� by� wpisany oraz o tym, kt�ra kom�rka by�a wpisana jako pierwsza
		pomockomorki.push_back(to_string(ilumasztowiec) + to_string(wktorastrone));
		pomockomorki.push_back(komorka);
		komorkistatki.push_back(pomockomorki);

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
		{
			plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 + i] = ilumasztowiec;
			string a(1, komorka[0] + i);
			pomockomorki.push_back(a + komorka.substr(1, 1));
		}
		// Wstawienie do tabeli komorkistatki informacji o d�ugo�ci masztowca, w kt�r� stron� by� wpisany oraz o tym, kt�ra kom�rka by�a wpisana jako pierwsza
		pomockomorki.push_back(to_string(ilumasztowiec) + to_string(wktorastrone));
		pomockomorki.push_back(komorka);
		komorkistatki.push_back(pomockomorki);

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
		{
			plansza[stoi(komorka.substr(1, 1)) + i][static_cast<int>(komorka[0]) - 97] = ilumasztowiec;
			pomockomorki.push_back(komorka[0] + to_string(stoi(komorka.substr(1, 1)) + i));
		}
		// Wstawienie do tabeli komorkistatki informacji o d�ugo�ci masztowca, w kt�r� stron� by� wpisany oraz o tym, kt�ra kom�rka by�a wpisana jako pierwsza
		pomockomorki.push_back(to_string(ilumasztowiec) + to_string(wktorastrone));
		pomockomorki.push_back(komorka);
		komorkistatki.push_back(pomockomorki);

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
		{
			plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97 - i] = ilumasztowiec;
			string a(1, komorka[0] - i);
			pomockomorki.push_back(a + komorka.substr(1, 1));
		}
		// Wstawienie do tabeli komorkistatki informacji o d�ugo�ci masztowca, w kt�r� stron� by� wpisany oraz o tym, kt�ra kom�rka by�a wpisana jako pierwsza
		pomockomorki.push_back(to_string(ilumasztowiec) + to_string(wktorastrone));
		pomockomorki.push_back(komorka);
		komorkistatki.push_back(pomockomorki);

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
						cout << ". ";
					else // Wypisanie statku
						cout << plansza[i - 1][j - 1] << " ";
				}
			}
		}
		cout << endl;
	}
}

void wypisz_plansze_gra(int plansza[10][10])
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
				if (j == 0)
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
						cout << "0 ";
					else if (plansza[i - 1][j - 1] == 1) // Wypisanie statku
						cout << "x ";
					else // Wypisanie nietrafionych p�l
						cout << "0 ";
				}
			}
		}
		cout << endl;
	}
}

void gra(int plansza[10][10], string komorki[10][10], vector<string> &uzytekomorki, vector<vector<string>> &komorkistatki)
{
	string komorka;
	bool sprawdzacz = 0, sprawdzaczkomorka = 0, sprawdzaczuzycie = 1, sprawdzacztrafienie = 0;

	// Ustawianie atakowanego pola
	cout << "Kt�re pole chcesz zaatakowa�? (Podaj ma�� liter�, a nast�pnie liczb�, np. d6): ";
	cin >> komorka;

	while (sprawdzacz != 1) // Sprawdzanie, czy wpisana kom�rka jest mo�liwa do zaatakowania
	{
		sprawdzacz = 0;
		sprawdzaczkomorka = 0;
		sprawdzaczuzycie = 1;

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

		// Sprawdzanie, czy u�ytkownik poda� kom�rk�, kt�rej nie wykorzysta� 
		for (int i = 0; unsigned(i) < uzytekomorki.size(); i++)
		{
			if (komorka.compare(uzytekomorki[i]) == 0)
			{
				sprawdzaczuzycie = 0;
				break;
			}
		}

		// Wypisanie b��d�w
		if (sprawdzaczkomorka == 0)
		{
			cout << "Nie mo�na zaatakowa� tego pola, gdy� poda�e� niew�a�ciw� kom�rk�! Spr�buj ponownie: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> komorka;
		}
		else if (sprawdzaczuzycie == 0)
		{
			cout << "Nie mo�na zaatakowa� tego pola, gdy� poda�e� ju� wykorzystan� przez Ciebie kom�rk�! Spr�buj ponownie: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> komorka;
		}
		else if (sprawdzaczkomorka == 1 || sprawdzaczuzycie == 1)
		{
			uzytekomorki.push_back(komorka);
			sprawdzacz = 1;
		}
	}

	int pomoci = 0, pomocj = 0;
	for (int i = 0; unsigned(i) < komorkistatki.size(); i++) // Sprawdzenie, czy u�ytkownik trafi� w statek przeciwnika
	{
		for (int j = 0; unsigned(j) < komorkistatki[i].size(); j++)
		{
			if (komorka == komorkistatki[i][j])
			{
				pomoci = i;
				pomocj = j;
				sprawdzacztrafienie = 1;
				break;
			}
		}
	}

	int ilumasztowiec, wktorastrone;
	string komorkapomoc;

	if (sprawdzacztrafienie == 1) // Je�li trafi�
	{
		komorkistatki[pomoci].erase(komorkistatki[pomoci].begin() + pomocj);
		if (komorkistatki[pomoci].size() == 2)
		{
			cout << "Trafiony zatopiony! :D" << endl;
			ilumasztowiec = stoi(komorkistatki[pomoci][0].substr(0, 1));
			wktorastrone = stoi(komorkistatki[pomoci][0].substr(1));
			komorkapomoc = komorkistatki[pomoci][1];
			cout << ilumasztowiec << " " << wktorastrone << endl;

			// Wypisanie p�l naoko�o statku
			if (wktorastrone == 1) // W g�r�
			{
				for (int i = -1; i <= 1; i++) // Wpisanie p�l naoko�o statku
				{
					if (static_cast<int>(komorkapomoc[0]) - 97 == 0 && i == -1) // Lewa �ciana
						continue;
					else if (static_cast<int>(komorkapomoc[0]) - 97 == 9 && i == 1) // Prawa �ciana
						continue;
					else
					{
						for (int j = -1; j <= ilumasztowiec; j++)
						{
							if (stoi(komorkapomoc.substr(1, 1)) == 9 && j == -1) // Dolna �ciana
								continue;
							else if (stoi(komorkapomoc.substr(1, 1)) == ilumasztowiec - 1 && j == ilumasztowiec) // G�rna �ciana
								continue;
							else if (i == 0 && j >= 0 && j <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
								continue;
							else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
							{
								if (plansza[stoi(komorkapomoc.substr(1, 1)) - j][static_cast<int>(komorkapomoc[0]) - 97 + i] == 0)
								{
									plansza[stoi(komorkapomoc.substr(1, 1)) - j][static_cast<int>(komorkapomoc[0]) - 97 + i] = 5;
									string a(1, komorkapomoc[0] + i);
									cout << "Komorka: " << a << stoi(komorkapomoc.substr(1, 1)) - j << " dla " << i << " i " << j << endl;
									uzytekomorki.push_back(a + to_string(stoi(komorkapomoc.substr(1, 1)) - j));
								}
							}
						}
					}
				}
				system("pause");
			}
			else if (wktorastrone == 2) // W prawo
			{
				for (int i = -1; i <= ilumasztowiec; i++) // Wpisanie p�l naoko�o statku
				{
					if (static_cast<int>(komorkapomoc[0]) - 97 == 0 && i == -1) // Lewa �ciana
						continue;
					else if (static_cast<int>(komorkapomoc[0]) - 97 == 10 - ilumasztowiec && i == ilumasztowiec) // Prawa �ciana
						continue;
					else
					{
						for (int j = -1; j <= 1; j++)
						{
							if (stoi(komorkapomoc.substr(1, 1)) == 9 && j == -1) // Dolna �ciana
								continue;
							else if (stoi(komorkapomoc.substr(1, 1)) == 0 && j == 1) // G�rna �ciana
								continue;
							else if (j == 0 && i >= 0 && i <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
								continue;
							else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
							{
								if (plansza[stoi(komorkapomoc.substr(1, 1)) - j][static_cast<int>(komorkapomoc[0]) - 97 + i] == 0)
								{
									plansza[stoi(komorkapomoc.substr(1, 1)) - j][static_cast<int>(komorkapomoc[0]) - 97 + i] = 5;
									string a(1, komorkapomoc[0] + i);
									uzytekomorki.push_back(a + to_string(stoi(komorkapomoc.substr(1, 1)) - j));
								}

							}
						}
					}
				}
			}
			else if (wktorastrone == 3) // W d�
			{
				for (int i = -1; i <= 1; i++) // Wpisanie p�l naoko�o statku
				{
					if (static_cast<int>(komorkapomoc[0]) - 97 == 0 && i == -1) // Lewa �ciana
						continue;
					else if (static_cast<int>(komorkapomoc[0]) - 97 == 9 && i == 1) // Prawa �ciana
						continue;
					else
					{
						for (int j = -1; j <= ilumasztowiec; j++)
						{
							if (stoi(komorkapomoc.substr(1, 1)) == 10 - ilumasztowiec && j == ilumasztowiec) // Dolna �ciana
								continue;
							else if (stoi(komorkapomoc.substr(1, 1)) == 0 && j == -1) // G�rna �ciana
								continue;
							else if (i == 0 && j >= 0 && j <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
								continue;
							else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
							{
								if (plansza[stoi(komorkapomoc.substr(1, 1)) + j][static_cast<int>(komorkapomoc[0]) - 97 + i] == 0)
								{
									plansza[stoi(komorkapomoc.substr(1, 1)) + j][static_cast<int>(komorkapomoc[0]) - 97 + i] = 5;
									string a(1, komorkapomoc[0] + i);
									uzytekomorki.push_back(a + to_string(stoi(komorkapomoc.substr(1, 1)) + j));
								}
							}
						}
					}
				}
			}
			else if (wktorastrone == 4) // W lewo
			{
				for (int i = -1; i <= ilumasztowiec; i++) // Wpisanie p�l naoko�o statku
				{
					if (static_cast<int>(komorkapomoc[0]) - 97 == ilumasztowiec - 1 && i == ilumasztowiec) // Lewa �ciana
						continue;
					else if (static_cast<int>(komorkapomoc[0]) - 97 == 9 && i == -1) // Prawa �ciana
						continue;
					else
					{
						for (int j = -1; j <= 1; j++)
						{
							if (stoi(komorkapomoc.substr(1, 1)) == 9 && j == -1) // Dolna �ciana
								continue;
							else if (stoi(komorkapomoc.substr(1, 1)) == 0 && j == 1) // G�rna �ciana
								continue;
							else if (j == 0 && i >= 0 && i <= ilumasztowiec - 1) // Omini�cie kom�rek ze statkiem
								continue;
							else // Wypisanie p�l niemo�liwych do zaj�cia przez inne statki
							{
								if (plansza[stoi(komorkapomoc.substr(1, 1)) - j][static_cast<int>(komorkapomoc[0]) - 97 - i] == 0)
								{
									plansza[stoi(komorkapomoc.substr(1, 1)) - j][static_cast<int>(komorkapomoc[0]) - 97 - i] = 5;
									string a(1, komorkapomoc[0] - i);
									uzytekomorki.push_back(a + to_string(stoi(komorkapomoc.substr(1, 1)) - j));
								}
							}
						}
					}
				}
			}

			komorkistatki.erase(komorkistatki.begin() + pomoci); // Usuni�cie kom�rki z zatopionym statkiem
			for (int i = 0; unsigned(i) < komorkistatki.size(); i++) // Wypisywanie kom�rek z nietrafionymi statkami
			{
				for (int j = 0; unsigned(j) < komorkistatki[i].size(); j++)
				{
					cout << komorkistatki[i][j] << " ";
				}
				cout << endl;
			}

			if (komorkistatki.size() == 0)
				return;
		}
		else
		{
			cout << "Trafiony! :)" << endl;
			for (int i = 0; unsigned(i) < komorkistatki.size(); i++)
			{
				for (int j = 0; unsigned(j) < komorkistatki[i].size(); j++)
					cout << komorkistatki[i][j] << " ";
				cout << endl;
			}
		}
		plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97] = 1;
		system("pause");
		wypisz_plansze_gra(plansza);
		gra(plansza, komorki, uzytekomorki, komorkistatki);
	}
	else // Je�li nie trafi�
	{
		cout << "Tym razem nie trafi�e�... :/" << endl;
		plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97] = 2;
		system("pause");
	}	
}

void menu(int plansza[10][10], string komorki[10][10], vector<vector<string>>& komorkistatki, int gracz)
{
	system("cls");
	cout << "STATKI!" << endl;
	cout << "Witaj graczu nr " << gracz << endl;
	cout << "Wybierz opcj�." << endl;
	cout << "1. Graj" << endl;
	cout << "2. Instrukcja" << endl;
	cout << "3. Wyjd�" << endl;
	
	int wybor, wyborgra;
	cout << "Wybierz opcj�: ";
	cin >> wybor;

	switch (wybor)
	{
		case 1:
		{
			system("cls");
			cout << "Graczu nr " << gracz <<". Wybierz opcj�." << endl;
			cout << "1. Ustaw statki sam" << endl;
			cout << "2. Ustaw statki losowo" << endl;
			cout << "Wybierz opcj�: ";
			cin >> wyborgra;
			switch (wyborgra)
			{
				case 1:
				{
					/*wypisz_plansze2(plansza);
					ustaw_statki(plansza, komorki, komorkistatki, 4);
					wypisz_plansze2(plansza);
					ustaw_statki(plansza, komorki, komorkistatki, 3);
					wypisz_plansze2(plansza);
					ustaw_statki(plansza, komorki, komorkistatki, 3);
					wypisz_plansze2(plansza);
					ustaw_statki(plansza, komorki, komorkistatki, 2);
					wypisz_plansze2(plansza);
					ustaw_statki(plansza, komorki, komorkistatki, 2);
					wypisz_plansze2(plansza);
					ustaw_statki(plansza, komorki, komorkistatki, 2);
					wypisz_plansze2(plansza);
					ustaw_statki(plansza, komorki, komorkistatki, 1);
					wypisz_plansze2(plansza);
					ustaw_statki(plansza, komorki, komorkistatki, 1);
					wypisz_plansze2(plansza);
					ustaw_statki(plansza, komorki, komorkistatki, 1);
					wypisz_plansze2(plansza);*/
					ustaw_statki(plansza, komorki, komorkistatki, 1);
					break;
				}	
				case 2:
				{
					for (int i = 1; i <= 4; i++)
						for (int j = 4; j >= i; j--)
							ustaw_statki_losowo(plansza, komorkistatki, i);
					wypisz_plansze2(plansza);
					cout << "Twoja losowo wygenerowana plansza." << endl;
					system("pause");
					break;
				}
				default:
				{
					cout << "Nie wybra�e� odpowiedniej opcji! Spr�buj ponownie: ";
					cin >> wyborgra;
					break;
				}
			}
			break;
		}
		case 2:
		{
			system("cls");
			cout << "Aby ustawi� statek, musisz wybra� jego kierunek i pierwsz� kom�rk�" << endl;
			cout << "Aby wybra� kierunek wpisujemy cyfr� do niego przypisan� i zatwierdzamy wyb�r enterem (1 - g�ra, 2 - prawo, 3 - d�, 4 - lewo)." << endl;
			cout << "Aby wybra� pierwsz� kom�rk�, wpisujemy jej indeks, zaczynaj�c od ma�ej litery od a do j, a nast�pnie liczb� od 1 do 10 i zatwierdzamy wyb�r enterem. Przyk�ad: d7" << endl;
			cout << "Dla przyk�adu, gdy wybierzemy kierunek w g�r� i pierwsz� kom�rk� a4 dla czteromasztowca, statek zostanie wpisany w kom�rki a4, a3, a2 i a1." << endl;
			cout << "Aby zaatakowa� kom�rk�, wpisujemy jej indeks, zaczynaj�c od ma�ej litery od a do j, a nast�pnie liczb� od 1 do 10 i zatwierdzamy wyb�r enterem. Przyk�ad: d7" << endl;
			cout << "Pierwsza osoba, kt�ra wyeliminuje wszystkie statki przeciwnika wygrywa! Mi�ej gry!" << endl;
			cout << endl << endl << "Autor: Jakub Rejdych" << endl;
			system("pause");
			menu(plansza, komorki, komorkistatki, gracz);
			break;
		}
		case 3:
			exit(1);
		default:
		{
			cout << "Nie wybra�e� odpowiedniej opcji! Spr�buj ponownie: ";
			cin >> wybor;
			break;
		}
	}
}

int main()
{
	int gracz1statki[10][10] = {}, gracz2statki[10][10] = {}, gracz1statkigra[10][10] = {}, gracz2statkigra[10][10] = {};
	vector<vector<string>> komorkistatki1;
	vector<vector<string>> komorkistatki2;
	vector<string> uzytekomorki1;
	vector<string> uzytekomorki2;
	string komorki[10][10];
	int wygrana = 1;

	// Wype�nienie tabel zerami
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gracz1statki[i][j] = 0;
			gracz2statki[i][j] = 0;
			gracz1statkigra[i][j] = 0;
			gracz2statkigra[i][j] = 0;
		}
	}

	// Wype�nienie tabeli mo�liwymi kom�rkami do wykorzystania
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			string a(1, 'a' + j);
			komorki[i - 1][j] = a + to_string(i);
		}
	}

	menu(gracz1statki, komorki, komorkistatki1, 1);
	menu(gracz2statki, komorki, komorkistatki2, 2);

	/*string komorka;
	komorka = "d7";

	string a(1, komorka[0] + 1);
	komorkistatki1.push_back(a + komorka.substr(1, 1));
	cout << komorkistatki1[0] << komorkistatki1.size() << endl;
	system("pause");*/

	/*wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, komorkistatki1, 4);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, komorkistatki1, 3);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, komorkistatki1, 3);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, komorkistatki1, 2);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, komorkistatki1, 2);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, komorkistatki1, 2);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, komorkistatki1, 1);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, komorkistatki1, 1);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, komorkistatki1, 1);
	wypisz_plansze2(gracz1statki);
	ustaw_statki(gracz1statki, komorki, komorkistatki1, 1);
	wypisz_plansze2(gracz1statki);*/

	/*for (int i = 1; i <= 4; i++)
		for (int j = 4; j >= i; j--)
			ustaw_statki_losowo(gracz2statki, komorkistatki2, i);
	for (int i = 1; i <= 4; i++)
		for (int j = 4; j >= i; j--)
			ustaw_statki_losowo(gracz1statki, komorkistatki1, i);

	wypisz_plansze2(gracz1statki);

	for (int i = 0; unsigned(i) < komorkistatki2.size(); i++)
	{
		for (int j = 0; unsigned(j) < komorkistatki2[i].size(); j++)
			cout << komorkistatki2[i][j] << " ";
		cout << endl;
	}
	cout << komorkistatki2.size();
	system("pause");

	wypisz_plansze2(gracz2statki);*/

	/*for (int i = 0; i < komorkistatki2.size(); i++)
	{
		for (int j = 0; j < komorkistatki2[i].size(); j++)
			cout << komorkistatki2[i][j] << " ";
		cout << endl;
	}
	system("pause");*/

	while (komorkistatki1.size() != 0 || komorkistatki2.size() != 0)
	{
		wypisz_plansze_gra(gracz1statkigra);
		cout << "Kolej gracza 1" << endl;
		gra(gracz1statkigra, komorki, uzytekomorki1, komorkistatki2);
		if (komorkistatki2.size() == 0)
		{
			wygrana = 1;
			break;
		}
		wypisz_plansze_gra(gracz2statkigra);
		cout << "Kolej gracza 2" << endl;
		gra(gracz2statkigra, komorki, uzytekomorki2, komorkistatki1);
		if (komorkistatki1.size() == 0)
		{
			wygrana = 2;
			break;
		}
	}

	system("cls");
	cout << "Wygra� gracz nr " << wygrana << "!" << endl;

	system("pause");
}