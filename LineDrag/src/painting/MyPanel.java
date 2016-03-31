package painting;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class MyPanel extends JPanel {
	
	int top=0, left=0;
	final int stillOffset = 20;
	final int moveOffset = 30;
	
    public MyPanel() {
        setBorder(BorderFactory.createLineBorder(Color.black));
        
        this.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                moveLine(e.getX(),e.getY(), stillOffset);
            }
        });

        this.addMouseMotionListener(new MouseAdapter() {
            public void mouseDragged(MouseEvent e) {
                moveLine(e.getX(),e.getY(), moveOffset);
            }
        });
    }

    public Dimension getPreferredSize() {
        return new Dimension(250,200);
    }

    private void moveLine(int x, int y, int offset) {
    	if((x < left+offset && x > left-offset) && (y < top+offset && y > top-offset)){
    		left = x; top = y;
    		repaint();
    	}
    }
    
    public void paintComponent(Graphics g) {
        super.paintComponent(g);       
        
        // Draw line
        g.drawLine(left, top, this.getWidth()/2, this.getHeight()/2);
    }
    
   
}