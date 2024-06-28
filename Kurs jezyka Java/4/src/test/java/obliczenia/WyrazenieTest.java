package obliczenia;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import struktury.Para;

import static org.junit.jupiter.api.Assertions.*;

class WyrazenieTest {
    private static final double EPSILON = 1e-9;
    @BeforeEach
    void setUp() {
        Zmienna.zbiorTablicowy.wstaw(new Para("x", 1.618));
    }
    @Test
    public void test1() { //7 + 5 * 3 - 1
        Wyrazenie w =
                new Odejmij(
                        new Dodaj(
                                new Liczba(7),
                                new Mnoz(
                                        new Liczba(5),
                                        new Liczba(3))),
                        new Liczba(1));
        System.out.println(w + " = " + w.oblicz());
        assertEquals(w.oblicz(), 21, EPSILON);
    }
    @Test
    public void test2() { //~ (2 - x) * e
        Wyrazenie w =
                new Przeciwienstwo(
                        new Mnoz(
                                new Odejmij(
                                        new Liczba(2),
                                        new Zmienna("x")
                                ),
                                new E()
                        )
                );
        System.out.println(w + " = " + w.oblicz());
        assertEquals(w.oblicz(), -(2 - 1.618) * Math.E, EPSILON);
    }

    @Test
    public void test3() { //(3 * π - 1) / (x + 5)
        Wyrazenie w =
                new Dziel(
                        new Odejmij(
                                new Mnoz(
                                        new Liczba(3),
                                        new PI()
                                ),
                                new Liczba(1)
                        ),
                        new Dodaj(
                                new Zmienna("x"),
                                new Liczba(5)
                        )
                );
        assertEquals(w.oblicz(), (3 * Math.PI - 1) / (1.618 + 5), EPSILON);
        System.out.println(w + " = " + w.oblicz());
    }
    @Test
    public void test4() {//sin( (x + 13) * π / (1 - x) )
        Wyrazenie w =
                new Sin(
                        new Dziel(
                                new Mnoz(
                                        new Dodaj(
                                                new Zmienna("x"),
                                                new Liczba(13)
                                        ),
                                        new PI()
                                ),
                                new Odejmij(
                                        new Liczba(1),
                                        new Zmienna("x")
                                )
                        )
                );
        assertEquals(w.oblicz(), Math.sin((1.618 + 13) * Math.PI / (1 - 1.618)), EPSILON);
        System.out.println(w + " = " + w.oblicz());
    }
    @Test
    public void test5() { //exp(5) + x * log(e, x)
        Wyrazenie w = new Dodaj(
                new Exp(new Liczba(5)),
                new Mnoz(
                        new Zmienna("x"),
                        new Log(
                                new E(),
                                new Zmienna("x")
                        )
                )
        );
        assertEquals(w.oblicz(), Math.exp(5) + 1.618 * Math.log(1.618), EPSILON);
        System.out.println(w + " = " + w.oblicz());
    }


}