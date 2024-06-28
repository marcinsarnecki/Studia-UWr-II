package struktury;

public interface Zbior {
    /**
     * Wyszukuje parę z zadanym kluczem.
     *
     * @param k klucz do wyszukania
     * @return znaleziona para lub null, jeśli nie znaleziono pary o podanym kluczu
     */
    Para szukaj(String k);

    /**
     * Wstawia do zbioru nową parę. Gdy para o podanym kluczu już istnieje w zbiorze,
     * metoda dokonuje aktualizacji wartości w znalezionej parze.
     *
     * @param p para do wstawienia lub zaktualizowania
     */
    void wstaw(Para p);

    /**
     * Usuwa ze zbioru parę o zadanym kluczu. Gdy para o podanym kluczu nie istnieje w zbiorze,
     * metoda nic nie robi.
     *
     * @param k klucz pary do usunięcia
     */
    void usun(String k);

    /**
     * Usuwa wszystkie pary ze zbioru, czyniąc zbiór pustym.
     */
    void czysc();

    /**
     * Podaje liczbę wszystkich par w zbiorze.
     *
     * @return liczba par w zbiorze
     */
    int ile();
}
