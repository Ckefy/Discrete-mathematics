import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class Main {

    static int n;

    static class Pair {
        int weight, index;

        Pair(int first, int second) {
            this.weight = first;
            this.index = second;
        }
    }

    static ArrayList<ArrayList<Integer>> matrix = new ArrayList<>();
    static ArrayList<Integer> parent = new ArrayList<>(), answer = new ArrayList<>();
    static ArrayList<Boolean> was = new ArrayList<>();

    static boolean dfs(int now) {
        if (was.get(now)) {
            return false;
        }
        was.set(now, true);
        for (int edge : matrix.get(now)) {
            if (parent.get(edge) == -1 || dfs(parent.get(edge))) {
                parent.set(edge, now);
                answer.set(now, edge);
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        try (Scanner in = new Scanner(new FileReader("matching.in"))) {
            try (BufferedWriter out = new BufferedWriter(new FileWriter("matching.out"))) {
                n = in.nextInt();
                ArrayList<Pair> vertex = new ArrayList<>();
                for (int i = 0; i < n; i++) {
                    vertex.add(new Pair(in.nextInt(), i));
                    matrix.add(new ArrayList<>());
                    was.add(false);
                    parent.add(-1);
                    answer.add(-1);
                }
                for (int i = 0; i < n; i++) {
                    int m = in.nextInt();
                    for (int j = 0; j < m; j++) {
                        int ver = in.nextInt();
                        ver--;
                        matrix.get(i).add(ver);
                    }
                }
                Collections.sort(vertex, Comparator.comparingInt(p -> p.weight));
                Collections.reverse(vertex);
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        was.set(j, false);
                    }
                    dfs(vertex.get(i).index);
                }
                for (int i = 0; i < answer.size(); i++) {
                    out.write(Integer.toString(answer.get(i) + 1));
                    out.write(' ');
                }
            }
        } catch (IOException e) {
            //ignore
        }
    }
}
