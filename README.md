# Nurses Work Schedule

## Założenia

- Wszyscy pracownicy są unikalni
- Pracownik po 1 zmianie posiada 2 zmiany odpoczynku
- Każdy pracownik ma jeden weekend wolny

## Dzień roboczy

- 2 zmiany w godzinach:
  - 7:00 - 19:00
  - 19:00 - 7:00
- Minimum 2 pracowników na zmianie
- Możliwość zmodyfikowania ilości pracowników w danym dniu 
- 14 zmian * 5 = 70 zmian w miesiącu

## Funkcje

- Wejście/Wyjście
    - mode1 (raportowanie)
    - mode2 (urlopy)
    - mode3 (pracownicy)
- Raportowanie
    - Generuj raport
    - Wyświetl raport dla pracownika
    - Wyświetl raport dla zarządu
- Pracownicy
    - Lista pracowników
    - Dodaj pracownika
    - Usuń pracownika

## 3 pliki w formacie CSV

1. Pracownicy 
    - Format: `Imie; Nazwisko; Id`
2. Grafik
    - Format: `Dzien; Zmiana; Imie; Nazwsiko; Czy_nadgodziny`
3. Urlopy
    - Format: `Imie; Nazwisko; Dzien; Miesiąc; Rok; Czy_na_cały_dzień; zmiana`

## Klasy

- CSVFileReader:
    - readFile(filename) `zwraca macierz wektorów z liniami i kolumnami`
- IO (interface)
    - readcommand
- mainIO (IO)
    - switch mode
    - execute procedure
- Procedure (interface)
    - runprocedure
- generatePlan (Procedure)
- generatePlanForNurses (Procedure)
- generatePlanForAll (Procedure)
- help (Procedure)
- DateToPart
    - convertDateToString() `dostaje "20.12.2023" zwraca indeksy`
- Nurse
    - m_firstname
    - m_surname
    - id
    - (vector int) holidays `0 - 69`
    - dateToPart* converter
    - addHolidays (int part)
- Shift
    - day
    - month
    - year
    - part `1(7:00-19:00) 2(19:00-7:00)`
    - (vector *Nurses) nursesAtThisDay

## Harmonogram
- Mateusz Smolarek:
    1. Zrobić README.md :white_check_mark:
    2. Zmienić Kod Runner :white_check_mark:
    3. Input/Output
    4. Dołożyć kolejne testy
    5. Wstawić testy w podfoldery
- Michał Borzuchowski:
    1. Algorytm
    2. Wysyłanie plików
- Spotkania
    - 09.01.2024 :white_check_mark:
    - 12.01.2024 :white_check_mark:
