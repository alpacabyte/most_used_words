#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cctype>

//declaring class of Words
class Word {
public:
    std::string name;
    int count = 1;
    int topCount = 0;
    Word* next;

    //Constructor of Word Class
    Word(std::string name) {
        this->name = name;
    }

    Word() {}
};

int main() {
    //initializing first element of linkedList
    Word* head = new Word("NULL");
    //initializing last element of linkedList
    Word* last = head;
    last->next = nullptr;
    //initializing iterator element of linkedList
    Word* iter;

    //initializing for stopWords array
    std::string stopWords[571] = { "a", "a�s", "able", "about", "above", "according", "accordingly", "across", "actually", "after", "afterwards", "again", "against", "ain�t", "all", "allow",
        "allows", "almost", "alone", "along", "already", "also", "although", "always", "am", "among", "amongst", "an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything",
        "anyway", "anyways", "anywhere", "apart", "appear", "appreciate", "appropriate", "are", "aren�t", "around", "as", "aside", "ask", "asking", "associated", "at", "available", "away",
        "awfully", "b", "be", "became", "because", "become", "becomes", "becoming", "been", "before", "beforehand", "behind", "being", "believe", "below", "beside", "besides", "best", "better",
        "between", "beyond", "both", "brief", "but", "by", "c", "c�mon", "c�s", "came", "can", "can�t", "cannot", "cant", "cause", "causes", "certain", "certainly", "changes", "clearly", "co",
        "com", "come", "comes", "concerning", "consequently", "consider", "considering", "contain", "containing", "contains", "corresponding", "could", "couldn�t", "course", "currently", "d",
        "definitely", "described", "despite", "did", "didn�t", "different", "do", "does", "doesn�t", "doing", "don�t", "done", "down", "downwards", "during", "e", "each", "edu", "eg", "eight",
        "either", "else", "elsewhere", "enough", "entirely", "especially", "et", "etc", "even", "ever", "every", "everybody", "everyone", "everything", "everywhere", "ex", "exactly", "example",
        "except", "f", "far", "few", "fifth", "first", "five", "followed", "following", "follows", "for", "former", "formerly", "forth", "four", "from", "further", "furthermore", "g", "get",
        "gets", "getting", "given", "gives", "go", "goes", "going", "gone", "got", "gotten", "greetings", "h", "had", "hadn�t", "happens", "hardly", "has", "hasn�t", "have", "haven�t", "having",
        "he", "he�s", "hello", "help", "hence", "her", "here", "here�s", "hereafter", "hereby", "herein", "hereupon", "hers", "herself", "hi", "him", "himself", "his", "hither", "hopefully",
        "how", "howbeit", "however", "i", "i�d", "i�ll", "i�m", "i�ve", "ie", "if", "ignored", "immediate", "in", "inasmuch", "inc", "indeed", "indicate", "indicated", "indicates", "inner",
        "insofar", "instead", "into", "inward", "is", "isn�t", "it", "it�d", "it�ll", "it�s", "its", "itself", "j", "just", "k", "keep", "keeps", "kept", "know", "knows", "known", "l", "last",
        "lately", "later", "latter", "latterly", "least", "less", "lest", "let", "let�s", "like", "liked", "likely", "little", "look", "looking", "looks", "ltd", "m", "mainly", "many", "may",
        "maybe", "me", "mean", "meanwhile", "merely", "might", "more", "moreover", "most", "mostly", "much", "must", "my", "myself", "n", "name", "namely", "nd", "near", "nearly", "necessary",
        "need", "needs", "neither", "never", "nevertheless", "new", "next", "nine", "no", "nobody", "non", "none", "noone", "nor", "normally", "not", "nothing", "novel", "now", "nowhere", "o",
        "obviously", "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one", "ones", "only", "onto", "or", "other", "others", "otherwise", "ought", "our", "ours", "ourselves", "out",
        "outside", "over", "overall", "own", "p", "particular", "particularly", "per", "perhaps", "placed", "please", "plus", "possible", "presumably", "probably", "provides", "q", "que", "quite",
        "qv", "r", "rather", "rd", "re", "really", "reasonably", "regarding", "regardless", "regards", "relatively", "respectively", "right", "s", "said", "same", "saw", "say", "saying", "says",
        "second", "secondly", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves", "sensible", "sent", "serious", "seriously", "seven", "several", "shall", "she",
        "should", "shouldn�t", "since", "six", "so", "some", "somebody", "somehow", "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry", "specified",
        "specify", "specifying", "still", "sub", "such", "sup", "sure", "t", "t�s", "take", "taken", "tell", "tends", "th", "than", "thank", "thanks", "thanx", "that", "that�s", "thats", "the",
        "their", "theirs", "them", "themselves", "then", "thence", "there", "there�s", "thereafter", "thereby", "therefore", "therein", "theres", "thereupon", "these", "they", "they�d",
        "they�ll", "they�re", "they�ve", "think", "third", "this", "thorough", "thoroughly", "those", "though", "three", "through", "throughout", "thru", "thus", "to", "together", "too",
        "took", "toward", "towards", "tried", "tries", "truly", "try", "trying", "twice", "two", "u", "un", "under", "unfortunately", "unless", "unlikely", "until", "unto", "up", "upon",
        "us", "use", "used", "useful", "uses", "using", "usually", "uucp", "v", "value", "various", "very", "via", "viz", "vs", "w", "want", "wants", "was", "wasn�t", "way", "we", "we�d",
        "we�ll", "we�re", "we�ve", "welcome", "well", "went", "were", "weren�t", "what", "what�s", "whatever", "when", "whence", "whenever", "where", "where�s", "whereafter", "whereas",
        "whereby", "wherein", "whereupon", "wherever", "whether", "which", "while", "whither", "who", "who�s", "whoever", "whole", "whom", "whose", "why", "will", "willing", "wish", "with",
        "within", "without", "won�t", "wonder", "would", "would", "wouldn�t", "x", "y", "yes", "yet", "you", "you�d", "you�ll", "you�re", "you�ve", "your", "yours", "yourself", "yourselves",
        "z", "zero" };

    //initializing the counter
    int start = clock();

    std::ifstream in;
    std::ofstream out;

    // word string is for each words and docs string is for 1 file
    std::string word, docs, allDocs;

    //boolean for if that part is in Bodies
    bool go = false;

    int countKelime = 0;

    // find words
    for (int i = 0; i < 22; i++) {
        // that opens files
        if (i < 10) {
            in.open("reut2-00" + std::to_string(i) + ".sgm");
        }

        else {
            in.open("reut2-0" + std::to_string(i) + ".sgm");
        }

        int pageWordCount = 0;

        // this part for reading the files
        while (in >> word) {
            // this part is for finding if the word is in bodies
            int isBody1 = word.find("<BODY>"), isBody2 = word.find("</BODY>"), isLt = word.find("&lt;");

            if (isBody1 != -1) {
                go = true;
                word.replace(0, isBody1 + 6, "");
            }

            else if (isBody2 != -1) {
                go = false;
            }

            // this is for checking &lt
            else if (isLt != -1) {
                word.replace(0, isBody1 + 5, "");
            }

            //if it is in bodies this part will execute for that word
            if (go) {
                // this bool for if it has any number
                bool isDigit2 = false;

                // this part for checking for if it has numbers, punctuation and turning upper cases into lower cases
                for (int i = 0, len = word.size(); i < len; i++)
                {
                    if (isdigit((word[i]))) {
                        isDigit2 = true;
                        break;
                    }

                    if (ispunct(word[i]))
                    {
                        //if we find '-' or '/', we are simply changing it to " "
                        if (word[i] == '-' || word[i] == '/') {
                            word.replace(i, 1, " ");
                        }
                        //anything else will be deleted
                        else if (word[i] != '\'')
                        {
                            word.erase(i--, 1);
                            len = word.size();
                        }
                    }

                    else {
                        //this is for lowercases
                        word[i] = tolower(word[i]);
                    }

                }
                if (!isDigit2) {
                    // if that string has no digits, it will adding to the docs string
                    docs += " " + word;
                    countKelime++;
                    pageWordCount++;
                }

            }
        }
        std::cout << "Page " << i + 1 << "/22" << " is refactored. It has " << pageWordCount << " countable words. Total count is now: " << countKelime << std::endl << std::endl;
        in.close();

        //this string will hold our temporary words for finding new words or counting them up
        std::string tempWord = "NULL";
        //that for loop is searching all chars of the docs string
        for (auto x : docs) {
            //if it finds any chars from bottom, it will stop the tempword at there and it will check for that word is in our list. If it is not in our list
            // it will create new object of it. If it is in our list, it will simply count it up.
            if ((x == ' ' || x == '\n' || x == '\t') && tempWord != "") {
                //I used iterator in there for searching in our list for tempWord, if it finds that, the found bool will be true and that objects counter
                //will be increased
                bool found = false;
                iter = head;
                while (iter != nullptr) {
                    if (iter->name == tempWord) {
                        iter->count++;
                        found = true;
                        break;
                    }
                    iter = iter->next;
                }

                //if found bool is false, it will check for stopWords list
                if (!found) {
                    bool isStop = false;
                    for (int i = 0; i < 571; i++) {
                        if (tempWord == stopWords[i]) {
                            isStop = true;
                            break;
                        }
                    }
                    //if it is not in stopWords list, then it will create new object of that word
                    if (!isStop) {
                        last->next = new Word(tempWord);
                        last = last->next;
                        last->next = nullptr;
                    }
                }
                tempWord = "";
            }
            else {
                tempWord += x;
            }
        }

        allDocs += docs;
        docs = "";
    }

    out.open("refactoredText.txt");
    out << allDocs;
    std::cout << "Refactored text created as refactoredText.txt" << std::endl << std::endl;
    out.close();


    //initializing for top10 Word objects array
    Word* top10[10];
    for (int i = 0; i < 10; i++) {
        top10[i] = head->next;
    }

    //this will find top10
    for (int i = 0; i < 10; i++) {
        iter = head->next;
        while (iter != nullptr) {
            //if iterator finds any counter that higher than our top list element, it will change it to iterator.
            if (iter->count > top10[i]->count) {
                top10[i] = iter;
            }
            iter = iter->next;
        }

        //changing found top object's count to topCount then count to 0, because We dont want to find same object in each top element
        top10[i]->topCount = top10[i]->count;
        top10[i]->count = 0;

    }

    std::cout << "Word " << "\t" << "Count" << std::endl;

    //and printing the name of top objects and topCounters of them
    for (int i = 0; i < 10; i++) {
        std::cout << top10[i]->name << "\t" << top10[i]->topCount << std::endl;
    }

    int end = clock();

    std::cout << std::endl << "Total Count: " << countKelime << std::endl << std::endl;

    //finally printing the total time
    std::cout << "Total Elapsed Time: " << ((float)end - start) / CLOCKS_PER_SEC << " seconds";

    return 0;

}
