#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP_SIZE 1000000

// Cream structura pentru culori
typedef struct culori {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} Culori;

// Cream structura pentru noduri
typedef struct node {
  Culori* culori;
  struct node* NW;
  struct node* NE;
  struct node* SW;
  struct node* SE;
  int nivel;
  unsigned char tip;
} Node;

// Cream structura pentru arbori
typedef struct tree {
  struct node* root;
} Tree;

// Cream functia de verificare a scorului
int verificare(Culori** grid, int x, int y, int width, int height, int prag,
               unsigned char* red, unsigned char* green, unsigned char* blue) {
  //* Valorile medii pentru culori
  unsigned long long sumRed = 0, SumGreen = 0, SumBlue = 0;
  for (int i = x; i < x + height; i++) {
    for (int j = y; j < y + width; j++) {
      // Facem suma pentru fiecare culoare
      sumRed += grid[i][j].red;
      SumGreen += grid[i][j].green;
      SumBlue += grid[i][j].blue;
    }
  }
  // Calculam valoarea medie pentru fiecare culoare
  *red = sumRed / (width * height);
  *green = SumGreen / (width * height);
  *blue = SumBlue / (width * height);

  //* Mean
  unsigned long long mean = 0;
  unsigned long long sumpow = 0;
  for (int i = x; i < x + height; i++) {
    for (int j = y; j < y + width; j++) {
      // Calculam suma de puteri
      sumpow += ((*red) - grid[i][j].red) * ((*red) - grid[i][j].red) +
                ((*green) - grid[i][j].green) * ((*green) - grid[i][j].green) +
                ((*blue) - grid[i][j].blue) * ((*blue) - grid[i][j].blue);
    }
  }
  // Calculam scorul
  mean = sumpow / (3 * width * height);
  //* Verificare mean si prag
  if (mean <= prag) return 0;
  return 1;
}

// Cream functia de creareArbore
Node* creareArbore(Culori** grid, int x, int y, int width, int height, int prag,
                   int* NrFrunze, int* NrNoduri) {
  // Crestem numarul de noduri
  (*NrNoduri)++;
  // Cream un nod nou, alocam memorie si initializam cu 0 toate valorile
  Node* root = malloc(sizeof(Node));
  root->culori = malloc(sizeof(Culori));
  root->culori->red = 0;
  root->culori->green = 0;
  root->culori->blue = 0;
  // Vedem daca mean <= prag
  int verificat =
      verificare(grid, x, y, width, height, prag, &root->culori->red,
                 &root->culori->green, &root->culori->blue);
  if (verificat == 1) {
    // Daca mean > prag atunci nodul este parinte, tipul este 0
    root->tip = 0;
    // Apelam functia de creareArbore pentru fiecare copil si modificam
    // parametrii in functie de copil
    root->NW = creareArbore(grid, x, y, width / 2, height / 2, prag, NrFrunze,
                            NrNoduri);
    root->NE = creareArbore(grid, x, y + (width / 2), width / 2, height / 2,
                            prag, NrFrunze, NrNoduri);
    root->SE = creareArbore(grid, x + (width / 2), y + (height / 2), width / 2,
                            height / 2, prag, NrFrunze, NrNoduri);
    root->SW = creareArbore(grid, x + (height / 2), y, width / 2, height / 2,
                            prag, NrFrunze, NrNoduri);
  } else if (verificat == 0) {
    // Daca mean <= prag atunci nodul este frunza, tipul este 1
    root->tip = 1;
    // Crestem numarul de frunze
    (*NrFrunze)++;
    root->NW = NULL;
    root->NE = NULL;
    root->SE = NULL;
    root->SW = NULL;
  }
  // Returnam nodul creat
  return root;
}

// Cream functia de distrugereArbore
void distrugeArbore(Node* root) {
  if (root == NULL) {
    return;
  }
  // Dam free la vectorul de culori
  free(root->culori);
  // Apelam functia pentru fiecare copil
  distrugeArbore(root->NW);
  distrugeArbore(root->NE);
  distrugeArbore(root->SE);
  distrugeArbore(root->SW);
  // Dam free la nod
  free(root);
}

// Cream functia care atribuie un nivel fiecarui nod din arbore
void AtribuireNivelNode(Node* node, int nivel) {
  if (node == NULL) return;
  // Atribuim nodului nivelul "nivel"
  node->nivel = nivel;
  // Apelam functia pentru fiecare copil, crescand nivelul
  AtribuireNivelNode(node->NE, nivel + 1);
  AtribuireNivelNode(node->NW, nivel + 1);
  AtribuireNivelNode(node->SE, nivel + 1);
  AtribuireNivelNode(node->SW, nivel + 1);
}

// Cream functia pentru a afla cel mai mare nivel din arbore
int NivelulMaxim(struct node* root) {
  if (root == NULL) return 0;
  int NE, NW, SW, SE;
  int NivelulMaximcopil = 0;

  // Apelam functia pentru fiecare copil
  NW = NivelulMaxim(root->NW);
  NE = NivelulMaxim(root->NE);
  SE = NivelulMaxim(root->SE);
  SW = NivelulMaxim(root->SW);

  // Daca nivelul unui copil este mai mare decat nivelul maxim atunci variabila
  // "NivelulMaximcopil" va lua acea valoare
  if (NW > NivelulMaximcopil) NivelulMaximcopil = NW;
  if (NE > NivelulMaximcopil) NivelulMaximcopil = NE;
  if (SE > NivelulMaximcopil) NivelulMaximcopil = SE;
  if (SW > NivelulMaximcopil) NivelulMaximcopil = SW;
  // returnam NivelulMaximcopil + 1
  return NivelulMaximcopil + 1;
}

// Cream functia pentru a afla cel mai mic Nivel din arbore
int NivelulMinim(struct node* root) {
  // Arborele este vid, adancimea minima este 0
  if (root == NULL) return 0;

  // Nodul este frunza, adancimea minima este 1
  if (root->NE == NULL && root->NW == NULL && root->SW == NULL &&
      root->SE == NULL) {
    return 1;
  }
  int NE, NW, SW, SE;

  // Apelam functia pentru fiecare copil
  NE = NivelulMinim(root->NE);
  NW = NivelulMinim(root->NW);
  SE = NivelulMinim(root->SE);
  SW = NivelulMinim(root->SW);
  int min = NE;

  // Daca gasim un copil cu un nivel mai mic decat min atunci min va lua acea
  // valoare
  if (NW < min) min = NW;
  if (SW < min) min = SW;
  if (SE < min) min = SE;

  // returnam min + 1
  return min + 1;
}

// Cream vetorul pentru nivel pentru task-ul 2
Node** CreareVectorNivel(Node* root, int NrNoduri) {
  if (root == NULL) {
    return NULL;
  }

  // Initializam vectorul de noduri
  Node** VectorNoduri = (Node**)malloc(sizeof(Node*) * NrNoduri);
  // O sa avem nevoie de doi contori
  int i = 0, j = 0;
  // initializam primul element din vector ca fiind root-ul
  VectorNoduri[j] = root;

  // i si j vor fi egale cand am trecut prin toate nodurile din arbore
  while (i <= j) {
    // ii atribuim lui temp nodul VectorNoduri[i] si dupa crestem valoarea
    // contorului i
    Node* temp = VectorNoduri[i++];

    // Adaugam copiii nodului in coada, dar inainte crestem valoarea versorului
    // j
    if (temp->NW != NULL) {
      VectorNoduri[++j] = temp->NW;
    }
    if (temp->NE != NULL) {
      VectorNoduri[++j] = temp->NE;
    }
    if (temp->SE != NULL) {
      VectorNoduri[++j] = temp->SE;
    }
    if (temp->SW != NULL) {
      VectorNoduri[++j] = temp->SW;
    }
  }

  // Returnam vectorul de noduri
  return VectorNoduri;
}

// Cream functia care o sa ne creeze fisierul PPM la task-ul 3
void CreareMatrice(FILE* file, Node* root, int x, int y, unsigned int width,
                   unsigned int height, Culori*** MatriceInter) {
  // Daca root este nul oprim functia
  if (root == NULL) return;
  // Daca nodul este parinte
  if (root->tip == 0) {
    // Apelam functia pentru fiecare copil, modificand parametrii corespunzator
    CreareMatrice(file, root->NW, x, y, width / 2, height / 2, MatriceInter);
    CreareMatrice(file, root->NE, x, y + (width / 2), width / 2, height / 2,
                  MatriceInter);
    CreareMatrice(file, root->SE, x + (width / 2), y + (height / 2), width / 2,
                  height / 2, MatriceInter);
    CreareMatrice(file, root->SW, x + (height / 2), y, width / 2, height / 2,
                  MatriceInter);
  } else if (root->tip == 1) {
    // Daca nodul este frunza atunci afisam pixelii nodului
    for (int i = x; i < x + height; i++) {
      for (int j = y; j < y + width; j++) {
        (*MatriceInter)[i][j].red = root->culori->red;
        (*MatriceInter)[i][j].green = root->culori->green;
        (*MatriceInter)[i][j].blue = root->culori->blue;
      }
    }
  }
}

// Cream functia care creeaza heap-ul de la task-ul 3
void CreareHeap(FILE* file, Node*** heap, int* cate) {
  // Cat timp nu am ajung la sfarsitul fisierului
  int sizecurrent = MAX_HEAP_SIZE;
  while (!feof(file)) {
    if (((*cate) + 2) >= MAX_HEAP_SIZE) {
      sizecurrent = MAX_HEAP_SIZE * ((*cate) + 1) * MAX_HEAP_SIZE;
      **heap = realloc(**heap, sizeof(Node*) * ((*cate) + 1) * MAX_HEAP_SIZE);
    }
    // Alocam spatiu pentru nod si vectorul de culori
    Node* node = calloc(1, sizeof(Node));
    node->culori = malloc(sizeof(Culori));
    // Citim tipul nodului
    fread(&node->tip, sizeof(unsigned char), 1, file);
    // Daca nodul este frunza atunci citim culorile
    if (node->tip == 1) {
      fread(&node->culori->red, sizeof(unsigned char), 1, file);
      fread(&node->culori->green, sizeof(unsigned char), 1, file);
      fread(&node->culori->blue, sizeof(unsigned char), 1, file);
    }
    // Bagam nodul in heap si crestem valoarea la cate, reprezentand cate noduri
    // avem in vector;
    (*heap)[*cate] = node;
    (*cate)++;
  }
}

// Facem functia care creeaza arborele de Decompresie
Node* CreareArboreDecompresie(FILE* file, Node** heap, int cate) {
  int j = 0;
  // o sa avem un j care va creste din 4 in 4 cand nodul este parinte
  for (int i = 0; i < cate - 4; i++) {
    // Daca nodul este parinte atunci va avea drept copii, nodurile de pe
    // pozitiile j+1, j+2, j+3 si j+4
    if (heap[i]->tip == 0) {
      heap[i]->NW = heap[j + 1];
      heap[i]->NE = heap[j + 2];
      heap[i]->SE = heap[j + 3];
      heap[i]->SW = heap[j + 4];
      j += 4;
    }
  }
  // Returnam primul nod din vector, adica root-ul
  return heap[0];
}

// Facem functia care distruge heap-ul
void DistrugeHeap(Node** heap, int n) {
  for (int i = 0; i < n; ++i) {
    // Dam free la fiecare vector de culori si noduri
    free(heap[i]->culori);
    free(heap[i]);
  }
  // Dam free la heap
  free(heap);
}

int main(int argc, char* argv[]) {
  // Initializam variabile
  int c1_flag = 0, c2_flag = 0, d_flag = 0;
  float c1_factor = 0, c2_factor = 0;
  char *input, *output;
  int NrNoduri = 0;
  input = argv[argc - 2];
  output = argv[argc - 1];
  int prag;

  for (int i = 1; i < argc - 2; i++) {
    // Daca argv[i] este -c1 inseamna ca c1_flag este 1 si pragul va fi
    // argv[i+1]
    if (strcmp(argv[i], "-c1") == 0) {
      c1_flag = 1;
      prag = atof(argv[i + 1]);
      i++;
    }
    // Daca argv[i] este -c2 inseamna ca c2_flag este 1 si pragul va fi
    // argv[i+1]
    if (strcmp(argv[i], "-c2") == 0) {
      c2_flag = 1;
      prag = atof(argv[i + 1]);
      i++;
    } else if (strcmp(argv[i], "-d") == 0) {
      // Daca avem -d atunci d_flag este 1
      d_flag = 1;
    }
  }

  // Daca nu avem flag-ul pentru -d
  if (d_flag == 0) {
    //!  -------------------------CERINTA 1-------------------------

    // Deschidem fisierul de intrare
    FILE* file = fopen(input, "rb");

    //* Citire fisier
    unsigned char* tip = malloc(sizeof(char) * 3);
    unsigned int width, height;
    int maxCuloare;

    // Citim tip-ul, width, height si valoarea maxima pentru culori
    fscanf(file, "%s\n%u %u\n%d", tip, &width, &height, &maxCuloare);
    // Citim \n
    fgetc(file);

    // Alocam spatiu pentru matricea grid
    Culori** grid = malloc(sizeof(Culori*) * height);
    for (int i = 0; i < height; i++) {
      grid[i] = malloc(sizeof(Culori) * width);
    }
    //* Citire matrice grid
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        fread(&grid[i][j], sizeof(struct culori), 1, file);
      }
    }

    fclose(file);

    // Cream Arborele de Compresie
    int NrFrunze = 0;
    Tree* ArboreCompresie = malloc(sizeof(Tree));
    ArboreCompresie->root =
        creareArbore(grid, 0, 0, width, height, prag, &NrFrunze, &NrNoduri);

    // Atrubuim un nivel fiecarui nod din arbore
    AtribuireNivelNode(ArboreCompresie->root, 1);

    // Aflam care este Nivelul maxim, Nivelul Minim si dimensiunea laturii
    // maxime
    int NivelulDeMaxim = NivelulMaxim(ArboreCompresie->root);
    int NivelulMinimFrunza = NivelulMinim(ArboreCompresie->root);
    int dimensiuneLaturaMax = width / pow(2, NivelulMinimFrunza - 1);

    // Daca c1_flag este 1 atunci punem datele in fisier
    if (c1_flag == 1) {
      //* Afisari
      file = fopen(output, "w");

      fprintf(file, "%d\n", NivelulDeMaxim);
      fprintf(file, "%d\n", NrFrunze);
      fprintf(file, "%d\n", dimensiuneLaturaMax);

      fclose(file);
      //* AFISARI ^
    }

    //!  -------------------------CERINTA 1-------------------------
    //*----------------------------------------------------------------------------
    //!  -------------------------CERINTA 2-------------------------
    if (c2_flag == 1) {
      // Daca c2_flag este 1 atunci facem vectorul de noduri
      Node** parcurgerenivel =
          CreareVectorNivel(ArboreCompresie->root, NrNoduri);

      // Deschidem fisierul unde scriem valorile
      file = fopen(output, "w");

      // Scriem valorile in fisier
      fwrite(&width, sizeof(unsigned int), 1, file);
      for (int i = 0; i < NrNoduri; i++) {
        if (parcurgerenivel[i]->tip == 0) {
          fwrite(&parcurgerenivel[i]->tip, sizeof(unsigned char), 1, file);
        } else if (parcurgerenivel[i]->tip == 1) {
          fwrite(&parcurgerenivel[i]->tip, sizeof(unsigned char), 1, file);
          fwrite(&parcurgerenivel[i]->culori->red, sizeof(unsigned char), 1,
                 file);
          fwrite(&parcurgerenivel[i]->culori->green, sizeof(unsigned char), 1,
                 file);
          fwrite(&parcurgerenivel[i]->culori->blue, sizeof(unsigned char), 1,
                 file);
        }
      }

      // inchidem fisierul si dam free-urile necesare
      fclose(file);
      free(parcurgerenivel);
    }
    //* Free-uri
    for (int i = 0; i < height; i++) {
      free(grid[i]);
    }
    free(grid);
    free(tip);
    distrugeArbore(ArboreCompresie->root);
    free(ArboreCompresie);
    //!  -------------------------CERINTA 2-------------------------
  }
  //*----------------------------------------------------------------------------
  //!  -------------------------CERINTA 3-------------------------
  if (d_flag == 1) {
    // Deschidem fisierul de unde citim vectorul
    FILE* file = fopen(input, "rb");
    unsigned int width, height;

    // Citim size-ul
    fread(&width, sizeof(unsigned int), 1, file);
    height = width;

    // Alocam spatiu pentru arbordele de decompresie si heap
    Tree* ArboreDecompresie = malloc(sizeof(Tree));
    int cate = 0;
    Node** heap = calloc(MAX_HEAP_SIZE, sizeof(Node*));

    // Cream matricea intermediara
    Culori** MatriceInter = calloc(height, sizeof(Culori*));
    for (int i = 0; i < height; i++) {
      MatriceInter[i] = calloc(width, sizeof(Culori));
    }

    // Cream heap-ul si Arborele de compresie
    CreareHeap(file, &heap, &cate);
    ArboreDecompresie->root = CreareArboreDecompresie(file, heap, cate);
    fclose(file);

    // Deschidem fisierul si scriem valorile pentru PPM
    file = fopen(output, "w");
    fprintf(file, "P6\n");
    fprintf(file, "%u %u\n", width, height);
    fprintf(file, "255\n");

    // Apelam functia de crearePPM
    CreareMatrice(file, ArboreDecompresie->root, 0, 0, width, height,
                  &MatriceInter);

    // Scrie, in fisier culorile
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        fwrite(&MatriceInter[i][j].red, sizeof(unsigned char), 1, file);
        fwrite(&MatriceInter[i][j].green, sizeof(unsigned char), 1, file);
        fwrite(&MatriceInter[i][j].blue, sizeof(unsigned char), 1, file);
      }
    }

    // Dam free la arbore si distrugem heap-ul si matricea intermediara
    for (int i = 0; i < height; i++) {
      free(MatriceInter[i]);
    }
    free(MatriceInter);
    free(ArboreDecompresie);
    DistrugeHeap(heap, cate);
    fclose(file);
  }
  //!  -------------------------CERINTA 3-------------------------

  return 0;
}
