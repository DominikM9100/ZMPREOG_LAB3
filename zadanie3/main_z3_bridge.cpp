/*
1. Numer grupy: WEL24MX1S4
2. Imie i nazwisko: Dominik Majak
3. Data wykonania: 2024-05-20
4. Srodowisko: Ubuntu 24.04 LTS, kompilacja i uruchomienie z poziomu konsoli
   Kompilacja: g++ -std=c++17 main_z3_bridge.cpp -o bridge
   Uruchomienie: ./bridge
5. Cel programu: Demonstracja wzorca projektowego Bridge, ktory oddziela
   abstrakcje (wiadomosci) od implementacji (sposobow wyswietlania).
*/


#include <iostream>
#include <string>


// Interfejs dla sposobu wyswietlania tekstu
class IWyswietlaczImpl
{
public:
  virtual ~IWyswietlaczImpl() = default;
  virtual std::string wyswietl(const std::string& tekst) const = 0;
  virtual std::string pobierzTypWyswietlania() const = 0;
};


// zwykle wyswietlanie tekstu
class NormalnyWyswietlacz : public IWyswietlaczImpl
{
public:
  std::string wyswietl(const std::string& tekst) const override
  {
    return tekst;
  }

  std::string pobierzTypWyswietlania() const override
  {
    return "Normalny";
  }
};


// wyswietlanie z wyroznieniem (otoczone gwiazdkami)
class PodswietlonyWyswietlacz : public IWyswietlaczImpl
{
private:
  std::string stworzLinieGwiazdek(int dlugosc) const
  {
    return std::string(dlugosc + 4, '*');
  }

public:
  std::string wyswietl(const std::string& tekst) const override
  {
    if (tekst.empty()) return "*** (pusta wiadomosc) ***";

    std::string wynik;
    std::string liniaGwiazdek = stworzLinieGwiazdek(tekst.length());

    wynik = liniaGwiazdek + "\n";
    wynik += "* " + tekst + " *\n";
    wynik += liniaGwiazdek;

    return wynik;
  }

  std::string pobierzTypWyswietlania() const override
  {
    return "Wyrózniony (gwiazdki)";
  }
};

// klasa abstrakcyjna - wiadomosci
class Wiadomosc
{
protected:
  IWyswietlaczImpl* wyswietlaczImpl;  // Bridge do implementacji

public:
  Wiadomosc(IWyswietlaczImpl* impl) : wyswietlaczImpl(impl) {}
  virtual ~Wiadomosc()
  {
    // nie usuwaj wyswietlaczImpl, poniewaz jest zarzadzany przez uzytkownika
  }

  // prezentacja wiadomosci
  virtual std::string prezentuj(const std::string& tresc) const = 0;
  // wybierz typ wiadomosci
  virtual std::string pobierzTypWiadomosci() const = 0;
  // Getter typu wyswietlania
  std::string pobierzTypWyswietlania() const {
    return wyswietlaczImpl->pobierzTypWyswietlania();
  }
};


// zwykla wiadomosc
class NormalnaWiadomosc : public Wiadomosc
{
public:
  NormalnaWiadomosc(IWyswietlaczImpl* impl) : Wiadomosc(impl) {}

  std::string prezentuj(const std::string& tresc) const override
  {
    return wyswietlaczImpl->wyswietl(tresc);
  }

  std::string pobierzTypWiadomosci() const override
  {
    return "Zwykla wiadomosc";
  }
};


// wiadomosc ostrzegawcza
class OstrzegawczaWiadomosc : public Wiadomosc
{
public:
  OstrzegawczaWiadomosc(IWyswietlaczImpl* impl) : Wiadomosc(impl) {}

  std::string prezentuj(const std::string& tresc) const override
  {
    std::string trescZOstrzezeniem = "[OSTRZEZENIE]: " + tresc;
    return wyswietlaczImpl->wyswietl(trescZOstrzezeniem);
  }

  std::string pobierzTypWiadomosci() const override
  {
    return "Wiadomosc ostrzegawcza";
  }
};


void wyswietlMenu()
{
  std::cout << "\n=== DEMONSTRACJA WZORCA BRIDGE ===\n";
  std::cout << "Dostepne rodzaje wiadomosci:\n";
  std::cout << "1. Zwykla wiadomosc\n";
  std::cout << "2. Wiadomosc ostrzegawcza (z prefixem [OSTRZEZENIE])\n\n";

  std::cout << "Dostepne sposoby wyswietlania:\n";
  std::cout << "A. Normalny (zwykly tekst)\n";
  std::cout << "B. Wyrózniony (otoczony gwiazdkami)\n\n";

  std::cout << "Instrukcje:\n";
  std::cout << "- Wybierz rodzaj wiadomosci (1 lub 2)\n";
  std::cout << "- Wybierz sposob wyswietlania (A lub B)\n";
  std::cout << "- Wpisz tresc wiadomosci\n";
  std::cout << "- Wpisz 'RESET' aby wrocic do poczatku programu\n";
  std::cout << "- Wpisz 'exit' aby zakonczyc program\n";
  std::cout << "=====================================\n";
}


void wyswietlKonfiguracje(const Wiadomosc* wiadomosc, const std::string& tresc)
{
  if (!wiadomosc) return;

  std::cout << "\n=== KONFIGURACJA ===" << std::endl;
  std::cout << "Rodzaj wiadomosci:    " << wiadomosc->pobierzTypWiadomosci() << std::endl;
  std::cout << "Sposob wyswietlania:  " << wiadomosc->pobierzTypWyswietlania() << std::endl;
  std::cout << "Tresc wiadomosci:   \"" << tresc << "\"" << std::endl;
}


int main()
{
  bool programDziala = true;

  while (programDziala) {
    wyswietlMenu();

    // wybierz rodzaj wiadomosci
    std::string wyborTypu;
    std::cout << "\nWybierz rodzaj wiadomosci (1 lub 2): ";
    std::getline(std::cin, wyborTypu);

    if (wyborTypu == "RESET") {
      std::cout << "\n>>> RESET: Program zostal zresetowany.\n";
      continue;
    }

    if (wyborTypu == "exit") {
      std::cout << "\nKoniec programu.\n";
      break;
    }

    // wybierz sposob wyswietlania
    std::string wyborWyswietlania;
    std::cout << "Wybierz sposob wyswietlania (A lub B): ";
    std::getline(std::cin, wyborWyswietlania);

    if (wyborWyswietlania == "RESET") {
      std::cout << "\n>>> RESET: Program zostal zresetowany.\n";
      continue;
    }

    if (wyborWyswietlania == "exit") {
      std::cout << "\nKoniec programu.\n";
      break;
    }

    // wprowadz tresc wiadomosci
    std::string tresc;
    std::cout << "Wpisz tresc wiadomosci: ";
    std::getline(std::cin, tresc);

    if (tresc == "RESET") {
      std::cout << "\n>>> RESET: Program zostal zresetowany.\n";
      continue;
    }

    if (tresc == "exit") {
      std::cout << "\nKoniec programu.\n";
      break;
    }

    // utworz odpowiednia implementacje wyswietlania
    IWyswietlaczImpl* wyswietlaczImpl = nullptr;
    if (wyborWyswietlania == "A" || wyborWyswietlania == "a") {
      wyswietlaczImpl = new NormalnyWyswietlacz();
    } else if (wyborWyswietlania == "B" || wyborWyswietlania == "b") {
      wyswietlaczImpl = new PodswietlonyWyswietlacz();
    } else {
      std::cout << "\nNieprawidlowy wybor sposobu wyswietlania. Uzywam domyslnego (A).\n";
      wyswietlaczImpl = new NormalnyWyswietlacz();
    }

    // utworz odpowiednia wiadomosc
    Wiadomosc* wiadomosc = nullptr;
    if (wyborTypu == "1") {
      wiadomosc = new NormalnaWiadomosc(wyswietlaczImpl);
    } else if (wyborTypu == "2") {
      wiadomosc = new OstrzegawczaWiadomosc(wyswietlaczImpl);
    } else {
      std::cout << "\nNieprawidlowy wybor rodzaju wiadomosci. Uzywam domyslnego (1).\n";
      wiadomosc = new NormalnaWiadomosc(wyswietlaczImpl);
    }

    // wyswietl konfiguracje
    wyswietlKonfiguracje(wiadomosc, tresc);
        
    // prezentacja wiadomosci
    std::cout << "\n=== WYNIK ===" << std::endl;
    std::string wynik = wiadomosc->prezentuj(tresc);
    std::cout << wynik << std::endl;

    // wyczysc pamiec
    delete wiadomosc;
    delete wyswietlaczImpl;

  }
    
  return 0;
}