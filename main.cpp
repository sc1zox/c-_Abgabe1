#include<iostream>
using namespace std;

class Date {
private:
    //Datumseigenschaften
    int Tag;
    int Monat;
    int Jahr;

public:
    //Forward Deklaration damit Compiler bescheid weiß
    string printDate() const;

    // Konstruktor um die privaten Attribute bei initalisierung zu setzen
    Date(int TagInput,int MonatInput,int JahrInput) {
        Tag = TagInput;
        Monat = MonatInput;
        Jahr = JahrInput;
    }
};

// Methodenimpl außerhalb der Klasse, Date:: um Zugehörigkeit zu definieren + const um zu signalisieren, dass die Methode das Objekt nicht aendert.
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
    float Sprung1;
    float Sprung2;
    Note_Enum NoteJump;
    Note_Enum NoteImprovement;
    Note_Enum NoteHighest;

public:
    //Forward Deklaration damit Compiler bescheid weiß
    void calculateNote();

    void calculateIncrease();

    void anzeigen();

    // Konstruktor default
    Schueler() : name("default"), vorname("default"), Geburtsdatum(Date(0, 0, 0)), NoteJump(KEINE_NOTE),
                 NoteImprovement(KEINE_NOTE), NoteHighest(KEINE_NOTE) {
    }

    // Konstruktor mit Parameter
    Schueler(Date geb, string nameNeu, string vornameNeu)
        : Geburtsdatum(geb), name(nameNeu), vorname(vornameNeu),
          NoteJump(KEINE_NOTE), NoteImprovement(KEINE_NOTE), NoteHighest(KEINE_NOTE) {
    }


    //setter Methoden
    void setSprung1(float sprung1) {
        Sprung1 = sprung1;
    }

    void setSprung2(float sprung2) {
        Sprung2 = sprung2;
    }

    void setNote(Note_Enum noteNew) {
        NoteJump = noteNew;
    }

    //getter Methoden
    string getName() { return name; }

    string getVorname() { return vorname; }

    float getSprung1() { return Sprung1; }
    float getSprung2() { return Sprung2; }
    Note_Enum getNoteJump() { return NoteJump; }
    Note_Enum getNoteImprovement() { return NoteImprovement; }
};

// Berechnung der Verbesserung eines Schuelers
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

// Berechnung der Note anhand der Weite eines Schuelers
void Schueler::calculateNote() {
    float sprung1 = getSprung1();
    float sprung2 = getSprung2();
    // ternary operator to take the best jump of the 2 jumps
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

// Methode um Schueler auf der Konsole auszugeben, ebenso werden beide Notenmethoden hier aufgerufen
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

    //Forward Deklaration damit Compiler bescheid weiß
    void schuelerAnlegen(Schueler SchuelerNeu);

    void calculatePrice();

    void alleSchuelerAnzeigen();

    Schueler* schuelerSuchenByName(string vorname,string nachname);

    bool schuelerLoeschen(string vorname,string name);

    Lehrer() : schueler{}, anzahl_schueler(0), bestPerformance(Schueler()), bestImprovement(Schueler()) {
    }

    // getter Methoden
    Schueler* getSchueler(int index) {
        if (index >= 0 && index < anzahl_schueler) {
            return &schueler[index];
        }
        throw out_of_range("Schueler index out of range");
    }

    Schueler getBestPerformance() {
        return bestPerformance;
    }

    Schueler getBestImprovement() {
        return bestImprovement;
    }

    int getAnzahlSchueler() {
        return anzahl_schueler;
    }
};
// Hier wird die static int gesetzt damit das Array initalisiert werden kann
int Lehrer::max_schueler = 50;

// Schueler überschreiben mit letztem array eintrag
bool Lehrer::schuelerLoeschen(string vorname, string name) {
    for (int i = 0; i < anzahl_schueler; i++) {
        if (schueler[i].getName() == name && schueler[i].getVorname() == vorname) {
            schueler[i] = schueler[anzahl_schueler - 1];
            anzahl_schueler--;
            cout << "Schueler wurde geloescht." << endl;
            return true;
        }
    }
    cout << "Schueler nicht gefunden!" << endl;
    return false;
}



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

// Funktion um einen Schueler zu suchen, Adresse zurück geben um Wert zu beschreiben
Schueler* Lehrer::schuelerSuchenByName(string vorname, string nachname) {
    for (int i = 0; i < anzahl_schueler; i++) {
        if (schueler[i].getName() == nachname && schueler[i].getVorname() == vorname) {
            return &schueler[i];
        }
    }
    cout<< "Schueler nicht gefunden!" << endl;
    return nullptr; // damit programm nicht abstürzt, null check in main
}

// Funktion um alle Schueler auszugeben
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

    // EVAL Programm um mit while Schleifen und switch statements+ eine Konsolenapplikation zu bauen

    while (auswahl != 0) {
        cout << "=== Lehrer-Schueler-Verwaltung ===" << endl;
        cout << "[1] Schueler anlegen" << endl;
        cout << "[2] Alle Schueler anzeigen" << endl;
        cout << "[3] Einen Schueler suchen und Loeschen" << endl;
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
                cout << "\n--- Einen Schueler suchen und Loeschen ---" << endl;
                string name, vorname;

                cout << "\n--- Name und Vorname bitte eingeben ---" << endl;
                cout << "Vorname: ";
                cin >> vorname;
                cout << "Nachname: ";
                cin >> name;

                Schueler* found = meinLehrer.schuelerSuchenByName(vorname, name);
                if (found) {
                    cout << "Schueler gefunden!" << endl;
                    found->anzeigen();
                }

                int subauswahl = -1;

                while (subauswahl != 0) {
                    cout << "=== Schueler-Verwaltung ===" << endl;
                    cout << "[1] Schueler loeschen" << endl;
                    cout << "[0] zurueck ins Hauptmenu"  << endl;
                    cin >> subauswahl;
                    switch (subauswahl) {
                        case 1: {
                            // null pointer check
                            if (!found) {
                                cout << "Schueler nicht gefunden!" << endl;
                                break;
                            }
                            bool isDeleted = meinLehrer.schuelerLoeschen(found->getVorname(), found->getName());
                            if (isDeleted) {
                                cout << "\n--- Schueler geloescht ---" << endl;
                            }
                            subauswahl = 0;
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
                int maxCount = meinLehrer.getAnzahlSchueler();
                float sprungNeu;
                do {
                    Schueler* tmp = meinLehrer.getSchueler(counter);  // Pointer holen um Sprung reinzueschreiben, da sonst copy by value
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
                int maxCount = meinLehrer.getAnzahlSchueler();
                float sprungNeu;
                do {
                    Schueler* tmp = meinLehrer.getSchueler(counter); // Pointer holen um Sprung reinzueschreiben, da sonst copy by value
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
                Schueler tmp = meinLehrer.getBestImprovement(); // Beste Steigerung wird geholt
                Schueler tmp2 = meinLehrer.getBestPerformance(); // Beste Leistung wird geholt
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
