package struktury;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;


class ParaTest {
    private static final double EPSILON = 1e-9;

    @Test
    public void testValidConstructor() {
        Para validPara = new Para("validkey", 42.0);

        // Check that the object is created successfully
        assertNotNull(validPara);
        assertEquals("validkey", validPara.klucz);
        assertEquals(42.0, validPara.getWartosc(), 0.0);
    }

    @Test
    public void testInvalidConstructorNullKlucz() {
        // Invalid 'klucz': null
        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> {
            new Para(null, 42.0);
        });

        assertEquals("Klucz nie moze byc nullem oraz musi skladac sie z malych liter alfabetu angielskiego", exception.getMessage());
    }

    @Test
    public void testInvalidConstructorUpperCaseKlucz() {
        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> {
            new Para("InvalidKey", 42.0);
        });

        assertEquals("Klucz nie moze byc nullem oraz musi skladac sie z malych liter alfabetu angielskiego", exception.getMessage());
    }

    @Test
    public void testInvalidConstructorNumericKlucz() {
        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> {
            new Para("Invalid123", 42.0);
        });

        assertEquals("Klucz nie moze byc nullem oraz musi skladac sie z malych liter alfabetu angielskiego", exception.getMessage());
    }
    @Test
    public void testClone() {
        Para originalPara = new Para("key", 42.0);
        Para clonedPara = originalPara.clone();

        assertNotSame(originalPara, clonedPara);

        assertEquals(originalPara.klucz, clonedPara.klucz);
        assertEquals(originalPara.getWartosc(), clonedPara.getWartosc(), EPSILON);

        originalPara.setWartosc(100.0);

        assertEquals(100.0, originalPara.getWartosc(), EPSILON);

        assertEquals(42.0, clonedPara.getWartosc(), EPSILON);
    }

    @Test
    public void testCompareTo() {
        Para para1 = new Para("abc", 42.0);
        Para para2 = new Para("def", 42.0);
        Para para3 = new Para("ghi", 24.0);

        assertEquals(0, para1.compareTo(para2));

        assertTrue(para1.compareTo(para3) > 0);

        assertTrue(para3.compareTo(para2) < 0);
    }
}