# Rozwiązanie zadania 
inb4: wszystkie pliki o których niżej mowa zamieściłem w: kapsssel/pwr_racing_team/edit/main/pwr_racing_team_project 
### Pierwszym krokiem była decyzja jak będę chciał przechowywać mapę z węzłami w programie
Aebym mógł za każdym odpaleniem programu zmieniać wartości dróg:
czerwonej - r
zielonej - g
niebieskiej - b
zdecydowałem się na ponumerowanie kolejnych węzłów od 1 do 15 jak widać na: mapa.png
następnie stworzyłem plik tekstowy: 
mapa_drog.txt w który wpisałem połączenia kolejnych węzłów zgodnie ze schematem: "nr_węzła nr_węzła_sąsiadującego kolor_drogi\n"
### Lista sąsiedztwa
w programie do przechowywania listy sąsiedztwa skrzyżowań/węzłów(junctions) wykorzystałem tablicę wektorów o typie vertex(który przechowuje numer danego węzła oraz koszt drogi do sąsiada) - wybór był podyktowany tym, że znałem ilość węzłów(tablica), ale nie znałem ilości sąsiadów poszczególnego węzła(vector) chciałem dynamicznie dodawać sąsiadów
lista sąsiedztwa jest zczytywana przez program z pliku mapa_drog.txt - takie rozwiązanie pozwala na łatwe zmienianie map, które program przetwarza(należy wtedy odpowiednio dostosować wielkosc tablicy vectorów oraz stałą junctions - określającą ilość węzłów). W trakcie zczytywania program rozpoznaje kolor drogi i przypisuje odpowiedni koszt(wcześniej ustalony przez użytkownika) każdemu z sąsiadów (po drogach można jeździć w obu stronach), na koniec dodaje do __listy sąsiadów__(vector) sąsiada1 numer sąsiada2 a do "listy sąsiadów" sąsiada2 numer sąsiada1. W ten sposob otrzymujemy tablice vectorów - __list sąsiadów__ gdzie numer tablicy to numer "właściciela" listy, a kazdy sąsiad z listy właściciela ma informacje jaki jest koszt dojazdu do wlasciciela.
### Najkrotsza droga od punktu A do punktu B
Program rozbija problem kilku podróży na każdą podróż osobno i sumuje ich koszta:np dla trasy ABC - program osobno policzy drogi AB i BC i wyswitli sume ich kosztow
wyznaczanie drogi odbywa sie poprzez funkcje: lowest_travel_cost( "tablica listy sąsiadów", punkt_start, punkt_stop) funkcja zwraca wartosc zmiennoprzecinkową która reprezentuje najmniejszy koszt drogi od punkt_start punkt_stop. Funkcja wykorzystuje do tego algorytm dijkstra
