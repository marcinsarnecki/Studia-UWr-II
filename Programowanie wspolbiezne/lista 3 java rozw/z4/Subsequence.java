class Subsequence implements Runnable {
    private int[] arr;
    final AtomicCounter atomicCounter;
    public SubsequenceResult result;
    private int l, r;

    public Subsequence(int[] arr, AtomicCounter atomicCounter, int l, int r) {
        this.arr = arr;
        this.atomicCounter = atomicCounter;
        this.l = l;
        this.r = r;
    }

    private SubsequenceResult merge(SubsequenceResult left, SubsequenceResult right, int m) {
        int ile = left.ile, k = left.x;
        if (left.ile < right.ile) {
            ile = right.ile;
            k = right.x;
        }
        if (arr[m] == arr[m + 1] && left.ileR + right.ileL > ile) {
            ile = left.ileR + right.ileL;
            k = arr[m];
        }
        if(left.n == left.ileL && arr[m] == arr[m+1])
            left.ileL = left.n + right.ileL;
        if(right.n == right.ileL && arr[m] == arr[m+1])
            right.ileR = right.n + left.ileR;
        return new SubsequenceResult(left.n + right.n, left.ileL, right.ileR, ile, k);
    }

    public SubsequenceResult findSequence(int l, int r) {
        if (l < r) {
            int m = (l + r) / 2;
            var left = findSequence(l, m);
            var right = findSequence(m + 1, r);
            return merge(left, right, m);
        }
        return new SubsequenceResult(1, 1, 1, 1, arr[l]);
    }

    @Override
    public void run() {
        if (this.l < this.r && atomicCounter.checkAndIncrement()) {
            int m = (l + r) / 2;
            var left = new Subsequence(arr, atomicCounter, l, m);
            var right = new Subsequence(arr, atomicCounter, m + 1, r);
            Thread t2 = new Thread(right);
            t2.start();
            left.run();
            try {
                t2.join();
                this.result = merge(left.result, right.result, m);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        } else {
            this.result = this.findSequence(l, r);
        }
    }

    static class SubsequenceResult {
        public int ileL = 0, ileR = 0, ile = 0, x = -1;
        public int n = 0;

        @Override
        public String toString() {
            return "SubsequenceResult{" +
                    "ileL=" + ileL +
                    ", ileR=" + ileR +
                    ", ile=" + ile +
                    ", x=" + x +
                    ", n=" + n +
                    '}';
        }

        public SubsequenceResult(int n, int ileL, int ileR, int ile, int x) {
            this.n = n;
            this.ileL = ileL;
            this.ileR = ileR;
            this.ile = ile;
            this.x = x;
        }
    }
}
