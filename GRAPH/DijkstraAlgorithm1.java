import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class DijkstraAlgorithm1 {

    // Method to perform Dijkstra's algorithm
    public static int[] dijkstra(int v, List<List<Pair>> adj, int s) {


        // Custom priority queue implemented using a min-heap
        MinHeap minHeap = new MinHeap(v);

        // Array to store the shortest distances from source
        int[] dist = new int[v];
        for (int i = 0; i < v; i++) {
            dist[i] = Integer.MAX_VALUE;
        }

        dist[s] = 0;
        minHeap.insert(new Pair(s, 0)); // Push the source node with distance 0

        while (!minHeap.isEmpty()) {
            Pair current = minHeap.extractMin();
            int node = current.vertex;
            int dis = current.weight;

            // Skip if this distance is greater than the already found shortest distance
            if (dis > dist[node])
                continue;

            for (Pair neighbor : adj.get(node)) {
                int adjNode = neighbor.vertex;
                int edgeWeight = neighbor.weight;

                // If a shorter path to adjNode is found
                if (dis + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = dis + edgeWeight;
                    minHeap.insert(new Pair(adjNode, dist[adjNode]));
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

    // Custom min-heap implementation
    static class MinHeap {
        private ArrayList<Pair> heap;
        private int size;

        public MinHeap(int initialCapacity) {
            this.heap = new ArrayList<>(initialCapacity);
            this.size = 0;
        }

        public boolean isEmpty() {
            return size == 0;
        }

        public void insert(Pair pair) {
            heap.add(pair); // Add the new element
            size++;
            heapifyUp(size - 1); // Maintain heap property
        }

        public Pair extractMin() {
            if (size == 0) {
                return null;
            }
            Pair min = heap.get(0);
            Pair last = heap.get(size - 1);
            heap.set(0, last); // Move the last element to the root
            heap.remove(size - 1); // Remove the last element
            size--;
            heapifyDown(0); // Maintain heap property
            return min;
        }

        private void heapifyUp(int index) {
            while (index > 0) {
                int parentIndex = (index - 1) / 2;
                if (heap.get(parentIndex).weight > heap.get(index).weight) {
                    swap(parentIndex, index);
                    index = parentIndex;
                } else {
                    break;
                }
            }
        }

        private void heapifyDown(int index) {
            while (index < size / 2) { // Check if there are children
                int leftChild = 2 * index + 1;
                int rightChild = 2 * index + 2;
                int smallerChild = leftChild;

                if (rightChild < size && heap.get(rightChild).weight < heap.get(leftChild).weight) {
                    smallerChild = rightChild;
                }

                if (heap.get(index).weight > heap.get(smallerChild).weight) {
                    swap(index, smallerChild);
                    index = smallerChild;
                } else {
                    break;
                }
            }
        }

        private void swap(int i, int j) {
            Pair temp = heap.get(i);
            heap.set(i, heap.get(j));
            heap.set(j, temp);
        }
    }
}
