import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

      private static Map<Integer, Integer> buildings = new TreeMap<>();
    public static void main(String[] args) {
        Scanner sn = new Scanner(System.in);
        int N = sn.nextInt();
        for (int i = 0; i < N; i++) {
            buildings.put(i, sn.nextInt());
        }
        int maxArea = 0;
        for (int i =0; i < N; i++) {
            int sum;
            int area = buildings.get(i);
            int leftArea = goLeft(i, area);
            int rightArea = goRight(i, area);
            sum = area + leftArea + rightArea;
            if (sum > maxArea) {
                maxArea = sum;
            }
        }
        sn.close();
        System.out.println(maxArea);
    }

    private static int goLeft(int i, int compareValue) {
        int sum = 0;
        if (i != 0) {
            for (int j = i-1; j >= 0; j--) {
                int area = buildings.get(j);
                if (area < compareValue) {
                    break;
                }
                sum+=compareValue;
            }
        }
        return sum;
    }
    private static int goRight(int i, int compareValue) {
        int sum = 0;
        if (i != buildings.size()-1) {
            for (int j = i+1; j < buildings.size(); j++) {
                int area = buildings.get(j);
                if (area < compareValue) {
                    break;
                }
                sum+=compareValue;
            }
        }
        return sum;
    }
}