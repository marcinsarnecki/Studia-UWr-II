using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace L03Z02
{
    public class Element<K, V>
    {
        public K key;
        public V value;
        public Element<K, V> ptr;
        public Element(K newKey, V newValue)
        {
            key = newKey;
            value = newValue;
            ptr = null;
        }
    }
    public class MyDictionary<K, V>
    {
        public Element<K, V> begin;
        public MyDictionary()
        {
            begin = null;
        }
        public void Insert(K key, V value)
        {
            this.Erase(key);
            if (begin == null)
            {
                Element<K, V> p = new Element<K, V>(key, value);
                begin = p;
                return;
            }
            else
            {
                Element<K, V> p = new Element<K, V>(key, value);
                p.ptr = begin;
                begin = p;
                return;
            }
        }
        public V Find(K key)
        {
            Element<K, V> it = begin;
            while (it != null)
            {
                if (it.key.Equals(key))
                    return it.value;
                it = it.ptr;
            }
            return default(V);
        }
        public void Erase(K key)
        {
            if (Find(key) == null) //jak nie ma to nic nie robimy
                return;
            Element<K, V> it = begin;
            if (it.key.Equals(key))
            {
                begin = begin.ptr;
                return;
            }
            while (it.ptr != null)
            {
                if (it.ptr.key.Equals(key))
                {
                    it.ptr = it.ptr.ptr;
                    return;
                }
                it = it.ptr;
            }
        }
    }
}


