package org.example;

import java.util.ArrayList;

public final class LiczbyPierwsze {
    private LiczbyPierwsze() {}

    private final static int POTEGA2 = 21;
    private final static int[] SITO = new int[1 << POTEGA2];
    private static boolean initialized = false;
    private static void init() {
        SITO[0] = 0;
        SITO[1] = 1;
        for(int i = 2; i < (1<<POTEGA2); i++)
            if(SITO[i] == 0)
                for(int j = i; j < (1<<POTEGA2); j += i)
                    if(SITO[j] == 0)
                        SITO[j] = i;
    }
    public static boolean czyPierwsza (long x) {
        if(!initialized) {
            initialized = true;
            init();
        }
        if(x < 2)
            return false;
        if(x < (1<<POTEGA2))
            return x == SITO[(int) x];
        long sq = (long)Math.ceil(Math.sqrt(x));
        for(int i = 2; i <= sq; i++)
            if(x % i == 0)
                return false;
        return true;
    }
    public static long[] naCzynnikiPierwsze (long x) {
        if(!initialized) {
            initialized = true;
            init();
        }
        if(x >= -1 && x <= 1) {
            return new long[]{x};
        }
        ArrayList<Long> factors = new ArrayList<>();
        if(x < 0) {
            factors.add((long) -1);
            x *= -1;
        }
        while(x > 1) {
            if(x < (1<<POTEGA2)) {
                long factor = SITO[(int) x];
                factors.add(factor);
                x /= factor;
                continue;
            }
            long sq = (long)Math.ceil(Math.sqrt(x));
            boolean isPrime = true;
            for(long i = 2; i <= sq; i++) {
                if(x % i == 0) {
                    factors.add(i);
                    x /= i;
                    isPrime = false;
                    break;
                }
            }
            if(isPrime) {
                factors.add(x);
                x = 1;
            }
        }
        long[] ans = new long[factors.size()];
        for(int i = 0; i < ans.length; i++)
            ans[i] = factors.get(i);
        return ans;
    }

}
