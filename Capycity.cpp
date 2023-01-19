#include <iostream>
#include <map>


using namespace std;

class CapycitySim {
public:
	int* gebaeudeSetzen(int* bauflaeche, int laenge, int breite, int artDesGebaeudes);
	int* flaecheFreigeben(int* bauflaeche, int laenge, int breite);
	void welcheKosten(int laenge, int breite, int anzahlWA, int anzahlWI, int anzahlSO, int artDesGebaeudes);

private:
	int laengeGebaeude, breiteGebaeude, koordinate1, koordinate2;
	int* bauflaeche;
	int gesamtPreis;
};

class Blueprint {
public:
	Blueprint() {};
	Blueprint(int l, int b) : laenge(l), breite(b) {};
	int* bauflaecheAngeben(int laenge, int breite);
	void bauflaecheAusgeben(int* bauflaeche, int laenge, int breite);
	void getKennzahl(int anzahlWA, int anzahlWI, int anzahlSO, int laenge, int breiteB);
private:
	int laenge, breite;
	int kennzahl;
};
int* Blueprint::bauflaecheAngeben(int laenge, int breite) {
	Blueprint bp(laenge, breite);
	int* bauflaeche = new int[laenge * breite] {0};
	return bauflaeche;
}
void Blueprint::bauflaecheAusgeben(int* bauflaeche, int laenge, int breite) {
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
	map<string, int> benoetigteMaterialien;
	int wasserpreis, windpreis, solarpreis;

public:
	Building() {}
	Building(int gp, map <string, int> bMats) : grundpreis(gp), benoetigteMaterialien(bMats) {};
	int getGrundpreis() const;
	int getWasserpreis();
	int getWindpreis();
	int getSolarpreis();
};

int Building::getGrundpreis() const {
	return this->grundpreis;
}
int Building::getWasserpreis() {
	Holz hlz(40, "Holz");
	Metall mtll(100, "Metall");
	Kunststoff knststff(20, "Kunststoff");

	map <string, int> matsWA;
	matsWA["Holz"] = 3;
	matsWA["Metall"] = 1;
	matsWA["Kunststoff"] = 1;

	Building wa(1000, matsWA);

	wasserpreis = wa.getGrundpreis() + matsWA.find("Holz")->second * hlz.getPreis() + matsWA.find("Metall")->second * mtll.getPreis() + matsWA.find("Kunststoff")->second * knststff.getPreis();

	return wasserpreis;
}
int Building::getWindpreis() {
	Holz hlz(40, "Holz");
	Metall mtll(100, "Metall");
	Kunststoff knststff(20, "Kunststoff");

	map <string, int> matsWI;
	matsWI["Holz"] = 1;
	matsWI["Metall"] = 4;
	matsWI["Kunststoff"] = 1;

	Building wi(2000, matsWI);

	windpreis = wi.getGrundpreis() + matsWI.find("Holz")->second * hlz.getPreis() + matsWI.find("Metall")->second * mtll.getPreis() + matsWI.find("Kunststoff")->second * knststff.getPreis();

	return windpreis;
}
int Building::getSolarpreis() {
	Holz hlz(40, "Holz");
	Metall mtll(100, "Metall");
	Kunststoff knststff(20, "Kunststoff");

	map <string, int> matsSO;
	matsSO["Holz"] = 2;
	matsSO["Metall"] = 4;
	matsSO["Kunststoff"] = 2;

	Building so(4000, matsSO);

	solarpreis = so.getGrundpreis() + matsSO.find("Holz")->second * hlz.getPreis() + matsSO.find("Metall")->second * mtll.getPreis() + matsSO.find("Kunststoff")->second * knststff.getPreis();

	return solarpreis;
}
class Wasserkraftwerk : public Building {
public:
	Wasserkraftwerk() {}
	Wasserkraftwerk(int gp, map <string, int> bMats) : Building(gp, bMats) {};
	Wasserkraftwerk(int wal) : wasserleistung(wal) {};
	int getWasserleistung() const;
private:
	int wasserleistung;
};
int Wasserkraftwerk::getWasserleistung() const {
	return this->wasserleistung;
}
class Windkraftwerk : public Building {
public:
	Windkraftwerk() {}
	Windkraftwerk(int gp, map <string, int> bMats) : Building(gp, bMats) {};
	Windkraftwerk(int wil) : windleistung(wil) {};
	int getWindleistung() const;
private:
	int windleistung;
};
int Windkraftwerk::getWindleistung() const {
	return this->windleistung;
}

class Solarpanele : public Building {
public:
	Solarpanele() {}
	Solarpanele(int gp, map <string, int> bMats) : Building(gp, bMats) {};
	Solarpanele(int sol) : solarleistung(sol) {};
	int getSolarleistung() const;
private:
	int solarleistung;
};
int Solarpanele::getSolarleistung() const {
	return this->solarleistung;
}
int* CapycitySim::gebaeudeSetzen(int* bauflaeche, int laenge, int breite, int artDesGebaeudes) {

	bool innerhalbDerBauflaeche = true;
	bool flaecheBelegt = false;


	if (artDesGebaeudes > 3 || artDesGebaeudes < 1) {
		cout << "1, 2, oder 3! \n";
		gebaeudeSetzen(bauflaeche, laenge, breite, artDesGebaeudes);
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
		gebaeudeSetzen(bauflaeche, laenge, breite, artDesGebaeudes);
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
		gebaeudeSetzen(bauflaeche, laenge, breite, artDesGebaeudes);
	}

	else if (flaecheBelegt == true) {
		cout << "Flaeche schon (teilweise) bebaut! \n";
		gebaeudeSetzen(bauflaeche, laenge, breite, artDesGebaeudes);
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

	}

	return bauflaeche;

}

int* CapycitySim::flaecheFreigeben(int* bauflaeche, int laenge, int breite) {
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

void CapycitySim::welcheKosten(int laenge, int breite, int anzahlWA, int anzahlWI, int anzahlSO, int artDesGebaeudes) {
	map <string, int> matsWA;
	matsWA["Holz"] = 3;
	matsWA["Metall"] = 1;
	matsWA["Kunststoff"] = 1;

	map <string, int> matsWI;
	matsWI["Holz"] = 1;
	matsWI["Metall"] = 4;
	matsWI["Kunststoff"] = 1;

	map <string, int> matsSO;
	matsSO["Holz"] = 2;
	matsSO["Metall"] = 4;
	matsSO["Kunststoff"] = 2;

	while ((anzahlWA + anzahlWI + anzahlSO) == 0) {
		cout << "Es existiert noch kein Gebäude \n";
		gebaeudeSetzen(bauflaeche, laenge, breite, artDesGebaeudes);
	}

	Wasserkraftwerk* wa2 = new Wasserkraftwerk();
	Windkraftwerk* wi2 = new Windkraftwerk();
	Solarpanele* so2 = new Solarpanele();


	cout << "Wie viele Wasserkraftwerke wurden gebaut: " << anzahlWA << "\n";
	cout << "Wie viele Windkraftwerke wurden gebaut: " << anzahlWI << "\n";
	cout << "Wie viele Solarpanele wurden gebaut: " << anzahlSO << "\n";
	cout << "\n";


	gesamtPreis = wa2->getWasserpreis() * anzahlWA + wi2->getWindpreis() * anzahlWI + so2->getSolarpreis() * anzahlSO;

	cout << "Ein Wasserkraftwerk kostet: " << wa2->getWasserpreis() << "\n";
	cout << "Dafuer wird folgendes Material benoetigt: \n";
	cout << matsWA.find("Holz")->second << " mal " << matsWA.find("Holz")->first << "\n";
	cout << matsWA.find("Metall")->second << " mal " << matsWA.find("Metall")->first << "\n";
	cout << matsWA.find("Kunststoff")->second << " mal " << matsWA.find("Kunststoff")->first << "\n";
	cout << "\n";

	cout << "Ein Windkraftwerk kostet: " << wi2->getWindpreis() << "\n";
	cout << "Dafuer wird folgendes Material benoetigt: \n";
	cout << matsWI.find("Holz")->second << " mal " << matsWI.find("Holz")->first << "\n";
	cout << matsWI.find("Metall")->second << " mal " << matsWI.find("Metall")->first << "\n";
	cout << matsWI.find("Kunststoff")->second << " mal " << matsWI.find("Kunststoff")->first << "\n";
	cout << "\n";
	cout << "Ein Solarpanel kostet: " << so2->getSolarpreis() << "\n";
	cout << "Dafuer wird folgendes Material benoetigt: \n";
	cout << matsSO.find("Holz")->second << " mal " << matsSO.find("Holz")->first << "\n";
	cout << matsSO.find("Metall")->second << " mal " << matsSO.find("Metall")->first << "\n";
	cout << matsSO.find("Kunststoff")->second << " mal " << matsSO.find("Kunststoff")->first << "\n";
	cout << "\n";

	cout << "Der Gesamtpreis betraegt : " << gesamtPreis << "\n";
	cout << "\n";

}
void Blueprint::getKennzahl(int anzahlWA, int anzahlWI, int anzahlSO, int laenge, int breite) {
	Wasserkraftwerk wal(500000000);
	Windkraftwerk wil(100000000);
	Solarpanele sol(50000000);

	kennzahl = ((wal.getWasserleistung() * anzahlWA + wil.getWindleistung() * anzahlWI + sol.getSolarleistung() * anzahlSO) / ((wal.getWasserpreis() * anzahlWA + wil.getWindpreis() * anzahlWI + wil.getSolarpreis() * anzahlSO) * laenge * breite));

	cout << "Die Kennzahl des Plans lautet: " << kennzahl << "\n";
	cout << "\n";

}


int main() {
	CapycitySim* capy = new CapycitySim();
	Blueprint* plan = new Blueprint();
	map<int, Building*> gebaeudeProPlan;
	map<int, int*> plantest;
	map<int, int> laengen;
	map<int, int> breiten;
	map<int, int> anzahlWIs;
	map<int, int> anzahlWAs;
	map<int, int> anzahlSOs;
	int anzahlPlaene = 0;
	int laenge, breite;
	int neueLaenge = 0, neueBreite = 0;
	int* neueBauflaeche{ 0 };
	int artDesGebaeudes = 0;
	int anzahlWA = 0, anzahlWI = 0, anzahlSO = 0;

	cout << "Bitte die Laenge der Bauflaeche angeben \n";
	cin >> laenge;
	laengen[anzahlPlaene] = laenge;
	cout << "Bitte die Breite der Bauflaeche angeben \n";
	cin >> breite;
	breiten[anzahlPlaene] = breite;

	int* bauflaeche = plan->bauflaecheAngeben(laenge, breite);
	plantest[anzahlPlaene] = bauflaeche;

	int menuepunkt = 0;
	while (menuepunkt != 6) {

		cout << "Menuepunkte: \n";
		cout << "Neuen Bauplan anlegen: 1 \n";
		cout << "Gebauede bauen: 2 \n";
		cout << "Bauflaeche frei machen: 3 \n";
		cout << "Bauflaeche ausdrucken: 4 \n";
		cout << "Welche Kosten: 5 \n";
		cout << "Exit: 6 \n";
		cout << "\n";
		cin >> menuepunkt;

		if (menuepunkt == 1) {
			anzahlWA = 0, anzahlWI = 0, anzahlSO = 0;
			anzahlPlaene++;
			cout << "Neue Laenge angeben: \n";
			cin >> neueLaenge;
			laengen[anzahlPlaene] = neueLaenge;
			cout << "Neue Breite angeben: \n";
			cin >> neueBreite;
			breiten[anzahlPlaene] = neueBreite;
			plantest[anzahlPlaene] = plan->bauflaecheAngeben(neueLaenge, neueBreite);
			plan->bauflaecheAusgeben(plantest[anzahlPlaene], neueLaenge, neueBreite);
		}
		else if (menuepunkt == 2) {
			cout << "Geben Sie die Art des Gebaeudes an: \n";
			cout << "1: Wasserkraftwerk, 2: Windkraftwerk, 3: Solarpanele. \n";
			cin >> artDesGebaeudes;
			capy->gebaeudeSetzen(plantest[anzahlPlaene], laengen[anzahlPlaene], breiten[anzahlPlaene], artDesGebaeudes);
			if (artDesGebaeudes == 1) {
				anzahlWA++;
				anzahlWAs[anzahlPlaene] = anzahlWA;
			}
			if (artDesGebaeudes == 2) {
				anzahlWI++;
				anzahlWIs[anzahlPlaene] = anzahlWI;
			}
			if (artDesGebaeudes == 3) {
				anzahlSO++;
				anzahlSOs[anzahlPlaene] = anzahlSO;
			}
		}
		else if (menuepunkt == 3) {
			capy->flaecheFreigeben(plantest[anzahlPlaene], laengen[anzahlPlaene], breiten[anzahlPlaene]);
		}
		else if (menuepunkt == 4) {
			plan->bauflaecheAusgeben(plantest[anzahlPlaene], laengen[anzahlPlaene], breiten[anzahlPlaene]);
		}
		else if (menuepunkt == 5) {
			capy->welcheKosten(laengen[anzahlPlaene], breiten[anzahlPlaene], anzahlWAs[anzahlPlaene], anzahlWIs[anzahlPlaene], anzahlSOs[anzahlPlaene], artDesGebaeudes);
			plan->getKennzahl(anzahlWAs[anzahlPlaene], anzahlWIs[anzahlPlaene], anzahlSOs[anzahlPlaene], laengen[anzahlPlaene], breiten[anzahlPlaene]);
		}
		else if (menuepunkt == 6) {
			cout << "Exit. \n";
			return 0;
		}
	}
};

