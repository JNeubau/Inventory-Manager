# Inventory-Manager

Tworzony przez nas system ma za zadanie ułatwić inwentaryzację stanu magazynów lub sklepu, pomagajac w zliczeniu i
porządkowaniu towarów. Aplikacja pozwala na dodawanie, usuwanie i opisywanie produktów. Dla ułatwienia pracy pomiędzy
zespołami możliwe jest dokonanie eksportu i importu bazy danych produktów. System jest głównie kierowany do osób
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
    * eksport bazy danych,
    * import bazy danych,
    * tworzenie przez użytkownika własnych kategorii produktów

2. Wymagania pozafunkcjonalne
    * prosty i przejrzysty interfejs użytkownika, wykonany terminalowov2
    * możliwość wprowadzenia dużej ilości produktów do bazy,
    * regularność zapisów do bazy danych

## Realizacja projektu ##

Oprogramowanie zostanie wykonane w postaci aplikacji desktopowej na komputery z systemem Windows (docelowo również
Linux). Projekt będzie korzystał z bibliotek do programowania aplikaci z interfejsem graficznym (np. z biblioteki wxWidgets).
Praca nad projektem będzie wzorować się na metodzie waterfall, która pozwoli na jasne rozdzielenie kolejnych etapów pracy
nad oprogramowaniem. W czasie prac projektowych korzystać będziemy z systemu kontroli wersji GIT, którego repozytorium
znajdzie się na platformie github.



## Kryteria akceptacyjne ##

Oprogramowanie pozwala na stworzenie nowej bazy danych z możliwością dodania, usunięcia i uaktualnienia informacji o
obiekcie oraz własnych kategorii produktów należących do bazy danych. Pozwala również na wgląd w utworzoną bazę danych,
zaimportowanie jej do innego formatu/bazy danych oraz utworzenie pliku z kodami kreskowymi. Wszystko to w przejrzystym,
przyjaznym dla użytkownika interfejsie.
