// compile: gcc filter.c -o filter
// run: ./filter

#include <stdio.h>
#include <stdlib.h>

//  koliko linija cemo obraditi 
#define LINES 5574

int isCh(char c){
  // provjerava jeli char nealfabetski
  if ((c >= 'a') && (c <= 'z') || (c >= 'A') && (c <= 'Z')) return 0;
  return 1;
}

int isAlpha(int c){
  // provjerava jeli char alfabetski
  return 1-isCh(c);
}

char toLow(char c){
  // ocekuje da ce dobiti alfabetski char
  if (c < 97) return c+32;
  return c;
}

int main(void){
  FILE *f, *g;
  char c;
  int n, k, h = 0, s = 0;
  f = fopen("data.txt", "r");
  g = fopen("data2.txt", "w");
  for (n = 0; n < LINES; n++){
    fscanf(f, "%c", &c);
    if (c == 'h') {
      // ako je ham stavi 0 na pocetak linije
      fprintf(g, "0");
      h++;
    }
    else if (c == 's'){
      // ako je spam stavi 1 na pocetak linije
      fprintf(g, "1");
      s++;
    }
    else printf("nesto nevalja: linija %d\n", n);
    // ako na pocetku linije ne pise ni spam ni ham, nesto je krivo
    while (isAlpha(c)) fscanf(f, "%c", &c);
    // ucitaj cijelu rijec (spam/ham) do kraja
    while (c != '\n'){
      k = 0;
      // sad si u stanju kad si procitao neku rijec do kraja
      // citaj nealfabetske znakove dok ide
      while (isCh(c)){
        fscanf(f, "%c", &c);
        if (c == '\n') break;
      }
      if (c == '\n') break;
      fprintf(g, " ");
      while (isAlpha(c)){
        // citaj alfabetske znakove dok ide, a upisi ih najvise 4
        if (k < 4) fprintf(g, "%c", toLow(c));
        fscanf(f, "%c", &c);
        k++;
      }
      while (k < 4){
        // ako je rijec kraca od 4 znaka dopuni sa _ zbog jednostavnosti poslije
        fprintf(g, "_");
        k++;
      }
    }
    fprintf(g, "\n");
  }
  // na ekran ispisi koliko ima hamova a koliko spamova
  printf("ham poruka: %d, spam poruka: %d\n", h, s);
  return 0;
}
