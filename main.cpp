#include<iostream>
#include <utility>
using namespace std;

class Date {
private:
    //Datumseigenschaften
    int Tag;
    int Monat;
    int Jahr;

public:
    string printDate();

    Date(int TagInput,int MonatInput,int JahrInput) {
        Tag = TagInput;
        Monat = MonatInput;
        Jahr = JahrInput;
    }
};

string Date::printDate() {
    return to_string(Tag) + "." + to_string(Monat) + "." + to_string(Jahr);
}

enum Note_Enum {
    SEHR_GUT = 1,
    GUT = 2,
    BEFRIEDIGEND = 3,
    AUSREICHEND = 4,
    MANGELHAFT = 5,
    UNGENUEGEND = 6,
    KEINE_NOTE = 7,
};

class Schueler {
private:
    //Schuelereigenschaften
    string name;
    string vorname;
    Date Geburtsdatum;
    float Sprung1;
    float Sprung2;
    Note_Enum NoteJump;
    Note_Enum NoteImprovement;
    Note_Enum NoteHighest;

public:
    void calculateNote();

    void calculateIncrease();

    void anzeigen();

    // Konstruktor default
    Schueler() : name("default"), vorname("default"), Geburtsdatum(Date(0, 0, 0)), NoteJump(KEINE_NOTE),
                 NoteImprovement(KEINE_NOTE), NoteHighest(KEINE_NOTE) {
    }

    // Konstruktor mit Parameter, used compiler optimization to pass by value and not copy it
    Schueler(Date geb, string nameNeu, string vornameNeu)
        : Geburtsdatum(geb), name(nameNeu), vorname(vornameNeu),
          NoteJump(KEINE_NOTE), NoteImprovement(KEINE_NOTE), NoteHighest(KEINE_NOTE) {
    }


    //setter
    void setSprung1(float sprung1) {
        Sprung1 = sprung1;
    }

    void setSprung2(float sprung2) {
        Sprung2 = sprung2;
    }

    void setNote(Note_Enum noteNew) {
        NoteJump = noteNew;
    }

    //getter
    string getName() { return name; }

    string getVorname() { return vorname; }

    float getSprung1() { return Sprung1; }
    float getSprung2() { return Sprung2; }
    Note_Enum getNoteJump() { return NoteJump; }
    Note_Enum getNoteImprovement() { return NoteImprovement; }
};

void Schueler::calculateIncrease() {
    float sprung1 = getSprung1();
    float sprung2 = getSprung2();
    float difference = sprung2 - sprung1;

    if (difference <= 0.1)
        NoteImprovement = UNGENUEGEND;
    else if (difference <= 0.2)
        NoteImprovement = MANGELHAFT;
    else if (difference <= 0.3)
        NoteImprovement = AUSREICHEND;
    else if (difference <= 0.4)
        NoteImprovement = BEFRIEDIGEND;
    else if (difference <= 0.5)
        NoteImprovement = GUT;
    else
        NoteImprovement = SEHR_GUT;
}


void Schueler::calculateNote() {
    float sprung1 = getSprung1();
    float sprung2 = getSprung2();
    float besterSprung = sprung1 >= sprung2 ? sprung1 : sprung2;

    if (besterSprung < 3.00)
        NoteJump = UNGENUEGEND;
    else if (besterSprung < 3.49)
        NoteJump = MANGELHAFT;
    else if (besterSprung < 3.99)
        NoteJump = AUSREICHEND;
    else if (besterSprung < 4.49)
        NoteJump = BEFRIEDIGEND;
    else if (besterSprung < 4.99)
        NoteJump = GUT;
    else if (besterSprung >= 5)
        NoteJump = SEHR_GUT;
    else
        NoteJump = KEINE_NOTE;
}

void Schueler::anzeigen() {
    calculateIncrease();
    calculateNote();
    NoteHighest = NoteImprovement < NoteJump ? NoteImprovement : NoteJump;
    cout << " Vorname: " << vorname << " Name: " << name << " Sprung 1: " << Sprung1 << " Sprung 2: " << Sprung2 <<
            ", Geburtsdatum: " << Geburtsdatum.printDate() << " Note: " << NoteHighest << endl;
}

class Lehrer {
private:
    static int max_schueler;
    Schueler schueler[50]; // Array von bis zu 50 Schülern
    int anzahl_schueler; // Anzahl der hinzugefügten Schüler
    Schueler bestPerformance;
    Schueler bestImprovement;

public:
    void schuelerAnlegen(Schueler SchuelerNeu);

    void calculatePrice();

    void alleSchuelerAnzeigen();

    Schueler schuelerSuchenByName(string vorname,string nachname);

    Lehrer() : schueler{}, anzahl_schueler(0), bestPerformance(Schueler()), bestImprovement(Schueler()) {
    }

    // getter
    Schueler* get_Schueler(int index) {
        if (index >= 0 && index < anzahl_schueler) {
            return &schueler[index];
        }
        throw out_of_range("Schueler index out of range");
    }

    Schueler get_BestPerformance() {
        return bestPerformance;
    }

    Schueler get_BestImprovement() {
        return bestImprovement;
    }

    int get_anzahl_schueler() {
        return anzahl_schueler;
    }
};

int Lehrer::max_schueler = 50;

// Pokal vergeben
void Lehrer::calculatePrice() {
    for (int i = 0; i < anzahl_schueler; i++) {
        if (schueler[i].getNoteJump() <= bestPerformance.getNoteJump()) {
            bestPerformance = schueler[i];
        }
        if (schueler[i].getNoteImprovement() <= bestPerformance.getNoteImprovement()) {
            bestImprovement = schueler[i];
        }
    }
}

// Funktion um einen Schueler zu suchen
Schueler Lehrer::schuelerSuchenByName(string vorname, string nachname) {
    for (int i = 0; i < anzahl_schueler; i++) {
        if (schueler[i].getName() == nachname && schueler[i].getVorname() == vorname) {
            return schueler[i];
        }
    }
    throw out_of_range("Schueler name not found");
}

// Funktion alle Schueler ausgeben
void Lehrer::alleSchuelerAnzeigen() {
    for (int i = 0; i < anzahl_schueler; i++) {
        schueler[i].anzeigen();
    }
}

// Funktion zum Anlegen
void Lehrer::schuelerAnlegen(Schueler SchuelerNeu) {
    if (anzahl_schueler < max_schueler) {
        schueler[anzahl_schueler] = SchuelerNeu;
        anzahl_schueler++;
    } else {
        cout << "Maximale Anzahl an Schülern erreicht!" << endl;
    }
}

int main() {
    Lehrer meinLehrer;

    int auswahl = -1;

    while (auswahl != 0) {
        cout << "=== Lehrer-Schueler-Verwaltung ===" << endl;
        cout << "[1] Schueler anlegen" << endl;
        cout << "[2] Alle Schueler anzeigen" << endl;
        cout << "[3] Einen Schueler suchen" << endl;
        cout << "[4] Sprung 1 eintragen" << endl;
        cout << "[5] Sprung 2 eintragen" << endl;
        cout << "[0] Beenden" << endl;
        cout << "Auswahl: ";
        cin >> auswahl;

        switch (auswahl) {
            case 1: {
                string name, vorname;
                int tag, monat, jahr;

                cout << "\n--- Neuen Schueler anlegen ---" << endl;
                cout << "Vorname: ";
                cin >> vorname;
                cout << "Nachname: ";
                cin >> name;
                cout << "Geburtstag (TT MM JJJJ): ";
                cin >> tag >> monat >> jahr;

                Date geb(tag, monat, jahr);
                Schueler neuerSchueler(geb, name,vorname );
                meinLehrer.schuelerAnlegen(neuerSchueler);
                cout << "Schueler wurde angelegt!" << endl;
                break;
            }
            case 2: {
                cout << "\n--- Alle Schueler auflisten ---" << endl;
                meinLehrer.alleSchuelerAnzeigen();
                break;
            }
            case 3: {
                cout << "\n--- Einen Schueler suchen ---" << endl;
                string name, vorname;

                cout << "\n--- Name und Vorname bitte eingeben ---" << endl;
                cout << "Vorname: ";
                cin >> vorname;
                cout << "Nachname: ";
                cin >> name;

                Schueler found = meinLehrer.schuelerSuchenByName(vorname, name);
                    cout << "Schueler gefunden!" << endl;
                    found.anzeigen();

                int subauswahl = -1;

                while (subauswahl != 0) {
                    cout << "=== Schueler-Verwaltung ===" << endl;
                    cout << "[1] Schueler loeschen" << endl;
                    cout << "[0] zurueck ins Hauptmenu"  << endl;
                    cin >> subauswahl;
                    switch (subauswahl) {
                        case 1: {
                            //TODO schüler löschen
                            cout << "\n--- Schueler geloescht ---" << endl;
                            break;
                        }
                        case 0: {
                            cout << "zurueck!" << endl;
                            break;
                        }
                        default:
                            cout << "Ungueltige Auswahl!" << endl;
                            break;
                    }
                }
                break;
            }
            case 4: {
                cout << "\n--- Sprung 1 eintragen ---" << endl;
                int counter = 0;
                int maxCount = meinLehrer.get_anzahl_schueler();
                float sprungNeu;
                do {
                    Schueler* tmp = meinLehrer.get_Schueler(counter);  // Pointer holen um Sprung reinzueschreiben, da sonst copy by value
                    if (tmp->getSprung1() == 0) {
                        cout << "\n Fuer Schueler: " << endl;
                        cout << tmp->getVorname() + " " + tmp->getName();
                        cout << "\n Sprung 1 eintragen: " << endl;
                        cin >> sprungNeu;
                        tmp->setSprung1(sprungNeu);
                    }
                    counter++;
                } while (counter < maxCount);

                break;
            }
            case 5: {
                cout << "\n--- Sprung 2 eintragen ---" << endl;
                int counter = 0;
                int maxCount = meinLehrer.get_anzahl_schueler();
                float sprungNeu;
                do {
                    Schueler* tmp = meinLehrer.get_Schueler(counter); // Pointer holen um Sprung reinzueschreiben, da sonst copy by value
                    if (tmp->getSprung2() == 0) {
                        cout << "\n Fuer Schueler: " << endl;
                        cout << tmp->getVorname() + " " + tmp->getName();
                        cout << "\n Sprung 2 eintragen: " << endl;
                        cin >> sprungNeu;
                        tmp->setSprung2(sprungNeu);
                    }
                    counter++;
                } while (counter < maxCount);

                break;
            }
            case 0: {
                cout << "Programm wird beendet." << endl;
                meinLehrer.calculatePrice(); //Hier wird der Pokal "vergeben"
                Schueler tmp = meinLehrer.get_BestImprovement(); // Beste Steigerung wird geholt
                Schueler tmp2 = meinLehrer.get_BestPerformance(); // Beste Leistung wird geholt
                cout << "Beste Verbesserung: " << endl;
                tmp2.anzeigen();

                cout << "Beste Leistung: " << endl;
                tmp.anzeigen();
                break;
            }
            default:
                cout << "Ungueltige Auswahl!" << endl;
                break;
        }
    }

    return 0;
}
