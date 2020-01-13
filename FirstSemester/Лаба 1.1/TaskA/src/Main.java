import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    static int n;
    static int maxn;
    static ArrayList<ArrayList<Integer>> g, gtr;
    static ArrayList<Boolean> was;
    static ArrayList<Integer> order, component;

    public static int xor(int a) {
        return a = maxn - 1 - a;
    }

    public static void dfsG(int v) {
        was.set(v, true);
        int u;
        for (int i = 0; i < maxn; i++) {
            if (g.get(v).get(i) == -1) {
                continue;
            }
            u = i;
            if (!was.get(u)) {
                dfsG(u);
            }
        }
        order.add(v);
    }

    public static void dfsGTR(int v, int count) {
        component.set(v, count);
        int u;
        for (int i = 0; i < maxn; i++) {
            if (gtr.get(v).get(i) == -1) {
                continue;
            }
            u = i;
            if (component.get(u) == -1) {
                dfsGTR(u, count);
            }
        }
    }

    public static void main(String[] args) {
        Scanner f1 = new Scanner(System.in);
        n = f1.nextInt() * 2;
        maxn = (int) Math.pow(2, Math.ceil(Math.log(n) / Math.log(2)));
        int m = f1.nextInt() * 2;
        g = new ArrayList<>();
        gtr = new ArrayList<>();
        was = new ArrayList<>();
        component = new ArrayList<>();
        order = new ArrayList<>();
        for (int i = 0; i < maxn; i++) {
            was.add(false);
            component.add(-1);
        }
        for (int i = 0; i < maxn; i++) {
            ArrayList<Integer> mas1 = new ArrayList<>();
            ArrayList<Integer> mas2 = new ArrayList<>();
            for (int j = 0; j < maxn; j++) {
                mas1.add(-1);
                mas2.add(-1);
            }
            g.add(mas1);
            gtr.add(mas2);
        }
        for (int i = 0; i < m / 2; i++) {
            int a = f1.nextInt(), b = f1.nextInt();
            a = translate(a);
            b = translate(b);
            if (g.get(xor(a)).get(b) == -1) {
                g.get(xor(a)).set(b, 1);
            }
            if (g.get(xor(b)).get(a) == -1) {
                g.get(xor(b)).set(a, 1);
            }
            if (gtr.get(b).get(xor(a)) == -1) {
                gtr.get(b).set(xor(a), 1);
            }
            if (gtr.get(a).get(xor(b)) == -1) {
                gtr.get(a).set(xor(b), 1);
            }
        }
        for (int i = 0; i < n / 2; i++) {
            if (!was.get(i)) {
                dfsG(i);
            }
        }
        for (int i = 0; i < n / 2; i++) {
            if (!was.get(xor(i))) {
                dfsG(xor(i));
            }
        }
        int count = 0;
        for (int i = 0; i < n / 2; i++) {
            int c = order.get(n - 1 - i);
            if (component.get(c) == -1) {
                dfsGTR(c, count);
                count++;
            }
        }
        for (int i = 0; i < n / 2; i++) {
            int c = order.get(n - 1 - (i + n / 2));
            if (component.get(c) == -1) {
                dfsGTR(c, count);
                count++;
            }
        }
        for (int i = 0; i < n / 2; i++) {
            if (component.get(i) == component.get(xor(i))) {
                System.out.println("YES");
                return;
            }
        }
        System.out.println("NO");
    }

    private static int translate(int a) {
        if (a < 0) {
            a = -1 * (a);
            a--;
            a = xor(a);
        } else {
            a--;
        }
        return a;
    }
}
