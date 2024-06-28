package struktury;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

public class ZbiorTablicowyTest {
    @Test
    public void testSzukajNieistniejacyElement() {
        ZbiorTablicowy zbior = new ZbiorTablicowy(5);
        Para foundPara = zbior.szukaj("nonexistent");
        assertNull(foundPara);
    }

    @Test
    public void testWstawNowyElement() {
        ZbiorTablicowy zbior = new ZbiorTablicowy(5);
        Para para = new Para("a", 42.0);
        zbior.wstaw(para);
        assertEquals(1, zbior.ile());
        Para foundPara = zbior.szukaj("a");
        assertNotNull(foundPara);
        assertEquals(para, foundPara);
    }

    @Test
    public void testAktualizujIstniejacyElement() {
        ZbiorTablicowy zbior = new ZbiorTablicowy(5);
        Para para1 = new Para("a", 42.0);
        Para para2 = new Para("a", 100.0);

        zbior.wstaw(para1);
        zbior.wstaw(para2);

        assertEquals(1, zbior.ile());
        assertEquals(100.0, zbior.szukaj("a").getWartosc());
    }

    @Test
    public void testWstawDoPelnegoZbioru() {
        ZbiorTablicowy zbior = new ZbiorTablicowy(2);
        zbior.wstaw(new Para("a", 42.0));
        zbior.wstaw(new Para("b", 100.0));

        assertThrows(IllegalStateException.class, () -> {
            zbior.wstaw(new Para("c", 200.0));
        });
    }

    @Test
    public void testUsunElement() {
        ZbiorTablicowy zbior = new ZbiorTablicowy(5);
        Para para = new Para("a", 42.0);
        zbior.wstaw(para);

        zbior.usun("a");

        assertEquals(0, zbior.ile());
        assertNull(zbior.szukaj("a"));
    }

    @Test
    public void testUsunNieitsniejacyElement() {
        ZbiorTablicowy zbior = new ZbiorTablicowy(5);
        zbior.usun("nonexistent");

        assertEquals(0, zbior.ile());
    }

    @Test
    public void testCzysc() {
        ZbiorTablicowy zbior = new ZbiorTablicowy(5);
        zbior.wstaw(new Para("a", 42.0));
        zbior.wstaw(new Para("b", 100.0));

        zbior.czysc();

        assertEquals(0, zbior.ile());
    }

    @Test
    public void testClone() {
        ZbiorTablicowy zbior1 = new ZbiorTablicowy(5);
        zbior1.wstaw(new Para("a", 42.0));
        zbior1.wstaw(new Para("b", 100.0));

        ZbiorTablicowy zbior2 = zbior1.clone();

        assertNotSame(zbior1, zbior2);

        assertEquals(zbior1.ile(), zbior2.ile());
        assertEquals(zbior1.szukaj("a"), zbior2.szukaj("a"));
        assertEquals(zbior1.szukaj("b"), zbior2.szukaj("b"));

        zbior2.wstaw(new Para("c", 200.0));

        assertEquals(2, zbior1.ile());
        assertNotNull(zbior1.szukaj("a"));
        assertNotNull(zbior1.szukaj("b"));
        assertNull(zbior1.szukaj("c"));
    }
}