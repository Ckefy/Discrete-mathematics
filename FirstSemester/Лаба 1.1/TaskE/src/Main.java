import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    static ArrayList<ArrayList<Integer>> g = new ArrayList<>();
    static ArrayList<ArrayList<Integer>> depend = new ArrayList<>(), how = new ArrayList<>();
    static ArrayList<Integer> numbers = new ArrayList<>();

    public static int dfs(int v, int depth) {
        int ans = depth;
        for (int i = 0; i < g.get(v).size(); i++) {
            if (g.get(g.get(v).get(i)).size() == 0) {
                continue;
            }
            ans = Math.max(ans, dfs(g.get(v).get(i), depth + 1));
        }
        return ans;
    }

    public static int dfs2(int v) {
        if (g.get(v).size() == 0) {
            return numbers.get(v);
        }
        int now = 0;
        for (int i = 0; i < g.get(v).size(); i++) {
            now += (Math.pow(2, g.get(v).size() - i - 1) * dfs2(g.get(v).get(i)));
        }
        return how.get(v).get(now);
    }

    public static void main(String[] args) {
        Scanner f1 = new Scanner(System.in);
        int n = f1.nextInt();
        StringBuilder answer = new StringBuilder();
        ArrayList<Integer> leaves = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            depend.add(new ArrayList<>());
            how.add(new ArrayList<>());
            g.add(new ArrayList<>());
        }
        for (int i = 0; i < n; i++) {
            int m = f1.nextInt();
            if (m == 0) {
                leaves.add(i);
                continue;
            }
            for (int j = 0; j < m; j++) {
                int v = f1.nextInt() - 1;
                g.get(i).add(v);
                depend.get(i).add(v);
            }
            for (int j = 0; j < Math.pow(2, m); j++) {
                how.get(i).add(f1.nextInt());
            }
        }
        //System.out.println(g);
        System.out.println(dfs(n - 1, 1));
        int k = leaves.size();
        for (int j = 0; j < n; j++) {
            numbers.add(0);
        }
        answer.append(dfs2(n - 1));
        for (int i = 1; i < Math.pow(2, k); i++) {
            int j = k - 1;
            if (numbers.get(leaves.get(j)) == 0) {
                numbers.set(leaves.get(j), 1);
            } else {
                while (numbers.get(leaves.get(j)) != 0) {
                    numbers.set(leaves.get(j), 0);
                    j--;
                }
                numbers.set(leaves.get(j), 1);
            }
            answer.append(dfs2(n - 1));
        }
        System.out.println(answer);
        System.out.println();
    }
}
