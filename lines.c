// compile: gcc lines.c -o lines 
// run: ./lines

#include <stdio.h>
#include <stdlib.h>

int equal(char *a, char *b){
  // provjerava jesu li dvije linije jednake
  int k;
  for (k = 0; k < 300; k++){
    if (a[k] != b[k]) return 0;
  }
  return 1;
}

void printLine(FILE *g, char *a){
  // ispisuje liniju
  int k;
  for (k = 0; k < 50; k++){
    fprintf(g, "%c", a[k]);
  }
  fprintf(g, "\n");
  return;
}

int main(void){
  FILE *f, *g;
  char c;
  int n = 0, i, j, y, b = 0, x = 0;
  char lines[6000][300];
  int checked[6000];
  f = fopen("data.txt", "r");
  g = fopen("duplici.txt", "w");
  
  // inicijaliziraj nizove
  for (i = 0; i < 6000; i++){
    for (j = 0; j < 300; j++){
      lines[i][j] = ' ';
    }
    checked[i] = 0;
  }

  // prodi kroz file i popuni niz lines
  i = 0;
  while (fscanf(f, "%c", &c) == 1){
    if (c == '\n') {
      i = 0;
      n++;
    }
    else {
      lines[n][i] = c;
      i++;
    }
  }
  // na ekran ispisi koliko ima poruka 
  fprintf(g, "broj poruka: %d\n", n);

  // ispisi sve duplice
  for (i = 0; i < n; i++){
    if (checked[i] == 1) continue;
    y = 0;
    for (j = i+1; j < n; j++){
      if(equal(lines[i], lines[j])){
        b++;
        checked[j] = 1;
        if (y == 0) {
          printLine(g, lines[i]);
          fprintf(g, "linija %d je ista kao linije:", i + 1);
        }
        fprintf(g, " %d", j + 1);
        y = 1;
      }
    }
    if (y == 1) {
      fprintf(g, "\n\n");
      x++;
    }
  }
  fprintf(g, "razlicitih poruka koje se ponavljaju: %d\n", x);
  fprintf(g, "broj poruka koje treba uklonit da bi sve bile unikat: %d\n", b);
  return 0;
}
