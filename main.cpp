#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int MAX_MOKINIU = 100;
const int MAX_PAZYMIU = 10;

// Nuskaito sveikaji skaiciu. Jei ivedama ne skaicius (pvz. raides), isvalo ivesti ir praso is naujo
int ivestiSkaiciu() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Klaida: iveskite sveikaji skaiciu: ";
    }
    return x;
}

// Nuskaito pazymi ir kartoja, kol jis bus skaleje nuo 1 iki 10
int ivestiPazymi() {
    int p = ivestiSkaiciu();
    while (p < 1 || p > 10) {
        cout << "Neteisingas pazymys. Iveskite skaiciu nuo 1 iki 10: ";
        p = ivestiSkaiciu();
    }
    return p;
}

int main() {
    string mokVard[MAX_MOKINIU];              // vienmatis masyvas - mokiniu vardai
    int mokPazym[MAX_MOKINIU][MAX_PAZYMIU];   // dvimatis masyvas - eilute = mokinys, stulpelis = pazymys
    int pazKiek[MAX_MOKINIU];                 // kiek pazymiu turi kiekvienas mokinys
    int mokKiek = 0;                          // kiek mokiniu yra sarase
    int pasirinkimas = 0;

    cout << fixed << setprecision(2);

// Meniu kartojamas, kol pasirenkama 7 (Iseiti)
    while (pasirinkimas != 7) {
        cout << "\nMOKINIU PAZYMIU SISTEMA\n";
        cout << "1. Ivesti mokini ir jo pazymius\n";
        cout << "2. Perziureti visu mokiniu pazymius\n";
        cout << "3. Perziureti konkretaus mokinio pazymius\n";
        cout << "4. Atnaujinti pazymi\n";
        cout << "5. Apskaiciuoti mokinio vidurki\n";
        cout << "6. Pasalinti mokini\n";
        cout << "7. Iseiti\n";
        cout << "Pasirinkite veiksma: ";
        pasirinkimas = ivestiSkaiciu();

        switch (pasirinkimas) {
            case 1: {
// Tikriname, ar nevirsytas mokiniu limitas
                if (mokKiek >= MAX_MOKINIU) {
                    cout << "Klaida: pasiektas mokiniu limitas (" << MAX_MOKINIU << ").\n";
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // isvalome likusi Enter po meniu pasirinkimo
                cout << "Iveskite mokinio varda: ";
                getline(cin, mokVard[mokKiek]);
                while (mokVard[mokKiek].empty()) {
                    cout << "Vardas negali buti tuscias. Iveskite varda: ";
                    getline(cin, mokVard[mokKiek]);
                }
// Pazymiu kiekis ribojamas nuo 0 iki 10
                cout << "Kiek pazymiu ivesite (0-" << MAX_PAZYMIU << ")? ";
                int kiek = ivestiSkaiciu();
                while (kiek < 0 || kiek > MAX_PAZYMIU) {
                    cout << "Neteisingas kiekis. Iveskite skaiciu nuo 0 iki " << MAX_PAZYMIU << ": ";
                    kiek = ivestiSkaiciu();
                }
                for (int j = 0; j < kiek; j++) {
                    cout << j + 1 << " pazymys: ";
                    mokPazym[mokKiek][j] = ivestiPazymi();
                }
                pazKiek[mokKiek] = kiek;
                mokKiek++;
                cout << "Mokinys pridetas. Mokiniu sarase: " << mokKiek << "\n";
                break;
            }
            case 2: {
                if (mokKiek == 0) {
                    cout << "Sarase nera mokiniu.\n";
                    break;
                }
// Isorinis ciklas eina per mokinius, vidinis - per to mokinio pazymius
                for (int i = 0; i < mokKiek; i++) {
                    cout << i + 1 << ". " << mokVard[i] << ": ";
                    if (pazKiek[i] == 0) {
                        cout << "(pazymiu nera)";
                    }
                    for (int j = 0; j < pazKiek[i]; j++) {
                        cout << mokPazym[i][j] << " ";
                    }
                    cout << "\n";
                }
                break;
            }
            case 7:
                cout << "Programa baigta.\n";
                break;
            default:
                cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 1 iki 7.\n";
        }
    }
    return 0;
}
