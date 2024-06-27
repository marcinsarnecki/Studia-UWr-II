using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using L03Z01;

namespace Zadanie1main
{
    class Program
    {
        static void Main(string[] args)
        {
            Lista<int> l = new Lista<int>();
            l.push_back(5);
            l.push_back(10);
            l.push_back(20);                    //cala lista: 5 10 20
            Console.WriteLine(l.begin.value);   // 5
            Console.WriteLine(l.end.value);     // 20
            l.push_back(25);
            l.push_back(30);
            while (l.is_empty() == false)        //cala lista: 5 10 20 25 30
            {
                Console.WriteLine(l.pop_front());
            }
            Console.ReadKey();
        }
    }
}
