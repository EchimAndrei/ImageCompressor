    Mai intai am initializat variabilele care ma vor ajuta la citirea datelor din comanda precum c1_flag care ma ajuta sa stiu ca a fost comanda apelata cu -c1 sau d_flag sa stiu daca am flag-ul -d.
    Am introdus numele fisierului de input in "input" si numele fisierului de output in "output".

            Cerinta1:
    Am deschis fisierul de input si am citit tipul, width, height si valoarea pentru culoarea maxima. Dupa am citit matricea de pixeli si am inchis fisierul. Apoi am alocat spatiu pentru arborele de compresie si am apelat functia de creareArbore.

        CreareArbore = Functie care imi creaza arbore, in aceasta am apelat functia de verificare. Aceasta imi returneaza 1 daca pragul este mai mic decat scorul de asemanare (pe care l-am calculat tot in aceeasi functie conform instructiunilor din PDF) si 0 daca pragul este mai mare sau egal.
                       Daca nodul este parinte atunci i-am atribuit tipul 1 si am apelat functia de CreareArbore pentru fiecare fiu al sau
                       Daca nodul este frunza atunci am crescut numarul de frunze
                       Functia returneaza fiecare nod creat

    Dupa ce am creat arborele, am atribuit fiecarui nod nivelul corespunzator, apeland functia AtrubireNivelNode

        AtribuireNodeNivel = Functie care atribuie fiecarui nod din arbore un nivel
                             Tot ce face e sa-i atribuie variabilei node->nive valoarea nivel si sa apeleze pentru fiecare copil aceeasi functie doar ca pentru nivel + 1

    Dupa am facut functii pentru a determina fiecare valoare ceruta la Cerinta1

        NivelulMaxim = Functie care determina nivelul cel mai mare din arbore
                       Apeleaza functia pentru fiecare copil al nodului si daca nodul are un nivel mai mare decat maximul, atunci maxim va lua valoarea acelui nivel

        NivelulMinim = Functie care determina nivelul minim din arbore al unei frunze
                        Functioneaza cam la fel ca functia de maxim

    Dupa verific daca am flag-ul de c1, daca da atunci afisez valorile cerute in fisier

                Cerinta2:

    Aloc spatiu pentru vectorul de noduri, apeland functia de CreareVectorNivel.

        CreareVectorNivel = Functie care creeaza vectorul de noduri. Ia fiecare nod in parte si il baga in vector.

     Dupa deschid fisierul de output si scriu valoarea Width-ului in el precum si celelalte valori cerute la cerinta2
     Desigur dupa dau free la toate variabilele alocate dinamic.


                Cerinta3:

    Deschid fieisrul de input si citesc size-ul. Dupa aloc memorie Arborele de decompresie si heap
    Apelez functia de creare Heap si crearea arborului de decompresie.

            CreareHeap = Citesc valori pana ajung la sfarsitul fisierului. Aloc spatiu pentru fiecare node si vectorul de culori. Daca nodul este frunza citesc valorile pentru fiecare culoare. Dupa adaug nodul in heap si cresc valoarea numarului de noduri.

            CreareArboreDecompresie = Trec prin fiecare element din vector si verific daca acesta e parinte, daca e parinte realizez legaturile cu fiecare fiu al sau.

    Dupa Creez o matrice intermediara ce o sa memoreze pixelii.

            CreareMatrice = Functie care creeaza o matrice intermediara ce o sa memoreze pixelii. 
    Dupa afisez in binar matricea de pixeli si dau free la toata memoria alocata dinamic.
