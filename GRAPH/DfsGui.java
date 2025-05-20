import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class DfsGui extends JFrame {
    private static final int NODE_RADIUS = 20;
    private static final Color NODE_COLOR = Color.RED;
    private static final Color EDGE_COLOR = Color.BLACK;
    private static final Color VISITED_COLOR = Color.GREEN;
    
    private final JPanel canvas;
    private final JButton startButton;
    
    private final ArrayList<Point> nodes = new ArrayList<>();
    private final ArrayList<int[]> edges = new ArrayList<>();
    
    private Point startNode = null;
    private Point endNode = null;
    
    public DfsGui() {
        setTitle("Graph Visualizer");
        setSize(800, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        
        canvas = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                drawGraph(g);
            }
        };
        canvas.setBackground(Color.WHITE);
        canvas.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                handleMouseClick(e.getPoint());
            }
        });
        
        startButton = new JButton("Start DFS");
        startButton.addActionListener(e -> startDFS());
        
        add(canvas, BorderLayout.CENTER);
        add(startButton, BorderLayout.SOUTH);
    }
    
    private void drawGraph(Graphics g) {
        // Draw edges
        g.setColor(EDGE_COLOR);
        for (int[] edge : edges) {
            Point p1 = nodes.get(edge[0]);
            Point p2 = nodes.get(edge[1]);
            g.drawLine(p1.x, p1.y, p2.x, p2.y);
        }
        
        // Draw nodes
        g.setColor(NODE_COLOR);
        for (Point node : nodes) {
            g.fillOval(node.x - NODE_RADIUS, node.y - NODE_RADIUS, NODE_RADIUS * 2, NODE_RADIUS * 2);
        }
        
        // Draw visited nodes
        if (visitedNode != null) {
            g.setColor(VISITED_COLOR);
            g.fillOval(visitedNode.x - NODE_RADIUS, visitedNode.y - NODE_RADIUS, NODE_RADIUS * 2, NODE_RADIUS * 2);
        }
    }
    
    private void handleMouseClick(Point point) {
        for (Point node : nodes) {
            if (node.distance(point) < NODE_RADIUS) {
                if (startNode == null) {
                    startNode = node;
                } else if (endNode == null) {
                    endNode = node;
                    edges.add(new int[]{nodes.indexOf(startNode), nodes.indexOf(endNode)});
                    startNode = null;
                    endNode = null;
                    canvas.repaint();
                }
                return;
            }
        }
        
        nodes.add(point);
        canvas.repaint();
    }
    
    private Point visitedNode = null;
    
    private void startDFS() {
        if (nodes.isEmpty()) return;
        
        new Thread(() -> {
            Stack<Point> stack = new Stack<>();
            boolean[] visited = new boolean[nodes.size()];
            Point start = nodes.get(0);
            stack.push(start);
            visited[nodes.indexOf(start)] = true;
            
            while (!stack.isEmpty()) {
                Point current = stack.pop();
                visitedNode = current;
                canvas.repaint();
                
                try {
                    Thread.sleep(500); // Delay for visualization
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                
                for (int[] edge : edges) {
                    Point neighbor = null;
                    if (nodes.get(edge[0]).equals(current)) {
                        neighbor = nodes.get(edge[1]);
                    } else if (nodes.get(edge[1]).equals(current)) {
                        neighbor = nodes.get(edge[0]);
                    }
                    if (neighbor != null && !visited[nodes.indexOf(neighbor)]) {
                        visited[nodes.indexOf(neighbor)] = true;
                        stack.push(neighbor);
                    }
                }
            }
            visitedNode = null;
            canvas.repaint();
        }).start();
    }
    
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            DfsGui frame = new DfsGui();
            frame.setVisible(true);
        });
    }
}

