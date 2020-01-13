import java.io.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Main {

    private static int n, m, upperColor = 0, inf = 1000000;
    static ArrayList<Tuple> edges = new ArrayList<>();
    static ArrayList<Boolean> I = new ArrayList<>();

    static class Tuple {
        int first, second, color;

        Tuple(int first, int second, int color) {
            this.first = first;
            this.second = second;
            this.color = color;
        }
    }

    static class DSU {
        ArrayList<Integer> master;
        ArrayList<Integer> rank;

        DSU() {
            ArrayList<Integer> master = new ArrayList<>();
            ArrayList<Integer> rank = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                master.add(i);
                rank.add(1);
            }
            this.master = master;
            this.rank = rank;
        }

        int findMaster(int now) {
            if (now == master.get(now)) {
                return now;
            } else {
                master.set(now, findMaster(master.get(now)));
                return master.get(now);
            }
        }

        void connect(int from, int to) {
            int masterFrom = findMaster(from);
            int masterTo = findMaster(to);
            if (rank.get(masterTo) < rank.get(masterFrom)) {
                master.set(masterTo, masterFrom);
            } else {
                master.set(masterFrom, masterTo);
            }
            if (rank.get(masterFrom).equals(rank.get(masterTo))) {
                rank.set(masterTo, rank.get(masterTo) + 1);
            }
        }
    }

    static ArrayList<ArrayList<Integer>> matrix;
    static ArrayList<Integer> X1, X2, distance;
    static ArrayList<Integer> path;

    static int BFS() {
        distance = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            distance.add(inf);
        }
        int mini = -1, min = inf; //if equals -1 then there`s no way between X1 X2
        //add extra vertex
        Queue<Integer> queue = new LinkedList<>();
        for (int i : X1) {
            queue.add(i);
            distance.set(i, 0);
        }
        while (!queue.isEmpty()) {
            int temp = queue.remove();
            for (int i : matrix.get(temp)) {
                if (distance.get(i) > 1 + distance.get(temp)) {
                    if (distance.get(i) == inf) {
                        queue.add(i);
                    }
                    distance.set(i, 1 + distance.get(temp));
                    path.set(i, temp);
                }
            }
        }
        for (int i : X2) {
            if (distance.get(i) < min) {
                min = distance.get(i);
                mini = i;
            }
        }
        return mini;
    }


    public static void main(String[] args) {
        try (Scanner in = new Scanner(new FileReader("rainbow.in"))) {
            try (BufferedWriter out = new BufferedWriter(new FileWriter("rainbow.out"))) {
                n = in.nextInt();
                m = in.nextInt();
                for (int i = 0; i < m; i++) {
                    Tuple tuple = new Tuple(in.nextInt(), in.nextInt(), in.nextInt());
                    tuple.first--;
                    tuple.second--;
                    tuple.color--;
                    edges.add(tuple);
                    upperColor = Math.max(upperColor, tuple.color);
                    I.add(false);
                }
                upperColor++;
                while (true) {
                    matrix = new ArrayList<>();
                    path = new ArrayList<>();
                    for (int i = 0; i < m; i++) {
                        matrix.add(new ArrayList<>());
                        path.add(-1);
                    }
                    ArrayList<Boolean> colors = new ArrayList<>();
                    for (int i = 0; i < upperColor; i++) {
                        colors.add(false);
                    }
                    for (int i = 0; i < m; i++) {
                        if (I.get(i)) {
                            //add to dsu everything except edge with number i
                            DSU dsu = new DSU();
                            colors = new ArrayList<>();
                            for (int j = 0; j < upperColor; j++) {
                                colors.add(false);
                            }
                            for (int j = 0; j < m; j++) {
                                if (i == j) {
                                    continue;
                                }
                                if (I.get(j)) {
                                    dsu.connect(edges.get(j).first, edges.get(j).second);
                                    colors.set(edges.get(j).color, true);
                                }
                            }
                            //now we have set I, we need to form graph
                            for (int j = 0; j < m; j++) {
                                if (!I.get(j)) {
                                    if (dsu.findMaster(edges.get(j).first) != dsu.findMaster(edges.get(j).second)) {
                                        matrix.get(i).add(j);
                                    }
                                    if (!colors.get(edges.get(j).color)) {
                                        matrix.get(j).add(i);
                                    }
                                }
                            }
                        }
                    }
                    //now we need to form X1 and X2 sets
                    X1 = new ArrayList<>();
                    X2 = new ArrayList<>();
                    colors = new ArrayList<>();
                    for (int i = 0; i < upperColor; i++) {
                        colors.add(false);
                    }
                    DSU newDsu = new DSU();
                    for (int i = 0; i < m; i++) {
                        if (I.get(i)) {
                            newDsu.connect(edges.get(i).first, edges.get(i).second);
                            colors.set(edges.get(i).color, true);
                        }
                    }
                    for (int i = 0; i < m; i++) {
                        if (!I.get(i)) {
                            if (newDsu.findMaster(edges.get(i).first) != newDsu.findMaster(edges.get(i).second)) {
                                X1.add(i);
                            }
                            if (!colors.get(edges.get(i).color)) {
                                X2.add(i);
                            }
                        }
                    }
                    int current = BFS();
                    if (current == -1) {
                        break;
                    }
                    while (current != -1) {
                        I.set(current, !I.get(current));
                        current = path.get(current);
                    }
                }
                ArrayList<Integer> answer = new ArrayList<>();
                for (int i = 0; i < m; i++) {
                    if (I.get(i)) {
                        answer.add(i);
                    }
                }
                out.write(Integer.toString(answer.size()));
                out.newLine();
                for (int i : answer) {
                    out.write(Integer.toString(i + 1));
                    out.write(' ');
                }
            }
        } catch (IOException e) {
            //ignore
        }
    }
}