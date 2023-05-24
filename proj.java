import java.math.BigDecimal;

public class proj {
    public static boolean is_primitive_root(long g, long n) {
        int i;
        BigDecimal number = new BigDecimal(1);

        for (i = 1; i < n - 1; i++) {
            number = number.multiply(new BigDecimal(g));

            if (number.remainder(new BigDecimal(n)).intValue() == 1)
                return false;
        }

        return true;
    }

    public static void main(String[] args) {
        long p = 5003;

        int count = 0;

        for (long i = 1; i < p; i++) {
            if (is_primitive_root(i, p)) {
                count++;
                // System.out.println(i + " Is primitive root to " + p);

            }
        }

        System.out.println(p+" Has "+count+" primative root");

    }
}
