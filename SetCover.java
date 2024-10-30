import java.util.*;

public class SetCover {

    // 집합 데이터 (각 S 집합이 포함하는 원소들)
    static Map<String, Set<Integer>> sets = new HashMap<>();
    static {
        sets.put("S1", new HashSet<>(Arrays.asList(1, 2, 3, 8)));
        sets.put("S2", new HashSet<>(Arrays.asList(1, 2, 3, 4, 8)));
        sets.put("S3", new HashSet<>(Arrays.asList(1, 2, 3, 4)));
        sets.put("S4", new HashSet<>(Arrays.asList(2, 3, 4, 5, 7, 8)));
        sets.put("S5", new HashSet<>(Arrays.asList(4, 5, 6, 7)));
        sets.put("S6", new HashSet<>(Arrays.asList(5, 6, 7, 9, 10)));
        sets.put("S7", new HashSet<>(Arrays.asList(4, 5, 6, 7)));
        sets.put("S8", new HashSet<>(Arrays.asList(1, 2, 4, 8)));
        sets.put("S9", new HashSet<>(Arrays.asList(6, 9)));
        sets.put("S10", new HashSet<>(Arrays.asList(6, 10)));
    }

    // Greedy Algorithm을 사용하여 집합 커버를 계산
    public static Set<String> greedySetCover(Set<Integer> universe, Map<String, Set<Integer>> sets) {
        Set<String> cover = new HashSet<>();
        Set<Integer> remaining = new HashSet<>(universe);

        while (!remaining.isEmpty()) {
            String bestSet = null;
            int maxCovered = 0;

            for (Map.Entry<String, Set<Integer>> entry : sets.entrySet()) {
                Set<Integer> intersection = new HashSet<>(remaining);
                intersection.retainAll(entry.getValue());

                if (intersection.size() > maxCovered) {
                    bestSet = entry.getKey();
                    maxCovered = intersection.size();
                }
            }

            if (bestSet == null) break;

            cover.add(bestSet);
            remaining.removeAll(sets.get(bestSet));
            sets.remove(bestSet);
        }

        return cover;
    }

    // Optimal Solution을 찾기 위해 모든 조합을 시도
    public static Set<String> optimalSetCover(Set<Integer> universe, Map<String, Set<Integer>> sets) {
        Set<String> bestCover = null;

        List<String> setList = new ArrayList<>(sets.keySet());
        int n = setList.size();
        int minCoverSize = Integer.MAX_VALUE;

        // 모든 가능한 조합을 검사
        for (int i = 1; i < (1 << n); i++) {
            Set<String> cover = new HashSet<>();
            Set<Integer> covered = new HashSet<>();

            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) > 0) {
                    String set = setList.get(j);
                    cover.add(set);
                    covered.addAll(sets.get(set));
                }
            }

            if (covered.containsAll(universe) && cover.size() < minCoverSize) {
                bestCover = new HashSet<>(cover);
                minCoverSize = cover.size();
            }
        }

        return bestCover;
    }

    public static void main(String[] args) {
        // Universe 집합 설정 (전체 원소 집합 U)
        Set<Integer> universe = new HashSet<>(Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));

        // Greedy Algorithm 실행
        long startTime = System.nanoTime();
        Set<String> greedyCover = greedySetCover(universe, new HashMap<>(sets));
        long endTime = System.nanoTime();
        System.out.println("Greedy Set Cover: " + greedyCover);
        System.out.println("Greedy Algorithm Time: " + (endTime - startTime) + " ns");

        // Optimal Solution 실행
        startTime = System.nanoTime();
        Set<String> optimalCover = optimalSetCover(universe, new HashMap<>(sets));
        endTime = System.nanoTime();
        System.out.println("Optimal Set Cover: " + optimalCover);
        System.out.println("Optimal Algorithm Time: " + (endTime - startTime) + " ns");
    }
}
