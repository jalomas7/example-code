/** Created on: April 5, 2016
	Author: Jacob Massengill
	Synopsis: color-changing-square
			  Model for use in this application. keeps track of what color to use
*/
package ccsquare;

import java.awt.Color;
import java.util.ArrayList;

public class CCSquareModel {
	Color color;
	private ArrayList<CCShape> shapes = new ArrayList<>();
	
	public CCSquareModel(Color color){
		this.color = color;
	}
	
	public final void update(Color color){
		Color oldColor = this.color;
		this.color = color;
		for(CCShape c : shapes){
			c.update(oldColor);
		}
	}
	
	public final void addShape(CCShape shape){
		shapes.add(shape);
	}
	
	public final Color getColor(){
		return color;
	}
}
