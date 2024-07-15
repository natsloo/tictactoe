#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <thread>
#include <chrono> // Potrzebne do std::chrono::seconds

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
int level;

int e_sesja_wygrane = 0;
int e_sesja_przegrane = 0;
int e_sesja_remisy = 0;

int t_sesja_wygrane = 0;
int t_sesja_przegrane = 0;
int t_sesja_remisy = 0;

int e_alltime_wygrane;
int e_alltime_przegrane;
int e_alltime_remisy;

int t_alltime_wygrane;
int t_alltime_przegrane;
int t_alltime_remisy;

void sleep_seconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void load_alltime_stats() {
    std::ifstream loader("stats.txt");
    if (loader.is_open()) {
        loader >> e_alltime_wygrane >> e_alltime_przegrane >> e_alltime_remisy;
        loader >> t_alltime_wygrane >> t_alltime_przegrane >> t_alltime_remisy;
        loader.close();
    }
}

void save_alltime_stats() {
    std::ofstream saver("stats.txt");
    if (saver.is_open()) {
        saver << e_alltime_wygrane << " " << e_alltime_przegrane << " " << e_alltime_remisy << "\n";
        saver << t_alltime_wygrane << " " << t_alltime_przegrane << " " << t_alltime_remisy << "\n";
        saver.close();
    }
}

void sesja_stats() {
        std::cout << "Stats from this session - easy:\n";
        std::cout << "Wins: " << e_sesja_wygrane << std::endl;
        std::cout << "Losses: " << e_sesja_przegrane << std::endl;
        std::cout << "Draws: " << e_sesja_remisy << std::endl;
        std::cout << "\nStats from this session - hard:\n";
        std::cout << "Wins: " << t_sesja_wygrane << std::endl;
        std::cout << "Losses: " << t_sesja_przegrane << std::endl;
        std::cout << "Draws: " << t_sesja_remisy << std::endl;
        std::cout<<std::endl;
}
void alltime_stats(){
        std::cout << "Alltime stats - easy:\n";
        std::cout << "Wins: " << e_alltime_wygrane << std::endl;
        std::cout << "Losses: " << e_alltime_przegrane << std::endl;
        std::cout << "Draws: " << e_alltime_remisy << std::endl;
        std::cout << "\nAlltime stats - hard:\n";
        std::cout << "Wins: " << t_alltime_wygrane << std::endl;
        std::cout << "Losses: " << t_alltime_przegrane << std::endl;
        std::cout << "Draws: " << t_alltime_remisy << std::endl;
        std::cout << std::endl;
}

void plansza_init() {
    if (level == 1) {
        std::cout << "Level: easy.\n\n";
    }
    else if (level == 2) {
        std::cout << "Level: hard.\n\n";
    }
    std::cout << "This is what the board layout looks like:\n\n";
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
    std::cout << "Your move! Choose a field.\n";
    std::cin >> pole;
    while (pole < 1 || pole > 9) {
        std::cout << "No such filed exists. Choose a number between 1 and 9.\n";
        std::cin >> pole;
    }
    while (!puste_pole_checker(pole)) {
        std::cout << "This field is already taken. Choose another one.\n";
        std::cin >> pole;
    }
    wykonaj_ruch(pole, gracz_znaczek);
    system("cls");
    plansza_init();
    rysuj_plansze();
}

void komputer_ruch() {
    int pole = rand() % 9 + 1;
    while (!puste_pole_checker(pole)) {
        pole = rand() % 9 + 1;
    }
    wykonaj_ruch(pole, komputer_znaczek);
    system("cls");
    plansza_init();
    std::cout << "The computer has chosen filed number "<<pole<<"!\n\n";
    rysuj_plansze();
}

void komputer_ruch_medium() {
    //check czy komputer może wygrać w jednym ruchu
    for (int p = 1; p < 10; p++ ) {
        if (puste_pole_checker(p)) {
            wykonaj_ruch(p, komputer_znaczek);
            if (wygrana_checker(komputer_znaczek)) {
                system("cls");
                plansza_init();
                std::cout << "The computer has chosen filed number " << p << "!\n\n";
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
                plansza_init();
                std::cout << "The computer has chosen filed number " << p << "!\n\n";
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
    if (level == 1) {
        if (wygrana_checker(gracz_znaczek)) {
            std::cout << ANSI_COLOR_GREEN << "Congrats! You've won! :D\n" << ANSI_COLOR_RESET;
            e_sesja_wygrane++;
            e_alltime_wygrane++;
        }
        else if (wygrana_checker(komputer_znaczek)) {
            std::cout << ANSI_COLOR_RED << "This time the computer was better :(\n" << ANSI_COLOR_RESET;
            e_sesja_przegrane++;
            e_alltime_przegrane++;
        }
        else if (remis_checker()) {
            std::cout << ANSI_COLOR_YELLOW << "Draw!\n" << ANSI_COLOR_RESET;
            e_sesja_remisy++;
            e_alltime_remisy++;
        }
    }
    else if (level == 2) {
        if (wygrana_checker(gracz_znaczek)) {
            std::cout << ANSI_COLOR_GREEN << "Congrats! You've won! :D\n" << ANSI_COLOR_RESET;
            t_sesja_wygrane++;
            t_alltime_wygrane++;
        }
        else if (wygrana_checker(komputer_znaczek)) {
            std::cout << ANSI_COLOR_RED << "This time the computer was better :(\n" << ANSI_COLOR_RESET;
            t_sesja_przegrane++;
            t_alltime_przegrane++;
        }
        else if (remis_checker()) {
            std::cout << ANSI_COLOR_YELLOW << "Draw!\n" << ANSI_COLOR_RESET;
            t_sesja_remisy++;
            t_alltime_remisy++;
        }
    }
    save_alltime_stats();
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

void stats_viewer() {
    load_alltime_stats();
    system("cls");
    std::cout << "What stats would you like to see?:\n1 - Current session stats\n2 - Alltime stats\n3 - 1+2\n";
    int s;
    while (!(std::cin >> s) || s < 1 || s > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "No such stats exist. Choose a number between 1 and 3.\n";
    }
    if (s == 1) {
        system("cls");
        sesja_stats();
    }
    else if (s == 2) {
        system("cls");
        alltime_stats();
    }
    else if (s == 3) {
        system("cls");
        sesja_stats();
        std::cout << std::endl;
        alltime_stats();
    }
    std::cout << "\nPress any key to return to Menu.\n";
    system("pause");
}

void menu() {
   
    std::string znaczek;
    std::cout << "Which sign would you like to play with? Choose X or O.\n";
    std::cin >> znaczek;
    while (znaczek != "o" && znaczek != "O" && znaczek != "x" && znaczek != "X") {
        std::cout << "No such sign exists. Choose X or O\n";
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
    std::cout << "\nWould you like to choose a colour for your sign?\nPress Y to go to the colour selection screen or N to continue with the default colour.\n";
    std::cin >> czy;
    while (czy != "n" && czy != "N" && czy != "y" && czy != "Y") {
        std::cout << "Press Y to go to the colour selection screen or N to continue with the default colour.\n";
        std::cin >> czy;
    }
    if (czy == "y" || czy == "Y") {
        system("cls");
        int kolor;
        std::cout << "Choose a colour:\n";
        std::cout << ANSI_COLOR_RED << "1 - Red" << ANSI_COLOR_RESET << "\n";
        std::cout << ANSI_COLOR_GREEN << "2 - Green" << ANSI_COLOR_RESET << "\n";
        std::cout << ANSI_COLOR_YELLOW << "3 - Yellow" << ANSI_COLOR_RESET << "\n";
        std::cout << ANSI_COLOR_BLUE << "4 - Blue" << ANSI_COLOR_RESET << "\n";
        std::cout << ANSI_COLOR_MAGENTA << "5 - Magenta" << ANSI_COLOR_RESET << "\n";
        std::cout << ANSI_COLOR_CYAN << "6 - Cyan" << ANSI_COLOR_RESET << "\n";
        std::cout << "7 - Random colour\n";
        while (!(std::cin >> kolor) || kolor < 1 || kolor>7) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "No such colour exists. Choose a number between 1 and 6.\n";
        }
        if (kolor == 7) {
            kolor = rand() & 6 + 1;
        }
        wybierz_kolor(kolor, gracz_znaczek);
        std::cout << "\n Your sign: " << gracz_znaczek << "!\n";
    }
    if (czy == "n" || czy == "N") {
        std::cout << "\n Your sign: " << gracz_znaczek << "!\n";
    }
    std::cout << "\nChoose the difficulty level:\n1 - Easy\n2 - Hard\n";
    while (!(std::cin >> level) || level != 1 && level != 2) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "No such level exists. Choose the correct number:\n1 - Easy\n2 - Hard\n";
    }

    std::cout << "\nWho shall start the game?\n1 - You\n2 - The computer\n";
    while (!(std::cin >> starter) || starter != 1 && starter != 2) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\tNo such player exists. Choose the correct number:\n1 - You\n2 - The computer\n";

    }

    system("cls");

    if (level == 1) {
        gameplay();
    }
    else if (level == 2) {
        gameplay_medium();
    }

    wyniki();

    std::cout << "\nWould you like to play again? If yes, press Y.\nIf you want to finish playing for now, press N.\nIf you want to see the stats, press S.\n";
    std::string tak;
    std::cin >> tak;
    while (tak != "y" && tak != "Y" && tak != "n" && tak != "N" && tak != "S" && tak != "s") {
        std::cout << "Press Y, if you want to play again.\nIf you want to see the stats, press S.\nIf you want to finish playing for now, press N.\n";
        std::cin >> tak;
    }
    if (tak == "n" || tak == "N") {
        system("cls");
        std::cout << ANSI_COLOR_GREEN<<"\n\n\tThanks for playing!\n\tSee you next time!\n\n"<<ANSI_COLOR_RESET;
        sleep_seconds(1);
        exit(0);
    }
    else if (tak == "y" || tak == "Y") {
        system("cls");
        menu();
    }
    else if (tak == "S" || tak == "s") {
        stats_viewer();
    }

}

void menu_init() {
    system("cls");
    std::string y;
    std::cout << ANSI_COLOR_MAGENTA<<"Welcome to Tic-tac-toe!"<<ANSI_COLOR_RESET<<"\nPress Y to start the game.\nPress S to see the stats.\nPress N to leave.\n";
    std::cin >> y;
    while (y != "Y" && y != "y" && y != "s" && y != "S" && y != "n" && y != "N") {
        std::cout << "Press Y to start the game.\nPress S to see the stats.\nPress N to leave.\n";
        std::cin >> y;
    }
    if (y == "Y" || y == "y") {
        system("cls");
        menu();
    }
    else if (y == "S" || y == "s") {
        stats_viewer();
    }
    else if (y == "n" || y == "N") {
        system("cls");
        std::cout << ANSI_COLOR_GREEN << "\n\n\tSee you next time!\n\n" << ANSI_COLOR_RESET;
        sleep_seconds(1);
        exit(0);
    }
}


int main()
{
    setlocale(LC_CTYPE, "Polish");
    srand(time(0));
    load_alltime_stats;
    while (true) {
        menu_init();
    }
    
}


