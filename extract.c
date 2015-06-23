// compile: gcc extract.c -o extract
// run: ./extract

#include <stdio.h>
#include <stdlib.h>

//  koliko linija cemo obraditi 
#define LINES 5574

// koliko ce biti najvise rijeci u keywords.txt
#define NUM 300

int isCh(char c){
  // provjerava jeli char nealfabetski
  if ((c >= 'a') && (c <= 'z') || (c >= 'A') && (c <= 'Z')) return 0;
  return 1;
}

int isAlpha(int c){
  // provjerava jeli char alfabetski
  return 1-isCh(c);
}

int isNum(char c){
  // provjerava jeli char broj
  if ((c >= '0') && (c <= '9')) return 1;
  return 0;
}

int isSpace(char c){
  // provjerava jeli char razmak
  if (c == ' ') return 1;
  return 0;
}

int isWeird(char c){
  // provjerava jeli znak nealfabetski, nenumericki te nerazmak
  if (isAlpha(c)) return 0;
  if (isNum(c)) return 0;
  if (isSpace(c)) return 0;
  return 1;
}

int isDot(char c){
  // provjerava jeli char interpunkcijski nakon kojeg se ocekuje razmak
  if ((c == '.') || (c == '!') || (c == '?') || (c == ',')) return 1;
  return 0;
}

char toLow(char c){
  // ocekuje da ce dobiti alfabetski char
  if (c < 97) return c+32;
  return c;
}

int equal(char *a, char *b){
  // provjerava jesu li dvije rijeci iste
  if (a[0] != b[0]) return 0;
  if (a[1] != b[1]) return 0;
  if (a[2] != b[2]) return 0;
  if (a[3] != b[3]) return 0;
  return 1;
}

int exsist(char s[4], char keys[NUM][4], int len){
  // provjerava jeli rijec u rjecniku
  int i;
  for (i = 0; i < len; i++){
    if (equal(s, keys[i])) return i;
  }
  return -1;
}


int main(void){
  FILE *f, *g, *h, *out;
  char c;
  char keys[NUM][4];
  char word[4];
  int keyarr[NUM];
  int len = 0, n, spam, a, b, dot, i;
  int msglen, wordnum, numnum, weirdnum, spel;
  double r;
  f = fopen("data.txt", "r");
  g = fopen("data2.txt", "r");
  h = fopen("keywords.txt", "r");
  out = fopen("out.txt", "w");

  // ucitaj rjecnik keyworda
  while (fscanf(h, "%c%c%c%c %d %d %lg ", keys[len], keys[len]+1, keys[len]+2, 
        keys[len]+3, &a, &b, &r) == 7) len++;
  
  // napisi header u out.txt
  fprintf(out,
      "spam broj_rijeci duljina nepismenost udio_brojeva udio_nealfanumerickih ");
  for (i = 0; i < len; i++){
    fprintf(out, "%c%c%c%c ", keys[i][0], keys[i][1], keys[i][2], keys[i][3]);
  }
  fprintf(out, "\n");

  for (n = 0; n < LINES; n++){
    // prvo iz neobradenog fajla izvadi broj charactera itd..
    fscanf(f, "%c", &c);
    if (c == 'h') {
      // zapamti jeli poruka ham ...
      spam = 0;
    }
    else if (c == 's'){
      // ... ili spam
      spam = 1;
    }
    else printf("nesto nevalja: linija %d\n", n);
    // ako na pocetku linije ne pise ni spam ni ham, nesto je krivo
    
    while (isAlpha(c)) fscanf(f, "%c", &c);
    // ucitaj cijelu rijec (spam/ham) do kraja
    dot = 0;
    msglen = 0;
    numnum = 0;
    weirdnum = 0;
    spel = 0;
    wordnum = 0;

    while (1){
      fscanf(f, "%c", &c);
      if (c == '\n') break;
      msglen++; // broj znakova
      if (isNum(c)) numnum++; // broji udio brojeva
      if (isWeird(c)) weirdnum++; // broji udio nealfanumerickih
      if ((isNum(c) || isAlpha(c)) && (dot == 1)) spel = 1; // nepismenost
      if (isDot(c)) dot = 1;
      else dot = 0;
    }

    // zatim iz obradenog izvadi kljucne rijeci
    fscanf(g, "%d", &a); // ucitaj jeli spam ili ham
    if (a != spam) printf("nisu konzistentni na liniji: %d\n", n);
    fscanf(g, "%c", &c); // ucitaj razmak
    for (i = 0; i < len; i++){
      keyarr[i] = 0; // ocisti niz koji cuva postojanje keyworda
    }

    while (c != '\n'){
      for (i = 0; i < 4; i++){
        fscanf(g, "%c", word+i);
      }
      wordnum++; // broj rijeci u poruci
      b = exsist(word, keys, len); // kljucna rijec
      if (b >= 0) keyarr[b] = 1;
      fscanf(g, "%c", &c); // ucitaj razmak
    }

    // zapisi feature vektor u out.txt
    fprintf(out, "%d %d %d %d %lg %lg ", spam, wordnum, msglen, spel, 
        (double)numnum/msglen, (double)weirdnum/msglen);
    for (i = 0; i < len; i++){
      fprintf(out, "%d ", keyarr[i]);
    }
    fprintf(out, "\n");
  }

  return 0;
}
