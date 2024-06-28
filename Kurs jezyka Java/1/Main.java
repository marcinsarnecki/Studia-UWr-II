package org.example;

import java.util.Scanner;

public class Main {
    public static String findChineseZodiacPatron(int year) {
        String[] patroni = {
                "Szczur", "Bawół", "Tygrys", "Królik", "Smok", "Wąż", "Koń", "Owca", "Małpa", "Kurczak", "Pies", "Świnia"
        };

        int remainder = (year - 4 + 12)% 12;
        String patron = switch (remainder) {
            case 0 -> patroni[0]; // Szczur
            case 1 -> patroni[1]; // Bawół
            case 2 -> patroni[2]; // Tygrys
            case 3 -> patroni[3]; // Królik
            case 4 -> patroni[4]; // Smok
            case 5 -> patroni[5]; // Wąż
            case 6 -> patroni[6]; // Koń
            case 7 -> patroni[7]; // Owca
            case 8 -> patroni[8]; // Małpa
            case 9 -> patroni[9]; // Kurczak
            case 10 -> patroni[10]; // Pies
            case 11 -> patroni[11]; // Świnia
            default -> "Nieznany patron";
        };

        return patron;
    }
    public static String rzymska(int n) {
        if (n <= 0 || n >= 4000) {
            throw new IllegalArgumentException("liczba " + n + " spoza zakresu 1-3999");
        }
        String[] rzymskie = {
                "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
        };
        int[] arabskie = {
                1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
        };
        StringBuilder roman = new StringBuilder();
        int i = 0;
        while (n > 0) {
            if (n >= arabskie[i]) {
                roman.append(rzymskie[i]);
                n -= arabskie[i];
            } else {
                i++;
            }
        }
        return roman.toString();
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String name = scanner.next();
        int year = scanner.nextInt();
        System.out.println("Hej " + name + "!");
        System.out.println("Podany rok urodzenia w notacji rzymskiej: " + rzymska(year));
        System.out.println("Chiński patron: " + findChineseZodiacPatron(year));
    }
}