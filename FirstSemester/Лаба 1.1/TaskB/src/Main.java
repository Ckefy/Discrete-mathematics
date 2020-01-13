import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner f1 = new Scanner(System.in);
        int n = f1.nextInt(), m = f1.nextInt();
        ArrayList<Integer> check = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            check.add(-1); //not initialized;
        }
        ArrayList<ArrayList<Integer>> mas = new ArrayList<>();
        ArrayList<ArrayList<Integer>> masres = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            ArrayList<Integer> mas1 = new ArrayList<>();
            ArrayList<Integer> mas2 = new ArrayList<>();
            for (int j = 0; j < n; j++) {
                int c = f1.nextInt();
                mas1.add(c);
                mas2.add(c);
            }
            mas.add(mas1);
            masres.add(mas2);
        }
        int now = 0;
        boolean flagLonely = true, flagNext = false;
        while (flagLonely) {
            flagLonely = false;
            for (int i = 0; i < m; i++) {
                int count = 0;
                for (int j = 0; j < n; j++) {
                    if (check.get(j) != -1) {
                        if ((check.get(j) == 0 && mas.get(i).get(j)==0) ||(check.get(j)==1 && mas.get(i).get(j)==1)){
                            flagNext = true;
                            break;
                        } else {
                            mas.get(i).set(j, -1);
                        }
                    }
                    if (mas.get(i).get(j) == -1) {
                        count++;
                    } else {
                        now = j;
                    }
                }
                if (flagNext){
                    flagNext = false;
                    continue;
                }
                if ((count == n) || (count < n - 1)) {
                    continue;
                }
                flagLonely = true;
                if (mas.get(i).get(now) == 1) {
                    check.set(now, 1);
                } else {
                    check.set(now, 0);
                }
                mas.get(i).set(now, -1);
            }
        }
        for (int i = 0; i < n; i++) {
            if (check.get(i) == -1) {
                check.set(i, 0);
            }
        }
        for (int i = 0; i < m; i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (masres.get(i).get(j) == -1) {
                    continue;
                }
                now = check.get(j);
                if (masres.get(i).get(j) == 0) {
                    now = (now == 0) ? 1 : 0;
                }
                sum += now;
            }
            if (sum == 0) {
                System.out.println("YES");
                return;
            }
        }
        System.out.println("NO");
    }
}
