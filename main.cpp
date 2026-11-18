#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_MOK = 100;
const int MAX_PAZ = 10;

// Patikrina, ar ivestas tikrai skaicius
int gautiSkaiciu() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Iveskite skaiciu: ";
    }
    return x;
}

int gautiPazymi() {
    int p = gautiSkaiciu();
    while (p < 1 || p > 10) {
        cout << "Pazymys turi buti nuo 1 iki 10. Bandykite dar karta: ";
        p = gautiSkaiciu();
    }
    return p;
}

int gautiNumeri(int max) {
    int nr = gautiSkaiciu();
    while (nr != 0 && (nr < 1 || nr > max)) {
        cout << "Neteisingas numeris (galima 1-" << max << ", 0 - atsaukti): ";
        nr = gautiSkaiciu();
    }
    return nr;
}

int main() {
    string vardai[MAX_MOK];
    int pazymiai[MAX_MOK][MAX_PAZ];
    int pazKiekis[MAX_MOK];
    int kiekMokiniu = 0;
    int pasirinkimas = 0;

    cout << fixed << setprecision(2);

    while (pasirinkimas != 7) {
        cout << "\n--- MOKINIU PAZYMIAI ---\n";
        cout << "1. Prideti mokini\n";
        cout << "2. Visi mokiniai ir pazymiai\n";
        cout << "3. Konkretaus mokinio pazymiai\n";
        cout << "4. Keisti pazymi\n";
        cout << "5. Mokinio vidurkis\n";
        cout << "6. Istrinti mokini\n";
        cout << "7. Iseiti\n";
        cout << "Pasirinkimas: ";
        pasirinkimas = gautiSkaiciu();

        switch (pasirinkimas) {
            case 1: {
                if (kiekMokiniu >= MAX_MOK) {
                    cout << "Sarasas pilnas!\n";
                    break;
                }
                cin.ignore();
                cout << "Mokinio vardas: ";
                getline(cin, vardai[kiekMokiniu]);
                while (vardai[kiekMokiniu].empty()) {
                    cout << "Iveskite varda: ";
                    getline(cin, vardai[kiekMokiniu]);
                }

                cout << "Kiek pazymiu ivesite (0-" << MAX_PAZ << ")? ";
                int k = gautiSkaiciu();
                while (k < 0 || k > MAX_PAZ) {
                    cout << "Iveskite skaiciu nuo 0 iki " << MAX_PAZ << ": ";
                    k = gautiSkaiciu();
                }

                for (int j = 0; j < k; j++) {
                    cout << j + 1 << "-as pazymys: ";
                    pazymiai[kiekMokiniu][j] = gautiPazymi();
                }
                pazKiekis[kiekMokiniu] = k;
                kiekMokiniu++;
                cout << "Mokinys pridetas.\n";
                break;
            }

            case 2: {
                if (kiekMokiniu == 0) {
                    cout << "Sarasas tuscias.\n";
                    break;
                }
                for (int i = 0; i < kiekMokiniu; i++) {
                    cout << i + 1 << ". " << vardai[i] << ": ";
                    if (pazKiekis[i] == 0) {
                        cout << "pazymiu nera";
                    } else {
                        for (int j = 0; j < pazKiekis[i]; j++) {
                            cout << pazymiai[i][j] << " ";
                        }
                    }
                    cout << endl;
                }
                break;
            }

            case 3: {
                if (kiekMokiniu == 0) {
                    cout << "Sarasas tuscias.\n";
                    break;
                }
                cout << "Mokinio numeris (1-" << kiekMokiniu << ", 0 - atgal): ";
                int nr = gautiNumeri(kiekMokiniu);
                if (nr == 0) break;

                int idx = nr - 1;
                cout << vardai[idx] << " pazymiai: ";
                if (pazKiekis[idx] == 0) {
                    cout << "pazymiu nera";
                } else {
                    for (int j = 0; j < pazKiekis[idx]; j++) {
                        cout << pazymiai[idx][j] << " ";
                    }
                }
                cout << endl;
                break;
            }

            case 4: {
                if (kiekMokiniu == 0) {
                    cout << "Sarasas tuscias.\n";
                    break;
                }
                cout << "Kurio mokinio pazymi keisti (1-" << kiekMokiniu << ", 0 - atgal)? ";
                int nr = gautiNumeri(kiekMokiniu);
                if (nr == 0) break;

                int idx = nr - 1;
                if (pazKiekis[idx] == 0) {
                    cout << "Sis mokinys neturi pazymiu.\n";
                    break;
                }

                cout << vardai[idx] << " pazymiai:\n";
                for (int j = 0; j < pazKiekis[idx]; j++) {
                    cout << "  " << j + 1 << ". " << pazymiai[idx][j] << endl;
                }

                cout << "Kurio pazymio numeri keisti (1-" << pazKiekis[idx] << ", 0 - atgal)? ";
                int pnr = gautiNumeri(pazKiekis[idx]);
                if (pnr == 0) break;

                cout << "Naujas pazymys: ";
                pazymiai[idx][pnr - 1] = gautiPazymi();
                cout << "Pazymys pakeistas.\n";
                break;
            }

            case 5: {
                if (kiekMokiniu == 0) {
                    cout << "Sarasas tuscias.\n";
                    break;
                }
                cout << "Mokinio numeris (1-" << kiekMokiniu << ", 0 - atgal): ";
                int nr = gautiNumeri(kiekMokiniu);
                if (nr == 0) break;

                int idx = nr - 1;
                if (pazKiekis[idx] == 0) {
                    cout << "Nera pazymiu, negalima apskaiciuoti vidurkio.\n";
                    break;
                }

                double suma = 0;
                for (int j = 0; j < pazKiekis[idx]; j++) {
                    suma += pazymiai[idx][j];
                }
                cout << vardai[idx] << " vidurkis: " << suma / pazKiekis[idx] << endl;
                break;
            }

            case 6: {
                if (kiekMokiniu == 0) {
                    cout << "Sarasas tuscias.\n";
                    break;
                }
                cout << "Kuri mokini istrinti (1-" << kiekMokiniu << ", 0 - atgal)? ";
                int nr = gautiNumeri(kiekMokiniu);
                if (nr == 0) break;

                // Perstumiame likusius elementus i kaire
                for (int i = nr - 1; i < kiekMokiniu - 1; i++) {
                    vardai[i] = vardai[i + 1];
                    pazKiekis[i] = pazKiekis[i + 1];
                    for (int j = 0; j < pazKiekis[i]; j++) {
                        pazymiai[i][j] = pazymiai[i + 1][j];
                    }
                }
                kiekMokiniu--;
                cout << "Mokinys istrintas.\n";
                break;
            }

            case 7:
                cout << "Darbas baigtas.\n";
                break;

            default:
                cout << "Tokio pasirinkimo nera.\n";
        }
    }

    return 0;
}