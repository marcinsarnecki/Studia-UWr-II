package org.example;

import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if(args.length == 0) {
            System.err.println("Brak podanych liczb!");
            return;
        }
        int n = args.length;
        long[] numbers = new long[n];
        for(int i = 0; i < n; i++)
            numbers[i] = Long.parseLong(args[i]);
        for(long num: numbers) {
            String result = num + " = " + String.join("*", Arrays.stream(LiczbyPierwsze.naCzynnikiPierwsze(num))
                    .mapToObj(String::valueOf)
                    .toArray(String[]::new));
            System.out.println(result);
        }
    }
}