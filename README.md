# Makra napisane przez Zofię Judę, 09.02.2025

Folder zawiera makra napisane w środowisku ROOT. Aby móc je uruchomić, należy mieć zainstalowane środowisko ROOT.
## Klasa My Signal (MySignal.h oraz MySignal.cxx)
Klasa MySignal jest używana do przechowywania i obliczania właściwości sygnałów. Zawiera następujące funkcje:
   * Gettery i settery dla zmiennych:
       * t0_var (czas początkowy)
       * tot_var (czas ponad progiem)
       * charge_var (ładunek)
       * amplitude_var (amplituda)
       * baseline_var (baseline)
   * Funkcje obliczeniowe, które równocześnie zmieniają wartość zmienej_var na wartość obliczoną:
        * CalcT0: Oblicza czas początkowy (t0) na podstawie wartości progowej.
        * CalcTot: Oblicza czas ponad progiem (ToT) na podstawie aktualnej wartości t0.
        * CalcCharge: Oblicza ładunek sygnału w zadanym przedziale czasowym.
        * CalcAmplitude: Oblicza amplitudę sygnału.
        * CalcBaseline: Oblicza baseline sygnału jako średnią z pierwszych n_mean punktów.
        * ShiftBaseline: Przesuwa baseline histogramu do poziomu 0.

Klasa jest wykorzystywana w makrze zadanie_2.C do przetwarzania danych z pliku wejściowego.
Przed użyciem makra zadanie_2.C, należy wytworzyć słowniki i plik .so (shared library) należy wpisać następujące komendy:
```
root
.L MySignal.cxx+
```
## Makro zadanie_2.C
Makro zadanie_2.C czyta dane z pliku wave_0.dat (domyślnie) i na podstawie tych danych oblicza właściwości sygnałów, takie jak:
* Amplituda
* Ładunek
* Czas początkowy (t0)
* Czas ponad progiem (ToT)
*  Baseline

Wyniki są zapisywane w drzewie ROOT (signal_tree) w pliku signals.root. Dodatkowo makro generuje histogramy przedstawiające rozkłady amplitudy, ładunku, czasu początkowego oraz ich wzajemne korelacje. Histogramy są zapisywane w pliku histogramy.root.
Przed uruchomieniem makra należy pamiętać o załadowaniu biblioteki do  sesji root:
```
root
gSystem->Load("MySignal_cxx.so");
```

Dalej można już załadować makro i uruchomić funkcję
```
.L zadanie_2.C
 zadanie_2("nazwa_pliku.dat");
draw_histo("signals.root", "signal_tree");
```

