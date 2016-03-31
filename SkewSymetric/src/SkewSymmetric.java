import java.util.Scanner;

public class SkewSymmetric {
	
	private int nRows = 0;
	
	//print out how many entries in a matrix
	//need to change in order for it to be
	//skew symmetric. 
	public SkewSymmetric(String[] args){
		if(args.length < 2){
			System.err.println("Must be an NxN matrix");
			return;
		}
		
		this.nRows = args.length;
		
		if(this.nRows != args.length){
			System.err.println("Must be an NxN matrix");
			return;
		}
		
		int[][] matrix = getMatrix(args);
		
		printMatrix(matrix);
		System.out.printf("minimum changes needed = %d%n" , minChanges(matrix));
		
	}
	
	//returns the minimum number of changes necessary to make this matrix
	//skew symmetric
	public int minChanges(int[][] matrix){
		int changes = 0;
		
		for(int i = 0; i < this.nRows; i++){
			for(int j = i; j < this.nRows; j++){
				changes += shouldChange(matrix, i, j);
			}
		}
		
		return changes;
	}
	
	//returns a matrix from args
	public int[][] getMatrix(String[] args){
		int[][] matrix = new int[this.nRows][this.nRows];
		
		for(int i=0; i < this.nRows; i++){
			matrix[i] = getRow(args[i]);
		}
		return matrix;
	}
	
	//prints a matrix
	public void printMatrix(int[][] matrix){
		for(int[] row: matrix){
			for(int n : row){
				System.out.printf("%4d", n);
			}
			System.out.println("");
		}
	}
	
	//gets a single row of a matrix from arg
	private int[] getRow(String arg){
		Scanner line = new Scanner(arg);
		int[] row = new int[this.nRows];
		for(int i = 0; i < this.nRows; i++){
			row[i] = line.nextInt();
		}line.close();
		
		return row;
	}
	
	//returns 1 if the entry should change, 0 otherwise.
	private int shouldChange(int[][] matrix, int i, int j){
		if(i == j){
			if(matrix[i][j] == 0) return 0;
			else return 1;
		}else{
			if(matrix[i][j] == (-1)*matrix[j][i]) return 0;
			else return 1;
		}
	}
	
	public static void main(String[] args) {
		new SkewSymmetric(args);
	}

}