#include<iostream>
#include <utility>
using namespace std;

constexpr int max_count = 50;

class Date {
private:
    //Datumseigenschaften
    int Tag;
    int Monat;
    int Jahr;

public:
    string printDate() const;

    Date(const int TagInput, const int MonatInput, const int JahrInput) {
        Tag = TagInput;
        Monat = MonatInput;
        Jahr = JahrInput;
    }
};

string Date::printDate() const {
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
    float Sprung1{0};
    float Sprung2{0};
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
    Schueler(const Date &geb, string nameNeu, string vornameNeu)
        : Geburtsdatum(geb), name(std::move(nameNeu)), vorname(std::move(vornameNeu)),
          NoteJump(KEINE_NOTE), NoteImprovement(KEINE_NOTE), NoteHighest(KEINE_NOTE) {
    }


    //setter
    void setSprung1(const float sprung1) {
        Sprung1 = sprung1;
    }

    void setSprung2(const float sprung2) {
        Sprung2 = sprung2;
    }

    void setNote(const Note_Enum noteNew) {
        NoteJump = noteNew;
    }

    //getter
    string getName() const { return name; }

    string getVorname() const { return vorname; }

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
    float sprung2 = getSprung2();

    if (sprung2 < 3.00)
        NoteJump = UNGENUEGEND;
    else if (sprung2 < 3.49)
        NoteJump = MANGELHAFT;
    else if (sprung2 < 3.99)
        NoteJump = AUSREICHEND;
    else if (sprung2 < 4.49)
        NoteJump = BEFRIEDIGEND;
    else if (sprung2 < 4.99)
        NoteJump = GUT;
    else if (sprung2 >= 5)
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
    Schueler schueler[max_count]; // Array von bis zu 100 Schülern
    int anzahl_schueler; // Anzahl der hinzugefügten Schüler
    Schueler bestPerformance;
    Schueler bestImprovement;

public:
    void schuelerAnlegen(const Schueler &SchuelerNeu);

    void calculatePrice();

    void alleSchuelerAnzeigen();

    Schueler *schuelerSuchenByName(const string &vorname, const string &nachname);

    Lehrer() : schueler{}, anzahl_schueler(0), bestPerformance(Schueler()), bestImprovement(Schueler()) {
    }

    // getter
    Schueler &get_Schueler(const int index) {
        if (index >= 0 && index < anzahl_schueler) {
            return schueler[index];
        }
        throw out_of_range("Schueler index out of range");
    }

    Schueler &get_BestPerformance() {
        return bestPerformance;
    }

    Schueler &get_BestImprovement() {
        return bestImprovement;
    }

    int get_anzahl_schueler() const {
        return anzahl_schueler;
    }
};

// Pokal vergeben
void Lehrer::calculatePrice() {
    for (int i = 0; i < anzahl_schueler; i++) {
        if (schueler[i].getNoteJump() < bestPerformance.getNoteJump()) {
            bestPerformance = schueler[i];
        }
        if (schueler[i].getNoteImprovement() < bestPerformance.getNoteImprovement()) {
            bestImprovement = schueler[i];
        }
    }
}

// Funktion um einen Schueler zu suchen
Schueler *Lehrer::schuelerSuchenByName(const string &vorname, const string &nachname) {
    for (int i = 0; i < anzahl_schueler; i++) {
        if (schueler[i].getName() == nachname && schueler[i].getVorname() == vorname) {
            return &schueler[i];
        }
    }
    return nullptr;
}

// Funktion alle Schueler ausgeben
void Lehrer::alleSchuelerAnzeigen() {
    for (int i = 0; i < anzahl_schueler; i++) {
        schueler[i].anzeigen();
    }
}

// Funktion zum Anlegen
void Lehrer::schuelerAnlegen(const Schueler &SchuelerNeu) {
    if (anzahl_schueler < max_count) {
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
                Schueler neuerSchueler(geb, vorname, name);
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

                Schueler *found = meinLehrer.schuelerSuchenByName(vorname, name);
                if (found == nullptr) {
                    cout << "Schueler konnte nicht gefunden werden!" << endl;
                } else {
                    cout << "Schueler gefunden!" << endl;
                    found->anzeigen();
                }
                break;
            }
            case 4: {
                cout << "\n--- Sprung 1 eintragen ---" << endl;
                int counter = 0;
                int maxCount = meinLehrer.get_anzahl_schueler();
                float sprungNeu;
                do {
                    Schueler &tmp = meinLehrer.get_Schueler(counter); // Adresse holen
                    if (tmp.getSprung1() == 0) {
                        cout << "\n Fuer Schueler: " << endl;
                        cout << tmp.getVorname() + " " + tmp.getName();
                        cout << "\n Sprung 1 eintragen: " << endl;
                        cin >> sprungNeu;
                        tmp.setSprung1(sprungNeu);
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
                    Schueler &tmp = meinLehrer.get_Schueler(counter); // Adresse holen
                    if (tmp.getSprung2() == 0) {
                        cout << "\n Fuer Schueler: " << endl;
                        cout << tmp.getVorname() + " " + tmp.getName();
                        cout << "\n Sprung 2 eintragen: " << endl;
                        cin >> sprungNeu;
                        tmp.setSprung2(sprungNeu);
                    }
                    counter++;
                } while (counter < maxCount);

                break;
            }
            case 0: {
                cout << "Programm wird beendet." << endl;
                meinLehrer.calculatePrice(); //Hier wird der Pokal "vergeben"
                Schueler &tmp = meinLehrer.get_BestImprovement(); // Beste Leistung wird geholt
                Schueler &tmp2 = meinLehrer.get_BestPerformance(); // Beste Steigerung wird geholt
                cout << "Beste Leistung: " << endl;
                tmp2.anzeigen();

                cout << "Beste Performance: " << endl;
                tmp.anzeigen();
                break;
            }
            default:
                cout << "Ungueltige Auswahl!" << endl;
        }
    }

    return 0;
}
