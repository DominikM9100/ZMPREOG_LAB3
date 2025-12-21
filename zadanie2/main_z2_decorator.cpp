/*
1. Numer grupy: WEL24MX1S4
2. Imie i nazwisko: Dominik Majak
3. Data wykonania: 2024-05-20
4. Srodowisko: Ubuntu 24.04 LTS, kompilacja i uruchomienie z poziomu konsoli
   Kompilacja: g++ -std=c++17 main_z2_decorator.cpp -o decorator
   Uruchomienie: ./decorator
5. Cel programu: Demonstracja wzorca projektowego Decorator, ktory umozliwia
   dynamiczne rozszerzanie funkcjonalnosci obiektow bez modyfikacji ich klasy.
*/


#include <iostream>
#include <string>


// interfejs IPrinter - definiuje operację drukowania
class IPrinter
{
public:
  virtual ~IPrinter() = default;
  virtual std::string drukuj(const std::string& tekst) = 0;
};


// klasa implementujaca IPrinter
class BasicPrinter : public IPrinter
{
public:
  std::string drukuj(const std::string& tekst) override
  {
    return tekst;
  }
};


// dekorator 1 - tekst bez zmian
class PrinterDecorator : public IPrinter
{
protected:
  IPrinter* wrappedPrinter;

public:
  PrinterDecorator(IPrinter* printer) : wrappedPrinter(printer) {}

  virtual ~PrinterDecorator()
  {
    delete wrappedPrinter;
  }

  std::string drukuj(const std::string& tekst) override
  {
    return wrappedPrinter->drukuj(tekst);
  }
};


// dekorator 2 - dodaj numerowanie linii
class LineNumberDecorator : public PrinterDecorator
{
private:
  unsigned int lineCnt;
    
public:
  LineNumberDecorator(IPrinter* printer)
    : PrinterDecorator(printer), lineCnt(1) {}

  std::string drukuj(const std::string& tekst) override
  {
    std::string numText = "[" + std::to_string(lineCnt) + "] " + tekst;
    lineCnt++;
    return wrappedPrinter->drukuj(numText);
  }

  void resetCounter()
  {
    lineCnt = 1;
  }
};


void wyswietlMenu()
{
  std::cout << "\n=== DEMONSTRACJA WZORCA DECORATOR ===\n";
  std::cout << "Instrukcje:\n";
  std::cout << "- Wpisz tekst, aby go wydrukowac z numerem linii\n";
  std::cout << "- Wpisz pusta linie (enter) aby zakonczyc program\n";
  std::cout << "- Wpisz 'RESET' aby zrestartowac numerowanie linii\n";
  std::cout << "=======================================\n";
}


int main()
{
  wyswietlMenu();

  // dekorator z numerowaniem linii
  LineNumberDecorator printer(new BasicPrinter());
  std::string input;

  while (true)
  {
    std::cout << "\nWprowadz tekst (enter = koniec / \"RESET\" = reset numerowania): ";
    std::getline(std::cin, input);

    // koniec programu
    if (input.empty()) {
      std::cout << "\nWprowadzono pusta linie. Koniec programu.\n";
      break;
    }

    // sprawdz komende RESET
    if (input == "RESET") {
      std::cout << "\n>>> RESET: Numerowanie linii zostalo zresetowane.\n";
      printer.resetCounter();
      continue;
    }

    // drukuj z uzyciem dekoratora
    std::string wynik = printer.drukuj(input);
    std::cout << "--- Wynik drukowania ---\n";
    std::cout << wynik << std::endl;
  }
    
  return 0;
}