import java.util.PriorityQueue;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Collections;

class Edge {
    int vertex1, vertex2, weight;

    public Edge(int vertex1, int vertex2, int weight) {
        this.vertex1 = vertex1;
        this.vertex2 = vertex2;
        this.weight = weight;
    }
}

class Graph {
    int vertices;
    ArrayList<Edge>[] adjacencyList;

    public Graph(int vertices) {
        this.vertices = vertices;
        adjacencyList = new ArrayList[vertices];
        for (int i = 0; i < vertices; i++) {
            adjacencyList[i] = new ArrayList<>();
        }
    }

    public void addEdge(int vertex1, int vertex2, int weight) {
        adjacencyList[vertex1].add(new Edge(vertex1, vertex2, weight));
        adjacencyList[vertex2].add(new Edge(vertex2, vertex1, weight)); // 무방향 그래프
    }

    public void primMST() {
        boolean[] visited = new boolean[vertices];
        PriorityQueue<Edge> priorityQueue = new PriorityQueue<>(Comparator.comparingInt((Edge e) -> e.weight)
                .thenComparingInt(e -> e.vertex1)
                .thenComparingInt(e -> e.vertex2));
    
        // 2번 정점에서 시작 (노드 'c')
        visited[2] = true;
        // 시작 노드에 연결된 간선들을 정렬하여 큐에 추가
        ArrayList<Edge> sortedEdges = new ArrayList<>(adjacencyList[2]);
        Collections.sort(sortedEdges, Comparator.comparingInt((Edge e) -> e.weight)
                .thenComparingInt(e -> e.vertex1)
                .thenComparingInt(e -> e.vertex2));
        priorityQueue.addAll(sortedEdges);
    
        ArrayList<Edge> mstEdges = new ArrayList<>();
        int mstWeight = 0;
    
        while (!priorityQueue.isEmpty()) {
            Edge edge = priorityQueue.poll();
    
            // 두 정점 모두 이미 방문한 경우 건너뜀
            if (visited[edge.vertex1] && visited[edge.vertex2]) continue;
    
            mstEdges.add(edge);
            mstWeight += edge.weight;
    
            // 방문하지 않은 정점 찾기
            int newVertex = visited[edge.vertex1] ? edge.vertex2 : edge.vertex1;
            visited[newVertex] = true;
    
            // 정점에 연결된 간선들을 정렬하여 큐에 추가
            sortedEdges = new ArrayList<>(adjacencyList[newVertex]);
            Collections.sort(sortedEdges, Comparator.comparingInt((Edge e) -> e.weight)
                    .thenComparingInt(e -> e.vertex1)
                    .thenComparingInt(e -> e.vertex2));
            for (Edge e : sortedEdges) {
                if (!visited[e.vertex2]) {
                    priorityQueue.add(e);
                }
            }
        }
    
        // MST 간선 출력
        System.out.println("Minimum Spanning Tree:");
        for (Edge edge : mstEdges) {
            System.out.println("(" + edge.vertex1 + ", " + edge.vertex2 + ", " + edge.weight + ")");
        }
        System.out.println("Total Weight of MST: " + mstWeight);
    }
}   

public class Prim {
    public static void main(String[] args) {
        long startTime = System.nanoTime();

        Graph graph = new Graph(6);

        // 입력 이미지에 따라 간선 추가
        graph.addEdge(0, 1, 3);  // a-b
        graph.addEdge(0, 3, 2);  // a-d
        graph.addEdge(0, 4, 4);  // a-e
        graph.addEdge(1, 2, 1);  // b-c
        graph.addEdge(1, 3, 4);  // b-d
        graph.addEdge(2, 5, 1);  // c-f
        graph.addEdge(3, 4, 5);  // d-e
        graph.addEdge(3, 5, 7);  // d-f
        graph.addEdge(4, 5, 9);  // e-f
        graph.addEdge(1, 5, 2);  // b-f (그래프의 추가 간선)

        graph.primMST();

        long endTime = System.nanoTime();
        System.out.println("Running time: " + (endTime - startTime) + " nanoseconds");
    }
}
