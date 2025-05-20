import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Main_bfs extends JFrame {
    public int nodeCounter = 0;
    private final int NODE_SIZE = 40;
    private ArrayList<Node> nodes = new ArrayList<>();
    private ArrayList<Edge> edges = new ArrayList<>();
    private Node selectedNode = null;
    private JTextArea resultArea;

    public Main_bfs() {
        setTitle("DFS and BFS Graph Traversal Visualization");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Canvas panel for drawing
        GraphPanel graphPanel = new GraphPanel();
        add(graphPanel, BorderLayout.CENTER);

        // Control panel with buttons
        JPanel controlPanel = new JPanel();
        JButton addNodeBtn = new JButton("Add Node");
        JButton addEdgeBtn = new JButton("Add Edge");
        JButton deleteNodeBtn = new JButton("Delete Node");
        // JButton startDfsBtn = new JButton("Start DFS");
        JButton startBfsBtn = new JButton("Start BFS");
        JButton resetBtn = new JButton("Reset");

        controlPanel.add(addNodeBtn);
        controlPanel.add(addEdgeBtn);
        controlPanel.add(deleteNodeBtn);
        // controlPanel.add(startDfsBtn);
        controlPanel.add(startBfsBtn); // Add BFS Button
        controlPanel.add(resetBtn);
        add(controlPanel, BorderLayout.NORTH);

        // Result area to display traversal order
        resultArea = new JTextArea(3, 40);
        resultArea.setEditable(false);
        add(new JScrollPane(resultArea), BorderLayout.SOUTH);

        // Action listeners for buttons
        addNodeBtn.addActionListener(e -> graphPanel.addNode());
        addEdgeBtn.addActionListener(e -> graphPanel.addEdge());
        deleteNodeBtn.addActionListener(e -> graphPanel.deleteNode());
        // startDfsBtn.addActionListener(e -> {
        // if (nodes.size() > 0) {
        // resultArea.setText(""); // Clear previous results
        // new Thread(() -> startDFS(0)).start();
        // }
        // });
        startBfsBtn.addActionListener(e -> {
            if (nodes.size() > 0) {
                String input = JOptionPane
                        .showInputDialog("Enter the starting vertex (index between 0 and " + (nodes.size() - 1) + "):");
                try {
                    int startIndex = Integer.parseInt(input);

                    // Check if the index is within the valid range
                    if (startIndex >= 0 && startIndex < nodes.size()) {
                        resultArea.setText(""); // Clear previous results
                        new Thread(() -> startBFS(startIndex)).start();
                    } else {
                        JOptionPane.showMessageDialog(this,
                                "Please enter a valid index between 0 and " + (nodes.size() - 1) + ".");
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(this, "Please enter a valid number.");
                }
            } else {
                JOptionPane.showMessageDialog(this, "Please add at least one node before starting BFS.");
            }
        });
        resetBtn.addActionListener(e -> resetGraph(graphPanel)); // Action for Reset Button
    }

    

    // Start BFS animation from node index
    private void startBFS(int startIndex) {
        boolean[] visited = new boolean[nodes.size()];
        bfs(startIndex, visited);
    }

    // BFS iterative function with animation and result display
    private void bfs(int startIndex, boolean[] visited) {
        Queue<Integer> queue = new LinkedList<>();
        queue.add(startIndex);
        visited[startIndex] = true;

        while (!queue.isEmpty()) {
            int nodeIndex = queue.poll();
            Node node = nodes.get(nodeIndex);

            // Append to result area
            SwingUtilities.invokeLater(() -> resultArea.append(node.getLabel() + " "));

            // Animate visit
            node.setVisited(true);
            repaint();
            try {
                Thread.sleep(1000); // Pause for animation
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // Enqueue all connected nodes that haven't been visited
            for (Edge edge : edges) {
                Node neighbor = null;
                if (edge.getFromNode() == node && !visited[nodes.indexOf(edge.getToNode())]) {
                    neighbor = edge.getToNode();
                } else if (edge.getToNode() == node && !visited[nodes.indexOf(edge.getFromNode())]) {
                    neighbor = edge.getFromNode();
                }
                if (neighbor != null) {
                    int neighborIndex = nodes.indexOf(neighbor);
                    if (!visited[neighborIndex]) {
                        queue.add(neighborIndex);
                        visited[neighborIndex] = true;
                    }
                }
            }

        }
        for (Node node : nodes) {
            node.setVisited(false);
        }
        repaint();
    }

    // Reset the graph by clearing nodes, edges, and the result area
    private void resetGraph(GraphPanel graphPanel) {
        nodes.clear();
        edges.clear();
        selectedNode = null;
        resultArea.setText(""); // Clear result area
        graphPanel.repaint(); // Refresh the canvas
        nodeCounter = 0;
    }

    // Panel to handle node and edge creation
    class GraphPanel extends JPanel {

        public GraphPanel() {
            addMouseListener(new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent e) {
                    // Select or add new node on click
                    selectOrAddNode(e.getX(), e.getY());
                }
            });
        }

        // Function to add nodes
        public void addNode() {
            JOptionPane.showMessageDialog(null, "Click anywhere on the panel to add a node.");
        }

        // Function to add edges based on selected nodes
        public void addEdge() {
            if (selectedNode != null) {
                JOptionPane.showMessageDialog(null, "Select another node to connect an edge.");
            }
        }

        // Function to delete selected node and its edges
        public void deleteNode() {
            if (selectedNode != null) {
                nodes.remove(selectedNode);
                // Remove edges associated with the deleted node
                edges.removeIf(edge -> edge.getFromNode() == selectedNode || edge.getToNode() == selectedNode);
                selectedNode = null;
                repaint();
            } else {
                JOptionPane.showMessageDialog(null, "Select a node to delete.");
            }
        }

        private void selectOrAddNode(int x, int y) {
            for (Node node : nodes) {
                if (node.contains(x, y)) {
                    if (selectedNode == null) {
                        selectedNode = node;
                        node.setSelected(true);
                    } else {
                        if (selectedNode != node) {
                            // Create an edge between two selected nodes
                            edges.add(new Edge(selectedNode, node));
                        }
                        selectedNode.setSelected(false);
                        selectedNode = null;
                    }
                    repaint();
                    return;
                }
            }
            // If no node selected, create a new node
            nodes.add(new Node(x, y, "N" + nodeCounter++));
            repaint();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);

            // Draw edges
            g.setColor(Color.BLACK);
            for (Edge edge : edges) {
                Node fromNode = edge.getFromNode();
                Node toNode = edge.getToNode();
                g.drawLine(fromNode.getX(), fromNode.getY(), toNode.getX(), toNode.getY());
            }

            // Draw nodes
            for (Node node : nodes) {
                if (node.isVisited()) {
                    g.setColor(Color.GREEN);
                } else if (node.isSelected()) {
                    g.setColor(Color.BLUE);
                } else {
                    g.setColor(Color.RED);
                }
                g.fillOval(node.getX() - NODE_SIZE / 2, node.getY() - NODE_SIZE / 2, NODE_SIZE, NODE_SIZE);
                g.setColor(Color.BLACK);
                g.drawString(node.getLabel(), node.getX() - NODE_SIZE / 2, node.getY() - NODE_SIZE / 2 - 10);
            }
        }
    }

    // Node class to represent graph nodes
    class Node {
        private int x, y;
        private String label;
        private boolean visited;
        private boolean selected;

        public Node(int x, int y, String label) {
            this.x = x;
            this.y = y;
            this.label = label;
            this.visited = false;
            this.selected = false;
        }

        public int getX() {
            return x;
        }

        public int getY() {
            return y;
        }

        public String getLabel() {
            return label;
        }

        public boolean isVisited() {
            return visited;
        }

        public void setVisited(boolean visited) {
            this.visited = visited;
        }

        public boolean isSelected() {
            return selected;
        }

        public void setSelected(boolean selected) {
            this.selected = selected;
        }

        public boolean contains(int x, int y) {
            return Math.sqrt(Math.pow(x - this.x, 2) + Math.pow(y - this.y, 2)) <= NODE_SIZE / 2;
        }
    }

    // Edge class to represent graph edges
    class Edge {
        private Node fromNode, toNode;

        public Edge(Node fromNode, Node toNode) {
            this.fromNode = fromNode;
            this.toNode = toNode;
        }

        public Node getFromNode() {
            return fromNode;
        }

        public Node getToNode() {
            return toNode;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Main_bfs).setVisible(true));
    }
}
