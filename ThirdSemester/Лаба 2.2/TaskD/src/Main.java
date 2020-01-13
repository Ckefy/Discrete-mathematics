import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {

    static int n, m;
    static HashMap<Integer, ArrayList<Integer>> map = new HashMap<>();

    public static boolean axiom3(Map.Entry<Integer, ArrayList<Integer>> A, Map.Entry<Integer, ArrayList<Integer>> B) {
        //B>A
        ArrayList<Boolean> B_A = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            B_A.add(false);
        }
        for (int elem : B.getValue()) {
            B_A.set(elem, true);
        }
        for (int elem : A.getValue()) {
            B_A.set(elem, false);
        }
        for (int curBit = 0; curBit < n; curBit++) {
            if (B_A.get(curBit)) {
                int newMask = (A.getKey() | (1 << curBit));
                if (map.containsKey(newMask)) {
                    return true;
                }
            }
        }
        return false;
    }

    public static void main(String[] args) {
        try (Scanner in = new Scanner(new FileReader("check.in"))) {
            try (BufferedWriter out = new BufferedWriter(new FileWriter("check.out"))) {
                n = in.nextInt();
                m = in.nextInt();
                int full = 1 << n;
                int mask; //mask of set
                ArrayList<Integer> E; //set of numbers

                boolean axiom1 = false;
                for (int i = 0; i < m; i++) {
                    int count = in.nextInt();
                    mask = 0;
                    E = new ArrayList<>();
                    for (int j = 0; j < count; j++) {
                        int temp = in.nextInt();
                        temp--;
                        mask |= (1 << temp);
                        E.add(temp);
                    }
                    if (count == 0) {
                        axiom1 = true;
                    }
                    map.put(mask, E);
                }
                if (!axiom1) {
                    out.write("NO");
                    return;
                }

                boolean axiom2 = false;
                ArrayList<Boolean> dp = new ArrayList<>();
                for (int curMask = 0; curMask < full; curMask++) {
                    int curBit = 0;
                    dp.add(map.containsKey(curMask));
                    axiom2 = dp.get(curMask); //if map contains it than it`s dp
                    //must be true
                    while (curMask >= (1 << curBit)) {
                        int childMask = (~(1 << curBit)) & curMask;
                        boolean temp = dp.get(curMask) & dp.get(childMask);
                        dp.set(curMask, temp);
                        curBit++;
                    }
                    if (axiom2 && !dp.get(curMask)) {
                        out.write("NO");
                        return;
                    }
                }

                for (Map.Entry<Integer, ArrayList<Integer>> A : map.entrySet()) {
                    for (Map.Entry<Integer, ArrayList<Integer>> B : map.entrySet()) {
                        if (A.getValue().size() == B.getValue().size()) {
                            continue;
                        }
                        if (A.getValue().size() > B.getValue().size()) {
                            if (!axiom3(B, A)) {
                                out.write("NO");
                                return;
                            }
                        } else {
                            if (!axiom3(A, B)) {
                                out.write("NO");
                                return;
                            }
                        }
                    }
                }
                out.write("YES");
            }
        } catch (IOException e) {
            //ignore
        }
    }
}
