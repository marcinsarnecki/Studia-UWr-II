using System;
using System.Collections.Generic;

namespace zadanie4
{
    class ListaLeniwa
    {
        protected List<int> l;
        protected int len;
        protected Random rnd;
        virtual public int element(int i)
        {
            if (i <= len) return l[i - 1];
            else while (i > len)
                {
                    l.Add(rnd.Next(Int32.MinValue, Int32.MaxValue));
                    len++;
                }
            return l[i - 1];
        }
        public int size()
        {
            return len;
        }
        public ListaLeniwa()
        {
            len = 0;
            rnd = new Random();
            l = new List<int>();
        }
    }
    class Pierwsze : ListaLeniwa
    {
        int lastPrime;
        bool isPrime(int num)
        {
            if (num < 2) return false;
            for (int i = 2; i * i <= num; i++)
                if (num % i == 0) return false;
            return true;
        }
        override public int element(int i)
        {
            if(len == 0)
            {
                l.Add(2);
                len = 1;
                lastPrime = 2;
            }
            if (i <= len) return l[i - 1];
            else while (i > len)
                {
                    lastPrime++;
                    while (!isPrime(lastPrime)) lastPrime++;
                    l.Add(lastPrime);
                    len++;
                }
            return l[i - 1];
        }
        public Pierwsze()
        {
            lastPrime = -1;
            len = 0;
            rnd = new Random();
            l = new List<int>();
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            ListaLeniwa ll = new ListaLeniwa();
            Console.Write("Wywoluje element(5): ");
            Console.WriteLine(ll.element(5));
            Console.Write("Wywoluje element(7): ");
            Console.WriteLine(ll.element(7));
            Console.WriteLine("Wypisuje 10 pierwszych elementow");
            for (int i = 1; i <= 10; i++) Console.WriteLine(i + ": " + ll.element(i));
            Pierwsze lp = new Pierwsze();
            Console.WriteLine("Wypisuje pierwsze 15 liczb pierwszych: ");
            for (int i = 1; i <= 15; i++) Console.WriteLine(i + ": " + lp.element(i));
        }
    }
}
