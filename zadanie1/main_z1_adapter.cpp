/*
1. Numer grupy: WEL24MX1S4
2. Imie i nazwisko: Dominik Majak
3. Data wykonania: 2024-05-20
4. Srodowisko: Ubuntu 24.04 LTS, kompilacja i uruchomienie z poziomu konsoli
   Kompilacja: g++ -std=c++17 main_z1_adapter.cpp -o adapter
   Uruchomienie: ./adapter
5. Cel programu: Demonstracja wzorca projektowego Adapter, ktory umozliwia 
   wspolprace klas o niezgodnych interfejsach bez modyfikacji ich kodu zrodlowego.
*/


#include <iostream>
#include <string>


// interfejs IPrinter - wymaga zwracania tekstu wielkimi literami
class IPrinter
{
public:
  virtual ~IPrinter() = default;
  virtual std::string drukuj(const std::string& tekst) const = 0;
};


// klasa SmallPrinter - niekompatybilna z IPrinter
class SmallPrinter
{
public:
  std::string printSmall(const std::string& tekst) const
  {
    std::string wynik = tekst;
    // konwersja na male litery
    for (char& znak : wynik) {
      if (znak >= 'A' && znak <= 'Z') znak = znak - 'A' + 'a';
    }
    return wynik;
  }
};


// Adapter
class PrinterAdapter : public IPrinter
{
private:
  SmallPrinter smallPrinter;    
  // funkcja do konwersji na wielkie litery
  std::string naWielkieLitery(const std::string& tekst) const
  {
    std::string wynik = tekst;
    for (char& znak : wynik) {
      if (znak >= 'a' && znak <= 'z') znak = znak - 'a' + 'A';
    }
    return wynik;
  }

public:
  std::string drukuj(const std::string& tekst) const override
  {
    // uzyj SmallPrinter
    std::string malymiLiterami = smallPrinter.printSmall(tekst);
    // konwertuj wynik na wielkie litery
    std::string wielkimiLiterami = naWielkieLitery(malymiLiterami);
    return wielkimiLiterami;
  }
};


void wyswietlMenu()
{
  std::cout << "\n=== DEMONSTRACJA WZORCA ADAPTER ===\n";
  std::cout << "1. Wprowadz tekst do wydrukowania\n";
  std::cout << "2. Wpisz 'RESET' aby zrestartowac program\n";
  std::cout << "3. Wpisz 'exit' aby zakonczyc program\n";
  std::cout << "===================================\n";
}


int main()
{
  bool programDziala = true;
    
  while (programDziala) {
    wyswietlMenu();

    PrinterAdapter adapter;
    std::string komenda;

    std::cout << "\nWprowadz tekst: ";
    std::getline(std::cin, komenda);

    // sprawdz komende 'RESET'
    if (komenda == "RESET") {
      std::cout << "\n>>> RESET: Program zostal zresetowany. Wracam do poczatku.\n";
      continue;
    }

    // sprawdz komende 'exit'
    if (komenda == "exit") {
      std::cout << "\nKoniec programu.\n";
      programDziala = false;
      continue;
    }

    // uzyj adaptera
    std::string wynik = adapter.drukuj(komenda);
    // bez adaptera
    SmallPrinter bezposrednio;
    std::string bezAdaptera = bezposrednio.printSmall(komenda);
    // pokaz roznice
    std::cout << "Bez adaptera (SmallPrinter):             \"" << bezAdaptera << "\"\n";
    std::cout << "Adapter (PrinterAdapter przez IPrinter): \"" << wynik << "\"\n";
  }

  return 0;
}