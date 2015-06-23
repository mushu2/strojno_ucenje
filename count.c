// compile: gcc count.c -o count
// run: ./count

#include <stdio.h>
#include <stdlib.h>

// koliko linija cemo obraditi
#define LINES 4500

// koliko ocekujemo da ce najvise biti razlicitih rijeci
#define NUM 100000

int equal(char *a, char *b){
  // provjerava jesu li dvije rijeci iste
  if (a[0] != b[0]) return 0;
  if (a[1] != b[1]) return 0;
  if (a[2] != b[2]) return 0;
  if (a[3] != b[3]) return 0;
  return 1;
}

void set(char *a, char *b){
  // postavlja rijec a na rijec b
  a[0] = b[0];
  a[1] = b[1];
  a[2] = b[2];
  a[3] = b[3];
  return;
}

int main(void){
  FILE *f, *g, *h;
  char word[4];
  char dict[NUM][4];
  int spam[NUM], ham[NUM];
  int sord[NUM], hord[NUM];
  double srat[NUM], hrat[NUM];
  int n, s, i, j, t, numw = 0, found, total = 0, spammsg = 0, hammsg = 0;
  int scand = 0, hcand = 0, hamw = 0, spamw = 0;
  char c;
  f = fopen("data2.txt", "r");
  g = fopen("data3.txt", "w");
  h = fopen("keywords.txt", "w");
  for (n = 0; n < LINES; n++){
    fscanf(f, "%d", &s); // ucitaj jeli spam ili ham
    if (s == 0) hammsg++; // izbroji ukupan broj ham/spam poruka
    else spammsg++;
    fscanf(f, "%c", &c); // ucitaj razmak
    while (c != '\n'){
      found = 0;
      for (i = 0; i < 4; i++){
        fscanf(f, "%c", &(word[i])); // ucitaj rijec
      }
      for (i = 0; i < numw; i++){
        // prodi kroz rijecnik i pogledaj ako vec imas zapisanu rijec
        if (equal(word, dict[i])){
          // ako da samo povecaj njezin spam/ham count
          if (s == 0) ham[i]++;
          else spam[i]++;
          found = 1;
        }
      }
      if (found == 0){
        // ako nisi rijec pronasao dodaj ju  na kraj rijecnika
        set(dict[numw], word);
        if (s == 0) ham[numw]++;
        else spam[numw]++;
        numw++;
      }
      if (s == 0) hamw++; // izbroji ukupan broj ham/spam rijeci
      else spamw++;
      fscanf(f, "%c", &c); // ucitaj razmak
    }
  }
  
  // sada imas kompletan dictionary te se rijec na poziciji dict[i] ukupno
  // pojavljuje spam[i] puta u spam porukama te ham[i] puta u ham porukama
  // sve to sad zapisi u datoteku g, te na stdout napisi koliko ima rijeci
  for (i = 0; i < numw; i++){
    total += ham[i];
    total += spam[i];
    fprintf(g, "%c%c%c%c %d %d\n",
        dict[i][0], dict[i][1], dict[i][2], dict[i][3], ham[i], spam[i]);
  }
  
  // izracunaj spam i ham ratio za svaku rijec
  for (i = 0; i < numw; i++){
    if (ham[i] == 0){ // hardkodirano 999, moguce da nece biti dobro ali se lako
      srat[i] = 999 + spam[i];  // provjeri je li dobro
      hrat[i] = 0;
    }
    else if (spam[i] == 0){
      srat[i] = 0;
      hrat[i] = 999 + ham[i];
    }
    else{
      srat[i] = ((double)spam[i])/(ham[i]) * ((double)hammsg/spammsg);
      hrat[i] = ((double)ham[i])/(spam[i]) * ((double)spammsg/hammsg);
    }
    sord[i] = i; // pomocni nizovi kojim cemo sortirati rijeci prema ratiu
    hord[i] = i;
  }
  for (i = 0; i < numw; i++){
    for (j = i+1; j < numw; j++){
      // insertion sort za spam i ham ratio
      // nizovi sord i hord cuvaju poredak od najveceg do najmanjeg ratia
      if (srat[sord[i]] < srat[sord[j]]){
        t = sord[i];
        sord[i] = sord[j];
        sord[j] = t;
      }
      if (hrat[hord[i]] < hrat[hord[j]]){
        t = hord[i];
        hord[i] = hord[j];
        hord[j] = t;
      }
    }
  }

  // ispisi kandidate za spam i ham koji imaju veliki ratio, ali i dovoljno
  // veliku frekvenciju ukupno. ovjde se moze malo experimentirati s granicama
  // granice 2 za ratio te 0.1% ukupnog broja rijeci te kategorije su odabrani
  // experimentalno
  for (j = 0; j < numw; j++){
    i = sord[j];
    if ((srat[i] > 2) && (spam[i] > 0.001*spamw)){
      fprintf(h, "%c%c%c%c %d %d %lg\n", dict[i][0], dict[i][1], dict[i][2],
          dict[i][3], ham[i], spam[i], srat[i]);
    scand++;
    }
    i = hord[j];
    if ((hrat[i] > 2) && (ham[i] > 0.001*hamw)){
      fprintf(h, "%c%c%c%c %d %d %lg\n", dict[i][0], dict[i][1], dict[i][2],
          dict[i][3], ham[i], spam[i], hrat[i]);
      hcand++;
    }
  }
  printf("broj razlicitih rijeci: %d\n", numw);
  printf("broj rijeci ukupno: %d\n", total);
  printf("broj spam rijeci ukupno: %d\n", spamw);
  printf("broj ham rijeci ukupno: %d\n", hamw);
  printf("broj spam poruka: %d\n", spammsg);
  printf("broj ham poruka: %d\n", hammsg);
  printf("spam kandidata: %d\n", scand);
  printf("ham kandidata: %d\n", hcand);
  return 0;
}

