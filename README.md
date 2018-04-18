# Zadanie Drzewo

## Opis zadania

Celem zadania jest implementacja drzewiastej struktury danych w oparciu o listy dwukierunkowe. Początkowo struktura zawiera jeden wierzchołek (korzeń) o numerze 0.

## Operacje na strukturze

`ADD_NODE <k>`

Dodaje nowy wierzchołek o numerze o jeden większym od poprzednio utworzonego. Jego rodzicem staje się wierzchołek o numerze <k>. Ustalamy, że nowy wierzchołek umiejscowiony zostaje na prawo od pozostałych dzieci <k>.

`RIGHTMOST_CHILD <k>`

Wypisuje numer wierzchołka, który jest skrajnie prawym dzieckiem <k>. Jeśli <k> jest liściem, wypisuje -1.

`DELETE_NODE <k>`

Usuwa wierzchołek o numerze <k> (k różne od 0). Krawędzie wychodzące z usuniętego wierzchołka w stronę dzieci zostają zaczepione w jego rodzicu, w tym samym miejscu, z którego wychodziła krawędź w stronę <k>. Kolejność pomiędzy krawędziami zostaje zachowana.

`DELETE_SUBTREE <k>`

Usuwa wierzchołek o numerze <k> (k różne od 0) razem z całym jego poddrzewem.

`SPLIT_NODE <k> <w>`

Dodaje nowy wierzchołek o numerze o jeden większym od poprzednio utworzonego. Jego rodzicem staje się wierzchołek o numerze <k>. Nowy wierzchołek umiejscowiony zostaje na prawo od wierzchołka <w> (można założyć, że <k> jest rodzicem <w>). Dodatkowo wszystkie krawędzie wychodzące z <k>, będące na prawo od wierzchołka o numerze <w>, zostają zaczepione w nowym wierzchołku, z zachowaniem kolejności.

Można założyć, że wierzchołki, których numery występują w poleceniach, znajdują się w strukturze. Wymagamy użycia listy do reprezentacji krawędzi wychodzących z wierzchołków. Każda pojedyncza operacja powinna działać w czasie stałym, za wyjątkiem DELETE_SUBTREE, gdzie czas działania powinien być proporcjonalny do rozmiaru usuwanego poddrzewa. Ponadto po wykonaniu operacji różnej od RIGHTMOST_CHILD należy wypisać jedną linię ze słowem OK.
