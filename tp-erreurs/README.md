# TP 3 - TP-Erreurs

le rendu de TP3 — Détection et correction d’erreurs des étudiants Aziz **BOURAHMA** et Benedictus Kent **RACHMAT**, groupe 6 du **S4 Licence 2 informatique**.

## 1. Simulation d’un canal binaire symétrique sans mémoire (CBSSM)

```bash
1.2
$ cat data/poeme.txt | ./cbssm 0.03

1.3
$ cat data/TP-Erreurs.zip | ./cbssm 0.02 > data/TP-Erreurs-002.zip

1.4
$ cat data/lille.gif | ./cbssm 0.007 > data/lille-007.gif
```

## 2. Codage par répétition 3 fois

2.1 Avec le tableau de Karnaugh on peut trouver le bit majoritaire depuis la somme de produit **_AB + BC + AC_**

2.6 Avec la commande :
```bash
$ cat data/TP-Erreurs.zip | ./encode repeat3 | ./decode repeat3 > data/archive.zip

$ cmp -l data/archive.zip data/TP-Erreurs.zip
```
On constate que les fichiers sont identique

2.7
```bash
$ cat data/TP-Erreurs.zip | ./encode repeat3 | ./cbssm 0.02  | ./decode repeat3 > data/archive-CBSSM.zip

$ cmp -l data/archive-CBSSM.zip data/TP-Erreurs.zip
```
On constate que les fichiers ne sont pas identique

2.8
| Type de fichier | Probabilité d'erreur | Description |
| :---         |     :---:      |          :---: |
| ZIP   | 0.2     | impossible de décompresser    |
| ZIP     | 0.02       | impossible de décompresser     |
| ZIP   | 0.002     | pas mal d'erreurs non corrigées mais unzip toujours possible   |
| ZIP     | 0.0002       | extremement peu de différence mais unzip toujours possible     |
| ZIP   | 0.00002     | pas de différence entre le fichier    |
| IMAGE     | 0.2       | impossible     |
| IMAGE     | 0.02       | impossible     |
| IMAGE     | 0.002       | ouveture possible     |

## 3. Codages linéaires systématiques

Ils sont bien implementée

3.12
```bash
$ cat data/TP-Erreurs.zip | ./encode repeat3-linear | ./decode repeat3-linear > data/repeatlinear.zip
$ cat data/TP-Erreurs.zip | ./encode parity2d | ./decode parity2d > data/parity2d.zip
$ cat data/TP-Erreurs.zip | ./encode hamming | ./decode hamming > data/hamming.zip
$ cat data/TP-Erreurs.zip | ./encode hammingp | ./decode hammingp > data/hammingp.zip

$ cmp -l data/repeatlinear.zip data/TP-Erreurs.zip
$ cmp -l data/parity2d.zip data/TP-Erreurs.zip
$ cmp -l data/hamming.zip data/TP-Erreurs.zip
$ cmp -l data/hammingp.zip data/TP-Erreurs.zip
```
On constate que les fichiers sont identique

## 4. Expérimentations

On compare les archives pour voir quelle encodage est le plus efficace

- repeat3-linear : seuil atteint avec p = 0.0002.
- parity2d : impossible de savoir, ça ne marche pas (mais pas pour lille.gif).
- hamming : seuil atteint avec p = 0.002, avec de 1 à 4 erreurs restantes.
- hammingp : seuil atteint avec p = 0.002.

```bash
$ cat data/TP-Erreurs.zip | ./encode hamming | ./cbssm 0.002  | ./decode hamming > data/question4.zip

$ cmp -b data/TP-Erreurs.zip data/question4.zip
```
NOTE : le cmp -c c'est pour compter les erreurs restantes

Donc à mon avis, le codage de hammingp est le plus efficace
