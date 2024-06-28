package org.example;

import figury.*;

public class Main {
    public static void main(String[] args) {

        Odcinek odcinek1 = new Odcinek(1.0, 2.0, 4.0, 5.0);
        System.out.printf("Odcinek  A(%.2f, %.2f), B(%.2f, %.2f) przesuwam o wektor (2,3)\n", odcinek1.A.getX(), odcinek1.A.getY(), odcinek1.B.getX(), odcinek1.B.getY());
        odcinek1.przesun(new Wektor(2.0, 3.0));
        System.out.printf("Odcinek: A(%.2f, %.2f), B(%.2f, %.2f)\n\n", odcinek1.A.getX(), odcinek1.A.getY(), odcinek1.B.getX(), odcinek1.B.getY());

        System.out.println("Obrot o 90 stopni wzgledem punktu (2,2)");
        Punkt punktObrotu = new Punkt(2.0, 2.0);
        double katObrotu = Math.PI / 2.0;
        odcinek1.obroc(punktObrotu, katObrotu);
        System.out.printf("Odcinek: A(%.2f, %.2f), B(%.2f, %.2f)\n\n", odcinek1.A.getX(), odcinek1.A.getY(), odcinek1.B.getX(), odcinek1.B.getY());


        System.out.println("Odbicie wzgledem prostej y = -x - 1");
        Prosta prostaOdbicia = new Prosta(1.0, 1.0, 1.0); // Przykładowa prosta
        odcinek1.odbij(prostaOdbicia);
        System.out.printf("Odcinek: A(%.2f, %.2f), B(%.2f, %.2f)\n\n", odcinek1.A.getX(), odcinek1.A.getY(), odcinek1.B.getX(), odcinek1.B.getY());

        try {
            System.out.println("Proba stworzenia odcinka z punktow (1,2), (1,2)\n");
            Odcinek odcinek2 = new Odcinek(1.0, 2.0, 1.0, 2.0);
        } catch (IllegalArgumentException e) {
            System.out.println("Blad: " + e.getMessage());
        }

        Trojkat trojkat1 = new Trojkat(new Punkt(1.0, 2.0), new Punkt(4.0, 5.0), new Punkt(5.0, 2.0));
        System.out.printf("\nTrojkat: A(%.2f, %.2f), B(%.2f, %.2f), C(%.2f, %.2f)\n",
                trojkat1.A.getX(), trojkat1.A.getY(),
                trojkat1.B.getX(), trojkat1.B.getY(),
                trojkat1.C.getX(), trojkat1.C.getY());

        // Przesunięcie trójkąta o wektor
        Wektor przesuniecie = new Wektor(0.0, -3.0);
        trojkat1.przesun(przesuniecie);
        System.out.println("Przesuwam Trojkat o wektor (0,-3)");
        System.out.printf("Trojkat: A(%.2f, %.2f), B(%.2f, %.2f), C(%.2f, %.2f)\n\n",
                trojkat1.A.getX(), trojkat1.A.getY(),
                trojkat1.B.getX(), trojkat1.B.getY(),
                trojkat1.C.getX(), trojkat1.C.getY());

        // Obrot trójkąta wokół punktu
        Punkt punktObrotuTrojkata = new Punkt(-1.0, 1.0);
        double katObrotuTrojkata = Math.PI;
        System.out.println("Obrot o 180 stopni wzgledem punktu (-1, 1)");
        trojkat1.obroc(punktObrotuTrojkata, katObrotuTrojkata);
        System.out.printf("Trojkat: A(%.2f, %.2f), B(%.2f, %.2f), C(%.2f, %.2f)\n\n",
                trojkat1.A.getX(), trojkat1.A.getY(),
                trojkat1.B.getX(), trojkat1.B.getY(),
                trojkat1.C.getX(), trojkat1.C.getY());

        // Odbicie trójkąta względem prostej
        Prosta prostaOdbiciaTrojkata = new Prosta(-1.0, 1.0, 0.0); // pionowa
        trojkat1.odbij(prostaOdbiciaTrojkata);
        System.out.println("Odbicie wzgledem prostej y=x");
        System.out.printf("Trojkat: A(%.2f, %.2f), B(%.2f, %.2f), C(%.2f, %.2f)\n\n",
                trojkat1.A.getX(), trojkat1.A.getY(),
                trojkat1.B.getX(), trojkat1.B.getY(),
                trojkat1.C.getX(), trojkat1.C.getY());

        try {
            System.out.println("Proba stworzenia trojkata z punktow wspolliniowych");
            Trojkat trojkat2 = new Trojkat(new Punkt(1.0, 2.0), new Punkt(4.0, 5.0), new Punkt(2.0, 3.0));
        } catch (IllegalArgumentException e) {
            System.out.println("Blad: " + e.getMessage());
        }

        System.out.printf("Prosta odbicia: a = %.2f, b = %.2f, c = %.2f\n", prostaOdbicia.a, prostaOdbicia.b, prostaOdbicia.c);
        System.out.printf("Prosta odbicia trojkata: a = %.2f, b = %.2f, c = %.2f\n", prostaOdbiciaTrojkata.a, prostaOdbiciaTrojkata.b, prostaOdbiciaTrojkata.c);
        if (Prosta.isPerpendicular(prostaOdbicia, prostaOdbiciaTrojkata)) {
            System.out.println("Dwie proste sa wzgledem siebie prostopadle");
        } else {
            System.out.println("Dwie proste nie sa wzgledem siebie prostopadle");
        }
    }
}