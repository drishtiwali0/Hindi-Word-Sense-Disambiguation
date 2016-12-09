/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author drishti
 */
import java.util.LinkedList;
import java.io.Serializable;
import java.util.List;
import in.ac.iitb.cfilt.jhwnl.JHWNL;
import in.ac.iitb.cfilt.jhwnl.JHWNLException;
import in.ac.iitb.cfilt.jhwnl.data.IndexWord;
import in.ac.iitb.cfilt.jhwnl.data.IndexWordSet;
import in.ac.iitb.cfilt.jhwnl.data.POS;
import static in.ac.iitb.cfilt.jhwnl.data.POS.NOUN;
import static in.ac.iitb.cfilt.jhwnl.data.POS.VERB;
import in.ac.iitb.cfilt.jhwnl.data.Pointer;
import in.ac.iitb.cfilt.jhwnl.data.PointerType;
import in.ac.iitb.cfilt.jhwnl.data.Word;
import in.ac.iitb.cfilt.jhwnl.data.Synset;
import in.ac.iitb.cfilt.jhwnl.dictionary.Dictionary;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.util.HashSet;
import static sun.org.mozilla.javascript.Context.exit;
public class lesk {
    static int simple_lesk(String sentence,String word) throws JHWNLException, IOException, Exception{
        JHWNL.initialize();
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter ( new FileOutputStream("output.txt"), "UTF-8"));
        sentence=sentence.replaceAll(word, "");
        String[] context = sentence.split(" ");
        System.out.println(word);
        Dictionary dictionary = Dictionary.getInstance();
        IndexWordSet disWDSet = dictionary.lookupAllMorphedIndexWords(word);
        List<String> contextWDArray=new LinkedList<String>();
        int contextSize = context.length;
        for(int i=0;i<contextSize;i++){
            IndexWordSet sentWDSet = dictionary.lookupAllMorphedIndexWords(context[i]);
            IndexWord[] sentWDArray = sentWDSet.getIndexWordArray();
            for(int j=0;j<sentWDArray.length;j++){
                int size=sentWDArray[j].getSenseCount();
                Synset[] sentSSArray = sentWDArray[j].getSenses();
                for(int k=0;k<size;k++){
                    if(sentSSArray[k].getWords()==null){
                        continue;
                    }
                    int tmpSize=sentSSArray[k].getWords().length;
                    Word[] tmp=new Word[tmpSize];
                    tmp=sentSSArray[k].getWords();
                    for(int h=0;h<tmpSize;h++){
                        contextWDArray.add(tmp[h].getLemma());    
                    }
                    
                }
            }
        }
        //int senSize=disWDSet.getSenseCount(POS.NOUN);
        int max_overlap=0;
        int sense=0;
        POS disPOS=new POS(1);
        List<String> senseWord =new LinkedList<String>();
        IndexWord[] disWDArray=disWDSet.getIndexWordArray();
        System.out.println(disWDArray.length);
        //System.out.println(disWDArray.getSense(1));
        for(int i=0;i<disWDArray.length;i++){
            int size=disWDArray[i].getSenseCount();
            System.out.print(size);
            Synset[] senseArray = disWDArray[i].getSenses();
            for(int j=0;j<size;j++){
                senseWord.clear();
                Word[] tmp=senseArray[j].getWords();
                for(int k=0;k<tmp.length;k++){
                    senseWord.add(tmp[k].getLemma());
                }
                String[] tmpStr =senseArray[j].getGloss().split(" ");
                for(int k=0;k<tmpStr.length;k++){
                    senseWord.add(tmpStr[k]);
                }
                HashSet hs = new HashSet();
                hs.addAll(senseWord);
                senseWord.clear();
                senseWord.addAll(hs);
                hs.clear();
                hs.addAll(contextWDArray);
                contextWDArray.clear();
                contextWDArray.addAll(hs);
                Pointer[] pointers = senseArray[j].getPointers();
                for (int k = 0; k < pointers.length; k++) {							
                    if(pointers[k].getType().equals(PointerType.ONTO_NODES)) {	// For ontology relation
			String mytmp=dictionary.getOntoSynset(pointers[k].getOntoPointer()).getOntoNodes();
                        //out.write(mytmp);
                        String[] tmp2=mytmp.split(" ");
                        for(int u=0;u<tmp2.length;u++){
                            senseWord.add(tmp2[u]);
                        }
                    } else {
			pointers[k].getTargetSynset();
                    }							
						}
                
                int overlap=0;
                int senseSize=senseWord.size();
                int contextArraySize=contextWDArray.size();
                for(int k=0;k<senseSize;k++){
                    for(int p=0;p<contextArraySize;p++){
                        if(contextWDArray.get(p).equals(senseWord.get(k))){
                            overlap++;
                            System.out.println("Same word:"+contextWDArray.get(p));
                        }
                    }
                }
                for(int d=0;d<senseSize-1;d++){
                        out.write(senseWord.get(d));
                        out.write(" ");
                }
                System.out.println("Yo ho ho!");
                out.write(senseWord.get(senseSize-1));
                out.write("\n");
                //System.out.println(senseWord.size());
                if(overlap>max_overlap){
                    max_overlap=overlap;
                    System.out.println(overlap);
                    System.out.println(senseWord);
                    sense=j;
                    disPOS=disWDArray[i].getPOS();
                    System.out.println(sense+" "+disPOS);
                }
            }
        }
        out.close();
        System.out.println(disPOS);
        return sense;
        
    }
    public static void main(String args[]) throws UnsupportedEncodingException, FileNotFoundException, IOException, JHWNLException, Exception{
            BufferedReader inputWordsFile = null;
		try {
			inputWordsFile = new BufferedReader(new InputStreamReader (new FileInputStream ("sentence.txt"), "UTF8"));
		} catch( FileNotFoundException e){
			System.err.println("Error opening input words file.");
			System.exit(-1);
		} catch (UnsupportedEncodingException e) {
			System.err.println("UTF-8 encoding is not supported.");
			System.exit(-1);
		}
                String inputLine,word;
	long[] synsetOffsets;
            if((inputLine = inputWordsFile.readLine()) != null){
                if((word=inputWordsFile.readLine())!=null){
                    int sense = simple_lesk(inputLine,word);
                    System.out.println(sense);
                }
            }
    }
}
