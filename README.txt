sadrzaj:

== ulaz ======
rawdata.txt - cisto kako je preuzeto od stranice
unshuffleddata.txt - izbrisano iz rawdata.txt krivo formatirane stvari

== izlaz ======
data.txt - izmjesane linije iz unshuffleddata.txt
data2.txt - izvadene samo rijeci i skracene na 4 slova iz data.txt
data3.txt - broj pojavljivanja rijeci
keywords.txt - sortirane kljucne rijeci po vaznosti
dulplici.txt - linije koje se ponavljaju
podaci.txt - podaci koliko imamo spamova/hamova u treningu/testu i slicno
out.txt - matrica featura

== kodovi ======
filter.c - radi prvo formatiranje, iz data.txt u data2.txt
count.c - vad kljucne rijeci, iz data2.txt u data3.txt i keywords.txt
lines.c - ispisuje duplice u duplici.txt
extract.c - vadi feature, u out.txt
run - pokrece sve ispocetka
