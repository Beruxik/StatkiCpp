#include<iostream>
#include<string>
#include<random>
#include<vector>
#include<windows.h>

using namespace std;

void ustaw_statki(int plansza[10][10], string komorki[20][20], vector<vector<string>>& komorkistatki, int ilumasztowiec)
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
		cout << "W jaki spos�b chcesz ustawi� " << ilumasztowiec << "masztowiec? (1 = w g�r�, 2 = w prawo, 3 = w d��, 4 = w lewo): ";
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
	cout << "Podaj kom�rk�, w kt�rej chcesz umie�ci� pierwsz� cz��� " << ilumasztowiec << "masztowca (Podaj ma�� liter�, a nast�pnie liczb� lub na odwr�t, np. d6 lub 6d): ";
	cin >> komorka;

	while (sprawdzacz != 1) // Sprawdzanie, czy wpisana kom�rka jest mo�liwa
	{
		sprawdzacz = 0;
		sprawdzaczkomorka = 0;
		sprawdzaczsciana = 0;
		pomocwpisanie = 0;

		if (komorka.length() < 2 || komorka.length() > 3)
			komorka = "k5";

		// Sprawdzanie, czy u�ytkownik wpisa� mo�liw� kom�rk�
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (komorka.compare(komorki[i][j]) == 0)
				{
					sprawdzaczkomorka = 1;
					break;
				}
			}
		}

		// Zmiana zmiennnej komorka z np. a1 na a0 lub z np. 1a na a0
		if (komorka.length() == 2 && komorka[0] >= 'a' && komorka[0] <= 'j')
			komorka = komorka[0] + to_string(stoi(komorka.substr(1, 1)) - 1);
		else if (komorka.length() == 3 && komorka[0] >= 'a' && komorka[0] <= 'j')
			komorka = komorka[0] + to_string(stoi(komorka.substr(1, 2)) - 1);
		else if (komorka.length() == 2 && komorka[0] >= '1' && komorka[0] <= '9')
			komorka = komorka[1] + to_string(stoi(komorka.substr(0, 1)) - 1);
		else if (komorka.length() == 3 && komorka[0] == '1' && komorka[1] == '0')
			komorka = komorka[2] + to_string(stoi(komorka.substr(0, 2)) - 1);
		else
			komorka = komorka[0] + to_string(stoi(komorka.substr(1, 1)) - 1);

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

	else if (wktorastrone == 3) // W d��
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

void ustaw_statki_losowo(int plansza[10][10], vector<vector<string>>& komorkistatki, int ilumasztowiec)
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

	else if (wktorastrone == 3) // W d��
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

void wypisz_plansze(int plansza[10][10], int jak)
{
	system("cls"); // Wyczyszczenie konsoli
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Zmienna do ustawiania kolor�w

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
					else if (plansza[i - 1][j - 1] == 5 && jak == 1) // Wypisanie "obw�dki" statku
						cout << "x ";
					else if (plansza[i - 1][j - 1] == 5 && jak == 0)
						cout << ". ";
					else // Wypisanie statku
					{
						SetConsoleTextAttribute(hConsole, 3); // Zmiana koloru czcionki na jasnoniebieski
						cout << plansza[i - 1][j - 1] << " ";
						SetConsoleTextAttribute(hConsole, 15); // Zmiana koloru czcionki na bia�y
					}
				}
			}
		}
		cout << endl;
	}
}

void wypisz_plansze_gra(int plansza[10][10])
{
	system("cls"); // Wyczyszczenie konsoli
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Zmienna do ustawiania kolor�w

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
					{
						SetConsoleTextAttribute(hConsole, 3); // Zmiana koloru czcionki na jasnoniebieski
						cout << "x ";
						SetConsoleTextAttribute(hConsole, 15); // Zmiana koloru czcionki na bia�y
					}
					else // Wypisanie nietrafionych p�l
						cout << "0 ";
				}
			}
		}
		cout << endl;
	}
}

void gra(int plansza[10][10], string komorki[20][20], vector<string>& uzytekomorki, vector<vector<string>>& komorkistatki, int gracz)
{
	string komorka;
	bool sprawdzacz = 0, sprawdzaczkomorka = 0, sprawdzaczuzycie = 1, sprawdzacztrafienie = 0;
	int jednomasztowiec = 0, dwumasztowiec = 0, trojmasztowiec = 0, czteromasztowiec = 0;

	jednomasztowiec = 0;
	dwumasztowiec = 0;
	trojmasztowiec = 0;
	czteromasztowiec = 0;

	// Wypisywanie ile statk�w zosta�o do zatopienia
	cout << "Do zatopienia zosta�o: " << endl;
	for (int i = 0; unsigned(i) < komorkistatki.size(); i++)
	{
		if (komorkistatki[i][komorkistatki[i].size() - 2][0] == '1')
			jednomasztowiec++;
		if (komorkistatki[i][komorkistatki[i].size() - 2][0] == '2')
			dwumasztowiec++;
		if (komorkistatki[i][komorkistatki[i].size() - 2][0] == '3')
			trojmasztowiec++;
		if (komorkistatki[i][komorkistatki[i].size() - 2][0] == '4')
			czteromasztowiec++;
	}

	if (jednomasztowiec != 0)
		cout << "Jednomasztowce: " << jednomasztowiec << endl;
	if (dwumasztowiec != 0)
		cout << "Dwumasztowce: " << dwumasztowiec << endl;
	if (trojmasztowiec != 0)
		cout << "Tr�jmasztowce: " << trojmasztowiec << endl;
	if (czteromasztowiec != 0)
		cout << "Czteromasztowce: " << czteromasztowiec << endl;

	// Ustawianie atakowanego pola
	cout << "Kt�re pole chcesz zaatakowa�? (Podaj ma�� liter�, a nast�pnie liczb� lub na odwr�t, np. d6 lub 6d): ";
	cin >> komorka;

	while (sprawdzacz != 1) // Sprawdzanie, czy wpisana kom�rka jest mo�liwa do zaatakowania
	{
		sprawdzacz = 0;
		sprawdzaczkomorka = 0;
		sprawdzaczuzycie = 1;

		if (komorka.length() < 2 || komorka.length() > 3)
			komorka = "k5";

		// Sprawdzanie, czy u�ytkownik wpisa� mo�liw� kom�rk�
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (komorka.compare(komorki[i][j]) == 0)
				{
					sprawdzaczkomorka = 1;
					break;
				}
			}
		}

		// Zmiana zmiennnej komorka z np. a1 na a0 lub z np. 1a na a0
		if (komorka.length() == 2 && komorka[0] >= 'a' && komorka[0] <= 'j')
			komorka = komorka[0] + to_string(stoi(komorka.substr(1, 1)) - 1);
		else if (komorka.length() == 3 && komorka[0] >= 'a' && komorka[0] <= 'j')
			komorka = komorka[0] + to_string(stoi(komorka.substr(1, 2)) - 1);
		else if (komorka.length() == 2 && komorka[0] >= '1' && komorka[0] <= '9')
			komorka = komorka[1] + to_string(stoi(komorka.substr(0, 1)) - 1);
		else if (komorka.length() == 3 && komorka[0] == '1' && komorka[1] == '0')
			komorka = komorka[2] + to_string(stoi(komorka.substr(0, 2)) - 1);
		else
			komorka = komorka[0] + to_string(stoi(komorka.substr(1, 1)) - 1);

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
		plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97] = 1;
		wypisz_plansze_gra(plansza);
		if (komorkistatki[pomoci].size() == 2)
		{
			cout << "Trafiony zatopiony! :D" << endl;

			ilumasztowiec = stoi(komorkistatki[pomoci][0].substr(0, 1));
			wktorastrone = stoi(komorkistatki[pomoci][0].substr(1));
			komorkapomoc = komorkistatki[pomoci][1];

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
									uzytekomorki.push_back(a + to_string(stoi(komorkapomoc.substr(1, 1)) - j));
								}
							}
						}
					}
				}
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
			else if (wktorastrone == 3) // W d��
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

			if (komorkistatki.size() == 0) // Sko�czenie dzia�ania funkcji po zwyci�stwie
				return;
		}
		else
			cout << "Trafiony! :)" << endl;
		system("pause");
		wypisz_plansze_gra(plansza);
		cout << "Kolej gracza nr " << gracz << endl;
		gra(plansza, komorki, uzytekomorki, komorkistatki, gracz);
	}
	else // Je�li nie trafi�
	{
		plansza[stoi(komorka.substr(1, 1))][static_cast<int>(komorka[0]) - 97] = 2;
		wypisz_plansze_gra(plansza);
		cout << "Tym razem nie trafi�e�... :/" << endl;
		system("pause");
	}
}

void menu(int plansza[10][10], string komorki[20][20], vector<vector<string>>& komorkistatki, int gracz)
{
	system("cls");
	cout << "0xxxx0...0xxx0....0xx0.....0x0" << endl;
	cout << "            STATKI!" << endl;
	cout << "0xxxx0...0xxx0....0xx0.....0x0" << endl;
	cout << "Witaj graczu nr " << gracz << endl;
	cout << "Wybierz opcj�." << endl;
	cout << "1. Graj" << endl;
	cout << "2. Instrukcja" << endl;
	cout << "3. Wyjd�" << endl;

	string wybor, wyborgra;
	cout << "Wybierz opcj�: ";
	cin >> wybor;

	while (wybor[0] < '1' || wybor[0] > '3') // Sprawdzanie, czy u�ytkownik poda� odpowiedni� opcj�
	{
		cout << "Nie poda�e� w�a�ciwej opcji! Spr�buj ponownie: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> wybor;
	}

	switch (static_cast<int>(wybor[0] - '0'))
	{
		case 1:
		{
			system("cls");
			cout << "Graczu nr " << gracz << ". Wybierz opcj�." << endl;
			cout << "1. Ustaw statki sam" << endl;
			cout << "2. Ustaw statki losowo" << endl;
			cout << "Wybierz opcj�: ";
			cin >> wyborgra;

			while (wyborgra[0] < '1' || wyborgra[0] > '3') // Sprawdzanie, czy u�ytkownik poda� odpowiedni� opcj�
			{
				cout << "Nie poda�e� w�a�ciwej opcji! Spr�buj ponownie: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> wyborgra;
			}

			switch (static_cast<int>(wyborgra[0] - '0'))
			{
				case 1:
				{
					wypisz_plansze(plansza, 1);
					ustaw_statki(plansza, komorki, komorkistatki, 4);
					wypisz_plansze(plansza, 1);
					ustaw_statki(plansza, komorki, komorkistatki, 3);
					wypisz_plansze(plansza, 1);
					ustaw_statki(plansza, komorki, komorkistatki, 3);
					wypisz_plansze(plansza, 1);
					ustaw_statki(plansza, komorki, komorkistatki, 2);
					wypisz_plansze(plansza, 1);
					ustaw_statki(plansza, komorki, komorkistatki, 2);
					wypisz_plansze(plansza, 1);
					ustaw_statki(plansza, komorki, komorkistatki, 2);
					wypisz_plansze(plansza, 1);
					ustaw_statki(plansza, komorki, komorkistatki, 1);
					wypisz_plansze(plansza, 1);
					ustaw_statki(plansza, komorki, komorkistatki, 1);
					wypisz_plansze(plansza, 1);
					ustaw_statki(plansza, komorki, komorkistatki, 1);
					wypisz_plansze(plansza, 1);
					ustaw_statki(plansza, komorki, komorkistatki, 1);
					wypisz_plansze(plansza, 1);
					cout << "Oto Twoja plansza graczu " << gracz << "." << endl;
					system("pause");
					break;
				}
				case 2:
				{
					for (int i = 1; i <= 4; i++)
						for (int j = 4; j >= i; j--)
							ustaw_statki_losowo(plansza, komorkistatki, i);
					wypisz_plansze(plansza, 0);
					cout << "Twoja losowo wygenerowana plansza." << endl;
					system("pause");
					break;
				}
			}
			break;
		}
		case 2:
		{
			system("cls");
			cout << "Aby ustawi� statek, musisz wybra� jego kierunek i pierwsz� kom�rk�." << endl;
			cout << "Aby wybra� kierunek wpisujemy cyfr� do niego przypisan� i zatwierdzamy wyb�r enterem (1 - g�ra, 2 - prawo, 3 - d��, 4 - lewo)." << endl;
			cout << "Aby wybra� pierwsz� kom�rk�, wpisujemy jej indeks, zaczynaj�c od ma�ej litery od a do j, a nast�pnie liczb� od 1 do 10 lub na odwr�t i zatwierdzamy wyb�r enterem. Przyk�ad: d7 lub 7d." << endl;
			cout << "Dla przyk�adu, gdy wybierzemy kierunek w g�r� i pierwsz� kom�rk� a4 dla czteromasztowca, statek zostanie wpisany w kom�rki a4, a3, a2 i a1." << endl;
			cout << "Aby zaatakowa� kom�rk�, wpisujemy jej indeks, zaczynaj�c od ma�ej litery od a do j, a nast�pnie liczb� od 1 do 10 lub na odwr�t i zatwierdzamy wyb�r enterem. Przyk�ad: d7 lub 7d." << endl;
			cout << "Pierwsza osoba, kt�ra wyeliminuje wszystkie statki przeciwnika wygrywa! Mi�ej gry!" << endl;
			cout << endl << endl << "Autor: Jakub Rejdych" << endl;
			system("pause");
			menu(plansza, komorki, komorkistatki, gracz);
			break;
		}
		case 3:
			exit(1);
	}
}

int main()
{
	int gracz1statki[10][10] = {}, gracz2statki[10][10] = {}, gracz1statkigra[10][10] = {}, gracz2statkigra[10][10] = {};
	vector<vector<string>> komorkistatki1;
	vector<vector<string>> komorkistatki2;
	vector<string> uzytekomorki1;
	vector<string> uzytekomorki2;
	string komorki[20][20];
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
			komorki[i - 1 + 10][j + 10] = to_string(i) + a;
		}
	}

	// Gra
	menu(gracz1statki, komorki, komorkistatki1, 1);
	menu(gracz2statki, komorki, komorkistatki2, 2);

	while (komorkistatki1.size() != 0 || komorkistatki2.size() != 0)
	{
		wypisz_plansze_gra(gracz1statkigra);
		cout << "Kolej gracza 1" << endl;
		gra(gracz1statkigra, komorki, uzytekomorki1, komorkistatki2, 1);
		if (komorkistatki2.size() == 0)
		{
			wygrana = 1;
			break;
		}
		wypisz_plansze_gra(gracz2statkigra);
		cout << "Kolej gracza 2" << endl;
		gra(gracz2statkigra, komorki, uzytekomorki2, komorkistatki1, 2);
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