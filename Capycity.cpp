#include <iostream>

using namespace std;

int main() {
	
	int laenge, breite, laengeGebaeude, breiteGebaeude, koordinate1, koordinate2;
	cout << "Bitte die Laenge der Bauflaeche angeben \n";
	cin >> laenge;
	cout << "Bitte die Breite der Bauflaeche angeben \n";
	cin >> breite;

	int* bauflaeche = new int[laenge * breite] {0};
	int menuepunkt = 0;
	while (menuepunkt != 5) {

		cout << "Menuepunkte: \n";
		cout << "Gebauede bauen: 1 \n";
		cout << "Bauflaeche frei machen: 2 \n";
		cout << "Bauflaeche ausdrucken: 3 \n";
		cout << "Exit: 4 \n";
		cin >> menuepunkt;


		if (menuepunkt == 1) {
			bool innerhalbDerBauflaeche = true;
			bool flaecheBelegt = false;


			cout << "Geben Sie die Laenge des Gebaeudes an: \n";
			cin >> laengeGebaeude;

			cout << "Geben Sie die Breite des Gebaeudes an: \n";
			cin >> breiteGebaeude;

			cout << "X-Koordinate: \n";
			cin >> koordinate2;
			cout << "Y-Koordinate: \n";
			cin >> koordinate1;

			if (laengeGebaeude > laenge || breiteGebaeude > breite) {
				cout << "Gebaeude ist zu gross fuer die Bauflaeche \n";
				menuepunkt = 1;
			}

			for (int y = 0; y < laengeGebaeude; ++y) {
				for (int x = 0; x < breiteGebaeude; ++x) {
					if (bauflaeche[(x + koordinate2) * laenge + (y + koordinate1)] > sizeof(bauflaeche)) {
						innerhalbDerBauflaeche = false;
						break;
					}

					else if (bauflaeche[(x + koordinate2) * laenge + (y + koordinate1)] == 1) {
						flaecheBelegt = true;
						break;
					}


				}
			}
			if (innerhalbDerBauflaeche == false) {
				cout << "Gebaude ueberschreitet die Flaeche des bebaubaren Bereichs. \n";
				menuepunkt = 1;
			}

			else if (flaecheBelegt == true) {
				cout << "Flaeche schon (teilweise) bebaut! \n";
				menuepunkt = 1;
			}

			else {
				for (int y = 0; y < laengeGebaeude; ++y) {
					for (int x = 0; x < breiteGebaeude; ++x) {
						bauflaeche[(x + koordinate2) * laenge + (y + koordinate1)] = { 1 };
						
					}
				}
			}
		}
		else if (menuepunkt == 2) {
			cout << "Geben Sie die Laenge der freizugebende Flaeche an: \n";
			cin >> laengeGebaeude;
			cout << "Geben Sie die Breite der freizugebende Flaeche an: \n";
			cin >> breiteGebaeude;
			cout << "Geben Sie die X Koordinate fuer die freizugebende Flaeche an: \n";
			cin >> koordinate1;
			cout << "Geben Sie die Y Koordinate fuer die freizugebende Flaeche an: \n";
			cin >> koordinate2;

			for (int y = 0; y < laengeGebaeude; ++y) {
				for (int x = 0; x < breiteGebaeude; ++x) {

					bauflaeche[(x + koordinate1) * laenge + (y + koordinate2)] = { 0 };

				}
			}
		}
		else if (menuepunkt == 3) {
			for (int i = 0; i < laenge; i++) {
				for (int j = 0; j < breite; j++) {
					if (bauflaeche[j * laenge + i] == 0) {
						printf("[   ]");
					}
					else if (bauflaeche[j * laenge + i] == 1) {
						printf("[ X ]");
					}
				}
				printf("\n");
			}

		}
		else if (menuepunkt == 4) {
			cout << "Exit. \n";
			return 0;
		}
	}
};


