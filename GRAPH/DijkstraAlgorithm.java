import java.util.*;

public class DijkstraAlgorithm {

    // Method to perform Dijkstra's algorithm
    public static int[] dijkstra(int v, List<List<Pair>> adj, int s) {
        // Priority queue to store the vertices to be processed
        PriorityQueue<Pair> pq = new PriorityQueue<>(Comparator.comparingInt(pair -> pair.weight));
        // Array to store the shortest distances from source
        int[] dist = new int[v];
        Arrays.fill(dist, Integer.MAX_VALUE);

        dist[s] = 0;
        pq.offer(new Pair(s, 0)); // Push the source node with distance 0

        while (!pq.isEmpty()) {
            Pair current = pq.poll();
            int node = current.vertex;
            int dis = current.weight;

            // Skip if this distance is greater than the already found shortest distance
            if (dis > dist[node]) continue;

            for (Pair neighbor : adj.get(node)) {
                int adjNode = neighbor.vertex;
                int edgeWeight = neighbor.weight;

                // If a shorter path to adjNode is found
                if (dis + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = dis + edgeWeight;
                    pq.offer(new Pair(adjNode, dist[adjNode]));
                }
            }
        }
        return dist;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of vertices: ");
        int v = scanner.nextInt();
        System.out.print("Enter the number of edges: ");
        int m = scanner.nextInt();

        // Adjacency list to represent the graph
        List<List<Pair>> adj = new ArrayList<>(v);
        for (int i = 0; i < v; i++) {
            adj.add(new ArrayList<>());
        }

        System.out.println("Enter each edge in the format 'u v w' where u and v are vertices and w is the weight:");
        for (int i = 0; i < m; i++) {
            int u = scanner.nextInt();
            int v2 = scanner.nextInt();
            int w = scanner.nextInt();
            adj.get(u).add(new Pair(v2, w));
            adj.get(v2).add(new Pair(u, w)); // For undirected graph, add edge in both directions
        }

        System.out.print("Enter the Source Node (0 to " + (v - 1) + "): ");
        int s = scanner.nextInt();

        // Input validation
        if (s < 0 || s >= v) {
            System.out.println("Invalid source node. Exiting.");
            return;
        }

        int[] distances = dijkstra(v, adj, s);

        System.out.println("Distances from source " + s + ":");
        for (int i = 0; i < v; i++) {
            if (distances[i] == Integer.MAX_VALUE) {
                System.out.println("Vertex " + i + ": INF");
            } else {
                System.out.println("Vertex " + i + ": " + distances[i]);
            }
        }

        scanner.close();
    }

    // Helper class to store the vertex and its corresponding weight
    static class Pair {
        int vertex;
        int weight;

        Pair(int vertex, int weight) {
            this.vertex = vertex;
            this.weight = weight;
        }
    }
}
