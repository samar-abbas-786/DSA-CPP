import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class GraphTraversalApp extends JFrame {
    public int vertexCounter = 0;
    private final int VERTEX_RADIUS = 40;
    private ArrayList<Vertex> vertexList = new ArrayList<>();
    private ArrayList<Connection> connectionList = new ArrayList<>();
    private Vertex activeVertex = null;
    private JTextArea outputTextArea;

    public GraphTraversalApp() {
        setTitle("Graph BFS Visualization Tool");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Panel for graph drawing
        GraphCanvas drawingCanvas = new GraphCanvas();
        add(drawingCanvas, BorderLayout.CENTER);

        // Control panel with buttons
        JPanel controlBar = new JPanel();
        JButton btnAddVertex = new JButton("Create Vertex");
        JButton btnAddConnection = new JButton("Create Connection");
        JButton btnRemoveVertex = new JButton("Delete Vertex");
        JButton btnStartBFS = new JButton("Initiate BFS");
        JButton btnReset = new JButton("Clear Graph");

        controlBar.add(btnAddVertex);
        controlBar.add(btnAddConnection);
        controlBar.add(btnRemoveVertex);
        controlBar.add(btnStartBFS);
        controlBar.add(btnReset);
        add(controlBar, BorderLayout.NORTH);

        // Text area for displaying BFS results
        outputTextArea = new JTextArea(3, 40);
        outputTextArea.setEditable(false);
        add(new JScrollPane(outputTextArea), BorderLayout.SOUTH);

        // Button event handling
        btnAddVertex.addActionListener(e -> drawingCanvas.addVertex());
        btnAddConnection.addActionListener(e -> drawingCanvas.createConnection());
        btnRemoveVertex.addActionListener(e -> drawingCanvas.removeVertex());
        btnStartBFS.addActionListener(e -> {
            if (vertexList.size() > 0) {
                String startingPoint = JOptionPane.showInputDialog("Enter the starting vertex (index 0 to " + (vertexList.size() - 1) + "):");
                try {
                    int startingIndex = Integer.parseInt(startingPoint);

                    // Ensure valid index
                    if (startingIndex >= 0 && startingIndex < vertexList.size()) {
                        outputTextArea.setText(""); // Clear previous results
                        new Thread(() -> executeBFS(startingIndex)).start();
                    } else {
                        JOptionPane.showMessageDialog(this, "Invalid index. Please enter a valid number.");
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(this, "Please enter a numeric value.");
                }
            } else {
                JOptionPane.showMessageDialog(this, "No vertices available. Please add vertices before starting BFS.");
            }
        });
        btnReset.addActionListener(e -> resetGraph(drawingCanvas));
    }

    // BFS execution with animation and output
    private void executeBFS(int startingIndex) {
        boolean[] isVisited = new boolean[vertexList.size()];
        breadthFirstSearch(startingIndex, isVisited);
    }

    private void breadthFirstSearch(int startingIndex, boolean[] isVisited) {
        Queue<Integer> traversalQueue = new LinkedList<>();
        traversalQueue.add(startingIndex);
        isVisited[startingIndex] = true;

        while (!traversalQueue.isEmpty()) {
            int currentIndex = traversalQueue.poll();
            Vertex currentVertex = vertexList.get(currentIndex);

            // Update output area
            SwingUtilities.invokeLater(() -> outputTextArea.append(currentVertex.getLabel() + " "));

            // Visualize visit
            currentVertex.setVisited(true);
            repaint();
            try {
                Thread.sleep(1000); // Animation delay
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // Traverse neighbors
            for (Connection connection : connectionList) {
                Vertex neighborVertex = null;
                if (connection.getSource() == currentVertex && !isVisited[vertexList.indexOf(connection.getDestination())]) {
                    neighborVertex = connection.getDestination();
                } else if (connection.getDestination() == currentVertex && !isVisited[vertexList.indexOf(connection.getSource())]) {
                    neighborVertex = connection.getSource();
                }
                if (neighborVertex != null) {
                    int neighborIndex = vertexList.indexOf(neighborVertex);
                    if (!isVisited[neighborIndex]) {
                        traversalQueue.add(neighborIndex);
                        isVisited[neighborIndex] = true;
                    }
                }
            }
        }

        // Reset visual state
        for (Vertex vertex : vertexList) {
            vertex.setVisited(false);
        }
        repaint();
    }

    // Resets the entire graph
    private void resetGraph(GraphCanvas canvas) {
        vertexList.clear();
        connectionList.clear();
        activeVertex = null;
        outputTextArea.setText("");
        canvas.repaint();
        vertexCounter = 0;
    }

    // Panel to draw vertices and connections
    class GraphCanvas extends JPanel {

        public GraphCanvas() {
            addMouseListener(new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent e) {
                    handleMousePress(e.getX(), e.getY());
                }
            });
        }

        public void addVertex() {
            JOptionPane.showMessageDialog(null, "Click on the canvas to create a new vertex.");
        }

        public void createConnection() {
            if (activeVertex != null) {
                JOptionPane.showMessageDialog(null, "Click on another vertex to create a connection.");
            } else {
                JOptionPane.showMessageDialog(null, "Select a vertex first to create a connection.");
            }
        }

        public void removeVertex() {
            if (activeVertex != null) {
                vertexList.remove(activeVertex);
                connectionList.removeIf(connection -> connection.getSource() == activeVertex || connection.getDestination() == activeVertex);
                activeVertex = null;
                repaint();
            } else {
                JOptionPane.showMessageDialog(null, "Select a vertex to delete.");
            }
        }

        private void handleMousePress(int x, int y) {
            for (Vertex vertex : vertexList) {
                if (vertex.contains(x, y)) {
                    if (activeVertex == null) {
                        activeVertex = vertex;
                        vertex.setSelected(true);
                    } else {
                        if (activeVertex != vertex) {
                            connectionList.add(new Connection(activeVertex, vertex));
                        }
                        activeVertex.setSelected(false);
                        activeVertex = null;
                    }
                    repaint();
                    return;
                }
            }
            vertexList.add(new Vertex(x, y, "V" + vertexCounter++));
            repaint();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);

            // Draw connections
            g.setColor(Color.BLACK);
            for (Connection connection : connectionList) {
                Vertex source = connection.getSource();
                Vertex destination = connection.getDestination();
                g.drawLine(source.getX(), source.getY(), destination.getX(), destination.getY());
            }

            // Draw vertices
            for (Vertex vertex : vertexList) {
                if (vertex.isVisited()) {
                    g.setColor(Color.GREEN);
                } else if (vertex.isSelected()) {
                    g.setColor(Color.BLUE);
                } else {
                    g.setColor(Color.RED);
                }
                g.fillOval(vertex.getX() - VERTEX_RADIUS / 2, vertex.getY() - VERTEX_RADIUS / 2, VERTEX_RADIUS, VERTEX_RADIUS);
                g.setColor(Color.BLACK);
                g.drawString(vertex.getLabel(), vertex.getX() - VERTEX_RADIUS / 2, vertex.getY() - VERTEX_RADIUS / 2 - 10);
            }
        }
    }

    // Vertex class representing graph nodes
    class Vertex {
        private int xPos, yPos;
        private String label;
        private boolean visited;
        private boolean selected;

        public Vertex(int x, int y, String label) {
            this.xPos = x;
            this.yPos = y;
            this.label = label;
            this.visited = false;
            this.selected = false;
        }

        public int getX() {
            return xPos;
        }

        public int getY() {
            return yPos;
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
            int radius = VERTEX_RADIUS / 2;
            return x >= xPos - radius && x <= xPos + radius && y >= yPos - radius && y <= yPos + radius;
        }
    }

    // Connection class representing edges
    class Connection {
        private Vertex source, destination;

        public Connection(Vertex source, Vertex destination) {
            this.source = source;
            this.destination = destination;
        }

        public Vertex getSource() {
            return source;
        }

        public Vertex getDestination() {
            return destination;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            GraphTraversalApp app = new GraphTraversalApp();
            app.setVisible(true);
        });
    }
}
