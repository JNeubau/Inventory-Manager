# Inventory-Manager

Tworzony przez nas system ma za zadanie ułatwić inwentaryzację stanu magazynów lub sklepu, pomagajac w zliczeniu i
porządkowaniu towarów. Aplikacja pozwala na dodawanie, usuwanie i opisywanie produktów. Dla ułatwienia pracy
możliwe jest dokonanie eksportu bazy danych produktów do pliku tekstowego. System jest głównie kierowany do osób
pracujących przy inwentaryzacji i magazynierów. Potrzebą utworzenia oprogramowania jest fakt, iż ręczna inwentaryzacja
zakłada wiele operacji, które należy przeprowadzać symultanicznie podczas sporządzania protokołu. Nasze oprogramowanie
ma ułatwić ten proces i pozwolić na łatwe wprowadzanie zmian dowolnego produktu w dowolnej chwili.

## Diagram klas ##

![](https://raw.githubusercontent.com/JNeubau/Inventory-Manager/main/uml.png)

## Wymagania systemowe ##

1. Wymagania funkcjonalne
    * dodawanie produktu do bazy danych,
    * usuwanie produktu z bazy danych,
    * modyfikowanie informacji o produkcie,
    * podgląd listy zapisanych produktów z podziałem na kategorie/zbiorczo,
    * eksport bazy danych do pliku tekstowego,
    * generowanie pliku tekstowego zawierającego nazwy produktów i odpowiadające im kody kreskowe,
    * tworzenie przez użytkownika własnych kategorii produktów

2. Wymagania pozafunkcjonalne
    * prosty i przejrzysty interfejs użytkownika, wykonany terminalowo,
    * możliwość wprowadzenia dużej ilości produktów do bazy,
    * łatwy wgląd w zawartość bazy danych

## Realizacja projektu ##

Oprogramowanie zostanie wykonane w postaci aplikacji terminalowej na komputery z systemem Linux (docelowo również
Windows). Projekt wzorowany jest na standardowym typie aplikacji konsolowej np. systemu Linux. Tj. zakłada się, że 
użytkownik zna komendy, a w razie wątpliwości może skorzystać z uniwersalnej komendy pomocy 'help'.

W czasie prac projektowych korzystać będziemy z systemu kontroli wersji GIT, którego repozytorium
znajdzie się na platformie github.

Nasz projekt zakłada porawność wpisywanych przez użytkownika wartości.


## Kryteria akceptacyjne ##

Oprodramowanie przy pierwszym uruchomieniu powinno stworzyć plik bazy danych w folderze
*database*. W konsoli wyświetli się wtedy komunkat o ewentualnym braku admina i możliwość
jego dodania lub panel do logowania, rejstracji i wyjścia z programu.

Admin bazy danych posiada opcje zmiany/uaktualniania/usuwania/dodawania użytkowników.
Aby zacząć korzystać z aplikacji konieczne jest posiadanie konta zwykłego użytkownika.

Program pozwala na dodanie nowego produktu do bazy danych przez komendę *new*.
Komenda *remove* pozawala na usunięcie predmiotu z bazy danych, a *modify* na zmodyfikowanie
informacji o produkcie, który już istnieje. Użytkownik ma też możliwość stworzenia bazy danych prduktów
zupełnie od nowa.

Aby nadzorować pracę nad bazą danych zostały też zaimplementowane komenty *show* pokazującą informacje
o pojedynczym produkcie oraz *showCat*, która pokzauje wszystkie produkty poukładane kategoriami.

Aby zapisać efekty swojej pracy, każdy użytkownik może też skorzystać z poleceń *importAll* (powoduje zapis całej utworzonej
bazy produktów do pliku tekstowego *'Database.txt'*) oraz *importBarcodes* (importuje do pliku tekstowego *'Barcodes.txt'*
tylko nazwy produktów wraz z odpowiadającym im kodem kreskowym).
Pliki tekstowe w oby przypadkach powinny sotać stworzone w głównym katalogu projektu
i być tworzone na nowo dla każdego wywołania komendy.
