using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace L03Z01
{
    public class Element<T>
    {
        public T value;
        public Element<T> ptr1, ptr2;
        public Element(T nowy)
        {
            value = nowy;
            ptr1 = ptr2 = null;
        }
    }

    public class Lista<T>
    {
        public Element<T> begin, end;
        private int size;

        public bool is_empty()
        {
            if (size == 0) return true;
            else return false;
        }
        public void push_front(T nowy)
        {
            if (size == 0)
            {
                Element<T> nowy_el = new Element<T>(nowy);
                nowy_el.ptr2 = null;
                nowy_el.ptr1 = null;
                begin = nowy_el;
                end = nowy_el;
                size++;
                return;
            }
            else
            {
                Element<T> nowy_el = new Element<T>(nowy);
                nowy_el.ptr2 = begin;
                nowy_el.ptr1 = null;
                begin.ptr1 = nowy_el;
                begin = nowy_el;
                size++;
            }
        }
        public void push_back(T nowy)
        {
            if (size == 0)
            {
                Element<T> nowy_el = new Element<T>(nowy);
                nowy_el.ptr2 = null;
                nowy_el.ptr1 = null;
                begin = nowy_el;
                end = nowy_el;
                size++;
                return;
            }
            else
            {
                Element<T> nowy_el = new Element<T>(nowy);
                nowy_el.ptr1 = end;
                nowy_el.ptr2 = null;
                end.ptr2 = nowy_el;
                end = nowy_el;
                size++;
            }
        }
        public T pop_front()
        {
            if (is_empty()) throw new InvalidOperationException("Pusta lista!");
            if (size == 1)
            {
                T usuwany = begin.value;
                begin = null;
                end = null;
                size--;
                return usuwany;
            }
            else
            {
                T usuwany = begin.value;
                begin = begin.ptr2;
                begin.ptr1 = null;
                size--;
                return usuwany;
            }
        }
        public T pop_back()
        {
            if (is_empty()) throw new InvalidOperationException("Pusta lista!");
            if (size == 1)
            {
                T usuwany = begin.value;
                begin = null;
                end = null;
                size--;
                return usuwany;
            }
            else
            {
                T usuwany = begin.value;
                end = end.ptr1;
                end.ptr2 = null;
                size--;
                return usuwany;
            }
        }
        public Lista()
        {
            begin = null;
            end = null;
            size = 0;
        }
    }
}
