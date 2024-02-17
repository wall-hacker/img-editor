````
  ___                 _____    _ _ _             
 |_ _|_ __ ___   __ _| ____|__| (_) |_ ___  _ __ 
  | || '_ ` _ \ / _` |  _| / _` | | __/ _ \| '__|
  | || | | | | | (_| | |__| (_| | | || (_) | |   
 |___|_| |_| |_|\__, |_____\__,_|_|\__\___/|_|   
                |___/                            
````
---
### Structura && Implementare 
---
- pentru a simplifica rezolvarea folosesc o structura de date (image) care 
retine toate informatiile necesare pentru incacarea, retinerea in memorie, 
editarea si salvarea unei imagini: matricele corespunzatoare imaginii color/
grayscale, dimensiunile imaginii, valoarea maxima a pixelilor, numarul magic
si coordonatele selctiei curente
- pentru modularizarea rezolvarii in main voi apela cate o functie care are
acelasi nume cu optiunea/comanda aleasa, ulterior, in interiorul functiei
respective fiind apelate alte functii cu roluri elementare (algoritmi de 
calcul, alocare/eliberare a memoriei etc.)
- voi citi comenzi de la tastatua pana la intalnirea comenzii "EXIT

---

**1] LOAD (incarea in memorie a unei imagini) :**

- daca comanda citita de la tastatura este "LOAD" citesc un nume de fisier, iar
daca acesta exista incarc o noua matrice in memorie, mai intai alocand-o 
dinamic (bazat pe tipul imaginii grayscale/color), iar apoi citind-o (citesc 
normal sau binar din fisier bazat pe numarul magic)
- de asemenea initializez coordonatele selectiei in asa fel incat toata 
imaginea va fii selectata

---

**2] SELECT (schimbarea selectiei curente) :**

- daca comanda citita de la tastatura este "SELECT" citesc un string care
trebuie separat in "termeni" pentru a putea determina validitatea parametrilor
- fac asta folosind functia strtok separand parametrii dupa " ". In cazul in
care parametrii obtinuti sunt "ALL" sau 4 numere intregi selectia este
valida si coordonatele se modifica corespunzator
- in cazul contrar fie avem o comanda invalida, fie avem un set invalid de 
coordonate

---

**3] ROTATE (rotirea selectiei curente) :**

- pentru executarea acestei comenzi am creat mai multe functii menite sa
roteasca selectia sau toata imaginea la un anumit unghi:
( "rotate_90_right_rectangle", "rotate_90_left_rectangle" si
"rotate_180_rectangle" sunt destinate rotirii intregii imagini, pe cand
"rotate_90_right", "rotate_90_left", "rotate_180" si "rotate_0" rotesc
doar o anumita selectie
- daca comanda citita de la tastatura este "ROTATE" citesc unghiul de rotatie
- verific daca selectia este dreptunghiulara
- in acest caz verific daca imaginea este selectata in totalitate. In cazul 
acesta rotesc imaginea folosind functiile metionate mai sus, dar in caz contrar
trebuie sa afisez pe ecran mesajul "The selection must be square"
- daca selectia este patrata folosesc functiile pentru rotire de selectie
- in cazul in care unghiul nu se regaseste printre cele din cerinta se va afisa
"Unsupported rotation angle"

---
**4] CROP (redimensionarea/reducerea pozei la dimensiunile selectiei curenta) :**

- daca comanda citita de la tastatura este "CROP" si avem o imagine incarcata
in memorie, fac o copie a imaginii curente, realoc matricele pentru
dimensiunile selectiei si apoi mut pixelii corespunzatoari selectiei in
matricea redimensionata
- schimbam selectia in asa fel incat toata imaginea sa fie selectata, eliberam
copia si afisam messajul "Image cropped"

---

**5] APPLY (aplicarea unui anumit filtru selectiei curente) :**

- pentru executarea acestei comenzi am creat mai multe functii:
	- clamp - functia explicata in cerinta temei
	- multir, multig, multib functii care efectueaza calculele de aplicare
	  a filtrului pentru pixelii corespunzatori componentelor r, g si b din
	  cadrul imaginii color
	- copy_kern o functie care copiaza o matrice de 3x3 pe care o folosesc
	  pentru a copia kernel - ul corespunzator celor 4 filtre implementate
- daca comanda citita de la tastatura este 'APPLY' citim un sir de caractere
- in cazul in care imaginea este grayscale verificam validitatea filtrului si
afisam in consecinta "Easy, Charlie Chaplin" sau "Invalid command"
- daca imaginea este color facem o copie a imagii si realocam matricele
- in urmatorul pas initializam kernel - urile filtrelor mentionate in cerinta
si in cazul in care filtrul este valid copiem unul dintre ele folosind functia
"copy_kern" in variabila "kern", in caz contrar se va afisa "APPLY parameter 
invalid"
- pentru aplicarea efectiva a filtrlui folosim functiile "multir", "multig"
"multib" care efectueaza calculele necesare dintre pixelii copiei si valorile
din kernel, resultatele pentru fiecare layer de culoare(r, g si b) fiind
stocate in matricea initiala

---

**6] SAVE (salvarea intr-un fisier a imaginii curente) :**

- daca comanda citita de la tastatura este 'SAVE' si avem o imagine incarcata
in memorie, citim un buffer ("buf") pentru a putea verifica cazul de salvare
in format ascii
- astfel folosim strtok pentru a separa numele fisierului in care vom salva
imaginea de un posibil parametru optiona "ascii". Folosim variabila x pentru
a retine daca parametrul ascii a aparut (x = -1) sau nu ( x != -1)
- in cazul ascii deschidem fisierul pentru scriere si scriem numarul magic
corespunzator, dimensiunile imaginii, valoarea maxima si apoi matricea de
pixeli a imaginii (img->matrix in cazul grayscale si tripletele
img->r, img->g si img->b pentru imaginile color)
- in cazul salvarii binare deschidem fisierul pentru scriere binara si repetam
scrierea de mai sus cu functiile corespunzatoare
- in ambele cazuri folosim functia round pentru a face aproximarile necesare, 
si prin variabila aux dam cast pixelilor care sunt double la tipul int

---

**7] Alte precizari:**

- pentru optiunea EXIT se opreste rularea instructiunii while, in cazul in care
nu avem o imagine incarcata in memorie se afiseaza "No image loaded" si se
efectueaza eliberarea tuturor resurselor
- cazul in care comanda nu este valida este tratat separat folosind variabila 
ok, care va avea valoarea 0 doar cand comanda nu se afla in lista data, pe 
ecran afisandu-se "Unrecognized command".

- - -
### Feedback && Comentarii
- - -
Acesta a fost primul meu proiect dificil din anul I de facultate. Provocarea a fost data atat de notiunile noi cat si de lucrul cu pointeri si structuri de date.
Mi-a placut foarte mult sa invat atat de devreme in facultate ce inseamna lucrul cu imagini (concept ce am aflat ulterior ca poate fi imbunatatit prin programarea paralela) dar si tehnicile folisite pentru aplicarea de filtre lucru care m-a inspirat sa creez un proiect personal pe acesta tema.
