import java.util.*;

class WordCount {
	public WordCount() {
		List<String> words = new ArrayList<String>();
		Scanner console = new Scanner(System.in);

		while (console.hasNextLine()) {
			String line = console.nextLine();
			Scanner tokenizer = new Scanner(line);
			while (tokenizer.hasNext()) {
				String word = tokenizer.next();
				words.add(word);
			}
			tokenizer.close();
		}
		console.close();
		countWordFrequencies(words);
	}

	void countWordFrequencies(List<String> words) {	
		Map<String, Integer> counter = new HashMap<>();
		
		for(String word : words){
			Integer i;
			if((i = counter.get(word))!=null){
				counter.put(word, i+1);
			}else{
				counter.put(word, 1);
			}
		}
	
		Map<String, Integer> sortedCounter = new TreeMap<>(counter);
		counter = null;
		
		for(Map.Entry<String, Integer> e : sortedCounter.entrySet()){
			System.out.printf("%-20s :%5d%n", e.getKey(), e.getValue().intValue());
		}
	}

	public static void main(String args[]) {
		new WordCount();
	}
}
