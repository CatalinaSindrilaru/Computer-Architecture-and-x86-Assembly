Nume: Sindrilaru Catalina-Maria

Grupa: 312CA

# MOMENTE DISPERATE - TEMA 1

## Organizare

Datele se stocheaza intr-un vector generic arr. Fiecare element
din vector va reprezenta de fapt o structura de date ce contine un
header (cu tipul dedicatiei si lungimea datelor ce urmeaza a fi stocate)
si datele propriu-zise (doua nume si doua numere - unde numerele vor
fi stocate ca int8_t, int16_t sau int32_t);
        
## Implementare

Pentru a stoca datele citite prin intermediul comenzilor insert si 
insert_at folosesc functia fill_data ce primeste ca parametru data_structure
data. Astfel, citesc tipul dedicatiei, primul nume, cele doua numere (cu
tipul de int conform tipului 1, 2, 3 de dedicatie), iar apoi ultimul nume.
Stiind toate acestea, pot calcula numarul octetilor, pe care ii ocupa. Stochez
tipul in data->header->type, iar lungimea, calculata anterior in  data->header->len.
Dupa ce aloc data->data pentru numarul de octeti corespunzator, copiez cele doua
nume si cele doua numere, sarind peste un anumit numar de octeti cu ajutorul unui
contor pe care il actualizez dupa fiecare copiere in parte.

Adaugarea propriu-zisa se face prin functiile add_last si add_at.
    
Add_last insereaza noile date la finalul zonei de memorie reprezenta de arr. 

* In cazul in care "vectorul" este gol, aloc arr cu dimensiunea datelor
pe care le voi copia in el, mai exact sizeof(unsigned char) (pentru tipul
dedicatiei din header) + sizeof(unsigned int) (pentru lungimea datelor propriu
zise ce vor fi copiate in continuare) + data->header->len (pentru datele
ce vor fi copiate). 
* Daca "vectorul" arr nu este gol, voi calcula cati octeti sunt in arr si
il voi realoca cu dimensiunea sa curenta + dimensiunile datelor pe care vreau sa
le adaug, mentionate si anterior. Mai apoi, copiez pe rand data->header->type,
data->header->len si data->data la finalul zonei de memorie.

Add_at insereaza o noua structura de date (un element in vector), tratand 3 cazuri,
atunci cand inserez la inceput, la final sau in interiorul vectorului.
Am ales sa folosesc un vector auxiliar in care am copiat memoria dinaintea
indexului la care vreau sa inserez, apoi sa copiez datele aferente structurii
pe care vreau sa o adaug, iar la final sa copiez datele ce au ramas din vectorul
initial. 

Delete_at sterge elementul cu indexul dorit din vector. Am tratat aceleasi 
3 cazuri ca la add_at, folosind pentru fiecare un vector auxiliar. La inceputul
functiei am retinut numarul total de octeti pe care ii are initial arr, numarul
de octeti fara ultimul element din vector, dar si la ce octet incepe si se termina
elementul de pe pozitia index, valori pe care le voi folosi ulterior. In toate
cazurile prezentate mai jos, la final arr devine auxiliarul.
* Pentru a sterge primul element din vector, copiez in vectorul auxiliar
toti octetii sarind peste octetii ce reprezinta prima structura.
* Pentru a sterge ultimul element, copiez in vectorul auxiliar toti octetii
din arr, dar fara cei ce reprezinta ultimul element. 
* Daca elementul pe care vreau sa il sterg se afla in interior, copiez mai
intai toti octetii de dinaintea lui in vectorul auxiliar. Trec peste octetii pe care
vreau sa ii sterg, iar apoi copiez toti octetii pana la final in continuarea
vectorului auxiliar. 

Afisarea unui singur element din vector in formatul dorit se face prin functia 
find_index, iar pentru a afisa toate elementele vectorului apelez functia find 
pentru fiecare in parte.

Find_index sare peste toti octetii pana ajunge la indexul dat, apoi citeste
data->header->type si data->header->len pentru structura pe care doresc sa o afisez.
In continuare, citesc octet cu octet pana ajung la '\0' pentru a afla lungimea
primului nume, pe care il si stochez in name1. Stiind tipul dedicatiei, stiu cati
octeti ocupa fiecare dintre numerele pe care le stochez in bill1 si bill2. Cel de-al
doilea nume il citesc aflandu-i inainte lungimea (din data->header->len scad lungimea
primului nume, dar si dimensiunea celor doua int-uri). La final, afisez datele.
