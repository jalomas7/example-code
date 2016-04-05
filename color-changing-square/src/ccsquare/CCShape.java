/** Created on: April 5, 2016
	Author: Jacob Massengill
	Synopsis: color-changing-square
				interface for defining color changing shapes.
				probably should have a changeColor method as well,
				but for this demo this should be fine.
*/
package ccsquare;
import java.awt.Color;

public interface CCShape {
	public void update(Color oldColor);
}
