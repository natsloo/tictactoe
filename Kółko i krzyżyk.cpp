#include <iostream>
#include <cstdlib>
#include <ctime>

// Definicje kodów ANSI dla kolorów tekstu
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"

std::string pola[3][3];
std::string gracz_znaczek;
std::string komputer_znaczek;
int starter;


void plansza_init() {

    std::cout << "Tak wygląda rozkład planszy.\n\n";
    std::cout << " 1 | 2 | 3 " << std::endl;
    std::cout << "___|___|___" << std::endl;
    std::cout << " 4 | 5 | 6 " << std::endl;
    std::cout << "___|___|___" << std::endl;
    std::cout << "   |   |" << std::endl;
    std::cout << " 7 | 8 | 9 \n\n" << std::endl;
}

void plansza() {
    std::cout << " 1 | 2 | 3 " << std::endl;
    std::cout << "___|___|___" << std::endl;
    std::cout << " 4 | 5 | 6 " << std::endl;
    std::cout << "___|___|___" << std::endl;
    std::cout << "   |   |" << std::endl;
    std::cout << " 7 | 8 | 9 \n\n" << std::endl;
}

void zeruj_tablice() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            pola[i][j] = " ";
        }
    }
}

void rysuj_plansze() {
    std::cout << " " << pola[0][0] << " | " << pola[0][1] << " | " << pola[0][2] << std::endl;
    std::cout << "___|___|___" << std::endl;
    std::cout << " " << pola[1][0] << " | " << pola[1][1] << " | " << pola[1][2] << std::endl;
    std::cout << "___|___|___" << std::endl;
    std::cout << "   |   |" << std::endl;
    std::cout << " " << pola[2][0] << " | " << pola[2][1] << " | " << pola[2][2] << std::endl;
    std::cout << std::endl;
}

void wykonaj_ruch(int pole, std::string znaczek) {
    switch (pole) {
    case 1: pola[0][0] = znaczek; break;
    case 2: pola[0][1] = znaczek; break;
    case 3: pola[0][2] = znaczek; break;
    case 4: pola[1][0] = znaczek; break;
    case 5: pola[1][1] = znaczek; break;
    case 6: pola[1][2] = znaczek; break;
    case 7: pola[2][0] = znaczek; break;
    case 8: pola[2][1] = znaczek; break;
    case 9: pola[2][2] = znaczek; break;
    }
}

void wybierz_kolor(int wybór, std::string &znaczek) {
    switch (wybór) {
    case 1: znaczek = ANSI_COLOR_RED + znaczek + ANSI_COLOR_RESET; break;
    case 2: znaczek = ANSI_COLOR_GREEN + znaczek + ANSI_COLOR_RESET; break;
    case 3: znaczek = ANSI_COLOR_YELLOW + znaczek + ANSI_COLOR_RESET; break;
    case 4: znaczek = ANSI_COLOR_BLUE + znaczek + ANSI_COLOR_RESET; break;
    case 5: znaczek = ANSI_COLOR_MAGENTA + znaczek + ANSI_COLOR_RESET; break;
    case 6: znaczek = ANSI_COLOR_CYAN + znaczek + ANSI_COLOR_RESET; break;
    default: znaczek = ANSI_COLOR_WHITE + znaczek + ANSI_COLOR_RESET; break;
    }
}

void cofnij_ruch(int pole) {
    wykonaj_ruch(pole, " ");
}

bool wygrana_checker(std::string znaczek) {
    //sprawdzanie pionowo
    for (int i = 0; i < 3; i++) {
        if (pola[i][0] == znaczek && pola[i][1] == znaczek && pola[i][2] == znaczek) {
            return true;
        }
    }
    //sprawdzenie poziomo
    for (int i = 0; i < 3; i++) {
        if (pola[0][i] == znaczek && pola[1][i] == znaczek && pola[2][i] == znaczek) {
            return true;
        }
    }
    //sprawdzenie po I przekątnej
    if (pola[0][0] == znaczek && pola[1][1] == znaczek && pola[2][2] == znaczek) {
        return true;
    }

    //sprawdzenie po II przekątnej
    if (pola[0][2] == znaczek && pola[1][1] == znaczek && pola[2][0] == znaczek) {
        return true;
    }
    return false;
}

bool remis_checker() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (pola[i][j] == " ") {
                return false;
            }
        }
    }
    return true;
}

bool puste_pole_checker(int pole) {
    switch (pole) {
    case 1: return pola[0][0] == " ";
    case 2: return pola[0][1] == " ";
    case 3: return pola[0][2] == " ";
    case 4: return pola[1][0] == " ";
    case 5: return pola[1][1] == " ";
    case 6: return pola[1][2] == " ";
    case 7: return pola[2][0] == " ";
    case 8: return pola[2][1] == " ";
    case 9: return pola[2][2] == " ";
    default: return false;
    }
}

void gracz_ruch() {
    int pole;
    std::cout << "Twój ruch! Wybierz pole.\n";
    std::cin >> pole;
    while (pole < 1 || pole > 9) {
        std::cout << "Nie ma takiego pola. Wybierz pole między 1 a 9.\n";
        std::cin >> pole;
    }
    while (!puste_pole_checker(pole)) {
        std::cout << "To pole jest już zajęte, wybierz inne.\n";
        std::cin >> pole;
    }
    wykonaj_ruch(pole, gracz_znaczek);
    system("cls");
    plansza();
    rysuj_plansze();
}

void komputer_ruch() {
    int pole = rand() % 9 + 1;
    while (!puste_pole_checker(pole)) {
        pole = rand() % 9 + 1;
    }
    wykonaj_ruch(pole, komputer_znaczek);
    system("cls");
    plansza();
    std::cout << "Komputer wybrał pole "<<pole<<"!\n\n";
    rysuj_plansze();
}

void komputer_ruch_medium() {
    //check czy komputer może wygrać w jednym ruchu
    for (int p = 1; p < 10; p++ ) {
        if (puste_pole_checker(p)) {
            wykonaj_ruch(p, komputer_znaczek);
            if (wygrana_checker(komputer_znaczek)) {
                system("cls");
                plansza();
                std::cout << "Komputer wybrał pole " << p << "!\n\n";
                rysuj_plansze();
                return;
            }
            cofnij_ruch(p);    
        }
        
    }

    //check czy gracz może wygrać w jednym ruchu
    for (int p=1; p < 10; p++) {
        if (puste_pole_checker(p)) {
            wykonaj_ruch(p, gracz_znaczek);
            if (wygrana_checker(gracz_znaczek)) {
                cofnij_ruch(p);
                wykonaj_ruch(p, komputer_znaczek);
                system("cls");
                plansza();
                std::cout << "Komputer wybrał pole " << p << "!\n\n";
                rysuj_plansze();
                return;
            }
            cofnij_ruch(p);
        }
        
    }

    //defaultowo ruch z generatora
    komputer_ruch();
}

void wyniki() {
    if (wygrana_checker(gracz_znaczek)) {
        std::cout <<ANSI_COLOR_GREEN<< "Gratulacje! Wygrałeś! :D\n"<<ANSI_COLOR_RESET;
    }
    else if (wygrana_checker(komputer_znaczek)) {
        std::cout <<ANSI_COLOR_RED<< "Tym razem komputer okazał się lepszy :(\n" << ANSI_COLOR_RESET;
    }
    else if (remis_checker()) {
        std::cout << ANSI_COLOR_YELLOW<<"Remis!\n" << ANSI_COLOR_RESET;
    }
}

void gameplay() {
    int kolej = starter;
    plansza_init();
    zeruj_tablice();
    rysuj_plansze();
    while (!wygrana_checker(komputer_znaczek)&&!wygrana_checker(gracz_znaczek)&&!remis_checker()) {
        if (kolej == 1) {
            gracz_ruch();
            kolej = 2;
        }
        else if (kolej == 2) {
            komputer_ruch();
            kolej = 1;
        }
    }
}

void gameplay_medium() {
    int kolej = starter;
    plansza_init();
    zeruj_tablice();
    rysuj_plansze();
    while (!wygrana_checker(komputer_znaczek) && !wygrana_checker(gracz_znaczek) && !remis_checker()) {
        if (kolej == 1) {
            gracz_ruch();
            kolej = 2;
        }
        else if (kolej == 2) {
            komputer_ruch_medium();
            kolej = 1;
        }
    }
}

void menu() {
   
    std::string znaczek;
    std::cout << "Jakim znaczkiem chcesz być? Wybierz x lub o.\n";
    std::cin >> znaczek;
    while (znaczek != "o" && znaczek != "O" && znaczek != "x" && znaczek != "X") {
        std::cout << "Wpisałeś zły znaczek, spróbuj ponownie!\n";
        std::cin >> znaczek;
    }
    if (znaczek == "x" || znaczek == "X") {
        komputer_znaczek = "o";

        gracz_znaczek = "x";
    }
    else if (znaczek == "o" || znaczek == "O") {
        komputer_znaczek = "x";

        gracz_znaczek = "o";
    }

    std::string czy;
    std::cout << "\nCzy chcesz wybrać kolor swojego znaczka?\nWciśnij Y, by przejść do wyboru koloru lub N, by kontynować z kolorem domyślnym.\n";
    std::cin >> czy;
    while (czy != "n" && czy != "N" && czy != "y" && czy != "Y") {
        std::cout << "Wciśnij Y, by przejść do wyboru koloru lub N, by kontynuować z kolorem domyślnym.\n";
        std::cin >> czy;
    }
    if (czy == "y" || czy == "Y") {
        system("cls");
        int kolor;
        std::cout << "Wybierz kolor:\n";
        std::cout << ANSI_COLOR_RED << "1 - Czerwony" << ANSI_COLOR_RESET << "\n";
        std::cout << ANSI_COLOR_GREEN << "2 - Zielony" << ANSI_COLOR_RESET << "\n";
        std::cout << ANSI_COLOR_YELLOW << "3 - Żółty" << ANSI_COLOR_RESET << "\n";
        std::cout << ANSI_COLOR_BLUE << "4 - Niebieski" << ANSI_COLOR_RESET << "\n";
        std::cout << ANSI_COLOR_MAGENTA << "5 - Magenta" << ANSI_COLOR_RESET << "\n";
        std::cout << ANSI_COLOR_CYAN << "6 - Cyjan" << ANSI_COLOR_RESET << "\n";
        while (!(std::cin >> kolor) || kolor < 1 || kolor>6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nie ma takiego koloru. Wybierz liczbę od 1 do 6.\n";
        }
        wybierz_kolor(kolor, gracz_znaczek);
        std::cout << "\n Twój znaczek to: " << gracz_znaczek << "!\n";
    }
    int level;
    std::cout << "\nWybierz poziom trudności:\n1 - Łatwy\n2 - Trudny\n";
    while (!(std::cin >> level) || level != 1 && level != 2) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Nie ma takiego poziomu trudności. Wybierz poprawny numer:\n1 - Łatwy\n2 - Trudny\n";
    }

    std::cout << "\nKto zaczyna? Wybierz odpowiedni numer:\n1 - Ty\n2 - Komputer\n";
    while (!(std::cin >> starter) || starter != 1 && starter != 2) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Nie ma takiego gracza. Wybierz poprawny numer:\n1 - Ty\n2 - Komputer\n";

    }

    system("cls");

    if (level == 1) {
        gameplay();
    }
    else if (level == 2) {
        gameplay_medium();
    }

    wyniki();

    std::cout << "\nCzy chciałbyś zagrać jeszcze raz? Jeśli tak, wybierz Y, jeśli chcesz zakończyć rozgrywkę, wybierz N.\n";
    std::string tak;
    std::cin >> tak;
    while (tak != "y" && tak != "Y" && tak != "n" && tak != "N") {
        std::cout << "Wybierz Y, jeśli chcesz zagrać jeszcze raz. Jeśli chcesz zakończyć rozgrywkę, wybierz N.\n";
        std::cin >> tak;
    }
    if (tak == "n" || tak == "N") {
        std::cout << ANSI_COLOR_GREEN<<"\n\tDzięki za grę!\n\tDo zobaczenia następnym razem!\n"<<ANSI_COLOR_RESET;
        exit(0);
    }
    else if (tak == "y" || tak == "Y") {
        std::cout << "\n";
        menu();
    }

}

void menu_init() {
    std::string y;
    std::cout << "Witaj w grze kółko i krzyżyk!\nWciśnij Y, jeśli możemy zaczynać.\n";
    std::cin >> y;
    while (y != "Y" && y != "y") {
        std::cout << "Wciśnij Y, jeśli możemy zaczynać.\n";
        std::cin >> y;
    }
    system("cls");
    menu();
}


int main()
{
    setlocale(LC_CTYPE, "Polish");
    srand(time(0));
    menu_init();
    
}


