using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using L03Z02;

namespace Zadanie2main
{
    class Program
    {
        static void Main(string[] args)
        {
            MyDictionary<int, string> m = new MyDictionary<int, string>();
            m.Insert(1, "Napis");
            m.Insert(1, "Napis");
            m.Insert(1, "Nowy Napis");//nadpisanie
            m.Insert(4, "abaab");
            m.Insert(8, "Slownik");
            m.Insert(10, "Obiekty");
            m.Insert(14, "Wroclaw");
            m.Insert(15, "Komputer");
            m.Insert(30, "Zeszyt");
            m.Insert(40, "Dlugopis");
            m.Insert(50, "Okno");

            m.Erase(50);//usuwanie istniejacych kluczy
            m.Erase(30);

            m.Erase(46);//usuniecie nieistniejaceo elementu nie powoduje bledu

            if (m.Find(50) != null)
                Console.WriteLine(m.Find(50));
            else Console.WriteLine("Nie ma pary z kluczem 50");
            if (m.Find(14) != null)
                Console.WriteLine(m.Find(14));
            else Console.WriteLine("Nie ma pary z kluczem 14");
            Console.ReadKey();
        }
    }
}