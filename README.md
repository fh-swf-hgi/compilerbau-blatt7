# Compilerbau Blatt 7

Dieses Repository enthaelt ein kleines Beispiel fuer die semantische Analyse:
Der Parser erzeugt einen AST fuer einfache Zuweisungen und Ausdruecke. Danach
berechnet `semantic.c` die Typattribute der AST-Knoten und fuehrt eine einfache
Symboltabelle.

## Bauen und ausfuehren

```sh
cd expr
make run
```

Der Lauf erzeugt:

- eine textuelle Symboltabelle auf der Konsole
- `ast.dot` als GraphViz-Beschreibung des AST
- `ast.png` als Bild des AST

Weitere Testfaelle lassen sich mit folgendem Ziel ausfuehren:

```sh
make test
```

Der Zieltest fuer die Erweiterung der Zuweisungsregel ist separat:

```sh
make test-widening
```

Dieser Test schlaegt im Ausgangszustand fehl und soll nach der Erweiterung der
semantischen Traversierung erfolgreich sein.

## Wichtige Dateien

- `parser.l`: Scanner-Regeln fuer Bezeichner, Integer, Double und Operatoren
- `parser.y`: Grammatikregeln und Erzeugung des AST
- `ast.h`, `ast.c`: AST-Datenstruktur und DOT-Ausgabe
- `symbols.h`, `symbols.c`: einfache Symboltabelle
- `semantic.h`, `semantic.c`: Typinferenz und semantische Pruefungen
- `main.c`: Programmstart, Parseraufruf und Ausgabe

Fuer das Praktikum ist vor allem `semantic.c` relevant.
