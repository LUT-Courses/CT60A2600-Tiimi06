# CT60A2600 – Tiimi06

## Kuvaus
Tämä on LUTin C-ohjelmoinnin kurssin (CT60A2600) harjoitustyö, toteutettuna tiimin Tiimi06 toimesta.  
Ohjelma toteuttaa valikkopohjaisen käyttöliittymän, jonka kautta käyttäjä voi:
- Käsitellä ja lajitella taulukkomuotoisia aineistoja (MergeSort nouseva/järjestys sekä laskeva järjestys)  
- Rakentaa ja käsitellä binääripuita  
- Käsitellä linkitettyjä listoja ja laskea tilastollisia arvoja (keskiarvo, mediaani, moodi)  
- Rakentaa suuntaamattoman painotetun graafin, etsiä lyhimmän polun Dijkstra-algoritmilla ja kirjoittaa tulokset tiedostoon  

Projektissa on kaksi vaihtoehtoista pääohjelmaa:  
- `Main.c` käyttämään suoraan moduuleja  
- `MainKirjasto.c` kirjasto­pohjainen lähestymistapa  

## Rakenne
- **Makefile**  
  - Kääntää jokaisen `.c`-tiedoston erikseen C99-standardeilla (`-std=c99 -Wall -pedantic`)  
  - Luodaan objektitiedostot `.o`-päätteellä ja linkitetään suoritettavaksi tiedostoksi `projekti`

- **Pääohjelmat**  
  - `Main.c` – valikkopohjainen ohjelma  
  - `MainKirjasto.c` + `MainKirjasto.h` – sama logiikka kirjasto­funktioiden kautta  

- **Moduulit**  
  - **MergeSortNousevaJKirjasto** / **MergeSortLaskevaJKirjasto**  
    Lajittelualgoritmit nousevaan ja laskevaan järjestykseen  
  - **Bintree**  
    Binääripuiden rakentaminen, läpikäynti ja vapautus  
  - **TilastoFaktatLista** / **TilastoFaktatBin**  
    Tilastollisten mittareiden (keskiarvo, mediaani, moodi jne.) laskenta listasta ja binääripuusta  
  - **Graafi**  
    Suuntaamattoman, painotetun graafin rakentaminen, solmujen lisäys, kaarien käsittely sekä lyhimmän polun etsintä ja tulostus  

## Asennus ja käyttö

1. **Kloonaa repo**  
   git clone https://github.com/LUT-Courses/CT60A2600-Tiimi06.git
   cd CT60A2600-Tiimi06

make
./projekti
make clean
