import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class Main {

    private static int n;

    static class Pair {
        int weight, index;

        Pair(int first, int second) {
            this.weight = first;
            this.index = second;
        }
    }

    static ArrayList<Boolean> dependent = new ArrayList<>();

    private static void findDependences(int mask) {
        for (int i = 0; i < n; i++) {
            int curBit = (1 << i);
            if ((curBit & mask) == 0) {
                if (!dependent.get(mask | curBit)) {
                    dependent.set(mask | curBit, true);
                    findDependences(mask | curBit);
                }
            }
        }
    }

    public static void main(String[] args) {
        try (Scanner in = new Scanner(new FileReader("cycles.in"))) {
            try (BufferedWriter out = new BufferedWriter(new FileWriter("cycles.out"))) {
                n = in.nextInt();
                int m = in.nextInt();
                ArrayList<Pair> vertex = new ArrayList<>();
                for (int i = 0; i < n; i++) {
                    vertex.add(new Pair(in.nextInt(), i));
                }
                for (int i = 0; i < (1 << n); i++) {
                    dependent.add(false);
                }
                int mask;
                for (int i = 0; i < m; i++) {
                    mask = 0;
                    int count = in.nextInt();
                    for (int j = 0; j < count; j++) {
                        mask |= (1 << (in.nextInt() - 1));
                    }
                    if (!dependent.get(mask)) {
                        dependent.set(mask, true);
                        findDependences(mask);
                    }
                }

                Collections.sort(vertex, Comparator.comparingInt(p -> (p.weight)));
                Collections.reverse(vertex);
                mask = 0;
                int ans = 0;
                for (int i = 0; i < n; i++) {
                    int curBit = (1 << vertex.get(i).index);
                    if (!dependent.get(mask | curBit)) {
                        mask |= curBit;
                        ans += vertex.get(i).weight;
                    }
                }
                out.write(Integer.toString(ans));
            }
        } catch (IOException e) {
            //ignore
        }
    }
}