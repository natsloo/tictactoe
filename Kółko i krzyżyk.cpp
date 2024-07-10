#include <iostream>
#include <cstdlib>
#include <ctime>


std::string pola[3][3];
std::string gracz_znaczek;
std::string komputer_znaczek;
int starter;

//std::string switchCase(int wybor) {
//    switch (wybor) {
//    case 1:
//        return pola[0][0];
//
//    case 2:
//        return pola[0][1];
//
//    case 3:
//        return pola[0][2];
//  
//    case 4:
//        return pola[1][0];
//     
//    case 5:
//        return pola[1][1];
//        
//    case 6:
//        return pola[1][2];
//       
//    case 7:
//        return pola[2][0];
//        
//    case 8:
//        return pola[2][1];
//      
//    case 9:
//        return pola[2][2];
//       
//    }
//}

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
    switch (pole) {
    case 1: pola[0][0] = gracz_znaczek; break;
    case 2: pola[0][1] = gracz_znaczek; break;
    case 3: pola[0][2] = gracz_znaczek; break;
    case 4: pola[1][0] = gracz_znaczek; break;
    case 5: pola[1][1] = gracz_znaczek; break;
    case 6: pola[1][2] = gracz_znaczek; break;
    case 7: pola[2][0] = gracz_znaczek; break;
    case 8: pola[2][1] = gracz_znaczek; break;
    case 9: pola[2][2] = gracz_znaczek; break;
    }
    system("cls");
    plansza();
    rysuj_plansze();
}

void komputer_ruch() {
    int pole = rand() % 9 + 1;
    while (!puste_pole_checker(pole)) {
        pole= rand() % 9 + 1;
    }
    switch (pole) {
    case 1: pola[0][0] = komputer_znaczek; break;
    case 2: pola[0][1] = komputer_znaczek; break;
    case 3: pola[0][2] = komputer_znaczek; break;
    case 4: pola[1][0] = komputer_znaczek; break;
    case 5: pola[1][1] = komputer_znaczek; break;
    case 6: pola[1][2] = komputer_znaczek; break;
    case 7: pola[2][0] = komputer_znaczek; break;
    case 8: pola[2][1] = komputer_znaczek; break;
    case 9: pola[2][2] = komputer_znaczek; break;
    }
    system("cls");
    plansza();
    std::cout << "Komputer wybrał pole "<<pole<<"!\n\n";
    rysuj_plansze();
    
}

void menu() {
    std::string y;
    std::cout << "Witaj w grze kółko i krzyżyk!\nWciśnij Y, jeśli możemy zaczynać.\n";
    std::cin >> y;
    while(y != "Y" && y != "y") {
        std::cout << "Wciśnij Y, jeśli możemy zaczynać.\n";
        std::cin >> y;
    }
    system("cls");
    std::string znaczek;
    std::cout << "Jakim znaczkiem chcesz być? Wybierz x lub o\n";
    std::cin >> znaczek;
    while (znaczek != "o" && znaczek != "O" && znaczek != "x" && znaczek != "X") {
        std::cout << "Wpisałeś zły znaczek, spróbuj ponownie!\n";
        std::cin >> znaczek;
    }
    if (znaczek == "x" || znaczek == "X") {
        komputer_znaczek = "o";
    }
    else if (znaczek == "o" || znaczek == "O") {
        komputer_znaczek = "x";
    }
    gracz_znaczek = znaczek;
    std::cout << "Kto zaczyna? Wybierz odpowiedni numer:\n1 - Ty\n2 - Komputer\n";
    std::cin >> starter;
    while (starter != 1 && starter != 2) {
        std::cout<<"Nie ma takiego gracza. Wybierz poprawny numer:\n1 - Ty\n2 - Komputer\n";
        std::cin >> starter;
    }
    system("cls");
    plansza_init();
    zeruj_tablice();
    rysuj_plansze();
}

void wyniki() {
    if (wygrana_checker(gracz_znaczek)) {
        std::cout << "Gratulacje! Wygrałeś! :D\n";
    }
    else if (wygrana_checker(komputer_znaczek)) {
        std::cout << "Tym razem komputer okazał się lepszy :(\n";
    }
    else if (remis_checker()) {
        std::cout << "Remis!\n";
    }
}

void gameplay() {
    int kolej = starter;
    while (!wygrana_checker(komputer_znaczek)&&!wygrana_checker(gracz_znaczek)&&!remis_checker()) {
        //std::cout << "dziala\n";
        //std::cout << kolej << std::endl;
        if (kolej == 1) {
            //std::cout << "dziala\n";
            gracz_ruch();
            kolej = 2;
        }
        else if (kolej == 2) {
            komputer_ruch();
            kolej = 1;
        }
    }

}

int main()
{
    setlocale(LC_CTYPE, "Polish");
    srand(time(0));
    menu();
    gameplay();
    wyniki();
}


