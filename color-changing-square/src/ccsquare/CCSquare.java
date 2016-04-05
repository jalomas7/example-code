/** Created on: April 5, 2016
	Author: Jacob Massengill
	Synopsis: color-changing-square
				a color changing square, click within it to change the main color
*/
package ccsquare;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JPanel;

public class CCSquare extends JPanel implements CCShape {
	CCSquareModel model;
	
	//all possible colors
	final Color[] colors = {Color.BLACK, Color.BLUE, Color.CYAN, Color.DARK_GRAY,
						  Color.GRAY, Color.GREEN, Color.LIGHT_GRAY, Color.MAGENTA,
						  Color.ORANGE, Color.PINK, Color.RED,Color.WHITE, Color.YELLOW};
	
	//side length of square
	final int size = 200;
	
	public CCSquare(CCSquareModel model){
		this.model = model;
		model.addShape(this);
		
		this.addMouseListener(new MouseAdapter(){
			public void mousePressed(MouseEvent e){
				changeColor(e);
			}
		});
		
		this.setPreferredSize(new Dimension(size*2,size));
	}
	
	//if clicked within the bounding box of the square, changed to a random color
	public void changeColor(MouseEvent e){
		if(e.getX() < this.getWidth()/2+size/2 && e.getX() > this.getWidth()/2 - size/2 &&
			e.getY() < this.getHeight()/2+size/2 && e.getY() > this.getHeight()/2 - size/2){
			model.update(colors[(int)(Math.random()*colors.length)]);
		}
	}
	
	//change the color to reflect the model
	public void update(Color oldColor){
		if(oldColor != model.getColor()){
			repaint(this.getWidth()/2 - size/2, this.getHeight()/2 - size/2, size, size);
		}
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		
		g.setColor(model.getColor());
		g.fillRect(this.getWidth()/2- size/2, this.getHeight()/2 -size/2, size, size);
	}
}
