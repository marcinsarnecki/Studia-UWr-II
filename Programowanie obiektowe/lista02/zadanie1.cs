using System;

namespace zadanie1
{
    class IntStream
    {
        protected int current, limit;
        protected bool end;
        virtual public int next()
        {
            if (current + 1 == limit)
                end = true;
            return current++;
        }
        virtual public bool eos()
        {
            return end;
        }
        virtual public void reset()
        {
            current = 0;
            end = false;
        }
        public IntStream()
        {
            current = 0;
            end = false;
            limit = Int32.MaxValue;
        }
    }
    class PrimeStream : IntStream
    {
        int nextPrime;
        bool isPrime(int num)
        {
            if (num < 2) return false;
            for (int i = 2; i * i <= num; i++)
                if (num % i == 0) return false;
            return true;
        }
        int findNextPrime()
        {
            current = nextPrime;
            while (true)
            {
                nextPrime++;
                if (nextPrime == limit)
                {
                    end = true;
                    break;
                }
                if (isPrime(nextPrime))
                    break;
            }
            return current;
        }
        override public int next()
        {
            return findNextPrime();
        }
        override public void reset()
        {
            current = 0;
            end = false;
        }
        public PrimeStream()
        {
            limit = Int32.MaxValue;
            end = false;
            nextPrime = 2;
            current = 0;
        }
    }
    class RandomStream : IntStream
    {
        Random rnd;
        override public bool eos()
        {
            return false;
        }
        public override int next()
        {
            return rnd.Next(Int32.MinValue, Int32.MaxValue);
        }
        public RandomStream()
        {
            rnd = new Random();
        }
    }
    class RandomWordStream
    {
        string characters;
        RandomStream rs;
        PrimeStream ps;
        public string next()
        {
            if (ps.eos())
                return "";
            char[] pom = new char[ps.next()];
            for (int i = 0; i < pom.Length; i++)
            {
                int x = Math.Abs(rs.next() % characters.Length);
                pom[i] = characters[x];
            }

            return new string(pom);
        }
        public RandomWordStream()
        {
            rs = new RandomStream();
            ps = new PrimeStream();
            characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        }
    }

    class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Kolejne liczby naturalne: ");
            IntStream istr = new IntStream();
            int i = 0;
            while (i++ < 10 && !istr.eos()) Console.WriteLine(istr.next());
            Console.WriteLine("Reset!");
            istr.reset();
            i = 0;
            while (i++ < 5 && !istr.eos()) Console.WriteLine(istr.next());
            Console.WriteLine("Kilka liczb pierwszych: ");
            PrimeStream pstr = new PrimeStream();
            i = 0;
            while (i++ < 5 && !pstr.eos()) Console.WriteLine(pstr.next());
            Console.WriteLine("Kilka liczb losowych: ");
            RandomStream rstr = new RandomStream();
            i = 0;
            while (i++ < 5) Console.WriteLine(rstr.next());
            Console.WriteLine("Losowe stringi o d³ugoœciach równym liczbom pierwszym");
            RandomWordStream rwstr = new RandomWordStream();
            i = 0;
            while (i++ < 5) Console.WriteLine(rwstr.next());

        }
    }
}