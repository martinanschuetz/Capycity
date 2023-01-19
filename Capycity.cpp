#include <iostream>

using namespace std;

class CapycitySim {
public:
	int* bauflaecheAngeben();
	void bauflaecheAusgeben(int* bauflaeche);
	int* gebaeudeSetzen(int* bauflaeche);
	int* flaecheFreigeben(int* bauflaeche);
	void welcheKosten();

private:
	int laenge, breite, artDesGebaeudes, laengeGebaeude, breiteGebaeude, koordinate1, koordinate2;
	int anzahlWA = 0, anzahlWI = 0, anzahlSO = 0;
	int* bauflaeche;
	int wasserpreis, windpreis, solarpreis, gesamtPreis;

};
class Materialien {
private:
	int preis;
	string welcheMats;
public:
	Materialien(int p, string wM) : preis(p), welcheMats(wM) {};
	int getPreis() { return preis; };
	string getMats() { return welcheMats; };
};
class Holz : public Materialien {
public:
	Holz(int p, string wM) : Materialien(p, wM) {};
};
class Metall : public Materialien {
public:
	Metall(int p, string wM) : Materialien(p, wM) {};
};
class Kunststoff : public Materialien {
public:
	Kunststoff(int p, string wM) : Materialien(p, wM) {};
};

class Building {
private:
	int grundpreis;
	Materialien* benoetigteMaterialien;
public:
	Building();
	Building(int gp, Materialien* bMats) : grundpreis(gp), benoetigteMaterialien{ bMats } {};
	int getGrundpreis() const;

};
int Building::getGrundpreis() const {
	return this->grundpreis;
}

class Wasserkraftwerk : public Building {
public:
	Wasserkraftwerk(int gp, Materialien* bMats) : Building(gp, bMats) {};

};
class Windkraftwerk : public Building {
public:
	Windkraftwerk(int gp, Materialien* bMats) : Building(gp, bMats) {};

};
class Solarpanele : public Building {
public:
	Solarpanele(int gp, Materialien* bMats) : Building(gp, bMats) {};
};

int* CapycitySim::bauflaecheAngeben() {
	cout << "Bitte die Laenge der Bauflaeche angeben \n";
	cin >> laenge;
	cout << "Bitte die Breite der Bauflaeche angeben \n";
	cin >> breite;

	int* bauflaeche = new int[laenge * breite] {0};
	return bauflaeche;

}
void CapycitySim::bauflaecheAusgeben(int* bauflaeche) {
	for (int i = 0; i < laenge; i++) {
		for (int j = 0; j < breite; j++) {
			if (bauflaeche[j * laenge + i] == 0) {
				printf("[    ]");
			}
			else if (bauflaeche[j * laenge + i] == 1) {
				printf("[ WA ]");
			}
			else if (bauflaeche[j * laenge + i] == 2) {
				printf("[ WI ]");
			}
			else if (bauflaeche[j * laenge + i] == 3) {
				printf("[ SO ]");
			}
		}
		printf("\n");
	}

}
int* CapycitySim::gebaeudeSetzen(int* bauflaeche) {

	bool innerhalbDerBauflaeche = true;
	bool flaecheBelegt = false;

	cout << "Geben Sie die Art des Gebaeudes an: \n";
	cout << "1: Wasserkraftwerk, 2: Windkraftwerk, 3: Solarpanele. \n";
	cin >> artDesGebaeudes;

	if (artDesGebaeudes > 3 || artDesGebaeudes < 1) {
		cout << "1, 2, oder 3! \n";
		gebaeudeSetzen(bauflaeche);
	}


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
		gebaeudeSetzen(bauflaeche);
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
		gebaeudeSetzen(bauflaeche);
	}

	else if (flaecheBelegt == true) {
		cout << "Flaeche schon (teilweise) bebaut! \n";
		gebaeudeSetzen(bauflaeche);
	}

	else {
		for (int y = 0; y < laengeGebaeude; ++y) {
			for (int x = 0; x < breiteGebaeude; ++x) {
				if (artDesGebaeudes == 1) {
					bauflaeche[(x + koordinate2) * laenge + (y + koordinate1)] = { 1 };
				}
				else if (artDesGebaeudes == 2) {
					bauflaeche[(x + koordinate2) * laenge + (y + koordinate1)] = { 2 };
				}
				else if (artDesGebaeudes == 3) {
					bauflaeche[(x + koordinate2) * laenge + (y + koordinate1)] = { 3 };
				}
			}
		}
		if (artDesGebaeudes == 1) {
			anzahlWA++;
		}
		if (artDesGebaeudes == 2) {
			anzahlWI++;
		}
		if (artDesGebaeudes == 3) {
			anzahlSO++;
		}
	}

	return bauflaeche;
}

int* CapycitySim::flaecheFreigeben(int* bauflaeche) {
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
	return bauflaeche;
}

void CapycitySim::welcheKosten() {
	while ((anzahlWA + anzahlWI + anzahlSO) == 0) {
		cout << "Es existiert noch kein Gebäude \n";
		gebaeudeSetzen(bauflaeche);
	}
	int holzanzahlwa = 0, metallanzahlwa = 0, kunststoffanzahlwa = 0;
	int holzanzahlwi = 0, metallanzahlwi = 0, kunststoffanzahlwi = 0;
	int holzanzahlso = 0, metallanzahlso = 0, kunststoffanzahlso = 0;

	Holz hlz(40, "Holz");
	Metall mtll(100, "Metall");
	Kunststoff knststff(20, "Kunststoff");

	Materialien* matsWA = new Materialien[5]{ hlz, hlz, hlz, mtll, knststff };
	Materialien* matsWI = new Materialien[6]{ mtll , mtll, mtll, mtll, hlz, knststff };
	Materialien* matsSO = new Materialien[8]{ hlz, hlz, mtll, mtll, mtll, mtll, knststff, knststff };


	Wasserkraftwerk wa(1000, matsWA);
	Windkraftwerk wi(2000, matsWI);
	Solarpanele so(4000, matsSO);


	for (int i = 0; i < 5; i++) {
		if (matsWA[i].getMats() == "Holz") {
			holzanzahlwa++;
		}
		else if (matsWA[i].getMats() == "Metall") {
			metallanzahlwa++;
		}
		else if (matsWA[i].getMats() == "Kunststoff") {
			kunststoffanzahlwa++;
		}
	}
	for (int i = 0; i < 6; i++) {
		if (matsWI[i].getMats() == "Holz") {
			holzanzahlwi++;
		}
		else if (matsWI[i].getMats() == "Metall") {
			metallanzahlwi++;
		}
		else if (matsWI[i].getMats() == "Kunststoff") {
			kunststoffanzahlwi++;
		}
	}
	for (int i = 0; i < 8; i++) {
		if (matsSO[i].getMats() == "Holz") {
			holzanzahlso++;
		}
		else if (matsSO[i].getMats() == "Metall") {
			metallanzahlso++;
		}
		else if (matsSO[i].getMats() == "Kunststoff") {
			kunststoffanzahlso++;
		}
	}

	wasserpreis = wa.getGrundpreis() + holzanzahlwa * hlz.getPreis() + metallanzahlwa * mtll.getPreis() + kunststoffanzahlwa * knststff.getPreis();
	cout << "Ein Wasserkraftwerk kostet: " << wasserpreis << "\n";
	cout << "Dafuer wird folgendes Material benoetigt: \n";
	for (int i = 0; i < 5; i++) {
		cout << matsWA[i].getMats() << " ";
	}
	cout << "\n";

	windpreis = wi.getGrundpreis() + holzanzahlwi * hlz.getPreis() + metallanzahlwi * mtll.getPreis() + kunststoffanzahlwi * knststff.getPreis();
	cout << "Ein Windkraftwerk kostet: " << windpreis << "\n";
	cout << "Dafuer wird folgendes Material benoetigt: \n";
	for (int i = 0; i < 6; i++) {
		cout << matsWI[i].getMats() << " ";
	}
	cout << "\n";

	solarpreis = so.getGrundpreis() + holzanzahlso * hlz.getPreis() + metallanzahlso * mtll.getPreis() + kunststoffanzahlso * knststff.getPreis();
	cout << "Ein Solarpanel kostet: " << solarpreis << "\n";
	cout << "Dafuer wird folgendes Material benoetigt: \n";
	for (int i = 0; i < 8; i++) {
		cout << matsSO[i].getMats() << " ";
	}
	cout << "\n";


	cout << "Wie viele Wasserkraftwerke wurden gebaut: " << anzahlWA << "\n";
	cout << "Wie viele Windkraftwerke wurden gebaut: " << anzahlWI << "\n";
	cout << "Wie viele Solarpanele wurden gebaut: " << anzahlSO << "\n";

	gesamtPreis = wasserpreis * anzahlWA + windpreis * anzahlWI + solarpreis * anzahlSO;

	cout << "Der Gesamtpreis betraegt : " << gesamtPreis << "\n";

}

int main() {
	CapycitySim* capy = new CapycitySim();


	int* bauflaeche = capy->bauflaecheAngeben();
	int menuepunkt = 0;
	while (menuepunkt != 5) {

		cout << "Menuepunkte: \n";
		cout << "Gebauede bauen: 1 \n";
		cout << "Bauflaeche frei machen: 2 \n";
		cout << "Bauflaeche ausdrucken: 3 \n";
		cout << "Welche Kosten: 4 \n";
		cout << "Exit: 5 \n";
		cin >> menuepunkt;


		if (menuepunkt == 1) {
			capy->gebaeudeSetzen(bauflaeche);
		}
		else if (menuepunkt == 2) {
			capy->flaecheFreigeben(bauflaeche);
		}
		else if (menuepunkt == 3) {
			capy->bauflaecheAusgeben(bauflaeche);
		}
		else if (menuepunkt == 4) {
			capy->welcheKosten();
		}
		else if (menuepunkt == 5) {
			cout << "Exit. \n";
			return 0;
		}
	}
};


