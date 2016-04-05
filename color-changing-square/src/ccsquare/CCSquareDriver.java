/** Created on: April 5, 2016
Author: Jacob Massengill
Synopsis: color-changing-square
			driver code, creates a model and two squares, displays them to the user.
*/
package ccsquare;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

import javax.swing.JFrame;

public class CCSquareDriver extends JFrame {

	public CCSquareDriver(){
		CCSquareModel model = new CCSquareModel(Color.RED);
		CCSquare square = new CCSquare(model);
		CCSquare square2 = new CCSquare(model);
		
		this.add(square, BorderLayout.CENTER);
		this.add(square2, BorderLayout.SOUTH);
		
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setPreferredSize(new Dimension(600, 800));
	}
	
	public static void createAndShowGUI(){
		CCSquareDriver driver = new CCSquareDriver();
		driver.pack();
		driver.setVisible(true);
	}
	
	public static void main(String[] args) {
		javax.swing.SwingUtilities.invokeLater(new Runnable(){

			public void run() {
				createAndShowGUI();
			}
		
		});
	}

}
