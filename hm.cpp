#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<cctype>
#include<cstdlib>
#include<ctime>
using namespace std;
struct Phrase
{
    string text;
    string :: size_type guessesRequired;
    bool isUsed = false;
};
bool isLetter(char letter);
string phraseWithBlanks(const string text, const string correctGuess);
int uniqueLetterCount(const string text);
int loadPhrasesFromFile(string file, Phrase phrase[],int length);
void printPhrase(Phrase phrase[],int length);
void swap(Phrase phrase[],int index1 , int index2);
int smallestValue(const Phrase phrase[], int length, int startIndex);
void selectionSort(Phrase phrase[], int length);
string phraseWithBlanks(const string text, string correct,char guess);
void drawGallows(int missCount);
int getDifficultyLevel();
int isUsed(Phrase phrase[],int range,int max , int min);
void runGame(Phrase phrase[],int phraseCount);
bool isInside(const string text, char letter);
int getRandomLevel(Phrase phrase[],int length,int level);
int randomNumber(int min , int max);
int main()
{
    string file = "default.txt";
    const int LENGTH = 100;
    int phraseCount;
    Phrase phrase[LENGTH];
    char guess; 
    phraseCount = loadPhrasesFromFile(file,phrase,LENGTH);
    selectionSort(phrase,phraseCount);
    runGame(phrase,phraseCount);
    return 0;
}
int randomNumber(int min , int max)
{
    int range = max - min + 1;
    return rand() % range - min;
}
int loadPhrasesFromFile(string file,Phrase phrase [],int length)
{
    int index =0;
    string line;
    ifstream in(file); 
    if(!in.is_open())
    {
        cout<<"The file did not open"<<endl;
        return 0;

    }
    while(getline(in,line))
    {

        phrase[index].text = line;
        phrase[index].isUsed = false;
        phrase[index].guessesRequired = uniqueLetterCount(line);
        ++index;
    }
    in.close();
    return index;
}
void printPhrase(Phrase phrase[],int length)
{
    int index;
    for(index =0; index < length; ++index)
    {
        cout<<setw(50) << left << phrase[index].text<<" "<< setw(3) << right << phrase[index].guessesRequired<<endl;
    }

}
int uniqueLetterCount( const string text)
{
    string uniqueLetters;
    char lowercase;
    for (string::size_type index = 0; index < text.size(); index++)
    {
        lowercase = tolower(text[index]);
        if (isalpha(lowercase) && uniqueLetters.find(lowercase) == string::npos)
        {
            uniqueLetters += lowercase;
        }
    }
    return uniqueLetters.size();
}
void swap(Phrase phrase[],int index1 , int index2)
{
    Phrase temp = phrase[index1];
    phrase[index1] = phrase[index2];
    phrase[index2] = temp;
}
int smallestValue(const Phrase phrase[], int length, int startIndex)
{
    int minIndex = startIndex;
    for(int index = startIndex +1; index < length; ++index)
    {
        if(phrase[minIndex].guessesRequired > phrase[index].guessesRequired)
        {
            minIndex = index;
        }
    }

    return minIndex;
}

void selectionSort(Phrase phrase[], int length)
{
    int minIndex;
    for(int firsIndexOfUnsorted = 0; firsIndexOfUnsorted < length;
        ++firsIndexOfUnsorted)
        {
            minIndex = smallestValue(phrase,length,firsIndexOfUnsorted);

            if(firsIndexOfUnsorted != minIndex)
            {
            swap(phrase,firsIndexOfUnsorted, minIndex);
            }
        }
}

void drawGallows(int missCount)
{
    cout
        << "   +----+     \n"
        << "   |    |     \n";

    switch (missCount)
    {
    case 0:
        cout
            << "   |       \n"
            << "   |       \n"
            << "   |       \n"
            << "   |       \n";
        break;

    case 1:
        cout
            << "   |    O  \n"
            << "   |    |  \n"
            << "   |       \n"
            << "   |       \n";
        break;

    case 2:
        cout
            << "   |    O  \n"
            << "   |   /|  \n"
            << "   |       \n"
            << "   |       \n";
        break;

    case 3:
        
        cout
            << "   |    O   \n"
            << "   |   /|\\ \n"
            << "   |        \n"
            << "   |        \n";
        break;

    case 4:
        cout
            << "   |    O   \n"
            << "   |   /|\\ \n"
            << "   |     \\ \n"
            << "   |        \n";
        break;

    default:
        cout
            << "   |    O    \n"
            << "   |   /|\\  \n"
            << "   |   / \\  \n"
            << "   |You're Dead\n";
    }


    
    cout << "  =============\n" << endl;
}
bool isLetter(char letter)
{
      return isalpha(letter);
}

bool isInside(const string text, char letter)
{
    if(text.find(letter) != string::npos)
    {
        return true;
    }
    return false;
}
string phraseWithBlanks(const string text,string correct, char guess)
{
    string gameWord;
           for(string::size_type index =0; index < text.length(); ++index)

       {

          
             if(!isLetter(text[index]) || isInside(correct, tolower(text[index])))

             {

                   gameWord += text[index];

             }

             else 
             {

                   gameWord += "_";

             }
       }



       return gameWord;


}
int isUsed(Phrase phrase[],int range,int max, int min)
{
  
    unsigned int seed = static_cast<unsigned int>(time(NULL));

    srand(seed);
    int index;
    do{
        index = rand() % range + min;
        phrase[index].isUsed;

    }while(phrase[index].isUsed != false);

    return index;
}
int getRandomLevel(Phrase phrase[],int length,int difficulty)
{

    int range = length/3;
    int min = range*(difficulty -1);
    int max = range *difficulty -1;
        switch(difficulty)
        {
            case 1:
            {
                return isUsed(phrase,range,max,min);

            }
            case 2:
            {
                return isUsed(phrase,range,max,min);

            }
            case 3:
            {
                return isUsed(phrase,range,max,min);


            }
            default:
                cout<<"There is an error"<<endl;
                return 0;

        }
}
int getDifficultyLevel()
{
    int level;
    bool valid = false;
    while(valid != true)
    {
    cout<<"Difficulty level:"<<left<<endl;
    cout<<setw(10)<<"1)"<<setw(15)<<left<<"Easy"<<endl;
    cout<<setw(10)<<"2)"<<setw(15)<<left<<"Medium"<<endl;
    cout<<setw(10)<<"3)"<<setw(15)<<left<<"Hard"<<endl;
    cout<<"Pick difficulty (1 - 3): ";
    cin>>level;
        if(level <= 0 && level > 3)
        {
            cout<<"Please enter a number between 1 -3"<<endl;
            cin>>level;
            valid = false;
        }
        else{
            valid = true;
        }
    }

    return level;
}
void runGame(Phrase phrase[],int phraseCount)
{
    int missCount=0;
    char guess;
    string incorrectGuesses;
    string correctGuess;
    char answer;
    int guessCount;
    char lowerGuess;
    int unique;
    int correctCount=0;
    int level;

    do{
        int difficulty = getDifficultyLevel();
        level = getRandomLevel(phrase,phraseCount,difficulty);

            do
            {

                drawGallows(missCount);
                cout<<""<<endl;
                cout<<phraseWithBlanks(phrase[level].text,correctGuess,guess)
                <<endl;
                  
                    cout<<"Previous incorrect guess: "<<incorrectGuesses<<endl;
                    cout<<" "<<endl;
                    cout<<"Please enter your guess: ";
                    cout<<" "<<endl;
                    cin>>guess;
                    lowerGuess = tolower(guess);
                        if(!isInside(phrase[level].text,lowerGuess) &&
                            !isInside(phrase[level].text,toupper(guess)))
                        
                        {
                            if(isInside(incorrectGuesses,lowerGuess) == false)
                            {
                            cout<<"Sorry "<<guess<<" is incorrect"<<endl;
                            ++missCount;
                            incorrectGuesses += guess;
                            }
                            else
                            {
                                cout<<"Oops you already guess wrong with this"
                                <<endl;
                            }
                        }
                        else
                        {

                                if(isInside(correctGuess,lowerGuess)== true)
                                {
                                    cout<<"Sorry but you have already used this"
                                    <<endl;
                                }
                                else
                                {
                                cout<<"Great you "<< guess<<" is correct"<<endl;
                                correctGuess+= guess;
                                ++correctCount;
                                }
                        }
                    cout<<endl;
                    cout<<endl;        
                    ++guessCount;
                    unique = uniqueLetterCount(phrase[level].text);
                    if(correctCount == unique)
                    {
                        cout<<"Congraduations You WON!"<<endl;
                        phrase[level].isUsed = true;
                       
                        break;
                    }
                    if(missCount == 5)
                    {
                      
                        drawGallows(5);
                        phrase[level].isUsed = true;
                    }

                }while(missCount != 5 ||  guess<=unique);

        cout<<"Thanks For playing would you like to play again? (Y/N)"<<endl;
        cin>>answer;
        missCount = 0;
        incorrectGuesses = " ";
        correctCount = 0;
        correctGuess = " ";
    }while(tolower(answer) == 'y');
    cout<<"hank you for playing"<<endl;
}