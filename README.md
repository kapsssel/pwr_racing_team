> inb4: wszystkie pliki o których niżej mowa zamieściłem w: kapsssel/pwr_racing_team/edit/main/pwr_racing_team_project
# Rozwiązanie zadania: Zadanie rekrutacyjne.pdf
### Pierwszym krokiem była decyzja jak będę chciał przechowywać mapę z węzłami w programie
Abym mógł za każdym odpaleniem programu zmieniać wartości dróg:
czerwonej - r
zielonej - g
niebieskiej - b
zdecydowałem się na ponumerowanie kolejnych węzłów od 1 do 15 jak widać na: __mapa.png__
następnie stworzyłem plik tekstowy: 
__mapa_drog.txt__ w który wpisałem połączenia kolejnych węzłów zgodnie ze schematem: __"nr_węzła nr_węzła_sąsiadującego kolor_drogi\n"__
### Lista sąsiedztwa
W programie do przechowywania _listy sąsiedztwa_ węzłów(__junctions__) wykorzystałem tablicę wektorów o typie __vertex__ _struct vertex{
    int nr;
    double cost;
};_ - wybór był podyktowany tym, że znałem ilość węzłów (tablica), ale nie znałem ilości sąsiadów poszczególnego węzła (vector) chciałem dynamicznie dodawać sąsiadów.
_Lista sąsiedztwa_ jest zczytywana przez program z pliku __mapa_drog.txt__ - takie rozwiązanie pozwala na łatwe zmienianie map, które program przetwarza (należy wtedy odpowiednio dostosować wielkosc tablicy vectorów oraz stałą __junctions__ - określającą ilość węzłów). W trakcie zczytywania program rozpoznaje kolor drogi i przypisuje odpowiedni koszt (wcześniej ustalony przez użytkownika) każdemu z sąsiadów (po drogach można jeździć w obie strony), na koniec dodaje do _listy sąsiadów_(vector) sąsiada1 numer sąsiada2 a do "listy sąsiadów" sąsiada2 numer sąsiada1. W ten sposob otrzymujemy tablice vectorów - _list sąsiadów_ gdzie numer tablicy to numer "właściciela" _listy_, a kazdy sąsiad z _listy_ właściciela ma informacje jaki jest koszt dojazdu do wlasciciela.
### Najkrotsza droga od punktu A do punktu B
Program rozbija problem kilku podróży na każdą podróż osobno i sumuje ich koszta: np dla trasy ABC - program osobno policzy drogi AB i BC i wyswietli sume ich kosztow
wyznaczanie drogi odbywa sie poprzez funkcje: __lowest_travel_cost( "tablica listy sąsiadów", punkt_start, punkt_stop)__ funkcja zwraca wartosc zmiennoprzecinkową która reprezentuje najmniejszy koszt drogi od punkt_start punkt_stop. Funkcja wykorzystuje do tego algorytm _dijkstra_ (funckja nie korzysta z idealnie odwzorowanego algorytmu Dijkstra tylko wolniejszej alternatywy ze zwykłą kolejką zamiast priorytetowej): który korzysta z tablicy __distance[i]__ (i=__junctions__) gdzie i-ta komórka przechowuje aktualny dystans i-tego węzła od __punkt_start__. Na początku funkcja ustawia wartość __big_enough__(=10000) dla kazdego węzła z wyjątkiem __punkt_start__, dla którego __distance[punkt_start]__=0. Następnie funkcja przy użyciu _kolejki_ (pierwszy w kolejce jest punkt_start, dalej beda pojawiac się numery kolejnych sasiadow), pętli _while_ oraz zawartej w niej pętli _for_(wykorzystujemy ją do przeglądania sąsiadów aktualnego węzła z _listy sąsiadów_) dociera do kolejnych sąsiadów naszego _grafu_ i sprawdza czy __distance[aktualnego węzła]+[koszt_drogi_do_aktualnie przegladany sasiad]__< __distance[aktualnie_przegladany_sasiad]__ jeśli tak to: __distance[aktualnie_przegladany_sasiad]__=__distance[aktualnego_węzła]+[koszt_drogi_do_aktualnie_przegladany_sasiad]__ i dodajemy __aktualnie_przegladany_sasiad__ do _kolejki_. Powtarzamy _while(!kolejka.empty())_. Ostatecznie optymalny koszt trasy z __punkt_start__ do __punkt_stop__ jest w __distance[punkt_stop]__, a więc return __distance[punkt_stop]__.
